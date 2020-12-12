#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day1 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day1(){ }

  ~Day1() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "1";
  }

  long DoWork1()
  {
    for (int i = 0; i < mData.size() - 2; ++i)
    {
      for (int j = i + 1; j < mData.size() - 1; ++j)
      {
          int a = stoi(mData[i]);
          int b = stoi(mData[j]);
          if (a + b == 2020)
            return a * b ;
      }
    }

    return 0;
  }

  long DoWork2()
  {
    for (int i = 0; i < mData.size() - 2; ++i)
    {
      for (int j = i + 1; j < mData.size() - 1; ++j)
      {
        for (int k = j + 1; k < mData.size(); ++k)
        {
          int a = stoi(mData[i]);
          int b = stoi(mData[j]);
          int c = stoi(mData[k]);
          if (a + b + c == 2020)
            return a * b * c;
        }
      }
    }


    return 0;
  }
  
  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork2());
  }

  bool Test() override
  {
    assert(Part1() == "744475");
    assert(Part2() == "70276940");
    return true;
  }
};
