#pragma once

#include "SolutionDay.h"

class Day7 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  using MapType = unordered_map<string, vector<pair<int, string>>>;
  using BucketMap = map<string, int>;
  DataType mData;

public:

  Day7() { }

  ~Day7() override { }

  string GetDay() override
  {
    return "7";
  }

  void ReadData()
  {
    mData = DataType();
    mData = rff(GetInputPath());
  }

  int checkBag(MapType & bagsMap, string bagStr, unordered_set<string> & accountedFor)
  {
    int ret = 0;
    auto & bag = bagsMap[bagStr];

    for (auto& p : bag)
    {
      string& innerBag = p.second;

      if (innerBag == "shiny gold")
      {
        ret++;
        accountedFor.insert(bagStr);
      }
      else
      {
        int r = checkBag(bagsMap, innerBag, accountedFor);
        if (r > 0)
          accountedFor.insert(bagStr);
        ret += r;
      }
    }
    return ret;
  }

  void checkBag2(MapType & bagsMap, string bagStr, BucketMap & bucket)
  {
    auto& bag = bagsMap[bagStr];

    for (auto& p : bag)
    {
      string & innerBag = p.second;
      bucket[innerBag] += p.first;
      for (int i = 0; i < p.first; ++i)
        checkBag2(bagsMap, innerBag, bucket);
    }
  }

  LL DoWork(bool partTwo)
  {
    MapType bagsMap;
    unordered_set<string> colors;
    for (auto d : mData)
    {
      const auto matches = RegexMatch(d, R"((\w+) (\w+) bags contain (.+).)");
      const string bagStr = matches[2];

      string colorMajor = matches[0] + " " + matches[1];

      if (bagStr.find("shiny gold") != string::npos)
        colors.insert(matches[0]);

      const auto bags = tok(bagStr, ',');
      for (auto bagsStrr : bags)
      {
        if (bagsStrr == "no other bags")
          continue;
        const auto matchesBags = RegexMatch(bagsStrr, R"((\d+) ([\w|\s]+) (bags|bag))");

        auto & bag = bagsMap[colorMajor];
        bag.push_back(make_pair( stoi(matchesBags[0]), matchesBags[1] ));
      }
    }

    if (!partTwo)
    {
      unordered_set<string> bagsContainingGold;
      for (auto b : bagsMap)
        checkBag(bagsMap, b.first, bagsContainingGold);
      return bagsContainingGold.size();
    }
    else
    {
      BucketMap bucket;
      checkBag2(bagsMap, "shiny gold", bucket);
      return accumulate(begin(bucket), end(bucket), 0, [](int t, auto c) { return t + c.second; });
    }
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
      assert(Part1() == "151");
      assert(Part2() == "41559");
    }
    return ISolutionDay::Test();
  }
};
