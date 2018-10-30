# 编译合约
执行如下命令, 生成wast和wasm文件:
```
dxx -o helloworld.wast helloworld.cpp
```

生成abi:
```
dxx -g helloworld.abi helloworld.cpp
```

# 部署合约

部署合约要求账户私钥已经导入钱包，并且是解锁状态
```
unlocked >>> deploy_contract helloworld nathan 0 0 ./helloworld DBX true

```
其中
```
// helloworld指定将要创建的合约名
// nathan为部署合约的帐户
// 0 0 分别指定了vm类型和版本号
// ./helloworld指定合约文件的路径
// DBX表示使用DBX支付手续费
// true表示执行，发起广播
```

# 调用合约
调用helloworld合约的hi方法：
```
unlocked >>> call_contract nathan helloworld null hi "{\"user\":\"user1\"}" DBX true
```
其中
```
// nathan指定调用合约的帐户
// helloworld指定要调用的合约帐户名
// null 表示不向合约发送资产
// hi 表示要调用的合约方法
//  "{\"user\":\"user1\"}" 表示合约hi文件的参数，参数以json格式传入
// DBX表示使用DBX支付手续费
// true表示执行，发起广播
```

此时在witness_node运行日志看到如下内容表示成功
```
[(22,count)->22] CONSOLE OUTPUT BEGIN =====================
hi, user1
[(22,count)->22] CONSOLE OUTPUT END =====================
```

```
// 22合约账户id，部署时，合约id有不同
```