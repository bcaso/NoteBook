---
title: Hieriarchy搜索技巧
tags: Unity,Animator,MeshRender,UnityEditor
grammar_cjkRuby: true
---
# 人物贴图
人物的贴图都是由meshrender，skinmeshrender来控制的
如果一个人物的贴图不正确，需要手动导入。
那么，就应该在`Hieriarchy`面板中搜索`t:meshrender` || `t:skinmeshrender`找到所有的需要设置贴图的部位