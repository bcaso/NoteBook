# 准星的实现

## 方式一：
素材：图片一张：

![尺寸256 * 256，DirtyWhite.png](https://i.loli.net/2019/04/24/5cc023d2e150f.jpg)
脚本：
`fps_Crosshair.cs`
```csharp?linenums
/****************************************************
    文件：fps_Crosshair.cs
	作者：WQ
    邮箱: bcaso@qq.com
    日期：2019/04/24 14:50
	功能：屏幕准星的控制
*****************************************************/

using UnityEngine;
using UnityEngine.UI;

public class fps_Crosshair : MonoBehaviour {
	public float     length;           //准星的长度
	public float     width;            //准星的宽度
	public float     distance;         //左右两条准星与上下两条的距离
	public Texture2D crosshairTexture; //准星的背景图

	private GUIStyle _lineStyle;
	private Texture  _tex;


	private void Start() {
		_lineStyle                   = new GUIStyle();
		_lineStyle.normal.background = crosshairTexture;
	}

	/// <summary>
	/// 准星的绘制
	/// </summary>
	private void OnGUI() {
		//left
		GUI.Box(new Rect((Screen.width - distance) / 2 - length,
		                 (Screen.height - width) / 2 ,
		                 length,
		                 width),
		        _tex, _lineStyle);
		//right
		GUI.Box(new Rect(
		                 (Screen.width + distance) / 2,
		                 (Screen.height - width) / 2 ,
		                 length,
		                 width),
		        _tex, _lineStyle);
		//top
		GUI.Box(new Rect(
		                 (Screen.width - width) / 2,
		                 (Screen.height - distance) / 2 - length ,
		                 width,
		                 length),
		        _tex, _lineStyle);
		//bottom
		GUI.Box(new Rect(
		                 (Screen.width - width) / 2,
		                 (Screen.height + distance) / 2 ,
		                 width,
		                 length),
		        _tex, _lineStyle);
	}
}
```
参数的设置：
![](https://i.loli.net/2019/04/24/5cc0252d04d84.jpg)

效果图：
![](https://i.loli.net/2019/04/24/5cc025871953d.jpg)

修改 Distance 参数来改变准星距离，或者说发散程度：
下图是将 Distance 修改为20后的效果。
![](https://i.niupic.com/images/2019/04/24/6gno.jpg)

### 原理：
![原理图](https://i.loli.net/2019/04/24/5cc02f216543e.jpg)
以左边的矩形为例，其 x 点在左下角，y 点在左竖线中间。
计算公式：
`x = (Screen.width - distance) / 2 - length`
解释：屏幕一半的宽度 - distance的一半 - length = x
`y = (Screen.height - width) / 2`
解释：屏幕一半的高度 - width的一半 = y

从屏幕中间的点来计算每个点所在的位置会更加方便理解。

### Rect
所使用到的Rect构造函数，`public Rect(float x, float y, float width, float height)`
由X和Y位置，宽度和高度定义的2D矩形。

Unity使用了许多2D坐标空间，其中大部分将X定义为向右增加，Y向上增加。一个例外是在GUI和GUILayout类中，其中Y向下增加。

GUI空间中说明了以下示例，其中（0,0）表示左上角，Y表示向下增加。

可以用两种不同的方式指定矩形。第一个是x和y位置以及宽度和高度：
![](https://i.loli.net/2019/04/24/5cc0323865f26.jpg)
另一种方法是使用每个边的X和Y坐标。这些被称为xMin，xMax，yMin和yMax：
![](https://i.loli.net/2019/04/24/5cc032d9d2803.jpg)

### GUI.Box
`public static void Box(Rect position, Texture image, GUIStyle style);`
上例中，image为新的Texture对象，可以修改为new Texture(), 最后一个参数，样式，在Start方法中设置：_lineStyle.normal.background = crosshairTexture; 把样式背景设置为了文章开头的`DirtyWhite`.
这调用方式真怪，应该设置图片的image是new的，且没赋值，style是设置样式的，却设置了背景。
也就是说准星是通过样式背景实现的。

### 使用
在玩家运动时，改变其Distance, 就能实现准星的涣散效果。

## 方式二：
在网上找准星素材，使用UGUI，一个画布，一个图片，放在中间，强制画布的sorting layer = Int16.Max
在玩家运动时，改变图片的缩放。

# 玩家准星、枪
这个有点扯远了。
思路：
在Update中检测鼠标左键输入，设置定时器，每秒钟能发射多少颗子弹。
往屏幕中间发射一条射线，记录碰撞到的点。进而实现攻击。
然后实例化子弹，从枪口到枪的前面（Vector3.forward）。
子弹的Z轴朝向碰撞到的点运动。`bullet.transform.LookAt(targetPoint);`//子弹的Z轴朝向目标
Destroy(bullet, 10);
计时器清零。

>教程地址：https://blog.csdn.net/baidu_39447417/article/details/74897704
