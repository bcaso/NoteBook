[TOC]

# 向屏幕中心发射射线
效果图：

https://i.niupic.com/images/2019/04/27/6gPC.gif
https://i.niupic.com/images/2019/04/27/6gPD.gif
由于直接放gif图的话，页面会无限加载。所以，就直接放链接，如上

```csharp?linenums
/****************************************************
    文件：RaycastShoot.cs
	作者：WQ
    邮箱: bcaso@qq.com
    日期：2019/04/27 8:51
	功能：发出射线，射击物体并造成伤害，播放射击音效，显示射击轨迹并等待一段时间后消失
*****************************************************/

using System.Collections;
using System.Security.Policy;
using UnityEngine;

[RequireComponent(typeof(LineRenderer))]
[RequireComponent(typeof(AudioSource))]
public class RaycastShoot : MonoBehaviour {
	//设置枪击带来的伤害值
	public int   gunDamage   = 1;
	public float fireRate    = 0.25f;
	public float weaponRange = 50f;
	//枪击冲击力
	public float hitForce = 100f;
	//GunEnd 游戏物体
	public Transform gunEnd;
	public GameObject bulletPrefab;

	//fps相机
	private Camera fpsCam;
	//射击轨迹显示的时间
	private WaitForSeconds shotDuration = new WaitForSeconds(0.07f);
	//枪击音效
	private AudioSource gunAudio;
	//射击轨迹
	private LineRenderer laserLine;
	private float        nextFire;

	private Vector3 targetPoint = Vector3.zero; //子弹朝向的目标点

	private void Start() {
		laserLine = GetComponent<LineRenderer>();
		gunAudio  = GetComponent<AudioSource>();
		fpsCam    = GetComponentInParent<Camera>();
	}

	private void Update() {
		if (Input.GetButton("Fire1") && Time.time > nextFire) {
			nextFire = Time.time + fireRate;
			//启用ShotEffect协程控制射线显示及隐藏
			StartCoroutine(ShotEffect());
			//在相机视口中心创建向量
			Vector3 rayOrigin = fpsCam.ViewportToWorldPoint(new Vector3(0.5f, 0.5f, 0.0f));

			RaycastHit hit;
			//将射击轨迹点设置为GunEnd对象的位置
			laserLine.SetPosition(0, gunEnd.position);
			//检测射线是否碰撞到对象
			if (Physics.Raycast(rayOrigin, fpsCam.transform.forward, out hit, weaponRange)) {
				//将射击轨迹点设置为碰撞发生的位置
				laserLine.SetPosition(1, hit.point);
				//获取被射中对象上的Health组件
				fps_EnemyHealth health = hit.collider.GetComponent<fps_EnemyHealth>();

				if (health != null) {
					//调用组件的Damage函数计算伤害
					health.TakeDamage(gunDamage);
				}

				//检测被射中的对象是否存在rigidbody组件
				if (hit.rigidbody != null) {
					hit.rigidbody.AddForce(-hit.normal * hitForce);
					Debug.Log("射中物体" + hit.rigidbody.gameObject);
				}

				//更新子弹目标点
				targetPoint = hit.point;
			}
			else {
				//如果未射中任何对象，则将射击轨迹终点设为相机前方的武器射程最大距离处
				laserLine.SetPosition(1, rayOrigin + (fpsCam.transform.forward * weaponRange));

				//更新子弹目标点
				targetPoint = fpsCam.transform.forward * 1000f;
			}


			//在枪口的位置实例化一颗子弹，按子弹发射点出的旋转，进行旋转
			GameObject go = Instantiate(bulletPrefab, gunEnd.position, gunEnd.rotation) as GameObject;
			//子弹朝向目标点
			go.transform.LookAt(targetPoint);
			Destroy(go, 3f);
		}
	}

	private IEnumerator ShotEffect() {
		gunAudio.Play();
		laserLine.enabled = true;
		yield return shotDuration;
		laserLine.enabled = false;
	}
}
```

