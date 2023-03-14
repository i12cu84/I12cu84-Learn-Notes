C for Graphics 
p1

shader
![](../assets/2022-04-21-14-46-40.png)

渲染管线
![](../assets/2022-04-21-14-46-52.png)
![](../assets/2022-04-21-14-47-47.png)
![](../assets/2022-04-21-14-49-00.png)
![](../assets/2022-04-21-14-49-37.png)

![](../assets/2022-04-21-14-53-43.png)

![](../assets/2022-04-21-14-56-01.png)

p2

三种语言GLSL (HLSL CG)

![](../assets/2022-04-21-14-56-46.png)

![](../assets/2022-04-21-14-57-17.png)
![](../assets/2022-04-21-14-58-31.png)
![](../assets/2022-04-21-15-00-22.png)

p3

![](../assets/2022-04-21-15-03-26.png)
![](../assets/2022-04-21-15-03-41.png)
![](../assets/2022-04-21-15-04-05.png)
![](../assets/2022-04-21-15-04-28.png)
![](../assets/2022-04-21-15-04-51.png)
![](../assets/2022-04-21-15-05-25.png)
![](../assets/2022-04-21-15-05-54.png)
![](../assets/2022-04-21-15-06-37.png)

![](../assets/2022-04-21-15-06-55.png)
![](../assets/2022-04-21-15-07-16.png)
![](../assets/2022-04-21-15-07-39.png)

![](../assets/2022-04-21-15-08-14.png)

p4

![](../assets/2022-04-21-15-16-34.png)
![](../assets/2022-04-21-15-20-12.png)

p5

创建
![](../assets/2022-04-21-15-26-09.png)
fixed function shader固定管线
Shader "name"{
    properties{
        //材质色
        _Color("Hain Clolr",color)=(1,1,1,1)
        //环境光色
        _Ambient("Ambient",color)=(0.3,0.3,0.3,0.3)
        //高光色
        _Specular("Specular",color)=(1,1,1,1)
        //随机高光的集中范围
        _Shininess("Shininess",range(0,8))=4
        //自发光色
        _Emission("Emission",color)=(1,1,1,1)
    }
    SubShader{
        pass{
            //颜色红色
            //color(1,0,0,1)
            //pp上渲染 小括号参数值
            //color[_Color]
            //材质命令块
            material{
                //材质颜色
                diffuse[_Color]
                //环境光
                ambient[_Ambient]
                //高光需要separatespecular on
                specular[_Specular]
                //浮点值描述高光强度的范围
                shininess[_Shininess]
                //自发光
                emission[_Emission]
            }
            //光照 开启或者关闭 on/off
            lighting on
            //独立正面高光
            separatespecular on
        }
    }
}

p6

//sd基础上
Shader "name"{
    properties{
        //材质色
        _Color("Hain Clolr",color)=(1,1,1,1)
        //环境光色
        _Ambient("Ambient",color)=(0.3,0.3,0.3,0.3)
        //高光色
        _Specular("Specular",color)=(1,1,1,1)
        //随机高光的集中范围
        _Shininess("Shininess",range(0,8))=4
        //自发光色
        _Emission("Emission",color)=(1,1,1,1)
        //纹理属性 设为空贴图
        _MainTex("MainTex",2d)="white"{}
        //纹理2
        _SecondTex("SecondTex",2d)=""{}
        //恒色
        _Constant("Constant",color)=(1,1,1,0.3)
    }
    SubShader{
        //标签 渲染队列 值 -> 影响渲染顺序 -> 完成透明效果
        Tags {"Queue" = "Transparent"}
        //通道
        pass{
            //Blending混合
            //渲染通道中设定 Alpha混合值
            //并未完全透明 原因:渲染有顺序 加入Tags即可
            Blend SrcAlpha OneMinusSrcAlpha
            material{
                //材质颜色
                diffuse[_Color]
                //环境光
                ambient[_Ambient]
                //高光需要separatespecular on
                specular[_Specular]
                //浮点值描述高光强度的范围
                shininess[_Shininess]
                //自发光
                emission[_Emission]
            }
            //光照 开启或者关闭 on/off
            lighting on
            //独立正面高光
            separatespecular on
            //纹理设置贴图 1 混合原有
            settexture[_MainTex]
            {
                //随后可以细节面板上贴图
                //primary代表前面所有颜色 相乘变成混合色 
                //double乘以二(两倍亮度) quad 四倍
                combine texture * primary double
            }
            //纹理设置贴图 2 混合1
            settexture[_SecondTex]
            {
                //恒色
                constantColor[_Constant]
                //previous 先前的纹理
                //,texture 只是取了Alpha通道
                combine texture * previous double,texture*constant
            }
            //混合次数有限
        }
    }
}
settexture 贴图
combine 返回贴图结果 (可以附加混合)
constantColor 恒色
blend Alpha混合
tags 变更渲染顺序达到效果

