---
title: Unity各种[]属性
tags: Unity,Inspector
grammar_cjkRuby: true
---
# 提示
`[Space]` 
`[Space (int num)]`
　　可以与上面形成一个空隙，可以带参数[Space(30)] 
`[Header("XXX")]`
　　在Inspector面板上给定义的字段的上一行加段描述，可以将属性隔离开，形成分组的感觉 
`[Tooltip(“XXX”)]`
　　在Inspector面板上鼠标移上定义的字段弹出描述 

# 序列化
`[SerializeField]`
　　在Inspector版面中显示非public属性，并且序列化 
`[NonSerialized]`
　　在Inspector版面中隐藏public属性，不执行序列化 
`[HideInInspector]`
　　使属性在Inspector中隐藏，但是还是可序列化，想赋值可以通过写程序赋值序列化 
`[System.Serializable]`
　　使自定义的类能进行序列化，即当做一个public成员的时候可以在Inspector显示 
`[FormerlySerializedAs(“XXX”)]`
　　该属性可以令变量以另外的名称进行序列化，并且在变量自身修改名称的时候，不会丢失之前的序列化的值 

# 限制变量范围
`[Range(min, max)]`
　　限制数值变量的取值范围并以滑动条显示在Inspector中 

# More
https://blog.csdn.net/FifthGently/article/details/78363364
https://blog.csdn.net/WarrenMondeville/article/details/53296958