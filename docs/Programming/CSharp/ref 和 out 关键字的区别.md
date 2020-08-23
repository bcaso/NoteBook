---
title: ref 和 out 关键字的区别
tags: csharp,Function
grammar_cjkRuby: true
---

# 简介
在C#中，ref与out是很特殊的两个关键字。使用它们，可以使**参数按照引用来传递**.
<br>
传递的不只是一个值，而是原来的变量, 变量的引用传递。变量更改，这个变量的值也会更改。
<br>
通常我们向方法中**传递的是值**.方法获得的是这些值的一个拷贝,然后使用这些拷贝,当方法运行完毕后,这些拷贝将被丢弃,而原来的值不将受到影响.
<br>
此外我们还有其他向方法**传递参数**的形式,引用(ref)和输出(out).
> paramsparams修饰的参数，可以传一个数组，参数修饰的数组相当于长度可变的参数数组。它是修饰参数（一维数组）的一个关键字。用处就是在不知道参数个数或参数个数有可能发生变化的情况下使用。具体使用请再Google.

```csharp?linenums
using System;
namespace Program {
    class MyClass {
        static void Main(string[] args) {
            TestRefAndOut();    //output: Hello World!
            Console.ReadKey();
        }
        
        //output: Hello World!
        static void TestRefAndOut() {
            string s1 = "Good Luck!";
            TestRef(ref s1);
            Console.WriteLine(s1);//output: Hello World!
        }
        static void TestRef(ref string str) {
            str = "Hello World!";
        }
    }
}
```
如果将上面代码中的`TestRef`方法中的参数改为`(out string str)`在将ref换成out后，会发现最后的输出仍然是相同的.

>在使用两个关键字时，调用方法时用的修饰符(ref || out) 要跟定义这个方法时的修饰符(ref || out)保持一致

代码如下：
```csharp?linenums
using System;
namespace Program {
    class MyClass {
        static void Main(string[] args) {
            TestRefAndOut();
            Console.ReadKey();
        }

        static void TestRefAndOut() {
            string s1 = "Good Luck!";
            TestRef(out s1);
            Console.WriteLine(s1);//output: Hello World!
        }
        static void TestRef(out string str) {
            str = "Hello World!";
        }
    }
}
```

# 那这两个关键字的区别是什么呢？
进一步测试：
`ref`
```csharp
static void TestRefAndOut(){
    string s1 = "Good Luck!";
    TestRef(ref s1);
}

static void TestRef(ref string str){
    Console.WriteLine(str);//output: Good Luck!            
}
```
`out`
```csharp
static void TestRefAndOut(){
    string s1 = "Good Luck!";
    TestOut(out s1);
}

static void TestOut(out string str){
    Console.WriteLine(str);//compile does not pass
}
```
**ref**的那段代码顺利编译，输出"Good Luck!"，而**out**那段代码却无法通过编译，提示`Use of unassigned out parameter 'str'`,即使用了未分配地址的out参数str。怎么回事呢？
<br>
原来**out参数在进入方法的时候，C#会自动清空它的一切引用和指向**，所以在上面的out例子中，**必需先要为 str 参数赋值**。如以下程序。
```csharp
static void TestRefAndOut(){
    string s1 = "Good Luck!";
    TestOut(out s1);
}

static void TestOut(out string str){
    str = "Hello World!";
    Console.WriteLine(str);//output: Hello World!
}
```
Ok，得到第一个区别： <font size = 5>out 参数在进入方法（函数）时后清空自己，使自己变成一个干净的参数，也因为这个原因必须在方法内部的"方法返回"之前为 out指向的参数赋值（**只有地址没有值的参数是不能被.net接受的**）；
而ref参数是不需要在被调用方法中赋值的,甚至也可以被调用方法中不改变ref参数的值，这都不会引起编译错误。</font>

<br>

在继续看一段代码：
```csharp
// ref:
static void TestRef(ref string str){
    str = "Hello World!";
}

static void TestRefAndOut(){
    string s1;
    TestRef(ref s1);
    Console.WriteLine(s1);//compile does not pass!
}
```

