# MIUI9 Adb 命令 修改MAC地址

```
//进入控制台并获取Root权限
adb shell
su

//查看网络配置信息
ifconfig

//记下无限网卡的名字，eth0,ra0,wlan0...
//我的Redmi 5 的是wlan0


//禁用网卡
ifconfig 无限网卡名 down

//修改MAC地址
ifconfig 无限网卡名 hw ether 新MAC地址

//重新启用网卡
ifconfig 无限网卡名 up

//输入ifconfig对比之前的查看修改结果
```

# 方式二
似乎可用
```
ip link set wlan0 down &&ip link set wlan0 address CC:2D:83:DB:A5:1H
```
> 全部教程地址如下：
http://www.miui.com/thread-11544042-1-1.html

# 查看当前mac地址
除了可以用ifconfig外，最直接的是：
```
cat /sys/class/net/wlan0/address 
```
