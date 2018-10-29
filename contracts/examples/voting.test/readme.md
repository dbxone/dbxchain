dxx -o voting.wast voting.cpp
dxx -g voting.abi voting.cpp
deploy_contract voting nathan 0 0 /root/dbxchain/contracts/examples/voting.test DBX true
call_contract nathan voting null list "{}" DBX true
call_contract nathan voting null vote "{\"id\":1, \"name\":\"user1\"}" DBX truek
call_contract nathan voting null count "{\"id\":1, \"name\":\"user1\"}" DBX true
