---
title: getch(),getche(),getchar()的区别 （综合转）
tags: C,Function
grammar_cjkRuby: true
---
[toc]
# (1) getch()和getche()函数
这两个函数都是从键盘上读入一个字符。其调用格式为:
```c
头文件：conio.h
getch(); //从控制台读取一个字符，但不显示在屏幕上
    在VS2017中使用这个函数在不引用头文件 conio.h的情况下，正常。在引用了这个头文件的情况下使用这个函数，会报错。
    Severity	Code	Description	Project	File	Line	Suppression State
Error	C4996	'getch': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _getch. See online help for details.
    意思大概是说getch()函数已被弃用，使用_getch()代替。

getche(); //从控制台取字符(带回显)
```

例1:
```c
#include <stdio.h>
main(){
    char c, ch;
    c=getch();      /*从键盘上读入一个字符不回显送给字符变量c*/ 
    putchar(c);     /*输出该字符*/
    ch=getche();    /*从键盘上带回显的读入一个字符送给字符变量ch*/
    putchar(ch);
}
```
利用回显和不回显的特点, 这两个函数经常用于交互输入的过程中完 **暂停** 等功能。
例2:
`Press any key to continue`的实现方式 ↓
```c?linenums
#include<stdio.h>
main(){
    printf("Press any key to continue...");
    getch();    /*等待输入任一键*/ 
} 
```
# (2) getchar()函数
&emsp;&ensp;getchar()函数也是从键盘上读入一个字符,并带回显。它与前面两个函数 的区别在于: getchar()函数等待输入直到按回车才结束, 回车前的所有输入字 符都会逐个显示在屏幕上。但只有第一个字符作为函数的返回值。 
　getchar()函数的调用格式为:
```
　getchar();
```

例3:
```c?linenums
#include <stdio.h>
main(){
    char c;
    c=getchar();     /*从键盘读入字符直到回车结束*/ 
    putchar(c);      /*显示输入的第一个字符*/
    printf("Press any key to continue...");
    getch();        /*等待按任一健*/ 
}
``` 

例4
```c?linenums
#include<stdio.h>
main(){
    char c;
    while ((c=getchar())!='/n')   /*每个getchar()依次读入一个字符*/
    printf("%c",c);           /*按照原样输出*/ 
    printf("Press any key to continue...")
    getch();                /*等待按任一健*/ 
}
```
再说下文件尾部getch();的原因。 

&emsp;&emsp;首先不要忘了，要用`getch()`必须引入头文件`conio.h`，以前学C语言的时候，我们总喜欢用在程序的末尾加上它，利用它来实现程序运行完了暂停不退出的效果。如果不加这句话，在TC2.0的环境中我们用Ctrl+F9编译并运行后，程序一运行完了就退回到TC环境中，我们根本来不及看到结果，这时要看结果，我们就要按Alt+F5回到DOS环境中去看结果，这很麻烦。而如果在程序的结尾加上一行`getch();`语句，我们就可以省掉会DOS看结果这个步骤，因为程序运行完了并不退出，而是在程序最后把屏幕停住了，按任意键才退回到TC环境中去。那我们来看看`getch()`到底起的什么作用，`getch()`实际是一个输入命令，就像我们用`cin>>`的时候程序会停下来等你输入，和`cin`不同的是，`getch()`的作用是从键盘接收一个字符，而且并不把这个字符显示出来，就是说，你按了一个键后它并不在屏幕上显示你按的什么，而继续运行后面的代码，所以我们在C++ 中可以用它来实现“按任意键继续”的效果，即程序中遇到`getch();`这行语句，它就会把程序暂停下来，等你按任意键，它接收了这个字符键后再继续执行后面的代码。
 &emsp;&emsp; 你也许会问，为什么我们在 C++ 中就没有在程序的末尾加上`getch()`。解释是，软件总是不段更新的，不好的地方当然需要改正，`getch()`加在程序末尾，它又不赋值给任何变量，所以它在这个地方完全是垃圾代码，与程序无关。C++ 中考虑到这一点，于是在每次程序运行完了并不退出，而是自动把屏幕停下来，并显示“press any key...”叫你按任意键退出，这就好比C++ 在它的环境中运行程序，在程序的末尾自动加上了一行`getch();`语句，并且在这行语句前还添加了一行输出语句`cout<<"press any key...";`来提示你程序结束了，按任意键继续。
