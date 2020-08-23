---
title: Random 随机数
tags: Unity,Function
grammar_cjkRuby: true
---
```csharp
void Start(){
    Random.InitState((int)System.DateTime.Now.Ticks);//这行不调用也行，Unity自身能保证每次随机出的数值不同。
}
void Update(){
    if(Input.GetKeyDown(KeyCode.Space)){
        Debug.Log(Random.Range(4, 100));
    }
]
```
这样，每次运行代码时，产生的数值就会不同了。