---
title: 状态机的切换状态 if(anim.IsInTransition(0)){...}
tags: Unity,Animator,Fuction
grammar_cjkRuby: true
---
例：开关门时，播放音效
要及时播放音效，就是在开关门（动画转换期间）播放音效
![动画状态机](https://i.loli.net/2018/11/23/5bf767d010924.jpg)
# 动画切换状态
所谓的动画切换状态就是上图中的两条转换线。在转换线期间的状态就是状态机处于切换状态，默认是第0层
代码：
```csharp?linenums
using UnityEngine;
using System.Collections;

public class doorController : MonoBehaviour {
    private Animator anim;
    private AudioSource _audio;
    private AudioClip doorOpenClip;
    private int isClosedID = Animator.StringToHash("isClosed");    
	void Start () {
        anim = GetComponent<Animator>();
        _audio = GetComponent<AudioSource>();
        doorOpenClip = Resources.Load<AudioClip>("Audio/door_open");
        _audio.clip = doorOpenClip;
	}

	void Update () {
        if (anim.IsInTransition(0))
            if (!_audio.isPlaying) _audio.Play();
    }
    void OnTriggerEnter(Collider other) {
        if (other.tag == Tags.player && anim.GetBool(isClosedID)) {
            anim.SetBool(isClosedID, false);
        } else anim.SetBool(isClosedID, true);
    }
    void OnTriggerExit(Collider other) {
        if (other.tag == Tags.player) { 
            anim.SetBool(isClosedID, true);
        }
    }
}
```
关于这个函数的使用，我感觉放在Update中比较好，我也把这个函数放在了TriggerEnter中使用，结果发现音效有时播放有时不播放。
放在Update中就可以及时检测出动画的切换状态，但同时损失了一点性能。