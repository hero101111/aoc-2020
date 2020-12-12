#pragma once

#include "util/util.h"

class ISolutionDay
{
protected:
  ofstream verbose;
public:

  ISolutionDay()
  {
    verbose.open(KVERBOSE, ios_base::out);
  }

  virtual string Part1() = 0;
  virtual string Part2() = 0;

  virtual ~ISolutionDay() { verbose.close(); };

  virtual bool Test() { mCurrentInput = "input";  return true; }

  virtual string GetDay() { return "0";  }

  string mCurrentInput{ "input" };

  string GetInputPath() 
  {
    const string day = GetDay(); 
    assert(day != "0");
    return KINPUT + day + "/" + mCurrentInput + ".txt";
  };

};
