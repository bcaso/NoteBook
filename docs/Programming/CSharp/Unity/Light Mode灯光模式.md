---
title: Light Mode灯光模式
tags: Unity,Light
grammar_cjkRuby: true
---
## Realtime 实时更新
这种较费性能
## Baked 烘焙的
节省系统性能
使用上：
* **Window** → **Lighting** → **Settings** 取消勾选最后的**Auto Generate**,有利于在开发中节省性能
* 把灯光照射到的所有物体都勾选为**Static**
* 把所有灯光都选中，修改Shadow Type,为soft shadows或者hard shadows,在烘焙过后，灯光选用烘焙模式，这两种占用资源都是一样的。
* 选中所有灯光，然后将Light下的Mode修改为**Baked**,然后进行烘培→**Window** → **Lighting** → **Settings** → **Generate Lighting**（手动灯光烘培）


## Mixed 混合的(Realtime + Baked)
常用于火光，因为火光是闪动的。
