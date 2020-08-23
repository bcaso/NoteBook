---
title: Mathf.Lerp
tags: Unity,Mathf,Function
grammar_cjkRuby: true
---
current = Mathf.Lerp(current, target, float t);
current 是当前值,
target 是目标值
t是百分比，值为0~1间
current 向 target 值增加t%

current - target 这段距离的t%

## 用于控制物体的移动
但是永远也到达不了目标值，运动速度会越来越慢
```csharp
void Update(){
    float x = cube.position.x;
    cube.position = new Vector(Mathf.Lerp(x, 10, Time.deltaTime * speed),0,0);
}
```