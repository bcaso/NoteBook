---
title: Unity人物漫游
tags: Unity,Algorithm
grammar_cjkRuby: true
---
# 具体思路:  

1.  测试环境下,在回调方法 `void OnDrawGizmos(){ }`中绘制出坦克要走的路线

2. 通过更改下一个路径点, 并判断它与下一个目标点的距离以及是否继续行走或循环行走, 来实现物体的漫游

## Path.cs
创建一个空物体改名为"Path",将其位置reset,  并在其身上挂载"Path"脚本. "Path"脚本用来绘制坦克要走的路线.
<u>注意: 划线调试结合`bool`值`IsDebug`使用是在开发中常用的一种调试方法</u>
<img src = "https://i.loli.net/2018/12/09/5c0c99f897498.jpg" title = "Path的Inspector面板" alt = "Path的Inspector面板" />
```csharp?linenums
/*
 * Author WD
 */
using UnityEngine;

public class Path : MonoBehaviour {
    //是否是调试模式
    public bool isDebug = true;
    //存放所有的路径点
    public Transform[] pointA;
    //规划路径上的点的总数
    public int Length {
        get { return pointA.Length; }
    }

    /// <summary>
    /// 根据下标获取路径上的某个点
    /// </summary>
    /// <param name="index">路径点下标</param>
    /// <returns>index所在的路径点</returns>
    public Vector3 GetPointAtIndex(int index) {
        return pointA[index].position;
    }
    void OnDrawGizmos() {
        if (!isDebug) return;
        //循环所有的路径点进行绘制路线
        for (int i = 0; i < pointA.Length - 1; i++) {
            Debug.DrawLine(pointA[i].position, pointA[i + 1].position, Color.red);
            Debug.Log(i);
        }
    }
}
```
### 效果图 
![](https://i.niupic.com/images/2018/12/09/5B7u.png)
## Enemy.cs
在Enemy身上创建并挂载"Enemy"脚本. 用来按照"Path"脚本中的路线行走.
```csharp?linenums
/*
 * Author WD
 */
using UnityEngine;
public class Enemy : MonoBehaviour {
    //脚本
    private Path path;
    //是否循环
    public bool IsLoop = true;
    //速度
    public float Speed = 20.0f;
    //当前敌人所在路径点的下标
    private int curPathIndex;

    //下一个路径点
    private Vector3 nextTargetPoint;
    void Start() {
        //获取脚本组件
        path = GameObject.FindWithTag(Tags.Path).GetComponent<Path>();
        curPathIndex = 0;
    }

    void Update() {
        //获取下一个路径点
        nextTargetPoint = path.GetPointAtIndex(curPathIndex);//第一次给下一个路径点时给的是第0个路径点,（满足<0.5f）. 也是为了避免数组越界

        //判断敌人当前的位置与下一路径点的位置是否小于一个值
        if (Vector3.Distance(transform.position, nextTargetPoint) < 0.5f) {
            //判断敌人行走的下一个路径点
            if (curPathIndex < path.Length - 1) {
                curPathIndex++;
            } else if (IsLoop) {//此时 curPathIndex == path.Length -1 也就是说到达了最后一个路径点
                curPathIndex = 0;//如果循环为真，则下一步向起始点移动
            } else return;//如果到达了终点，还不循环，就停止移动。
        }
        //下一路径点的方向
        Vector3 dir = nextTargetPoint - transform.position;
        //移动旋转
        //transform.position += transform.forward * Speed * Time.deltaTime;
        transform.Translate(Vector3.forward * Speed * Time.deltaTime);
        transform.rotation = Quaternion.LookRotation(dir);
    }
}
```
## Tags.cs
存放所有tag值
```csharp
/*
 * Author WD
 */
using UnityEngine;

public class Tags : MonoBehaviour {
    public const string Path = "Path";
}
```