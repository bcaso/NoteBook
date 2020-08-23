---
title: Mathf.Clamp
tags: Unity,Function
grammar_cjkRuby: true
---
将一个变量的值控制在某个范围内。
```csharp
public static float Clamp(float value, float min, float max);
```
value是这个变量，
如果value < min, value = min;
如果value > max, value = max;
如果value > min && value < max，value = value;
例：
```csharp
private int hp = 100;
void TakeDamage(){
    hp -= 9;
    hp = Mathf.Clamp(hp, 0, 100);
}
```
这样玩家的血量就会处于一个正常的范围内了。