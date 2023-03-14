using UnityEngine;
using System.Collections;
//枪动画
public class GunAnimation:MonoBehaviour
{
    //先录制三个自定义的动画 分别为以下三个
    //开枪动画
    public string fireAnimName="PlayerGun01_Fire";
    //更换弹匣动画
    public string updateAmmoAnimName="PlayerGun01_UpdateAmmo";
    //缺少子弹动画
    public string lackBulletAnimName="PlayerGun01_LackBullet";
    public AnimationAction action;
    private void Awake()
    {
        action =new AnimationAction(GetConponentInChildren<Animation>());
    }
    //记得将动画 Animations中的Element 0-2三个动画定义好
}
//武器模块
[RequireComponent(typeof(AudioSource))]
public class Gun:MonoBehaviour
{
    //攻击力
    public float atk=100;
    //需要发射子弹的预设
    public GameObject bulletProfab;
    //开火的位置变换组件
    public Transform firePointTF;
    private AudioSource audioSource;
    //发射子弹时的音频片段
    public AudioClip clip;
    //枪口特效
    private MuzzleFlash muzzleFlash;
    private GunAnimation anim;
    //为子类提供重写Start方法的机会
    protected virtual void Start()
    {
        print("Gun--Start");
        anim=GetComponent<GunAnimation>();
        muzzleFlas=GetComponentInChildren<MuzzleFlash>();
    }
    //开火              子弹朝向
    public void Firing(Vector3 direction)
    {
        //玩家枪发射:枪口方向
        //敌人反射:从枪口位置朝向玩家头部位置
        //准备子弹
        //判断弹匣内是否包含子弹
        //如果敌人枪没有动画 &&如果准备子弹失败
        if(anim!=null && Ready()==false)return ;
        //发射子弹
        //创建子弹 播放音频 播放动画
        audioSouce.PlayOneShot(clip);
        // anim.action.Play(anim.fireAnimName);//会出动画播放的逻辑问题（连开几次枪只会播放一次的情况
        //如果有，才播动画
        if(anim)
            anim.action.PlayQueued(anim.fireAnimName);//能够解决以上的问题
        muzzleFlash.DisplayerFlash();
        //创建子弹
        Instantiate(bulletPrefab,firePointTF.position,Quaternion.LookRotation(direction));
    }
    //准备子弹
    private bool Ready()
    {
        //如果弹匣内没有子弹||在播放换弹匣动画
        if(currentAmmoBullets<=0 || anim.action.IsPlaying(anim.updateAmmoAnimName))
            return false;//返回没有子弹
        //减一发子弹
        currentAmmoBullets--;
        if(currentAmmoBullets==0)//如果正好没有子弹
        {
            anim.action.Play(anim.lackBulletAnimName);//播放缺少子弹动画
            print(currentAmmoBullets);
        }
        return true;
        //如果缺少子弹播放缺少子弹动画
    }
    //弹夹容量
    public int ammoCapacity=15;
    //当前弹匣内子弹数15
    public int currentAmmoBullets=15;
    //剩余子弹数90
    public int remainBullets=90;
    //更换弹夹
    public void UpdateAmmo()
    {
        //如果没有剩余子弹 或者 弹匣内子弹数等于容量(相当于满子弹)
        if(remainBullets<=0||currentAmmoBullets=ammoCapacity)return;
        //如果剩余子弹数 大于 弹匣容量 则返回弹匣容量数 否则返回剩余数
        currentAmmoBullets=remainBullets>=ammoCapacity?ammoCapacity:remainBullets;
        remainBullets-=currentAmmoBullets;
        anim.action.Play(anim.updateAmmoAnimName);
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
        if(Input.GetMouseButtonDown(0))//按0
        {
            base.Firing(base.firePointTF.forward);
        }
        if(Input.GetMouseButtonDown(1))//按1 换弹夹
        {
            base.UpdateAmmo();
        }
    }
}
//动画组件 源自3unity script.cs
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
        // Debug.Log(animName);
        //因为动画太短，所以会出现问题 53行anim.action.Play(anim.fireAnimName);
        // anim.CrossFade(animName);
        anim.PlayQueued;//需要放到队列里播
    }
    public void PlayQueued(string animName)
    {
        anim.PlayQueued(animName);
    }
    //判断指定动画是否正在播放     动画片段名称
    public void IsPlaying(string animName)
    {
        return anim.IsPlaying(animName);
    }
}
//敌人AI 源自3unity script.cs
[RequireComponent(typeof(EnemyAnimation))]//勿忘动画名称
[RequireComponent(typeof(EnemyMotor))]
[RequireComponent(typeof(EnemyStatusInfo))]
public class EnemyAI:MonoBehaviour
{
    //马达设置面向朝向玩家
    motor.LookRotation(PlayerStatusInfo.Instance.headTF.position);
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
    private Gun gun;
    private void Start()
    {
        anim=GetComponent<EnemyAnimation>();
        motor=GetComponent<EnemyMotor>();
        gun=GetComponentInChildren<Gun>();
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
    //延迟攻击时间
    public float delay=0.3f;
    private void Attack()
    {
        //注视玩家
        motor.LookRotation(PlayerStatusInfo.Instance.headTF.position);
        //如果攻击动画没有播放
        if(!anim.action.IsPlaying(anim.attackAnimName))
            anim.action.Play(anim.idleAnimName);//播放闲置动画 ,同样在unity引擎中 模块的设置中输入动画名称
        if(atkTimer<=Time.time)//攻击间隔
        {
            //播放攻击动画
            anim.action.Play(anim.attackAnimName);
            //随后,在unity引擎中 将物体模块的Enemy Animation(Script)上 (达内p144案例)
            //将 Run Anim Name\Attack Anim Name\Idle Anim Name\Death Anim Name 右边填写动画的名称
            //以枪发射子弹 朝我那家头部
            //发射子弹（建议使用动画事件替代
            Invoke("Shoot",delay);//0.3f延迟
            //发起攻击
            atkTimer=Time.time+atkInterval;
        }
    }
    //射击朝向
    private void shoot()
    {
        //发起攻击 (从枪口位置指向玩家头部位置)
        gun.Firing(PlayerStatusInfo.Instance.headTF.position-gun.firePointTF.position);
    }
}
//玩家状态信息类
public class PlayerStatusInfo:MonoBehaviour
{
    //提供当前类对象的引用 静态应用
    public static PlayerStatusInfo Instance{get;private set;}
    //玩家头部位置变换
    public Transform headTF;
    public void Awake()
    {
        Instance=this;
    }
    public float HP=1000;
    public float maxHP=1000;
    public void Damage(float amount)
    {
        HP-=amount;
        //闪现红屏
        Debug.Log("受伤："+HP);
        if(HP<=0)
        {
            Death();
        }
    }
    public void Death()
    {
        //游戏结束相关方法
        Debug.Log("游戏结束");
    }
}
//子弹 定义子弹共有行为
public class Bullet:MonoBehaviour
{
    //
    [HideInInspector]
    public float atk;
    //子弹发射的距离 攻击距离
    public float attackDistance=200;
    //射线检测层
    public LayerMask mask;
    //目标飞向位置
    private Vectoe3 targetPos;
    //移动速度
    private float moveSpeed=200;
    protected RaycastHit hit;
    private void Awake()
    {
        CalculateTargetPoint();
    }
    //计算目标点
    private void CalculateTargetPoint()
    {
        //子弹朝向从自己枪口开始向前发射
        //从当前位置(枪口位置) 当前方向(枪口方向) 受击目标信息 攻击最大距离 射线检测层
        if(Physics.Raycast(this.transform.position,this.transform.forward,out hit,attackDistance,mask))
            targetPos=hit.point;
        else
            targetPos=this.transform.position+this.transform.forward*attackDistance;
    }
    //移动
    private void Update()
    {
        Movement();
        //如果到达目标点
        if((this.transform.position-targetPos).sqrMagnitude<0.1f)
        {
            //销毁目标
            Destory(this.gameObject);
            GenerateContactEffect();
        }
    }
    private void Movement()
    {
        this.transform.position=Vector3.MoveTowards(this.transform.position,targetPos,moveSpeed*Time.deltaTime);
    }
    //到达目标点:销毁 创建相关特效
    //创建相关特效
    //根据目标点物体的标签hit.collider.tag
    private void GenerateContactEffect()
    {
        //根据目标物体标签 创建相应特效
        if(hit.collider=null)return ;
        // switch(hit.collider.tag)
        // {
        //     case "":
        //     back;
        // }
        //特效名称规则：存放路径+接触物体标签
        //通过代码读取资源
        //资源必须放到Resources目录下 ContactEffects/tag
        // GameObject prefabGO=Resources.Load<GameObject>("目录/资源名称");
        //根据标签加载资源[建议]使用对象池替代
        GameObject prefabGO=Resources.Load<GameObject>("ContactEffects/Effects"+hit.collider.tag);//路径
        if(prefabGO)//创建资源 资源预设 目标点位置向法线方向移动0.01m z轴朝向法线方向
            // Instantiate(prefabGO,targetPos,Quaternion.identity);
            Instantiate(prefabGO,targetPos+hit.normal*0.01f,Quaternion.LookRotation(hit.normal));
    }
}
//敌人子弹
public class EnemyBullet:Bullet
{
    private void OnTriggerEnter(Collider other)
    {
        //如果与玩家接触
        if(other.tag=="MainCamera")
        {
            //玩家减血
            PlayerStatusInfor.Instance.Damage(atk);
            //销毁子弹
            Destroy(this.gameObject);
        } 
    }
}
//玩家子弹
public class PlayerBullet:Bullet//记得设计mask
{
    //根据敌人部位减血
    //希望到达物体上再减血，需要使用委托
    private void Start()
    {
        //击中部位的名称：base.hit.collider.name
        float atk=CalculateAttackForce();
        if(hit.collider!=null && hit.collider.tag=="Enemy")//如果碰撞器存在
        {
            Debug.Log(atk);
            // hit.collider.GetComponent<EnemyStatusInfo>().Damage(atk); 逻辑错误
            hit.collider.GetComponentInParent<EnemyStatusInfo>().Damage(atk);//脚本其实在父物体上 需要向上找
        }
    }
    private void CalculateAttackForce()
    {
        //建议使用配置文件替换 根据受击物体补位名称
        //Coll
        switch(hit.collider.name)
        {
            case "Coll_Head"://头部
            return atk*3;
            case "Coll_Body"://身体
            return atk*1.5f;
            default://其他
            return atk;
            // break;//应该有break奇怪没有
        }
    }
}
using UnityEngine;
using System.Collections;
using System.Collections.Generic;
//敌人马达 提供移动旋转寻路
public class EnemyMotor:MonoBehaviour
{
    //旋转速度
    public float rotationSpeed=10;
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
        //头部高于自身物体 人物倾斜
        //旋转速度过快
        // targetPoint.y=this.transform.position.y;
        Quaternion dir=
            Quaternion.Lerp(
                this.transform.rotation,
                Quaternion.LookRotation(targetPoint-this.transform.position),
                rotationSpeed*Time.deltaTime
            );
        //仅仅沿y轴旋转
        this.transform.eulerAngles=new Vector3(0,euler.y,0);
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
        //如果没有死亡
        if(HP<=0)return;
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
        spawn.GenerateEnemy();
        //禁用 AI
        GetComponent<EnemyAI>().enabled=false;
    }
}
//HTC VIVE 虚拟现实 steamVR
//连发枪
namespace InvincibleLegend//以后每个类都加如此  
{
    public class AutomaticGun:Gun
    {
        private SteamVR_TranckedObject trackedObject;
        private SteamVR_Controller.Device device;
        private float timer;
        public float interval=0.1f;
        //找追踪对象
        protected override void Start()
        {
            base.Start();
            trackedObject=GetComponentInParent<SteamVR_TrackedObject>();
        }
        //连发
        protected override void Update()
        {
            base.Update();
            if(device==null)
                device=SteamVR_Controller.Input((int)trackedObject.index);
            //如果按下扳机键执行
            if(device.GetPress(SteamVR_Controller.ButtonMask.Trigger)&&timer<=Time.time)
            {
                // print("Press");
                Firing(firePointTF.forward);
                timer=Time.time+interval;
            }
        }
    }
}
//VRTK VR常见功能工具包
// using UnityEngine;
// using VRTK;
// public class Gun:VRTK_InteractableObject
// {
//     private GameObject bullet;
//     private float bulletSpeed=1000f;
//     private float bulletLife=5f;
//     private override void StartUsing(GameObject using )
//     {
//         base.StartUsing(usingObject);
//         FireBullet();
//     }
//     protected override void Start()
//     {
//         base.Start();
//     }
// }

//单发枪,附加到枪物体中
namespace InvincibleLegend//以后每个类都加如此  
{
    //事件:当满足某种条件,自动调用方法的过程
    public class SingleGun:Gun
    {
        protected override void Start()
        {
            base.Start();//调用父类的Start方法
            GetComponentInParent<VRTK_ControllerEvents>();
        }
        private void Update()
        {
            if(Input.GetMouseButtonDown(0))//按0 鼠标左右键
            {
                base.Firing(base.firePointTF.forward);
            }
            if(Input.GetMouseButtonDown(1))//按1 换弹夹
            {
                base.UpdateAmmo();
            }
        }
    }
}
//直至P205 由于后面将是SteamVR学习目前无用将停置
//                                 BV12s411g7gU