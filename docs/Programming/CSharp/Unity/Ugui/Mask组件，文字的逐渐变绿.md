---
title: Mask组件，文字的逐渐变绿
tags: Unity,Mask
grammar_cjkRuby: true
---
![如图](https://i.loli.net/2019/01/20/5c43fc748b38f.jpg)

条件：文本下挂多个图片物体。
每个图片组件所在的物体上把颜色修改为想要的颜色
图片组件所在的Row*都可以不挂Mask组件物体

图片组件的Image的Material与Text组件的Material必须保持一致。要么都为None，要么都为UIOverLayer

总结：
如果头晕：
Text组件与子物体的Image，都挂上Mask，都不设置Material。
