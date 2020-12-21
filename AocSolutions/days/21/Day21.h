#pragma once

#include "SolutionDay.h"

struct Food
{
  set<string> ingredients;
  set<string> allergens;
};

class Day21 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
  using DataType = vector<string>;
  DataType mData;
  
  vector<Food> foods;

public:

  Day21() { }

  ~Day21() override { }

  string GetDay() override
  {
    return "21";
  }
  
  map<string, string> findAllergens()
  {
    map<string, set<string>> potentials;
    
    for (auto f : foods)
    {
      for (auto alerg : f.allergens)
      {
        set<string> & pot = potentials[alerg];
        
        if (pot.empty())
          potentials[alerg] = f.ingredients;
        else
        {
          set<string> intersect;
          set_intersection(begin(pot), end(pot), begin(f.ingredients), end(f.ingredients), inserter(intersect, begin(intersect)));
          potentials[alerg] = intersect;
        }
      }
    }
    
    auto reduceIng = [&](string ingredient, string allergen)
    {
      int ret = 0;
      for (auto & [p, ps] : potentials)
      {
        if (p != allergen)
        {
          auto & coll = potentials[p];
          ret += coll.erase(ingredient);
        }
      }
      return ret;
    };
    
    while (true)
    {
      bool doneWork = false;
      for (auto pIt : potentials)
      {
        if (pIt.second.size() == 1)
        {
          if (reduceIng(*pIt.second.begin(), pIt.first) > 0)
            doneWork = true;
        }
      }
      if (!doneWork)
        break;
    }
    
    map<string, string> ret;
    for (auto [k, v] : potentials)
      ret[*v.begin()] = k;
    
    return ret;
  }

  void ReadData()
  {
    mData = DataType();
    foods.clear();

    mData = rff(GetInputPath());
    
    for (auto d : mData)
    {
      Food food;
      auto [ingredients, allergens] = RegExMatch2(d, R"((.+) \(contains (.+)\))");
      auto ingredientsList = tok(ingredients, ' ');
      for (auto ing : ingredientsList)
        food.ingredients.insert(ing);
      
      auto allergenList = tok(allergens, ',');
      for (auto allerg : allergenList)
      {
        string alergen = trim(allerg);
        food.allergens.insert(alergen);
      }
      
      foods.push_back(food);
    }
  }

  string DoWork(bool partTwo)
  {
    map<string, string> dangerous = findAllergens();
    
    if (!partTwo)
    {
      LL ret = 0;
      for (auto f : foods)
      {
        for (auto ing : f.ingredients)
          if (dangerous.find(ing) == end(dangerous))
            ret++;
      }
      return to_string(ret);
    }
    else
    {
      string ret = "";
            
      set<string> poisons;
      for (auto [k,v] : dangerous)
        poisons.insert(v);
      
      for (auto d : poisons)
        ret += findInMapByValue(dangerous, d)->first + ",";
      
      return ret.substr(0, ret.size() - 1);
    }
  }

  string Part1() override
  {
    ReadData();

    return DoWork(false);
  }

  string Part2() override
  {
    ReadData();

    return DoWork(true);
  }

  bool Test() override
  {
    {
      mCurrentInput = "input";
      assert(Part1() == "2573");
      assert(Part2() == "bjpkhx,nsnqf,snhph,zmfqpn,qrbnjtj,dbhfd,thn,sthnsg");
    }
    return ISolutionDay::Test();
  }
};
