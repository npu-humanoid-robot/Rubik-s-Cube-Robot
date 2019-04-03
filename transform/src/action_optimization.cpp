//  Copyright:NPU Soccer Robot Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.19
//  Version:3.0



#include <transform.h>
using namespace std;
//以下四个为连续动作的优化动作

//L1接转B面或者转F面优化
//sur为面，即L1接的是哪个面
void Transform::L1WithBorFOpt(char sur) {
    //右夹子夹紧的情况下，左轴顺时针旋转90
    leftRColckwise();
    //右夹子松开
    rightClipLoosen();
    //后接B，左轴逆时针90，后接F,左轴顺时针90，要同时更新序列
    if(sur == 'B')
    {
        //右夹子松开的情况下，左轴逆时针旋转90
        leftRcountercolckwise();
        //右夹子夹紧
        rightClipClamp();
        //更新序列
        LRoationUpdate(3);
    }
    else if(sur == 'F') 
    {
        //右夹子松开的情况下，左轴顺时针旋转90
        leftRColckwise();
        //右夹子夹紧
        rightClipClamp();
        //更新序列
        LRoationUpdate(1);
    }
    else
    {
        std::cout <<"L1WithBorFOPT error"<<endl;
    }
    
}


//L3接转B面或者转F面优化
void Transform::L3WithBorFOpt(char sur) {
    //右夹子夹紧的情况下，左轴逆顺时针旋转90
    leftRcountercolckwise();
    //右夹子松开
    rightClipLoosen();
    //后接B，左轴逆时针90，后接F,左轴顺时针90，要同时更新序列
    if(sur == 'B')
    {
        //右夹子松开的情况下，左轴逆时针旋转90
        leftRcountercolckwise();
        //右夹子夹紧
        rightClipClamp();
        //更新序列
        LRoationUpdate(3);
    }
    else if(sur == 'F') 
    {
        //右夹子松开的情况下，左轴顺时针旋转90
        leftRColckwise();
        //右夹子夹紧
        rightClipClamp();
        //更新序列
        LRoationUpdate(1);
    }
    else
    {
        std::cout <<"L3WithBorFOPT error"<<endl;
    }
}

//D1接转B面或者转F面优化
void Transform::D1WithBorFOpt(char sur) {
    //左夹子夹紧的情况下，右轴顺时针90
    rightRColckwise();
    //左夹子松开
    leftClipLoosen();
    //后接B，右轴逆转针90,后接F，右轴顺转90,其后要更新序列
    if(sur == 'B')
    {
        //左夹子松开的情况下，右轴顺时针旋转90
        rightRColckwise();
        //左夹子夹紧
        leftClipClamp();
        //更新序列
        RRoationUpdate(1);
    }
    else if(sur == 'F')
    {
        //左夹子松开的情况下，右轴逆时针旋转90
        rightRcountercolckwise();
        //左夹子夹紧
        leftClipClamp();
        //更新序列
        RRoationUpdate(3);
    }
    else
    {
        std::cout <<"L3WithBorFOPT error"<<endl;
    }

}

//D3接转B面或者转F面优化
void Transform::D3WithBorFOpt(char sur) {
    //左夹子夹紧的情况下，右轴逆时针90
    rightRcountercolckwise();
    //左夹子松开
    leftClipLoosen();
    //后接B，右轴逆转针90,后接F，右轴顺转90,其后要更新序列
    if(sur == 'B')
    {
        //左夹子松开的情况下，右轴顺时针旋转90
        rightRColckwise();
        //左夹子夹紧
        leftClipClamp();
        //更新序列
        RRoationUpdate(1);
    }
    else if(sur == 'F')
    {
        //左夹子松开的情况下，右轴逆时针旋转90
        rightRcountercolckwise();
        //左夹子夹紧
        leftClipClamp();
        //更新序列
        RRoationUpdate(3);
    }
    else
    {
        std::cout <<"D3WithBorFOPT error"<<endl;
    }
}


