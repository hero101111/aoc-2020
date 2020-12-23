#pragma once

#include "SolutionDay.h"

class Day23 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
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

    //cups = stoll(tok("418976235"s));


    
    cups = { 4,1,8,9,7,6,2,3,5 };
     //cups = {3, 8, 9, 1, 2, 5, 4, 6, 7  };
     // 4,1,8,9,7,6,2,3,5
     //mData.fromfile(GetInputPath());
    mData = rff(GetInputPath());
  }

  LL DoWork()
  {
    LL ret = 231;

    auto getIndex = [&](LL val)
    {

      /*auto it = find(begin(cups), end(cups), val);
      assert(it != end(cups));
      return it - begin(cups);*/
    };

    LL startInsert = 10;
    while (cups.size() < 1'000'000)
    {
      cups.push_back(startInsert);
      startInsert++;
    }
    
    unordered_map<LL, list<LL>::iterator> itCache;

    auto getMin = [&]() -> LL
    {
      for (LL s = 1; s <= 1'000'000; ++s)
        if (itCache.find(s) != end(itCache))
          return s;
      return 1;
    };

    auto getMax = [&]() -> LL
    {
      for (LL s = 1'000'000; s >= 1; --s)
        if (itCache.find(s) != end(itCache))
          return s;
      
      return 1;
    };

    vector<LL> cache;
    {
      auto it = begin(cups);
      while (it != end(cups))
      {
        itCache[*it] = it;
        it++;
      }
    }

    //verbose << join(cups, " ");

    LL picked1, picked2, picked3;
    auto crt = cups.begin();
    for (LL step = 0; step < 10'000'000; step++)
    {
      if (step % 1000 == 0)
        cout << step << endl;
      auto pickIt = crt;
     
      advance(pickIt, 1);
      if (pickIt == end(cups))
        pickIt = cups.begin();
      picked1 = *pickIt;
      itCache.erase(picked1);
      auto toRemove1 = pickIt;
      advance(pickIt, 1);
      cups.erase(toRemove1);
  
      if (pickIt == end(cups))
        pickIt = cups.begin();
      picked2 = *pickIt;
      itCache.erase(picked2);
      auto toRemove2 = pickIt;
      advance(pickIt, 1);
      cups.erase(toRemove2);


      if (pickIt == end(cups))
        pickIt = cups.begin();
      picked3 = *pickIt;
      itCache.erase(picked3);
      auto toRemove3 = pickIt;
      cups.erase(toRemove3);

      LL lowest = getMin();
      LL highest = getMax();

      LL destVal = *crt - 1;
      while (picked1 == destVal || picked2 == destVal || picked3 == destVal)
      {
        destVal -= 1;
      }

      if (destVal < lowest)
      {
        destVal = highest;
      }

      auto destIt = itCache[destVal];
      advance(destIt, 1);

      destIt = cups.insert(destIt, picked3);
      itCache[picked3] = destIt;

      destIt = cups.insert(destIt, picked2);
      itCache[picked2] = destIt;

      destIt = cups.insert(destIt, picked1);
      itCache[picked1] = destIt;

      if (*crt == cups.back())
        crt = cups.begin();
      else
        advance(crt, 1);
    }

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

    cout << "values are " << val1 << " " << val2 << endl;
    ret = val1 * val2;

    /*string val;
    for (auto l : cups)
      val += to_string(l);
    cout << val;*/

    // const auto matches = RegexMatch(passData, R"()");
    return ret;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork());
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork());
  }

  bool Test() override
  {
    {
      mCurrentInput = "test";
      //assert(Part1() == "");
      //assert(Part2() == "");
    }
    {
      mCurrentInput = "input";
      //assert(Part1() == "");
      //assert(Part2() == "");
    }
    return ISolutionDay::Test();
  }
};
