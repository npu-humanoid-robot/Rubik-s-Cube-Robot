//  Copyright:NPU Soccer Robot Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.18
//  version2.0
//  This file is mainly used to implement 
//  various basic methods in the transform class defined in transform.h


#include <transform.h>
using namespace std;

//动作函数
//左手夹子松开
void Transform::leftClipLoosen() {
    out[numAction] = '0';
    out[numAction+1] = '1';
    out[numAction+2] = '0';
    out[numAction+3] = '1';
    numAction += 4;
}
//右夹子松开
void Transform::rightClipLoosen() {
    out[numAction] = '1';
    out[numAction+1] = '1';
    out[numAction+2] = '0';
    out[numAction+3] = '1';
    numAction += 4;
}
//左手夹子夹紧
void Transform::leftClipClamp() {
    out[numAction] = '0';
    out[numAction+1] = '1';
    out[numAction+2] = '1';
    out[numAction+3] = '0';
    numAction += 4;
}
//右手夹子夹紧
void Transform::rightClipClamp() {
    out[numAction] = '1';
    out[numAction+1] = '1';
    out[numAction+2] = '1';
    out[numAction+3] = '0';
    numAction += 4;
}
//左转轴顺时针90度
void Transform::leftRColckwise() {
    out[numAction] = '0';
    out[numAction+1] = '0';
    out[numAction+2] = '0';
    out[numAction+3] = '1';
    numAction += 4;
}
//左转轴逆时针90度
void Transform::leftRcountercolckwise() {
    out[numAction] = '0';
    out[numAction+1] = '0';
    out[numAction+2] = '1';
    out[numAction+3] = '0';
    numAction += 4;
}
//右转轴顺时针90度
void Transform::rightRColckwise() {
    out[numAction] = '1';
    out[numAction+1] = '0';
    out[numAction+2] = '0';
    out[numAction+3] = '1';
    numAction += 4;
}
//右转轴逆时针90度
void Transform::rightRcountercolckwise() {
    out[numAction] = '1';
    out[numAction+1] = '0';
    out[numAction+2] = '1';
    out[numAction+3] = '0';
    numAction += 4;
}
//左转轴转180度
void Transform::leftR180() {
    out[numAction] = '0';
    out[numAction+1] = '0';
    out[numAction+2] = '1';
    out[numAction+3] = '1';
    numAction += 4;
}
//右转轴转180度
void Transform::rightR180() {
    out[numAction] = '1';
    out[numAction+1] = '0';
    out[numAction+2] = '1';
    out[numAction+3] = '1';
    numAction += 4;
}
//以下四个为组合动作，即转90度要返回，而转180度无需返回原位置
//左顺转90度并回到原位置
void Transform::leftRColckwisAndReturn() {
    leftRColckwise();
    leftClipLoosen();
    leftRcountercolckwise();
    leftClipClamp();
}
//左逆转90度并回到原位置
void Transform::leftRCounterwiseAndReturn() {
    leftRcountercolckwise();
    leftClipLoosen();
    leftRColckwise();
    leftClipClamp();
}
//右顺转90度并回到原位置
void Transform::rightRColckwisAndReturn() {
    rightRColckwise();
    rightClipLoosen();
    rightRcountercolckwise();
    rightClipClamp();
}
//右逆转90度并回到原位置
void Transform::rightRCounterwiseAndReturn() {
    rightRcountercolckwise();
    rightClipLoosen();
    rightRColckwise();
    rightClipClamp();
}

//times=1,表示顺时针90度，times=2表示180度，times=3表示逆时针转90度
//以下两个函数作用为更新面朝向变化后的解算序列
void Transform::LRoationUpdate(int times) {
    if(times == 1)
    {
        for(int i = 0;i < in.length();i++)
        {
            if(in[i] == 'F')
                in[i] = 'D';
            else if(in[i] == 'D')
                in[i] = 'B';
            else if(in[i] == 'B')
                in[i] = 'U';
            else if(in[i] == 'U')
                in[i] = 'F';
        }
    }
    else if(times == 2)
    {
        for(int i = 0;i < in.length();i++)
        {
            if(in[i] == 'F')
                in[i] = 'B';
            else if(in[i] == 'D')
                in[i] = 'U';
            else if(in[i] == 'B')
                in[i] = 'F';
            else if(in[i] == 'U')
                in[i] = 'D';
        }
    }
    else if(times == 3)
    {
        for(int i = 0;i < in.length();i++)
        {
            if(in[i] == 'F')
                in[i] = 'U';
            else if(in[i] == 'D')
                in[i] = 'F';
            else if(in[i] == 'B')
                in[i] = 'D';
            else if(in[i] == 'U')
                in[i] = 'B';
        }
    }
}
void Transform::RRoationUpdate(int times) {
    if(times == 1)
    {
        for(int i = 0;i < in.length();i++)
        {
            if(in[i] == 'F')
                in[i] = 'R';
            else if(in[i] == 'R')
                in[i] = 'B';
            else if(in[i] == 'B')
                in[i] = 'L';
            else if(in[i] == 'L')
                in[i] = 'F';
        }
    }
    else if(times == 2)
    {
        for(int i = 0;i < in.length();i++)
        {
            if(in[i] == 'F')
                in[i] = 'B';
            else if(in[i] == 'R')
                in[i] = 'L';
            else if(in[i] == 'B')
                in[i] = 'F';
            else if(in[i] == 'L')
                in[i] = 'R';
        }
    }
    else if(times == 3)
    {
        for(int i = 0;i < in.length();i++)
        {
            if(in[i] == 'F')
                in[i] = 'L';
            else if(in[i] == 'R')
                in[i] = 'F';
            else if(in[i] == 'B')
                in[i] = 'R';
            else if(in[i] == 'L')
                in[i] = 'B';
        }
    }
}


