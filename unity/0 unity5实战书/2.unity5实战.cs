using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//ctrl+k c/u 注释/取消
public class Myself_Move : MonoBehaviour
{
    //运行一次的代码 void start(){}
    //每帧运行的代码 void Update(){}
    void Start()
    {
        //Debug.Log("hello world");
    }


    //2.1 对象旋转
    public float speed = 3.0f;
    void Update()
    {
        //对象顺时针旋转
        //transform.rotate(0, speed, 0);
        //对象向前移动
        transform.translate(0, 0, speed);
    }


    //2.2 定义枚举数据结构 将名称和设置关联起来
    public enum RotationAxes
    {
        MouseXAndY=0,
        MouseX=1,
        MouseY=2
    }
    //旋转类型的框架
    public RotationAxes axes = RotationAxes.MouseXAndY;
    void Update()
    {
        if (axes == RotationAxes.MouseX)
        {
            //水平旋转
        }
        else if(axes==RotationAxes.MouseY)
        {
            //垂直旋转
        }else
        {
            //水平且垂直旋转
        }
    }


    //2.3 水平旋转 还没响应鼠标
    public RotationAxes axes = RotationAxes.MouseXAndY;
    //为旋转速度声明的一个变量
    public float sentitivityHor = 9.0f;
    void Update()
    {
        if (axes == RotationAxes.MouseX)
        {
            transform.Rotate(0, sentitivityHor, 0);
        }
    }


    //2.4 响应鼠标而调整后的旋转命令
    //transform.Rotate(0,Input.GetAxis("Mouse X")*sensitivityHor,0;


    //2.5 MouseLook 垂直旋转
    public float sensitivityHor = 9.0f;
    public float sensivityVert = 9.0f;
    public float minimumVert = -45.0f;
    public float maximumVert = 45.0f;
    private float _rotationX = 0;
    void Update()
    {
        if (axes == RotationAxes.MouseX)
        {
            transform.Rotate(0, Input.GetAxis("Mouse X") * sensitivityHor, 0);
        }
        else if (axes == RotationAxes.MouseY)
        {
            _rotationX -= Input.GetAxis("Mouse Y") * sensivityVert;
            //基于鼠标增加垂直角度
            _rotationX = Mathf.Clamp(_rotationX, minimumVert, maximumVert);
            //将垂直角度限制在最小值和最大值之间
            float rotationY = transform.localEulerAngles.y;
            transform.localEulerAngles = new Vector3(_rotationX, rotationY, 0);
            //使用存储的旋转值创建新的Vector
        }
    }


    //2.6 MouseLook 中的水平且垂直旋转
    //...
    else
    {
       _rotationX-=Input.GetAxis("Mouse X")*sensitivityVert;
       _rotationX=Mathf.Clamp(_rotationX,minimumVert,maximumVert);
       float delta = Input.GetAxis("Mouse X") * sensitivityHor;
       delta是旋转的变化量
       float rotationY = transform.localEulerAngles + delta;
       transform.lovalEulerAngles=new Vector3(_rotationX, rotationY.0);
    }
    ...


    //2.7 完整的MouseLook脚本
    public enum RotationAxes
    {
        MouseXAndY = 0,
        MouseX = 1,
        MouseY = 2
    }
    public float sensitivityHor = 9.0f;
    public float sensivityVert = 9.0f;
    public float minimumVert = -45.0f;
    public float maximumVert = 45.0f;
    private float _rotationX = 0;
    void Update()
    {
        if (axes == RotationAxes.MouseX)
        {
            transform.Rotate(0, Input.GetAxis("Mouse X") * sensitivityHor, 0);
        }
        else if (axes == RotationAxes.MouseY)
        {
            _rotationX -= Input.GetAxis("Mouse Y") * sensivityVert;
            //基于鼠标增加垂直角度
            _rotationX = Mathf.Clamp(_rotationX, minimumVert, maximumVert);
            //将垂直角度限制在最小值和最大值之间
            float rotationY = transform.localEulerAngles.y;
            transform.localEulerAngles = new Vector3(_rotationX, rotationY, 0);
            //使用存储的旋转值创建新的Vector
        }
        else
        {
            _rotationX-=Input,GetAxis("Mouse Y") * sensitivityVert;
            _rotationX = Mathf.Clamp(_rotationX, minimumVert, maximumVert);
            float delta = Input.GetAxis("Moust X") * sensitivityHor;
            float rotationY = transform.localEulerAngles.y + delta;
            transform.localEulerAngles = new Vector3(_rotationX, rotationY, 0);
        }
    }


