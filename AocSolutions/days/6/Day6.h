#pragma once

#include "SolutionDay.h"

class Day6 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

public:

  Day6() { }

  ~Day6() override { }

  string GetDay() override
  {
    return "6";
  }

  void ReadData()
  {
    mData = DataType();
    mData = rff(GetInputPath());
    mData.push_back("");
  }

  LL DoWork(bool partTwo)
  {
    LL ret = 0;

    set<char> tempQuestions;
    set<char> countedQuestions;
    bool isFresh = true;
    for (auto line : mData)
    {
      tempQuestions.clear();

      if (line == "")
      {
        ret += countedQuestions.size();
        countedQuestions.clear();
        isFresh = true;       
      }
      else
      {
        for (char c : line)
          tempQuestions.insert(c);
        
        if (countedQuestions.empty() && isFresh)
        {
          countedQuestions = tempQuestions;
        }
        else
        {
          set<char> temp;
          if (partTwo)
            set_intersection(begin(countedQuestions), end(countedQuestions), begin(tempQuestions), end(tempQuestions), inserter(temp, end(temp)));
          else
            set_union(begin(countedQuestions), end(countedQuestions), begin(tempQuestions), end(tempQuestions), inserter(temp, end(temp)));

          countedQuestions = temp;
        }
        isFresh = false;        
      }
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
      assert(Part1() == "6775");
      assert(Part2() == "3356");
    }
    return ISolutionDay::Test();
  }
};
