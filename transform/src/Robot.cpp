#include "Robot.h"

robot::robot()
{
  IsWarning = false;
  m_cube.clear();
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
    case 10:
      right_spin_CCW();
      break;
    case 2:
      left_spin_CCW();
      break;
    case 11:
      right_spin_OT();
      break;
    case 3:
      left_spin_OT();
      break;
    case 13:
      right_open();
      break;
    case 5:
      left_open();
      break;
    case 14:
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
  }
}

void robot::right_spin_CW()
{
  if (rightArm.Clamp == false)
  {
    if (leftArm.Clamp == true)
    {
      m_cube.CY();
    }
    else
    {
      m_cube.D();
    }
    rightArm.Spin = (!rightArm.Spin);
  }
  else
    IsWarning = true;
}
void robot::left_spin_CW()
{
  if (leftArm.Clamp == false)
  {
    if (rightArm.Clamp == true)
    {
      m_cube.CX();
    }
    else
    {
      m_cube.L();
    }
    leftArm.Spin = (!leftArm.Spin);
  }
  else
    IsWarning = true;
}
void robot::right_spin_CCW()
{
  if (rightArm.Clamp == false)
  {
    if (leftArm.Clamp == true)
    {
      m_cube.Y();
    }
    else
    {
      m_cube.CD();
    }
    rightArm.Spin = (!rightArm.Spin);
  }
  else
    IsWarning = true;
}
void robot::left_spin_CCW()
{
  if (leftArm.Clamp == false)
  {
    if (rightArm.Clamp == true)
    {
      m_cube.CY();
    }
    else
    {
      m_cube.D();
    }
    leftArm.Spin = (!leftArm.Spin);
  }
  else
    IsWarning = true;
}

void robot::left_close()
{
  leftArm.close();
}
void robot::right_close()
{
  rightArm.close();
}
void robot::left_open()
{
  leftArm.open();
}
void robot::right_open()
{
  rightArm.open();
}

bool robot::check_status()
{
  if (leftArm.Clamp && rightArm.Clamp)
    IsWarning = true;
  else if (leftArm.Spin && rightArm.Spin)
    IsWarning = true;
  else
    IsWarning = false;
  return IsWarning;
}