    //2.8 使用2.1旋转代码进行修改
    public float speed = 6.0f;
    void Update()
    {
        transform.Translate(0, speed, 0);
    }


    //2.9 相应按钮的位移
    void Update()
    {
        //键盘映射的间接名称
        float deltaX=Input.GetAxis("Horizontal")*speed;
        float deltaZ=Input.GetAxis("Vertical")*speed;
        transform.Translate(deltaX,0,deltaZ);//移动
    }


    //2.10 使用deltaTime使得运动独立于帧率
    void Update()
    {
        float deltaX=Input.GetAxis("Horizontal")*speed;
        float deltaZ=Input.GetAxis("Vertical")*speed;
        transform.Translate(deltaX*Time.deltaTime,0,deltaZ*Time.deltaTime);//移动 Time.deltaTime独立于帧率
    }


    //2.11 使用CharacterController而不是Transform移动
    private CharacterController _charContrller;//用于引用CharacterController变量
    void Start(){
        _charController=GetComponent<CharacterController>();//使用附加到相同对象上的其他组件
    }
    void Update(){
        float deltaX=Input.GetAxis("Horizontal")*speed;
        float deltaZ=Input.GetAxis("Vertical")*speed;
        Vectro3 movement=new Vector3(movement,speed);//将对焦移动的速度限制为和沿着轴移动的速度一样
        movement*=Time.deltaTime;
        movement=transform.TransformDirection(movement);//把movement向量从本地变换为全局坐标
        _charController.Move(movement);//告知CharacterController通过movement向量移动
    }


    //2.12 将重力添加给移动代码
    public float gravity=-9.8f;
    void Update(){
        movement=Vector3.ClampMagitude(movement,speed);
        movemengt.y=gravity;//使用重力值
    }

    //2.13 完成后的 FPSInput脚本
    //public class前加入以下两句
    [RequireComponent(typeof(CharacterController))]
        //R方法确保脚本附加了其他需要的组件 执行这种依赖并把需要的组件作为参数
    [AddComponentMenu("Control Script/FPS Input")]
        //脚本将在Unity编辑器钟添加组件菜单
    //而后 class内
    public float speed = 6.0f;
    public float gravity=-9.8f;
    private CharacterController _charController;//用于引用CharacterController变量
    void Start(){
        _charController=GetComponent<CharacterController>();//使用附加到相同对象上的其他组件
    }
    void Update(){
        float deltaX=Input.GetAxis("Horizontal")*speed;
        float deltaZ=Input.GetAxis("Vertical")*speed;
        Vectro3 movement=new Vector3(movement,speed);//将对焦移动的速度限制为和沿着轴移动的速度一样
        movement.y=gravity;
        movement*=Time.deltaTime;
        movement=transform.TransformDirection(movement);//把movement向量从本地变换为全局坐标
        _charController.Move(movement);//告知CharacterController通过movement向量移动
    }

}


//2.13 完成后的 FPSInput脚本 (出了问题)
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
[RequireComponent(typeof(CharacterController))]
//R方法确保脚本附加了其他需要的组件 执行这种依赖并把需要的组件作为参数
[AddComponentMenu("Control Script/FPS Input")]
//脚本将在Unity编辑器钟添加组件菜单
public class Myself_Move : MonoBehaviour{
    public float speed = 3.0f;
    public float gravity = -9.8f;
    private CharacterController _charController;//用于引用CharacterController变量
    void Start()
    {
        _charController = GetComponent<CharacterController>();//使用附加到相同对象上的其他组件
    }
    void Update()
    {
        float deltaX = Input.GetAxis("Horizontal") * speed;
        float deltaZ = Input.GetAxis("Vertical") * speed;
        Vectro3 movement = new Vector3(movement, speed);//将对焦移动的速度限制为和沿着轴移动的速度一样
        movement.y = gravity;
        movement *= Time.deltaTime;
        movement = transform.TransformDirection(movement);//把movement向量从本地变换为全局坐标
        _charController.Move(movement);//告知CharacterController通过movement向量移动
    }
}


// 当时项目备份
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class Myself_Move : MonoBehaviour{
    void Start(){//运行一次
    }
    public float speed = 3.0f;//移动速度设置
    void Update(){//每帧运行一次 与帧率有关
        //transform.rotate(0, speed, 0);//旋转
        float deltaX = Input.GetAxis("Horizontal") * speed;//前后移动捕捉
        float deltaZ = Input.GetAxis("Vertical") * speed;
        if (deltaX >= 0) Debug.Log("1");
        transform.Translate(deltaX * Time.deltaTime, 0, deltaZ * Time.deltaTime);//移动 Time.deltaTime独立于帧率
    }
}
