p7

surface shaders
Shader "name" {
    Properties{
        //颜色
        _Color("Color",Color)=(1,1,1,1)
        //纹理属性
        _MainTex("Albedo (RGB)",2D)="white"()
        //浮点值 计算光泽度
        _Glossiness("Smoothness",Range(0,1))=0.5
        //浮点值 计算表现金属光泽
        _Metallic("Metallic",Range(0,1))=0.0
    }
    SubShader{
        //无需pass通道
        //渲染类型 不透明类型
        Tags{"RenderType"="Opaque"}
        //层级细节
        LOD 200
        //代码块 后使用CG语法
        CGPROGRAM
        //pragma s-按照s形式编写 surf-描述函数 Standard基于物理的光照模型 类型选项
        #pragma surface surf Standard fullforwardshadows
        //对着色器用硬件3.0着色处理指令范围
        #pragma target 3.0
        //结构体 描述uv坐标(纹理坐标)
        struct Input{
            //没有uv编译后得不到纹理采样 (名称固定)
            float2 uv_MainTex;
        };
        //四属性具体声明 类型不是一一对应的
        fixed4 _Color;
        half _Metallic;
        half _Glossiness;
        //二维纹理
        sampler2D _MainTex;
        //函数 无返回 两个参数 in输入 inout输入输出
        //surf...类型 基于物理的光照模型
        //![](../assets/2022-04-21-17-03-12.png)
        void surf(Input IN,inout SurfaceOutputStandard o){
            //颜色值 采样
            fixed4 c=text2D(_MainTex,IN.uv_MainTex)*_Color;
            //取RGB值
            o.Albedo=c.rqb;
            o.Metallic=_Metallic;
            o.Smoothness=_Glossiness;
            //取Alpha
            o.Alpha=c.a;
        }
        ENDCG
    }
    //默认 回滚到Diffuse 
    FallBack "Diffuse"
}

p8

相比p7更旧版的
![](../assets/2022-04-21-17-06-23.png)
//按照透明物体来渲染
Tags{"RenderType"="Opaque" "queue"="transparent"}
//以alpha混合的物体 加上着色
#pragma surface surf Lambert alpha addshadow
//具有阴影效果
#pragma surface surf Lambert addshadow

p9

cg输入输出常用语义
Shader "name"{
    SubShader{
        pass{
            //启用cg 固定大写
            CGPROGRAM
            //v顶点程序 vert函数名
            #pragma vertex vert
            //f片段程序 frag函数名
            #pragma fragment frag
            //c语言规范的函数 输入输出类型
            //定点程序 输出 类型 名字:语义(位置)
            void vert(in float2 objPos:POSITION,out float4 pos:POSITION,out float4 col:COLOR0){
                //凑成四阶向量 模型坐标上进行渐变变化
                ![](../assets/2022-04-21-18-33-27.png)
                pos=float4(objPos,0,1);
                //蓝色输出
                //col=float4(0,0,1,1)
                //语义不同 但可复制 语义:处理范围的规范
                col=pos;
            }
            //片段程序 拿到vert 输出 语义(颜色) COLOR=COLOR0
            //inout 输入且输出
            void frag(inout float4 col:COLOR0){
                //改写绿色
                col=float4(0,1,0,1);
            }
            ENDCG
        }
    }
}

p10

profile 数据类型

