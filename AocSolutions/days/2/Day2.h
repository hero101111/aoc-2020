#pragma once

#include "SolutionDay.h"

class Day2 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day2() { }

  ~Day2() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "2";
  }

  long DoWork(int part)
  {
    long long ret = 0;

    for (auto passData : mData)
    {
      const auto matches = RegexMatch(passData, R"((\d+)-(\d+)\s(\w):\s(\w+))");

      const char letter = matches[2][0];
      string password = matches[3];
      
      switch (part)
      {
      case 1:
      {
        LL min = stoi(matches[0]);
        LL max = stoi(matches[1]);

        LL c = count(begin(password), end(password), letter);
        if (clamp(c, min, max) == c)
          ret++;
        break;
      }
      case 2:
      {
        int posA = stoi(matches[0]) - 1;
        int posB = stoi(matches[1]) - 1;

        if (password[posA] == letter ^ password[posB] == letter)
          ret++;
        break;
      }
      }
    }

    return ret;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(1));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(2));
  }

  bool Test() override
  {
    assert(Part1() == "506");
    assert(Part2() == "443");

    return true;
  }
};
