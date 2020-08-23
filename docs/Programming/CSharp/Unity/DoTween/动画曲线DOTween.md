---
title: 动画曲线DOTween
tags: Unity,DOTween,Component
grammar_cjkRuby: true
---
DOMove的返回值是一个Tweener类型的动画,根据这个动画，来设置这个动画的属性，如动画曲线，动画循环播放次数，完成执行事件

```csharp
using UnityEngine;
using DG.Tweening;
public class MyPanel:MonoBehaviour{
    void Start(){
        Tween tweener = transform.DOLocalMoveX(0, 5);//把一个图片移动到屏幕中央，ui的移动最好使用DOLocalMove,本地坐标。为什么屏幕中间的坐标是0，0，0，不知道
        tweener.SetEase(Ease.OutBounce);//Ease是个枚举类型的变量，OutBouncd是弹性滚动，当运动到目标位置，就像是弹球掉落到地上，会进行弹动。如果是Liner,线性的，就是平均变化。
        tweener.SetLoops(3);//动画循环播放3次，参数如果数0，也是播放1次。
        tween.OnComplete(OnTweenComplete);
    }
    void OnTweenComplete(){
        Debug.Log("动画播放完成了。。这个是OnComplete事件绑定的方法");
    }
}
```