Shader "name"{
    SubShader{
        pass{
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            void vert(in float2 objPos:POSITION,out float4 pos:POSITION,out float4 col:COLOR0){
                pos=float4(objPos,0,1);
                col=pos;
            }
            void frag(inout float4 col:COLOR0){
                float r=1;
                float g=0;
                float b=0;
                float a=1;
                //构造四维float
                //float float2 float3 float4
                col=float4(r,g,b,a);
                //half 16位精度 浮点值
                //half half2 half3 half4
                //fixed 向量
                //fixed fixed2 fixed3 fixed4
                //bool int (sampler*)
            }
            ENDCG
        }
    }
}

![](../assets/2022-04-21-18-39-59.png)

![](../assets/2022-04-21-18-44-24.png)

p11

向量 swizzle操作 矩阵 数组 结构体
bool bl=true;
//三目
col bl?col:fixed4(0,1,0,1);
float2 fl2=float2(1,0);
float3 fl3=float3(1,0,0);
float4 fl4=float4(1,0,0,0);
float4 fl=float4(fl2.xy,1); // xyzv rgba (xy互换值互换 xx表取两个x)
col=fl;//颜色赋值转换

typedef float4 FL4; //宏定义 可替换
#define MACROFL float4(fl2.xy,1);
float4 fl=MACROFL //上行有分号 因而不用分号

float2x2 M2x2={1,0,1,1};//矩阵
float2x4 M2x4={0,0,1,1 ,0,1,0,1};
col=M2x4[0];//取了0,0,1,1
float arr[4]={1,0.5,0.5,1};
col=float4(arr[0],arr[1],arr[2],arr[3]);

struct v2f
{
    float4 pos;
    float2 uv;
};
v2f o;
o.pos=fl4;
o.uv=fl2;

p12

switch if while do..while for同c语言

p13

cg函数

Shader "name"{
    SubShader{
        pass{
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            void Fnuc(out float4 c);

            //传入数组必须指定 且无误差
            float Func2(float arr[2]){
                float sum=0;
                for(int i=0;i<arr.Length;++i){
                    sum+=arr[i];
                }
                return sum;
            }

            void vert(in float2 objPos:POSITION,out float4 pos:POSITION,out float4 col:COLOR0){
                pos=float4(objPos,0,1);
                col=pos;
            }
            void frag(inout float4 col:COLOR0){
                //Func(col);
                float arr[]={0.5,0.5};
                col.x=Func2(arr);
            }
            //out参数 传出
            void Func(out float4 c){
                c=float4(0,1,0,1);
            }
            ENDCG
        }
    }
}

----------------------------------------------------------------

sbin.cgsic


void Func(out float4 c){
    c=float4(0,1,0,1);
}
float Func2(float arr[2]){
    float sum=0;
    for(int i=0;i<arr.Length;++i){
        sum+=arr[i];
    }
    return sum;
}

vf2.shader

Shader "name"{
    SubShader{
        pass{
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            //调用自己写的 用\/都可以(任何数量)
            #include "sbin/sbin.cginc"
            void vert(in float2 objPos:POSITION,out float4 pos:POSITION,out float4 col:COLOR0){
                pos=float4(objPos,0,1);
                col=pos;
            }
            void frag(inout float4 col:COLOR0){
                //Func(col);
                float arr[]={0.5,0.5};
                col.x=Func2(arr);
            }
            ENDCG
        }
    }
}

p14

内建函数

数学函数 几何函数 纹理函数 导数函数等CG标准库

