#pragma once

#include "SolutionDay.h"

class MatchRule
{
public:
  
  string name;
  string p1, p2, p3, p4, p5;
  string letter;
  
  enum class Type
  {
    SimpleLetter = 0,
    SimpleOtherRule,
    Compound,
    Piped2,
    Piped4,
    Piped1_2,
    Piped2_3
  };
  
  Type type;
  
  bool operator == (const MatchRule & other) const
  {
    return name == other.name;
  }
  
  bool operator < (const MatchRule & other) const
  {
    return name < other.name;
  }
};

using Rule = MatchRule;

class Day19 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;
  
  map<string, MatchRule> rules;
  vector<string> toValidate;

public:

  Day19() { }

  ~Day19() override { }

  string GetDay() override
  {
    return "19";
  }
  
  pair<bool, string> IsRuleValid(Rule & rule, string data)
  {
    if (rule.type == Rule::Type::SimpleLetter)
    {
      if (data.size() < 1)
        return make_pair(false, data);
      if (data.substr(0, 1) != rule.letter)
        return make_pair(false, data);
      
      return make_pair(true, data.substr(1));
    }
    else if (rule.type == Rule::Type::SimpleOtherRule)
    {
      assert(rules.find(rule.p1) != end(rules));
      Rule & otherRule = rules[rule.p1];
      
      return IsRuleValid(otherRule, data);
    }
    else if (rule.type == Rule::Type::Compound)
    {
      assert(rules.find(rule.p1) != end(rules));
      assert(rules.find(rule.p2) != end(rules));
      Rule & otherRule1 = rules[rule.p1];
      Rule & otherRule2 = rules[rule.p2];
      auto isValid1 = IsRuleValid(otherRule1, data);
      if (!isValid1.first)
        return make_pair(false, data);
      auto isValid2 = IsRuleValid(otherRule2, isValid1.second);
      if (!isValid2.first)
        return make_pair(false, data);
      auto ret = isValid2;
      if (!rule.p3.empty() && !ret.second.empty())
      {
        assert(rules.find(rule.p3) != end(rules));
        Rule & otherRule3 = rules[rule.p3];
        auto isValid3 = IsRuleValid(otherRule3, ret.second);
        if (!isValid3.first)
          return make_pair(false, data);
        ret = isValid3;
      }
      
      return ret;
    }
    else if (rule.type == Rule::Type::Piped2)
    {
      assert(rules.find(rule.p1) != end(rules));
      assert(rules.find(rule.p2) != end(rules));
      Rule & otherRule1 = rules[rule.p1];
      Rule & otherRule2 = rules[rule.p2];
      {
        auto isValid1 = IsRuleValid(otherRule1, data);
        if (isValid1.first)
          return isValid1;
      }
      
      {
        auto isValid2 = IsRuleValid(otherRule2, data);
        if (isValid2.first)
          return isValid2;
      }
      
      return make_pair(false, data);
    }
    else if (rule.type == Rule::Type::Piped4)
    {
      assert(rules.find(rule.p1) != end(rules));
      assert(rules.find(rule.p2) != end(rules));
      assert(rules.find(rule.p3) != end(rules));
      assert(rules.find(rule.p4) != end(rules));
      
      {
        Rule comp1;
        comp1.type = Rule::Type::Compound;
        comp1.name = "temp1";
        comp1.p1 = rule.p1;
        comp1.p2 = rule.p2;
        
        auto isValid1 = IsRuleValid(comp1, data);
        if (isValid1.first)
          return isValid1;
      }
      
      {
        Rule comp2;
        comp2.type = Rule::Type::Compound;
        comp2.name = "temp2";
        comp2.p1 = rule.p3;
        comp2.p2 = rule.p4;
        
        auto isValid2 = IsRuleValid(comp2, data);
        if (isValid2.first)
          return isValid2;
      }
      
      return make_pair(false, data);
    }
    
    else if (rule.type == Rule::Type::Piped1_2)
    {
      assert(rules.find(rule.p1) != end(rules));
      assert(rules.find(rule.p2) != end(rules));
      assert(rules.find(rule.p3) != end(rules));
      
      Rule & otherRule1 = rules[rule.p1];
      {
        auto isValid1 = IsRuleValid(otherRule1, data);
        if (isValid1.first)
          return isValid1;
      }
      {
        Rule comp1;
        comp1.type = Rule::Type::Compound;
        comp1.name = "temp1";
        comp1.p1 = rule.p2;
        comp1.p2 = rule.p3;
        
        auto isValid1 = IsRuleValid(comp1, data);
        if (isValid1.first)
          return isValid1;
      }
      
      return make_pair(false, data);
    }
    
    else if (rule.type == Rule::Type::Piped2_3)
    {
      assert(rules.find(rule.p1) != end(rules));
      assert(rules.find(rule.p2) != end(rules));
      assert(rules.find(rule.p3) != end(rules));
      assert(rules.find(rule.p4) != end(rules));
      assert(rules.find(rule.p5) != end(rules));
      
      {
        Rule comp1;
        comp1.type = Rule::Type::Compound;
        comp1.name = "temp1";
        comp1.p1 = rule.p1;
        comp1.p2 = rule.p2;
        
        auto isValid1 = IsRuleValid(comp1, data);
        if (isValid1.first)
          return isValid1;
      }
      
      {
        Rule comp2;
        comp2.type = Rule::Type::Compound;
        comp2.name = "temp2";
        comp2.p1 = rule.p3;
        comp2.p2 = rule.p4;
        comp2.p3 = rule.p5;
        
        auto isValid2 = IsRuleValid(comp2, data);
        if (isValid2.first)
          return isValid2;
      }
      
      return make_pair(false, data);
    }
    else
    {
      assert(!"Invalid");
    }
  }

  void ReadData(bool partTwo)
  {
    mData = DataType();
    rules.clear();
    toValidate.clear();
    
    mData = rff(GetInputPath());
    
    bool secondPart = false;
    for (auto d : mData)
    {
      if (d == "")
      {
        secondPart = true;
        continue;
      }
      if (partTwo)
      {
        if (d == "8: 42")
          d = "8: 42 | 42 8";
        if (d == "11: 42 31")
          d = "11: 42 31 | 42 11 31";
      }
      if (!secondPart)
      {
        // read rule
        
        if (RegexIsMatch(d, "(\\d+): \"\\w\""))
        {
          auto [ruleId, ruleLetter] = RegExMatch2(d, "(\\d+): \"(\\w)\"");
          MatchRule rule;
          rule.type = MatchRule::Type::SimpleLetter;
          rule.letter = ruleLetter;
          rule.name = ruleId;
          rules[ruleId] = rule;
        }
        else if (RegexIsMatch(d, R"((\d+): (\d+) (\d+) \| (\d+) (\d+) (\d+))"))
        {
          auto [ruleId, r1, r2, r3, r4, r5] = RegExMatch6(d, R"((\d+): (\d+) (\d+) \| (\d+) (\d+) (\d+))");
          MatchRule rule;
          rule.name = ruleId;
          rule.type = MatchRule::Type::Piped2_3;
          rule.p1 = r1;
          rule.p2 = r2;
          rule.p3 = r3;
          rule.p4 = r4;
          rule.p5 = r5;
          rules[ruleId] = rule;
        }
        else if (RegexIsMatch(d, R"((\d+): (\d+) (\d+) \| (\d+) (\d+))"))
        {
          auto [ruleId, r1, r2, r3, r4] = RegExMatch5(d, R"((\d+): (\d+) (\d+) \| (\d+) (\d+))");
          MatchRule rule;
          rule.name = ruleId;
          rule.type = MatchRule::Type::Piped4;
          rule.p1 = r1;
          rule.p2 = r2;
          rule.p3 = r3;
          rule.p4 = r4;
          rules[ruleId] = rule;
        }
        else if (RegexIsMatch(d, R"((\d+): (\d+) \| (\d+) (\d+))"))
        {
          auto [ruleId, r1, r2, r3] = RegExMatch4(d, R"((\d+): (\d+) \| (\d+) (\d+))");
          MatchRule rule;
          rule.name = ruleId;
          rule.type = MatchRule::Type::Piped1_2;
          rule.p1 = r1;
          rule.p2 = r2;
          rule.p3 = r3;
          rules[ruleId] = rule;
        }
        else if (RegexIsMatch(d, R"((\d+): (\d+) \| (\d+))"))
        {
          auto [ruleId, r1, r2] = RegExMatch3(d, R"((\d+): (\d+) \| (\d+))");
          MatchRule rule;
          rule.name = ruleId;
          rule.type = MatchRule::Type::Piped2;
          rule.p1 = r1;
          rule.p2 = r2;
          rules[ruleId] = rule;
        }
        else if (RegexIsMatch(d, R"((\d+): (\d+) (\d+) (\d+))"))
        {
          auto [ruleId, r1, r2, r3] = RegExMatch4(d, R"((\d+): (\d+) (\d+) (\d+))");
          MatchRule rule;
          rule.type = MatchRule::Type::Compound;
          rule.name = ruleId;
          rule.p1 = r1;
          rule.p2 = r2;
          rule.p3 = r3;
          rules[ruleId] = rule;
        }
        else if (RegexIsMatch(d, R"((\d+): (\d+) (\d+))"))
        {
          auto [ruleId, r1, r2] = RegExMatch3(d, R"((\d+): (\d+) (\d+))");
          MatchRule rule;
          rule.type = MatchRule::Type::Compound;
          rule.name = ruleId;
          rule.p1 = r1;
          rule.p2 = r2;
          rules[ruleId] = rule;
        }
        else if (RegexIsMatch(d, R"((\d+): (\d+))"))
        {
          auto [ruleId, r1] = RegExMatch2(d, R"((\d+): (\d+))");
          MatchRule rule;
          rule.type = MatchRule::Type::SimpleOtherRule;
          rule.name = ruleId;
          rule.p1 = r1;
          rules[ruleId] = rule;
        }
        else
        {
          assert(!"Invalid input");
        }
      }
      else
      {
        // read input data to be validated
        toValidate.push_back(d);
      }
    }
    
  }

  LL DoWork()
  {
    LL ret = 0;

    Rule & rule0 = rules["0"s];
    
    for (auto m : toValidate)
    {
      auto isValid = IsRuleValid(rule0, m);
      if (isValid.first && isValid.second.empty())
        ret++;
    }
    return ret;
  }

  string Part1() override
  {
    ReadData(false);

    return std::to_string(DoWork());
  }

  string Part2() override
  {
    ReadData(true);

    return std::to_string(DoWork());
  }

  bool Test() override
  {
    {
      mCurrentInput = "input";
      assert(Part1() == "222");
      assert(Part2() == "339");
    }
    return ISolutionDay::Test();
  }
};