```csharp
// out：
static void TestOut(out string str){
    str = "Hello World!";
} 
static void TestRefAndOut(){
    string s1;
    TestOut(out s1);
    Console.WriteLine(s1);//output: Hello World!
}
```
这回发现，ref这段代码无法编译了，s1是一个空引用，所以无法使用。而out参数则因为上述的那个原因，它不在乎s1是不是空引用，因为就算s1不是空引用，它也会把s1变成空引用的。

Ok，第二个区别：**ref参数在使用前必需初始化，而out不需要。（out必须在新的方法内部为out指向的参数赋值）**

# 区别
ref和out区别:
* 使用ref的时候必须要先赋值，否则编译错误，而out并不需要。
* 对应的，在实现的方法中，out必须赋值，而ref不强求。
    * 在用法上概括一下就是：out适合用在需要retrun多个返回值的地方，而ref则用在需要被调用的方法修改调用者的引用的时候。

# unity中的特殊情况
unity中的很多函数中的out修饰符在使用时后面的变量都没有指定类型，具体原因，待研究
如下面代码中的`out hit`就没没有指定hit是什么类型的参数。

![鼠标射线](https://i.loli.net/2018/10/17/5bc70a68a11dc.png)
代码：
```csharp?linenums
void update(){
    if(Input.GetMouseButtonDown(0)){
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if(Physics.Raycast(ray, out hit)){
            //hit.point,打印鼠标点击的位置
            print(hit.point);
        }
    }
}
```

<br>

# 试编写一程序，要求输出数组中最大值，同时打印这个最大值的索引
答案在最后 ↓
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
// 复制粘贴到编辑器中试下吧？
这段代码同样可以改为ref，修改方式同例2
```csharp
using System;
namespace Program {
    class MyClass {
        static void Main(string[] args) {
            int[] array = new int[] { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 20, 20, 20, 18 };
            int maxIndex;
            Console.WriteLine("The maxium value in array is {0}", GetMax(array, out maxIndex));
            // 输出这个最大值第一次出现的位置(可能有多个最大值), 同时因为这个maxIndex是从0开始的所以要加1
            Console.WriteLine("The first occurrence of this value is at element {0}", maxIndex + 1);

            Console.ReadKey();
        }
        /// <summary>
        /// 计算一个数组的最大值，并返回这个值，同时改变最大值索引
        /// </summary>
        /// <param name="array">传入要计算的数组</param>
        /// <param name="maxIndex">传入一个表示最大值索引的int型变量，这个值是引用类型</param>
        /// <returns>返回传入的数组中的最大值</returns>
        static int GetMax(int[] array, out int maxIndex) {
            maxIndex = 0;
            int max = 0;
            for (int i = 0; i < array.Length; i++) {
                if (array[i] > max) {
                    max = array[i];
                    maxIndex = i;
                }
            }
            return max;             // 返回最大值，同时在方法执行时 改变 maxIndex
        }
    }
}
```

## 例2：
```csharp
using System;
namespace Program {
    class MyClass {       
        static void Main(string[] args) {

            string text;
            MyClass myClass = new MyClass();
            myClass.ChangeText(out text);
            Console.WriteLine(text);

            Console.WriteLine("last text output in loop: {0}", text);
            Console.ReadKey();
        }
        void ChangeText(out string text) {
            text = String.Empty;
            for (int i = 0; i < 10; i++) {
                text = "Line " + Convert.ToString(i);
                Console.WriteLine("{0}", text);
            }
        }
    }
}
```
例2改为ref
```csharp
using System;
namespace Program {
    class MyClass {       
        static void Main(string[] args) {

            string text = String.Empty;
            MyClass myClass = new MyClass();
            myClass.ChangeText(ref text);
            Console.WriteLine(text);

            Console.WriteLine("last text output in loop: {0}", text);
            Console.ReadKey();
        }
        void ChangeText(ref string text) {
            //text = String.Empty;
            for (int i = 0; i < 10; i++) {
                text = "Line " + Convert.ToString(i);
                Console.WriteLine("{0}", text);
            }
        }
    }
}
```