---
title: Mathf.Max / Min
tags: Unity,Mathf,Function
grammar_cjkRuby: true
---
返回两个或多个值中的最大/最小值
public static float Max(float a, float b);
public static float Max(params float[] values);
Min同上
```csharp
Debug.Log(Mathf.Max(1.2, 2.4, 3.8, 5.6));//prints 5.6
Debug.Log(Mathf.Min(33,12,35,123,989,32,32,11.01f));//prints 11.01
```