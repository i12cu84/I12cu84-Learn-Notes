using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class Myself_Move : MonoBehaviour{

    //3.1 附加到摄像机上的RayShooter脚本
    private Camera _camera;
    void Start(){
        _camera=GetComponent<Camera>();//访问相同对象上附加的其他组件
    }
    void Update(){
        if(Input.GetMouseButtonDown(0)){//相应鼠标按键
            Vector3 point = new Vector3(_camera.pixelWidth/2,_camera.pixelHeight/2,0);//屏幕中心是宽高的一半
            Ray ray=_camera.SereenPointToRay(point);//使用S()在摄像机所在的位置创建射线
            RaycastHit hit;
            if(Physics.Raycast(ray,out hit)){//R给引用变量填充信息
                Debug.Log("Hit "+hit.point);//接收射线击中坐标
            }
        }
    }


    //3.2 添加球体指示器的RayShooter脚本
    private Camera _camera;
    void Start(){
        _camera=GetComponent<Camera>();
    }
    void Update(){
        if(Input.GetMouseButtonDown(0)){//这个方法大部分代码与3.1一样
            Vector3 point=new Vector3(_camera.pixelWidth/2,_camera.pixelHeight/2,0);
            Ray ray=_camera.SereenPointToRay(point);
            RaycastHit hit;
            if(Physics.Raycast(ray,out hit)){
                StartCoroutine(SphereIndicator(hit.point));//运行协程来相应击中
            }
        }
    }
    private IEnumerator SphereIndicator(Vector3 pos){//协程使用I方法
        GameObject sphere=GameObject.CreatePrimitive(PrimitiyeType.Shere);
        yield return new WaitForSeconds(1);//y关键词告诉协程何处暂停
        Destroy(sphere);//移除GO并清除内存
    }


    //3.3 准心可视化指示器
    void Start(){
        _camera=GetComponent<Camera>();
        Cursor.lockState=CursoLockMode.Locked;//隐藏屏幕中心的光标
        Cusor.visible=false;
    }
    void OnGUI(){
        int size=12;
        float posX=_camera.pixelWidth/2-size/4;
        float posY=_camera.pixelHeight/2-size/2;
        GUI.Label(new Rect(posX,posY,size,size),"*");//GUI命令在屏幕上显示文本
    }


    //3.4 检测是否击中目标对象
    ...
    if(Physics.Raycast(ray,out hit)){
        GameObject hitObject=hit.transform.gameObjec;//获取射线集中对象
        ReactiveTarget target=hitObject.GetComponent<ReactiveTarget>();
        if(target!=null){//检查对象上是否有ReactiveTarget组件
            Debug.Log("Target hit");
        }else{
            StartCoroutine(SphereIndicator(hit.point));
        }
    }
    ...


    //3.5 将消息发给目标对象
    ...
    if(target!=null){
        target.ReactToHit();
    }else{
        StartCoroutine(SphereIndicator(hit.point));
    }
    ...


    //3.6当受击ReativeTarget终止
    public void ReactToHit(){//通过设计脚本调用的方法
        StartCoroutine(Die());
    }
    private IEnumerator Die(){//推倒敌人 1.5秒后销毁
        this.transform.Rotate(-75,0,0);
        yield return new WaitForSeconds(1.5f);
        Destroy(this.gameObject);//对象能销毁自己 就像一个分开独立的对象
    }


    //3.7 基本WanderingAI脚本
    public float speed=3.0f;
    public float obstacleRange=5.0f;//移动速度值和对墙壁做出反应的距离
    void Update(){
        transform.Translate(0,0,speed*Time.deltaTime);//每帧持续向前移动 不管旋转
        Ray ray=new Ray(transform.position,transform.forwartd);
        RaycastHit hit;
        if(Physics.SphereCast(ray,0.75f,out hit)){//使用沿着射线的长度发射射线
            if(hit.distance<obstacleRange){
                float angle=Random.Range(-110,110);//转向一个半随机的新方向
                transform.Rotate(0,angle,0);
            }
        }
    }


    //3.8 添加alive状态的WanderingAI脚本
    private bool _alive;//布尔值用于跟踪敌人是否存货
    void Start(){
        _alive=true;//初始化
    }
    void Update(){
        if(_alive){
            transform.Translate(0,0,speed*Time,deltaTime),
            ...//只有当角色存货时才移动
        }
    }
    public void SetAlive(bool alive){
        _alive=alive;//公有方法允许外部代码影响alive的值
    }


    //3.9 ReactiveTarget告诉WanderingAI什么时候该死亡
    ...
    public void ReactToHit(){
        WanderingAI behavior=GetComponent<WanderingAI>();
        if(behavior !=null){//检查角色是否有W脚本 
            behavior.SetAlive(false);
        }
        StartCoroutine(Die());
    }
    ...


    //3.10 产生敌人预设的SenceController
    [SerializeField] peivate GameObjectenemyPrefab;//序列号变量 用于链接预设对象
    private GameObject _enemy;//一个私有变量 跟踪场景钟敌人的实例
    void Update(){
        if(_enemy==null){//只有当场景没有敌人时才产生一个新的敌人
            _enemy=Instantiate(enemyPrefab) as GameObject;//这个方法复制预设对象
            _enemy.transform.position=new Vector3(0,1,0);
            float angle=Random.Range(0,360);
            _enemy.Transform.Rotate(0,angle,0);
        }
    }


    //3.11 WanderingAI追加发射火球
    ...
    [SerizeField] private GameObjectfireballPrefab;//任何方法前添加这两个字段 就像在SenceController中那样
    privateGameObject _fireball;
    ...
    if(Physics.SphereCast(ray,0.75f,out hit)){
        GameObjecthitObject=hit.transform.gameObject;
        if(hitObject.GetComponent<PlayerCharacter>()){//使用在RayShooter中检查目标对象的方式检查玩家
            if(_fireball==null){//和在SceneController中检查空GameObject一样的逻辑
                _fireball=Instantiate(fireballPrefab) as GameObject;//I方法跟SenceController中的一样
                _fireball.transform.position=transform.TransformPoint(Vector3.forward*1.5f);//将火球放置在敌人面前并指向同一方向
                _fireball.transform.rotation=transform.rotation;
            }
        }
        else if (hit.distance<obstacleRange){
            float angle=Random.Range(-110,110);
            transform.Rotate(0,angle,0);
        }
    }

    
    //3.12 对碰撞做出反应Fireball脚本
    public float speed=10.0f;
    public int damage=1;
    void Update(){
        transform.Translate(0,0,speed*Time.deltaTime);
    }
    void OnTriggerEnter(Collider other){//当其他对象和这个触发器碰撞时调用这个方法
        PlayerCharacter player=other.GetComponent<PlayerCharacter>();
        if(player!=null){//检查other对象是否为PlayerCharacter
            Debug.Log("Player hit");
        }
        Destory(this.gameObject);
    }
    //注意需要关闭RIgidbody组件重力 (page 62)


    //3.13 能受到伤害的玩家
    private int _health;
    void Start(){
        _health=5;//初始化血量
    }
    public void Hurt(int damage){
        _health-=damage;//减少玩家血量
        Debug.Log("Health: "+_health);
    }
}

