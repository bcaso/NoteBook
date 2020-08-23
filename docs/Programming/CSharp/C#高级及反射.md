<!--这是一个锚点，名称为"Head", 类型为"#", 也是一个空的超链接-->
<a href = "#" name = "Head"></a>

[toc]


# C#高级之反射
<!--这是一个锚点，名称为"chapter1", 类型为"#", 也是一个空的超链接-->
<a href = "#" name = "chapter1"></a>
## 1. 动态创建对象
`BindingFlags`: 要访问的字段或方法的权限描述，
必须要同时具备两个描述：
 1.要有访问的成员的访问权限描述 
 2.要有访问的成员的归属描述
必须与 Public | NonPublic 一起指定 Instance | Static,否则不返回成员
简而言之，就是`是否为public | 是否为Static`
这么说可能有问题，但就下面的例子来说，可以这么理解。


### 1.1 无参构造函数
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

<a href = "#Head" title = "跳转到目录">返回顶层</a>
### 1.2 有参构造函数
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
<a href = "#Head" title = "跳转到目录">返回顶层</a>



<!--这是一个锚点，名称为"chapter2", 类型为"#", 也是一个空的超链接-->
<a href = "#" name = "chapter2"></a>
## 2. 访问类中成员
非静态的类中的字段，需要通过对象访问，静态类中的字段需要通过类访问。
所以在给字段设置值时，如果是静态类，则对象可以为空，或者任意值，如果是普通类，则需要填入类。
### 2.1 读写字段
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

<a href = "#Head" title = "跳转到目录">返回顶层</a>


<!--这是一个锚点，名称为"chapter3", 类型为"#", 也是一个空的超链接-->
<a href = "#" name = "chapter3"></a>
## 3. 访问类中的方法
由于篇幅原因，不再展示带有私有构造函数的类的函数的调用，当对象被实例化后，函数的调用形式一样。
### 3.1 无参方法

#### void 方法
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
#### static 方法
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

#### 有返回值的方法
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
### 3.2 有参方法
#### void 方法 和 static void方法
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

#### 有返回值的方法
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

#### 有参有返回值的重载方法
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
