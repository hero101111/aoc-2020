#pragma once

#include "SolutionDay.h"

class Tile
{
public:
  
  DynamicMap<char> data;
  LL label;
  vector<Tile *> upper, lower, left, right;
  
  Tile() { }  
  
  Tile(const Tile & other)
  {
    data = other.data;
    label = other.label;
    upper = other.upper;
    lower = other.lower;
    left = other.left;
    right = other.right;
  }
  
  string UpperBorder()
  {
    return join(data.GetLine(data.min_y));
  }
  
  string LowerBorder()
  {
    return join(data.GetLine(data.max_y));
  }
  
  string LeftBorder()
  {
    return join(data.GetColumn(data.min_x));
  }
  
  string RightBorder()
  {
    return join(data.GetColumn(data.max_x));
  }
  
  void RemoveBorders()
  {
    data.min_x++;
    data.max_x--;
    data.min_y++;
    data.max_y--;
  }
  
  bool operator == (const Tile & other) const
  {
    return (label == other.label) && (data == other.data);
  }
  
  vector<Tile *> GoMaxLeft(vector<Tile *> currentPath)
  {
    if (left.empty())
    {
      currentPath.push_back(this);
      return currentPath;
    }
    
    vector<Tile *> maxRet;
    for (auto * next : left)
    {
      vector<Tile *> path = currentPath;
      path.insert(end(path), this);
      
      auto localRet = next->GoMaxLeft(path);
      if (localRet.size() > maxRet.size())
      {
        maxRet = localRet;
      }
    }
    
    return maxRet;
  }

  vector<Tile *> GoMaxRight(vector<Tile *> currentPath)
  {
    if (right.empty())
    {
      currentPath.push_back(this);
      return currentPath;
    }
    
    vector<Tile *> maxRet;
    for (auto * next : right)
    {
      vector<Tile *> path = currentPath;
      path.insert(end(path), this);
      
      auto localRet = next->GoMaxRight(path);
      if (localRet.size() > maxRet.size())
      {
        maxRet = localRet;
      }
    }
    
    return maxRet;
  }
  
  vector<Tile *> GoMaxDown(vector<Tile *> currentPath)
  {
    if (lower.empty())
    {
      currentPath.push_back(this);
      return currentPath;
    }
    
    vector<Tile *> maxRet;
    for (auto * next : lower)
    {
      vector<Tile *> path = currentPath;
      path.insert(end(path), this);
      
      auto localRet = next->GoMaxDown(path);
      if (localRet.size() > maxRet.size())
      {
        maxRet = localRet;
      }
    }
    
    return maxRet;
  }

  vector<Tile *> GoMaxUp(vector<Tile *> currentPath)
  {
    if (upper.empty())
    {
      currentPath.push_back(this);
      return currentPath;
    }
    
    vector<Tile *> maxRet;
    for (auto * next : upper)
    {
      vector<Tile *> path = currentPath;
      path.insert(end(path), this);
      
      auto localRet = next->GoMaxUp(path);
      if (localRet.size() > maxRet.size())
      {
        maxRet = localRet;
      }
    }
    
    return maxRet;
  }
};

class TileDaddy
{
public:
  
  TileDaddy()
  {
  }
  
  void Add(LL tileId, DynamicMap<char> data)
  {
    Tile wrapper;
    wrapper.data = data;
    wrapper.label = tileId;
    
    allTiles.push_back(wrapper);
  }
  
  void Validate()
  {
    for (auto & wrapper : allTiles)
    {
      auto left = wrapper.LeftBorder();
      auto right = wrapper.RightBorder();
      auto lower = wrapper.LowerBorder();
      auto upper = wrapper.UpperBorder();
      
      leftCache[left].push_back(&wrapper);
      rightCache[right].push_back(&wrapper);
      upperCache[upper].push_back(&wrapper);
      lowerCache[lower].push_back(&wrapper);
    }
    
    for (auto & wrapper : allTiles)
    {
      auto left = wrapper.LeftBorder();
      auto right = wrapper.RightBorder();
      auto lower = wrapper.LowerBorder();
      auto upper = wrapper.UpperBorder();
      
      vector<Tile * > upperCandidates = lowerCache[upper];
      vector<Tile * > lowerCandidates = upperCache[lower];
      vector<Tile * > leftCandidates  = rightCache[left];
      vector<Tile * > rightCandidates = leftCache[right];
      
      for (auto * cand : upperCandidates)
      {
        if (cand->label != wrapper.label)
        {
          wrapper.upper.push_back(cand);
          cand->lower.push_back(&wrapper);
        }
      }
      for (auto * cand : lowerCandidates)
      {
        if (cand->label != wrapper.label)
        {
          wrapper.lower.push_back(cand);
          cand->upper.push_back(&wrapper);
        }
      }
      for (auto * cand : leftCandidates)
      {
        if (cand->label != wrapper.label)
        {
          wrapper.left.push_back(cand);
          cand->right.push_back(&wrapper);
        }
      }
      for (auto * cand : rightCandidates)
      {
        if (cand->label != wrapper.label)
        {
          wrapper.right.push_back(cand);
          cand->left.push_back(&wrapper);
        }
      }
    }
  }
  
