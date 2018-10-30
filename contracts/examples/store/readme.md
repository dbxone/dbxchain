dxx -o store.wast store.cpp
dxx -g store.abi store.cpp
deploy_contract store nathan 0 0 /root/dbxchain/contracts/examples/store DBX true
call_contract nathan store null set "{}" DBX true
call_contract nathan store null show "{}" DBX true
