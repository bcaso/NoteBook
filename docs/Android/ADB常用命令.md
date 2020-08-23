# 备份手机照片
```console
adb pull storage/4478-9737/DCIM C:\Users\god\Pictures

explorer C:\Users\god\Pictures
```
`4478-9737`可能根据不同的手机有不同的名称

# 查看wifi密码
```console
adb shell
su
cat /data/misc/wifi/*.conf
```
# 拷贝wifi密码文件到电脑
```console
adb devices 
adb shell 
su 
cp /data/misc/wifi/wpa_supplicant.conf /mnt/sdcard/ 
 
adb pull sdcard/wpa_supplicant.conf 
```
