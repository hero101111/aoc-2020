#pragma once

#include "SolutionDay.h"

class Day16 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

  vector<tuple<LL, LL, LL, LL>> dataIntervals;
  vector<vector<LL>>            nearbyTickets;
  vector<LL>                    myTicket;
  vector<vector<int>>           intervalFieldCandidates;
  vector<int>                   solutionPartTwo;

  enum class Step
  {
    Intervals = 0,
    Ticket,
    Nearby
  };

public:

  Day16() { }

  ~Day16() override { }

  string GetDay() override
  {
    return "16";
  }

  void ReadData()
  {
    mData = DataType();
    mData = rff(GetInputPath());
  }

  bool IsInRange(LL val)
  {
    for (auto [l1, l2, l3, l4] : dataIntervals)
    {
      if ((val >= l1 && val <= l2) || (val >= l3 && val <= l4))
      return true;
    }
    return false;
  }


  bool IsInRange(LL val, tuple<LL, LL, LL, LL> interval)
  {
    auto [l1, l2, l3, l4] = interval;
 
    if ((val >= l1 && val <= l2) || (val >= l3 && val <= l4))
      return true;
   
    return false;
  }

  bool IsIndexCandidate(tuple<LL, LL, LL, LL> help, int index)
  {
    bool satisfiesAll = true;
    for (auto ticket : nearbyTickets)
    {
      auto field = ticket[index];
      satisfiesAll &= IsInRange(field, help);
      if (!satisfiesAll)
        break;
    }
    if (satisfiesAll)
      return true;
    return false;
  }

  vector<int> GetIndexCandidates(tuple<LL, LL, LL, LL> help)
  {
    vector<int> ret;
    for (int i : rangeint(0, myTicket.size() - 1))
      if (IsIndexCandidate(help, i))
        ret.push_back(i);
    return ret;
  }

  bool IsSolutionValid(vector<int> intervalFields)
  {
    for (int i : rangeint(0, intervalFields.size() - 1))
    {
      auto& interval = dataIntervals[i];
      auto intervalField = intervalFields[i];
      for (auto & ticket : nearbyTickets)
      {
        auto field = ticket[intervalField];
        bool inRange = IsInRange(field, interval);
        if (!inRange)
          return false;
      }
    }
    return true;
  }

  bool Solve(int crtIntervalIndex, vector<int> pastIntervals)
  {
    if (crtIntervalIndex == dataIntervals.size())
    {
      if (IsSolutionValid(pastIntervals))
      {
        solutionPartTwo = pastIntervals;
        return true;
      }
      else
        return false;
    }
    else
    {
      auto & interval = dataIntervals[crtIntervalIndex];
      auto & cand = intervalFieldCandidates[crtIntervalIndex];
      vector<int> newIntervals(pastIntervals.size());
      for (int i : rangeint(0, pastIntervals.size() - 1))
        newIntervals[i] = pastIntervals[i];

      for (auto c : cand)
      {
        if (find(begin(pastIntervals), end(pastIntervals), c) != end(pastIntervals))
          continue;

        vector<int> candIntervals = newIntervals;
        candIntervals.push_back(c);
        bool solved = Solve(crtIntervalIndex + 1, candIntervals);
        if (solved)
          return true;
      }
    }
    return false;
  }

  LL DoWork(bool partTwo)
  {
    LL ret = 0;

    Step step = Step::Intervals;

    for (auto d : mData)
    {
      if (d == "your ticket:")
      {
        step = Step::Ticket;
        continue;
      }
      if (d == "nearby tickets:")
      {
        step = Step::Nearby;
        continue;
      }
      if (d == "")
      {
        continue;
      }
      if (step == Step::Intervals)
      {
         const auto [l1, l2, l3, l4] = RegExMatch4(d, R"(.+: (\d+)-(\d+) or (\d+)-(\d+))");
         dataIntervals.push_back(make_tuple(stoll(l1), stoll(l2), stoll(l3), stoll(l4)));
      }
      if (step == Step::Ticket)
      {
        myTicket = stoll(tok(d, ','));
      }

      if (step == Step::Nearby)
      {
        bool invalidTicket = false;
        auto tokens = tok(d, ',');
        for (auto t : tokens)
        {
          LL val = stoll(t);
          if (!IsInRange(val))
          {
            if (!partTwo)
            {
              ret += val;
            }
            invalidTicket = true;
            break;
          }
        }
        if (invalidTicket) continue;
        nearbyTickets.push_back(stoll(tokens));
      }
    }

    if (partTwo)
    {
      for (auto& interval : dataIntervals)
      {
        vector<int> cand = GetIndexCandidates(interval);
        intervalFieldCandidates.push_back(cand);
      }

      Solve(0, {});

      ret = 1;
      for (int i : rangeint(0, 5))
        ret *= myTicket[solutionPartTwo[i]];
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
      assert(Part1() == "24110");
      assert(Part2() == "6766503490793");
    }
    return ISolutionDay::Test();
  }
};
