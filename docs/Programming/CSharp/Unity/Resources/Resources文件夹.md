---
title: Resources文件夹
tags: Unity,Resources
grammar_cjkRuby: true
---
这个文件夹可以在资源目录中的任意一处，可以是根目录，可以是某个文件夹的子目录。
```csharp
Resources.Load(string path);
```
这个方法的加载资源，path的书写不需要加`Resources/`以及文件扩展名，如果有多个重名文件的话。使用下面这个**泛型**方法：

```csharp
this.GetComponent<Image>().sprite = Resources.Load<Sprite>("78");
  this.GetComponent<SpriteRenderer>().sprite = Resources.Load<Sprite>("78");
```
## 游戏物体的动态加载

```csharp
//把资源加载到内存中
GameObject vrgiftsall = Resources.Load("Prefab/VR/biggiftsvr")as GameObject;
//用加载得到的资源对象，实例化游戏对象，实现游戏物体的动态加载
 GameObject biggiftvrload = Instantiate (vrgiftsall) as GameObject;
```
上述代码中biggiftsvr是放在下路径为Resources/Prefab/VR的一个物体，随便定义个GameObject用来加载过来，然后再实例化为biggiftvrload ，所以你要使用的真正的GameObject是biggiftvrload 。

原文：https://blog.csdn.net/alayeshi/article/details/51093624 

# 2d图片集

![图集](https://i.loli.net/2019/02/14/5c658b496fe28.jpg)
如图，如果要使用`UI_2`这个图片资源。
有两种方法，一是定义一个`public Sprite sprite;`在Inspector中拖拽该图片。
另一种是用`Resources.LoadAll<>`
```csharp
private Sprite[] _ui1;//从Resources加载图集
private Sprite _sprite;//要使用的Sprite

void Start(){
    _ui1 = Resources.LoadAll<Sprite>("UI");
    _sprite = _ui1[2];//得到对应Sprite
}
```

