/*  Copyright 2014 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#ifndef MAIDSAFE_ROUTING_MESSAGES_FIND_GROUP_RESPONSE_H_
#define MAIDSAFE_ROUTING_MESSAGES_FIND_GROUP_RESPONSE_H_

#include <vector>

#include "maidsafe/common/config.h"
#include "maidsafe/passport/types.h"

#include "maidsafe/routing/types.h"

namespace maidsafe {

namespace routing {

class FindGroupResponse {
 public:
  FindGroupResponse() = default;
  ~FindGroupResponse() = default;

  FindGroupResponse(Address target_id, std::vector<passport::PublicPmid> group)
      : target_id_(std::move(target_id)), group_(std::move(group)) {}

  FindGroupResponse(FindGroupResponse&& other) MAIDSAFE_NOEXCEPT
      : target_id_(std::move(other.target_id_)),
        group_(std::move(other.group_)) {}

  FindGroupResponse& operator=(FindGroupResponse&& other) MAIDSAFE_NOEXCEPT {
    target_id_ = std::move(other.target_id_);
    group_ = std::move(other.group_);
    return *this;
  }

  FindGroupResponse(const FindGroupResponse&) = delete;
  FindGroupResponse& operator=(const FindGroupResponse&) = delete;

  template <typename Archive>
  Archive& load(Archive& archive) {
    group_.clear();
    std::size_t group_size(0);
    archive(target_id_, group_size);
    for (std::size_t i = 0; i < group_size; ++i) {
      group_.emplace_back();
      archive(group_.back());
    }
    return archive;
  }

  template <typename Archive>
  Archive& save(Archive& archive) const {
    archive(target_id_, group_.size());
    for (const auto& public_pmid : group_)
      archive(public_pmid);
    return archive;
  }

  Address target_id() const { return target_id_; }
  std::vector<passport::PublicPmid> group() const { return group_; }

 private:
  Address target_id_;
  std::vector<passport::PublicPmid> group_;
};

}  // namespace routing

}  // namespace maidsafe

#endif  // MAIDSAFE_ROUTING_MESSAGES_FIND_GROUP_RESPONSE_H_