1.数学函数（Mathematical Functions）
abs(x)	返回输入参数的绝对值
acos(x)	反余切函数，输入参数范围为[-1,1]， 返回[0,π]区间的角度值
all(x)	如果输入参数均不为0，则返回ture； 否则返回flase。&&运算
any(x)	输入参数只要有其中一个不为0，则返回true。
asin(x)	反正弦函数,输入参数取值区间为，返回角度值范围为, 
atan(x)	反正切函数，返回角度值范围为
atan2(y,x)	计算y/x的反正切值。实际上和atan(x)函数功能完全一样，至少输入参数不同。atan(x) = atan2(x, float(1))。
ceil(x)	对输入参数向上取整。例如： ceil(float(1.3)) ，其返回值为2.0
clamp(x,a,b)	如果x值小于a，则返回a；
如果x值大于b，返回b；
否则，返回x。
cos(x)	返回弧度x的余弦值。返回值范围为
cosh(x)	双曲余弦（hyperbolic cosine）函数，计算x的双曲余弦值。
cross(A,B)	返回两个三元向量的叉积(cross product)。注意，输入参数必须是三元向量！
degrees(x)	输入参数为弧度值(radians)，函数将其转换为角度值(degrees)
determinant(m)	计算矩阵的行列式因子。
dot(A,B)	返回A和B的点积(dot product)。参数A和B可以是标量，也可以是向量（输入参数方面，点积和叉积函数有很大不同）。
exp(x)	计算的值，e=2.71828182845904523536
exp2(x)	计算的值
floor(x)	对输入参数向下取整。例如floor(float(1.3))返回的值为1.0；但是floor(float(-1.3))返回的值为-2.0。该函数与ceil(x)函数相对应。
fmod(x,y)	返回x/y的余数。如果y为0，结果不可预料。
frac(x)	返回标量或矢量的小数
frexp(x, out i)	将浮点数x分解为尾数和指数，即， 返回m，并将指数存入i中；如果x为0，则尾数和指数都返回0
isfinite(x)	判断标量或者向量中的每个数据是否是有限数，如果是返回true；否则返回false;
isinf(x)	判断标量或者向量中的每个数据是否是无限，如果是返回true；否则返回false;
isnan(x)	判断标量或者向量中的每个数据是否是非数据(not-a-number NaN)，如果是返回true；否则返回false;
ldexp(x, n)	计算的值
lerp(a, b, f)	计算或者的值。即在下限a和上限b之间进行插值，f表示权值。注意，如果a和b是向量，则权值f必须是标量或者等长的向量。
lit(NdotL, NdotH, m)	N表示法向量；
L表示入射光向量；
H表示半角向量；
m表示高光系数。 
函数计算环境光、散射光、镜面光的贡献，返回的4元向量。 
X位表示环境光的贡献，总是1.0; 
Y位代表散射光的贡献，如果 ，则为0；否则为 
Z位代表镜面光的贡献，如果 或者，则位0；否则为;
W位始终位1.0
log(x)	计算的值，x必须大于0
log2(x)	计算的值，x必须大于0
log10(x)	计算的值，x必须大于0
max(a, b)	比较两个标量或等长向量元素，返回最大值。
min(a,b)	比较两个标量或等长向量元素，返回最小值。
modf(x, out ip)	把x分解成整数和分数两部分，每部分都和x有着相同的符号，整数部分被保存在ip中，分数部分由函数返回
mul(M, N)	矩阵M和矩阵N的积，计算方法如下
mul(M, v)	矩阵M和列向量v的积，公式如下
mul(v, M)	行向量v和矩阵M的积，公式如下
noise(x)	根据它的参数类型，这个函数可以是一元、二元或三元噪音函数。返回的值在0和1之间，并且通常与给定的输入值一样
pow(x, y)	 
radians(x)	函数将角度值转换为弧度值
round(x)	返回四舍五入值。
rsqrt(x)	x的平方根的倒数，x必须大于0
saturate(x)	把x限制到[0,1]之间
sign(x)	如果则返回1；否则返回0
sin(x)	输入参数为弧度，计算正弦值，返回值范围 为[-1,1]
sincos(float x, out s, out c)	该函数是同时计算x的sin值和cos值，其中s=sin(x)，c=cos(x)。该函数用于“同时需要计算sin值和cos值的情况”，比分别运算要快很多!
sinh(x)	计算x的双曲正弦
smoothstep(min, max, x)	值x位于min、max区间中。如果x=min，返回0；如果x=max，返回1；如果x在两者之间，按照下列公式返回数据：
step(a, x)	如果，返回0；否则，返回1
sqrt(x)	求x的平方根，，x必须大于0
tan(x)	计算x正切值
tanh(x)	计算x的双曲线切线
transpose(M)	矩阵M的转置矩阵
如果M是一个AxB矩阵，M的转置是一个BxA矩阵，它的第一列是M的第一行，第二列是M的第二行，第三列是M的第三行，等等



