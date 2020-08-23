---
title: SeabedAdventures_v0.1.3 代码优化 
tags: Unity
grammar_cjkRuby: true
---
控制按钮的代码，写了一个BtnCtrl类，这个类在 SeabedAdventures_v0.1.2 中是个普通的方法，当前版本中已经修改为了抽象类。
```csharp?linenums
using UnityEngine;
using UnityEngine.UI;

namespace SeabedAdventures {
    public abstract class BtnCtrl : MonoBehaviour {
        [HideInInspector] public VRTriggerItem triggerItem;

        private Image buttonImage;

        /// <summary>
        /// 按钮所在的图片组件,待改变
        /// </summary>
        public Image ButtonImage {
            //属性赋值，在Start中赋值可能会出现空引用。
            get {
                if (buttonImage == null) {
                    buttonImage = GetComponent<Image>();
                }

                return buttonImage;
            }
        }


        private Sprite normalSprite;

        /// <summary>
        /// 按钮没有被凝视时的Sprite
        /// </summary>
        public Sprite NormalSprite {
            get {
                if (normalSprite == null) {
                    normalSprite = Resources.Load<Sprite>("normalSprite");
                }

                return normalSprite;
            }
        }


        private Sprite overSprite;

        /// <summary>
        /// 按钮被凝视时的的Sprite
        /// </summary>
        public Sprite OverSprite {
            get {
                if (overSprite == null) {
                    overSprite = Resources.Load<Sprite>("overSprite");
                }

                return overSprite;
            }
        }

        private void OnEnable() {
            triggerItem = GetComponent<VRTriggerItem>() ?? gameObject.AddComponent<VRTriggerItem>();
            triggerItem.onOver += OnOver;
            triggerItem.onOut += OnOut;
            triggerItem.onTrigger += OnTrigger;
        }

        private void OnDisable() {
            triggerItem.onOver -= OnOver;
            triggerItem.onOut -= OnOut;
            triggerItem.onTrigger -= OnTrigger;
        }

        public abstract void OnOver();
        public abstract void OnOut();
        public abstract void OnTrigger();
    }
}
```
# 例：
```csharp
using UnityEngine;

namespace SeabedAdventures {
    /// <summary>
    /// 显示Dialog002
    /// </summary>
    public class btn001 : BtnCtrl {
        public Transform  Dialog001;
        public GameObject Dialog002;

        /// <summary>
        /// 播放背景音乐
        /// </summary>
        private void Start() {
            AudioManager.Instance.PlayMusic("AudioSources/anime_01_loop", true);
        }

        public override void OnOver() {
            //图片的变换和缩放
            ButtonImage.sprite = OverSprite;
            this.transform.localScale = new Vector3(transform.localScale.x * 1.2f, transform.localScale.y * 1.2f, transform.localScale.z * 1.2f);
        }

        public override void OnOut() {
            //图片的变换和缩放
            ButtonImage.sprite = NormalSprite;
            this.transform.localScale = new Vector3(transform.localScale.x / 1.2f, transform.localScale.y / 1.2f, transform.localScale.z / 1.2f);
        }

        public override void OnTrigger() {
            if (RingCtrl.Instance.isTrigger && triggerItem.isTrigger) {
                Dialog002.SetActive(true);
                Dialog001.gameObject.SetActive(false);
            }
        }
    }
}
```