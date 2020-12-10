#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day10 : public ISolutionDay
{
private:

  using DataType = vector<LL>;
  DataType mData;

public:

  Day10() { }

  ~Day10() override { }

  string GetDay() override
  {
    return "10";
  }

  void ReadData()
  {
    mData = DataType();
    mData = rffll(GetInputPath());
  }

  LL DoWork(bool partTwo)
  {
    LL ret = 0;

    map<string, int> nodes;
    Graph<string> g(mData.size() + 2);

    LL maxE = *max_element(begin(mData), end(mData)) + 3;
    mData.push_back(maxE);
    mData.push_back(0);
    int crt = 0;
    for (auto d : mData)
    {
      nodes[to_string(d)] = d;
    }

    for (const auto i : nodes)
    {
      for (const auto j : nodes)
      {
        auto node1 = i.first;
        auto node2 = j.first;
        if (node1 != node2)
        {
          int dist = j.second - i.second;
          if (dist > 0 && dist <= 3)
          {
            g.AddEdge(node1, node2, dist);
          }
        }
      }
    }

    auto path = g.SortTopologically();
    
    if (!partTwo)
    {
      int diff1 = 0;
      int diff3 = 0;

      for (int i = 0; i < path.size() - 1; ++i)
      {
        auto & node = path[i];
        auto & nextNode = path[i + 1];

        int dist = nodes[nextNode] - nodes[node];
        if (dist == 1)
          diff1++;
        if (dist == 3)
          diff3++;
      }
      ret = diff1 * diff3;
    }
    else
    {
      vector<pair<string, string>> intervals;
      string L, R;
      for (int i = 0; i < path.size(); ++i)
      {
        auto & n = path[i];

        auto from = g.GetEdgesFrom(n);

        if (L.empty() && from.size() > 1)
        {
          L = n;
          continue;
        }

        if (!L.empty() && path[i - 1] == L)
        {
          continue;
        }

        if (!L.empty() && nodes[n] - nodes[path[i - 2]] >= 3)
        {
          R = path[i - 1];
          intervals.push_back(make_pair(L, R));
          L.clear();
          R.clear();
          i -= 1;
        }
      }

      ret = 1;
      for (auto interval : intervals)
        ret *= g.CountPaths(interval.first, interval.second);
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
      assert(Part1() == "2482");
      assert(Part2() == "96717311574016");
    }
    return ISolutionDay::Test();
  }
};
