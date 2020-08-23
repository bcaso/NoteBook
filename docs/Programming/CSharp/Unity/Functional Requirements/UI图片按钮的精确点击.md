[TOC]

<p align = center><font size = 5>精确点击</font></p>
![](https://i.loli.net/2019/09/14/7wy5gfcXFQUqTCb.png)
要求图片上（作为一个按钮），②的部分的内容，不会被鼠标点击所触发点击事件。

# 实现方案
## 一、Unity自带解决方案
### 实现
①点开图片的属性面板，开启`Read/Write Enabled`选项
②在该图片上的一个脚本的Start方法（或Awake或其他）中加入下面一行代码即可
`GetComponent<Image>().alphaHitTestMinimumThreshold = 0.1f;`

### 原理
   图片中被遮罩隐藏的部分的像素的alpha都是0，所以看起来都是透明的。要使这部分内容不被触发，就在点击时判断点击部位的图片像素是否小于某个值。
   因此可以通过修改Image组件的 alphaHitTestMinimumThreshold 的值来达到目的，至于为什么是0.1f，这个是习惯吧。
   这个变量的值默认是0.
### 缺点
这个解决方案需要开启`Read/Write Enabled`
①使图片占用的内存增大一倍
②图片不能被并入图集

### 总结
一般，这个方案是不被采用的。

## 二、Polygon Collider 2D 组件
### 实现
①在Image上挂载`Polygon Collider 2D`组件，并设置好多边形碰撞器形状，即点击的区域
②在Image上建立新脚本，如CustomImage,继承Image,并重写`IsRaycastLocationValid`方法,具体代码如下：
```csharp
using UnityEngine;
using UnityEngine.UI;

public class CustomImage : Image {
	private PolygonCollider2D _polygon;

	private PolygonCollider2D Polygon {
		get {
			if (_polygon == null) {
				_polygon = GetComponent<PolygonCollider2D>();
			}

			return _polygon;
		}
	}


	public override bool IsRaycastLocationValid(Vector2 screenPoint, Camera eventCamera) {
		Vector3 point; //rect区域的世界坐标
		RectTransformUtility.ScreenPointToWorldPointInRectangle(rectTransform, screenPoint, eventCamera, out point);
		return Polygon.OverlapPoint(point); //判断坐标是否在2D图片上
	}
}
```
### 原理
`Polygon Collider 2D`组件控制了图片的碰撞器，也就是按钮能触发的区域，这个方案也能用于很多其他方面，比如，一幅风景画中的某颗树是能被点击的
### 缺点
这个解决方案需要一定的代码量，操作起来不熟练。
没看明白，以上代码跟那个组件的关系。。。
这还涉及了UGUI底层代码。

### 总结
