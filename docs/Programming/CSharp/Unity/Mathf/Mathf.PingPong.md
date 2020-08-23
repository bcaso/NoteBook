---
title: Mathf.PingPong
tags: 新建,模板,小书匠
grammar_cjkRuby: true
---
public static float **PingPong**(float **t**, float **length**);
让数值t在 0到length之间往返。t值永远不会大于length的值，也永远不会小于0。
t 就是运动速度
且不能设置最小值，默认最小值是0。
## 物体颜色闪烁
任何能显示在场景中的物体上都有MeshRenderer这个组件.
通过插值运算改变物体的颜色:
在Inspector赋予两个插值颜色.
![](http://p75k5ihmt.bkt.clouddn.com/18-5-25/45397258.jpg)
>注: 当材质球错误不合适时,是不能产生效果的. 可直接新建个Cube来测试代码;
```cs
using UnityEngine;

public class changeColor : MonoBehaviour {

    private Color tempColor;
    public Color StartColor;
    public Color EndColor;

    private Material mat;

    public bool isFlash;

    private void Awake() {
        this.mat = this.GetComponent<MeshRenderer>().material;
        this.StartFlashing();
    }

    public void StartFlashing() {
        this.isFlash = true;
    }
    public void StopFlashing() {
        this.isFlash = false;
    }

    void Update() {
        if (this.isFlash) {
            this.tempColor = Color.Lerp(this.StartColor, this.EndColor, Mathf.PingPong(Time.time, 1f));
            this.mat.color = this.tempColor;        // 完全没必要写这个tempColor,直接等于即可...
        }    
    }
}
```