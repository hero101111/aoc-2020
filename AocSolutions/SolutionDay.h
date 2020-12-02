#pragma once

#include "util/util.h"
#include "util/IntComputer.h"

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

  virtual bool Test() { return true; }
};
