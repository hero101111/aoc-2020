#pragma once

#include "SolutionDay.h"

class Day17 : public ISolutionDay
{
private:

  using DataType = map<Point, bool>;
  DataType mData;

public:

  Day17() { }

  ~Day17() override { }

  string GetDay() override
  {
    return "17";
  }
  
  vector<Point> GetNeighs(Point p, bool is4dimensional)
  {
    vector<Point> ret;
    for (LL z : rangeint(-1, 1))
      for (LL y : rangeint(-1, 1))
        for (LL x : rangeint(-1, 1))
        {
          if (is4dimensional)
          {
            for (LL w : rangeint(-1, 1))
            {
              if (x != 0 || y != 0 || z != 0 || w != 0)
              {
                ret.push_back( { p.x + x, p.y + y, p.z + z, p.w + w} );
              }
            }
          }
          else
          {
            if (x != 0 || y != 0 || z != 0)
              ret.push_back( { p.x + x, p.y + y, p.z + z } );
          }
        }
    return ret;
  }
  
  bool IsActive(DataType & data, Point p)
  {
    if (data.find(p) == end(data)) return false;
    return data[p] == true;
  }
  
  void SetActive(DataType & data, Point p, bool active)
  {
    data[p] = active;
  }
  
  LL GetNeighActiveCount(DataType & data, Point p, bool is4dimensional)
  {
    auto neighs = GetNeighs(p, is4dimensional);
    return count_if(begin(neighs), end(neighs), [&](Point q) { return IsActive(data, q); });
  }
  
  DataType GetDataWithNeighs(DataType & data, bool is4dimensional)
  {
    auto dataCopy = data;
    for (auto [pos, enabled] : data)
    {
      auto neighs = GetNeighs(pos, is4dimensional);
      for (auto n : neighs)
      {
        dataCopy[n] = IsActive(data, n);
      }
    }
    return dataCopy;
  }

  void ReadData()
  {
    mData = DataType();
    DynamicMap<char> inputs;
    
    inputs.fromfile(GetInputPath());
    for (auto [pos, c] : inputs.Traverse())
    {
     if (c == '#')
       mData[pos] = true;
    }
  }

  LL DoWork(bool partTwo)
  {
    LL ret = 0;
    
    int count = 0;
    while (true)
    {
      mData = GetDataWithNeighs(mData, partTwo);
      auto workMap = mData;
      for (auto [p, d] : mData)
      {
        LL activeCount = GetNeighActiveCount(mData, p, partTwo);
        if (IsActive(mData, p))
        {
          if (activeCount == 2 || activeCount == 3)
          {
            // remain active
          }
          else
          {
            SetActive(workMap, p, false);
          }
        }
        else
        {
          if (activeCount == 3)
          {
            SetActive(workMap, p, true);
          }
          else
          {
            // remain inactive
          }
        }
      }
      mData = workMap;
      
      ret = count_if(begin(mData), end(mData), [](auto d){ return d.second == true;});
      
      if (++count == 6)
        break;
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
      assert(Part1() == "232");
      assert(Part2() == "1620");
    }
    return ISolutionDay::Test();
  }
};
