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
    use of the MaidSafe Software.                                                                */

#include "maidsafe/common/asio_service.h"
#include "boost/filesystem/path.hpp"

#include "maidsafe/routing/utils.h"
#include "maidsafe/routing/routing_node.h"

#include "maidsafe/passport/detail/fob.h"



int main(int argc, char* argv[]) {
    using maidsafe::routing::RoutingNode;
    int exit_code(0);

    const boost::filesystem::path kPathToBootstrap(
                maidsafe::ThisExecutableDir() / "routing_bootstrap.dat");

    const passport::PmidAndSigner pmid_and_signer(passport::CreatePmidAndSigner());
    const passport::Pmid pmid_key(pmid_and_signer.first);
    
    try {
        auto unuseds(maidsafe::log::Logging::Instance().Initialise(argc, argv));
        if (unuseds.size() != 2U)
          BOOST_THROW_EXCEPTION(maidsafe::MakeError(maidsafe::CommonErrors::invalid_parameter));

        // TODO: thread_count is to be determined
        maidsafe::IoService<boost::asio::io_service> io_service(30);
        RoutingNode routing_node(&io_service.service(), kPathToBootstrap,
                                 pmid_key, std::shared_ptr<RoutingNode::Listener>());
    }
    catch (const maidsafe::maidsafe_error& error) {


    }
    catch (const std::exception& e) {
        
    }
    return exit_code;
}
