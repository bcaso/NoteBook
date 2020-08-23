---
title: ScrollRect滚动
tags: Unity,UGUI,Component
grammar_cjkRuby: true
---

![组件如图](http://p75k5ihmt.bkt.clouddn.com/18-11-8/13370351.jpg)
ScrollRect组件可以控制物体的滚动，可以不指定滚动条组件。

# 属性解释
Horizontal && Vertical 表示能够向哪个方向拖拽

## Movement Type 滚动类型
Elastic 表示弹性滚动，就是鼠标拖拽结束松开的时候的效果。

# 鼠标的拖拽接口
IBeginDragHandler,IEndDragHandler
通过实现这两个接口

# 代码：
```csharp?linenums
using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class LevelButtonScrollRect : MonoBehaviour ,IBeginDragHandler,IEndDragHandler
{
    private ScrollRect scrollRect;

    public float smoothing = 4;
    private float[] pageArray=new float[]{ 0,0.33333f,0.66666f,1 };
    public Toggle[] toggleArray;
    private float targetHorizontalPosition=0;
    private bool isDraging = false;
	// Use this for initialization
	void Start ()
	{
	    scrollRect = GetComponent<ScrollRect>();
	}
	
	// Update is called once per frame
	void Update ()
	{
        if(isDraging==false)
	        scrollRect.horizontalNormalizedPosition = Mathf.Lerp(scrollRect.horizontalNormalizedPosition,
	            targetHorizontalPosition, Time.deltaTime*smoothing);
	}


    public void OnBeginDrag(PointerEventData eventData)
    {
        isDraging = true;
    }

    public void OnEndDrag(PointerEventData eventData)
    {
        isDraging = false;
        float posX = scrollRect.horizontalNormalizedPosition;
        int index = 0;
        float offset = Mathf.Abs(pageArray[index] - posX);
        for (int i = 1; i < pageArray.Length; i++)
        {
            float offsetTemp = Mathf.Abs(pageArray[i] - posX);
            if (offsetTemp < offset)
            {
                index = i;
                offset = offsetTemp;
            }
        }
        targetHorizontalPosition = pageArray[index];
        toggleArray[index].isOn = true;
        //scrollRect.horizontalNormalizedPosition = pageArray[index];
    }

    public void MoveToPage1(bool isOn) {
        if (isOn)
        {
            targetHorizontalPosition = pageArray[0];
        }
    }
    public void MoveToPage2(bool isOn) {
        if (isOn) {
            targetHorizontalPosition = pageArray[1];
        }

    }
    public void MoveToPage3(bool isOn) {
        if (isOn)
        {
            targetHorizontalPosition = pageArray[2];
        }

    }
    public void MoveToPage4(bool isOn) {

        if (isOn)
        {
            targetHorizontalPosition = pageArray[3];
        }
    }
}
```