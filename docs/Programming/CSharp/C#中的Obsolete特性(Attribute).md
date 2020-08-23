---
title: C#中的Obsolete特性(Attribute)
tags: Csharp,Attribute
grammar_cjkRuby: true
---
使用Obsolete特性来标记该方法是一个被荒弃的方法。
Obsolete attribute位于System命名空间，它是一个attribute类型，以Obsolete或者ObsoleteAttribute来指定attribute类型都是允许的，在编译时，会自动添加上 “Attribute” 后缀。
指定一个attribute，用方括号[]围起所期望的attribute，置于所要修饰的方法、接口、属性、委托、事件等语言元素之前。对于Obsolete attribute，还可以为其指定0、1或2个参数。
```csharp
using System;
class Program{
    static void Main(){
        MethodA();
    }

    [Obsolete("Use MethodB instead")]
    static void MethodA(){

    }
}
```
该程序在编译时会产生警告消息：警告 1 “Program.MethodA()”已过时:“Use MethodB instead” 。
对于C#中的其它构造器，用同样的方法来使用Attributes。Obsolete attribute可以不含参数；可以含一个参数，用以产生一个编译警告信息；也可以含两个参数，第一个参数用以产生编译警告/错误时的提示信息，第二个参数用以指定处理方式（true：产生编译错误；false：产生编译警告）。

对于有不同版本的程序代码，obsolete attribute显得大有用武之地。如果开发了一个新的方法，并且可以确定不再希望使用某方法，那么就可以使用Obsolete attribute来修饰该方法，编译代码后，按警告/错误提示信息逐一更正原来的代码。在一个大型工程中，有助于协调不同的程序员所采用的方法。