//以下几个函数用于将F,U，B，R转至L或D，同时更新序列

//想转R面，直接的方法只有一种方法即R到L，RtoB，B再toD伴随的转动和夹子的松闭太多暂不予以考虑
void Transform::RtoL() {
    //左夹子松开
    leftClipLoosen();
    //右手转180度
    rightR180();
    //左夹子夹紧
    leftClipClamp();
    //更新序列
    RRoationUpdate(2);
            
}
void Transform::RtoF() {
    //左夹子松开
    leftClipLoosen();
    //右手逆转90
    rightRcountercolckwise();
    //左夹子夹紧
    leftClipClamp();
    //右夹子松开
    rightClipLoosen();
    //右手顺转90
    rightRColckwise();
    //右手夹紧
    rightClipClamp();
    //更新序列
    RRoationUpdate(3);
}
void Transform::RtoB() {
    //左夹子松开
    leftClipLoosen();
    //右手顺转90
    rightRColckwise();
    //左夹子夹紧
    leftClipClamp();
    //右夹子松开
    rightClipLoosen();
    //右夹子逆时针90度
    rightRcountercolckwise();
    //右夹子夹紧
    rightClipClamp();
    //更新序列
    RRoationUpdate(1);

}

//想转F面的话共有两项选择
//第一种:F面到D面
void Transform::FtoD() {
    //右夹子松开
    rightClipLoosen();
    //左轴顺转90度
    leftRColckwise();
    //右夹子夹紧
    rightClipClamp();
    //左夹子松开
    leftClipLoosen();
    //左夹子逆转90度
    leftRcountercolckwise();
    //左夹子夹紧
    leftClipClamp();
    //更新序列
    LRoationUpdate(1);
}
//第二种:F面到L面
void Transform::FtoL() {
    //左夹子松开
    leftClipLoosen();
    //右轴逆转90度
    rightRcountercolckwise();
    //左夹子夹紧
    leftClipClamp();
    //右夹子松开
    rightClipLoosen();
    //右夹子顺转90度
    rightRColckwise();
    //右夹子夹紧
    rightClipClamp();
    //更新序列
    RRoationUpdate(3);
}
//欲转U面，U至D
void Transform::UtoD() {
    //右夹子松开
    rightClipLoosen();
    //左轴转180度
    leftR180();
    //右夹子夹紧
    rightClipClamp();
    //更新序列
    LRoationUpdate(2);
}
//UtoF
void Transform::UtoF() {
    //右夹子松开
    rightClipLoosen();
    //左手顺转90
    leftRColckwise();
    //右夹子夹紧
    rightClipClamp();
    //左夹子松开
    leftClipLoosen();
    //左手逆转90
    leftRcountercolckwise();
    //左夹子夹紧
    leftClipClamp();
    //更新序列
    LRoationUpdate(1);
}
//UtoD
void Transform::UtoB() {
    //右夹子松开
    rightClipLoosen();
    //左手逆转90度
    leftRcountercolckwise();
    //右夹子夹紧
    rightClipClamp();
    //左夹子松开
    leftClipLoosen();
    //左夹子顺转90
    leftRColckwise();
    //左夹子夹紧
    leftClipClamp();
    //更新序列
    LRoationUpdate(3);
}

