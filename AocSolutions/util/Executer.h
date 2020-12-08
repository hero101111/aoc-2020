#pragma once

class Executer
{
public:

  enum class INSTR
  {
    nop = 0,
    acc,
    jmp
  };

  using ISET = vector<pair<INSTR, int>>;
  ISET mInstructions;
  int mAccumulator{ 0 };

  INSTR instrFromString(string str)
  {
    if (str == "acc")
      return INSTR::acc;
    if (str == "jmp")
      return INSTR::jmp;

    return INSTR::nop;
  }

  void ReadData(vector<string> rawInstr)
  {
    for (auto d : rawInstr)
    {
      const auto matches = RegexMatch(d, R"((\w+) (.+))");
      INSTR instr = instrFromString(matches[0]);
      int value = stoi(matches[1]);
      mInstructions.push_back(make_pair(instr, value));
    }
  }

  bool HasAt(LL index, INSTR instr)
  {
    assert(index < mInstructions.size());
    if (index >= mInstructions.size())
      return false;

    return mInstructions[index].first == instr;
  }

  bool SetAt(LL index, pair<INSTR, int> instrData)
  {
    assert(index < mInstructions.size());
    if (index >= mInstructions.size())
      return false;

    mInstructions[index] = instrData;
    return true;
  }

  void Execute(function<bool(Executer &, LL)> ipPred)
  {
    assert(!mInstructions.empty());
    for (int iP = 0; iP <= mInstructions.size();)
    {
      if (ipPred != nullptr && !ipPred(*this, iP))
        return;

      auto& instr = mInstructions[iP];

      if (instr.first == INSTR::acc)
      {
        mAccumulator += instr.second;
        iP += 1;
      }
      else if (instr.first == INSTR::jmp)
      {
        iP += instr.second;
        continue;
      }
      else if (instr.first == INSTR::nop)
      {
        iP += 1;
      }
    }
  }
};