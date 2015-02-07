PUT, all functions are templated on DataType

< MaidNode::Put<DataType> | MaidManager::HandlePut<DataType> | DataManager::InstantiateData<DataType>  | PmidManagers::Store<DataType> | PmidNode::Persist<DataType> >

< MaidNode::Put(D) {
     client_routing.put(D) }
 | MaidManager::HandlePut(D) {
     Allow ? ChargeCost(K*M*D.size())
             return Flow [ DataManager{D.name}, InstantiateData(D) ]
           : return Error [ MaidNode, error::OutOfCredit ] }
 | DataManager{D.name}::InstantiateData(D) {
     ReplicationPmidNodes = SelectKClosestNodesTo(D.name)
     Register(D.name, D, ReplicationPmidNodes)  // Store D in register until persisted in PmidNodes;
                                                // Same register serves later re-use for cache.
     return Flow [ PmidManager{ReplicationPmidNodes}, Store(D) ] }
 | PmidManager{ReplicationPmidNode}::Store(D) {
     return Flow [ PmidNode, Persist(D) ]
 | PmidNode::Persist(D) {
      PersistInVault(D)
      on_error return Error [ PmidManager{PmidNode}, error::FailedToStoreInVault(D) ]
      return Flow [ ] } >





legend:
 <      scatter
 >      gather
 |       sentinel
 D     data
 H()   Hash512
 H^n() n-th Hash512
 ManagersGroup{Address};  {Address} omitted where evident, e.g. MaidManagers{MaidNode}