  map<string, vector<Tile *>> leftCache, rightCache, upperCache, lowerCache;
  vector<Tile> allTiles;
};

class Day20 : public ISolutionDay
{
private:

  using DataType = vector<string>;
  DataType mData;
  
  using WorkType = map<LL, DynamicMap<char>> ;
  WorkType tiles;

public:

  Day20() { }

  ~Day20() override { }
  
  DynamicMap<char> Flip(DynamicMap<char> m)
  {
    DynamicMap<char> ret;
    for (auto [pos, c] : m.Traverse())
    {
      ret[Point{pos.y, pos.x}] = c;
    }
    return ret;
  }
  
  string GetDay() override
  {
    return "20";
  }

  void ReadData()
  {
    mData = DataType();

    mData = rff(GetInputPath());
    
    LL tileId;
    DynamicMap<char> crtMap;
    mData.push_back("");
    for (auto d : mData)
    {
      if (RegexIsMatch(d, R"(Tile (\d+):)"))
      {
        tileId = stoll(RegexMatch(d, R"(Tile (\d+):)")[0]);
      }
      else if (d == "")
      {
        verbose.close();
        crtMap.fromfile(KVERBOSE);
        tiles[tileId] = crtMap;
        verbose.open(KVERBOSE, ios_base::out);
        crtMap = DynamicMap<char>();
      }
      else
      {
        verbose << d << endl;
      }
    }
  }
  
  vector<DynamicMap<char>> GetRotatedAndFlipped(DynamicMap<char> data)
  {
    vector<DynamicMap<char>> ret;
    for (int count = 0; count < 4; ++count)
    {
      ret.push_back(data);
      ret.push_back(data.flipX());
      ret.push_back(data.flipY());
      data = data.rotateClockwise();
    }
    return ret;
  }
  
  int findMonsters(DynamicMap<char> world)
  {
    DynamicMap<char> monsterPattern;
    monsterPattern.fromfile(KINPUT + GetDay() + "/monster.txt");
    string day = GetDay();
    auto processWorld = [&monsterPattern, day](DynamicMap<char> worldToProcess) -> int
    {
      int monsterCount = 0;
      for (auto [worldPos, worldC] : worldToProcess.Traverse())
      {
        bool hasMonster = true;
        for (auto [monsterPos, monsterC] : monsterPattern.Traverse())
        {
          if (monsterC != '#')
            continue;
          
          char worldChar;
          if (worldToProcess.at({ worldPos + monsterPos }, &worldChar))
          {
            if (worldChar != monsterC)
            {
              hasMonster = false;
              break;
            }
            else
            {
              int debugI = 0;
              debugI++;
            }
          }
          else
          {
            hasMonster = false;
            break;
          }
        }
        if (hasMonster)
        {
          monsterCount++;
          for (auto [monsterPos, monsterC] : monsterPattern.Traverse())
          {
            if (monsterC == '#')
              worldToProcess[{ worldPos + monsterPos }] = 'O';
          }
        }
      }
      if (monsterCount > 0)
      {
        return worldToProcess.for_each([](char c){ return c == '#'; });
      }
      else
      {
        return 0;
      }
    };
    
    auto rotatedAndFlipped = GetRotatedAndFlipped(world);
    for (auto parallelWorld : rotatedAndFlipped)
    {
      int counter = processWorld(parallelWorld);
      if (counter > 0) return counter;
    }
    
    return 0;
  }

