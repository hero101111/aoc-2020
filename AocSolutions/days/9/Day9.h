#pragma once

#include "SolutionDay.h"

class Day9 : public ISolutionDay
{
private:

  using DataType = vector<LL>;
  DataType mData;

public:

  Day9() { }

  ~Day9() override { }

  string GetDay() override
  {
    return "9";
  }

  void ReadData()
  {
    mData = DataType();
    mData = rffll(GetInputPath());
  }

  LL DoWork(bool partTwo)
  {
    if (!partTwo)
    {
      int offset = 25;
       for (int i = offset; i < mData.size(); ++i)
       {
         bool isValid = false;
         for (int j = i - offset; j < i - 1; j++)
           for (int k = j + 1; k < i; k++)
           {
             if (mData[j] + mData[k] == mData[i])
               isValid = true;
           }
         if (!isValid)
           return mData[i];
       }
    }
    else
    {
      LL toFind = DoWork(false);

      for (int i = 0; i < mData.size() - 1; i++)
      {
        for (int j = i + 1; j < mData.size(); j++)
        {
          LL sum = 0;
          for (int k = i; k <= j; ++k)
            sum += mData[k];
          if (sum == toFind)
          {
            vector<LL> outs;
            for (int k = i; k <= j; ++k)
              outs.push_back(mData[k]);
            sort(begin(outs), end(outs));

            return *outs.begin() + *(outs.end() - 1);
          }
        }
      }
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
      assert(Part1() == "90433990");
      assert(Part2() == "11691646");
    }
    return ISolutionDay::Test();
  }
};
