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
            //栈区小 堆区大
            //值类型 int bool char
            //引用型 string Array
            int[] arr=new int[]{1};
            int[] arr2=arr;//指向了同一个地址,相当于c引用
            string s1="1";
            string s2=s1;
            s1="2";//此时s2还是"1",因其修改的是栈中存储的引用
            int a2=1;
            Fun1(ref a2);//变成2
            int a3=1;//用于接收方法的结果,所以可以不用赋值
            Fun3(out a3);//变成2
            int result;
            //TryParse返回两个结果,out输出转换后的结果,返回值返回是否可以转换
            bool re=int.TryParse("250+",out resule);
            object o=a2;//装箱操作,最消耗性能
            a3=(int)o;//拆箱操作,次消耗性能
            string str02=""+a2;//会产生装箱操作,影响效率
            //string str02=""+a2.ToString;//则不会
            string s1="12";
            string s2="12";
            bool r1=object.ReFerenceEquals(s1,s2);//判断是否同源,同源
            string s3=new string (new char[]{'1','2'});
            string s4=new string (new char[]{'1','2'});
            bool r1=object.ReFerenceEquals(s3,s4);//判断是否同源,不同源
            s1="21";//开辟新的空间,原有无指向,则会被回收
            object o1=1;
            o1=2.0;o1="ok";o1=true;//每一次修改都会开辟新的空间
            // string strnumber="";
            // for(int i=0;i<10;i++)
            // {//注:每次拼接都会产生新的对象来替换引用,因此绝对不能这么干!
            //     strnumber=strnumber+i.ToString();//能干成,但垃圾会很多
            // }
            //适用性,频繁对字符串增删改
            StringBuilder builder=new StringBuider(10);//10为一次开辟可以容纳10个字符大小的空间
            for(int i=0;i<10;i++)                      //避免产生垃圾
            {//可变字符,功能同上,但新能利用率更高
                builder.Append(i);//其实是一个模板类,加载了各种功能,这是其一已定义的内置函数
            }
            string resule=builder.ToString();
            builder.Append("123");//会自动扩容,但会产生垃圾
            s1 = builder.Insert(0,"s1");//builder.Reokace();//builder.Remove();
            //字符串常用方法:ToArray  Contains  ToLower  IndexOf  Substring  Trim  Split  Join
            //MoveDirection.??? (这相当于类型名 是枚举 限定调用者取值
            //用处:增强可读 限定取值
            //语法 enum 变量名:数据类型{(值1=0,值2=1,...) }
            [Glags]//标记可使用按位,增强可读性,可删
            enum person {
                tall=1, //001
                rich=2, //010
                white=4,//100
            }
            person(tall|rich);//让按位取或变成"并且"
            //条件1.任意多个枚举做|运算 的结果不能与其他枚举值相同(2的n次)2.定义枚举时,用Flags特性修饰
            //函数定义思路 if((style&person.tall)==person.tall) 输出!
            //按位与 得到 可以输出
            person style=(person)Enum.parse(typeof(person),"tall"); //字符串转枚举
            string strenum=person.tall.ToString();                  //枚举转字符串
            
        }
        //值参数
        private static void Fun(int a)
        {
            a=2;
        }
        //引用参数 按引用传递 传递实参变量自身的内存地址
        //作用:改变数据
        private static void Fun1(ref int a)
        {//方法内部修改引用参数 实质上就是在修改实参变量
            a=2;
        }
        //输出参数 按 引用传递 传递实参变量自身的内存地址
        //作用:返回结果
        private static void Fun2(out int a)
        {//区别之一 方法内部必须为输出参数赋值
        //区别之二 输出参数 传递 之前可以不赋值
            a=2;
        }
        //定义两个整数交换的方法
        private static void Swop(ref int one,ref int two)
        {//改变实参
            int temp=one;
            one=two;
            two=temp;
        }
        //求正方形面积周长
        private static void Rect(int length,int width,out int area,out int perimeter)
        {//area perimeter可以没赋值就更改(因out)
            area=length*width;
            perimeter=(lenght+width)*2;
        }
        
    }
}