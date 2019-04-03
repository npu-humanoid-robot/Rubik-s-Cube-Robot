#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <iomanip>
using namespace std;

class Transform{
public:

    //构造函数
    Transform(){
        numAction = 0;
        cost = 0;
        minCost = 1000000000;
        maxSearchStep = 0;
        input();
        preProcess();
        calulateMaxSearchStep();
    }
    //新建一个对象后首先调用这个方法，结果便在result里了
    void mainControl(int which);
    
    void printCharResult();

    //获得动作数
    int getMinCost();

    void printFinalOut();
    
    
private:

    //基础动作

    //左手夹子松开
    void leftClipLoosen();
    //右夹子松开
    void rightClipLoosen();
    //左手夹子夹紧
    void leftClipClamp();
    //右手夹子夹紧
    void rightClipClamp();
    //左转轴顺时针90度
    void leftRColckwise();
    //左转轴逆时针90度
    void leftRcountercolckwise();
    //右转轴顺时针90度
    void rightRColckwise();
    //右转轴逆时针90度
    void rightRcountercolckwise();
    //左转轴转180度
    void leftR180();
    //右转轴转180度
    void rightR180();


    //以下四个为组合动作，即转90度要返回，而转180度无需返回原位置

    //左顺转90度并回到原位置
    void leftRColckwisAndReturn();
    //左逆转90度并回到原位置
    void leftRCounterwiseAndReturn();
    //右顺转90度并回到原位置
    void rightRColckwisAndReturn();
    //右逆转90度并回到原位置
    void rightRCounterwiseAndReturn();

    //times=1,表示顺时针90度，times=2表示180度，times=3表示逆时针转90度
    //以下两个函数作用为更新面朝向变化后的解算序列
    void LRoationUpdate(int times);
    void RRoationUpdate(int times);

    //以下几个函数用于将F,U，B，R转至L或D，同时更新序列
    //想转R面，直接的方法只有一种方法即R到L，RtoB，B再toD伴随的转动和夹子的松闭太多暂不予以考虑
    void RtoL();
    void RtoF();
    void RtoB();

    //想转F面的话共有两项选择
    //第一种:F面到D面
    void FtoD();
    //第二种:F面到L面
    void FtoL();

    //欲转U面，
    void UtoD();
    void UtoF();
    void UtoB();

    //欲转B面，两种方法
    //第一种，BtoL
    void BtoL();
    //第二种，BtoD
    void BtoD();

    //L,D面旋转
    void roationOfLD(int i);

    //输入函数，暂定从控制台读入，即标准输入
    void input();
    void preProcess();

    //就算基本动作数
    void calulateCost();
    void calulateMaxSearchStep();

    void printFinalChoice();
    void printChoice();


    //连续动作优化
    void L1WithBorFOpt(char sur);
    void L3WithBorFOpt(char sur);

    void D1WithBorFOpt(char sur);
    void D3WithBorFOpt(char sur);

    

    //处理输入的魔方解法字符串，一步一步编译为硬件层需要序列
    //输出的序列在out中
    void controller();

    //输出函数，暂时定位打印在控制台中，方便调试，亦方便使用管道通信来进行进程间的合作
    void printOut();
    //void printFinalOut();
    void toChar();
    
    int getCost();
    //深搜
    void dfs(int depth);
    void dfs_better(int depth);
    void dfs_opt(int depth);


    std::string in;
    std::string in_copy;
    char out[5000];
    char finalOut[5000];
    int numAction;
    int cost;
    int minCost;
    int maxSearchStep;
    int* choice;
    int* finalChoice;

    unsigned char result[150];
};
