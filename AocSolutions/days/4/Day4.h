#pragma once

#include "SolutionDay.h"

class Day4 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

public:

  Day4() { }

  ~Day4() override { }

  string GetDay() override
  {
    return "4";
  }

  void ReadData()
  {
    mData = DataType();

    mData = rff(GetInputPath());
    mData.push_back("");
  }

  LL DoWork(bool isPart2)
  {
    LL ret = 0;

    vector<string> req = {"byr", "iyr", "eyr","hgt","hcl","ecl","pid"};
    auto validator = [](map<string, string> m) -> bool {
      bool isValid = true;
      
      isValid &= m["byr"].size() == 4 && stoi(m["byr"]) >= 1920 && stoi(m["byr"]) <= 2002;
      isValid &= m["iyr"].size() == 4 && stoi(m["iyr"]) >= 2010 && stoi(m["iyr"]) <= 2020;
      isValid &= m["eyr"].size() == 4 && stoi(m["eyr"]) >= 2020 && stoi(m["eyr"]) <= 2030;

      // hgt
      {
        auto val = m["hgt"];
        bool validVal = false;
        auto regexCm = RegexMatch(val, R"(^(\d+)cm$)");
        auto regexIn = RegexMatch(val, R"(^(\d+)in$)");
        if (regexCm.size() == 1)
        {
          int num = stoi(regexCm[0]);
          validVal = num >= 150 && num <= 193;
        }
        if (regexIn.size() == 1)
        {
          int num = stoi(regexIn[0]);
          validVal = num >= 59 && num <= 76;
        }
        isValid &= validVal;
      }

      {
        isValid &= RegexIsMatch(m["hcl"], R"(^#([0-9a-f]){6}$)");
      }
      {
        auto validEcl = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
        if (find(begin(validEcl), validEcl.end(), m["ecl"]) == end(validEcl))
          isValid = false;
      }

      {
        isValid &= RegexIsMatch(m["pid"], R"(^([0-9]){9}$)");
      }

      return isValid;
    };
    // const auto matches = RegexMatch(passData, R"()");
    
    map<string, string> crt;
    for (auto d : mData)
    {
      auto tokens = tok(d);
      for (auto t : tokens)
      {
        auto tokens2 = tok(t, ':');
        crt[tokens2[0]] = tokens2[1];
      }
      if (d == "")
      {
        
        bool isValid = true;
        for (auto r : req)
        {
          if (crt.find(r) == end(crt))
            isValid = false;
        }
        if (isValid && isPart2) isValid &= validator(crt);
        if (isValid)
        {
          ret++;
        }

        crt.clear();
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
      mCurrentInput = "test";
      //assert(Part1() == "0");
      //assert(Part2() == "");
    }
    {
      mCurrentInput = "input";
      assert(Part1() == "213");
      assert(Part2() == "147");
    }
    return ISolutionDay::Test();
  }
};
