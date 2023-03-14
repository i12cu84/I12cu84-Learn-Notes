using UnityEngine;
using System.Collections;
//镜头缩放
public class CareamZoom:MonoBehaviour
{
    public bool isDown;
    private void Update1()
    {
        //捕捉鼠标按下方法
        isDown=Input.GetMouseButton(0);
        // isDown=Input.GetMouseButtonDown(0);
        // isDown=Input.GetMouseButtonUp(0);
        //捕捉键盘按下方法 检测按下C同时按D 检测一遍
        if(Input.GetKey(KeyCode.C)&& Input.GetKeyDown(KeyCode.D))
        {
            print("CD");
        }
    }
    //瞄准镜 实现镜头缩放
    //1.按下镜头拉近 再次按下拉远 (设置Camera的FOV属性
    //2.逐渐的拉近
    //3.缩放等级经常变化
    private Camera camera;
    private void Start()
    {
        camera=GetComponent<Camera>();
    }
    private bool isFar=true;
    private void Update2()
    {
        if(Input.GetMouseButtonDown(1))
        {
            isFar=!isFar//默认时60
            if(isFar)   //拉远60
                camera.fieldOfView=60;
            else        //拉近20
                camera.fieldOfView=20;
        }
    }
    private void Update3()
    {
        if(Input.GetMouseButtonDown(1))
        {
            //按时执行1帧
            isFar=!isFar//默认时60
        }
        //每帧执行
        if(isFar)//拉远20 -> 60
        {
            if(camera.fieldOfView<60)
                camera.fieldOfView+=2;
        }
        else     //拉近60 -> 20
        {
            if(camera.fieldOfView>20)
                camera.fieldOfView-=20;
        }
    }
    private void Update4()
    {
        if(Input.GetMouseButtonDown(1))
        {
            //按时执行1帧
            isFar=!isFar//默认时60
        }
        //每帧执行
        if(isFar)//拉远20 -> 60
        {   //加速度,由快到慢,无限接近终点(不可能等于终点) Lerp(起点,终点,比例) 0.1f每次取10%
            camera.fieldOfView=Mathf.Lerp(camera.fieldOfView,60,0.1f);
            if(Mathf.Abs(camera.fieldOfView-60)<0.1f)
                camera.fieldOfView=60;
        }
        else     //拉近60 -> 20
        {
            camera.fieldOfView=Mathf.Lerp(camera.fieldOfView,20,0.1f);
            if(Mathf.Abs(camera.fieldOfView-20)<0.1f)
                camera.fieldOfView=20;
        }
    }
    public  float[] zoomLevel;//在unity引擎中设置层级
    private int index;
    private void Update()
    {
        if(Input.GetMouseButtonDown(1))
            // index=index<zoomLevel.Length-1?index++,0;//回到原点
            index=(index+1)%zoomLevel.Length;//取余方式简化过程
        camera.fieldOfView=Mathf.Lerp(camera.fieldOfView,zommLevel[index],0.1f);
        if(Mathf.Abs(camera.fieldOfView-zommLevel[index])<0.1f)
            camera.fieldOfView=zommLevel[index];
    }
}
public class DoRotation:MonoBehaviour
{
    //鼠标键盘输入的用法
    public float hor;
    private void Update1()
    {
        //按W往前走
        if(Input.GetKey(KeyCode.W))
            this.transform.Translate(0,0,10*Time.deltaTime);
        //玩家希望可以自定义按键
        //虚拟按钮  Vertical 真实按键 w s
        //InputManger 其中定义一个Name
        //a ← 返回-1   d → 返回1  不按 返回0
        hor=Input.GetAxis("Horizontal");
        // Input.GetButton("");
    }
    //控制摄像机随鼠标移动而旋转
    public float rotateSpeed=1;
    private void FixedUpdate()
    {
        //鼠标左右移动
        float x=Input.GetAxis("Mouse X");//鼠标移动 返回的x -> 往左是负 往右是正 不动是0
        float y=Input.GetAxis("Mouse y");//鼠标移动 返回的y -> 往下是负 往上是正 不动是0
        if(x!=0 || y!=0)//如果移动了
            RotateView(x,y);//旋转函数
    }
    private void RotateView(float x,float y)
    {
        x*=rotateSpeed;//用于调整速度
        y*=rotateSpeed;
        //沿y轴旋转 沿自身
        this.transform.Rotate(-y,0,0);
        //沿世界旋转
        this.transform.Rotate(0,x,0,Space.World);
    }
}
//上下左右移动
public class PlayerController:MonoBehaviour
{
    private void Update()
    {
        float hor=Input.GetAxis("Horizontal");//InputManager中的Name -> Horizontal
        float ver=Input.GetAxis("Vertical");
        if(hor!=0 || ver!=0);
            Movement(hor,ver);
    }
    public float moveSpeed=10;
    private void Movement()
    {
        hor*=moveSpeed*Time.deltaTime;  
        ver*=moveSpeed*Time.deltaTime;
        this.transform.Translate(hor,0,ver);
    }
}
//3D数学
public class VectorDemo:MonoBehaviour
{
    private void Update()
    {
        
    }
    //有关模长计算
    private void Demo01()
    {
        Vector3 pos=this.transform.position;
        float m01=Mathf.Sqrt(Mathf.Pow(pos.x,2)+Mathf.Pow(pos.y,2)+Mathf.Pow(pos.z,2));
        float m02=pos.magnitude;
        float m03=Vector3.Distance(Vector3.zero,pos);//三者相同效果
        Debug.LogFormat("{0}--{1}--{2}",m01,m02,m03);//输出验证
        Debug.DrawLine(Vector3.zero,pos);
    }
    //方向 获取向量方向 (单位向量
    private void Demo02()
    {
        Vector3 pos=this.transform.position;
        Vector3 n01=pos/pos.magnitude;
        Vector3 n03=pos.normalized;
        Debug.DrawLine(Vector3,zero,pos);
    }
    //向量计算
    public Transform t1,t2,t3;
    private void Demo03()
    {
        Vector3 relativeDirection=t1.position-t2.position;
        //方向t2->t1 大小终点间距 位置坐标原点
        //t3沿着relativeDirection方向移动
        if(Input.GetKey(KeyCode.A))//按A启动
        {
            //relativeDirection.normalized:获取方向避免两个物体间距对速度有影响
            // t3.Translate(relativeDirection);
            t3.position=t3.position+relativeDirection.normalized;//同上一行
            //相加->两个向量对角线
        }
        Debug.DrawLine(Vector3.zero,relativeDirection);
    }
    //向量乘法
    private void Demo04()
    {
        Vector3 vect=new Vector3();
        vect=vect/2;
        vect=2/vect;
        //向量点乘
        float dot=Vector3.Dot(t1.position.normalized,t2.position.normalized);//计算内角夹角
        float angle=Mathf.Acos(dot)*Mathf.Rad2Deg;
        if(angle>60)
            1;//如果两个向量夹角大于60则...
        //向量叉乘
        Vector3 corss=Vector3.Cross(t1.position,t2.position);
        //计算一圈夹角
        if(cross.y<0)
            angle=360-angle;
        Debug.DrawLine(Vector3.zero,cross,Color.red);
        // this.transform.forward;//物体的在世界的坐标
        // this.transform.right;
        // this.transform.up;
    }
}
//角度、弧度转换
public class Trigonometric:MonoBehaviour
{
    private void Start()
    {
        Demo01();
    }
    private void Demo01()
    {
        //角度->弧度
        float d1=60;
        float r1=d1*Mathf.PI/180;
        float r2=d1*Mathf.Deg2Rad;
        print(r1+"--"+r2);
        //弧度->角度
        float r1=3;
        float d1=r1*180/Mathf.PI;
        float d2=r1*Mathf.Rad2Deg;
        print(d1+"--"+d2);
    }
    private void Demo02()
    {
        float x=50,b=20;
        //a=tanx * b
        float a=Mathf.Tan(x*Mathf.Deeg2Rad)*b;
        /angle=arc tan a/b
        float angle=Mathf.Atan(a/b)*Mathf.Rad2Deg;//atan->弧度
    }
    private void Demo03()
    {
        //从自身坐标系转换到世界坐标系中
        //自身坐标系:原点物体的轴心点
        // Vector3 worldPoint=transform.TransformPoint(0,0,10);
        //计算物体右前方30度10米
        float x=Mathf.Sin(30*Mathf.Deg2Rad)*10;
        float z=Mathf.Cos(30*Mathf.Deg2Rad)*10;
        Vector3 worldPoint=transform.TransformPoint(x,0,z);
        Debug.DrawLine(this.transform.position,worldPoint);
    }
}
//欧拉角 无法完全伸展旋转 方便好使 但是表达方式不唯一
public class EulerDemo:MonoBehaviour
{
    //万向节死锁
    public Vector3 euler;
    private void OnGUI()
    {
        euler=this.transform.eulerAngles;
        if(GUILayout.RepeatButton("沿x轴旋转"))
        {
            //欧拉角没有方向大小的概念
            //因为3为向量包含xyz 所以类型为Vector3
            //欧拉角xyz表示各个轴向上的旋转角度
            Vector3 euler=this.transform.eulerAngles;
            //位置 有方向和大小
            //向量的xyz表示各个轴向上的有向位移
            Vector3 pos=this.transform.position;
        }
        if(GUILayout.RepeatButton("沿y轴旋转"))
        {
            // this.transform.eulerAngles+=new Vector3(0,1,0);
            this.transform.eulerAngles+=Vector3.up;
        }
        if(GUILayout.RepeatButton("沿z轴旋转"))
        {
            // this.transform.eulerAngles+=new Vector3(0,0,1);
            this.transform.eulerAngles+=Vector3.forward;
        }
    }
}
//四元数 可以避免万向节死锁 但是难使
public class QuaternionDemo:MonoBehaviour
{
    private Vector3 vect;
    // private void Start()
    // {
    //     vect=new Vector3(0,0,10);
    // }
    private void OnGUI()
    {
        if(GUILayout.Button("设置物体旋转角度"))
        {
            //旋转轴
            Vector3 axix=Vector3.up;
            //旋转弧度
            float rad=50*Mathf.Deg2Rad;
            Quaternion qt=new Quaternion();
            qt.x=Mathf.Sin(rad/2)*axis.x;
            qt.y=Mathf.Sin(rad/2)*axis.y;
            qt.z=Mathf.Sin(rad/2)*axis.z;
            qt.w=Mathf.Cos(rad/2);
            this.transform.rotation=qt;
            //欧拉角->四元数
            this.transform.rotation=Quaternion.Euler(0,50,0);
        }
        if(GUILayout.RepeatButton("沿x轴旋转"))
        {
            this.transform.rotation*=Quaternion.Euler(1,0,0);
        }
        if(GUILayout.RepeatButton("沿y轴旋转"))
        {
            this.transform.rotation*=Quaternion.Euler(0,1,0);
        }
        if(GUILayout.RepeatButton("沿z轴旋转"))
        {
            this.transform.rotation*=Quaternion.Euler(0,0,1);
        }
    }
    private void Update()
    {
        Debug.DrawLine(this.transform.position,vect)
        // if(GUILayout.RepeatButton("计算右前方30度10m处坐标"))
        if(Input.GetMouseButtonDown(0))
        {
            //0 0 10 向量根据当前物体旋转而旋转
            vect=this.transform.rotation*new Vector3(0,0,10);
            //vect 向量 沿y轴旋转30度
            vect=Quaternion.Euler(0,30,0)*vect;
            //vect 向量 移动到当前物体位置
            vect=this.transform.position+vect;
            // vect=this.transform.position+Quaternion Euler(0,30,0)*this.transform.rotation*new Vector3(0,0,10);
        }
    }
}
//切线检测
public class TangentDetection:MonoBehaviour
{
    public string playerTag="Player";
    private Transform playerTF;
    private float radius;
    private void Start()
    {
        GameObject playerGO=GameObject.FindWithTag(playerTag);
        plyaerTF=playerGO.transform;
        radius=playerGO.GetComponent<CapuleCollider>().radius;
    }
    //计算切点
    private Vector3 leftTangent,rightTangent;
    private void CalculateTangent()
    {
        Vector3 playerToExplosion=this.transform.position-playerTF.position;
        Vector3 playerToExplosionDirection=playerToExplosion.normalized*radius;
        float angle=Mathf.Acos(radius/playerToExplosion.magnitude)*Mathf.Rad2Deg;
        // leftTangent=Quaternion.Euler(0,-angle,0)*playerToExplosionDirection;
        // rightTangent=Quaternion.Euler(0,angle,0)*playerToExplosionDirection;
        //加上玩家的位置才能跟随玩家的位置而动
        leftTangent=playerTF.position+Quaternion.Euler(0,-angle,0)*playerToExplosionDirection;
        rightTangent=playerTF.position+Quaternion.Euler(0,angle,0)*playerToExplosionDirection;
    }
    public void Detection()
    {
        CalculateTangent();
        Debug.DrawLine(this.transform.position,leftTangent);
        Debug.DrawLine(this.transform.position,rightTangent);
    }
    private void Update()
    {
        Detection();
    }
}
//
public class VectorAPIDmoe:MonoBehaviour
{
    public Transform t1;
    public Vector3 planeNorm;
    private void Update()
    {
        // Vector3 vect=new Vector3(0,0,10);
        // Vector3 norm=vect.normalized;// 0 0 1
        // vect.Normalize();//             -> 0 0 1
        Vector3 resule=Vector3.ProjectOnPlane(t1.position,planeNorm);
        Debug.DrawLine(Vector3.zero,result,Color.red);
        Debug.DrawLine(Vector3.zero,t1.position);
    }
    public AnimationCurve curve;
    private float x;
    //设置持续时间
    public float duration=1;
    private Vector3 targetPos=new Vector3(0,0,10);
    //移动
    private void OnGUI()
    {
        if(GUILayout.RepeatButton("MoveTowards"))
        {
            //将当前物体移动到 0 0 10位置
            //匀速移动到达目标点
            this.transform.position=Vector3.MoveTowards(this.transform.position,targetPos,0.1f);  
        }
        if(GUILayout.RepeatButton("Lerp"))
        {
            //将当前物体移动到 0 0 10位置
            //先快到慢 不能打到目标点 无限接近 
            //终点 与 比例固定
            this.transform.position=Vector3.Lerp(this.transform.position,targetPos,0.1f);  
        }
        if(GUILayout.RepeatButton("LerpUnclamped"))
        {
            x+=Time.deltaTime/duration;//duration设置持续时间
            //自然运动 起点固定 终点固定 比例根据曲线变化
            this.transform.position=Vector3.LerpUnclamped(Vector3.zero,targetPos,curve.Evaluate(x));  
        }
    }
}
public class QuaternionAPIDemo:MonoBehaviour
{
    private void OnGUI()
    {
        if(GUILayout.Button("转"))
        {
            //1.欧拉角->四元数
            Quaternion.Euler(欧拉角)
            //2.四元数->欧拉角
            Quaternion qt=this.transform.rotation;
            Vector3 euler=qt.eulerAngles;
            //3.轴 角 y轴旋转50度
            this.transform.rotation=Quaternion.AngleAxis(50,Vector3.up);
            // Quaternion.Euler(0,50,0); //同一写法 
        }
        if(GUILayout.Button("直接转向"))
        {
            //z轴指向一个方向
            //当前物体注视tf旋转
            //this.transform.position看着tf.position
            Vector3 dir=tf.posotion-this.transform.position;//末-初
            //4.当前物体注视tf旋转
            this.transform.rotation=Quaternion.LookRotation(dir);
            //this.transform.LookAt(tf);//同一个功能
        }
        if(GUILayout.RepeatButton("RotateTowards"))
        {
            Quaternion dir=Quaternion.LookRotation(tf.posotion-this.transform.position);//末-初
            //5.差值旋转 Lerp
            // this.transform.rotation=Quaternion.Lerp(this.transform.rotation,dir,0.1f);//加速朝向
            //6.匀速旋转
            this.transform.rotation=Quaternion.RotateTowards(this.transform.rotation,dir,0.1f);//匀速朝向
        }
        if(GUILayout.RepeatButton("RotateTowards"))
        {
            Quaternion dir=Quaternion.Euler(0,90,0);
            this.transform.rotation=Quaternion.Lerp(this.transform.rotation,Quaternion.Euler(0,90,0),0.1f);
            //7.如果当前旋转角度 接近目标旋转角度
            if(Quaternion.Angle(this.transform.rotation,dir)<1)//小于1度
            {
                this.transform.rotation=dir;
            }
        }
        if(GUILayout.RepeatButton("RotateTowards"))
        {
            //8.x轴注视旋转
            // this.transform.right=tf.position-this.transform.position;
            //x轴正方向->注视目标位置的方向
            Quaternion dir=Quaternion.FromToRotation(Vector3.right,tf.position-this.transform.position);
            this.transform.rotation=dir;
        }
    }
    public Transform tf;
}
//根据用户输入的方向旋转角色,并向前移动
public class CharcterMotor:MonoBehaviour
{
    public float moveSpeed=10;
    puvlic float rotateSpeed=50;
    private void Update()
    {
        float hor=Input.GetAxis("Horizontal");
        float ver=Input.GetAxis("Vertical");
        if(hor!=0 || ver!=0)
            MovementRotateion(hor,ver);
    }
    private void MovementRotateion(float hor,float ver)
    {
        Quaternion dir=Quaternion.LookRotation(new Vector3(hor,0,ver));
        this.transform.rotation=Quaternion.Lerp(this.transform.rotation,dir,Time.deltaTime*rotateSpeed);
        this.transform.Translate*(0,0,Time.deltaTime*moveSpeed);
    }
}
//限制移动屏幕以内(小飞机飞行为例)
public class PlayerController:MonoBehaviour
{
    private Camera mainCamera;
    private void Start()//重复引用放start里
    {
        mainCamera=Camera.main;
    }
    private void Update()//里面尽量少写内容
    {
        float hor=Input.GetAxis("Horizontal");
        float ver=Input.GetAxis("Vertical");
        if(hor!=0 || ver!=0)
            Movement(hor,ver);
    }
    public float moveSpeed=10;
    public Vector3 local;
    private void Movement(float hor,float ver)//移动
    {
        hor*=moveSpeed*Time.deltaTime;
        ver*=moveSpeed*Time.deltaTime;
        //判断物体的屏幕坐标
        //世界坐标转换为屏幕坐标
        Vector3 screenPoint=mainCamera.WorldToScreenPoint(this.transform.position);
        //限制
        //如果超过屏幕,停止运动 
        //举例:左右停止
        if((screenPoint.x<=0 && hor<0 )||(screenPoint.x>=Screen.width&&hor>0))//最左 && 向左 || 最右 && 向右
            hor=0;
        //举例:上出 下进  | 下出 上进
        if(screenPoint.y>Screen.height)
            screenPoint=0;
        if(screenPoint.y<Screen.height)
            screenPoint=Screen.height0;
        this.transform.position=mainCamera.ScreenToWorldPoint(screenPoint);
        this.transform.Translate(hor,0,ver);
    }
}
//物理引擎 Rightbody + 碰撞器 Collider(Box Collider性能用的少/Mesh Collider效果好)
//Mass 质量 Drag 阻力 Angular Drag 角阻力 Interpolate 插值  Collision Detection 碰撞检测 Use Gravity 重力 Is Kinematic 运动刚体
//碰撞接触状态
public class Bullet:MonoBehaviour
{
    //当满足碰撞条件
    //接触的第一帧执行
    private void OnCollisionEnter(Collision other)//参数随意
    {
        //事件参数类
        //other:获取对方碰撞器组件other.collider.GetConponent<?>()
        //获取第一个接触点
        ContactPoint cp=other.contacts[0];
        // cp.point接触点的世界坐标
        // cp.nromal接触面法线
        print("OnCollisionEnter--"+other.collider.name);//输出了碰撞到组件的名字
    }
    //当满足除法条件
    //接触的第一帧执行
    //碰撞触发3条件 有碰撞组件 其中有刚体组件 其中勾选isTrigger
    private void OnTriggerEnter(Collider other)//参数随意
    {
        //事件参数类
        //other:获取对方碰撞器组件other.GetConponent<?>()
        print("OnTriggerEnter--"+other.name);//输出了碰撞到组件的名字
    }
    public float moveSpeed=50;
    //固定更新 每次物理引擎碰撞接触时更新
    private void FixedUpdate()
    {
        //帧数+位置
        Debug.Log(Time.frameCount+"--"+this.transform.position);
        this.transform.Translate(0,0,Time.deltaTime*moveSpeed);
    }
    public LayerMask mask;
    //目标位置
    private Vector3 targetPos;
    //如果物体移动速度过快,碰撞检测将会失效
    //解决方案:在开始时,使用射线检测
    private void Start()
    {
        //重载10
        RaycastHit hit;
        //(起点坐标,方向,受击物体信息,举例,?)
        if(Physics.Raycast(this.transfrom.position,this.transform.forward,out hit,100,mask))
        {
            //检测到物体
            targetPos=hit.point;//击中的位置
        }
        else 
        {
            //没有检测到物体
            targetPos=this.transform.position+this.transform.forward*100;//当前位置
        }
    }
    private void Update()
    {
        this.transform.position=Vector3.MoveTowards(this.transform.position,targePos,Time.deltaTime*moveSpeed);
        if((this.transform.position-targetPos).sqrMagnitude<0.1f)//靠近判断
        {
            print("接触目标点");
            Destroy(this.gameObject);//销毁子弹
        }
    }
}
//武器模块
[RequireComponent(typeof(AudioSource))]
public class Gun:MonoBehaviour
{
    private AudioSource audioSource;
    //发射子弹时的音频片段
    public AudioClip clip;
    //为子类提供重写Start方法的机会
    protected virtual void Start()
    {
        print("Gun--Start");
    }
    //开火              子弹朝向
    public void Firing(Vector3 direction)
    {
        //玩家枪发射:枪口方向
        //敌人反射:从枪口位置朝向玩家头部位置
        //
        //准备子弹
        //判断弹匣内是否包含子弹

        //发射子弹
        //创建子弹 播放音频
        audioSouce.PlayOneShot(clip);
    }
    //弹夹容量

