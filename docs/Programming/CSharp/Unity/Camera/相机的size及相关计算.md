# 相机的Size属性及相关计算
![](https://i.loli.net/2019/05/01/5cc921e3a1710.jpg)
屏幕比例：9:16
要使相机完全包裹图中的绿草地，要怎么设置size属性？
先给出结论：**相机的size = 屏高的一半**


![platform 1024 * 219 ](https://i.loli.net/2019/05/01/5cc92227c9fe3.jpg)

![每个单位100像素](https://i.loli.net/2019/05/01/5cc922c55d847.jpg)

## 思路
图片像素尺寸为 1024 * 219，unity默认是1个单位100像素，图片的单位比例就是：10.24 * 2.19
屏幕比例是: 9(宽):16(高)

相机的size = 屏高的一半
设相机的size为x，则 2x/10.24 = 16/9
求得x = 9.10
![size](https://i.loli.net/2019/05/01/5cc924fdc88f5.jpg)

<br>
<br>
<br>

再比如: 把一张1920*1080像素的图片设置为场景背景，如何设置size？屏幕分辨率还是16：9
![enter description here](https://i.loli.net/2019/05/01/5cc9265a84926.jpg)

1920:1080 = 16:9
设相机size = x
则 2x / 10.80 = 16 / 9
求得 x = 9.6