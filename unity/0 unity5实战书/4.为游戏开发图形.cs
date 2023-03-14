using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class Myself_Move : MonoBehaviour{
    //4.1  将粒子效果附加到3D对象上 在直线路径上前后移动对象
    public float speed=3.0f; //这些是对象移动的位置和范围
    public float maxZ=16.0f;
    public float mixZ=-16.0f;
    private int _direction=1;//当前对象往哪个方向移动
    void Update(){
        transform.Translate(0,0,_direction*speed*Time.deltaTime);
        bool bounced=false;
        if(transform.positon.x>maxZ || transform.position.z<minZ){
            _direction=-direction;//切回原来方向
            bounced=true;
        }
        if(bounced){//如果切换方向 本帧对象额外移动一次
            transform.Translate(0,0,_direction*speed*Time.deltaTime);
        }
    }
    
}