2.几何函数(Geometric Functions)
distance(pt1, pt2)	两点之间的欧几里德距离（Euclidean distance）
faceforward(N,I,Ng)	如果，返回N；否则返回-N。
length(v)	返回一个向量的模，即sqrt(dot(v,v))
normalize(v)	返回v向量的单位向量
reflect(I, N)	根据入射光纤方向I和表面法向量N计算反射向量，仅对三元向量有效
refract(I,N,eta)	根据入射光线方向I，表面法向量N和折射相对系数eta,计算折射向量。如果对给定的eta,I和N之间的角度太大，返回(0,0,0)。
只对三元向量有效



3.纹理映射函数(Texture Map Functions)
tex1D(sampler1D tex, float s)	一维纹理查询
tex1D(sampler1D tex, float s, float dsdx, float dsdy)	使用导数值（derivatives）查询一维纹理
Tex1D(sampler1D tex, float2 sz)	一维纹理查询，并进行深度值比较
Tex1D(sampler1D tex, float2 sz, float dsdx,float dsdy)	使用导数值（derivatives）查询一维纹理， 并进行深度值比较
Tex1Dproj(sampler1D tex, float2 sq)	一维投影纹理查询
Tex1Dproj(sampler1D tex, float3 szq)	一维投影纹理查询，并比较深度值
Tex2D(sampler2D tex, float2 s)	二维纹理查询
Tex2D(sampler2D tex, float2 s, float2 dsdx, float2 dsdy)	使用导数值（derivatives）查询二维纹理
Tex2D(sampler2D tex, float3 sz)	二维纹理查询，并进行深度值比较
Tex2D(sampler2D tex, float3 sz, float2 dsdx,float2 dsdy)	使用导数值（derivatives）查询二维纹理，并进行深度值比较
Tex2Dproj(sampler2D tex, float3 sq)	二维投影纹理查询
Tex2Dproj(sampler2D tex, float4 szq)	二维投影纹理查询，并进行深度值比较
texRECT(samplerRECT tex, float2 s)	二维非投影矩形纹理查询（OpenGL独有）
texRECT (samplerRECT tex, float3 sz, float2 dsdx,float2 dsdy)	二维非投影使用导数的矩形纹理查询（OpenGL独有）
texRECT (samplerRECT tex, float3 sz)	二维非投影深度比较矩形纹理查询（OpenGL独有）
texRECT (samplerRECT tex, float3 sz, float2 dsdx,float2 dsdy)	二维非投影深度比较并使用导数的矩形纹理查询（OpenGL独有）
texRECT proj(samplerRECT tex, float3 sq)	二维投影矩形纹理查询（OpenGL独有）
texRECT proj(samplerRECT tex, float3 szq)	二维投影矩形纹理深度比较查询（OpenGL独有）
Tex3D(sampler3D tex, float s)	三维纹理查询
Tex3D(sampler3D tex, float3 s, float3 dsdx, float3 dsdy)	结合导数值（derivatives）查询三维纹理
Tex3Dproj(sampler3D tex, float4 szq)	查询三维投影纹理，并进行深度值比较
texCUBE(samplerCUBE tex, float3 s)	查询立方体纹理
texCUBE (samplerCUBE tex, float3 s, float3 dsdx, float3 dsdy)	结合导数值（derivatives）查询立方体纹理
texCUBEproj (samplerCUBE tex, float4 sq)	查询投影立方体纹理



4.偏导数函数(Derivative Functions)
ddx(a)	近似a关于屏幕空间x轴的偏导数
ddy(a)	近似a关于屏幕空间y轴的偏导数



5.调试函数(Debugging Function)
void debug(float4 x)	如果在编译时设置了DEBUG，片段着 色程序中调用该函数可以将值x作为COLOR语义的最终输出；否则该函数什么也不做。

//本视频看至p14 后续内容都有学过不再赘述笔记内容