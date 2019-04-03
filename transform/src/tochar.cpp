


#include <transform.h>


void Transform::toChar() {
    int num = minCost * 4;
    int tmp[8];
    
    int count = 0;
    if (minCost % 2 == 1)
    {
        finalOut[num] = '0';
        finalOut[num+1] = '0';
        finalOut[num+2] = '0';
        finalOut[num+3] = '0';
        finalOut[num] = '\0';
    }
    //std::cout <<"num: "<<num<<std::endl;
    for(int i = 0;i < num;i = i + 8)
    {
        int k = 0;
        for(int j = i;j < i + 8;j++){
            tmp[k] = int(finalOut[j] - '0');
            //std::cout <<tmp[i]<<" ";
            k++;
        }
        //std::cout <<std::endl;
        int merge = 0;
        for(int j = 0;j < 8;j++)
            merge += tmp[j] << (7-j);
        
        //std::cout <<merge<<" ";
        result[count] = merge;
        count++;
    }
    
}

void Transform::printCharResult() {
    for(int i = 0;i < (minCost + 1) / 2;i++)
        std::cout <<std::hex<<int(result[i])<<" ";
    std::cout <<std::endl;
}

void Transform::mainControl(int which) {
    // rightClipLoosen();
    // leftRcountercolckwise();
    // rightClipClamp();
    // LRoationUpdate(3);
    if(which == 0)
        dfs(0);
    else if(which == 1)
    {
        dfs_opt(0);
        std::cout <<"dfs_better"<<std::endl;
    }
    
    toChar();
}