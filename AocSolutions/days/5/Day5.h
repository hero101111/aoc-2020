#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day5 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day5() { }

  ~Day5() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(KINPUT "5\\input.txt");
  }

  long DoWork()
  {
    long long ret = 0;

    for (auto d : mData)
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
