---
title: Unity性能测试之Time.realtimeSinceStartup
tags: Unity,Function
grammar_cjkRuby: true
---

```csharp?linenums
void Start(){
    float time1 = Time.realtimeSinceStartup;
    for(int i = 0; i < runCount; i++){
        Method1();
    }
    float time2 = Time.realtimeSinceStartup;
    Debug.Log(time2 - time1);//单位是秒，这里输出的是这个Method1()执行runCout次所耗费的时间

    float time3 = Time.realtimeSinceStartup;
    for(int i = 0; i < runCount; i++){
        Method2();
    }
    float time4 = Time.realtimeSinceStartup;
    Debug.Log(time4 - time3);//单位是秒，这里输出的是这个Method2()执行runCount次所耗费的时间

    //两个时间做对比就能知道Method1()与Method2()哪个更耗费性能。
}
```
由于是性能测试，把上面的代码放在Start()中执行一次即可。