
public class Lifecycle:MoniBehaviour//没有这个父类 不能用print
{
    //脚本:.cs的文本文件 类文件
    //  附加到游戏物体中,定义游戏对象行为指令的代码

    // c#逻辑类:
    // 字段
    // 属性
    // 构造函数
    // 方法

    //脚本:
    //字段
    //方法
    
    [SerializeField]//序列化字段 作用:在编辑器中显示私有变量
    private int a=100;//编译编译器看不到,以上设置可以看到

    [HideInInspector]//在编译器中隐藏字段
    public int b=200;//编译器可以直接看到

    [Range(0,100)]//限制更改范围
    public int c;//可以看到也可以设置值
    

    public int A
    {
        get
        {
            return this.a;
        }
        set
        {
            this.a=value;
        }
    }

    public Lifecycle()
    {
        Debug.Log("构造函数");
        //不要在脚本中写构造函数
        //不能在子线程中访问主线程成员
        //b=Time.time;
    }

    //private int d=Random.Range(1,101);会出错
    //*************初始阶段*************
    //执行时机:创建游戏对象 立即执行 早于 Start
    //作用:初始化
    private void Awake()
    {
        Debug.Log("Awake--"+Time.time+"--"+this.name);
    }

    //执行时机:创建游戏对象 脚本启用 才执行 (1次)
    //作用:初始化
    private void Start()
    {
        Debug.Log("Awake--"+Time.time+"--"+this.name);
    }
    //*************物理阶段*************
    //执行时机:每隔固定时间执行1次
    //适用性:适合对物体做物理操作(移动、旋转),不会受到渲染影响
    private void FixedUpdate()//默认0.02s,即更新频率,不建议更改
    {//渲染时间不固定(每帧渲染物体量不同、机器性能不同)
        Debug.Log(Time.time);
    }
    //执行时机:鼠标按下,需要拥有封装器,物理编译器"Box Collider" 输入事件
    //OnMouseEnter  鼠标移入
    //OnMouseOver   鼠标经过
    //OnMouseExit   鼠标离开
    //OnmouseUp     鼠标抬起
    private void OnMouseDown()
    {
        Debug.Log("OnMouseDown");
    }
    //执行时机:渲染帧执行,执行间隔不固定(更好)
    //适用性:处理游戏逻辑
    //*************游戏逻辑*************
    private void Update()
    {

    }
    //执行时机:渲染帧执行,执行间隔不固定(更好)在Update之后,但在同一帧内
    //适用性:处理游戏逻辑
    private void LateUpdate()
    {

    }
    //当前可见 当Mesh Renderer 在任何相机上可见时调用
    private void OnBecameVisible()
    {

    }
    //当前不可见 当Mesh Renderer 在任何相机上都不可见时调用
    private void OnBecameInvisible()
    {

    }
    //*************结束阶段************
    //对象变为不可用或附庸游戏对象非激活状态时此函数调用
    private void OnDisable()
    {

    }
    //当脚本销毁或附属的游戏对象被销毁时被调用
    private void OnDestroy()
    {

    }
    //当程序结束 应用程序退出时被调用
    private void OnApplicationQuit()
    {

    }
    
    //控制台调试 记得测完删掉,慎用
    //Debug.Log("变量"); 随时能用
    //print(变量); 要继承MoniBehaviour才能用,仅脚本适用           选中按F12可以溯源
    //Console控制台操作:clear 清除 collapse 折叠相同项 
    //                 clear on play 运行时清空(不选则会累加) error pause 出错暂停
    //Librayy ScriptAssemblies Assembly-CSharp.dll拖到ILSpy发编译工具 可以看到脚本
    // private void Update()
    // {
    //     //输出各种办法测试
    // }

