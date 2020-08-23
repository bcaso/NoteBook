```c#
/****************************************************
            文件：OnClickExample.cs
        	作者：WQ
            邮箱: bcaso@qq.com
            日期：2019/09/23 9:34
        	功能：手势识别器，点击事件
        	         通过重写父类UIWidgetsPanel下的createWidget方法
        	         返回一个手势识别器，这个识别器也是一个Widget类型的
        	             注册手势识别器中的onTap事件即可实现点击
*****************************************************/

using Unity.UIWidgets.engine;
using Unity.UIWidgets.painting;
using Unity.UIWidgets.widgets;
using UnityEngine;
using Color = Unity.UIWidgets.ui.Color;

namespace LearnUIWidgets {
	public class OnClickExample : UIWidgetsPanel {
		protected override Widget createWidget() =>
			//返回一个手势识别器类，整个本身就是一个图片，也是就是当前类是一个手势识别器，因为当前类重写了这个方法，也不知道这样理解对不对
			//这个手势识别器中有一个child，Widget类型，应该也能是特别多的控件，不只是Text
			//点击事件是针对当前图片的，当前类，当前控件这个图片
			new GestureDetector(
			                    child: new Text(data: "HelloWorld",
			                                    style: new TextStyle(
			                                                         color: Color.white,
			                                                         fontSize: 30
			                                                        )),
			                    onTap: () => { Debug.Log("onTop"); }
			                   );
	}
}
```

# 点击触发要求
①要有GestureDetector
②GestureDetector要有child 和 onTap事件。
③对child的类型不限，但要求是Widgets类型，没有child,单有这个类，不能触发`onTap`事件
这个类本身是一个RawImage，在UIWidgets中大概相当于Unity中Panel的地位，图片有多大，点击触发的区域就有多大，但是没有child，无法触发。

# 触发问题
以上示例中，无论是点击到哪个位置，不论是否点击到了文字上，都会触发onTap事件。
而在某些案例中，只要在点击了文字，才会触发点击事件。不知道这其中有什么要求。