  LL DoWork(bool partTwo)
  {
    LL mapN = sqrt(tiles.size());
    
    TileDaddy manager;
    
    auto processMap = [&](LL name, DynamicMap<char> & m)
    {
      manager.Add(name, m);
    };
    
    for (auto & [tileName, tile] : tiles)
    {
      auto rotatedAndFlipped = GetRotatedAndFlipped(tile);
      for (auto & worldData : rotatedAndFlipped)
      {
        processMap(tileName, worldData);
      }
    }
    
    manager.Validate();
    
    auto walk = [&](Tile & tile)
    {
      auto maxRight = tile.GoMaxRight({});
      auto maxLeft  = tile.GoMaxLeft({});
      auto maxUpper = tile.GoMaxUp({});
      auto maxLower = tile.GoMaxDown({});

      return make_tuple(maxUpper.size(), maxUpper.back(), 
                        maxRight.size(), maxRight.back(), 
                        maxLower.size(), maxLower.back(), 
                        maxLeft.size(), maxLeft.back());
    };
    
    Tile* topLeft{}, * topRight{}, * lowerRight{}, * lowerLeft{};
    
    LL part1ret = 1;
    for (auto & tile : manager.allTiles)
    {
      auto [maxUpper, maxUpperO, 
            maxRight, maxRightO,
            maxLower, maxLowerO,
            maxLeft, maxLeftO] = walk(tile);
      
      // found upper left corner
      if (maxRight == mapN && maxLower == mapN && 
          maxLeft == 1 && maxUpper == 1)
      {
        LL l1 = tile.label;
        
        auto [maxUpper2, maxUpperO2, 
              maxRight2, maxRightO2, 
              maxLower2, maxLowerO2, 
              maxLeft2, maxLeftO2] = walk(*maxRightO);
        
        // upper right corner
        if (maxLower2 == mapN && maxLeft2 == mapN && 
            maxUpper2 == 1 && maxRight2 == 1)
        {
          LL l2 = maxRightO->label;
          
          auto [maxUpper3, maxUpperO3, 
                maxRight3, maxRightO3, 
                maxLower3, maxLowerO3, 
                maxLeft3, maxLeftO3] = walk(*maxLowerO2);
          
          // lower right corner
          if (maxLeft3 == mapN && maxUpper3 == mapN && 
              maxRight3 == 1 && maxLower3 == 1)
          {
            LL l3 = maxLowerO2->label;
            
            auto [maxUpper4, maxUpperO4, 
                  maxRight4, maxRightO4, 
                  maxLower4, maxLowerO4, 
                  maxLeft4, maxLeftO4] = walk(*maxLeftO3);
            
            // lower left corner
            if (maxUpper4 == mapN && maxRight4 == mapN &&
                maxLeft4 == 1 && maxLower4 == 1)
            {
              LL l4 = maxLeftO3->label;
              
              part1ret = l1 * l2 * l3 * l4;
              
              topLeft = &tile;         // lower right
              topRight = maxRightO;    // upper right
              lowerRight = maxLowerO2; // upper left
              lowerLeft = maxLeftO3;   // lower right
              
              break;
            }
          }
        }
      }
    }
    
    if (!partTwo)
      return part1ret;
    
    LL part2ret = 1;
    
    map<Point, Tile *> world;
    auto lines = topLeft->GoMaxDown({});
    assert(lines.size() == mapN);
    for (int i = 0; i < lines.size(); ++i)
    {
      Tile * start = lines[i];
      auto crtLine = start->GoMaxRight({});
      assert(crtLine.size() == mapN);
      for (int j = 0; j < crtLine.size(); ++j)
      {
        world[{j, i}] = crtLine[j];
        world[{j, i}]->RemoveBorders();
      }
    }
    
    DynamicMap<char> realWorld;
    for (int y = 0; y < mapN; ++y)
    {
      for (int x = 0; x < mapN; ++x)
      {
        auto worldPart = world[{x, y}];
        
        for (auto [pos, c] : worldPart->data.Traverse())
        {
          realWorld[{x * 8 + pos.x - 1, y * 8 + pos.y - 1}] = c;
        }
      }
    }
    DynamicMap<char> controlTwo;
    part2ret = findMonsters(realWorld);
    return part2ret;
  }

  string Part1() override
  {
    ReadData();

    auto ret = std::to_string(DoWork(false));
    return ret;
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
      assert(Part1() == "2699020245973");
      assert(Part2() == "2012");
    }
    return ISolutionDay::Test();
  }
};
