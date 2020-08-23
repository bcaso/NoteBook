```cs
// TODO: Hello
// TODO Hello
// ToDo
```
Ctrl + Alt + K 弹出任务列表，即可查看 已设置的todo注释
或者，View → TaskList 
或者，View → Previous Task
或者，View → Nest Task

简单来说，//todo就类似于我们看书时使用的书签，当我们为了某种功能预留下编程的入口，但是短时间内又没时间完成代码时就可以留下一个//todo标记，它仅仅代表着这里还有坑没填。在VS编程环境下，在视图菜单下会有一个任务列表的选项，我们打开这是视图，可以很方便的管理我们做出的//todo标记，跟书签一样，可以帮助我们快速定位。
>https://blog.csdn.net/buaazyp/article/details/80068818
在代码的后面添加形如下面注释：

```cs
//TODO: (未实现）……

//UNDONE:（没有做完）……

//HACK：（修改）……

```

等到再次打开VS的时候，找到 ：视图>任务列表

即可显示所有带有TODO注释的代码位置。



方便项目管理者，对代码的编写更加的灵活，节省了不少时间。
>https://blog.csdn.net/guo13313/article/details/51228515
## TODO 高亮
在VS2005 中, 默认注释中的TODO并没有高亮

想要设置TODO高亮需要在VS中安装 `TODO HIGHLIGHT` 插件
>https://blog.csdn.net/dietime1943/article/details/79658088