
//  Copyright:NPU Soccer Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.18
//  Entry to the whole program

//
#include <transform.h>
#include <Robot.h>
//Used for UART on raspberry
#include <wiringPi.h>
#include <wiringSerial.h>

int main(int argc, char const *argv[])
{
    int fd;
    unsigned char message;
    Transform *tessst = new Transform();
    test->mainControl();

    if (wiringPiSetup() < 0)
        return 1;

    if ((fd = serialOpen((char *)"/dev/ttyAMA0", 9600)) < 0)
        return 1;

    printf("serial test start ...\n");
    std::cout << "minCost: " << test->getMinCost() << std::endl;
    test->printCharResult();

    message = test->getMessage();
    serialPrintf(fd, (char *)message);

    //while(1)
    //{
    //	serialPutchar(fd,serialGetchar(fd));
    //	printf("can recive the message..\n");
    //}
    serialClose(fd);
    return 0;
}

/*
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
        Transform *test = new Transform();
        unsigned char *message;
        char list[200];
        test->mainControl();
        //test->controller();
        cin.getline(list, 200, '\n');
        test_robot->disorder(list);
        test_robot->display();
        std::cout << "minCost: " << test->getMinCost() << std::endl;
        test->printCharResult();
        test->printFinalOut();
        //test->printOut();
        message = test-> getMessage();
        test_robot->translate(message);
        test_robot->display();
        
    }
    return 0;
    
}
*/
