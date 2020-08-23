# 问题描述
工厂模式，将UI面板预制体直接实例话化到`Hierarchy`面板上，因为不是直接实例`Canvas`下，所以，要手动设置下UI面板的RectTransform
## 由此引发的问题：
①UI不显示，位置不对
②将UI面板手动放置在Canvas下后，缩放比例不对，因为，UI面板是以自身的缩放为基础，要以Canvas为父对象，自身的比例就会放大。
④修改以上设置后，UIPanel的位置依然不对，因为锚点只有在Canvas下才存在。当UIPanel在`Hierarchy`根目录下时，锚点不存在，并会产生混乱，在移动到Canvas下后，也就发生错乱。
# 解决
①设置父物体`setparent`
②设置`localPosition`为vector3.zero，将left, top, posZ都置为0
③设置`localScale`为vector3.one
④设置`锚点`为居中