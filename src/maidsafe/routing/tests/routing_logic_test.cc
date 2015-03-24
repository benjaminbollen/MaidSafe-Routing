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

#include <memory>
#include <vector>

#include "maidsafe/common/test.h"
#include "maidsafe/common/utils.h"

#include "maidsafe/passport/types.h"
#include "maidsafe/passport/passport.h"

#include "maidsafe/routing/types.h"

namespace maidsafe {

namespace routing {

namespace test {

using GroupsOfGroup = std::vector<std::pair<Identity,std::vector<Identity>>>;

std::vector<Identity> CreateIdentities(size_t quantity) {
  std::vector<Identity> identities;
  while (quantity-- > 0)
    identities.emplace_back(Identity(RandomBytes(identity_size)));
  return identities;
}

void SortIdentities(std::vector<Identities>& network, const Identity& target) {
  std::sort(network.begin(), network.end(),
            [&](const Identity& lhs, const Identity& rhs) {
              return CloserToTarget(lhs, rhs, target);
            });
}

// returns first N identities from sorted network
template <size_t N>
std::vector<Identity> GetIdentities(const std::vector<Identity>& network) {
  std::vector<Identity> selected_identites;
  size_t size(network.size() < N ? network.size() : N);
  for (size_t i = 0; i != size; ++i)
    selected_identites.push_back(network[i]);
  return selected_identites;
}

/*
std::vector<std::pair<size_t, Identity>>
    GetCountedCommonPmidNames(std::vector<std::vector<Identity>>& pmids) {
  assert(pmids.size() >= GroupSize);
  for (size_t i = 0; i != pmids.size(); ++i)
    if (pmids[i].size() < GroupSize)
      BOOST_THROW_EXCEPTION(MakeError(CommonErrors::invalid_argument));

  std::multiset<Identity> all_pmids;
  std::set<Identity> unique_pmids;
  std::vector<std::pair<size_t, Identity>> count_pmid_pairs;

  for (size_t i = 0; i != pmids.size(); ++i) {
    for (size_t j = 0; j != pmids[i].size(); ++j) {
      all_pmids.insert(pmids[i][j]);
      unique_pmids.insert(pmids[i][j]);
    }
  }

  for (const auto& pmid : unique_pmids)
    count_pmid_pairs.push_back(std::make_pair(all_pmids.count(pmid), pmid));

  std::sort(count_pmid_pairs.begin(), count_pmid_pairs.end(),
            [](const std::pair<size_t, Identity>& lhs, const std::pair<size_t, Identity>& rhs) {
              return lhs.first < rhs.first;
            });

  return count_pmid_pairs;
}
*/

std::vector<std::pair<size_t, Identity>>
    FrequencyCount(GroupsOfGroup pmids) {
  assert(pmids.size() >= GroupSize);
  for (size_t i = 0; i != pmids.size(); ++i)
    if (pmids[i].size() < GroupSize)
      BOOST_THROW_EXCEPTION(MakeError(CommonErrors::invalid_argument));

  std::multiset<Identity> all_pmids;
  std::set<Identity> unique_pmids;
  std::vector<std::pair<size_t, Identity>> count_pmid_pairs;



  for (size_t i = 0; i != pmids.size(); ++i) {
    for (size_t j = 0; j != pmids[i].size(); ++j) {
      all_pmids.insert(pmids[i][j]);
      unique_pmids.insert(pmids[i][j]);
    }
  }

  for (const auto& pmid : unique_pmids)
    count_pmid_pairs.push_back(std::make_pair(all_pmids.count(pmid), pmid));

  std::sort(count_pmid_pairs.begin(), count_pmid_pairs.end(),
            [](const std::pair<size_t, Identity>& lhs, const std::pair<size_t, Identity>& rhs) {
              return lhs.first < rhs.first;
            });

  return count_pmid_pairs;
}

TEST(GroupQuorumLogicTest, FUNC_Merge) {
  auto network(CreatePmids(500));
  auto group_address(Address(Identity(RandomBytes(identity_size))));
  SortPmids(pmids, group_address);
  std::vector<Identity> address_sorted_pmids(GetPmidNames<GroupSize>(pmids));
  std::vector<std::pair<Identity,std::vector<Identity>>> closest_pmids;

  for (size_t i = 0; i != address_sorted_pmids.size(); ++i) {
    SortPmids(pmids, Address(address_sorted_pmids[i]));
    closest_pmids.push_back(std::make_pair(address_sorted_pmids[i],
                                           GetPmidNames<GroupSize>(pmids)));
  }

  auto count_pmid_pairs(GetCountedCommonPmidNames(closest_pmids));

  for (auto i = count_pmid_pairs.size() - 1; i != count_pmid_pairs.size() - GroupSize - 1; --i)
    EXPECT_GE(count_pmid_pairs[i].first, QuorumSize);
}

}  // namespace test

}  // namespace routing

}  // namespace maidsafe
