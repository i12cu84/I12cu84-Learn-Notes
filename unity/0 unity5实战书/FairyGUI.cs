using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using FairyGUI;

public class FairyGUI : MonoBehaviour{
    void Start(){
        Groot.inst.SetContenScalFactor(800,600);
        UIPackage.AddPackage("FGUI/Package");//导入路径下的文件 
        GComponent component=UIPackage.CreateObject("Package1","Component1") as GComponent;//as.... 等同.asCom 类型转换
        GRoot.inst.AddChile(component);
    }

    void Start(){
        minUI=GetComponent<UIPanel>().ui;
        
    }
}
//p14 按钮动效混用
//https://www.bilibili.com/video/BV1NW411977N?p=19
//目前到达19新手指引