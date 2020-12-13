#pragma once

#include "SolutionDay.h"

class Day13 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

public:

  Day13() { }

  ~Day13() override { }

  string GetDay() override
  {
    return "13";
  }

  void ReadData()
  {
    mData = DataType();
    mData = rff(GetInputPath());
  }

  LL DoWork(bool partTwo)
  {
    LL ret = 0;
    LL start = stoll(mData[0]);
    vector<LL> buses;
    auto tokens = tok(mData[1], ',');
    for (auto t : tokens)
    {
      if (t != "x")
      {
        buses.push_back(stoll(t));
      }
      else
        buses.push_back(-1);
    }
    
    if (!partTwo)
    {
      LL minBus = -1;
      LL rem = -1;
      
      LL startTime = start;
      
      while (true)
      {
        for (auto bus : buses)
        {
          if (bus == -1) continue;
          if (startTime % bus == 0)
          {
            minBus = bus;
            rem = startTime - start;
            break;
          }
        }
        
        if (minBus >= 0)
          break;
        
        startTime++;
      }
      ret = rem * minBus;
    }
    
    else
    {
      vector<pair<LL, LL>> times;
      int offset = -1;
      for (auto bus : buses)
      {
        offset++;
        if (bus >= 0)
          times.push_back(make_pair(bus, bus - offset));
      }
      
      ret = getChineseRemainderMinNumber(times);
    }
    return ret;
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
      assert(Part1() == "3865");
      assert(Part2() == "415579909629976");
    }
    return ISolutionDay::Test();
  }
};
