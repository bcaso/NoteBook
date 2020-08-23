---
title: Foreach遍历一个物体的所有子物体
tags: Unity,Function
grammar_cjkRuby: true
---
```csharp
public GameObject bgImage;
foreach(Transform t in bgImage.gameObject.transform){
    t.gameObject.GetComponent<Image>().enabled = false;
}
```
上面中foreach的作用是遍历bgImge下所有子物体，并得到子物体的Image组件，然后禁用。