    //用VS调试
    //断点测试 F11下一步 右键 快速监视、左下角即时窗口
    //单帧调试:启动调试 运行场景 暂停游戏 加断点 单帧执行 结束调试
}
//Component类提供了查找在当前物体自身、后代、先辈组件的功能
public class ComponentDemo:MOnoBehaviour
{
    public void OnGUI()
    {
        if(GUILayout.Button("按钮"))
        {
            print("ok");//用于测试
            //屏幕左上角会出现一个按钮 点一下会显示ok
            //this.camera [Obsolete]否决的 被废弃掉的
            this.transform.position=new Vector3(0,0,10);
            //this指Componet transform指所选区 position指类型
            this.GetComponent<MeshRenderer>().material.color=Color.red;(颜色) 颜色类型
            //GerComponent 返回组件
            var allComponent=this.GetComponents<Component>();
            foreach(var item in allComponent)
            {
                Debug.Log(item.GetType());
            }
            //获取当前物体所有组件
        }
        
        if(GUILayout.Button("GetComponents"))
        {//获取后代物体的指定类型组件,从自身开始以深搜方式
            var allComponent=this.GetComponentsInChildren<MeshRenderer>();
            foreach(var item in allComponent)
            {
                item.material.color=Color.red;//变成红色
            }
        }
    }
}
//Transform类提供了查找父根子变换改变的功能
public class TransformDemo:MonoBehaviour
{
    public Transform tf;
    private void OnGUI()
    {
        if(GUILayout.Button("foreach -- transform"))
        {
            foreach(Transform child in transform)
            {
                print(child.name);
                //child 为每个子物体的变换组件
                //child.position+=Vector3.up*10.0F;
            }
        }
        if(GUILayout.Button("foreach -- transform"))
        {
            //物体相对于世界坐标系原点的位置
            this.transform.position
            //物体相对于父物体轴心点位置  即相对位置
            this.transform.localPosition
            //物体与模型缩放比例 只可读
            this.transform.lossyScale
            //相对于父物体缩放比例 可读写
            this.transform.localScale
        }
        if(GUILayout.Button("pos/scale"))
        {
            //向自身坐标系 z轴移动1米
            this.transform.Translate(0,0,1);
            //向世界坐标系 z轴移动1米
            this.transform.Translate(0,0,1,Space.World);
            //沿自身坐标系 y轴旋转 10度
            this.transform.Rotate(0,10,0);
            //沿世界坐标系 y轴旋转 10度
            this.transform.Rotate(0,10,0,Space.World);
        }
        if(GUILayout.RepeatButton("RotateAround"))//重复按着
        {
            this.transform.RotateAround(Vector3.zero.Vector3.up,1);//y轴一次转1度
            this.transform.RotateAround(Vector3.zero.Vector3.forward,1);//z轴一次转1度
            //获取根物体变换组件
            Transfom rootTF=this.transform.root;
            //获取父物体变换组件    
            Transfom rootTF=this.transform.parent;
            //设置父物体 物体位置世界坐标
            this.transform.SetParent(tf);
            //设置父物体 物体位置自身坐标
            this.transform.SetParent(tf,false);
            //根据名称获取子物体
            Transform childTF = this.tansform.Find("子物体名称");
            //
            this.transform.GetChild();
        }
        if(GUILayout.Button("Find"))
        {
            //根据索引搜索子物体
            int count=this.transform.childCount;
            for(int i=0;i<count;i++)
            {
                Transform childTF=this.transform.GetChild(i);
            }
        }
    }
}

