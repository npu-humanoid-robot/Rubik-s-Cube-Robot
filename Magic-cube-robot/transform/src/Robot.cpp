#include "Robot.h"

robot::robot()
{
  IsWarning = 0;
  m_cube.clear();
  Debug = true;
}

void robot::disorder(char *chain)
{
  m_cube.play(chain);
}

void robot::translate(unsigned char *chain)
{
  if (chain[0] != 255 || chain[1] != 255)
  {
    cout << "error!" << endl;
    return;
  }
  int total_step = chain[2];
  int i = 0;
  while (i < total_step && (!check_status()))
  {
    int operate = 0;
    if (i % 2 == 0)
      operate = chain[i / 2 + 3] / 16;
    else
      operate = chain[i / 2 + 3] % 16;
    switch (operate)
    {
    case 9:
      right_spin_CW();
      break;
    case 1:
      left_spin_CW();
      break;
    case 10: //a
      right_spin_CCW();
      break;
    case 2:
      left_spin_CCW();
      break;
    case 11: //b
      right_spin_OT();
      break;
    case 3:
      left_spin_OT();
      break;
    case 13: //d
      right_open();
      break;
    case 5:
      left_open();
      break;
    case 14: //e
      right_close();
      break;
    case 6:
      left_close();
      break;
    }
    i++;
  }
  if (IsWarning)
  {
    cout << "error at :[" << i << "] " << endl;
    if (IsWarning == 1)
    {
      cout << "Part:"
           << "Clamp" << endl;
    }
    else if (IsWarning == 2)
    {
      cout << "Part:"
           << "Spin" << endl;
    }
  }
}

void robot::right_spin_CW()
{
  if (leftArm.Clamp == true)
  {
    m_cube.CY();
  }
  else if (rightArm.Clamp == false)
  {
    m_cube.D();
  }
  rightArm.doSpin();
  if (Debug)
    cout << "right_spin_CW  ["
         << "rightArm.Spin : " << rightArm.Spin << " ]" << endl;
}
void robot::left_spin_CW()
{
  if (rightArm.Clamp == true)
  {
    m_cube.CX();
  }
  else if(leftArm.Clamp == false)
  {
    m_cube.L();
  }
  leftArm.doSpin();

  if (Debug)
    cout << "left_spin_CW  ["
         << "leftArm.Spin : " << leftArm.Spin << " ]" << endl;
}
void robot::right_spin_CCW()
{
  if (leftArm.Clamp == true)
  {
    m_cube.Y();
  }
  else if (rightArm.Clamp == false)
  {
    m_cube.CD();
  }
  rightArm.doSpin();

  if (Debug)
    cout << "right_spin_CCW  ["
         << "rightArm.Spin : " << rightArm.Spin << " ]" << endl;
}
void robot::left_spin_CCW()
{
  if (rightArm.Clamp == true)
  {
    m_cube.X();
  }
  else if(leftArm.Clamp == false)
  {
    m_cube.CL();
  }
  leftArm.doSpin();

  if (Debug)
    cout << "left_spin_CCW  ["
         << "leftArm.Spin : " << leftArm.Spin << " ]" << endl;
}

void robot::left_close()
{
  leftArm.close();
  if (Debug)
    cout << "left_close  ["
         << "leftArm.Clamp : " << leftArm.Clamp << " ]" << endl;
}
void robot::right_close()
{
  rightArm.close();
  if (Debug)
    cout << "right_close  ["
         << "rightArm.Clamp : " << rightArm.Clamp << " ]" << endl;
}
void robot::left_open()
{
  leftArm.open();
  if (Debug)
    cout << "left_open  ["
         << "leftArm.Clamp : " << leftArm.Clamp << " ]" << endl;
}
void robot::right_open()
{
  rightArm.open();
  if (Debug)
    cout << "right_open  ["
         << "rightArm.Clamp : " << rightArm.Clamp << " ]" << endl;
}

bool robot::check_status()
{
  if (leftArm.Clamp && rightArm.Clamp)
    IsWarning = 1;
  else if (leftArm.Spin && rightArm.Spin)
    IsWarning = 2;
  else
    IsWarning = 0;
  return IsWarning;
}
