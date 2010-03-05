// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ssl/ssl_client_auth_handler.h"

#include <cryptuiapi.h>
#pragma comment(lib, "cryptui.lib")

#include "app/l10n_util.h"
#include "base/string_util.h"
#include "chrome/browser/browser_list.h"
#include "chrome/browser/browser.h"
#include "chrome/browser/browser_window.h"
#include "chrome/browser/chrome_thread.h"
#include "grit/generated_resources.h"
#include "net/url_request/url_request.h"

void SSLClientAuthHandler::DoSelectCertificate() {
  net::X509Certificate* cert = NULL;
  // TODO(jcampan): replace this with our own cert selection dialog.
  // CryptUIDlgSelectCertificateFromStore is blocking (but still processes
  // Windows messages), which is scary.
  HCERTSTORE client_certs = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, NULL,
                                          0, NULL);
  BOOL ok;
  for (size_t i = 0; i < cert_request_info_->client_certs.size(); ++i) {
    PCCERT_CONTEXT cc = cert_request_info_->client_certs[i]->os_cert_handle();
    ok = CertAddCertificateContextToStore(client_certs, cc,
                                          CERT_STORE_ADD_ALWAYS, NULL);
    DCHECK(ok);
  }

  HWND browser_hwnd = NULL;
  Browser* browser = BrowserList::GetLastActive();
  if (browser)
    browser_hwnd = browser->window()->GetNativeHandle();

  std::wstring title = l10n_util::GetString(IDS_CLIENT_CERT_DIALOG_TITLE);
  std::wstring text = l10n_util::GetStringF(
      IDS_CLIENT_CERT_DIALOG_TEXT,
      ASCIIToWide(cert_request_info_->host_and_port));
  PCCERT_CONTEXT cert_context = CryptUIDlgSelectCertificateFromStore(
      client_certs, browser_hwnd, title.c_str(), text.c_str(), 0, 0, NULL);

  if (cert_context) {
    cert = net::X509Certificate::CreateFromHandle(
        cert_context,
        net::X509Certificate::SOURCE_LONE_CERT_IMPORT);
  }

  ok = CertCloseStore(client_certs, CERT_CLOSE_STORE_CHECK_FLAG);
  DCHECK(ok);

  CertificateSelected(cert);
}
