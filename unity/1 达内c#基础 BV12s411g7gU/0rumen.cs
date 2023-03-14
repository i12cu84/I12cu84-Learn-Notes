//引入命名空间
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//定义类的住址
namespace shape
{
    //定义类
    class Program
    {
        //Ctrl+K,F 自动对齐 K,C 注释选中 K,U取消注释
        //定义方法
        static void Main1(string[] args) { }//可备用存储
        static void Main(string[] args)
        {
            Console.Title = "标题";
            //控制台.写一行   
            Console.WriteLine("Hello World!");
            //控制台.读一行
            string input = Console.ReadLine();
            Console.WriteLine("你输入了：" + input);
            float sum = 1.0f;//要带f
            double sumd = 1.0;//可不带
            char chara = 'a';
            string str = string.Format("第一个变量{0},第二个变量{1},第三个变量{2}", sum, sumd, chara);
            //可能参数希望是string,这是占位符
            Console.WriteLine("参数：{0:}", 10);//标准数字字符串格式化 变成货币￥10.00
            Console.WriteLine("{0:d2}", 5);//05
            Console.WriteLine("{0:f1}", 1.26);//1.3
            Console.WriteLine("{0:p0}", 0.1);//10%
            //转义符  \"引号 \0空 \r\n回车换行 \t tab键
            string strnumber="123";
            int strnumberint=int.Parse(strnumber);//str转int、数值
            strnumber=strnumberint.ToString();//任意转str
            #region 这是标题（不影响代码
            //折叠
            #endregion
            byte b3=100;
            int i3=b3;//隐式转换
            byte b4=(byte)i3;//显式转换
            //因大可转小 小不可转大
            int[] a;
            a=new int[6];
            a[0]=1;a[1]=2;a[2]=3;a[3]=4;a[4]=5;a[5]=6;//...
            string[] array01=new string[2]{"a","b"};
            bool[] array02={true,false,false};
            float[] tempe=new float[3]{1,3,7};
            float max=GetMax(tempe);//奇怪的问题
            //相当于float max=GetMax(new float[3]{1,3,7});
            foreach (var item in a){ //(类型 变量名 in 数组名称) 从头到尾依次读取
                //var输于推断类型,任何类型都可以直接赋值 局限代码可读差
                Console.WriteLine(item);//局限，只能读取不能修改
            }
            //声明 父类类型 赋值 子类对象 即上转型,主要用于函数定义的参数
            Array arr01=new int[2];
            Array arr02=new double[2];
            //object万类之祖 赋值任意类型
            object o1=1;
            object o2=true;
            object o3=new int[3];
            //var猜测 Array数组爸爸 object万类祖
            //常用属性
            //数组长度      数组名.Length
            //清除元素值    Array.Clear
            //复制元素      Array.copy          数组名.CopyTo
            //克隆          数组名.Clone
            //查找元素      Array.IndexOf       Array.LastIndexOf
            //排序          Array.Sort      从小到大
            //反转          Array.Reverse   用排序后反转就逆序
            int[,] array21=new int[5,3];
            //array.Length ==> 15
            int [][] array002;//null
            array002 =new int[4][];//创建具有四个元素的交错数组
            array002[0] = new int[3];
            array002[1] = new int[5];
            array002[2] = new int[4];
            array002[3] = new int[1];
            array002[0][0] = 1;//对第一个赋值
            for(int i=0;i<array002.Length();i++)//..?
            {
                for(int j=0;j<array002[i].Length();j++)
                {
                    Console.Write(array002[i][j]+"\t");
                }
                Console.WriteLine();
            }
        }

        //一个函数拿来引用
        private static float GetMax(float[] array)
        {
            float max=array[0];
            for(int i=1;i<array.Length;i++)
            {//注意是大写，而且没有括号
                if(max<array[i])
                    max=array[i];
            }
            return max;
        }
        private static int Add(params int[] arr)
        //params 参数数组 对于方法内部而言只是个普通数组
        //对于调用者而言,可以传递数组、一组类型相同的变量集合、不传递参数
        {
            int sum=0;
            foreach(var item int arr)
            {
                sum+=item;
            }
            return sum;
        }
    }
}
