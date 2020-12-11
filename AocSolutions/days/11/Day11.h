#pragma once

#include "SolutionDay.h"
#include "util/util.h"

using namespace std::views;

class Day11 : public ISolutionDay
{
private:

  using DataType = DynamicMap<char>;
  DataType mData;

public:

  Day11() { }

  ~Day11() override { }

  string GetDay() override
  {
    return "11";
  }

  void ReadData()
  {
    mData = DataType();

    mData.fromfile(GetInputPath());
  }

  bool IsOccupied(char c)
  {
    return c == '#';
  }

  bool IsFloor(char c)
  {
    return c == '.';
  }

  bool IsEmpty(char c)
  {
    return c == 'L';
  }

  int GetOccupiedCount(Point p, bool getFirstNeighbors)
  {
    int ret = 0;

    auto walk = [&](Point direction) {
      Point q = p;
      char c;
      while (true)
      {
        q = q + direction;
        if (mData.at(q, &c))
        {
          if (IsOccupied(c)) { ret++; break; }
          if (!IsFloor(c)) break;
        }
        else
          break;

        if (getFirstNeighbors)
          break;
      }
    };

    for (int x : rangeint(-1, 1))
      for (int y : rangeint(-1, 1))
      {
        if (abs(x) != 0 || abs(y) != 0)
          walk({ x, y });
      }

    return ret;
  }

  int RunStep(bool partTwo)
  {
    int changes = 0;

    DynamicMap newMap = mData;
    for (auto [cellLocation, cellContent] : mData.Traverse())
    {
      const int occupiedCount = GetOccupiedCount(cellLocation, !partTwo);
      
      if (IsEmpty(cellContent) && occupiedCount == 0)
      {
        newMap[cellLocation] = '#';
        changes++;
      }
      else if (IsOccupied(cellContent) && (occupiedCount >= (partTwo ? 5 : 4)))
      {
        newMap[cellLocation] = 'L';
        changes++;
      }
    }

    mData = newMap;
    return changes;
  }

  LL DoWork(bool partTwo)
  {
    while (true)
    {
      if (RunStep(partTwo) == 0)
        break;
    }

    return mData.for_each([&](char c) { return (IsOccupied(c)); });
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
      assert(Part1() == "2359");
      assert(Part2() == "2131");
    }
    return ISolutionDay::Test();
  }
};
