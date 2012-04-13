// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_DOM_STORAGE_COMMON_H_
#define CONTENT_COMMON_DOM_STORAGE_COMMON_H_
#pragma once

#include "build/build_config.h"

#include "base/basictypes.h"
#include "webkit/dom_storage/dom_storage_types.h"

#ifdef ENABLE_NEW_DOM_STORAGE_BACKEND
// TODO(michaeln): delete this file
#else
const int64 kLocalStorageNamespaceId = 0;
const int64 kInvalidSessionStorageNamespaceId = kLocalStorageNamespaceId;

enum DOMStorageType {
  DOM_STORAGE_LOCAL = 0,
  DOM_STORAGE_SESSION
};
#endif  // ENABLE_NEW_DOM_STORAGE_BACKEND
#endif  // CONTENT_COMMON_DOM_STORAGE_COMMON_H_
