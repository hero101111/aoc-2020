#pragma once

#include "SolutionDay.h"

class Day24 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;
  
  unordered_map<Point, bool> flippedTiles;

public:

  Day24() { }

  ~Day24() override { }

  string GetDay() override
  {
    return "24";
  }
  
  void ProcessLine(string directions)
  {
    Point crt;
    string s = directions;
    
    while (!s.empty())
    {
      char dir = s.front();
      switch (dir)
      {
        case 's':
        {
          crt.y -=2;
          s.erase(s.begin());
          char subdir = s.front();
          switch (subdir)
          {
            case 'e':
              crt.x -= 1;
              break;
            case 'w':
              crt.x += 1;
              break;
            default:
              assert(!"Unsupported");
          }
          break;
        }       
        case 'n':
        {
          crt.y += 2;
          s.erase(s.begin());
          char subdir = s.front();
          switch (subdir)
          {
            case 'e':
              crt.x -= 1;
              break;
            case 'w':
              crt.x += 1;
              break;
            default:
              assert(!"Unsupported");
          }
          break;
        }
        case 'e':
          crt.x -= 2;
          break;
        case 'w':
          crt.x += 2;
          break;
        default:
          assert(!"Unsupported");
      }
      s.erase(s.begin());
    }
    
    if (flippedTiles.find(crt) == end(flippedTiles))
      flippedTiles[crt] = true;
    else
      flippedTiles[crt] = !flippedTiles[crt];
  }

  void ReadData()
  {
    mData = DataType();
    flippedTiles.clear();
    //mData.fromfile(GetInputPath());
    mData = rff(GetInputPath());
    
    for (auto d : mData)
      ProcessLine(d);
    
  }

  LL DoWork(bool partTwo)
  {
    auto addWhiteIfNotPresent = [&](Point p)
    {
      if (flippedTiles.find(p) == end(flippedTiles))
        flippedTiles[p] = false;
    };
    
    for (int i = 0; i < (partTwo ? 100 : 0); ++i)
    {
      auto tiles = flippedTiles;
      
      // insert white tiles
      for (auto [tile, isBlack] : tiles)
      {
        if (isBlack)
        {
          // east
          addWhiteIfNotPresent(tile + Point{ -2, 0 });
          
          // west
          addWhiteIfNotPresent(tile + Point{ 2, 0 });
          
          // northwest
          addWhiteIfNotPresent(tile + Point{ 1, 2 });
          
          // northeast
          addWhiteIfNotPresent(tile + Point{ -1, 2 });
          
          // southwest
          addWhiteIfNotPresent(tile + Point{ 1, -2});
          
          // southeast
          addWhiteIfNotPresent(tile + Point{-1, -2});
        }
      }
      tiles = flippedTiles;
      
      for (auto [tile, isBlack] : tiles)
      {
        int adjacent = 0;
        int adjacentBlack = 0;
        for (auto [tile2, isBlack2] : tiles)
        {
          if (tile == tile2) continue;
          double d = tile.DistanceTo(tile2);
          double sq5 = sqrt(5);
          
          bool adj = false;
          if (d == 2 || d == sq5)
            adj = true;
          
          if (adj) adjacent++;
          
          if (adj && isBlack2)
            adjacentBlack++;
        }
        assert(adjacent <= 6);
        if (isBlack && (adjacentBlack == 0 || adjacentBlack > 2))
            flippedTiles[tile] = false;
        if (!isBlack && adjacentBlack == 2)
            flippedTiles[tile] = true;
      }
    }
    
    LL blackTileCount = 0;
    for (auto [tile, isBlack] : flippedTiles)
      if (isBlack)
        blackTileCount++;
    return blackTileCount;
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
      assert(Part1() == "424");
      auto p2 = Part2();
      assert(p2 == "3737");
    }
    return ISolutionDay::Test();
  }
};
