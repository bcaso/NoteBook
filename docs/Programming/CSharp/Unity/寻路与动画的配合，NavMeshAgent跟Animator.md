---
title: 寻路配合动画
tags: Unity,Navigation,Animator
grammar_cjkRuby: true
---
# 动画状态机的配置
![待上传.png](https://i.loli.net/2018/10/18/5bc8a3312fccc.png)

# 代码
```csharp?linenums
using UnityEngine;
using UnityEngine.AI;

public class Move : MonoBehaviour {
    public NavMeshAgent agent;
    public Animator anim;
	
	void Update () {
        if (Input.GetMouseButtonDown(0)) {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            bool isHit = Physics.Raycast(ray,out hit);
            if (isHit) {
                agent.SetDestination(hit.point);
            }
        }
        anim.SetFloat("speed", agent.velocity.magnitude);
	}
}
```
# 注意
动画的转换条件是NavMeshAgent组件下的Speed。
但是在使用时，不是写为：
```csharp
anim.SetFloat("speed", agent.speed/*这个speed就是小写*/);
```
而是写为：
```csharp
anim.SetFloat("speed", agent.velocity.magnitude);
```
原因可能是因为agent.speed这个值是固定的。一但改变，就固定了。

![条件参数speed](https://i.loli.net/2018/10/18/5bc8a5ad589cb.png)