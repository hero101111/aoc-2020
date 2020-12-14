#pragma once

#include "SolutionDay.h"

class Day14 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
  using DataType = vector<string>;
  DataType mData;
  
  unordered_map<LL, LL> memory;

public:

  Day14() { }

  ~Day14() override { }

  string GetDay() override
  {
    return "14";
  }
  
  LL applyMask(LL value, string mask)
  {
    LL pw2 = 1;
    for (LL i = mask.size() - 1; i >= 0; --i)
    {
      char crtBit = mask[i];
      if (crtBit == '1')
      {
        value |= pw2;
      }
      if (crtBit == '0')
      {
        if ( (value & pw2) == pw2)
        {
          value -= pw2;
        }
      }
      pw2 *= 2;
    }
    return value;
  }
  
  void generateMemAddresses(string mask, vector<LL> & aOut, LL offset = 0)
  {
    vector<LL> ret;
    
    bool hasSwitches = false;
    for (LL i = offset; i < mask.size(); ++i)
    {
      if (mask[i] == 'X')
      {
        hasSwitches = true;
        
        string mask1 = mask;
        mask1[i] = '0';
        generateMemAddresses(mask1, aOut, i);
   
        string mask2 = mask;
        mask2[i] = '1';
        generateMemAddresses(mask2, aOut, i);
      
        return;
      }
    }
    if (!hasSwitches)
    {
      auto toAdd = stoll(mask, nullptr, 2);
      aOut.push_back(toAdd);
    }
  }
  
  vector<LL> applyMemMask(LL memAddr, string mask)
  {
    LL pw2 = 1;
    for (LL i = mask.size() - 1; i >= 0; --i)
    {
      char crtBit = mask[i];
      if (crtBit == '0')
      {
        bool hasBit = ((memAddr & pw2) == pw2);
        mask[i] = hasBit ? '1' : '0';
      }
      if (crtBit == '1')
      {
        mask[i] = '1';
      }
      
      pw2 *= 2;
    }
    vector<LL> ret;
    generateMemAddresses(mask, ret);
    return ret;
  }

  void ReadData()
  {
    mData = DataType();

    mData = rff(GetInputPath());
  }

  LL DoWork(bool partTwo)
  {
    memory.clear();
    
    string crtMask = "";
    
    for (auto d : mData)
    {
      const auto mask = RegexMatch(d, R"(mask = (.+))");
      if (!mask.empty())
      {
        crtMask = mask[0];
      }
      
      const auto mem = RegexMatch(d, R"(mem\[(\d+)\] = (.+))");
      if (!mem.empty())
      {
        LL crtVal = stoll(mem[1]);
        LL loc = stoll(mem[0]);
      
        if (!partTwo)
        {
          crtVal = applyMask(crtVal, crtMask);
          memory[loc] = crtVal;
        }
        else
        {
          vector<LL> locations = applyMemMask(loc, crtMask);
          for (auto locCell : locations)
            memory[locCell] = crtVal;
        }
      }
    }
    
    LL sum = 0;
    for (auto [m, v] : memory)
      sum += v;

    return sum;
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
      assert(Part1() == "8471403462063");
      assert(Part2() == "2667858637669");
    }
    return ISolutionDay::Test();
  }
};
