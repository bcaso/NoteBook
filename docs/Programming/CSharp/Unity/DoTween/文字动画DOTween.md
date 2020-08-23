---
title: 文字动画DOTween
tags: Unity,DOTween,Component,Function
grammar_cjkRuby: true
---
```csharp
using UnityEngine;
using DG.Tweening;
using UnityEngine.UI;

public class MyText:MonoBehaviour{
    private Text text;//在start中获取，比在update中用GetComponent<Text>()要节省性能。
    void Start(){
        text = this.GetComponent<Text>();
        text.DOText("你现在看到的是使用DOTween中的DOText方法显示的打字机效果的文本显示",6);//第一个参数是文本内容，第二个参数是时间。6秒以打字机效果把文字显示出来。如果Text组件的内容不是空的，那么则会一个字一个字的覆盖掉原来的文本。
    }
}
```