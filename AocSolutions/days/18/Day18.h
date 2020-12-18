#pragma once

#include "SolutionDay.h"

enum class Operation
{
  NOP = 0,
  Add,
  Multiply
};

class Day18 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
  using DataType = vector<string>;
  DataType mData;

  
public:

  Day18() { }

  ~Day18() override { }

  string GetDay() override
  {
    return "18";
  }
  
  LL calculateSimpleExp(string expression)
  {
    vector<string> tokens = tok(expression, ' ');
    LL ret = 0;
    Operation op = Operation::NOP;
    for (string t : tokens)
    {
      if (t == "*")
        op = Operation::Multiply;
      else if (t == "+")
        op = Operation::Add;
      else
      {
        if (op == Operation::NOP)
          ret = stoll(t);
        else if (op == Operation::Multiply)
          ret = ret * stoll(t);
        else if (op == Operation::Add)
          ret = ret + stoll(t);
      }
    }
    return ret;
  }
  
  LL calculateSimpleExp2(string expression)
  {
    vector<string> tokens = tok(expression, ' ');
    while (true)
    {
      bool foundPlus = false;
      for (int i = 0; i < expression.size() - 1; ++i)
      {
        char c = expression[i];
        if (c == '+')
        {
          string left, right;
          int j, k;
          
          for (j = i - 2; j >= 0; --j)
            if (j == 0 || expression[j] == ' ')
            {
              left = expression.substr(j, i - j);
              break;
            }
          
          for (k = i + 2; k <= expression.size(); ++k)
            if (k == expression.size() || expression[k] == ' ')
            {
              if (k == expression.size())
                k--;
              right = expression.substr(i + 2, k - i - 1);
              if (k == expression.size() - 1)
                k++;
              break;
            }
          
          string replaceWith = to_string(stoll(left) + stoll(right));
          
          int offset = j == 0 ? 0 : 1;
          expression.replace(j + offset, k - j - offset, replaceWith);
    
          foundPlus = true;
          break;
        }
      }
      if (!foundPlus)
      {
        break;
      }
    }
    return calculateSimpleExp(expression);
  }
  
  string removeExpressionParantheses(string exp, bool partTwo)
  {
    string ret = exp;
    while (true)
    {
      size_t lastLeft = string::npos;
      
      bool noParanthese = true;
      for (size_t i = 0; i < exp.size(); ++i)
      {
        char c = exp[i];
        if (c == '(')
        {
          noParanthese = false;
          lastLeft = i;
        }
        else if (c == ')')
        {
          if (lastLeft != string::npos)
          {
            string toReplace = exp.substr(lastLeft, i - lastLeft + 1);
            string toReplaceEval = toReplace.substr(1, toReplace.size() - 2);
            string replaceWith = removeExpressionParantheses(toReplaceEval, partTwo);
            
            exp = exp.replace(lastLeft, i - lastLeft + 1, replaceWith);
            
            lastLeft = string::npos;
            break;
          }
          
          lastLeft = string::npos;
        }
      }
      if (noParanthese)
      {
        return to_string(partTwo ? calculateSimpleExp2(exp) : calculateSimpleExp(exp));
        break;
      }
    }
    return ret;
  }
  
  LL evalExpression(string exp, bool partTwo)
  {
    string simplified = removeExpressionParantheses(exp, partTwo);
    return calculateSimpleExp2(simplified);
  }

  void ReadData()
  {
    mData = DataType();
    mData = rff(GetInputPath());
  }

  LL DoWork(bool partTwo)
  {
    LL ret = 0;
    
    for (auto d : mData)
    {
      LL value = evalExpression(d, partTwo);
      ret += value;
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
      assert(Part1() == "8298263963837");
      assert(Part2() == "145575710203332");
    }
    return ISolutionDay::Test();
  }
};
