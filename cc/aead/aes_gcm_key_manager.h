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

#include <algorithm>
#include <vector>

#ifndef TINK_AEAD_AES_GCM_KEY_MANAGER_H_
#define TINK_AEAD_AES_GCM_KEY_MANAGER_H_

#include "cc/aead.h"
#include "cc/key_manager.h"
#include "cc/util/errors.h"
#include "cc/util/status.h"
#include "cc/util/statusor.h"
#include "google/protobuf/message.h"
#include "proto/aes_gcm.pb.h"
#include "proto/tink.pb.h"

namespace crypto {
namespace tink {

class AesGcmKeyManager : public KeyManager<Aead> {
 public:
  AesGcmKeyManager() : key_type_(kKeyType) {}

  // Constructs an instance of AES-GCM Aead for the given 'key_data',
  // which must contain AesGcmKey-proto.
  crypto::tink::util::StatusOr<std::unique_ptr<Aead>> GetPrimitive(
      const google::crypto::tink::KeyData& key_data) const override;

  // Constructs an instance of AES-GCM Aead for the given 'key',
  // which must be AesGcmKey-proto.
  crypto::tink::util::StatusOr<std::unique_ptr<Aead>>
  GetPrimitive(const google::protobuf::Message& key) const override;

  // Generates a new random AesGcmKey, based on the specified 'key_template',
  // which must contain AesGcmKeyFormat-proto.
  crypto::tink::util::StatusOr<std::unique_ptr<google::protobuf::Message>>
      NewKey(const google::crypto::tink::KeyTemplate& key_template)
      const override;

  // Returns the type_url identifying the key type handled by this manager.
  const std::string& get_key_type() const override;

  // Returns the version of this key manager.
  uint32_t get_version() const override;

  virtual ~AesGcmKeyManager() {}

 private:
  static constexpr char kKeyTypePrefix[] = "type.googleapis.com/";
  static constexpr char kKeyType[] =
      "type.googleapis.com/google.crypto.tink.AesGcmKey";

  std::string key_type_;

  // Constructs an instance of AES-GCM Aead for the given 'key'.
  crypto::tink::util::StatusOr<std::unique_ptr<Aead>>
  GetPrimitiveImpl(const google::crypto::tink::AesGcmKey& key) const;

  crypto::tink::util::Status Validate(
      const google::crypto::tink::AesGcmParams& params) const;
  crypto::tink::util::Status Validate(
      const google::crypto::tink::AesGcmKey& key) const;
  crypto::tink::util::Status Validate(
      const google::crypto::tink::AesGcmKeyFormat& key_format) const;
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_AEAD_AES_GCM_KEY_MANAGER_H_