public class GameObjectDemo:MonoBehaviour
{
    private void OnGUI()
    {
        //在场景中物体激活状态(物体时机激活状态)
        this.gameObject.activeInHierarchy;
        //物体自身激活状态(物体时机激活状态)
        this.gameObject.activeSelf;
        //设置物体启用\禁用
        this.gameObject.SetActive();
        if(GUILayout.Button("添加光源"))
        {
            //Light light=new Light();
            //创建物体
            GameObject lightGO=new GameObject();
            //添加组件
            Light light=this.gameObject.AddComponent<Light>();
            light.color=Color.red;
            light.type=LightType.Point;//创建了点光源
        }
        //在场景中根据名称查找物体(慎用)
        //GameObject.Find("游戏对象名称")
        //获取所有使用该标签的物体
        GameObject[] allEnemy =GameObject.FindGameObjectsWithTag("Enemy");
        //获取使用该标签的物体(单个)
        GameObject playerGO =GameObject.FindWithTag("Player");
        //根据类型查找对象
        Object.FindObjectOfType<MeshRenderer>();
        FindObjectsOFType<MeshRenderer>();
        //销毁对象
        Object.Destroy;
        Destroy(gameObject,5);//5秒后销毁对象

    }
}
//练习:找到组件中血量最低的对象
public class Enemy:MonoBehaciour
{
    public float HP;
}
public class FindEnemyDemo:MonoBehaviour
{   
    private void OnGUI()
    {
        if(GUILayout.Button("查找血量最低的敌人"))
        {
            //查找场景中所有Enemy类型的引用
            Enemy[] allEnemy=object.FindObjectsOfType<Enemy>();
            //获取血量最低的对象引用
            Enemy min=FindEnemyByMinHP(allEnemy);
            //根据Enemy类型引用 获取其他组件类型引用
            min.GetComponent<MeshRenderer>().material.color=Color.red;
        }
    }
    public Enemy FindEnemyByMinHP(Enemy[] allEnemy)
    {
        //假设第一就是血量最低的敌人
        Enemy min=allEnemy[0];
        //一次与后面比较
        for(int i=1;i<allEnemy.Length;i++)
        {
            if(min.HP>allEnemy[i].HP)
                min=allEnemy[i];
        }
        return min;
    }
}
//利用递归在层级未知的情况下查找子物体:变换组件助手类
public class TransformHelper
{   
    //父物体名称,子物体名称
    public static Transform GetChild(Transform parentTF,string childName)
    {
        //在子物体中查找
        Transform childTF=parentTF.Find(childName);
        if(childTF!=null)return childTF;//如果找到
        //将问题交由子物体 递归
        int count=parentTF.childCount;
        for(int i=0;i<count;i++)
        {
            GetChild(parentTF.GetChild(0),childName);
            if(childTF!=null)
                return childTF;
        }
        return null;//没找到
    }
}
//设置控件
if(GUILayout.Button("层级未知,查找子物体"))
{
    var childTF=TransformHelper.GetChild(this.transform,"Cube(5)");
    childTF.GetComponent<MeshRenderer>().material.color=Color.red;
}
//查找最近的敌人 float distance =Vector3.Distance(物体1位置,物体2位置);
using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class Enemy:MonoBehaviour
{
    public float HP;
}
public class TimeDemo:MnonoBehaviour
{
    public float t;
    //渲染场景时执行
    public void Update()
    {
        //t=Time.time;
        //每渲染帧 执行一次 旋转1度 帧多旋转快(性能有关)
        this.transform.Rotate(0,1,0);
        //旋转速度不受机器性能 渲染影响(性能无关)
        this.transform.Rotate(0,1*Time.deltaTime,0);
        //不受Uncale暂停影响
        this.transform.Rotate(0,1*Time.unscaledDeltaTime,0);

    }
    //每0.02s执行一次,与渲染无关,受TimeScale影响
    public void FixedUpdate()
    {
        this.transform.Rotate(0,1,0);
    }
    //游戏暂停 个别物体不受影响
    public void OnGUI()
    {
        if(GUILayout.Button("暂停游戏"))
        {
            Time.timeScale=0;//暂停时FixedUpdate不会运行
        }
        if(GUILayout.Button("继续游戏"))
        {
            Time.timeScale=1;
        }
    }

}
public class CountdownTimer:MonoBehaviour
{
    //UnityEngine.UI.Text
    //int second =120;
    //02:00 -> 01:59
    //Update中1秒修改1次
    //需求1秒修改一次Text文本内容
    //查找组件引用
    //定义变量 秒
    //秒 -> 时间格式
    //修改文本
    private Text txtTimer;
    public int second=120;
    private void Start()
    {
        //重点,建立一个对象
        txtTimer=this.GetComponent<Text>();
        //Timer();
        //重复调用(被执行方法名称,第一次执行时间,每次执行间隔)
        InvokeRepeating("Timer3".1,1);//1s调用一次
        // Invoke(被执行的方法,开始调用时间);//延迟一段时间执行
    }
    //如何每秒修改一次
    //重点:在Update每帧执行的方法中.个别语句实现指定间隔执行一次
    //方法一:Time.time 先动
    private float nextTime=1;//下次修改时间
    private void Update()
    {
        Timer1();
        Timer2();
        Timer3();
    }
    private void Timer1()
    {
        //如果到了修改时间
        if(Time.time>nextTime)
        { 
            second--;
            textTimer.text=string.Format("{0:d2}:{1:d2}",second/60 second%60);//d2 以0填充
            //变红
            if(second<=10)
                txtTimer.color=Color.red;
            nextTime=Time.time+1;
        }
    }
    //方法二:Time.deltaTime 等一下再动
    private float totalTime;//累计时间
    private void Timer2()
    {
        //累加每帧间隔
        totalTime+=Time.deltaTime;
        if(totalTime>=1)
        {
            second--;
            textTimer.text=string.Format("{0:d2}:{1:d2}",second/60 second%60);//d2 以0填充
            totalTime=0;
        }
    }
    //方法三:Invoke 适合做简单 重复 每隔固定时间 重复执行
    private void Timer3()
    {
        second--;
        textTimer.text=string.Format("{0:d2}:{1:d2}",second/60 second%60);//d2 以0填充
        if(second<=0)
        {
            //取消调用
            Cancellnvoke("Timer");//这个方法不执行
        }
    }
}
//组件动画
//ctrl+6 = ->window ->animation
//选中组件 -> add component -> animation -> create 创建物理文件(.anim) -> 保存
//选中物理文件 -> add property 添加组件 -> 时间线 1:30 1秒和30帧
//选末置位时间点 在这个时间点时 更改物体状态 -> 将会自动补全动画
public class Door:MonoBehaviour
{
    private bool doorState=false;//门状态
    public string animName="Door";//"Door"是一个动画的文件名
    private Animation anim;
    private void Start()
    {
        anim=GetConponent<Animation>();
    }
    //点击当前物体时执行
    private void OnMouseDown()
    {
        if(!doorState)
        {
            //开门操作 0 -> 1
            anim[animName].speed=1;//"Door"是一个动画的文件名
        }
        else
        {
            //关门操作 1 -> 0
            anim[animName].speed=-1;
            if(anim.isPlaying==false)
            { 
                //从最后开始
                anim[animName].time=anim[animName].length;//要从1到0
            }
            //倒着播放
            anim[animName].time=-1;//要从1到0
        }
        anim.Play(animName);
        doorState=!doorState;
        //"Door"文件 Wrap Mode状态设置 -> Once 一次 / Loop 循环 / Ping Pong 头到尾反复 / Clamp Forever 不动
    }
}
//目标:查找最近的敌人 工程文件:basescript
//调用按钮
if(GUILayout.Button("查找最近的敌人"))
{
    Enemy[] allEnemy=FindObjectsOFType<Enemy>();
    Enemy min=FindEnemyByMinDistance(allEnemy);
    //找到标红
    min.GetComponent<MeshRenderer>().material.color=Color.red;
}
//Enemy 类有HP数据一个属性
public Enemy FindEnemyByMinDistance(Enemy[] allEnemy)
{
    private Camera my_camera;//自己做一个上机
    // private Transform myTransform;
    private void Start()
    {
        // 以前unity4 的方法
        // myCamera=this.camera;
        // 现在unity5 的方法
        myCamera=this.GetComponent<Camera>();
        //能不每帧去做,就不要每帧去做
        // myTransform=this.transform;
    }
    //假设第一个元素就是距离最近的
    Enemy min=allEnemy[0];
    //minDistance中存储假设的最近的距离
    //                  三维距离 函数           position世界位置    原物体位置
    float minDistance = Vector3.Distance(this.transform.position,min.transform.position);
    for(int i=1;i<allEnemy.Length;i++)
    {
        // this.camera.FOV 以前unity4 的方法
        float new Distance=Vector3.Distance(this.transform.position,allEnemy[i].transform.position);
        if(minDistance<newDistance)
        {
            min=allEnemy[i];
            minDistance=newDistance;
        }
    }
    return min;
}

