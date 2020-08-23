# CharacterController.Move的模拟重力
```csharp
private const float FloGravity   = 9.8f;
private CharacterController _cc;

private const float FloSpeed = 10f;//速度
private float _floYDistance = 3f;//y轴的偏移量
void Start(){
    _cc = GetComponent<CharacterController>();
}

void Update(){
    Vector3 movement = transform.forward * Time.deltaTime * 100f;
    movement.y -= FloGravity * Time.deltaTime;
    
//    _cc.Move(movement);//向前走
   //向上跳
    _cc.Move((transform.forward * FloSpeed + new Vector3(0, _floYDistance, 0)) * Time.deltaTime);
}
```