&emsp;&emsp;实际上我们编译好的程序在程序结束了本身是不会停下来的，我们可以在编译产生的Debug目录中找到这个编译好的应用程序（扩展名exe），在文件夹中双击运行它，你会发现屏幕闪了一下MS-DOS窗口就关闭了，因为程序运行完就自动退出了，回到了windows环境，当然，如果我们在DOS环境中运行这个程序，我们就可以直接在看到DOS屏幕上看到程序运行结果，因为程序运行完后并不清屏。　　
&emsp;&emsp;还有一个语句，和`getch()`很相似，`getche()`，它也需要引入头文件`conio.h`，那它们之间的区别又在哪里呢？不同之处就在于`getch()`无返回显示，`getche()`有返回显示。怎么说呢？我举个例子你就明白了。

```c?linenums
#include<stdio.h>
#include<conio.h>
int main(void){
    char ch;
    for(int i=0;i<5;i++){
        ch=getch();
        printf("%c",ch);
    }
    return 0;
}
```
&emsp;&emsp;这里输入输出我用的是C的函数库，没有用C++ 的`iostream.h`，这个我等会再说。首先这是个连续5次的循环来实现5次停顿，等待我们输入，我们编译并运行这个程序，假设我们分别输入`abcde`，屏幕上显示的结果是`abcde`，这个abcde并不是在`ch=getch();`中输出的，我们把`printf("%c",ch);`这行语句去掉，就会发现我们按5次任意键程序就结束了，但屏幕上什么都没有显示。
&emsp;&emsp;然后我们在把代码中的`getch()`换成`getche()`看看有什么不同，我们还是分别输入`abcde`，这时屏幕上显示的结果是`aabbccddee`，我们把`printf("%c",ch);`这行语句再去掉看看，显示的结果就是`abcde`了，说明程序在执行`ch=getche();`这条语句的时候就把我们输入的键返回显示在屏幕上，有无回显就是它们的唯一区别。
 好了，我们再来说说为什么不用C++ 函数库的原因。你可以试试把这个程序改成C++ 的形式：
