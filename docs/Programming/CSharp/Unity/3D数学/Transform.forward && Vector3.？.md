---
title: Transform.forword && Vector3.*
tags: Unity,Transform,3D数学
grammar_cjkRuby: true
---
Transfrom.Translate();

# transform.forward
## 物体会 朝者 （Space.* + 自身旋转的角度） 进行移动

## Space.Self
```csharp
void Update(){
    transform.Translate(Transform.forward * Time.deltaTime, Space.Self);
}
```
物体会朝着自身坐标系（物体坐标系，模型坐标系，本地坐标系）的z轴进行移动。
如果物体自身绕y轴旋转20度，那么物体就会朝着 自身坐标系的z轴 + 20度 的方向进行移动。

## Space.World
```csharp
void Update(){
    transform.Translate(Transform.forward * Time.deltaTime, Space.World);
}
```
物体会朝着世界坐标系（全局坐标系）的z轴进行移动
如果物体自身绕y轴旋转20度，那么物体就会朝着 世界坐标系的z轴 + 20度的方向进行移动。

# Vector3.forward Vector3.right Vector3.up
## 物体会朝着 Sapce.* 的z轴进行移动，不考虑物体自身的旋转
```csharp?linenums
void Update(){
    /*  Vector3.forward Vector3.right Vector3.up
     *  根据 Space.* 的z轴进行移动，不考虑物体自身的旋转角度
     */
    //transform.Translate(Vector3.forward * Time.deltaTime, Space.Self);//朝着自身方向的z轴进行移动
    //transform.Translate(Vector3.forward * Time.deltaTime, Space.World);//朝着世界坐标方向的z轴进行移动

    //transform.Translate(Vector3.right * Time.deltaTime, Space.Self);//朝着 自身坐标系的x轴正方向进行移动
    //transform.Translate(Vector3.right * Time.deltaTime, Space.World);//朝着 世界坐标系的x轴正方向进行移动

    //transform.Translate(Vector3.up * Time.deltaTime, Space.Self);//朝着 自身坐标系的y轴正方向进行移动
    //transform.Translate(Vector3.up * Time.deltaTime, Space.World);//朝着 世界坐标系的y轴正方向进行移动
}
```