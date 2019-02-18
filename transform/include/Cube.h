#include <iostream>
#include <stdio.h>
using namespace std;

class cube
{
  private:
    char topset[9];
    char froset[9];
    char rigset[9];
    char lefset[9];
    char botset[9];
    char behset[9];

  public:
    char state[20][5];
    cube() { clear(); };

    void clear();
    void display();
    void output();

    void play(char *chain);

    //void disarrange(int step);

    void actxy(int level, int way);
    void actxz(int level, int way);
    void actyz(int level, int way);

    void R() { actxz(0, 1); };
    void r()
    {
        actxz(0, 1);
        actxz(1, 1);
    };
    void X()
    {
        actxz(0, 1);
        actxz(1, 1);
        actxz(2, 1);
    };
    void CX()
    {
        actxz(0, 0);
        actxz(1, 0);
        actxz(2, 0);
    };
    void L() { actxz(2, 0); };
    void CL() { actxz(2, 1); };
    void l()
    {
        actxz(2, 0);
        actxz(1, 0);
    };

    void U() { actxy(0, 1); };
    void u()
    {
        actxy(0, 1);
        actxy(1, 1);
    };
    void Y()
    {
        actxy(0, 1);
        actxy(1, 1);
        actxy(2, 1);
    };
    void CY()
    {
        actxy(0, 0);
        actxy(1, 0);
        actxy(2, 0);
    };
    void D() { actxy(2, 0); };
    void CD() { actxy(2, 1); };
    void d()
    {
        actxy(2, 0);
        actxy(1, 0);
    };

    void F() { actyz(0, 1); };
    void f()
    {
        actyz(0, 1);
        actyz(1, 1);
    };
    void Z()
    {
        actyz(0, 1);
        actyz(1, 1);
        actyz(2, 1);
    };
    void CZ()
    {
        actyz(0, 0);
        actyz(1, 0);
        actyz(2, 0);
    }
    void B() { actyz(2, 0); };
    void b()
    {
        actyz(2, 0);
        actyz(1, 0);
    };
};
