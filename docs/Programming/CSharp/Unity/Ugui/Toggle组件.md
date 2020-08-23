---
title: Toggle组件
tags: Unity,UGUI,Toggle
grammar_cjkRuby: true
---
挂有Toggle组件的OnValueChagne所调用的方法：
```csharp
public void Selected(bool isOn){
    if(isOn){
        //Do something here...
    }
}
```
这个方法中的isOn就是Toggle组件下的isOn属性，当Toggle组件被点击时，值就改变，就会调用`Selected`这个方法，那么其isOn属性也就会被传入到这个方法中，赋值给isOn。