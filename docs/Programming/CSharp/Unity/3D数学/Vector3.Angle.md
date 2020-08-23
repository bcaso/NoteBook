---
title: Vector3.Angle
tags: Unity,Vector3,3D数学
grammar_cjkRuby: true
---
`public static float Angle(Vector3 from, Vector3 to);`
返回一个float 类型的值，表示角度大小。
例：判断一个敌人是否能看到玩家
假设敌人的视野范围是120⁰，那么一半也就是60度。
判断敌人是否能够看到玩家，只需要判断敌人的正前方，与敌人指向玩家的向量的方向的夹角是否小于60⁰。
假设敌人是O，玩家是P，那么敌人指向玩家的向量即向量`!$\overrightarrow {OP}$`

![夹角](https://i.loli.net/2018/11/27/5bfcce1371277.jpg)
```csharp?linenums
using UnityEngine;
using System.Collections;

public class EnemyInSight : MonoBehaviour {
    public bool isPlayerInSight = false;
    private Transform player;
    private Vector3 playerDir;//玩家的方位
    public float fieldOfView = 130.0f;//视野范围 130度角
    void Start() {
        player = GameObject.FindWithTag(Tags.player).transform;
    }
    void OnTriggerStay(Collider other) {
        if (other.tag == Tags.player) {
            playerDir = player.transform.position - transform.position;
            float angle = Vector3.Angle(transform.forward, playerDir);
            if (angle < 0.5f * fieldOfView) {
                isPlayerInSight = true;
            } else isPlayerInSight = false;
        }
    }
    void OnTriggerExit(Collider other) {
        if (other.tag == Tags.player) isPlayerInSight = false;
    }
}
```