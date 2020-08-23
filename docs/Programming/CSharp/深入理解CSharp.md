---
title: 深入理解CSharp
tags: oop,Csharp
grammar_mindmap: true
renderNumberedHeading: true
grammar_code: true
grammar_mathjax: true
grammar_linkify: true
---
# 前言
1.看代码时，要想搞清调用关系，可以复制代码到 https://sharplab.io 

# 例图：
```plantuml!
Son --|> Parent
class Parent{
    +field : type
    
    +Parent() : ctor
    +Parent() : ~
    +SayHi() : virtual void
}

class Son{
    +field : type
    
    +Son() : ctor
    +Son() : ~
    +SayHi() : override void
    +Hello() : void
}
```

# 深入理解继承
从内存角度讲：从堆空间中申请一块内存，存储Parent(那并不是一个实例化的对象),再开辟另一块内存储存Son,两者都是独立的。Son应该看作是一个指针，指向这两块内存空间，因此能够操作父类。

构造函数：
Son继承自Parent;
当实例化Son时，会先调用父类的构造函数，然后再调用子类的构造函数。

析构函数：
销毁的时候调用。
先调用子类Son，再调用父类。也就是先销毁子类，再销毁父类。

父类 == 基类 == 超类
## 实例化出的对象的字段
一个子类在实例化之前，需要先实例化从父类继承到的部分
![实例化出两个对象其name字段,不是同一个,而是每个对象都独有一个 =600*300](https://i.loli.net/2019/05/21/5ce36c1a0c01662585.jpg)

# 深入理解多态
## 简单说明
父类的指针指向子类，调用子类的方法。
父类的指针`tempParent`指向子类，调用子类的方法`SayHi()`(看后面的虚方法)
```csharp?linenums
Parent tempParent = new Son();
tempParent.SayHi();
```

```csharp?linenums
Parent tempParent = new Son();
>>~~tempParent.Hello();~~<<//Error 找不到Hello
```
由父类声明实例出的子类，在转换前不能调用子类特有的方法和属性。因为此时实例化出的对象虽然是子类，但是指针指向了父类。找不到外面的方法和属性。如图：
![父类声明实例化子类的内存图 =400*250](https://i.loli.net/2019/04/28/5cc4e346d733b.jpg)


要调用Hello(),需要在父类中写个虚方法，子类重写该方法，或者直接用子类声明并实例化子类。子类调用自己的方法。如果是父类声明，实例化子类，还可以通过转型来调用子类特有的方法和属性包括字段。

以上是对多态的简单描述，理解多态的关键是虚方法和里氏转换。请接着看
## 虚方法
>虚方法：调用方法时，声明类与实例类的区别，结合 https://sharplab.io 可轻松搞清函数的调用关系。
https://www.cnblogs.com/jiajiayuan/archive/2011/09/14/2176015.html#undefined
关于在C#中构造函数中调用虚函数的问题：
https://www.cnblogs.com/xpvincent/p/4459452.html
重载overload, override
https://www.cnblogs.com/jiajiayuan/archive/2011/09/15/2177051.html

override virtual abstract 方法都可以被重写。
## 类型转换
### 向上转型(隐式类型转换) 与 向下转型(显式转换)
>向上转型与向下转型
https://blog.csdn.net/wangqingbo0829/article/details/48474173
多态与向上转型
https://www.cnblogs.com/georgewing/archive/2009/05/26/1489484.html


向上转型后的对象将不再能够使用子类中特有的字段，属性和方法。

>向上转型：将子类对象转为父类对象。此处父类对象可以是接口。
向上转型得到的对象的类型，打印出来看还是子类。但语法上算父类。
向下转型：把父类对象转为子类对象。
>将子类对象赋给父类的引用就是向上转型，Animal a2 = new Dog();中的new Dog()就是实例化一个没有名字的对象，然后转型给父类的引用a2，仅此而已。


>如果向下转型失败，则得到null。继续调用对象的数据时，肯定会出现空引用异常。

>时间：2019/05/21 
>感觉有点意思，多态是向上转型，然后要调用子类特有的数据时，只需要再向下转型
><br>
>

```csharp?linenums
using System;
using static System.Console;

namespace 类型转换 {
  class Program {
    static void Main(string[] args) {
      Person person = new Man(name: "张三", age: 22); //隐式类型转换，向上转型,总会成功
      Man    man    = (Man) person;                 //显式类型转换，向下转型,除非转换的类型是当初构造它的类型，否则可能失败
      man.Eat();                                    //调用子类特有的方法

      //仿造官方案例：对象的生成都成功了，但是在Test方法内部，如果使用强制转换，则会抛异常，如果使用as转换，则都转换为了null
      //https://docs.microsoft.com/zh-cn/dotnet/csharp/programming-guide/types/casting-and-type-conversions 
      Test(new Person(name: "Tom", age: 20));
      Test(new Person()); 
      /*
       * Person p = new Person();
       * Man man = p as Man;
       */
      Test(new Man(name: "Jerry", age: 2));
    }

    static void Test(Person p) {
      //			Man man = (Man) p;//使用这个，Test(new Person())，Test(new Person("a", 1));会报错
      Man man = p as Man; //使用这个, Test(new Person())，Test(new Person("a", 1));会转换失败，变为null，在使用它之前都不会抛异常
    }
  }

  public class Person {
    public Person() { }

    public Person(string name, int age) {
      this.Name = name;
      this.Age  = age;
    }

    public string Name { get; set; }
    public int    Age  { get; set ; }
  }

  public class Man : Person {
    public Man(string name, int age) : base(name, age) { }

    public void Say() => WriteLine($"I am {Name}, {Age} years old." );
    public void Eat() => WriteLine("I can eat");
  }

  public class Woman : Person {
    public Woman(string baseName, int age) : base(baseName, age) { }

    public void Say() => WriteLine($"I am {Name}, {Age} years old." );
  }
}
```
### 逆变与协变
## 抽象类抽象方法
>https://www.cnblogs.com/jiajiayuan/archive/2011/09/13/2174376.html
抽象类特点
<ol>
    <li>抽象成员必须标记为abstract,并且不能有任何实现</li>
    <li>抽象成员必须在抽象类中</li>
    <li>抽象类不能被实例化</li>
    <li>子类继承抽象类后必须把父类中的所有抽象成员都重写，除非子类也是一个抽象类，则可以不重写</li>
    <li>抽象成员的访问修饰符不能是private</li>
    <li>在抽象类中可以包含实例成员,并且抽象类的实例成员可以不被子类实现</li>
    <li>抽象类是有构造函数的。虽然不能被实例化</li>
    <li>如果父类的抽象方法中有参数，那么。继承这个抽象父类的子类在重写父类的方法的时候必须传入对应的参数</li>
</ol>

使用须知：如果父类中的方法有默认的实现，并且父类需要被实例化，这时可以考虑将父类定义成一个普通类，用虚方法来实现多态。
## 构造方法
非静态的构造方法，可以用public, private 来修饰

非静态的构造方法，如果提供了其他构造方法，则其默认的无参构造方法则被隐藏（如果没有显式声明的话）

构造方法中的`:`表示当前构造方法之前先执行`:`后的一个构造方法，后面可接this,指向当前类中的其他构造方法，base执行父类中的构造方法，通过参数列表，也就是实参来区分。

把当前构造参数列表中的参数传递给后面的构造函数中的参数，先执行完后面的构造，再执行当前的构造。

如果`:`后面是无参的构造，那么就先执行完后面的无参构造再执行当前的构造，此时没有参数传递，此时肯定是有参构造调用无参构造，无参构造调用自己就死循环了。

如果是一个无参的构造调用一个有参的构造，那么就需要为后面的有参构造赋值传入实际的值，如：
```csharp
using System;

class Person {
  public string Name;
  private Person() { }

  public Person(string name) => this.Name = name;
}

class Student : Person {
  public Student() : base("张三") => Console.WriteLine($"我是一个学生，我叫{Name}");
}

class Program {
  public static void Main(string[] args) {
    Student s = new Student();
  }
}
```
### 静态构造方法
静态构造函数不允许出现访问权限修饰符,public, private 都是错的。

静态构造方法必须无参数

静态的构造方法不会隐藏默认的无参构造方法。
```csharp?linenums
using System;

namespace CtorTest {
	class Program {
		public static void Main(string[] args) {
			//先调用静态的构造方法，再调用非静态的构造方法
//			Person p = new Person();

			//并没有在内存中开辟空间，所以也就没有实例化，所以不会调用其构造方法
			Person p = null;

			//会调用其静态构造函数，然后再调用其静态的Hello方法
			Person.Hello();
			Person.Hello();//静态构造方法只会被调用一次，之后这个就被载入内存了。
		}
	}

	class Person {
		//第一次被加载入内存时被调用,如果第一次调用这个类且是调用这个类中的静态方法，这个构造也会被执行
		static Person() {
			Console.WriteLine("静态的构造方法被执行了");
		}

		public Person() {
			Console.WriteLine("非静态的构造方法被执行了");
		}

		public static void Hello() {
			Console.WriteLine("Hello world!");
		}
	}
}
```
## 关键字
### new
步骤：
<ol>
    <li>在堆中开辟空间</li>
    <li>在开辟的空间中创建对象</li>
    <li><b>调用对象的构造函数</b></li>
</ol>

___
### this
<ol>
    <li>代表当前类的<font size = 5 color = red>对象</font></li>
    <li>显式的调用当前类的构造函数</li>
</ol>

___
### base
区别于this的第一条
<ol>
    <li>显式调用父类的构造函数</li>
    <li>调用父类的成员</li>
</ol>

___
### const
const变量必须有初值
const为编译时常量，程序编译时将对常量值进行解析，并将所有常量引用替换为相应值。

由于const常量在编译时将被替换为字面量，使得其取值类型受到了一定限制。const常量只能被赋予数字(整数、浮点数)、字符串以及枚举类型。

常量字段 public const int a = 10; 
静态字段 public static int a = 10; 

静态字段、常量字段都只能用类名访问，不能用对象访问。常量字段默认也是静态的，是属于类的，只不过不用static修饰符修饰。

>关于 readonly 与 const的区别，更详细的解释
https://www.cnblogs.com/Kenny-Jiang/archive/2008/05/26/1207969.html#undefined
### readonly
readonly变量有初值或只能在构造方法中进行赋值，运行时常量
>关于 readonly 与 const的区别，更详细的解释
https://www.cnblogs.com/Kenny-Jiang/archive/2008/05/26/1207969.html#undefined
### sealed
修饰类或方法
修饰的类叫密封类，不能被继承
修饰的方法叫做密封方法，不能被继续重写（首先，这个方法重写了父类的方法，这个方法不能被子类再重写，只针对override, 不能在virtual后面，如果希望一个方法不被重写，就不应该写virtual）,能被子类重写的方法有 override, virtual, abstract),也就是只有override 方法才能被密封
## 接口
接口的功能要单一
接口不能被实例化，同抽象类一样。实例化接口没有意义。
但是可实例化一个由接口声明的且继承自借口的类。（类似抽象类，可实例化一个继承抽象类的子类）
类中的成员的默认的访问修饰符是private,而接口中默认的访问修饰符是public

（默认为public ）接口中的成员不能有任何实现（“光说不做”，只是定义了一组未实现的成员）

接口中只能有方法、属性、索引器、事件，表有“字段和构造函数”。(字段实际上是数据，属性也只是对数据做了访问限制，数据由类来储存，接口实现的是一种能力，接口中不能有构造函数，因为没有意义)

接口与接口之间可以继承

接口不能继承一个类，而类可以继承接口（接口只能继承于接口，而类即可以继承接口，也继承继承类）

实现接口的子类必须实现该接口中的全部成员。

一个类可以同时继承一个类并实现多个接口，如果一个子类同时继承了父类A,并实现了接口IA，那么语法上A必须些在IA的前面。

`class MyClass:A, IA{}`, 因为类是单继承的。
```csharp?linenums
interface IFly{
    void Fly();
}

interface IStrong{
    void Strong();
}

interface InwKuWdIr{
    void NwKuWdIr();
}

//接口不需要实现接口成员，（抽象类也不需要实现抽象父类的成员）
interface ISupperMan: IFly, IStrong, InwKuWdIr{//超人有飞、强壮、内裤外穿的能力
}
```

显示实现接口的目的：解决方法的重名问题（继承接口的类中的函数与接口中的必须要实现的函数重名）

当一个抽象类实现接口的时候，需要子类去实现接口。

尽量不要让父类去实现接口，因为子类必须实现，还不如直接写在父类中。

接口中的方法不是抽象方法。所以不能被重写，不能加 override,
可以加virtual,或者abstract(继承了接口的抽象类)
```csharp?linenums
interface USB{
    void Charge();
    void TransportData();
}

class Mouse : USB{
//    public override void Charge(){}//Error 没有找到合适的方法重写
    public void Charge(){
    }
}
```
## 委托
### 委托与多态
<b>委托不属于类</b>，放在类外，就属于命名空间。
可以把函数（方法）看作委托的子类。
使用委托需要创建对象，参数是与委托签名相同的方法
然后调用对象，并传入参数（如果有的话）。

方法参数中的委托，可以看作是方法的占位符
```csharp?linenums
	public delegate void DelSayHi(string name);

	class Program {
		static void Main(string[] args) {
			//函数可以直接赋值给一个委托对象 委托的签名必须跟函数的签名一样
			DelSayHi del = SayHiChinese; //new DelSayHi(SayHiChinese);//new或不new，最终都是new了，没有new只是简写了
			del("张三");
			Console.ReadKey();
		}

		static void SayHiChinese(string name) {
			Console.WriteLine("吃了么" + name);
		}

		static void SayHiEnglish(string name) {
			Console.WriteLine("Ohayo" + name);
		}
	}
```
### Lambda => "goes to" 
### 泛型委托
### Winform中的EventHandler
Winform中的事件注册用的全部都是Eventhandler委托
```
this.button1.Click += new System.EventHandler(this.button1_Click);//传递一个方法
```
而这个委托的声明如下：
```csharp?linenums
// Decompiled with JetBrains decompiler
// Type: System.EventHandler
// Assembly: mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089
// MVID: 659CD5F0-C4CE-410C-B23A-6CADD71BB76F
// Assembly location: C:\Windows\Microsoft.NET\Framework64\v4.0.30319\mscorlib.dll

using System.Runtime.InteropServices;

namespace System
{
  /// <summary>Represents the method that will handle an event that has no event data.</summary>
  /// <param name="sender">The source of the event. </param>
  /// <param name="e">An object that contains no event data. </param>
  [ComVisible(true)]
  [__DynamicallyInvokable]
  [Serializable]
  public delegate void EventHandler(object sender, EventArgs e);
}
```
sender表示事件源，sender表示触发事件的对象。
因为委托绑定的方法要与委托的签名一致。所以按钮点击的事件的方法签名都如下显示：
```csharp?linenums
private void button1_Click(object sender, EventArgs e){}
```
如果是按钮点击事件，那么这个事件绑定的方法中传入的sender参数就是Button类型的对象,测试代码如下：
```csharp?linenums
private void button1_Click(object sender, EventArgs e){
    Button btn = (Button)sender;
    MessageBox.Show("按钮被点击了");//如果转换成功则会执行到这行代码，否则抛异常。如果上面把sender转换Label类型的对象，则会抛出异常。
}
```

并非所有的方法签名都如此。如按钮的鼠标按下事件的方法：
```csharp?linenums
private void button1_MouseDown(object sender, MouseEventArgs e){}
```
当然，MouseEventArgs 继承自 EventArgs, 相对于EventArgs，MouseEventArgs多了一些属性，如下图：
![MouseEventArgs](https://i.loli.net/2019/05/19/5ce0a503cae2c42878.jpg)
Clicks是按下并释放按键的次数，Button是鼠标的哪个按钮被按下。
### 事件
#### 事件与委托
事件的本质就是封装了的一个多播委托。类似属性封装了字段。所以使用事件必须得有委托。

>正规的解释：事件的本质是类型安全的委托。委托本质上是一个类型。
事件只能在类的内部调用（事件是类的数据成员，定义在类内部），类似委托。类型安全是因为，事件在外部无法调用，外部可以注册或移除事件，但不能调用事件。而委托变量在外部除了注册外还能调用这个委托变量。

>* 委托的作用：
> 给函数占位，在不知道将来要执行的方法的具体代码时，可以先用一个委托变量来代替方法调用（委托的返回值，参数列表要确定）。在实际调用前，需要为委托赋值，否则为`null`
>* 事件的使用：
>事件的作用与委托变量一样，只是功能上被委托变量有更多的限制。（比如：1.只能通过+=或-=来绑定方法（事件处理程序）2.只能在类内部调用（触发）事件。）

事件作为类的数据成员，不是一种类型; 只能定义在类内。不能写在命名空间下。
#### 事件必须是<b>委托类型</b>？
声明的形式上与委托的区别：
```csharp?linenums
namespace test{
    public delegate void DelTest();
    class Program{
        public event DelTest delEvent;//声明事件不需要写()
        public DelTest delDel;//声明委托变量，与声明事件相比少了个event
        
        public static void Main(string[] args){}
    }
}
```
![事件的IL代码 =600*400](https://i.loli.net/2019/05/19/5ce0add4e37ff97663.jpg)
如上图，是事件`DelPlayOver`的IL代码。
首先DelPlayOver是一个事件，类型是EventHandler
其中有两个方法`add`与`remove`类似属性的getter和setter访问器，因为封装的是委托，所以事件也是委托类型，event是关键字。

>与委托的区别：
1.多了个event关键字
2.事件的注册只能使用+=或者-=，而委托还可以使用=
#### 声明和使用
```csharp?linenums
namespace MyNamespace {
	//声明一个代理
	public delegate void MyDelegate(object o);

	//声明一个类，在类的内部声明事件
	public class MyClass {
		//利用上面的代理声明一个事件
		public event MyDelegate MyEvent;

		//定义一个方法调用事件
		public void FireAway(object o) {
			if (MyEvent != null) {
				//调用处理事件的方法
				MyEvent(o);
			}
		}
	}

	public class MainClass {
		//创建一个处理事件的方法
		private static void EventFunction(object o) {
			Console.WriteLine("发生某种事件：", o);
		}

		//主方法
		public static void Main() {
			//声明一个对象
			MyClass m = new MyClass();
			//将处理事件的方法和事件关联,其形式类似使用多重代理
			m.MyEvent += new MyDelegate(EventFunction);
			//触发事件
			m.FireAway(m);
		}
	}
}
```
## 泛型
### 特点
在一个命名空间中，可以存在两个类名相同的类，但是这两个类泛型需要（数量）不一样
泛型只可以用在当前类中，继承后就不再是泛型了。
反省参数写在类名后或者方法名后，用`<>`括起来。

# 区别与联系
## 结构体和类
关于C#中结构体的一些理解和总结和一些事例：
https://www.cnblogs.com/cuitsl/archive/2011/08/22/2149896.html
### 相同点
都包含字段，属性，方法
修饰的访问权限
都是通过new来实例化对象
结构体中除了不能手动写出默认的public的构造外，可以包含静态构造，有参数的构造，其使用和类一样。调用时机和类一样。
### 不同点
#### 内存上存储位置
结构体对象是在栈上开辟的空间。类是在堆上开辟的空间。

所以，结构体是值类型，不是引用类型，而类是引用类型。
所以，unity中的射线检测的有个hit.point就必须是out修饰的。

结构体中始终包含一个public权限的无参构造方法。

```csharp?linenums
using System;

namespace StructTest {
	/// <summary>
	/// 结构体的有参构造方法中必须给所有的字符赋值，或者就不用构造方法
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	public struct Point {
		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}

		//非static, const字段,不能直接赋初值，可以放在构造方法中,或者在实例化后赋值
		public        double x , y;
		public static int    z = 3;
		public const  int    a = 3;
		//属性
		public double X {
			get { return x; }
		}

		//方法
		public void Hello() {
			Console.WriteLine("Hello world!");
		}
	}

	class Program {
		static void Main(string[] args) {
			Point p = new Point(1, 1);
			Console.WriteLine($"未改变前：Point.x = {p.x}, Point.y = {p.y}"); //未改变前：Point.x = 1, Point.y = 1

			Change(p);
			Console.WriteLine($"Change(p)后：Point.x = {p.x}, Point.y = {p.y}"); //Change(p)后：Point.x = 1, Point.y = 1

			Change(out p);
			Console.WriteLine($"Change(out p)后：Point.x = {p.x}, Point.y = {p.y}"); //Change(out p)后：Point.x = 3, Point.y = 4

            //结构体中始终包含一个public无参的构造方法，且不能被手动写出来，下一行代码正确。且没问题
			Point p1 = new Point();			
		}

		static void Change(Point p) {
			p.x = 3f;
			p.y = 4f;
		}

		static void Change (out Point p) {
			p.x = 3f;
			p.y = 4f;
		}
	}
}
```
#### 不能有析构方法
析构方法
结构体中不允许写析构方法。
>1.栈上代码的执行效率快
2.栈上的空间不需要程序员管理，堆上的空间需要手动管理。
在堆上开辟一个空间，实例化一个对象，当这个对象不再使用时，需要手动的销毁这个对象，有个线程会自动去做，不用去管。当这个对象被销毁时会调用析构方法。
在栈上开辟的空间，不需要程序员管理，所以就没有析构这一回事。
#### 没有继承与被继承
结构体只有一个父类就做Object
结构体不能被类或者结构体继承，也不能继承其他结构或类。
### 常见结构体
#### int(Int32)
int 是 Int32的别名，而Int32是结构体类型
##### bool(Boolean)
bool是Boolean的别名，而Boolean是结构体类型
#### C#的基本数据类型
C#的基本数据类型都是值类型，也都是结构体。

## 静态和非静态
* 静态成员：被static修饰
* 实例成员：不被static修饰
* 静态成员先于实例成员被加载到内存中
* 只有创建了对象，才有实例成员
* 静态类中只能存在静态成员
* 静态构造方法不能有访问权限（默认是私有的，但不能写出来）和参数
* 静态类只能有一个父类，叫做Object，与结构体一样，没有继承关系。

## 静态构造函数 与 静态变量
(MSDN）
https://docs.microsoft.com/zh-cn/dotnet/csharp/programming-guide/classes-and-structs/static-constructors
>静态构造函数在什么时候会被调用？
>* 第一次实例化类的对象时，会优先普通的构造函数被调用
>* 第一次调用类的一个静态方法时

静态变量只会被赋值一次，就是在第一次使用它时

### Console类就是一个静态类

```csharp?linenums
static class Student {
		//private string _name; //error: 不能在静态类声明实例成员（静态类没有办法创建对象，所以就不需要有实例字段）
		//静态成员先于实例成员被加载到内存中，只有创建了对象才有实例成员
}
```
### 实例类中可以有静态成员，静态方法中不能调用实例成员
```csharp?linenums
class Person{
    private string _name;
    public static void Test(){
        _name = "字符串";//Error: 有Person类就有静态成员，静态成员先于类成员进入内存，就有这个方法，但是有这个方法不一定有实例成员（只有类成员的情况下才有_name）,所以静方法中不能访问实例成员
    }
}
```
### 普通方法中可以调用静态成员
```csharp?linenums
public static string _gender;
public void Test2(){
    _gender = "男";//调用这个方法时就一定有了实例成员，有实例成员就一点先有了静态成员
}
```
静态成员先于实例成员进入内存，所以静态方法中可以调用实例成员
### Console静态工具类，以及什么时候使用静态类？
* 工具类，使用的时候不用创建对象（方便）
* 在整个项目中资源共享,正因为是资源共享，所以静态成员必须等到整个项目都结束的时候，才会被资源释放，项目中应该尽量少用。伴随静态是随程序生成，伴随程序中止的。如果你要释放，是不是不该定义成静态呢
* 例：qq客户端，登录后，qq窗体上的qq邮箱，qq微薄，qq空间等按钮。调用的就是静态类中的方法，当用户点开对应的网页时，不需要重新输入账号密码。原理就是：登录成功后，账号密码被储存到一个静态类中，当点击qq空间时，会去静态类中判断账号密码是否正确。
如图：
![enter description here](https://i.loli.net/2019/05/12/5cd784e82e976.jpg)

## 单例模式与静态
在一个项目中的不同模块中获取对象，获取到的是同一个对象
### 创建单例模式的步骤
<ol>
    <li>构造函数私有化，防止new对象</li>
    <li>创建一个静态字段，表示当前类的对象,比如Instance</li>
    <li>从类的内部创建一个对象为Instance赋值，并使用静态方法返回这个对象，静态方法需要使用静态字段，所以instance也要用static修饰</li>
</ol>

___
### 单例例子及最简单例
```csharp?linenums
class Program {
	public static void Main(string[] args) {
		//p == p1
		Person p  = Person.GetInstance();
		Person p1 = Person.GetInstance();
	}
}

class Person {
	private Person() { }
	//只会实例化一次，在初始化赋值，因为是静态的，所以只会赋值一次。也就是赋初值
	//因为是只在初始化时赋值，也可以写为readonly,但是不能写为const，因为const需要在编译前就有值，对于Person类,这是不可能的。
	//由于const常量在编译时将被替换为字面量，使得其取值类型受到了一定限制。const常量只能被赋予数字(整数、浮点数)、字符串以及枚举类型。
	//private static Person Instance = new Person();
	private static readonly Person Instance = new Person();


	public static Person GetInstance() {
		return Instance;
	}
}
```
由于static修饰的变量只会被赋初值一次，那么最简单例如下：
为了严谨，另加了readonly修饰符
```csharp?linenums
class Program {
	public static void Main(string[] args) {
		Person.Instance.Hello();
	}
}

class Person {
	private Person() { }

	public static readonly Person Instance = new Person();

	public void Hello() {
		Console.WriteLine("Hello world!");
	}
}
```
无论如何创建单例，都有私有构造函数，这就防止了外部new.

如上的最简单例，可以没有readonly修饰，因为有私有构造函数，但是如果没有私有构造函数，外部也就可以改变这个值，通过这个new。所以，有readonly更严谨。
### WinForm单例
例：
点击 button1,创建一个Form2窗口并显示，做为单例，无论点击多少次，就只返回一个且还是那一个Form2的对象
```csharp?linenums
//other code
private void button1_Click(object sender, EventArgs e) {
	Form2 frm2 = Form2.GetSingle(); //new Form2();
	frm2.Show();
}
//other code
```
```csharp?linenums
public partial class Form2 : Form {
	//第一步：构造函数私有化
	private Form2() {
		InitializeComponent();
	}

	//第二部：声明一个静态的字段用来存储全局唯一的窗体对象
	private static Form2 _single = null;

	//第三步：通过一个静态函数返回一个全局唯一的对象
	public static Form2 GetSingle() {
		if (_single == null) {
			_single = new Form2();
		}

		return _single;
	}

	private void Form2_FormClosing(object sender, FormClosingEventArgs e) {
		//当你关闭窗体的时候 让窗体2的资源不被释放
		_single = new Form2();
	}
}
```
### Unity单例：
```csharp?linenums
public class Ring : MonoBehaviour {
    //创建一个私有的构造函数，防止外界new对象
    private Ring(){}
    
    //创建一个静态字段
	public static Ring  Instance = null;
	
	//创建一个静态方法，为静态字段赋值,并返回
	public static Ring GetInstance(){
        //什么时候需要，什么时候进行实例化，调用这个方法的使用需要。
	    if(Instance = null){
	        Instance = this;
	    }
	    
	    return Instance;
	}
	
	private       Image _image;
	public float FillAmount {
		get { return _image.fillAmount; }
		set { _image.fillAmount = value; }
	}

	public bool FillDone {
		get {
			if (_image.fillAmount >= 0.97f) {
				_image.fillAmount = 0;
				return true;
			}
			return false;
		}
	}

	void Awake() {
		_image            = GetComponent<Image>();
		_image.fillAmount = 0;
	}
}
```
另一种更巧妙的，使用静态属性代替 静态字段和静态方法
```csharp?linenums
using UnityEngine;
using UnityEngine.UI;


public class Ring : MonoBehaviour {
    //创建一个私有的构造函数，防止外界new对象
    private Ring(){}

    //创建一个静态字段，静态属性返回这个字段，在Awake()中为这个字段赋值
	public static Ring  Instance{get;private set;};
	
	
	private       Image _image;
	public float FillAmount {
		get { return _image.fillAmount; }
		set { _image.fillAmount = value; }
	}

	public bool FillDone {
		get {
			if (_image.fillAmount >= 0.97f) {
				_image.fillAmount = 0;
				return true;
			}
			return false;
		}
	}

	void Awake() {
		Instance          = this;
		_image            = GetComponent<Image>();
		_image.fillAmount = 0;
	}
}
```
### 问：能不能用普通方法返回单例对象？
不能，普通方法是实例成员，要访问实例成员必须得到类的对象。类的对象无法保证在外部创建且使用语法保证只创建一个。

## 值类型与引用类型
### ref 与 out参数
两个都是引用传递。
使用ref型参数时，传入的参数必须先被初始化。把<b>值传递</b>变为<b>引用传递</b>
对out而言，必须在方法中对其完成初始化。

使用ref和out时，在方法的参数和执行方法时，都要加ref或out关键字。以满足匹配。

out适合用在需要return 多个关键字的地方。
ref用在需要被调用的方法修改调用者的引用的时候。
### 实参与形参
```csharp?linenums
class MyClass {
	static void Main(string[] args) {
		string name = "张三";
		string pwd  = "password";
		string msg;
		bool   result;
		result = Login(name, pwd, out msg);//调用方法时传入的是实参
	}

	static bool Login(string loginName, string pwd, out string msg) {//方法的定义中的是形参列表
		if (loginName.Equals("张三") && pwd.Equals("password")) {
			msg = "登录成功";
			return true;
		}
		else if (loginName.Equals("张三")) {
			msg = "密码错误";
			return false;
		}
		else {
			msg = "账号或密码不正确！";
			return false;
		}
	}
}
```
### 特殊情况
数组类型是引用类型，即使元素类型是值类型（所以即便int是值类型，int[]也是引用类型）

枚举（使用enum来声明）是值类型

委托类型（使用delegate来声明）是引用类型

接口类型（使用interface来声明）是引用类型，但可由值类型实现
### 堆栈
“引用类型保存在堆上，值类型保存在栈上”

这个说法是错误的，第一部分是正确的——引用类型的实例总是在堆上创建的。但第二部分就有问题了。前面讲过，变量的值是在它声明的位置储存的。所以，假定一个类中有一个int类型的实例变量，那么在这个类的任何对象中，该变量的值总是和对象中的其他数据在一起，也就是在堆上。
只有局部变量（方法内部声明的变量）和方法参数在栈上。(意思是如果局部变量或方法内部声明的变量如果是值类型，那么它就在栈上，如果是引用类型，则会在栈上创建一个指针变量，指向堆上所创建的变量，)
对于C#2及更高版本，很多局部变量并不完全存放在栈中，第五章中的匿名方法会讲到这一点。
-- C# in Depth Third Edition chapter:2.3  Page42
### params参数
params必须是形参列表中的最后一个元素

在调用含有params修饰的函数时
1. 传递一个与params修饰的相同类型的数组
2. 传递1个或n个与与params修饰的相同类型的数组元素

```csharp?linenums
class Program {
	static void Main(string[] args) {
		Test(0, new [] {1, 2, 3,});
		Test(0, 1, 2, 3);
	}

	static void Test(int i, params int [] arr) { }
}
```

实参与形参相同也好，不相同也罢，两者根本不是一个人。
### 引用传递
参数中如果是对象，那么就是又在栈上开辟了一个指针变量，这个指针指向实参。
例：
```csharp?linenums
class Person(){}
class Program(){
    static void Main(){
        Person person = new Person();
        Test(person);
    }
    
    static void Test(Person p){
        Person p1 = new Person();
        p = p1;
        //Do something to p
    }
}
```

如Test方法中的p，就是在栈开辟的一个指针变量，保存实参person的地址
如果将p 再赋值其他变量，如上的p = p1.就是把p又指向了p1.这里的p和person是两个不同的指针变量，不过是同指向了一块内存空间，改变p的指向后，person的指向不变。

![对象，变量，引用传递，内存堆栈图](https://i.loli.net/2019/05/12/5cd7e8e84e7e1.gif)

动态图地址：https://i.loli.net/2019/05/12/5cd7e8e84e7e1.gif
#### Unity中的对象引用
同上，并没有创建新实例，而是创建了一个指针变量指向了那个对象。不论是在Inspector上拖拽赋值还是Find赋值，都是再给指针变量赋值，而且指针变量也是有类型的。

# 访问修饰符
可用来修饰类、字段、属性和方法，用来描述被修饰的内容可访问的范围。
## public static readonly 顺序无所谓
当这三个修饰符或者其中两个同时修饰一个变量时，顺序是无所谓的。
```csharp?linenums
class Program {
	public static void Main(string[] args) {
		Person.Instance.Hello();
	}
}

class Person {
	private Person() { }

//	public static readonly Person Instance = new Person();
//   public readonly static Person Instance = new Person();
    static readonly public Person Instance = new Person();

	public void Hello() {
		Console.WriteLine("Hello world!");
	}
}
```
## 其余的就靠ide的智能提示或纠错

# 字符串
## 简单说明
* 重要特性
    不可变性，对字符串的任何操作，都会在内存中产生一块新的实例
    驻留池
    可以把字符串看作是char类型的只读数组
* GC:Garbage Collection 

垃圾回收，每隔一段时间，会扫描整个内存，发现，如果有的空间没有被指向，则立刻把它销毁。
## 把字符串当作只读数组：
```csharp?linenums
string str = "abcdefg";
Console.WriteLine(str[5]);//f
```
## == 与 Equal 的区别
Equals默认比较的是栈上的地址，== 比较的是值
地址在栈上，值在堆上
一般在使用Equal时，都会重写这个方法。
当比较的两个对象都是字符串时，比较这两个字符串在堆空间的值。
## StringBuilder
Append()
Insert()
Replace()
Remove()
Clear()
ToString();//这sb必须转为string类型才能用
不展开说了，就那么些方法。

具体的用例：Winform的webBrower.DocumentText = sb.ToString();
```csharp?linenums
		private void button1_Click(object sender, EventArgs e) {
			StringBuilder sb = new StringBuilder();
			sb.Append("<html>");
			sb.Append("<head>");
			sb.Append("</head>");
			sb.Append("<body>");
			sb.Append("<table bgcolor='yellow' border='1px' cellpadding='0px' cellspacing='0px'>");
			sb.Append("<tr>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("</tr>");
			sb.Append("<tr>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("</tr>");
			sb.Append("<tr>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("<td>我是动态被加载出来的哟~~~~</td>");
			sb.Append("</tr>");
			sb.Append("</tr>");

			sb.Append("</table>");
			sb.Append("</body>");
			sb.Append("</html>");

			webBrowser1.DocumentText = sb.ToString();
		}
```
![](https://i.loli.net/2019/05/13/5cd9452643a8370884.jpg)

## 字符串转义
将一个字符串，包含转转义字符的字符串，通过转义变为合法的字符串
## 字符串操作

### string.ToCharArray() 修改字符串
```csharp?linenums
string str = "abcdefg";
char[] chs = str.ToCharArray();
chs[2] = 'z';
foreach(char item in chs){
    Console.WriteLine(item);
}
str = new string(chs);//abzdefg
```
### String.Intern(String) Method 驻留池
>https://docs.microsoft.com/en-us/dotnet/api/system.string.intern?redirectedfrom=MSDN&view=netframework-4.8#System_String_Intern_System_String_
http://www.wjgbaby.com/2017/09/30/c%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E5%92%8C%E9%A9%BB%E7%95%99%E6%B1%A0/
### null 与 空 的区别
null没有在内存中开辟空间
空 在内存中开辟了空间，存储的就是 空
### String.IsNullOrEmpty(String) Method 字符串的判null或空
### String.ToLower Method String.ToUpper Method
由于字符串的不可变性，所以这两个静态方法是有返回值的。返回值是转换的结果。
### String.IndexOf Method 返回字符在字符串中的索引值
可以配合while循环找出字符串中存在某个字符的次数
例：
```csharp?linenums
//有如下字符串：【"患者：“大夫，我咳嗽得很重。”     大夫：“你多大年记？”     患者：“七十五岁。”     大夫：“二十岁咳嗽吗”患者：“不咳嗽。”     大夫：“四十岁时咳嗽吗？”     患者：“也不咳嗽。”     大夫：“那现在不咳嗽，还要等到什么时咳嗽？”"】。需求：请统计出该字符中“咳嗽”二字的出现次数，以及每次“咳嗽”出现的索引位置。
int index = str.IndexOf("咳嗽");
Console.WriteLine("第1次出现咳嗽的位置是{0}", index);
//我们每一次都应该从上一次找到的位置加1开始往后找
int count = 1;
while (true) {//或者把这里的条件改为index != -1
	index = str.IndexOf("咳嗽", index + 1);
	if (index == -1) {
		break;
	}
	count++;
	Console.WriteLine("第{0}次出现咳嗽的位置是{1}", count, index);
}
Console.ReadKey();
```
### String.Substring 字符串截取
案例：打字机
```csharp?linenums
	IEnumerator StartType() {
		while (_curPos < _string.Length - 1) {
			yield return  new WaitForSeconds(0.2f);

			Debug.Log("_curPos = " + _curPos + "string Length:" + _string.Length);
			text.text = str.Substring(0, _curPos++);
		}

		_curPos   = 0;
		text.text = _string;

		if (TypeDone != null) {
			TypeDone();
		}

		yield break;
	}
```
### String.Split Method 字符串分隔
```csharp?linenums
string str = "张  ,,--三  ,李,,--四  a  ";
string[] strNew = str.Split(new char[]{',', ' ', '-'});//返回的数组长度不变，其中逗号空格横线都被替换为了""，空
```
### Trim() TrimEnd() TrimStart() 删除空白符或者删除指定字符
```csharp?linenums
string s = "   张   ,,,--    三 ,,,--   ";
Console.Write(s.Trim(' ',',','-'));//张   ,,,--    三
```
如上，Trim只删除了前后的，给定的符号（默认为空格）
单纯使用Trim()函数，将会把字符串的前后空白符删除，然后返回删除后的字符串
>官方解释：	
从当前 String 对象移除所有前导空白字符和尾部空白字符。

官方手册：
https://docs.microsoft.com/zh-cn/dotnet/api/system.string.trim?view=netframework-4.0
### String.Join Method
```
public static string Join (string separator, params object[] values);
public static string Join (string separator, params string[] value);
```
```csharp?linenums
string res = string.Join("|", 'c', "张三", 100, 3.14, true, 5000m);
Console.WriteLine(res);//c|张三|100|3.14|True|5000
```
### String.Contains() String.Replace()  包含与替换
```csharp?linenums
Console.WriteLine("请输入你要回复的内容");
string contents = Console.ReadLine();
//判断contents中是否包含敏感词
if (contents.Contains("老赵")) {
	contents = contents.Replace("老赵", "****");
}
Console.WriteLine(contents);
```

# 集合
增删改查
## 非泛型集合
### ArrayList
ArrayList.Add(Object obj);
可添加任意类型的参数到集合中，功能强大，但涉及到装箱和拆箱。

ArrayList.Add()添加单个元素到集合中。
ArrayList.AddRange()添加多个元素到集合中

区别：
ArrayList.Add(new int[]{1, 2, 3});//添加一个集合元素到集合中，这个数组包含3个元素
ArrayList.AddRange(new int[]{1, 2, 3});//添加三个元素到集合中，这个集合新加了3个元素

集合都实现了ICollection接口（ArrayList确实实现了，其他的不清楚），所以，在Add，或者AddRange方法的参数中可以添加集合。或者单个元素。
这是接口的向上转型。
### Hashtable
## 泛型集合
`List<T>` 与 `Dictionary<TKey, TValue>`的命名空间都是`System.Collections.Generic;`
### `List<T>`
#### 属性
Capcity 可以包含的元素个数,当不够存储时，该值会自动扩充当前的2倍
Count 元素个数
#### 方法
##### 添加删除清空插入
```csharp?linenums
List<int> list = new List<int>();
list.Add(100);
list.AddRange(new int[]{1, 2, 3, 4, 5, 6});
Console.WriteLine(list[5]); //output: 5

list.Remove(100);           //移除100
list.RemoveAll(n => n > 3); //移除所有>3的数

list.RemoveAt(3);           //移除索引为3的元素
list.RemoveRange(1, 6);     //移除索引为[1,1+6]的元素（int startIndex, int count），第一个是开始索引，第二个是个数
list.Clear();               //清空集合

list.Insert(1, 100);        //在索引为1的后面插入元素100
list.InsertRange(0, new int[]{ 1, 2, 3, 4, 5, 6});//插入一个集合
```
##### 集合与数组的转换
集合转数组
```csharp?linenums
List<int> list = new List<int>();
for(int i = 0; i < 100; i++){
    list.Add(i);
}

int[] arr = list.ToArray();//能转换为什么类型的数组取决于集合的类型
```

数组转集合
```csharp?linenums
int[] nums = {1, 2, 3, 4, 5, 6};
list<int> list = nums.ToList();
```
### Dictionary<TKey, TValye>
foreach遍历：
```csharp?linenums
class Program {
	static void Main(string[] args) {
		Dictionary<string, string> dic = new Dictionary<string, string>();
		dic.Add("1", "张三");
		dic.Add("2", "李四");
		dic.Add("3", "王五");
		dic.Add("4", "赵六");
		//键值对集合中的键必须是唯一的
		//dic.Add(4, "田七");
		//键值对集合中的值是可以重复的
		dic.Add("5", "王五");
		//可以给键值对集合中的某一个值进行重新赋值
		dic["4"] = "田七";
		//键值对集合常用函数
		//判断集合中是否已经包含某一个键
		if (!dic.ContainsKey("3")) {
			dic.Add("3", "玩狗蛋儿");
		}
		else {
			dic["3"] = "王狗蛋儿";
		}

		Console.WriteLine(dic["3"]); //整体代表的就是值

		//使用foreach循环，通过遍历键值对的形式对键值对集合进行遍历
		//第一种遍历方式：遍历集合中的键
		foreach (string item in dic.Keys) {
			Console.WriteLine("键---{0}            值---{1}", item, dic[item]);
		}

		//第二种遍历方式：遍历集合中的键值对
		foreach (KeyValuePair<string, string> kv in dic) {
			Console.WriteLine("键---{0}            值---{1}", kv.Key, kv.Value);
		}

		Console.ReadKey();
	}
}
```
## 练习题
### 英汉字典
见附件

## 面试题
### 统计一个字符串中各字符出现的次数
```csharp?linenums
class Program {
	static void Main(string[] args) {
		string                str = "Welcome to China! Hello World!";
		Dictionary<char, int> dic = new Dictionary<char, int>();
		for (int i = 0; i < str.Length; i++) {
			if (str[i].Equals(' ') || str[i].Equals('!')) {
				continue;
			}

			//如果不包含，就添加进字典（第一次）
			if (!dic.ContainsKey(str[i])) {
				dic.Add(str[i], 1);
			}
			//否则，字典中存放数据次数的值自增
			else {
				dic[str[i]]++;
			}
		}

		//打印结果
		foreach (KeyValuePair<char, int> kv in dic) {
			Console.WriteLine($"Letter: {kv.Key}, Count: {kv.Value}");
		}

		Console.ReadKey();
	}
}
```
>C# in Depth Third Edition p54 代码清单3-1(统计文本中的单词数)
### 把中文日期转换为数组
见附件

# 序列化
就是把数据转换为0或者1，为了网络或者硬盘方便存储数据
网线：高电压1，低电压0，光纤与这个不同

# 迭代器
https://www.cnblogs.com/yangecnu/archive/2012/03/17/2402432.html

# 装箱和拆箱
## 简单说明
装箱：值类型 → 引用类型(Object类型)
拆箱：引用类型 → 值类型

装箱与拆箱的类型必须一致,如下代码，在拆箱时会报错。（指定的转换无效）
```csharp?linenums
static void Testaaa() {
	int    n = 10;
	object o = n;          //装箱,把int装箱
	double d = (double) o; //拆箱，拆为double
	Console.WriteLine(d);
	Console.ReadKey();
}
```
上面的拆箱时如果用int型去拆就不会报错。
## 装箱、拆箱必须是：值类型→引用类型 或 引用类型 → 值类型
object, 接口。值类型是可以实现接口。
Person p = new Student();//父类声明，实例化一个子类，这个叫隐式转换，不叫装箱。
Student stu = (Student)p;//这个叫显式类型转换，不叫拆箱

int类型为什么能装箱到object类型，但不能装箱到staring类型或Person类型？
>因为object类型是int类型的父类

拆箱时，必须用装箱时的类型来拆箱，如上代码所示。
## 方法重载时，如果具有该类型的重载，那么就不叫拆箱或装箱
`int n = 10; Console.WriteLine(n); //没有发生装箱，因为方法重载`
```csharp?linenums
static void Main(){
    int n = 10;
	Test(100);//调用的是Test(int n);
}

static void Test(object o) { }
static void Test(int n) { }
```
会匹配并调用最合适的方法。
## 接口与值类型之间的装箱与拆箱
```csharp?linenums
int n = 10;
IComparable com=n;//装箱操作
```
int32继承了IComparable接口，而接口也是引用类型，int32是值类型，所以发生了装箱
```csharp
public struct Int32 : IComparable, IFormattable, IConvertible, IComparable<int>, IEquatable<int>{}
```
## 字符串与数字相加调用的是string.Contact();
```csharp?linenums
int n = 10;
object o = n; //装箱1次
n = 100;
Console.WriteLine(n + "," + (int) o);//2次
Console.ReadKey();
```
3次装箱，一次拆箱
这段代码中的Console.WriteLine();
调用了`string.Concat(object arg0, object arg1, object arg2);`
其中，n 到 object 装箱一次，o到object装箱一次。
","到object没有装箱，因为两者都是引用类型。

![IL 中间语言，3次box，1次unbox, 并且调用的string.Contact的重载也显示出了](https://i.loli.net/2019/05/14/5cda13d075de597989.jpg)
## IL中间语言 box, unbox
装箱与拆箱的查看和方法的重载的查看
## 面试题
以下代码装箱了吗？如果发生了装箱，哪句代码？为什么？
```csharp?linenums
int n = 10;
string s1 = n.ToString();
string s2 = n.GetType().ToString();//由于GetType()不是虚方法子类没有重写，所以调用时需要通过object来调用。
Console.WriteLine(s1 + "\t\t\t" + s2);
```
`n.GetType()`发生了一次装箱。`GetType()`是object的，int没有，要把int转换为object，然后再调用这个方法
`n.ToString()` int.ToString()在int中是存在的。所以也就不存在装箱操作
最后一行代码的重载是三个string,没有重载
所以，以上代码就只发生了一次装箱。


```csharp?linenums
string s1 = "a";
int n1 = 10;
double d1 = 99.9;
object o = 10;//装箱一次，将int值转换为object类型
string s2 = "x";
string s3 = s1 + n1 + d1 + o + s2;//内部调用的还是Contact();
Console.WriteLine(s3);
Console.ReadKey();
```
`string s3 = s1 + n1 + d1 + o + s2;//内部调用的还是Contact();`调用的重载是`string.Contact(param object[] args)`
这里面的n1 一次，d1一次

所以，这段代码共有3次装箱。

# 程序集
## 概念
程序集是.net中的概念。
.net中的dll与exe文件都是程序集。（区别在于一个可执行，有Main函数，另一个不能被执行，没有程序入口）
程序集(Assembly)，可以看作是一堆相关类打一个包，相当于java中的jar包

使用程序集的好处？
* 程序集中只引用必须的程序集，减少程序的尺寸。
* 程序集可以封装一些代码，只提供必要的访问接口。

程序集包含资源文件，类型元数据（描述在代码中定义的每一类型和成员，二进制形式）、IL代码（这些都被装在exe或dll中），每个程序集都有自己的名称，版本等信息。这些信息可以通过`AssemblyInfo.cs`文件来定义。（显示在exe文件的属性页的详细信息选项卡中）
## 添加程序集
建一个项目程序集的引用。
再新建一个类库Common。
Common项目下添加一个类Person.
Person类中写一个方法：
```csharp
public void write(){
    File.WriteAllText("1.txt", "张三 李四 王五 赵六 田七"); 
}
```
![程序集](https://i.loli.net/2019/05/19/5ce0f51b1807621109.jpg)
“Common”与“程序集的引用”两个项目是没有关系的。

要想在"程序集引用"项目中使用"Common"项目中的Write方法：
在“程序集引用”项目中添加对"Common"项目的引用。
导入Person类的命名空间，把Person类的访问权限设置为`public`,否则在“程序集引用”项目中或其他外部项目中是无法使用这个类的。哪怕是添加了这个程序集。

编译Common项目，把dll放在另一个项目下（与exe相同目录），引用这个dll文件的另一种形式：
```csharp?linenums
using System.Text;
using System.Reflection;
using System.IO;
namespace 反射{
    class Program{
        static void Main(string[] args){
            string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Common.dll");
            Assembly ass = Assembly.LoadFile(path);
            
            //动态的获得程序集，路径是exe文件的相对路径下的Plugin文件夹
            string pathPlugin = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Plugins");
            //获得path路径下所有程序集文件的全路径
            string[] files = Directory.GetFiles(path, "*.dll");
            //遍历files, 加载所有的dll程序集文件
            foreach(string item in files){
                 ass = Assembly.LoadFile(item);
            }
            
            Console.WriteLine("加载程序集成功！");
            Console.ReadKey();
        }
    }
}
```
## Assembly.GetTypes
获得所有元数据（所有权限都能得到）
## Assembly.GetExportedTypes() : Type[]
获得程序集中定义的公共类型(public,不包括私有类型)
## 引入命名空间
命名空间就是类的“文件夹”，类就是“文件夹”中的文件，需要导入命名空间
添加引用：
如果需要在一个项目中，访问另一个项目中的某一个类
<ol>
    <li>添加对另一个项目的引用</li>
    <li>导入命名空间</li>
</ol>

# 反射
## 概念
动态获取程序集的元数据的功能

反射就是直接通过.dll来创建对象，调用成员。

通过类型元数据来获取对象的一些相关信息，并且还可以实例化对象调用方法等，这个就叫做“反射”

反射让创建对象的方式发生了改变
## 使用场景
IDE的智能提示，就是反射获取到类的属性、方法名等
反编译工具
## Type类
获得类型的类型。
实现反射的一个重要的类，通过这个类，可以获取类中的所有信息，包括方法、属性等。可以动态调用类的属性、方法。

Type是对类的描述。

bool IsAssignableFrom(Type c);//是否可以从c赋值，判断当前的类型的变量是不是可以接受c类型变量的赋值

typeof(Plugin).IsAssignableFrom(t);

bool IsInstanceOfType(object o);//判断对象o是否是当前类的实例（当前类可以是o的类，父类、接口）

bool IsSubclassOf(Type c);//判断当前类是否是类c的子类，类的事，没有接口的事

IsAbstract,判断是否为抽象的，含接口


```csharp?linenums
Type t = typeof(Person);//通过类获得Type
Type t = p.GetType("name");//通过对象获得类的Type

//"C:\adb.dll"
Assembly asm = Assembly.LoadFile("c:\abc.dll");

//调用Assembly的GetExportedTypes方法可以得到Assembly中定义的所有的public类型。

//调用Assembly的GetTypes()方法可以得到Assembly中定义的所有的类型

//调用Assembly的GetType(name)方法可以得到Assembly中定义的全名为name的类型信息

插件：扩展主程序功能的dll
```
## 动态创建对象的三个常用函数
Assembly.CreateInstance() 和 Activator.CreateInstance(Type t)的区别

Activator.CreateInstance(Type t)会动态调用类的无参构造函数创建一个对象，返回值就是创建的对象，如果类没有无参构造函数就会报错。
GetContructor(参数列表);//这个是找到带参数的构造函数

```csharp?linenums
static void Main(string[] args){
    string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Common.dll");
    Assembly ass = Assembly.LoadFile(path);
    
    //object o = ass.CreateInstance("Common.Person");//创建dll文件中的Common命名空间下的Person对象，调用其public的无参的构造函数，如果调不到则报错
    //把o强转为Person类型就可以继续操作了
    
    Type t = ass.GetType("Common.Person");
    object o1 = Activator.CreateInstance(t, params object[] args);//第二个参数，是object类型的可变数组，可以创建带有参数的构造函数的对象。
    //同上, 把o1强转为Person类型就可以继续操作
    
    Console.WriteLine(o1.GetType());//output: Common.Person, 说明创建成功
    
    //获得数据源中的属性数组
    PropertyInfo[] props = o1.GetType().GetProperties();
    foreach(PropertyInfo item in props){
        Console.WriteLine(item.Name);
    }
    
    //得到o1对象的所有方法，包括这个对象的父类方法
    MethodInfo[] md = o1.GetType().GetMethods();
    foreach(MethodInfo item in md){
        Console.WriteLine(item);
    }
    
    //得到o1对象的某个方法
    MethodInfo o1SayHelloMethod = o1.GetType().GetMethod("SayHello");
    //调用这个方法,第一个参数是拥有该方法的对象，第二个参数是方法的参数列表，如果有返回值，可以选择接收
    //object MethodBase.Invoke(object obj, object[] parameters);
    o1SayHelloMethod.Invoke(o1, null);//没有参数就填null

    Console.ReadKey();
}
```
关于动态调用成员的其他类
* MemberInfo 类，抽象类，有很多子类，获取程序集成员的相关信息（类型，方法，事件，字段和属性）
* PropertyInfo 获取属性
    * 主要成员：CanRead、CanWrite、propertyType属性类型;
    * SetValue、GetValue：读取值，设置值，第一个参数是实例对象，因为set、get要针对具体实例，最后一个参数null. pInfo.SetValue(p1, 30, null)
* MethodInfo 获取方法
    * MethodInfo都是和具体对象不相关的，所以需要第一个参数执行要执行的对象
* FieldInfo 获取字段
* EventInfo 获取事件

___
## 案例
反射实现计算器，Winform（简单工厂）和纯反射实现。
### 动态创建对象
`BindingFlags`: 要访问的字段或方法的权限描述，
必须要同时具备两个描述：
 1.要有访问的成员的访问权限描述 
 2.要有访问的成员的归属描述
必须与 Public | NonPublic 一起指定 Instance | Static,否则不返回成员
简而言之，就是`是否为public | 是否为Static`
这么说可能有问题，但就下面的例子来说，可以这么理解。
#### 无参构造函数
```csharp?linenums
/****************************************************
	文件：Program.cs
	作者：WQ
	邮箱: bcaso@qq.com
	日期：2019/04/21 18:06
	功能：C#高级之反射练习	     
*****************************************************/

using System;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		/// <summary>
		/// 构造函数默认都是public且无参的
		/// </summary>
		public PersonPublicCtor() {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}
	}

	class PersonPrivateCtor {
		private PersonPrivateCtor() {
			Console.WriteLine(GetType() + "/PersonPrivateCtor() private且无参的构造方法被调用");
		}
	}

	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor"); //要实例化的对象的类有命名空间的话需要加上
			Object person1Obj = Activator.CreateInstance(person1);


			//实例化一个具有私有构造函数的对象
			Type   person2    = Type.GetType("ConsoleApp1.PersonPrivateCtor"); //要实例化的对象的类有命名空间的话需要加上
			Object person2Obj = Activator.CreateInstance(person2, true);//第二个参数为true表示可以匹配任何权限的无参构造方法
		}
	}
}
```
![执行结果](https://i.loli.net/2019/04/21/5cbc633e299f6.jpg)
#### 有参构造函数
```csharp?linenums
/****************************************************
	文件：Program.cs
	作者：WQ
	邮箱: bcaso@qq.com
	日期：2019/04/21 18:06
	功能：C#高级之反射练习	     
*****************************************************/

using System;
using System.Reflection;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		/// <summary>
		/// 构造函数默认都是public且无参的
		/// </summary>
		public PersonPublicCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}
	}

	class PersonPrivateCtor {
		private PersonPrivateCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPrivateCtor() private且无参的构造方法被调用");
		}
	}

	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上
			Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型


			//实例化一个具有私有构造函数的对象
			Type person2 = Type.GetType("ConsoleApp1.PersonPrivateCtor"); //要实例化的对象的类有命名空间的话需要加上
			// NonPublic = 32 | Instance = 4,
			// 0x00000020     | 4
			// ‭00100000‬       | ‭0100‬
			//     0100 
			// 00100100 → 36
			Object person2Obj =
				Activator.CreateInstance(
				                         person2,                                       //type
				                         BindingFlags.NonPublic | BindingFlags.Instance, //bindingAttr
				                         null,                                           //binder
				                         new Object[] {1, 2.0, "string"},                //args
				                         null                                            //culture
				                        ); 
		}
	}
}
```
### 访问类中成员
非静态的类中的字段，需要通过对象访问，静态类中的字段需要通过类访问。
所以在给字段设置值时，如果是静态类，则对象可以为空，或者任意值，如果是普通类，则需要填入类。
#### 读写字段
```csharp?linenums
/****************************************************
	文件：Program.cs
	作者：WQ
	邮箱: bcaso@qq.com
	日期：2019/04/22 10:37
	功能：C#高级之反射练习
*****************************************************/

using System;
using System.Reflection;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		public  int a;
		private int b;

		public static  int c;
		private static int d;


		/// <summary>
		/// 构造函数默认都是public且无参的
		/// </summary>
		public PersonPublicCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}
	}

	class PersonPrivateCtor {
		public  int a2;
		private int b2;

		public static  int c2;
		private static int d2;

		private PersonPrivateCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPrivateCtor() private且无参的构造方法被调用");
		}
	}

	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上
			Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型

			//访问 public int a
			//因为要访问的字段是 public 非 static的，所以 可以简写为 FieldInfo a = person1.GetField("a"); 
			FieldInfo a = person1.GetField("a", BindingFlags.Public | BindingFlags.Instance);
			a.SetValue(person1Obj, 1);                        //给person1Obj的a字段进行赋值，赋值为1
			int aa = Convert.ToInt32(a.GetValue(person1Obj)); //获取person1Obj的字段a的值,返回值是object类型，所以要进行强制转转换
			Console.WriteLine("public int a = " + aa);

			//访问 private int b
			FieldInfo b = person1.GetField("b", BindingFlags.NonPublic | BindingFlags.Instance);
			b.SetValue(person1Obj, 2);
			int bb = Convert.ToInt32(b.GetValue(person1Obj));
			Console.WriteLine("private int b = " + bb);

			//访问 public static  int c
			FieldInfo c = person1.GetField("c", BindingFlags.Public | BindingFlags.Static);
			c.SetValue(person1Obj, 0);
			c.SetValue(null, 3); //为静态字段设置值时，第一个参数（object对象）可以为任意值，一般使用null
			int cc = Convert.ToInt32(c.GetValue(person1Obj));
			cc = Convert.ToInt32(c.GetValue(null)); //同上，可以为null
			Console.WriteLine("public static int c = " + cc);

			//访问 private static int d
			FieldInfo d = person1.GetField("d", BindingFlags.NonPublic | BindingFlags.Static);
			d.SetValue(person1Obj, 0);
			d.SetValue(null, 4); //为静态字段设置值时，第一个参数（object对象）可以为任意值，一般使用null
			int dd = Convert.ToInt32(d.GetValue(person1Obj));
			dd = Convert.ToInt32(d.GetValue(null)); //同上，可以为null
			Console.WriteLine("private static int d = " + dd);


			//实例化一个具有私有构造函数的对象
			Type person2 = Type.GetType("ConsoleApp1.PersonPrivateCtor"); //要实例化的对象的类有命名空间的话需要加上
			// NonPublic = 32 | Instance = 4,
			// 0x00000020     | 4
			// ‭00100000‬       | ‭0100‬
			//     0100 
			// 00100100 → 36
			Object person2Obj =
				Activator.CreateInstance(
				                         person2,                                        //type
				                         BindingFlags.NonPublic | BindingFlags.Instance, //bindingAttr
				                         null,                                           //binder
				                         new Object[] {1, 2.0, "string"},                //args
				                         null                                            //culture
				                        );

			//当实例化出一个对象后，下面的对字段的操作同上
			//访问 public int a2
			//同上，可以简写为：FieldInfo a2 = person2.GetField("a2");
			FieldInfo a2 = person2.GetField("a2", BindingFlags.Public | BindingFlags.Instance);
			a2.SetValue(person2Obj, 11);
			int aa2 = Convert.ToInt32(a2.GetValue(person2Obj));
			Console.WriteLine("public int a2 = " + aa2);

			//访问 private int b2
			FieldInfo b2 = person2.GetField("b2", BindingFlags.NonPublic | BindingFlags.Instance);
			b2.SetValue(person2Obj, 22);
			int bb2 = Convert.ToInt32(b2.GetValue(person2Obj));
			Console.WriteLine("private int b2 = " + bb2);

			//访问 public static  int c2
			FieldInfo c2 = person2.GetField("c2", BindingFlags.Public | BindingFlags.Static);
			c2.SetValue(person2Obj, 0);
			c2.SetValue(null, 33); //为静态字段设置值时，第一个参数（object对象）可以为任意值，一般使用null
			int cc2 = Convert.ToInt32(c2.GetValue(person2Obj));
			cc2 = Convert.ToInt32(c2.GetValue(null)); //同上，可以为null
			Console.WriteLine("public static int c2 = " + cc2);

			//访问 private static int d2
			FieldInfo d2 = person2.GetField("d2", BindingFlags.NonPublic | BindingFlags.Static);
			d2.SetValue(person2Obj, 0);
			d2.SetValue(null, 44); //为静态字段设置值时，第一个参数（object对象）可以为任意值，一般使用null
			int dd2 = Convert.ToInt32(d2.GetValue(person2Obj));
			dd2 = Convert.ToInt32(d2.GetValue(null)); //同上，可以为null
			Console.WriteLine("private static int d2 = " + dd2);
		}
	}
}
```
![执行结果](https://i.loli.net/2019/04/22/5cbd2978e1918.jpg)
`d2.SetValue(null, 44); //为静态字段设置值时，第一个参数（object对象）可以为任意值，一般使用null`
>第一个参数表示对象，object类型，在SetValue中没有使用，因为没有意义???，所以可以为任意值，一般使用null。

`dd2 = Convert.ToInt32(d2.GetValue(null)); //同上，可以为null`
### 访问类中的方法
由于篇幅原因，不再展示带有私有构造函数的类的函数的调用，当对象被实例化后，函数的调用形式一样。
#### 无参方法
##### void 方法
```csharp?linenums
/****************************************************
	文件：Program.cs
	作者：WQ
	邮箱: bcaso@qq.com
	日期：2019/04/22 10:37
	功能：C#高级之反射练习
*****************************************************/

using System;
using System.Reflection;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		/// <summary>
		/// 构造函数默认都是public且无参的
		/// </summary>
		public PersonPublicCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}

		public void ShowA() {
			Console.WriteLine("public void ShowA();");
		}

		private void ShowB() {
			Console.WriteLine("private void ShowB();");
		}
	}


	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上
			Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型
			
			//public void ShowA();
			MethodInfo method0ShowA = person1.GetMethod("ShowA",BindingFlags.Public|BindingFlags.Instance);
			method0ShowA.Invoke(person1Obj, null); //参数为：调用对象，方法的参数列表
			
			//private void ShowB();
			MethodInfo methodShowB = person1.GetMethod("ShowB", BindingFlags.NonPublic | BindingFlags.Instance);
			methodShowB.Invoke(person1Obj, null); //参数为：调用对象，方法的参数列表
		}
	}
}
```
##### static 方法
```csharp?linenums
/**************************************************** 
    文件：Program.cs 
    作者：WQ 
    邮箱: bcaso@qq.com 
    日期：2019/04/22 10:37 
    功能：C#高级之反射练习 
*****************************************************/ 
 
using System; 
using System.Reflection; 
 
namespace ConsoleApp1 { 
    class PersonPublicCtor { 
        /// <summary> 
        /// 构造函数默认都是public且无参的 
        /// </summary> 
        public PersonPublicCtor(int a, double b, string c) { 
            Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用"); 
        } 
 
		public static void ShowC() {
			Console.WriteLine("public static void ShowC();");
		}

		private static void ShowD() {
			Console.WriteLine("private static void ShowD();");
		} 
    } 
 
 
    class Program { 
        static void Main(string[] args) { 
            //实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化 
            Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上 
            Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型 
             
			//public static void ShowC();
			MethodInfo methodShowC = person1.GetMethod("ShowC", BindingFlags.Public | BindingFlags.Static);
			methodShowC.Invoke(null, null); //参数为：调用对象（静态方法可以为null,或任意值），方法的参数列表

			//private static void ShowD();
			MethodInfo methodShowD = person1.GetMethod("ShowD", BindingFlags.NonPublic | BindingFlags.Static);
			methodShowD.Invoke(null, null); //参数为：调用对象（静态方法可以为null,或任意值），方法的参数列表
        } 
    } 
} 
```
##### 有返回值的方法
```csharp?linenums
/**************************************************** 
    文件：Program.cs 
    作者：WQ 
    邮箱: bcaso@qq.com 
    日期：2019/04/22 10:37 
    功能：C#高级之反射练习 
*****************************************************/

using System;
using System.Reflection;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		/// <summary> 
		/// 构造函数默认都是public且无参的 
		/// </summary> 
		public PersonPublicCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}


		public string ShowA() {
			return "public string ShowA()";
		}

		private string ShowB() {
			return "private string ShowB()";
		}

		public static string ShowC() {
			return "public static string ShowC()";
		}

		private static string ShowD() {
			return "private static string ShowD()";
		}
	}


	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化 
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上 
			Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型 

			//public string ShowA() 
			MethodInfo methodShowA = person1.GetMethod("ShowA", BindingFlags.Public | BindingFlags.Instance);
			//public object Invoke(object obj, object[] parameters) 
			//Invoke返回值为object类型，即函数的返回值, 需要强转为需要的类型,ToString()就是转换为string类型 
			Console.WriteLine(methodShowA.Invoke(person1Obj, null).ToString());

			//private string ShowB(); 
			MethodInfo methodShowB = person1.GetMethod("ShowB", BindingFlags.NonPublic | BindingFlags.Instance);
			Console.WriteLine(methodShowB.Invoke(person1Obj, null).ToString());

			//public static string ShowC(); 
			MethodInfo methodShowC = person1.GetMethod("ShowC", BindingFlags.Public | BindingFlags.Static);
			Console.WriteLine(methodShowC.Invoke(null, null).ToString());

			//private static string ShowD(); 
			MethodInfo methodShowD = person1.GetMethod("ShowD", BindingFlags.NonPublic | BindingFlags.Static);
			Console.WriteLine(methodShowD.Invoke(null, null).ToString());
		}
	}
}
```
![有返回值的方法](https://i.loli.net/2019/04/22/5cbd502f6f6f4.jpg)
#### 有参方法
##### void 方法 和 static void方法
```csharp?linenums
/**************************************************** 
    文件：Program.cs 
    作者：WQ 
    邮箱: bcaso@qq.com 
    日期：2019/04/22 10:37 
    功能：C#高级之反射练习 
*****************************************************/

using System;
using System.Reflection;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		/// <summary> 
		/// 构造函数默认都是public且无参的 
		/// </summary> 
		public PersonPublicCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}


		public void ShowA(int a, double b, string c) {
			Console.WriteLine("public void ShowA(int a, double b, string c)()");
		}

		private void ShowB(int a, double b, string c) {
			Console.WriteLine("private void ShowB(int a, double b, string c)()");
		}

		public static void ShowC(int a, double b, string c) {
			Console.WriteLine("public static void ShowC(int a, double b, string c)()");
		}

		private static void ShowD(int a, double b, string c) {
			Console.WriteLine("private static void ShowD(int a, double b, string c)()");
		}
	}


	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化 
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上 
			Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型 

			//public void ShowA() 
			MethodInfo methodShowA = person1.GetMethod("ShowA", BindingFlags.Public | BindingFlags.Instance);
			//public object Invoke(object obj, object[] parameters) 
			methodShowA.Invoke(person1Obj, new object[] {1, 2.0f, "string"});

			//private void ShowB(); 
			MethodInfo methodShowB = person1.GetMethod("ShowB", BindingFlags.NonPublic | BindingFlags.Instance);
			methodShowB.Invoke(person1Obj, new object[] {1, 2.0f, "string"});

			//public static void ShowC(); 
			MethodInfo methodShowC = person1.GetMethod("ShowC", BindingFlags.Public | BindingFlags.Static);
			methodShowC.Invoke(null, new object[] {1, 2.0f, "string"});

			//private static void ShowD(); 
			MethodInfo methodShowD = person1.GetMethod("ShowD", BindingFlags.NonPublic | BindingFlags.Static);
			methodShowD.Invoke(null, new object[] {1, 2.0f, "string"});
		}
	}
}
```
![void 方法 和 static void方法](https://i.loli.net/2019/04/22/5cbd4e929e8dc.jpg)
##### 有返回值的方法
```csharp?linenums
/**************************************************** 
    文件：Program.cs 
    作者：WQ 
    邮箱: bcaso@qq.com 
    日期：2019/04/22 10:37 
    功能：C#高级之反射练习 
*****************************************************/

using System;
using System.Reflection;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		/// <summary> 
		/// 构造函数默认都是public且无参的 
		/// </summary> 
		public PersonPublicCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}


		public string ShowA(int a, double b, string c) {
			return "public string ShowA()";
		}

		private string ShowB(int a, double b, string c) {
			return "private string ShowB()";
		}

		public static string ShowC(int a, double b, string c) {
			return "public static string ShowC()";
		}

		private static string ShowD(int a, double b, string c) {
			return "private static string ShowD()";
		}
	}


	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化 
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上 
			Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型 

			//public string ShowA() 
			MethodInfo methodShowA = person1.GetMethod("ShowA", BindingFlags.Public | BindingFlags.Instance);
			//public object Invoke(object obj, object[] parameters) 
			//Invoke返回值为object类型，即函数的返回值, 需要强转为需要的类型,ToString()就是转换为string类型 
			Console.WriteLine(methodShowA.Invoke(person1Obj, new object[] {1, 2.0f, "string"}).ToString());


			//private string ShowB(); 
			MethodInfo methodShowB = person1.GetMethod("ShowB", BindingFlags.NonPublic | BindingFlags.Instance);
			Console.WriteLine(methodShowB.Invoke(person1Obj, new object[] {1, 2.0f, "string"}).ToString());


			//public static string ShowC(); 
			MethodInfo methodShowC = person1.GetMethod("ShowC", BindingFlags.Public | BindingFlags.Static);
			Console.WriteLine(methodShowC.Invoke(null, new object[] {1, 2.0f, "string"}).ToString());

			//private static string ShowD(); 
			MethodInfo methodShowD = person1.GetMethod("ShowD", BindingFlags.NonPublic | BindingFlags.Static);
			Console.WriteLine(methodShowD.Invoke(null, new object[] {1, 2.0f, "string"}).ToString());
		}
	}
}
```
![有返回值的方法](https://i.loli.net/2019/04/22/5cbd4f360d4df.jpg)
##### 有参有返回值的重载方法
```csharp?linenums
/****************************************************  
    文件：Program.cs  
    作者：WQ  
    邮箱: bcaso@qq.com  
    日期：2019/04/22 10:37  
    功能：C#高级之反射练习  
*****************************************************/

using System;
using System.Reflection;

namespace ConsoleApp1 {
	class PersonPublicCtor {
		/// <summary>  
		/// 构造函数默认都是public且无参的  
		/// </summary>  
		public PersonPublicCtor(int a, double b, string c) {
			Console.WriteLine(GetType() + "/PersonPublicCtor() public且无参的构造方法被调用");
		}


		public string Show(int a, double b, string c) {
			return "public string ShowA()";
		}

		private int Show(double b, int a, string c) {
			return a;
		}

		public static int Show(string a, int b, string c) {
			return b;
		}

		private static int Show(int a, double b, int c) {
			return a;
		}
	}


	class Program {
		static void Main(string[] args) {
			//实例化一个具有公共构造函数的对象，默认会使用public权限的无参的构造方法来实例化  
			Type   person1    = Type.GetType("ConsoleApp1.PersonPublicCtor");        //要实例化的对象的类有命名空间的话需要加上  
			Object person1Obj = Activator.CreateInstance(person1, 1, 2.0f, "Hello"); //最后一个参数是params objects[] args类型  

			//public string Show(int a, double b, string c)
			MethodInfo methodShowA = person1.GetMethod("Show",                                      //methodName
			                                           BindingFlags.Public | BindingFlags.Instance, //bindingAttr
			                                           null,                                        //binder
			                                           new Type[] {
				                                           typeof(int), typeof(double), typeof(string)
			                                           } ,  //type 
			                                           null //modifiers
			                                          );
			//public object Invoke(object obj, object[] parameters)  
			//Invoke返回值为object类型，即函数的返回值, 需要强转为需要的类型,ToString()就是转换为string类型  
			Console.WriteLine(methodShowA.Invoke(person1Obj, new object[] {1, 2.0f, "string"}).ToString());


			//private int Show(double b, int a, string c)
			MethodInfo methodShowB = person1.GetMethod("Show", BindingFlags.NonPublic | BindingFlags.Instance, null,
			                                           new Type[] {typeof(double), typeof(int), typeof(string)}, null);
			Console.WriteLine(methodShowB.Invoke(person1Obj, new object[] {1.0f, 2, "string"}).ToString());


			//public static int Show(string a, int b, string c)
			MethodInfo methodShowC = person1.GetMethod("Show", BindingFlags.Public | BindingFlags.Static, null,
			                                           new Type[] {
				                                           typeof(string), typeof(int), typeof(string)
			                                           }, null
			                                          );
			Console.WriteLine(methodShowC.Invoke(null, new object[] {"strA", 1, "strC"}).ToString());

			//private static int Show(int a, double b, int c) 
			MethodInfo methodShowD = person1.GetMethod("Show", BindingFlags.NonPublic | BindingFlags.Static, null,
			                                           new Type[] {
				                                           typeof(int), typeof(double), typeof(int)
			                                           }, null);
			Console.WriteLine(methodShowD.Invoke(null, new object[] {1, 2.0f, 3}).ToString());
		}
	}
}
```
![有参，有返回值，有重载的方法](https://i.loli.net/2019/04/22/5cbd61c875ded.jpg)

# XML
InnerXml与InnerText的区别在于InnerXml会把加入的内容当作Xml代码处理（如果有的话）。
不然就跟InnerText一样。InnerText会把xml代码中的符号转义。

Value 与 InnerText的区别，Value是InnerText的属性封装。基本没有区别。
## 文档对象模型
```csharp?linenums
using System;
using System.Collections.Generic;
using System.Xml;

namespace 文档对象模型_new {
	class Student {
		public int    ID     { get; set; }
		public string Name   { get; set; }
		public int    Age    { get; set; }
		public char   Gender { get; set; }
	}

	class Program {
		static void Main(string[] args) {
			List<Student> students = new List<Student>() {
				new Student() {
					ID     = 1,
					Name   = "扬洪波",
					Age    = 28,
					Gender =  '女'
				},
				new Student() {
					ID     = 2,
					Name   = "刘歧",
					Age    = 29,
					Gender = '中'
				},
				new Student() {
					ID     = 3,
					Name   = "汪磊",
					Age    = 20,
					Gender = '男'
				}
			};

			XmlDocument    document       = new XmlDocument();
			XmlDeclaration xmlDeclaration = document.CreateXmlDeclaration("1.0", "utf-8", null);
			XmlElement     root           = document.CreateElement("Person");

			document.AppendChild(xmlDeclaration); //添加描述
			document.AppendChild(root);           //添加根

			foreach (Student student in students) {
				XmlElement stu = document.CreateElement("Student"); //子节点对象
				//文档创建属性
				XmlElement name   = document.CreateElement("Name");
				XmlElement age    = document.CreateElement("Age");
				XmlElement gender = document.CreateElement("Gender");

				//属性设置值
				name.InnerXml   = student.Name;
				age.InnerXml    = student.Age.ToString();
				gender.InnerXml = student.Gender.ToString();

				//对象标签属性				
				stu.SetAttribute("studentID", student.ID.ToString());
				//添加对象
				root.AppendChild(stu);
				//对象的其他属性
				stu.AppendChild(name);
				stu.AppendChild(age);
				stu.AppendChild(gender);
			}

			document.Save("Student.xml");
			Console.WriteLine("保存或创建成功");
		}
	}
}
```
## XmlNode 与 XmlElement区别
>https://www.cnblogs.com/oilsun/archive/2012/07/07/2580427.html

>https://bbs.csdn.net/topics/70298324
```csharp?linenums
Element 是 Node 的子集 如:
<Book>             //node
  <Name>           //node
    C#             //node
  </Name>          //node
</Book>            //node

以上所有都是 Node
但是 只有 <Name>C#</Name> 和 <Book>.....</Book> 是 Element
```
## 增删改查
### 一般方式
`Person.xml`
```xml?linenums
<?xml version="1.0" encoding="utf-8"?>
<Person>
    <Student studentID="1">
        <Name>扬洪波</Name>
        <Age>28</Age>
        <Gender>女</Gender>
    </Student>
    <Student studentID="2">
        <Name>刘歧</Name>
        <Age>29</Age>
        <Gender>中</Gender>
    </Student>
    <Student studentID="3">
        <Name>T</Name>
        <Age>20</Age>
        <Gender>男</Gender>
    </Student>
    <Student studentID="10">
        <Name>john</Name>
        <Age>25</Age>
        <Gender>M</Gender>
    </Student>
</Person>
```

```csharp?linenums
using System;
using System.Xml;

namespace 对XML进行增删改查 {
	class Program {
		static void Main(string[] args) {
			//增加对象：ID = 10, Name = "john", Age = 25, Gender = 'M'
			//删除对象ID = 1
			//改变对象ID = 3, Name = "Tom"

			XmlDocument Person = new XmlDocument();
			Person.Load("Person.xml");

			XmlElement  root        = Person.DocumentElement; //根节点
			XmlNodeList xmlNodeList = root.ChildNodes;        //得到子节点集合


			#region 增加对象：ID = 10, Name = "john", Age = 25, Gender = 'M'

			bool hasID10 = false;
			foreach (XmlNode xmlNode in xmlNodeList) {
				if (xmlNode.Attributes["studentID"].Value == "10") {
					hasID10 = true;
				}
			}

			if (!hasID10) {
				XmlElement john = Person.CreateElement("Student");
				john.SetAttribute("studentID", "10");
				XmlElement Name   = Person.CreateElement("Name");
				XmlElement Age    = Person.CreateElement("Age");
				XmlElement Gender = Person.CreateElement("Gender");
				Name.InnerXml   = "john";
				Age.InnerXml    = "25";
				Gender.InnerXml = "M";
				root.AppendChild(john);
				john.AppendChild(Name);
				john.AppendChild(Age);
				john.AppendChild(Gender);
				Console.WriteLine("已经添加对象john");
			}

			#endregion 增加对象：ID = 10, Name = "john", Age = 25, Gender = 'M'

			#region 删除对象ID = 1

			XmlNode ID1 = null;
			foreach (XmlNode xmlNode in xmlNodeList) {
				if (xmlNode.Attributes["studentID"].Value == "1") {
					ID1 = xmlNode;
				}
			}

			if (ID1 != null) {
				root.RemoveChild(ID1);
				Console.WriteLine("已删除ID为1的对象");
			}

			#endregion

			#region 改变对象ID = 3, Name = "Tom"

			foreach (XmlNode xmlNode in xmlNodeList) {
				if (xmlNode.Attributes["studentID"].Value == "3") {
					if (xmlNode["Name"].InnerXml != "Tom") {
						xmlNode["Name"].InnerXml = "Tom";
						Console.WriteLine("已经把ID为3的对象的Name改为Tom");
					}
				}
			}

			#endregion


			Person.Save("Person.xml");
		}
	}
}
```
### 高级方式XPath
#### 增删改查
`Person.xml`
```csharp?linenums
<?xml version="1.0" encoding="utf-8"?>
<Person>
    <Student studentID="1">
        <Name>john</Name>
        <Age>25</Age>
        <Gender>M</Gender>
    </Student>
    <Student studentID="2">
        <Name>刘歧</Name>
        <Age>29</Age>
        <Gender>中</Gender>
    </Student>
    <Student studentID="3" test="test数据">
        <Name>T</Name>
        <Age>20</Age>
        <Gender>男</Gender>
    </Student>
</Person>
```
```csharp?linenums
using System;
using System.Xml;

namespace 对xml实现增删改查使用XPath {
	public class Class1 {
		//增加对象：ID = 10, Name = "john", Age = 25, Gender = 'M'
		//删除对象ID = 1
		//改变对象ID = 3, Name = "Tom" ，删除标签属性test = "3" 

		public static void Main(string[] args) {
			XmlDocument personXmlDocument = new XmlDocument();
			personXmlDocument.Load("Person.xml"); //得到文档
			XmlNode Student = personXmlDocument.SelectSingleNode("/Person");


			#region 增加对象：ID = 10, Name = "john", Age = 25, Gender = 'M'

			XmlNode ID10 = personXmlDocument.SelectSingleNode("/Person/Student[@studentID = '10']");
			if (ID10 == null) {
				ID10 = personXmlDocument.CreateElement("Student");
				XmlElement Name   = personXmlDocument.CreateElement("Name");
				XmlElement Age    = personXmlDocument.CreateElement("Age");
				XmlElement Gender = personXmlDocument.CreateElement("Gender");
				Name.InnerXml   = "john";
				Age.InnerXml    = "25";
				Gender.InnerXml = "M";

				//创建标签属性，属性也是使用文档对象创建
				XmlAttribute studentID = personXmlDocument.CreateAttribute("studentID");
				//添加到对象
				ID10.Attributes.Append(studentID);
				//修改值
				ID10.Attributes["studentID"].Value = "10";

				ID10.AppendChild(Name);
				ID10.AppendChild(Age);
				ID10.AppendChild(Gender);
				Student.AppendChild(ID10);
				Console.WriteLine("已经添加ID10");
			}
			else {
				Console.WriteLine("ID10已存在");
			}

			#endregion

			#region 删除对象ID = 1

			//XmlNode ID1 = personXmlDocument.SelectSingleNode("/Person/Student[@studentID='1']");//绝对路径，以/开头
			XmlNode ID1 = Student.SelectSingleNode("Student[@studentID='1']"); //使用相对路径，绝对路径以/开始
			if (ID1 != null) {
				Student.RemoveChild(ID1);
				Console.WriteLine("已经移除ID为1的属性");
			}
			else {
				Console.WriteLine("ID1不存在或已被删除");
			}

			#endregion 删除对象ID = 1

			#region 改变对象ID = 3, Name = "Tom"

			XmlNode ID3 = Student.SelectSingleNode("Student[@studentID = '3']");
			if (ID3 != null) {
				ID3.SelectSingleNode("Name").InnerXml = "Tom"; //这里改为.Value="Tom"。直接会抛异常Value在XmlNode中不能设置值
//				ID3.Attributes.RemoveNamedItem("test");        //删除名为test的标签属性
				//或者使用下面的方式
				XmlAttribute test = ID3.Attributes["test"];
				ID3.Attributes.Remove(test);
				Console.WriteLine("ID3的Name已被修改，ID3的test标签属性已被移除");
			}
			else {
				Console.WriteLine("ID3不存在");
			}

			#endregion


			personXmlDocument.Save("Person.xml");
		}
	}
}
```
#### XPath的相对路径与绝对路径以及其他知识点
>http://www.ruanyifeng.com/blog/2009/07/xpath_path_expressions.html

# 文件操作
## File
只能操作小文件，是一次性读取
### 文件位置
要读取的文件要最好是放在程序的相对路径下。
路径：`\解决方案名\项目名\bin\Debug\文件名.txt`
```csharp?linenums
static void Main(string[] args){
    string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Common.dll");//得到的是与exe相对路径下的文件common.dll的绝对路径
    Assembly ass = Assembly.LoadFile(path);
    Console.WriteLine("加载程序集成功！");
    Console.ReadKey();
}
```
### 常用操作
File是个静态类，不能创建对象，只能使用它的静态方法
复制Copy()
剪切Move()
删除Delete()
判断文件是否存在Exists()
### File.ReadAllines(stirng filePath)读取文本
//返回值是文本文件的所有的行，默认采用Utf-8去尝试读取文本文件
File.ReadAllLines(string filePath) : string[]

Encoding.Default 获取系统默认的编码格式
```csharp?linenums
//练习8：求员工工资文件中，员工的最高工资、最低工资、平均工资
//文件内容：
//肖义    350000
//艾青    53000
//李四    1000
//王狗蛋儿    20000
//用来存储工资
List<int> list  = new List<int>();
string[]  lines = File.ReadAllLines(@"C:\Users\god\Desktop\工资.txt", Encoding.Default);
for (int i = 0; i < lines.Length; i++) {
	//空格与tab符不一回事
	string[] temp = lines[i].Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
	//temp[1]对应的是工资，temp[0]是姓名
	list.Add(int.Parse(temp[1]));
}
Console.WriteLine(list.Max());
Console.WriteLine(list.Min());
Console.WriteLine(list.Sum());
Console.WriteLine(list.Average());
Console.ReadKey();
```
### File.ReadAllText()
读取所有文本，返回值是一个字符串。
默认会尝试使用utf-8打开文件。
### File.ReadAllByte(string filePath) : byte[]
读取所有字节，返回值是字节数组
使用Encoding转换为别的格式然后再使用
### File.WriteAllBytes
### File.WriteAllLines
### File.WriteAllText
### StreamWriter往文件中追加数据
```csharp?linenums
//创建文本文件到exe所在目录
string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "data.txt");
	if (!File.Exists(path)) {
	File.Create(path);
}

//File.WriteAllLines(path, _text);//把数据全部写入到文件中，如果有内容先清空
//把数据追加到文件中
using (StreamWriter sw = new StreamWriter(path, true)) {//true表示追加
	foreach (string s in _text) {
		sw.WriteLine(s);
	}

	sw.WriteLine();//在追加完一次数据后添加一个换行
}

//打开并查看文件内容
System.Diagnostics.Process.Start("Explorer.exe", path);
```

## Directory
### 案例
#### 文件管理器Winform
## FileStream(可用于大文件，操作字节，支持所有文件，数据的最终形式就是二进制，字节)

# 工具类
## 正则表达式
常用的三种情况：
* 判断是否匹配:`Regex.IsMatch("string", "正则表达式");`
* 字符串提取：`Regex.Match("string", "要提取的字符串的正则表达式");`一次只能提取一个
* 字符串提取：`Regex.Matches()`可以提取所有匹配的字符串
* 字符串替换：`Regex.Replace("string", "正则", "替换内容")`

工具：
`The Regulator version 2.0` //有可能崩溃，之后就再也打不开了。。
### 从网页中提取所有邮箱
### 正则表达式下载页面图片到指定文件目录下
```csharp?linenums
using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;

namespace 下载网页中的图片到文件 {
	class Program {
		static void Main(string[] args) {
			//正则
			string pattern = "<img src=\"(?<address>http://cdn1.pussygirls.com/.+/.+/.+.jpg)";

			WebClient webClient = new WebClient();
			//下载网页数据到字节数组
			byte[] buffer = webClient.DownloadData("http://pussygirls.com");
			//将字节数据转为字符串，也就是网页代码
			string htm = Encoding.Default.GetString(buffer);
			//用于保存网页代码中的图片地址
			List<string> picsName = new List<string>();

			//往集合中添加图片地址
			MatchCollection matchCollection =	Regex.Matches(htm, pattern);
			foreach (Match match in matchCollection) {
				if (match.Success) {
					picsName.Add(match.Groups["address"].Value);
				}
			}

			//创建files目录用于存储下载的图片
			if (!Directory.Exists("files")) {
				Directory.CreateDirectory("files");
			}

			Console.WriteLine($"总共获取到{picsName.Count}张图片。下载开始：");
			int i = picsName.Count;
			int j = 0;
			foreach (string item in picsName) {
				Console.WriteLine($"正在下载第{++j}张图片，下载进度:{j}/{i}");
				//截取文件名
				int    index    = item.LastIndexOf('/');
				string fileName = item.Substring(index + 1);
				//将文件下载到files目录下
				webClient.DownloadFile(item, "files/" + fileName);
			}

			//下载完成后打开目录
			System.Diagnostics.Process.Start("Explorer.exe", @".\files");
			Console.WriteLine("下载成功");


			Console.ReadKey();
		}
	}
}
```
### 基本操作
匹配成功与替换
### 输入是否合法
## 计时器Stopwatch
使用步骤：
* 创建一个Stopwatch对象stopwatch
* 调用对象的<b>Start()</b>方法，开始计时,`stopwatch.Start();`
* 要计算的代码逻辑内容，常是for循环
* 最后调用`stopwatch.Stop()`方法，停止计时
* `stopwatch.Elapsed`就是代码运行时长

```csharp?linenums
StringBuilder sb = new StringBuilder();
//00:00:00.1022297
Stopwatch sp = new Stopwatch();
sp.Start();
for (int i = 0; i < 100000; i++){
    sb.Append(i);
}
sp.Stop();

Console.WriteLine(sp.Elapsed);
Console.WriteLine(sb.ToString());
```
## MD5加密
```csharp?linenums
class Program {
	static void Main(string[] args)	{
		//张三abc  abc123  明文保存

		string str = "123";
		//202cb962ac59075b964b07152d234b70
		//202cb962ac59075b964b07152d234b70
		//202cb962ac5975b964b7152d234b70
		//3244185981728979115075721453575112
		string md5Str = GetMd5(str);
		Console.WriteLine(md5Str);
		Console.ReadKey();
	}

	static string GetMd5(string str) {
		MD5    md5    = MD5.Create();
		byte[] buffer = Encoding.Default.GetBytes(str);
		//开始加密 返回加密好的字节数组
		byte[] bufferMd5 = md5.ComputeHash(buffer);
		//转成字符串
		//string result = Encoding.Default.GetString(bufferMd5);
		//return result;
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < bufferMd5.Length; i++){
			sb.Append(bufferMd5[i].ToString("x2")); //x:表示将十进制转换为16进制
		}
		return sb.ToString();
	}
}
```
关于ToString("x2");
>https://www.cnblogs.com/kuang906/articles/2301361.html
# 垃圾回收
垃圾回收不受控制，可用`GC.COllect();`来强制回收。微软强烈不建议手动调用。
垃圾回收是不定时的被调用，自动调用并扫描垃圾然后回收。