---
title: Mathf.MoveTowards
tags: Unity,Function
grammar_cjkRuby: true
---
```csharp
void Update(){
    float x = cube.position.x;
    float newX = Mathf.MoveTowards(x, 10, Time.deltaTime * speed);
    cube.position = new Vector3(newX, 0, 0);
}
```
speed的单位是米/秒
Mathf.MoveTowards(a, b, t);
return a + t;//(a + t) < b