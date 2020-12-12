#pragma once

#include "SolutionDay.h"

class Day3 : public ISolutionDay
{
private:
  DynamicMap<char> mData;

public:
  Day3() {}

  ~Day3() override {}

  void ReadData()
  {
    mData = DynamicMap<char>();
    mData.fromfile(GetInputPath());
  }
  
  string GetDay() override
  {
    return "3";
  }

  vector<LL> DoWork(vector<Point> slopes)
  {
    vector<LL> ret;

    for (auto slope : slopes)
    {
      int crttotal = 0;

      Point start{0, 0};
      while (true)
      {
        LL checkX = start.x % (mData.max_x + 1);

        if (mData.hasAt({checkX, start.y}, '#'))
          crttotal++;

        start.x += slope.x;
        start.y += slope.y;

        if (start.y > mData.max_y)
          break;
      }
      ret.push_back(crttotal);
    }

    return ret;
  }

  string Part1() override
  {
    ReadData();

    vector<Point> slopes = {{3, 1}};

    return std::to_string(DoWork(slopes)[0]);
  }

  string Part2() override
  {
    ReadData();

    vector<Point> slopes = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

    auto data = DoWork(slopes);
    LL result = accumulate(begin(data), end(data), 1ll, std::multiplies<LL>());
    return std::to_string(result);
  }

  bool Test() override
  {
    {
      mCurrentInput = "test";
      assert(Part1() == "7");
      assert(Part2() == "336");
    }
    {
      mCurrentInput = "input";
      assert(Part1() == "203");
      assert(Part2() == "3316272960");
    }
    return ISolutionDay::Test();
  }
};
