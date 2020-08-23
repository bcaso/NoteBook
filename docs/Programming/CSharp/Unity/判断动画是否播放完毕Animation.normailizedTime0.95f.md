# 判断动画是否播放完毕
2018.06.05
```csharp?linenums
animation.Play("roar");
if (anim.IsPlaying("roar") && anim["roar"].normalizedTime >= 1)  {

}
```
这个判断有问题，没成功执行里面的代码

建议使用协程来播放动画，yield return动画的长度，然后再执行其他
```csharp?linenums
    IEnumerator GameOver() {
        _animation.Play("die");
        yield return new WaitForSeconds(_animation.GetClip("die").length);
        Destroy(this.gameObject);           // 这个是在下一帧执行的。
        Debug.Log("HelloWorld");
        StopCoroutine(GameOver());
    }
```
或者说在代码中注册个事件，见笔记 AnimationEvent的使用。Event.time = clip.Length就行了。

2019/04/14  17:23
```csharp?linenums
/****************************************************
    文件：test.cs
	作者：WQ
    邮箱: bcaso@qq.com
    日期：2019/04/14 17:14
	功能：normalizeTime测试
*****************************************************/

using UnityEngine;

public class test : MonoBehaviour {
	private bool _booIsPlay = true;
	private Animation _animation;
	private void Start() {
		_animation = GetComponent<Animation>();
		_animation.Play("bgBar");
	}

	private void Update() {
		if (_animation["bgBar"].normalizedTime > 0.95f && _booIsPlay) {
			Debug.Log("动画条填充完毕");
			_animation.Play("bgImage");
			_booIsPlay = false;
		}
	}
}
```
# 总结
判断动画是否播放完毕可用通过判断 anim.normalizedTime 的值进行。
需要注意的是这个取值是0到1，但是只有使用>0.95f作为判断条件时才能时条件成立。(0.95f或者近似值，但不能是1)
`>=1`永远不可能成立
该问题终结！