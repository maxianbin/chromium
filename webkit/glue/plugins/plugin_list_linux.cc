// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "config.h"

#include "webkit/glue/plugins/plugin_list.h"

#include "base/file_util.h"
#include "base/logging.h"

namespace NPAPI {

void PluginList::PlatformInit() {
}

void PluginList::GetPluginDirectories(std::vector<FilePath>* plugin_dirs) {
  NOTIMPLEMENTED();
}

void PluginList::LoadPluginsFromDir(const FilePath& path) {
  file_util::FileEnumerator enumerator(path,
                                       false, // not recursive
                                       file_util::FileEnumerator::DIRECTORIES);
  for (FilePath path = enumerator.Next(); !path.value().empty();
       path = enumerator.Next()) {
    LoadPlugin(path);
  }
}

bool PluginList::ShouldLoadPlugin(const WebPluginInfo& info) {
  NOTIMPLEMENTED();
  return true;
}

void PluginList::LoadInternalPlugins() {
  // none for now
  NOTIMPLEMENTED();
}

} // namespace NPAPI

