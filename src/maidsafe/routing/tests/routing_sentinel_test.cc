/*  Copyright 2015 MaidSafe.net limited

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


#include <chrono>
#include <thread>

#include "maidsafe/routing/sentinel.h"
#include "maidsafe/common/test.h"
#include "maidsafe/common/node_id.h"
#include "maidsafe/common/utils.h"
#include "maidsafe/routing/types.h"


namespace maidsafe {

namespace routing {

namespace test {


// structure to track messages sent to sentinel and what sentinel result should be
class SignatureGroup {
 public:
  SignatureGroup(GroupAddress, size_t);

 private:
  GroupAddress group_address_;
  std::vector<std::pair<Identity, PublicPmid>> nodes_;
};

// persistent sentinel throughout all sentinel tests
//
class SentinelMessageSimulation : public testing::Test {
 public:
  SentinelMessageSimulation()
    : sentinel_(SendGetClientKey, SendGetGroupKey) {}

  void SendGetClientKey(Address node_address);
  void SendGetGroupKey(GroupAddress group_address);

  // Add a correct, cooperative group of indictated total size and responsive quorum
  void AddCorrectGroup(GroupAddress group_address, size_t group_size = GroupSize,
                       size_t active_quorum = QuorumSize);

 protected:
  Sentinel sentinel_;
  mutable std::mutex sentinel_mutex_;

 private:
  std::vector<SignatureGroup> groups_;
};

void SentinelMessageSimulation::SendGetClientKey(Address node_address) {

}

void SentinelMessageSimulation::SendGetGroupKey(GroupAddress group_address) {
  //std::lock_guard<std::mutex> lock(mutex_);
  auto itr = std::find_if(std::begin(groups_), std::end(groups_), );
}

// first try for specific message type, generalise later
// PutData is chosen as fundamental type with data payload.
TEST(RoutingTest, BEH_SentinelSimpleAdd) {

  NonEmptyString data(RandomString(100));
  SerialisedData message_data(std::begin(data.string()), std::end(data.string()));
  PutData put_message(ImmutableData, message_data);


}

}  // namespacce test

}  // namespace routing

}  // namespace maidsafe
