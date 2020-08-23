---
title: DOLocalMove移动至目标位置
tags: Unity,DoTween,Component,Function
grammar_cjkRuby: true
---
```csharp
using UnityEngine;
using DG.Tweening;

public class MyButton:MonoBehaviour{
    public RectTransform panelTransform;
    
    public void OnClick(){
        panelTransform.DOLocalMove(new Vector(0, 0, 0), 1);//把当前位置移动移动至0,0,0的位置，时间为1秒。使用的是本地坐标。推荐使用这个方法代替DOMove，如果没有特殊需求的话，就用这个方法。  最后一个时间参数是float类型。
    }
}
```