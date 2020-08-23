```c#
/****************************************************
            文件：SetupApp.cs
        	作者：WQ
            邮箱: bcaso@qq.com
            日期：2019/09/23 9:25
        	功能：UIWidgets的图片控件，只需要建立的类继承Unity.UIWidgets.engine.UIWidgetsPanel即可，然后这个控件挂在一个UI物体上，这个物体就是一个UI Image
        	     UIWidgetsPanel继承了UGUI的RawImage,所以就是一个图片，可以挂在物体上
*****************************************************/

using Unity.UIWidgets.engine;
using Unity.UIWidgets.painting;
using Unity.UIWidgets.widgets;

namespace LearnUIWidgets {
	public class SetupApp : UIWidgetsPanel {
		protected override Widget createWidget() =>
			new Unity.UIWidgets.widgets.Text("Hello", style: new TextStyle(
			                                                               color: Unity.UIWidgets.ui.Color.white, //这个是颜色，是UIWidgets的Color
			                                                               fontSize: 30
			                                                              ));
	}
}
```
效果：
![](https://i.loli.net/2019/09/23/jC6pbcs5UligQ7P.png)