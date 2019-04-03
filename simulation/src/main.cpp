
//  Copyright:NPU Soccer Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.18
//  Entry to the whole program

//
#include <transform.h>
#include <Robot.h>


int main(int argc, char const *argv[])
{
    // Transform* trf = new Transform();
    // trf->controller();
    // trf->printOut();
    // std::cout <<"Cost:"<<trf->getCost()<<std::endl;
    // delete trf;
    while(true)
    {
        robot *test_robot = new robot();
        //Transform *test = new Transform();
        unsigned char *message;
        char list[200];
        //test->mainControl(1);
        //test->controller();
        cin.getline(list, 200, '\n');
        test_robot->disorder(list);
        test_robot->display();
        test_robot->output();
        //std::cout << "minCost: " << std::dec <<test->getMinCost() << std::endl;
        //test->printCharResult();
        //test->printFinalOut();
        //test->printOut();
        //message = test-> getMessage();
        //test_robot->translate(message);
        //test_robot->display();
        
    }
    return 0;
    
}