    //当前弹匣内子弹数15

    //剩余子弹数90

    //更换弹夹
    public void UpdateAmmo()
    {
        
    }
}
//单发枪,附加到枪物体中
public class SingleGun:Gun
{
    // //覆盖父类的start
    // private void Start()
    // {
    //     print("SingleGun--Start");
    // }
    //vs技巧:override+空格 选择Start
    //调用父类的Start的方法
    protected override void Start()
    {
        base.Start();//父类的基础上
        print("SingleGun--Start");
    }
    private void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            //base.Firing(枪口方向)'
        }
    }
}
//连发枪
public class AutomaticGun:Gun
{
    //略
}
//子弹 定义子弹共有行为
public class Bullet:MonoBehaviour
{
    protected RaycastHit hit;
    //计算目标点
    //移动
    //到达目标点:销毁 创建相关特效
    //创建相关特效
    //根据目标点物体的标签hit.collider.tag
    private void GenerateContactEffect()
    {
        //通过代码读取资源
        //资源必须放到Resources目录下 ContactEffects/xxx
        GameObject prefabGO=Resources.Load<GameObject>("目录/资源名称");
        //创建资源
        Instantiate(prefabGO);
    }
}
//玩家子弹
public class PlayerBullet:MonoBehaviour
{
    //根据敌人部位减血
    //希望到达物体上再减血,需要使用委托
    private void Start()
    {
        // base.hit.collider.name 击中部位的名称
    }
}
//敌人子弹
public class EnemyBullet:Bullet
{
    private void OnTriggerEnter(Collider other)
    {
        //如果与玩家接触
        //玩家减血
    }
}
//Physic Material 动态摩擦力 静态摩擦力 弹力