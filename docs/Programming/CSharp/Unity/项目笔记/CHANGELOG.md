# v0.1.5
使用单例模板来创建单例类，解决了v0.1.2以来的Bug：
* 单例类在加载新的场景（非当前）后消失，或者出现空引用异常

## Fixed bugs
* AudioManager的可能出现空引用

# v0.1.4
BtnCtrl类的代码优化，按钮图片的属性访问设限，提供公共方法来修改图片的状态。供子类直接调用。
增加了qTimer类。
 定时器功能。可在一定程度上替换协程。
&emsp;&emsp;该类也是用协程实现的。

# v0.1.3
控制按钮的代码，写了一个BtnCtrl类，这个类在 v0.1.2 中是个普通的方法，当前版本中已经修改为了抽象类。
准星使按钮变化的事件都放在了子类中去实现。

# v0.1.2
加入了AudioManager, 脚本是QFramework中的。
由于游戏有两个场景，所以，AudioManager物体不能在加载到第二个场景后被销毁，可以在`Start()`方法中调用`DontDestroyOnLoad`方法：
```
void Start(){
//...
    DontDestroyOnLoad(transform.gameObject);
//...
}
```
但是当游戏结束后，重新加载游戏时，第二个场景中的未被销毁的`AudioManager`会再出现重新加载后的第一个场景。那么就会出现两个AudioManager。
但不影响游戏效果。

为解决这个问题，不再在Start中调用DontDestroyOnLoad方法，而是在第二个场景中也创建一个AudioManager物体。
这里又出现了调用顺序的问题。
经过一番尝试后，把单的例的赋值操作放在了`Onnable();`中。

## 问题
这个脚本不是很好用，可用另一个版本的AudioManager，但是功能实现了。

# v0.1.1
第一次整理备份
## Features
* 加入AudioManger

# TODO
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化
- [ ] 代码复杂化


