// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#include "cc/aead/aead_config.h"

#include "cc/key_manager.h"
#include "cc/registry.h"
#include "cc/aead/aes_gcm_key_manager.h"
#include "cc/util/status.h"

namespace util = crypto::tink::util;

namespace crypto {
namespace tink {

// static
util::Status AeadConfig::RegisterStandardKeyTypes() {
  return RegisterKeyManager(new AesGcmKeyManager());
}

// static
util::Status AeadConfig::RegisterLegacyKeyTypes() {
  return util::Status::OK;
}

// static
util::Status AeadConfig::RegisterKeyManager(KeyManager<Aead>* key_manager) {
  if (key_manager == nullptr) {
    return util::Status(util::error::INVALID_ARGUMENT,
                        "Parameter 'key_manager' must be non-null.");
  }
  return Registry::get_default_registry().RegisterKeyManager(
      key_manager->get_key_type(), key_manager);
}

}  // namespace tink
}  // namespace crypto
