```c#
		//必须，多个Pass（通道）按代码中的先后顺序进行执行（渲染）
        //一般不建议使用多个Pass通道，因为每渲染一个Pass，DrawCall就多一个
        Pass
        {
            Name "Default" //Pass通道名称
            //Tags()可以在每个Pass通道里面进行定义
            Tags
            {
                "LightMode" = "ForwardBase"         //定义该Pass通道在Unity渲染流水中的角色
                "RequireOptions" = "SoftVegetation" //满足某些条件时才渲染该通道
            }//可以在每个Pass通道里面定义
            
            //CG语言所写的代码，主要是定点片元着色器
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            // make fog work
            #pragma multi_compile_fog

            #include "UnityCG.cginc"

            struct appdata{...};

            struct v2f{...};

            sampler2D _MainTex;
            float4 _MainTex_ST;

            v2f vert (appdata v){...}

            fixed4 frag (v2f i) : SV_Target{...}
            ENDCG
        }
```