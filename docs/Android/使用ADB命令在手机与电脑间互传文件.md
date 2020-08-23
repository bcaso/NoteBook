# adb不是内部或外部命令，也不是可运行的程序或批量文件。
配置环境变量:把JAVA sdk的`platform-tools`添加到系统变量中，或者把Android SDK中的 `platform-tools` 添加到系统环境变量中。
然后新开命令行窗口进行测试

# 用命令行把手机上的文件拷贝到电脑上
```console
adb pull sdcard/test.png
```
将把test.png放在当前文件夹下。
例：
```console
C:\Users\god>adb pull sdcard/download/123.jpg
sdcard/download/123.jpg: 1 file pulled. 3.5 MB/s (54460 bytes in 0.015s)
```
命令：`adb pull sdcard/download/123.jpg`是在`C:\Users\god`目录下执行的，所以，`123.jpg`自然也会被拷贝到这个目录下
![](https://i.loli.net/2019/04/06/5ca8b381ce242.jpg)

执行`pull`这个命令时必须在电脑目录下。

# 拷贝带有访问权限的文件到电脑
这个不能直接使用pull命令，`/data/`,`/system/`等目录下的文件都是需要权限的

解决步骤：
* 得到权限
    * 分别执行`adb shell` 和 `su`两条命令,当
* 拷贝文件到`/mnt/sdcard/`下
    * `cp 123.jpg /mnt/sdcard/`
* 再使用pull命令拷贝到电脑
    * `pull `

使用了`/mnt/sdcard/` 做为中转站

```
//进入安卓控制台
E:\test>adb shell

//使用su命令获取root权限
shell@hwC199:/ $ su

//获取root权限后，$ 符号会变成 #
//进入到目标文件夹
root@hwC199:/ # cd /data/data/com.android.contacts/databases/

//查找目标文件并拷贝到 /mnt/sdcard/ 下
root@hwC199:/data/data/com.android.contacts/databases # ls
contacts_app.db
contacts_app.db-journal

root@hwC199:/data/data/com.android.contacts/databases # cp contacts_app.db /mnt/sdcard/
_app.db /mnt/sdcard/



//新开一个命令行窗口并使用pull命令获取文件到当前目录下
//E:\test>adb pull sdcard/contacts_app.db
```


>这里的sdcard并不一定是真正的sdcard卡，没插sdcard卡的情况下也有这个目录
/storage/sdcard
/sdcard
/mnt/sdcard
<br>
以上三者的区别？
<br>
/sdcard是/mnt/sdcard的符号链，指向/mnt/sdcard，
<br>
/storage/sdcard 是sdcard的分区……


# 拷贝文件到手机sdcard/
```console
adb push Temp/contacts_app.db /sdcard/
```
把文件contacts_app.db拷贝到手机sdcard上

# 拷贝手机wifi密码到电脑

![拷贝手机WIFI密码到电脑](https://i.loli.net/2019/04/06/5ca8bd1e908fc.jpg)
 1. 查看手机设备
 2. 进入手机控制台
 3. 获取root权限
 4. 拷贝目标文件到 `/mnt/sdcard/`
 5. 新开一个命令提示窗
 6. pull目标文件到当前目录下
 
```console
adb devices
adb shell
su
cp /data/misc/wifi/wpa_supplicant.conf /mnt/sdcard/

adb pull sdcard/wpa_supplicant.conf
```
