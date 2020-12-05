﻿#pragma once

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
    LL ret = 0;

    vector<Point> seats;
    for (auto d : mData)
    { 
      int min = 0;
      int max = 127;


      int row = 0, column = 0;
      for (int i = 0; i < d.size(); ++i)
      {
        char c = d[i];

        if (c == 'F' || c == 'L')
        {
          max = max - ceil(((double)max - min) / 2);
        }
        if (c == 'B' || c == 'R')
        {
          min = min + ceil(((double)max - min) / 2);
        }

        if (i == 6)
        {
          row = min;
          min = 0;
          max = 7;
        }

        if (i == d.size() - 1)
        {
          column = min;
          seats.push_back({ row, column });
        }
      }
    }

    vector<LL> seatValues;
    for (auto s : seats)
    {
      seatValues.push_back(s.x * 8 + s.y);
    }

    if (!partTwo)
    {
      return *max_element(begin(seatValues), end(seatValues));
    }
    else
    {
      sort(begin(seatValues), end(seatValues));
      for (int i = 1; i < seatValues.size() - 2; ++i)
      {
        if (seatValues[i - 1] != seatValues[i] - 1)
        {
          return seatValues[i] - 1;
        }
        if (seatValues[i + 1] != seatValues[i] + 1)
        {
          return seatValues[i] + 1;
        }
      }
    }

    return *std::max_element(begin(seatValues), end(seatValues));
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