只需要设置其width为0.1或者更小一点即可
![lineRenderer组件](https://i.niupic.com/images/2019/04/27/6gPE.png)
lineRenderer组件可以设置的起点的位置，终点的位置，起点的宽度以及终点的宽度，如下图：
```csharp?linenums
/****************************************************
    文件：BulletMove.cs
	作者：WQ
    邮箱: bcaso@qq.com
    日期：2019/04/27 9:40
	功能：子弹移动
*****************************************************/

using UnityEngine;

public class BulletMove : MonoBehaviour {
	public float bulletSpeed = 100f;

	private void Update() {
		transform.Translate(Vector3.forward * bulletSpeed * Time.deltaTime, Space.Self);
	}
}
```
>参考文章：
https://www.chinaar.com/ZYJC/1256.html
https://blog.csdn.net/baidu_39447417/article/details/74897704

[========]


2019/05/05 补充示例：
```csharp?linenums
/****************************************************
    文件：GunController.cs
	作者：WQ
    邮箱: bcaso@qq.com
    日期：2019/05/05 18:01
	功能：fps射击
*****************************************************/

using System.Collections;
using UnityEngine;

namespace shoter {
	public class GunController : MonoBehaviour {
		//射线距离
		public float shootLength = 100f;
		//枪的终点
		public Transform gunEnd;
		//子弹预制体
		public GameObject bullet;
		//子弹运动速度
		public float bulletMoveSpeed = 60f;
		//下次射击时间间隔
		public float nextFire = 0.3f;
		//射线目标点
		private Vector3 targetPos;

		//射击力度，给予被攻击物体的反向作用力
		public float hitForce = 100f;
		//lineRenderer
		private LineRenderer _LineRenderer;


		private void Start() {
			_LineRenderer         = GetComponent<LineRenderer>();
			_LineRenderer.enabled = false;
		}

		//控制枪的射击
		void Update() {
			//定时器
			nextFire -= Time.deltaTime;

			//设置射线的起点
			_LineRenderer.SetPosition(0, gunEnd.position);

			//按键检测
			if (Input.GetKey(KeyCode.Mouse0) && nextFire < 0) {
				//发射子弹
				GameObject go = Instantiate(bullet, gunEnd.position, Quaternion.identity);

				//射线检测
				RaycastHit hit;
				if (Physics.Raycast(Camera.main.ViewportToWorldPoint(new Vector3(.5f, .5f, 0)),
				                    Camera.main.transform.forward, out hit, shootLength)) {
					targetPos = hit.point;

					//敌人的受伤处理
					if (hit.collider.CompareTag("Enemy")) {
						//Do something here...
						hit.transform.SendMessage("GetDamage");
						if (hit.rigidbody) {
							hit.rigidbody.AddForce(-hit.normal * hitForce);
						}
					}
				}
				//如果什么都没有射到，就将目标点设置为相机前1000m
				else {
					targetPos = Camera.main.transform.forward * 1000;
				}


				//显示射线
				StartCoroutine("ShowEffect");
				//设置射线的目标
				_LineRenderer.SetPosition(1, targetPos);


				//看向目标点
				go.transform.LookAt(targetPos);
				//施加力
				go.GetComponent<Rigidbody>().velocity = go.transform.forward * bulletMoveSpeed;


				//定时销毁子弹
				Destroy(go.gameObject, 3f);

				//重置定时器
				nextFire = 0.3f;
			}
		}

		/// <summary>
		/// 控制射线效果显示时长
		/// </summary>
		/// <returns></returns>
		IEnumerator ShowEffect() {
			float timer = 0;
			while (timer <= 0.07f) {
				_LineRenderer.enabled = true;
				yield return  null;
				timer += Time.deltaTime;
			}

			_LineRenderer.enabled = false;
		}
	}
}
```

## 关于非球形子弹,同样适用于球形子弹
```csharp?linenums
/****************************************************
    文件：GunController.cs
	作者：WQ
    邮箱: bcaso@qq.com
    日期：2019/05/10 17:45
	功能：fps射击
*****************************************************/

using System.Collections;
using UnityEngine;

namespace shoter {
	public class GunController : MonoBehaviour {
		//射线距离
		public float shootLength = 100f;
		//枪的终点
		public Transform gunEnd;
		//子弹预制体
		public GameObject bullet;
		//子弹运动速度
		public float bulletMoveSpeed = 60f;
		//下次射击时间间隔
		public float nextFire = 0.3f;
		//射线目标点
		private Vector3 targetPos;

		//射击力度，给予被攻击物体的反向作用力
		public float hitForce = 100f;

		//lineRenderer
		private LineRenderer _LineRenderer;

		private Camera m_Camera;


		private void Start() {
			_LineRenderer         = GetComponent<LineRenderer>();
			_LineRenderer.enabled = false;
			m_Camera              = Camera.main;
		}

		//控制枪的射击
		void Update() {
			//定时器
			nextFire -= Time.deltaTime;

			//设置射线的起点
			_LineRenderer.SetPosition(0, gunEnd.position);

			//按键检测
			if (Input.GetKey(KeyCode.Mouse0) && nextFire < 0) {
				//射线检测
				RaycastHit hit;
				if (Physics.Raycast(Camera.main.ViewportToWorldPoint(new Vector3(.5f, .5f, 0)),
				                    Camera.main.transform.forward, out hit, shootLength)) {
					targetPos = hit.point;
					Debug.Log(hit.collider.gameObject.name);

					//敌人的受伤处理
					if (hit.collider.CompareTag("Enemy")) {
						//Do something here...
						hit.transform.SendMessage("GetDamage");
						if (hit.rigidbody) {
							hit.rigidbody.AddForce(-hit.normal * hitForce);
						}
					}
				}
				//如果什么都没有射到，就将目标点设置为相机前1000m
				else {
					targetPos = Camera.main.transform.forward * 1000;
				}

				//发射子弹,为防止射线射到子弹，子弹要在射线发出后再生成
				GameObject go = Instantiate(bullet, gunEnd.position, gunEnd.rotation);

				//显示射线
				StartCoroutine("ShowEffect");
				//设置射线的目标点
				_LineRenderer.SetPosition(1, targetPos);


				//控制子弹方向，看向目标点
				go.transform.LookAt(targetPos);
//				go.transform.LookAt(Camera.main.transform.forward * 1000); //偏离准星一点点
				//给子弹施加力
				go.GetComponent<Rigidbody>().velocity = go.transform.forward * bulletMoveSpeed;
//				go.GetComponent<Rigidbody>().AddForce(go.transform.forward * bulletMoveSpeed); //与上行相比，施加力，力的值要大于上面速度的值，可能要大到1000

				//go.GetComponent<Rigidbody>().velocity = Vector3.forward * bulletMoveSpeed;//不可用，方向偏向世界的z轴

				//定时销毁子弹
				Destroy(go.gameObject, 3f);

				//重置定时器
				nextFire = 0.3f;
			}
		}


		/// <summary>
		/// 看向相机并控制与相机的相对位置
		/// 位置的设置，可通过一个空物体放在相机下，位置归0，然后再拿出来作为枪的父物体，或者计算出偏移量，然后一直保持这个位置
		/// 枪的位置再适当调整下
		/// </summary>
		private void FixedUpdate() {
			//设置位置
			transform.position = m_Camera.transform.position;
			//lerp到相机的本地坐标
			transform.rotation = Quaternion.Lerp(transform.rotation, m_Camera.transform.localRotation,
			                                     15 * Time.deltaTime
			                                    );
			//看向准星,这个不写也能实现效果
		}


		/// <summary>
		/// 控制射线效果显示时长
		/// </summary>
		/// <returns></returns>
		IEnumerator ShowEffect() {
			float timer = 0;
			while (timer <= 0.07f) {
				_LineRenderer.enabled = true;
				yield return  null;
				timer += Time.deltaTime;
			}

			_LineRenderer.enabled = false;
		}
	}
}
```

## 简易版
```csharp?linenums
/****************************************************
    文件：GunCtrl.cs
	作者：WQ
    邮箱: bcaso@qq.com
    日期：2019/05/10 18:15
	功能：射击的简单实现，子弹（任何形状）朝向准星发射
*****************************************************/

using System;
using UnityEngine;
using VRStandardAssets.Utils;

public class GunCtrl : MonoBehaviour {
	public Camera     m_Camera;
	public Transform  gunEnd;
	public GameObject bullet;
	public float      speed = 60;

	private float   nextFire = 0.3f;
	private Vector3 targetPos;


	private void Start() { }

	private void Update() {
		//按键检测
		nextFire -= Time.deltaTime;
		if (Input.GetMouseButton(0) && nextFire < 0) {
			//射线
			Ray        ray = new Ray(m_Camera.transform.position, m_Camera.transform.forward);
			RaycastHit hit;

			//目标点的计算
			//如果有射到物体
			if (Physics.Raycast(ray, out hit, 300)) {
				targetPos = hit.point;
			}
			//如果什么都没射到，将目标点设置为1000m外
			else {
				targetPos = m_Camera.transform.forward * 1000;
			}

			//生成子弹
			GameObject go = Instantiate(bullet, gunEnd.position, gunEnd.rotation);

			//子弹看向目标点
			go.transform.LookAt(targetPos);

			//子弹运动
			go.GetComponent<Rigidbody>().velocity = go.transform.forward * speed;

			Destroy(go.gameObject, 5f);

			nextFire = 0.3f;
		}
	}
}
```