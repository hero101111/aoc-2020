#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day4 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day4() { }

  ~Day4() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(KINPUT "4\\input.txt");
  }

  long DoWork()
  {
    long long ret = 0;

    for (auto passData : mData)
    {
    }
    return ret;

  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork());
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork());
  }
  
  bool Test() override 
  {
    return true;
  }
};
