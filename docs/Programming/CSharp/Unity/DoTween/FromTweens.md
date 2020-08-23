---
title: FromTweens
tags: Unity,DoTween,Component,Function
grammar_cjkRuby: true
---
# transform.DOMoveX();
transform.DOMoveY()
transform.DOMoveZ()
目标，时间
例：
```csharp
using UnityEngine;
using DG.Tweening;
public class MyCube:MonoBehaviour{
    void Start(){
        transform.DOMove(5,1);//把当前物体的位置的x坐标移动至5，时间为1秒。
    }
}
```
# transform.DOMoveX.From();
from动画，加上From()方法后，就表示从目标位置移动到当前位置
```csharp
using UnityEngine;
using DG.Tweening;
public class MyCube:MonoBehaviour{
    void Start(){
        transform.DOMove(5,1).From();//从x坐标为5的位置移动到当前位置
    }
}
```
# transform.DOMoveX.From(true);
加上true后表示，从目标位置移动到当前坐标，。但此时的目标坐标是个相对坐标。
如果当前物体的x坐标为1
那么使用
```csharp
transform.DOMoveX(5, 1).From(true);
```
就是把当前物体从x为6移动到x为1.
当From(true)时，目标值=目标值+当前值