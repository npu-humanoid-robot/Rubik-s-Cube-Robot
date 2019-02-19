#include "Cube.h"

class robot_arm
{

public:
  bool Clamp; //true -> 夹子松开//false -> 夹子夹紧
  bool Spin;  //true -> 非正常状态//false -> 正常状态
  robot_arm()
  {
    Clamp = false;
    Spin = false;
  };
  void close() { Clamp = false; };
  void open() { Clamp = true; };
  void doSpin()
  {
    if (Spin == false) Spin = true;
    else Spin = false;
  };
  ~robot_arm(){};
};

class robot
{
private:
  cube m_cube;
  robot_arm leftArm;
  robot_arm rightArm;

  int IsWarning;

  bool Debug;

public:
  bool check_status();
  void translate(unsigned char *chain);
  void disorder(char *chain);
  void display() { m_cube.display(); };
  robot();
  ~robot(){};

  void right_spin_CW();
  void left_spin_CW();
  void right_spin_CCW();
  void left_spin_CCW();
  void left_close();
  void right_close();
  void left_open();
  void right_open();
  void left_spin_OT()
  {
    left_spin_CW();
    left_spin_CW();
  };
  void right_spin_OT()
  {
    right_spin_CW();
    right_spin_CW();
  };
};
