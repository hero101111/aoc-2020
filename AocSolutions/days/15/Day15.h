#pragma once

#include "SolutionDay.h"

class Day15 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
  using DataType = vector<LL>;
  DataType mData;

public:

  Day15() { }

  ~Day15() override { }

  string GetDay() override
  {
    return "15";
  }

  void ReadData()
  {
    mData = DataType();

    //mData.fromfile(GetInputPath());
    vector<string> fileData = rff(GetInputPath());
    auto tokens = tok(fileData[0], ',');
    for (auto t : tokens)
      mData.push_back(stoll(t));
  }

  LL DoWork(LL search)
  {
    LL turn = 0;
    LL turnNum = -1;
    unordered_map<LL, vector<LL>> turnMap;
    
    LL counter = 0;
    for (LL i : rangeint(1, mData.size()))
    {
      turn++;
      turnNum = mData[i - 1];
      turnMap[turnNum].push_back(turn);
    }
    
    while (true)
    {
      if (turn == search)
      {
        return turnNum;
      }
      
      turn++;
      if (turnMap[turnNum].size() == 1)
      {
        turnNum = 0;
      }
      else
      {
        auto & vec = turnMap[turnNum];
        turnNum = vec[vec.size() - 1] - vec[vec.size() - 2];
      }
      
      turnMap[turnNum].push_back(turn);
      
      if (turnMap[turnNum].size() > 2)
      {
        turnMap[turnNum].erase(begin(turnMap[turnNum]));
      }
      
      counter++;
    }
    return 0;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(2020));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(30000000));
  }

  bool Test() override
  {
    {
      mCurrentInput = "input";
      assert(Part1() == "273");
      assert(Part2() == "47205");
    }
    return ISolutionDay::Test();
  }
};
