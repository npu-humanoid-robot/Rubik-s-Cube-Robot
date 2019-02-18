
//  Copyright:NPU Soccer Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.18
//  Entry to the whole program

#include <transform.h>
#include <Robot.h>
int main(int argc, char const *argv[])
{
    // Transform* trf = new Transform();
    // trf->controller();
    // trf->printOut();
    // std::cout <<"Cost:"<<trf->getCost()<<std::endl;
    // delete trf;
    robot *test_robot = new robot();
    Transform *test = new Transform();
    unsigned char *message;
    char list[100];
    test->mainControl();
    cin.getline(list, 100, '\n');
    test_robot->disorder(list);
    test_robot->display();
    std::cout << "minCost: " << test->getMinCost() << std::endl;
    test->printCharResult();
    message = test-> getMessage();
    test_robot->translate(message);
    test_robot->display();
    return 0;
}
