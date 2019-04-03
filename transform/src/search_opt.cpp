//  Copyright:NPU Soccer Robot Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.19
//  Version:3.0

#include <transform.h>
using namespace std;

void Transform::dfs_opt(int depth) {
    if(depth >= this->maxSearchStep)
    {
    
        calulateCost();
        //cout <<"cost: "<<cost<<endl;
    
        if(cost < this->minCost)
        {
            
            minCost = cost;
            for(int i = 0;i < this->maxSearchStep;i++)
                finalChoice[i] = choice[i];
            for(int i = 0;i < numAction;i++)
                finalOut[i] = out[i]; 
            finalOut[numAction] = '\0';
        }
    }    
    else
    {
        int i = depth * 2;

        if(in[i] == 'L' || in[i] == 'D')
        {
            int iniActionNum = numAction; //用于保存现场
            std::string in_tmp = in;
            
            if(in[i+1] != '2' && i + 2 < in.length() && 
                        (in[i+2] =='B' || in[i+2] == 'F' ) ) //can opt
            {
                choice[depth] = 0;
                if(in[i] == 'L' && in[i+1] == '1') //L1接B或F
                    L1WithBorFOpt(in[i+2]);
                else if(in[i] == 'L' && in[i+1] == '\'') //L3接B或F
                    L3WithBorFOpt(in[i+2]);
                else if(in[i] == 'D' && in[i+1] == '1') //D1接B或F
                    D1WithBorFOpt(in[i+2]);
                else if(in[i] == 'D' && in[i+1] == '\'') //D3接B或F
                    D3WithBorFOpt(in[i+2]);
                cout <<"Finish opt"<<endl;
                dfs_opt(depth+1);
                numAction = iniActionNum;
            }
            
            
            for(int i = depth * 2;i < in.length();i++)
                in[i] = in_tmp[i];

            choice[depth] = 1;
            roationOfLD(depth);
         
            dfs_opt(depth+1);
            numAction = iniActionNum; //恢复现场
            
            
            
        }
        else if(in[i] == 'R')
        {
            int iniActionNum = numAction; //用于保存现场
            RtoL();
            choice[depth] = 0;
            roationOfLD(depth);
           
            dfs_opt(depth+1);
            numAction = iniActionNum; //用于恢复现场
        }
        else if(in[i] == 'F')
        {
            std::string in_tmp = in; //因为要二叉，所以要保存序列现场
            //两个选择
            int iniActionNum = numAction; //保存动作现场
           
            FtoD();
          
            choice[depth] = 0;
            
            roationOfLD(depth);
            dfs_opt(depth+1);
            numAction = iniActionNum; //恢复动作现场


            for(int i = depth * 2;i < in.length();i++)
                in[i] = in_tmp[i];                    //恢复序列现场
            FtoL();

            choice[depth] = 1;
            roationOfLD(depth);
            dfs_opt(depth+1);
            numAction = iniActionNum;  //恢复动作现场
        
        }
        else if(in[i] == 'U') //只有这一种方案
        {
            int iniActionNum = numAction;
            UtoD();
            choice[depth] = 0;
            roationOfLD(depth);
            dfs_opt(depth+1);
            numAction = iniActionNum;
        }
        else if(in[i] == 'B') //结构同F
        {
            //两个选择
            int iniActionNum = numAction;
            std::string in_tmp = in;
            BtoD();
            choice[depth] = 0;
            roationOfLD(depth);
            
            dfs_opt(depth+1);
            numAction = iniActionNum;
            
            for(int i = depth * 2;i < in.length();i++)
                in[i] = in_tmp[i];

            BtoL();
            choice[depth] = 1;
            roationOfLD(depth);
            dfs_opt(depth+1);
            numAction = iniActionNum;
        }

    }
    
}