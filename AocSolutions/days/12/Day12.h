#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day12 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
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
    mData = DataType();

    mData = rff(GetInputPath());
    for (auto d : mData)
    {
      auto [dir, quant] = RegExMatch2(d, R"((\w)(\d+))");
      dirs.push_back(make_pair(dir[0], stoi(quant)));
    }
    //mData.fromfile(GetInputPath());
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

  LL DoWork()
  {
    LL ret = 121;

    char direction = 'E';
    Point location;
    for (auto d : dirs)
    {
      switch (d.first)
      {
      case 'N':
        location.y += d.second;
        break;
      case 'S':
        location.y -= d.second;
        break;
      case 'E':
        location.x += d.second;
        break;
      case 'W':
        location.x -= d.second;
        break;
      case 'L':
        direction = RotateDirection(direction, -d.second);
        break;
      case 'R':
        direction = RotateDirection(direction, d.second);
        break;
      case 'F':
        switch (direction)
        {
        case 'N':
          location.y += d.second;
          break;
        case 'S':
          location.y -= d.second;
          break;
        case 'E':
          location.x += d.second;
          break;
        case 'W':
          location.x -= d.second;
          break;
        }
        break;
      }
    }
    ret =  manhattan(0, 0, location.x, location.y);

    return ret;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork());
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork());
  }

  bool Test() override
  {
    {
      mCurrentInput = "test";
      //assert(Part1() == "25");
      //assert(Part2() == "");
    }
    {
      mCurrentInput = "test2";
      //assert(Part1() == "");
      //assert(Part2() == "");
    }
    {
      mCurrentInput = "input";
      //assert(Part1() == "");
      //assert(Part2() == "");
    }
    return ISolutionDay::Test();
  }
};
