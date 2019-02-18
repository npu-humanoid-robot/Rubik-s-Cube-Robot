


#include <transform.h>


void Transform::toChar() {
    int num = minCost * 4;
    int tmp[8];
    
    int count = 0;
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
            merge += tmp[j] << j;
        
        //std::cout <<merge<<" ";
        result[count] = merge;
        count++;
    }
    
}

void Transform::printCharResult() {
    for(int i = 0;i < (minCost + 1) / 2;i++)
        std::cout <<std::hex<<result[i]<<" ";
    std::cout <<std::endl;
}

void Transform::mainControl() {
    dfs(0);
    toChar();
}