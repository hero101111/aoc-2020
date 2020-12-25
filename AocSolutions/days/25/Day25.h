#pragma once

#include "SolutionDay.h"

class Day25 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

public:

  LL cardPubKey, doorPubKey;
  int cardLoop = 1, doorLoop = 1;

  Day25() { }

  ~Day25() override { }

  string GetDay() override
  {
    return "25";
  }

  void ReadData()
  {
    mData = DataType();

    mData = rff(GetInputPath());

    cardPubKey = stoll(mData[0]);
    doorPubKey = stoll(mData[1]);
  }

  int FindLoopNumber(LL subject, LL searched)
  {
    LL value = 1;
    int count = 1;
    while (true)
    {
      value *= subject;
      value = value % 20201227;

      if (value == searched)
        return count;

      count++;
    }
    return count;
  }


  LL Encode(LL subject, int loopLimit)
  {
    LL value = 1;
    int count = 1;
    while (true)
    {
      value *= subject;
      value = value % 20201227;

      count++;
      if (count > loopLimit)
        return value;

    }
    return value;
  }

  string DoWork(bool partTwo)
  {
    if (partTwo)
      return "MERRY CHRISTMAS";

    cardLoop = FindLoopNumber(7, cardPubKey);
    LL encKey = Encode(doorPubKey, cardLoop);
    return to_string(encKey);
  }

  string Part1() override
  {
    ReadData();

    return DoWork(false);
  }

  string Part2() override
  {
    ReadData();

    return DoWork(true);
  }

  bool Test() override
  {
    {
      mCurrentInput = "input";
      assert(Part1() == "7269858");
      assert(Part2() == "MERRY CHRISTMAS");
    }
    return ISolutionDay::Test();
  }
};
