/*******************************************************************************
 *  Copyright 2012 maidsafe.net limited                                        *
 *                                                                             *
 *  The following source code is property of maidsafe.net limited and is not   *
 *  meant for external use.  The use of this code is governed by the licence   *
 *  file licence.txt found in the root of this directory and also on           *
 *  www.maidsafe.net.                                                          *
 *                                                                             *
 *  You are not free to copy, amend or otherwise use this source code without  *
 *  the explicit written permission of the board of directors of maidsafe.net. *
 ******************************************************************************/

#include "maidsafe/routing/tests/mock_service.h"

namespace maidsafe {

namespace routing {

namespace test {

MockService::MockService(RoutingTable& routing_table,
                         NonRoutingTable& non_routing_table,
                         NetworkUtils& utils)
    : Service(routing_table, non_routing_table, utils) {}

MockService::~MockService() {}

}  // namespace test

}  // namespace routing

}  // namespace maidsafe

