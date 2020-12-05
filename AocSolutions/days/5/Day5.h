#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day5 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

public:

  Day5() { }

  ~Day5() override { }

  string GetDay() override
  {
    return "5";
  }

  void ReadData()
  {
    mData = DataType();

    mData = rff(GetInputPath());
  }

  LL DoWork(bool partTwo)
  {
    vector<LL> seatValues;

    transform(begin(mData), end(mData), back_inserter(seatValues), [](string seat)
    {
      seat = RegexReplace(seat, { { "F|L", "0" }, { "B|R", "1" } });
      return 8 * stoi(seat.substr(0, 7), nullptr, 2) + stoi(seat.substr(7, 3), nullptr, 2);
    });

    if (!partTwo)
    {
      return *max_element(begin(seatValues), end(seatValues));
    }
    else
    {
      sort(begin(seatValues), end(seatValues));
      for (auto it = begin(seatValues) + 1; it != end(seatValues); ++it)
        if (*(it-1) != *it - 1)
          return *it - 1;
    }
    return 0;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(false));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(true));
  }

  bool Test() override
  {
    {
      mCurrentInput = "input";
      assert(Part1() == "915");
      assert(Part2() == "699");
    }
    return ISolutionDay::Test();
  }
};
