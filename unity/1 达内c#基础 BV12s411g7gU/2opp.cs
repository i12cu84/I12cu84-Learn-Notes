using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace shape
{
    class Program
    {
        static void Main(string[] args)
        {
            Wife wife01;//wife类型引用
            wife01 = new Wife();//实例化对象
            wife01.Setname("6");
            Console.WriteLine(wife01.Getname());
            wife wife02=wife01;
            wife02.Setname("7");
            Console.WriteLine(wife01.Getname());//是7
            wife wife03=wife01;
            wife03 =new Wife();//指向发生了改变
            wife03.Setname("8");
            Console.WriteLine(wife01.Getname());//还是7
            wife03.Name="9";//省事,调用set方法
            Wife wife04=new Wife(" ");//不会throw error,因为是为构造函数传参;
            //数组初始化必须指定大小,读写元素必须通过索引
            //crrl+r+m 提取方法,将所选语句提取到一个自命名方法名称中
            // Dictionary<string,User> dic =new Dictionary<string,User>//根据键查找值
            // dic.Add("lj","123");
            // User ljUser=dic["lj"];
            Wife wife05=new Student();//父类引用指向子类对象 只能使用父类成员
            Student stu02=(Student)wife05;//如果要访问子类成员,需要强制类型转换
            Student stu03=new Student();//子类还可以使用父类对象
            //static 静态成员变量 类被加载初始化 且只有一份 存在优先于对象 被所有对象所共享 常驻内存
            //public int xxx;           每个对象都存储一份 "杯子"
            //public static int XXX;    仅仅存储一份 所有对象共享 "饮水机"
            //静态类不能实例化 只能包含静态成员
            //静态类不能被继承 但是静态方法、属性都可以被继承
            //利:单独空间存储 所有对象共享 可以直接被类名调用
            //弊:静态方法中只能访问静态成员,共享数据被多个对象访问会出现并发冲突(加锁?)
            //适用场合1.所有对象需要共享数据2.在没有对象前就要访问成员3.工具类适合做静态类(常用,不需要过多数据)
            Random.Next(1,100);//随机数 静态类调用 工具类 例Math
            List<int> resullt=new List<int>(count);
            result=resullt.ToArray();
            //结构体 可以将class 改成 struct 即变成结构体
            //结构体自带无参数构造函数,所以不能包含无参数构造函数
            //构造函数中,必须先为所有字段赋值
            //举例构造函数public Direction(int rlndex,int clndex):this()
            //加":this()"引用即可不需要为所有字段赋值
            //Direction dir=new Direction(); class 情况下 左栈右堆
            //Direction dir=new Direction(); struct情况下 左栈右栈
            //Direction[] dir=new Direction[]; struct情况下 数组在堆
            //结构体更省空间,省性能
            //const /static 的定义量可以赋值
        }
    }
    class Wife
    {//默认private 私有
        private string name;//具有默认值,对象收回,成员清除 可以与局部变量同名
        public void Setname(string name)//用户保护
        {//为了数据上的验证,因而使用公开的方法来验证
            if(name == " ") throw new Exception("你的名字呢?");//丢出异常
            else this.name=name;
        }
        public string Getname()
        {
            return name;
        }
        public string Name
        {//与下二等效
            get//本质是方法
            {//读取保护
                return name;
            }
            set
            {//写入保护
                this.name=value;//写入的数据被称为value
            }
        }
        //构造函数提供了创建对象的方式,常用于初始化类的数据成员
        //若没有构造函数则会自动提供一个无参构造函数
        public Wife()//若不想外部使用,则可以private
        {//没有返回值,与类同名

        }
        public Wife(string name):this()//调用无参的重载
        {//已有构造函数,最好创建如上的无参构造函数,相当于重载
            this.name=name;
        }
        
        static void Main(string[] args)
        {
            //继承 static 结构体

        }
    }
    class Student:Wife//类继承 public可以 protected可以 private不可以
    {
        //prop tab tab
        private age;
    }
}
