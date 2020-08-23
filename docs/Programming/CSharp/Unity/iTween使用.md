---
title: iTween使用
tags: iTween
---
[toc!]

## 上下不停的弹跳

```csharp?linenums
/****************************************************
    文件：Doodle.cs
	作者：Ivy
    邮箱: bcaso@qq.com
    日期：2019/05/02 20:12
	功能：上下不停的弹跳，利用iTween插件(免费的，仅一个脚本，从资源商店中导入)
    课程：涂鸦跳跳DoodleJump
	地址：http://www.sikiedu.com/course/252/task/11581/show
*****************************************************/

using UnityEngine;

public class Doodle : MonoBehaviour {
	//y轴偏移
	public float offsetY = 10;
	//动画的时长
	public float time    = 0.5f;

	private void Start() {
		iTween.MoveBy(gameObject, iTween.Hash(
		                                      "y", offsetY,
		                                      "easeType", iTween.EaseType.easeInOutQuad, //正弦曲线，先快后慢
		                                      "loopType", iTween.LoopType.pingPong,      //来回
		                                      "time", time
		                                     ));
	}
}
```

## 暂停动画事件
```csharp?linenums
public void Pause(){
    iTween.Stop(gameObject);//把当前物体身上的动画事件都删除
    iTween.Stop();//把所有物体身上的动画事件都删除
}
```