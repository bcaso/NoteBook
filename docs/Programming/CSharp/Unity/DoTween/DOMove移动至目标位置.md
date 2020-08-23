---
title: DOMove移动值目标位置
tags: Unity,DoTween,Component,Function
grammar_cjkRuby: true
---
```csharp
using UnityEngine;
using DG.Tweening;

public class MyButton:MonoBehaviour{
    public RectTransform panelTransform;

    //按钮点击事件所绑定的方法
    public void OnClick(){
        panelTransform.DOMove(new Vector3(0, 0, 0), 1);//让panelTransform从当前位置动画到0，0，0的位置，时间为1秒
    }
}
```