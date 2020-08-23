教程地址：
http://www.sikiedu.com/course/260/task/12147/show#

官方的代码封装的一团糟。
其中要得到UI的宽高的代码需要记住的有：
```
	Debug.Log(this.GetComponent<RectTransform>().sizeDelta);
	Debug.Log(this.GetComponent<RectTransform>().sizeDelta.x);
	Debug.Log(this.GetComponent<RectTransform>().sizeDelta.y);
	//动态的修改值
	this.GetComponent<RectTransform>().sizeDelta = new Vector2(0, 1);
```

网上找到的一个扩展类：
https://answers.unity.com/questions/888257/access-left-right-top-and-bottom-of-recttransform.html
```c#
using UnityEngine;
 public static class RectTransformExtensions
 {
     public static void SetLeft(this RectTransform rt, float left)
     {
         rt.offsetMin = new Vector2(left, rt.offsetMin.y);
     }
 
     public static void SetRight(this RectTransform rt, float right)
     {
         rt.offsetMax = new Vector2(-right, rt.offsetMax.y);
     }
 
     public static void SetTop(this RectTransform rt, float top)
     {
         rt.offsetMax = new Vector2(rt.offsetMax.x, -top);
     }
 
     public static void SetBottom(this RectTransform rt, float bottom)
     {
         rt.offsetMin = new Vector2(rt.offsetMin.x, bottom);
     }
	 /// <summary>
	/// offsetMin是RectTransform左下角相对于左下Anchor的距离。
	/// offsetMax是RectTransform右上角相对于右上Anchor的距离；
	/// 不明白的是为什么右上都是负的
	/// </summary>
	public static void SetRect(this RectTransform trs, float left, float top, float right, float bottom) {
		trs.offsetMin = new Vector2(left, bottom);
		trs.offsetMax = new Vector2(-right, -top);
	}
 }
```
Now you can call these methods like this :
```c#
 myRectTransform.SetLeft(100);
```
# 基本使用说明
https://blog.csdn.net/chang_1134/article/details/78087271
例子挺不错

# 网上搜集到的一些可能遇到的问题
## ScrollView的Content不能根据实际Content下的游戏物体的多少自动改变Content的宽高问题
https://blog.csdn.net/qq_34818497/article/details/80771787

trigger的通过修改sizeDelta来解决问题：
http://www.sikiedu.com/course/260/task/12150/show
