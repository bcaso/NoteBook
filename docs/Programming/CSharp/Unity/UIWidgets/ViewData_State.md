```c#
/****************************************************
            文件：StateExample.cs
        	作者：WQ
            邮箱: bcaso@qq.com
            日期：2019/09/23 10:33
        	功能：点击事件修改组件数据，更新方式：单向数据流的方式
*****************************************************/

using Unity.UIWidgets.engine;
using Unity.UIWidgets.painting;
using Unity.UIWidgets.widgets;

namespace LearnUIWidgets {
	public class StateExample : UIWidgetsPanel {
		protected override Widget createWidget()
			=> new Counter();

		/// <summary>
		/// 做容器，组件
		///  这个类里面不做渲染工作
		/// </summary>
		class Counter : StatefulWidget {
			public override State createState()
				=> new CounterState();
		}

		/// <summary>
		/// 管理数据
		/// </summary>
		class CounterState : State<Counter> {
			private int mCount { get; set; } //C# 6.0 feature
//			private int mCount { get; set; } = 0; //C# 6.0 feature

			/// <summary>
			/// 状态初始化函数
			/// </summary>
			public override void initState() {
				mCount = 0;
			}

			/// <summary>
			/// build写真正要渲染的组件
			/// </summary>
			/// <param name="context"></param>
			/// <returns></returns>
			public override Widget build(BuildContext context) =>
				new GestureDetector(
				                    child: new Text($"Click Count: {mCount}", style: new TextStyle(fontSize: 30)),
				                    onTap: () => this.setState(() => mCount++)
				                   );
		}
	}
}
```
# 数据更新问题
如果上面的数据更新事件是这么写的：
`onTap: () => mCount++`
那么在UI上的数据是看不到变化的。
必须使用this.setState，对数据的更改才能显示到UI上。
`onTap: () => this.setState(() => mCount++)`

其内部是调用了markNeedsBuild()方法，改为以下这种方式也能实现：
```c#
onTap: () => {
	mCount ++;
	(context as StatefulElement).markNeedsBuild();//标记当前组件需要重新build一次，因为数据有更改
}
```
不建议这种写法，除非特别理解底层实现代码。

# 具体实现步骤
继承自UIWidgetspanel的都是无状态的，要修改数据，不要在这个类中添加事件啥的。
①这个类只返回一个组件，
②因为要有状态，所以再弄一个内部类`a`继承自`StatefulWidget`，和另一个内部类`b`继承自`State<a>`
&nbsp;&nbsp;&nbsp;&nbsp;Ⅰ. a中的`createState():State` 返回一个`b`实例
&nbsp;&nbsp;&nbsp;&nbsp;Ⅱ. b中的`build():Widget` 返回一个组件，这个方法中写具体的实现代码和事件。
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;「1」事件代码也必须在setState中，不然数据的更新不会反映在UI上
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`this.setState(() => {//Do something here}})`

例：http://www.sikiedu.com/course/410/task/30115/show#
