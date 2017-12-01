/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/dreamview/backend/util/json_util.h"

#include "google/protobuf/util/json_util.h"
#include "gtest/gtest.h"
#include "modules/dreamview/proto/hmi_status.pb.h"

namespace apollo {
namespace dreamview {
namespace util {

using Json = nlohmann::json;

TEST(JsonUtilTest, ProtoToTypedJson) {
  HMIStatus status;
  status.set_current_map("MapA");
  const std::string json_str = JsonUtil::ProtoToTypedJson("TypeA", status);

  Json json_obj = Json::parse(json_str.begin(), json_str.end());
  EXPECT_EQ("TypeA", json_obj["type"]);
  EXPECT_EQ("MapA", json_obj["data"]["currentMap"]);
}

TEST(JsonUtilTest, GetStringFromJson) {
  Json json_obj;
  json_obj["key1"] = 0;
  json_obj["key2"] = "";
  json_obj["key3"] = "value2";

  std::string value;
  // No such key.
  EXPECT_FALSE(JsonUtil::GetStringFromJson(json_obj, "key0", &value));
  // Value is not string.
  EXPECT_FALSE(JsonUtil::GetStringFromJson(json_obj, "key1", &value));
  // Empty string.
  EXPECT_TRUE(JsonUtil::GetStringFromJson(json_obj, "key2", &value));
  EXPECT_TRUE(value.empty());
  // Non empty string.
  EXPECT_TRUE(JsonUtil::GetStringFromJson(json_obj, "key3", &value));
  EXPECT_EQ("value2", value);
}

}  // namespace util
}  // namespace dreamview
}  // namespace apollo
