[TOC]
# 基本结构

```
       +> Properties +--> variables
       |
       |            +--> Tags
       |            |
Shader +> SubShader +--> Pass
                    |   +-------------------------+
                    +-->+ Renderer Render Settings|
                        +-------------------------+
                        | Cull off                |
                        | ZTest Always            |
                        | Zwrite off              |
                        | LOD 100                 |
                        | ...                     |
                        +-------------------------+

```
## 预览
```c#
Shader "Unlit/001" //这里的名字最好跟文件名保持一致，方便查找
{
    //定义变量，这里的变量在属性面板能看到，定义变量类型有个下划线的区别
    Properties
    {        
        //_变量名称("外面显示名称", 变量类型) = 默认值
        //外面显示名称也是变量名称，用来在属性面板显示，为了与变量名称区别，变量名称要加下划线
        _Int("Int", Int) = 2                 //后面不需要分号
        _Float("Float", Float) = 1.5         //后面不需要f
        _Float1("Float1", float) = 1.5
        _Range("Range", range(0.0, 2.0)) = 1.0//默认1.0，取值范围是 0.0 - 2.0
        //关于颜色，无论代码中的值取多少，在属性面板上的颜色中RGBA始终是255, 255, 255, 255也就是白色
        _Color("Color", Color) = (0, 0, 0, 0)
        _Color1("Color1", Color) = (1, 1, 1, 1)
        _Color2("Color2", Color) = (133, 133, 133, 133)
        
        _Vector("Vector", Vector) = (1, 1, 2, 2)
        _3D("3D", 3D) = "black"{}            //3D类型，几乎用不到
        _Cube("Cube", Cube) = "white"{}      //Cube类型        
        _MainTex ("Texture", 2D) = "white" {}//Texture类型
    }
    SubShader //一个shader文件中可包含多个SubShader块代码
    {
        //Tags可选，也可以在其他地方定义
        Tags { "RenderType"="Opaque" }
        
        //Renderer 设置，英文：Renderer Render Settings
        Cull off
        ZTest Always
        Zwrite off
        LOD 100

        //必须，多个Pass（通道）按代码中的先后顺序进行执行（渲染）
        //一般不建议使用多个Pass通道，因为每渲染一个Pass，DrawCall就多一个
        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            // make fog work
            #pragma multi_compile_fog

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                UNITY_FOG_COORDS(1)
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                UNITY_TRANSFER_FOG(o,o.vertex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                // sample the texture
                fixed4 col = tex2D(_MainTex, i.uv);
                // apply fog
                UNITY_APPLY_FOG(i.fogCoord, col);
                return col;
            }
            ENDCG
        }
    }
}
```
## Tags
```c#
    	//Tags可选, key = value
        Tags 
        {
         "Queue" = "Transparent"             //Queue渲染顺序，Transparent透明
         "RenderType"="Opaque"               //渲染类型，用于着色器替换功能
         "DisableBatching" = "True"          //是否进行合批
         "ForceNoShadowCasting" = "True"     //物体是否投射阴影
         "IgnoreProjector" = "True"          //是否受Projector影响（做阴影的东西），通常用于透明的物体
         "CanUseSpriteAltas" = "False"       //是否是用于图片的Shader，通常用于UI
         "PreviewType" = "Plane"             //用作Shader面板预览类型，属性面板的预览显示类型，球体或平面
         } 
```
Tags标签也可以写在Pass通道的开始
```c#
 Pass
 {
 	//Tags()可以在每个Pass通道里面进行定义
	...
 }
```
## Renderer Render Settings
渲染器渲染设置
```c#
		//Renderer Renderer Settings 渲染器渲染设置
        Cull off
        ZTest Always
        Zwrite off
        LOD 100
```
也可以放在Pass通道中的其他代码之前
```c#
Pass
{
        Cull off
        ZTest Always
        Zwrite off
        LOD 100
}
```
## 变量范围
由于Tags和Renderer Render Settings的设置既可以在SubShader内，也可以在SubShader外，如果内外皆有定义相同的变量的话。那么会走外面的。
>http://www.sikiedu.com/course/409/task/29857/show  00:53