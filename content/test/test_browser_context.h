// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_TEST_TEST_BROWSER_CONTEXT_H_
#define CONTENT_TEST_TEST_BROWSER_CONTEXT_H_
#pragma once

#include "base/compiler_specific.h"
#include "base/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/scoped_temp_dir.h"
#include "content/public/browser/browser_context.h"

namespace content {
class MockResourceContext;
}

class TestBrowserContext : public content::BrowserContext {
 public:
  TestBrowserContext();
  virtual ~TestBrowserContext();

  // Takes ownership of the temporary directory so that it's not deleted when
  // this object is destructed.
  FilePath TakePath();

  void SetSpecialStoragePolicy(quota::SpecialStoragePolicy* policy);

  virtual FilePath GetPath() OVERRIDE;
  virtual bool IsOffTheRecord() const OVERRIDE;
  virtual content::DownloadManager* GetDownloadManager() OVERRIDE;
  virtual net::URLRequestContextGetter* GetRequestContext() OVERRIDE;
  virtual net::URLRequestContextGetter* GetRequestContextForRenderProcess(
      int renderer_child_id) OVERRIDE;
  virtual net::URLRequestContextGetter* GetRequestContextForMedia() OVERRIDE;
  virtual content::ResourceContext* GetResourceContext() OVERRIDE;
  virtual content::GeolocationPermissionContext*
      GetGeolocationPermissionContext() OVERRIDE;
  virtual content::SpeechRecognitionPreferences*
      GetSpeechRecognitionPreferences() OVERRIDE;
  virtual bool DidLastSessionExitCleanly() OVERRIDE;
  virtual quota::SpecialStoragePolicy* GetSpecialStoragePolicy() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(DOMStorageTest, SessionOnly);
  FRIEND_TEST_ALL_PREFIXES(DOMStorageTest, SaveSessionState);

  scoped_ptr<content::MockResourceContext> resource_context_;
  ScopedTempDir browser_context_dir_;
  scoped_refptr<quota::SpecialStoragePolicy> special_storage_policy_;

  DISALLOW_COPY_AND_ASSIGN(TestBrowserContext);
};

#endif  // CONTENT_TEST_TEST_BROWSER_CONTEXT_H_