//欲转B面，两种方法
//第一种，BtoL
void Transform::BtoL() {
    //左夹子松开
    leftClipLoosen();
    //右轴顺转90度
    rightRColckwise();
    //左夹子夹紧
    leftClipClamp();
    //右夹子松开
    rightClipLoosen();
    //右夹子逆转90度
    rightRcountercolckwise();
    //右夹子夹紧
    rightClipClamp();
    //更新序列
    RRoationUpdate(1);
}
//第二种，BtoD
void Transform::BtoD() {
    //右夹子松开
    rightClipLoosen();
    //左轴逆转90度
    leftRcountercolckwise();
    //右夹子夹紧
    rightClipClamp();
    //左夹子松开
    leftClipLoosen();
    //左夹子顺转90度
    leftRColckwise();
    //左夹子夹紧
    leftClipClamp();
    //更新序列
    LRoationUpdate(3);
}

void Transform::input() {
    getline(cin,in);
}
void Transform::preProcess() {
    int Length = in.length();
    for(int i = 0;i < Length;i++)
        if(in[i] == ' ')
            in[i] = '1';
    string tmp( int(((Length+2) / 3)) * 2,0 );
    int j = 0;
    for(int i = 0;i <= Length;i += 3)
    {
        tmp[j] = in[i];
        tmp[j+1] = in[i+1];
        j += 2;
    }
    in = tmp;
    Length = in.length();
    cout <<"in_length: "<<Length<<endl;
    cout <<"in: "<<in<<endl;
    in_copy = in;
}
//处理输入的魔方解法字符串，一步一步编译为硬件层需要序列
//输出的序列在out中
void Transform::controller() {
    srand((unsigned)time(NULL));
    try
    {
        int Length = in.length();
        for(int i = 0;i < Length;i += 2) 
        {
            if(in[i] == 'L' || in[i] == 'D') 
            {
                if(in[i] == 'L') 
                {
                    //cout <<"here"<<endl;
                    if(in[i+1] == '\'')
                        leftRCounterwiseAndReturn();
                    else if(in[i+1] == '1')
                        leftRColckwisAndReturn();
                    else if(in[i+1] == '2')
                        leftR180();
                    else
                    {
                        throw "the operand in input is illegal";
                    }
                }
                else if(in[i] == 'D')
                {
                    if(in[i+1] == '\'')
                        rightRCounterwiseAndReturn();
                    else if(in[i+1] == '1')
                        rightRColckwisAndReturn();
                    else if(in[i+1] == '2')
                        rightR180();
                    else
                    {
                        throw "the angel of rotation in input is illegal";
                        //throw i;
                    }
                    
                }
            }//if(in[i] == 'L' || in[i] == 'D')
            else if(in[i] == 'R')
            {
                RtoL();
                //已转化为D面的转动问题，故i -= 2与进入下一次循环的i += 2 抵消
                i -= 2;
            }
            else if(in[i] == 'F')
            {
                //两个选择
                //int ran = rand() % 2;
                //if (ran == 1)
                    FtoD();
                //else
                 //   FtoL();
                
                //FtoL();
                i -= 2;
            }
            else if(in[i] == 'U') //只有这一种方案
            {
                UtoD();
                i -= 2;
            }
            else if(in[i] == 'B')
            {
                //两个选择
                //int ran = rand() % 2;
                //if(ran == 1)
                    BtoD();
                //else
                 //   BtoL();
                i -= 2;
            }
            else
            {
                throw "the surface to rotate in input is illegal";
                //throw i;
            }
        }
    }
    catch(const char* msg)
    {
        cerr <<msg<<endl;
    }
  
    
    this->calulateCost();
}

//将结果打印出来
void Transform::printOut() {
    int i = 0;
    while(true)
    {
        cout <<out[i];
        if(out[i] == '\0')
            break;
        i++;
    } 
    cout <<endl;
}

void Transform::calulateCost() {
    this->cost = numAction / 4;
    //cout <<"calulateCost"<<endl;
}

int Transform::getCost() {
    return this->cost;
}

void Transform::calulateMaxSearchStep() {
  
    this->maxSearchStep = in.length() / 2;
    this->choice = new int[maxSearchStep];
    this->finalChoice = new int[maxSearchStep];
    cout <<"maxSearchStep: "<<this->maxSearchStep<<endl;
}

int Transform::getMinCost() {
    return this->minCost;
}

//Mainly used for debugging 
void Transform::printFinalChoice() {
    for(int i = 0;i < maxSearchStep;i++)
        cout <<finalChoice[i]<<" ";
    cout <<endl;
}

//Mainly used for debugging 
void Transform::printChoice() {
    for(int i = 0;i < maxSearchStep;i++)
        cout <<finalChoice[i]<<" ";
    cout <<endl;
}

void Transform::printFinalOut() {
    int i = 0;
    while(true)
    {
        cout <<finalOut[i];
        if(finalOut[i] == '\0')
            break;
        i++;
        if(i % 4 == 0)
            cout <<" ";
    }
    cout <<endl;
    //cout <<"outcost :"<<i/4<<endl;

}
