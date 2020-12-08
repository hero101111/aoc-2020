#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/executer.h"

class Day8 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

public:

  Day8() { }

  ~Day8() override { }

  string GetDay() override
  {
    return "8";
  }

  void ReadData()
  {
    mData = DataType();
    mData = rff(GetInputPath());
  }

  string Part1() override
  {
    ReadData();
    Executer exec;
    exec.ReadData(mData);

    LL accumulator = 0;
    unordered_set<int> executedIps;
    exec.Execute([&](Executer &, LL iP) -> bool
    {
      bool executedAlready = executedIps.find(iP) != end(executedIps);
      if (executedAlready)
        return false;
      executedIps.insert(iP);
      return true;
    });

    return std::to_string(exec.mAccumulator);
  }

  string Part2() override
  {
    ReadData();

    Executer exec;
    exec.ReadData(mData);

    for (int i = 0; i < exec.mInstructions.size(); ++i)
    {
      Executer execTRY = exec;

      if (execTRY.HasAt(i, Executer::INSTR::jmp))
        execTRY.SetAt(i, make_pair(Executer::INSTR::nop, execTRY.mInstructions[i].second));
      else if (execTRY.HasAt(i, Executer::INSTR::nop))
        execTRY.SetAt(i, make_pair(Executer::INSTR::jmp, execTRY.mInstructions[i].second));
      else
        continue;

      bool foundSolution = false;

      unordered_set<int> executedIps;
      execTRY.Execute([&](Executer & crtExecuter, LL iP) -> bool
      {
        bool executedAlready = executedIps.find(iP) != end(executedIps);
        if (executedAlready)
          return false;
        if (iP >= crtExecuter.mInstructions.size())
        {
          foundSolution = true;
          return false;
        }

        executedIps.insert(iP);
        return true;
      });
      
      if (foundSolution)
        return to_string(execTRY.mAccumulator);
      else
        continue;
    }

    return std::to_string(0);
  }

  bool Test() override
  {
    {
      mCurrentInput = "input";
      assert(Part1() == "1766");
      assert(Part2() == "1639");
    }
    return ISolutionDay::Test();
  }
};
