#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day12 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;

  vector<pair<char, int>> dirs;

public:

  Day12() { }

  ~Day12() override { }

  string GetDay() override
  {
    return "12";
  }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
    dirs.clear();
    for (auto d : mData)
    {
      auto [dir, quant] = RegExMatch2(d, R"((\w)(\d+))");
      dirs.push_back(make_pair(dir[0], stoi(quant)));
    }
  }

  char RotateDirection(char dir, int rot)
  {
    vector<char> dirs = { 'E', 'S', 'W', 'N' };
    int start = find(dirs.begin(), dirs.end(), dir) - begin(dirs);
    int steps = rot / 90;
    int crtIndex = start;
    while (steps != 0)
    {
      if (steps > 0)
      {
        crtIndex += 1;
        steps--;
      }
      else if (steps < 0)
      {
        crtIndex -= 1;
        steps++;
      }
      
      if (crtIndex == dirs.size())
        crtIndex = 0;
      if (crtIndex == -1)
        crtIndex = dirs.size() - 1;

      if (steps == 0)
        break;
    }
    auto ret = dirs[crtIndex];
    return ret;
  }

  void Walk(Point & location, char walkDir, int quant)
  {
    switch (walkDir)
    {
    case 'N':
      location.y += quant;
      break;
    case 'S':
      location.y -= quant;
      break;
    case 'E':
      location.x += quant;
      break;
    case 'W':
      location.x -= quant;
      break;
    default:
      assert(!"invalid");
    }
  }

  LL DoWork(bool partTwo)
  {
    Point location, waypoint{ 10, 1 };
    char direction = 'E';
    for (auto [dir, quant] : dirs)
    {
      if (dir == 'F')
      {
        if (partTwo)
        {
          Point diff = waypoint;
          for (auto i : rangeint(1, quant))
            location = location + diff;
        }
        else
        {
          Walk(location, direction, quant);
        }
      }
      else if (dir == 'L')
      {
        if (partTwo)
        {
          waypoint = waypoint.GetRotatedAround(Point(), -quant);
        }
        else
        {
          direction = RotateDirection(direction, -quant);
        }
      }
      else if (dir == 'R')
      {
        if (partTwo)
        {
          waypoint = waypoint.GetRotatedAround(Point(), quant);
        }
        else
        {
          direction = RotateDirection(direction, quant);
        }
      }
      else
      {
        Walk(partTwo ? waypoint : location, dir, quant);
      }
    }    
    LL ret = manhattan(0, 0, location.x, location.y);
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
      assert(Part1() == "381");
      assert(Part2() == "28591");
    }
    return ISolutionDay::Test();
  }
};
