---
title: 导航系统Navigation
tags: Unity,Navigation
grammar_cjkRuby: true
---
# 设置Navigation的烘焙对象并烘焙
选中所有待烘焙的对象，然后在Inspector面板上勾选`Static`，实际上只需要勾选 **Navigation Static**

<left>![选择烘焙对象.png](https://i.loli.net/2018/10/17/5bc6f27204b0a.png)</left><right>![Bake一下](https://i.loli.net/2018/10/17/5bc6f37b925b3.png)<right>

# 自定义物体对象是否为可行走
选中对象，然后**Object** → 勾选**Navigation Static** → **Navigation Area**  ？Walkable ：Not Walkable
如图：

![设置对象是否为可行走](https://i.loli.net/2018/10/17/5bc6f59e5a2e6.png)
最后再Bake一下。

# 烘焙的是物体对象的MeshRender组件
如果一个被烘焙的物体的区域不规则，不正常，或者在Navigation下的Object那就把该物体在Hierarchy上展开其子物体，找到含有Mesh Render组件的那个物体，然后再在Navigation 下的Object选项卡下勾选Navigation Static 然后就能够重新设置该物体的烘焙区域了。最后重新烘焙一次即可。