
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
    test->mainControl(0);
    std::cout <<"minCost: "<<test->getMinCost()<<std::endl;
    test->printFinalOut();
    test->printCharResult();
    delete test;

    Transform* test1 = new Transform();
    test1->mainControl(1);
    std::cout <<"minCost: "<<std::dec<<test1->getMinCost()<<std::endl;
    test1->printFinalOut();
    test1->printCharResult();
    delete test1;
    
    return 0;
}
