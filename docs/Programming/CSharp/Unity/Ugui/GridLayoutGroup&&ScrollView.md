教程地址：
http://www.sikiedu.com/course/260/task/12143/show

# GridLayoutGroup
## 问题
### 播放后UI跳动
将`Content`的RectTransform的`PosY` && `Height` 全部改为`0`。仅修改 GridLayoutGroup的 `Top`达到效果。
仅修改Height没用，仅修改PosY,停止运行后，其值变得很诡异，所以可以改变Height和Top，改变Height是为了在Scene面板中看到边框，改变Top是为了效果。

经过多次测试，UI跳动的问题是由`PosY`引起的。这个值最好设置为0，通过修改其他的值就能实现效果。

#### 切换程序后，再切换到Unity，Content内容消失
这个问题也是由`PosY`引起的，改动这个值，Content即出现，然后再改回0即可。
或者一个更通用的解决办法：禁用该物体，然后再启用。就是让Unity重新渲染下，然后就解决了。

### Content设计
>教程链接：http://www.sikiedu.com/course/260/task/12175/show#

![](https://i.loli.net/2019/10/13/PV7l16O3RbGmnAh.png)