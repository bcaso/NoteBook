# 涉及设计模式
装饰模式
建造者模式

# 疑问
先上一段怪异代码：
```c#
public class Test {
	/// <summary>
	/// 返回this
	/// </summary>
	/// <returns></returns>
	public Test ta () {
		return this;
	}

	/// <summary>
	/// 返回this
	/// </summary>
	/// <returns></returns>
	public Test tb() {
		return this;
	}

	/// <summary>
	/// 返回一个新实例
	/// </summary>
	/// <returns></returns>
	public Test tc() {
		return new Test();
	}

	/// <summary>
	/// 使用静态方法返回一个新实例
	/// </summary>
	/// <returns></returns>
	public static Test td() {
		return new Test();
	}
}

public class program {
	void main() {
		Test ta = new Test().ta().ta().ta();

		//为什么可以ta().tb()...?
		Test tb = new Test().ta().tb().tb();

		//返回一个新实例.ta().tb()...
		Test tc = new Test().tc().ta().tb();

		//使用静态创建对象然后再对象.ta().tb().tc()
		Test td = Test.td().ta().tb().tc();
	}
}
```

# 使用
```c#
			ContainerBuilder.GetBuilder()
				.Child(
				       TextBuilder.GetBuilder()
					       .Data("Hello World")
					       .FontSize(30)
					       .Build()
				      )
				.AlignmentCenter()
				.Build();
```
这是其中一种命名规范，http://www.sikiedu.com/course/410/task/30112/show#

链式编程实现：
①如上代码需要新建Container组件，那么就新建一个类`ContinerBuilder`
②创建所有需要的字段`mChild`, `mAlignment`
③所有的属性赋值都放在方法中，方法的返回值都是`this`
④创建一个`Build`方法，返回`Container`组件的一个新实例，并且传入这个类中的已经赋值好的变量。
`return new Container(child: mChild, alignment: mAlignment);`

```c#
using Unity.UIWidgets.painting;
using Unity.UIWidgets.widgets;

namespace WQFramework.UIWidgets {
	public class ContainerBuilder {
		private Widget    mChild     { get; set; }
		public  Alignment mAlignment { get; set; }

		public static ContainerBuilder GetBuilder() => new ContainerBuilder();

		public ContainerBuilder Child(Widget child) {
			mChild = child;
			return this;
		}

		public ContainerBuilder AlignmentCenter() {
			mAlignment = Alignment.center;
			return this;
		}

		public ContainerBuilder AlignmentTopRight() {
			mAlignment = Alignment.topRight;
			return this;
		}

		public Container Build() {
			return new Container(child: mChild, alignment: mAlignment);
		}
	}
}
```

## 案例
```c#
using System;
public class C {           
        private static  void Main()        {
            Person person = new Person { Name = "Tom" }
                .Run()
                .Sing()
                .Swim();
        }

        class Person{
            public string Name { get; set; }

            public Person Run()
            {
                Console.WriteLine("Run");
                return this;
            }
            
            public Person Sing()
            {
                Console.WriteLine("Sing");
                return this;
            }
            
            public Person Swim()
            {
                Console.WriteLine("Swim");
                return this;
            }
        }
}
```
![](https://i.loli.net/2019/09/24/KHXfnCGbrvk2Nah.png)

执行顺序：
①实例化Person类对象person
②为Name字段赋值
③调用 person.Run方法，假设返回值为 C+Person
④接着使用 C+Person 调用 person.Run方法，依然返回 C+Person
⑤接着使用 C+Person 调用 person.Sing方法，依然返回 C+Person
⑥接着使用 C+Person 调用 person.Swim方法，然后再返回 C+Person
依然不是特别清楚在内存上是怎么表示的。

## 内存中的对象是怎么样的
# 相关教程
https://www.cnblogs.com/ldp615/archive/2009/08/07/1541189.html