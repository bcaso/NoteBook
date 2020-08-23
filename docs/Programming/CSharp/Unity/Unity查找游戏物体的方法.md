---
title: Unity查找游戏物体的方法
tags: Unity,GameObject
grammar_cjkRuby: true
---
## GameObject.Find(string str);
1.可以使用路径查找，也可以不使用。

使用路径查找一般可以解决重名问题，但是如果该物体的路径变动，那么代码也需调整。

2.如果要查找的物体是隐藏的物体，或者该物体任何一个祖先物体是隐藏的，那么就无法查找这个物体。

3.该方法为遍历场景中的所有游戏物体来进行查找，使用效率低，不能放在Update中执行。


## Transform.Find(string str);
1.同样支持路径查找

2.查找隐藏对象的前提是transform所在的根节点必须可见，即active=true
例：
```csharp
Transform[] ts = FindObjectsOfType<Transform>();//不查找未激活的物体，这个是查找所有游戏场景中的物体
foreach(Transform t in ts){
    Debug.log(t.name);
}
```

## Transform.parent(string str);
3：查找父物体：Transform.parent

Gameobject.FindGameObjectWithTag(Tags.player);
## 通过标签查找的方法
GameObject.FindWithTag()
GameObject.FindGameObjectsWithTag()

Transform player = GameObject.FindGameObjectWithTag(Tags.player).transform;
### 标签类
public const string 变量名 = "标签名";
```csharp
    public const string player = "Player";
    public const string playerHp = "playerHp";
    public const string enemy = "Enemy";
    //...
```

## 5：  LookAt方法：
朝向某物体：Transform组件下还有lookat方法，public Transform target;，transform.LookAt(target);在面板中选择要看向的物体，摄像机看向物体就可以用这个。

个人建议优先使用顺序：

Transform.Find() > GameObject.FindWithTag() > GameObject.Find()

# 返回值
当使用Transform.Find()/GameObject.Find()方法时，如果找不到所要的物体，这个方法就会返回null
所以我猜想，可以用这个来判断游戏中是否存在某个游戏物体。