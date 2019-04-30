


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

void Transform::toChar_opt() {
    int num = minCost * 4;
    int tmp[8];
    
    int count = 0;
    if (minCost % 2 == 1)
    {
        finalOut_opt[num] = '0';
        finalOut_opt[num+1] = '0';
        finalOut_opt[num+2] = '0';
        finalOut_opt[num+3] = '0';
        finalOut_opt[num] = '\0';
    }
    //std::cout <<"num: "<<num<<std::endl;
    for(int i = 0;i < num;i = i + 8)
    {
        int k = 0;
        for(int j = i;j < i + 8;j++){
            tmp[k] = int(finalOut_opt[j] - '0');
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
    final_opt();
    //toChar();
    toChar_opt();

}

unsigned char *Transform::getMessage() {
    output[0] = 255;
    output[1] = 255;
    output[2] =( minCost + 1)/2;
    int sum = 0;
    for (int i = 0; i < ((minCost + 1) / 2); i++)
    {
        output[i + 3] = result[i];
        sum += result[i];
    }
    output[3 + (minCost + 1) / 2] = sum % 256; //计算和校验位
    output[4 + (minCost + 1) / 2] = 0;
    for (int i = 0; i<4 + (minCost + 1) / 2; i++)
    std::cout << std::hex << (int)output[i] << " ";
    std::cout<<endl;
    return output;
}

void Transform::AdjustForImage() {
    RRoationUpdate(1);
}

// 最后的优化，冗余动作，比如松紧松优化为松
void Transform::final_opt() {
    int i = 0;
    int j = 0;
    while(true) 
    {
        if(finalOut[i] == '\0' || finalOut[i + 4] == '\0')
          break;
        else
        {
            //左夹子先紧再松
            if(finalOut[i] == '0' && finalOut[i+1] == '1' && finalOut[i+2] == '1' && finalOut[i+3] == '0'
                && finalOut[i+4] == '0' && finalOut[i+5] == '1' && finalOut[i+6] == '0' && finalOut[i+7] == '1')
            {
                i = i + 8;
            }
            else if(finalOut[i] == '1' && finalOut[i+1] == '1' && finalOut[i+2] == '1' && finalOut[i+3] == '0'
                && finalOut[i+4] == '1' && finalOut[i+5] == '1' && finalOut[i+6] == '0' && finalOut[i+7] == '1')
            {
                i = i + 8;
            }
            else
            {
                finalOut_opt[j] = finalOut[i];
                finalOut_opt[j+1] = finalOut[i+1];
                finalOut_opt[j+2] = finalOut[i+2];
                finalOut_opt[j+3] = finalOut[i+3];
                finalOut_opt[j+4] = finalOut[i+4];
                finalOut_opt[j+5] = finalOut[i+5];
                finalOut_opt[j+6] = finalOut[i+6];
                finalOut_opt[j+7] = finalOut[i+7];
                j = j + 8;
                i = i + 8;
            }
        }
    }
    if(finalOut[i] != '0')
    {
        finalOut_opt[j] = finalOut[i];
        finalOut_opt[j+1] = finalOut[i+1];
        finalOut_opt[j+2] = finalOut[i+2];
        finalOut_opt[j+3] = finalOut[i+3];
    }
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