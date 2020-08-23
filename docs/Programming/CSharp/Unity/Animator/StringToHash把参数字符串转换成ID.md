---
title: StringToHash把参数字符串转换成ID
tags: Unity,Animator,Function
grammar_cjkRuby: true
---
# 函数原型

## Animator.SetFloat//SetInt等其他set类似

public void SetFloat(string name, float value);
public void SetFloat(string name, float value, float dampTime, float deltaTime);
public void SetFloat(int id, float value);
public void SetFloat(int id, float value, float dampTime, float deltaTime);
# StringToHash
`public static int StringToHash(string name);`

Generates an parameter id from a string. 
从字符串生成一个参数ID。 
Ids are used for optimized setters and getters on parameters. 
ID是用于参数的存取器优化（setters 和 getters）。
当使用Animator时，如果要引用某个状态或者参数，有两种方法。 

1：通过字符串名称 
2：通过整数“Hash ID” 
通过“Hash ID”更有优势，因为不容易出错，且更加高效。将名称转换为哈希值可以提高索引的速度。
两种的使用方式不同。animation状态或者parameters的字符串(Tag)需要通过对象使用；但是“Hash ID”不需要，他是**Animator的静态方法**。



例如：官方案例–Stealth中
```csharp
using UnityEngine;
public class DoneHashIDs : MonoBehaviour{
    // Here we store the hash tags for various strings used in our animators.
    public int dyingState;
    public int locomotionState;
    public int shoutState;
    public int deadBool;
    public int speedFloat;
    public int sneakingBool;
    public int shoutingBool;
    public int playerInSightBool;
    public int shotFloat;
    public int aimWeightFloat;
    public int angularSpeedFloat;
    public int openBool;

    public Animator anim;
    void Awake ()
    {
        dyingState = Animator.StringToHash("Base Layer.Dying");
        locomotionState = Animator.StringToHash("Base Layer.Locomotion");
        shoutState = Animator.StringToHash("Shouting.Shout");
        deadBool = Animator.StringToHash("Dead");
        speedFloat = Animator.StringToHash("Speed");
        sneakingBool = Animator.StringToHash("Sneaking");
        shoutingBool = Animator.StringToHash("Shouting");
        playerInSightBool = Animator.StringToHash("PlayerInSight");
        shotFloat = Animator.StringToHash("Shot");
        aimWeightFloat = Animator.StringToHash("AimWeight");
        angularSpeedFloat = Animator.StringToHash("AngularSpeed");
        openBool = Animator.StringToHash("Open");
    }
    void Start(){
        anim = GetComponent<Animator>();
    }
    void Update(){
        //使用上
        //一般使用
        anim.SetFloat("Shot", 1.2f);
        //使用id值，AnimatorID，第一个参数
        anim.SetFloat(shotFloat, 1.2f);//因为这个变量一但写错，编译就不能通过，一定程度上比上面写法更加靠谱。
        
        //上面都是给变量设置一个值
        //下面是如何得到值
        if(anim.GetFloat(shotFloat) > 3){//参数还是id，也可以写为字符串包含的变量名
            //Do something here...
        }
        
    }
}
```