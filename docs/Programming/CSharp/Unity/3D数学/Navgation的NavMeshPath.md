---
title: Navgation的NavMeshPath
tags: Navigation
grammar_cjkRuby: true
---
例：判断敌人能否听到玩家的走路声（玩家走路有正常走路跟慢走Sneak的两种状态，慢走时没有脚步声）
给敌人一个检测范围，SphereColider Trigger,要足够大。
敌人通过寻路组件控制。
```csharp?linenums
using UnityEngine;
using System.Collections;

public class EnemySight : MonoBehaviour {

    public bool playerInSight = false;
    public float fieldOfView = 110;
    public Vector3 alertPosition = Vector3.zero;

    private SphereCollider collider;
    private Animator playerAnim;
    private NavMeshAgent navAgent;
    private Vector3 preLastPlayerPosition = Vector3.zero;

    void Awake() {
        playerAnim = GameObject.FindGameObjectWithTag(Tags.player).GetComponent<Animator>();
        navAgent = this.GetComponent<NavMeshAgent>();
        collider = this.GetComponent<SphereCollider>();
    }
    void Start() {
        preLastPlayerPosition = GameController._instance.lastPlayerPostion;
    }

    void Update() {

        if (GameController._instance.lastPlayerPostion != preLastPlayerPosition) {
            alertPosition = GameController._instance.lastPlayerPostion;

            preLastPlayerPosition = GameController._instance.lastPlayerPostion;
        }
    }

    public void OnTriggerStay(Collider other) {
        if (other.tag == Tags.player) {
            Vector3 forward = transform.forward;
            Vector3 playerDir = other.transform.position - transform.position;
            float temp =  Vector3.Angle(forward, playerDir);
            RaycastHit hitInfo;
            bool res =  Physics.Raycast(transform.position + Vector3.up, other.transform.position - transform.position, out hitInfo);
            if (temp < 0.5f * fieldOfView && ( res==false  ||hitInfo.collider.tag==Tags.player  ) ) {
                playerInSight = true;
                alertPosition = other.transform.position;
                GameController._instance.SeePlayer(other.transform);
            } else {
                playerInSight = false;
            }

            if (playerAnim.GetCurrentAnimatorStateInfo(0).IsName("Locomotion")) {
                NavMeshPath path = new NavMeshPath();
                if( navAgent.CalculatePath(other.transform.position, path )){
                    Vector3[] wayPoints = new Vector3[path.corners.Length + 2];
                    wayPoints[0] = transform.position;
                    wayPoints[wayPoints.Length - 1] = other.transform.position;
                    for (int i = 0; i < path.corners.Length; i++) {
                        wayPoints[i + 1] = path.corners[i];
                    }
                    float length = 0;
                    for (int i = 1; i < wayPoints.Length; i++) {
                        length += (wayPoints[i] - wayPoints[i - 1]).magnitude;
                    }
                    if (length < collider.radius) {
                        alertPosition = other.transform.position;
                    }
                }
            }

        }
    }
    public void OnTriggerExit(Collider other) {
        if (other.tag == Tags.player) {
            playerInSight = false;
        }
    }

}
```
>stealth秘密行动第30讲
2018年11月27日 星期二 19:09 既没听懂也没看懂。。。。。。。