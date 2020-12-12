#pragma once

#include "SolutionDay.h"

class Day19 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
  using DataType = vector<string>;
  DataType mData;

public:

  Day19() { }

  ~Day19() override { }

  string GetDay() override
  {
    return "19";
  }

  void ReadData()
  {
    mData = DataType();

    //mData.fromfile(GetInputPath());
    mData = rff(GetInputPath());
  }

  LL DoWork()
  {
    LL ret = 0;

    // const auto matches = RegexMatch(passData, R"()");
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
    {
      mCurrentInput = "test";
      //assert(Part1() == "");
      //assert(Part2() == "");
    }
    {
      mCurrentInput = "input";
      //assert(Part1() == "");
      //assert(Part2() == "");
    }
    return ISolutionDay::Test();
  }
};