using UnityEngine;
using System.Collections;
using System.Collections.Generic;
//敌人马达 提供移动旋转寻路
public class EnemyMotor:MonoBehaviour
{
    // public Transform[] points; 变成 路线设置起来
    public WayLine line;
    //当前路点的索引 默认0
    private int currentPointIndex;
    public float moveSpeed=5;
    //向前移动
    public void MovementForward()
    {
        //略 translate
        this.transform.Translate(0,0,moveSpeed*Time.deltaTime);//ctrl+句号 -> 自动生成字段存根
    }
    //注释旋转 需要注释的目标点
    public void LookRotation(Vector3 targetPoint)
    {
        //当前物体注视目标点旋转
        this.transform.LookAt(targetPoint);
    }
    //寻路 沿路点 Vector3[] 移动
    public bool Pathfinding()
    {
        // return true;
        //需要继续寻路
        //return false; 到达终点,无需寻路
        //如果到达目标点(判断 当前位置 与 目标点间距 Vector3.Distance)
        //更新目标点(向下一个路点移动)
        //如果超过索引,则停下 false 停止寻路
        if(line==null || currentPointIndex>=line.WayPoints.Length)return false;//?==null是否没有寻路点的判断
        //朝向目标点
        LookRotation(line.WayPoints[currentPointIndex]);
        //向前移动
        MovementForward();
        //如果到达目标点
        // //浮点情况下 容易出错 因为浮点无法可能一致 if(this.transform.position==points[currentPointIndex].position)
        if(Vector3.Distance(this.transform.line.WayPoints[currentPointIndex])<0.5f)//当前位置接近于目标点
            currentPointIndex++;
        return true;//可以继续寻路
    }
    // private void Update()
    // {
    //     Pathfinding();//调用运行mod测试
    // }
}
//敌人状态信息类 定义敌人 提供受伤死亡功能
public class EnemyStatusInfo:MonoBehaviour
{
    //当前血量
    public float HP=200;
    //血量最大值
    public float maxHP=200;
    //受伤 需要扣除血量amount
    public void Damage(float amount)
    {
        //扣血
        HP-=amout;
        //血量为0时,调用死亡方法
        if(HP<=0)Death();
    }
    //敌人生成器引用
    public EnemySpawn spawn;
    //死亡延迟销毁时间
    public float deathDelay=5;
    //死亡
    public void Death()
    {
        //播放死亡动画
        var anim=GetComponent<EnemyAnimation>();
        anim.action.Play(anim.deathAnimName);
        //销毁当前物体
        Destroy(this.gameObject,deathDelay);
        // Debug.Log("挂了");
        //设置路线装填
        GetComponent<EnemyMotor>().line.IsUsable=true;
        //产生下一个敌人

    }
}
//敌人动画 定义需要播放的动画片段名称
public class EnemyAnimation:MonoBehaviour
{
    //跑步动画名称
    public string runAnimName;
    //攻击动画名称
    public string attackAnimName;
    //闲置动画名称
    public string idleAnimName;
    //死亡动画名称
    public string deathAnimName;
    //动画行为类
    public AnimationAction action;
    private void Awake()
    {
        //在这个物体的后代中存在Animation
        action=new AnimationAction(GetComponentInChildren<Animation>());
        
    }
}
//动画行为类 提供有关动画的行为
public class AnimationAction
{
    //附加在敌人模型上的动画组件引用
    private Animation anim;
    //创建动画行为类
    public animationAction(Animation anim)
    {
        this.anim=anim;
    }
    //播放动画
    public void Play(string animName)
    {
        anim.CrossFade(animName);
    }
    //判断指定动画是否正在播放     动画片段名称
    public void IsPlaying(string animName)
    {
        return anim.IsPlaying(animName);
    }
}
//敌人AI
[RequireComponent(typeof(EnemyAnimation))]//勿忘动画名称
[RequireComponent(typeof(EnemyMotor))]
[RequireComponent(typeof(EnemyStatusInfo))]
public class EnemyAI:MonoBehaviour
{
    //定义敌人状态的枚举类型
    public enum State
    {
        //攻击状态
        Attack,
        //寻路状态
        PathFinding
    }
    //当前敌人状态
    private State currentState=State.PathFinding;//初始默认寻路
    private EnemyAnimation anim;
    private EnemyMotor motor;
    private void Start()
    {
        anim=GetComponent<EnemyAnimation>();
        motor=GetComponent<EnemyMotor>();
    }
    //攻击计时器
    private float atkTimer;
    //攻击间隔
    public float atkInterval=3;
    private void Update()
    {
        //判断
        switch(currentState)
        {
            case State.PathFinding:
                PathFinding()//寻路
                break;
            case State.Attack:
                Attack();//攻击
                break;
        }
        //执行寻路
        //执行攻击
    }
    private void PathFinding()
    {
        //播放动画
        anim.action.Play(anim.runAnimName);
        //执行寻路(调用马达(motor)类中寻路方法 
        //如果寻路结束,修改状态为攻击
        if(motor.Pahtfinding()==false)currentState=State.Attack;//一直动 bool返回值 false表示寻路结束
        //播放跑步动画
        //如果寻路结束,修改状态为攻击
    }
    private void Attack()
    {
        //如果攻击动画没有播放
        if(!anim.action.IsPlaying(anim.attackAnimName))
            anim.action.Play(anim.idleAnimName);//播放闲置动画 ,同样在unity引擎中 模块的设置中输入动画名称
        if(atkTimer<=Time.time)//攻击间隔
        {
            //播放攻击动画
            anim.action.Play(anim.attackAnimName);
            //随后,在unity引擎中 将物体模块的Enemy Animation(Script)上 (p144案例)
            //将 Run Anim Name\Attack Anim Name\Idle Anim Name\Death Anim Name 右边填写动画的名称
            //发起攻击
            atkTimer=Time.time+atkInterval;
        }
    }
}
//路线类
public class WayLine
{
    //当前路线左右路点坐标
    public Vector3[] WayPoints{get;set;}
    //是否可用
    public bool IsUsable{get;set;}//默认false
    //构造函数(?)..
    public WayLine(int wayPointCount)
    {
        WayPoints=new Vector3[wayPointCount];
        IsUsable=true;
    }
}
//敌人生成器
public class EnemySpawn:MonoBehaviour
{
    //需要创建的敌人预值件数组
    public GameObject[] enemyType;
    //需要创建的敌人最大数目
    public int maxCount=5;
    //开始同时创建的敌人数目
    public int startCount=2;
    //已经创建敌人数量
    private int spawnedCount;
    //最大生成延迟随机生成时间
    public float maxDelay=10;
    //生成一个敌人
    public void GenerateEnemy()
    {
        spawnedCount++;
        //如果生成数量打到上限
        if(spawnedCount>=maxCount)
        {
            return;
        }
        // 延迟时间随机
        Invoke("CreateEnemy",Random.Range(1,maxDelay));//延迟3秒
    }
    //随机选择一个路线
    public void CreateEnemy()
    {
        // 选择一条可以使用的路线
        //选择所有可以使用的路线
        WayLine[] usableWayLines=SelectUsableWayLine();
        //随机选择一条
        WayLine line=usableWayLines[Random.Range(0,usableWayLines.Length)];
        // object.Instantiate(敌人预制件,位置,旋转角度)
        int randomIndex=Random.Range(0,enemyType.Length);
        //创建敌人
        // GameObject go=Instantiate(enemyType[randomIndex],路线的第一个路点,Quaternion.identity)as GameObject;//as强制类型转换
        GameObject go=Instantiate(enemyType[randomIndex],line.WayPoints[0],Quaternion.identity)as GameObject;
        //配置信息
        EnemyMotor motor=go.GetComponent<EnemyMotor>();
        motor.line=line;
        line.IsUsable=false;//不可以使用
        //传递生成器对象引用[建议使用委托代替]
        // spawn.GenerateEnemy();
        go.GetComponent<EnemyStatusInfo>().spawn=this;
    }
    private void Start()
    {
        CalculateWayLines();
    }
    private WayLine[] lines;
    //移动路线 计算所有路线(获取每条路线中的路点坐标)
    private void CalculateWayLines()
    {
        lines=new WayLine[this.transform.chileCount];//有多少个子模块 就建立多少个子模块数组
        for(int i=0;i<lines.Length;i++)
        {
            //每一个路线
            // int count=this.transform.GetChild(i).childCount;//获取当前子孩子的路点数
            // lines[i]=new WayLine();
            // lines[i].WayPoints=new Vector3[count];
            //路线变换组件的引用
            Transform wayLineTF=this.transform.GetChild(i);
            // 在WayLine写完构造函数后 可以更迭以下
            // lines[i]=new WayLine();
            //设置可行
            // lines[i].IsUsable=true;
            //创建路点数组对象
            // lines[i].WayPoints=new Vector3[wayLineTF.childCount];
            //创建路线对象
            //整合成一下一条代码
            //创建路线对象
            lines[i]=new WayLine(wayLineTF.childCount);
            for(int pointIndex=0;i<wayLineTF.childCount;i++)
            {
                lines[i].WayPoints[pointIndex]=
                    wayLineTF.GetChild(pointIndex).position;
            }
        }
    }
    //选择所有可以使用的路线
    private WayLine[] SelectUsableWayLine()//返回数组
    {
        //                                      表示容量大小,可以删去
        List<WayLine>resule=new List<WayLine>(lines.Length);//需要 using System.Collections.Generic;
        //遍历所有路线
        foreach(var item in lines)
        {
            //如果可以使用,添加到result列表中
            if(item.IsUsable)resule.Add(item);
        }
        return resule.ToArray();
    }
}