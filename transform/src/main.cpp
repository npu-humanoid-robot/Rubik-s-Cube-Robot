
//  Copyright:NPU Soccer Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.18
//  Entry to the whole program 


#include <transform.h>
int main(int argc, char const *argv[])
{
    // Transform* trf = new Transform();
    // trf->controller();
    // trf->printOut();
    // std::cout <<"Cost:"<<trf->getCost()<<std::endl;
    // delete trf;

    Transform* test = new Transform();
    test->mainControl();
    std::cout <<"minCost: "<<test->getMinCost()<<std::endl;
    
    test->printCharResult();
    return 0;
}
