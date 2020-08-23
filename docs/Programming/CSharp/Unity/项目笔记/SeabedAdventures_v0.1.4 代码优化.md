---
title: SeabedAdventures_v0.1.4 代码优化
tags: Unity
grammar_cjkRuby: true
---
按钮的凝视时与不再凝视时的图片变化具体逻辑在父类中实现，子类调用父类的方法。
增加了qTimer类。
定时器功能。可在一定程度上替换协程。
&emsp;&emsp;该类也是用协程实现的。