```c?linenums
#include<iostream.h>
#include<conio.h>
int main(void){
    char ch;
    for(int i=0;i<5;i++){
        ch=getch();
        cout<<ch;
    }
    return 0;
}
```
&emsp;&emsp;你会发现运行结果是完全不同的，说实话我也搞不清它是怎么编译运行的，以前我在C++ 中用它来实现任意键继续的功能就发现了这个问题。<font color = red>如果在`getch();`后面有个`cout<<"……";`语句的话他会先执行下面的`cout<<"……";`然后再执行`getch();`实现停顿，有时再两个语句中间加上一个`cout<<endl;`可以解决这个问题，但如果用C中的printf()就从没有出现过这种问题。至于到底是为什么，我也不知道，只能猜想，可能是因为getch()是C的函数库中的函数，在C++中不怎么好用，就是说是编译系统本身的问题，与我们写的程序没有关系。不知道我分析是不是正确的，还希望高手能予以指点，谢谢！</font>
&emsp;&emsp;有人会说，既然是C的函数库中的，那么就应该淘汰了，我们还研究它，还用它干嘛？但是我发现还是有用着它的地方，否则我也不会在这里说这么多来耽误大家的时间。我就举个例子吧，程序如下：
```c?linenums
#include<stdio.h>
#include<conio.h>
int main(void){
    char ch='*';
    while(ch=='*'){
        printf("/n按 * 继续循环，按其他键退出！");
        ch=getch();
    }
    printf("/n退出程序！");
    return 0;    
}
```
&emsp;&emsp;我们可以在这个循环体中添加我们想要的功能，程序中按*继续循环，其他任意键退出，而且利用`getch()`无回显的特性，我们不管按什么，都不会在屏幕上留下痕迹，使我们的界面达到美观效果，如果还有更好的办法实现这个功能，我可能就不会在这里提这么多了。如果你真的有更好的办法，请一定告诉我，谢谢！
&emsp;&emsp;下面我把别人网页上的几个例子转载如下：
<font color = green>//例一：这个例子是为了说明getch()和getche()的区别</font>
```c?linenums
#include<stdio.h>
#include<conio.h>
int main(void){
    char c, ch;
    c=getch();      /*从键盘上读入一个字符不回显送给字符变量c*/
    putchar(c);     /*输出该字符*/
    ch=getche();    /*从键盘上带回显的读入一个字符送给字符变量ch*/
    putchar(ch);
    printf("/n/n");
    return 0;
}
```
--------------------------------------
<font color = "Green">//例二：这个例子是演示交互输入的过程中完成暂停功能</font>
```c?linenums
#include<stdio.h>
#include<conio.h>
int main(void){
    char c, s[20];
    printf("Name:");
    gets(s);
    printf("Press any key to continue...");
    getch();    /*等待输入任一键*/
    return 0;
}
```
<font color = "Green">//例三：getchar()函数也是从键盘上读入一个字符，并带回显。它与前面两个函数的区别在于：
//　　　getchar()函数等待输入直到按回车才结束，回车前的所有输入字符都会逐个显示在屏幕上。
//　　　但只有第一个字符作为函数的返回值。</font>
```c?linenums
#include<stdio.h>
#include<conio.h>
int main(void){
    char c;
    c=getchar();    /*从键盘读入字符直到回车结束*/
        //getchar()在这里它只返回你输入字符串的第一个字符，并把返回值赋值给c
    putchar(c);     /*显示输入的第一个字符*/
    return 0;
}
```
//例四：呵呵，这个程序你运行一下，相信你又会有疑问了
```c?linenums
#include<stdio.h>
#include<stdlib.h>
int main(void){
    char c;
    while ((c=getchar())!='\n')/*每个getchar()依次读入一个字符*/
    printf("%c",c);         /*按照原样输出*/
    return 0;
}
```
&emsp;&emsp;例四的程序运行时，首先停下来，等你输入一串字符串，输入完毕后，它把你输入的整个字符串都输出来了，咦，你不是说getchar()只返回第一个字符么，这里怎么？
&emsp;&emsp;不要急，我慢慢跟你解释，忍耐一下，马上就讲完了。因为我们输入的字符串并不是取了第一个字符就把剩下的字符串丢掉了，它还在我们的内存中，就好比，开闸放水，我们把水放到闸里去以后，开一次闸就放掉一点，开一次就放掉一点，直到放光了为止，我们输入的字符串也是这么一回事，首先我们输入的字符串是放在内存的缓冲区中的，我们调用一次`getchar()`就把缓冲区中里出口最近的一个字符输出，也就是最前面的一个字符输出，输出后，就把它释放掉了，但后面还有字符串，所以我们就用循环把最前面的一个字符一个个的在内存中释放掉，直到不满足循环条件退出为止。例子中循环条件里的'/n'实际上就是你输入字符串后的回车符，所以意思就是说，直到遇到回车符才结束循环，而`getchar(`函数就是等待输入直到按回车才结束，所以实现了整个字符串的输出。当然，我们也可以把循环条件改一下，比如`while ((c=getchar())!='a')`，什么意思呢，意思就是遇到字符'a'就停止循环。 
>--------------------- 本文来自 猫已经找不回了 的CSDN 博客 ，全文地址请点击：https://blog.csdn.net/hairetz/article/details/4161954?utm_source=copy