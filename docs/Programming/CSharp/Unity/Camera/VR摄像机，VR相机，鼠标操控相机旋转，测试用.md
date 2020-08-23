---
title: VR摄像机，VR相机，鼠标操控相机旋转，测试用
tags: VR,Unity,Camera
grammar_cjkRuby: true
---
>仅测试时使用, 打包时要禁用! 不然在GearVr眼镜上可以用触摸板控制镜头的移动.


在测试时，用鼠标控制准星（相机）的`localEulerAngles`
仅测试使用：
# 方案一
```csharp?linenums
using UnityEngine;

public class CameraController : MonoBehaviour {

    public float xSpeed = 15f;
    public float ySpeed = 15f;
    public bool IsDebug = false;
    private void Update() {
        if(!IsDebug) return;
        MouseControl();
    }

    void MouseControl() {
        float x = Input.GetAxis("Mouse X");
        float y = Input.GetAxis("Mouse Y");
        
        Vector3 v = this.transform.localEulerAngles;
        v.y += x * Time.deltaTime * xSpeed;
        v.x -= y * Time.deltaTime * ySpeed;
        
        this.transform.localEulerAngles = v;
    }
}
```
# 方案二：优化简洁版:
```csharp?linenums
using UnityEngine;

public class CameraController : MonoBehaviour {
	public bool IsDebug = false;
	void Update () {
	    if(!IsDebug) return;
        float x = Input.GetAxis("Mouse X");
        float y = Input.GetAxis("Mouse Y");

        Vector3 v = this.transform.localEulerAngles;

        v.y += x;
        v.x -= y;

        this.transform.localEulerAngles = v;
	}
}
```

# 方案三
```csharp?linenums
using UnityEngine;

public class FollowMouseMove : MonoBehaviour {

    public float moveSpeed = 5.0f;

    void Update(){

        // 获得鼠标当前位置的X和Y
        float mouseX = Input.GetAxis("Mouse X") * moveSpeed ;
        float mouseY = Input.GetAxis("Mouse Y") * moveSpeed ;

        // 鼠标在Y轴上的移动号转为摄像机的上下运动，即是绕着X轴反向旋转
        Camera.main.transform.localRotation = Camera.main.transform.localRotation * Quaternion.Euler(-mouseY, 0, 0);

        // 鼠标在X轴上的移动转为主角左右的移动，同时带动其子物体摄像机的左右移动
        transform.localRotation = transform.localRotation * Quaternion.Euler(0, mouseX, 0);
    }
}
```
>代码来自：https://jingyan.baidu.com/article/3065b3b6b67378becff8a480.html