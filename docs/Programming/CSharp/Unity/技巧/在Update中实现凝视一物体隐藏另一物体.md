---
title: 在Update中实现凝视一物体隐藏另一物体
tags: Unity, AR, VR
grammar_cjkRuby: true
---
如果要实现凝视一物体显示一物体，并将上一物体隐藏，可用委托的方式实现，思路如下：
* 当凝视一物体时，给全部物体发消息，都隐藏
* 最后让被凝视的物体显示

提供另一种方式：
* 创建一空物体Parent，用于存放所有需要隐藏的物体
* 凝视一物体_goObj(默认为null)，触发事件
* 将Parent的子物体全部隐藏
* 如果`_goObj`为空则显示对应物体，并将其生成到目标位置，赋值给`_goObj`，防止重复生成
  * 将其在Hierarchy上的位置设置到空物体Parent下（保持其世界坐标）。
* 如果`_goObj`不为空，则显示`_goObj`

下面的代码截取自BaiduAR项目中的图片识别，当图片被成功识别，会调用OnRespond(),并实现显示图片对应的物体，同时隐藏上一显示的物体。

```csharp
    using UnityEngine;

    public class ImageRecognition : MonoBehaviour {
        //熊预制体
        public GameObject Prefab;

        private GameObject _goObj = null;

        //生成位置
        public Transform SpawnPos;

        //存放所有已生成的物体作为子物体，用于将其隐藏
        private Transform _parent;

        //监听组件
        private BaiduARImageRecognitionResult _result;

        private void Awake() {
            //得到监听组件
            _result = GetComponent<BaiduARImageRecognitionResult>();

            //添加一个响应事件
            _result.OnRespond.AddListener(new UnityAction(OnRespond));
        }

        private void Start() {
            //得到父物体
            _parent = GameObject.Find("Parent").transform;
        }

        /// <summary>
        /// 图片识别的响应方法, 在图片被识别到后触发
        /// </summary>
        private void OnRespond() {
            // 将所有子物体隐藏
            for (int i = 0; i < _parent.childCount; i++) {
                _parent.GetChild(i).gameObject.SetActive(false);
            }

            //显示图片识别后对应的物体
            if (!_goObj) {
                _goObj = Instantiate(Prefab, SpawnPos.position, SpawnPos.rotation);

                //设置层级视图中的父物体，不改变其世界坐标
                _goObj.transform.SetParent(this._parent, true);
            }
            else { //显示当前物体
                _goObj.SetActive(true);
            }
        }
    } //Class_end
```