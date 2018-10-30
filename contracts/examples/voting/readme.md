# 合约介绍
投票合约，记录查看删除候选人的id，姓名，票数等。

# 编译合约
```
dxx -o voting.wast voting.cpp
dxx -g voting.abi voting.cpp
```

# 部署合约

部署合约要求账户私钥已经导入钱包，并且是解锁状态
```
unlocked >>> deploy_contract voting nathan 0 0 ./voting DBX true
```
其中
```
// voting指定将要创建的合约名
// nathan为部署合约的帐户
// 0 0 分别指定了vm类型和版本号
// ./voting指定合约文件的路径
// DBX表示使用DBX支付手续费
// true表示执行，发起广播
```

# 调用合约

## 投票
```
call_contract nathan voting null vote "{\"id\":1, \"name\":\"user1\"}" DBX true
call_contract nathan voting null vote "{\"id\":1, \"name\":\"user1\"}" DBX true

call_contract nathan voting null vote "{\"id\":2, \"name\":\"user2\"}" DBX true
call_contract nathan voting null vote "{\"id\":3, \"name\":\"user3\"}" DBX true
```

## 查看票数
```
call_contract nathan voting null count "{\"id\":1}" DBX true
```

此时在witness_node运行日志看到如下内容.
```
[(22,count)->22] CONSOLE OUTPUT BEGIN =====================
id=1, name=user1, count=2
[(22,count)->22] CONSOLE OUTPUT END =====================
```

## 查看投票列表
```
call_contract nathan voting null list "{}" DBX true
```

此时在witness_node运行日志看到如下内容.
```
[(22,count)->22] CONSOLE OUTPUT BEGIN =====================
id=1, name=user1, count=2
id=2, name=user2, count=1
id=3, name=user3, count=1
[(22,count)->22] CONSOLE OUTPUT END =====================
```

## 删除候选人
```
call_contract nathan voting null remove "{\"id\":1}" DBX true
```
此时在witness_node运行日志看到如下内容.
```
[(22,count)->22] CONSOLE OUTPUT BEGIN =====================
remove name==user1
[(22,count)->22] CONSOLE OUTPUT END =====================
```

