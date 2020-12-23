#pragma once

#include "SolutionDay.h"

class Day23 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

  list<LL> cups;

public:

  Day23() { }

  ~Day23() override { }

  string GetDay() override
  {
    return "23";
  }

  void ReadData()
  {
    mData = DataType();    
    cups = { 4,1,8,9,7,6,2,3,5 };
    mData = rff(GetInputPath());
  }

  string DoWork(bool partTwo)
  {
    if (partTwo)
    {
      LL startInsert = 10;
      while (cups.size() < 1'000'000)
      {
        cups.push_back(startInsert);
        startInsert++;
      }
    }
    
    unordered_map<LL, list<LL>::iterator> itCache;

    vector<LL> cache;
    {
      auto it = begin(cups);
      while (it != end(cups))
      {
        itCache[*it] = it;
        it++;
      }
    }

    auto crt = cups.begin();
    for (LL step = 0; step < (partTwo ? 10'000'000 : 100); step++)
    {
      auto pickIt = crt;
     
      advance(pickIt, 1);

      vector<LL> picked;
      for (int i : rangeint(1, 3))
      {
        if (pickIt == end(cups))
          pickIt = cups.begin();
        picked.push_back(*pickIt);
        itCache.erase(*pickIt);
        auto toRemove1 = pickIt;
        advance(pickIt, 1);
        cups.erase(toRemove1);
      }

      LL destVal = *crt;
      do
      {
        destVal -= 1;
        if (destVal < 1)
          destVal = partTwo ? 1'000'000 : 9;
      } while (contains(picked, destVal));


      auto destIt = itCache[destVal];
      advance(destIt, 1);

      for (auto pickedIt = picked.rbegin(); pickedIt != picked.rend(); ++pickedIt)
      {
        destIt = cups.insert(destIt, *pickedIt);
        itCache[*pickedIt] = destIt;
      }

      if (*crt == cups.back())
        crt = cups.begin();
      else
        advance(crt, 1);
    }

    if (partTwo)
    {
      auto it = cups.begin();
      while (*it != 1)
        advance(it, 1);

      advance(it, 1);
      if (it == end(cups))
        it = begin(cups);
      LL val1 = *it;

      advance(it, 1);
      if (it == end(cups))
        it = begin(cups);
      LL val2 = *it;
 
      string ret = to_string(val1 * val2);
      return ret;
    }
    else
    {
      string ret = join(cups, "");
      size_t posOf1 = ret.find('1');
      assert(posOf1 != string::npos);
      ret = ret.substr(posOf1 + 1) + ret.substr(0, posOf1);
      return ret;
    }
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
      auto p1 = Part1();
      assert(Part1() == "96342875");
      assert(Part2() == "563362809504");
    }
    return ISolutionDay::Test();
  }
};
