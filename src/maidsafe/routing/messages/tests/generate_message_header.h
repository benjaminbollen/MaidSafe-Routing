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

#ifndef MAIDSAFE_ROUTING_MESSAGES_TESTS_GENERATE_MESSAGE_HEADER_H_
#define MAIDSAFE_ROUTING_MESSAGES_TESTS_GENERATE_MESSAGE_HEADER_H_

#include "maidsafe/common/utils.h"
#include "maidsafe/routing/message_header.h"

namespace maidsafe {

namespace routing {

namespace test {


inline MessageHeader GenerateMessageHeader() {
  return MessageHeader{
      DestinationAddress{
          std::make_pair(Destination(Address{RandomString(Address::kSize)}), boost::none)},
      SourceAddress{NodeAddress(Address{RandomString(Address::kSize)}), boost::none, boost::none},
      MessageId{RandomUint32()}, rsa::Sign(rsa::PlainText{RandomString(Address::kSize)},
                                           asymm::GenerateKeyPair().private_key)};
}

}  // namespace test

}  // namespace routing

}  // namespace maidsafe

#endif  // MAIDSAFE_ROUTING_MESSAGES_TESTS_GENERATE_MESSAGE_HEADER_H_