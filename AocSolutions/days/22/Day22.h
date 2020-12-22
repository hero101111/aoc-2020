#pragma once

#include "SolutionDay.h"

struct Player
{
  deque<LL> cards;
  LL name;
};

class Day22 : public ISolutionDay
{
private:

  //using DataType = DynamicMap<char>;
  using DataType = vector<string>;
  DataType mData;

public:
  
  vector<Player> mPlayers;

  Day22() { }

  ~Day22() override { }

  string GetDay() override
  {
    return "22";
  }
  
  LL calculateScore(pair<int, vector<Player>> winInfo)
  {
    auto & player = winInfo.second[winInfo.first - 1];
    
    assert (!player.cards.empty());
    
    LL score = 0;
    LL mult = 1;
    while (!player.cards.empty())
    {
      LL card = player.cards.back();
      score += mult++ * card;
      player.cards.pop_back();
    }
    return score;
    
    return -1;
  }

  void ReadData()
  {
    mData = DataType();
    
    mPlayers.clear();
    
    int crtPlayer = 0;
    
    mData = rff(GetInputPath());
    
    for (auto d : mData)
    {
      if (d.size() > 5)
      {
        crtPlayer++;
        mPlayers.push_back(Player());
        mPlayers.back().name = crtPlayer;
        continue;
      }
      if (d == "") continue;
      LL card = stoll(d);
      mPlayers.back().cards.push_back(card);
    }
  }
  
  pair<int, vector<Player>> PartOne(vector<Player> players)
  {
    while (true)
    {
      map<LL, LL> cards;
      
      LL max = -1;
      int winnerName = -1;
      bool gameOver = false;
      
      for (auto & player : players)
      {
        if (player.cards.empty())
        {
          gameOver = true;
          break;
        }
      }
    
      if (gameOver)
        break;
      
      for (auto & player : players)
      {
        LL card = player.cards.front();
        player.cards.pop_front();
        cards[player.name] = card;
        
        if (card > max)
        {
          max = card;
          winnerName = (int)player.name;
        }
      }
      
      assert(winnerName >= 1);
      Player & winner = players[winnerName - 1];
      LL winnerCard = cards[winnerName];
      LL otherCard = cards[winnerName == 1 ? 2 : 1];
      winner.cards.push_back(winnerCard);
      winner.cards.push_back(otherCard);
    }
    int winnerName = players[0].cards.empty() ? 2 : 1;
    return make_pair(winnerName, players);
  }
  
  pair<int, vector<Player>> runGame(vector<Player> players)
  {
    vector<pair<deque<LL>, deque<LL>>> prevRounds;
    
    while (true)
    {
      map<LL, LL> cards;
      
      LL max = -1;
      int winnerName = -1;
      bool gameOver = false;
      
      for (auto prevRound : prevRounds)
      {
        if (prevRound.first == players[0].cards && prevRound.second == players[1].cards)
        {
          // wins
          players[1].cards.clear();
          return make_pair(1ll, players);
        }
      }
      prevRounds.push_back(make_pair(players[0].cards, players[1].cards));
      for (auto & player : players)
      {
        if (player.cards.empty())
        {
          gameOver = true;
          break;
        }
      }
    
      if (gameOver)
        break;
      
      for (auto & player : players)
      {
        LL card = player.cards.front();
        player.cards.pop_front();
        cards[player.name] = card;
        
        if (card > max)
        {
          max = card;
          winnerName = (int)player.name;
        }
      }
      
      LL card1 = cards[players[0].name];
      LL card2 = cards[players[1].name];
      if (players[0].cards.size() >= card1 &&
          players[1].cards.size() >= card2)
      {
        vector<Player> newPlayerData = players;
        newPlayerData[0].cards.clear();
        newPlayerData[1].cards.clear();
        vector<Player> newPlayerClone = players;
        for (LL i = 0; i < card1; ++i)
        {
          LL card = newPlayerClone[0].cards.front();
          newPlayerClone[0].cards.pop_front();
          newPlayerData[0].cards.push_back(card);
        }
        for (LL i = 0; i < card2; ++i)
        {
          LL card = newPlayerClone[1].cards.front();
          newPlayerClone[1].cards.pop_front();
          newPlayerData[1].cards.push_back(card);
        }
        
        auto winData = runGame(newPlayerData);
        winnerName = winData.first;
      }
      else
      {
        bool oneWins = card1 > card2;
        if (oneWins)
        {
          winnerName = (int)players[0].name;
        }
        else
        {
          winnerName = (int)players[1].name;
        }
      }
      
      assert(winnerName >= 1);
      Player & winner = players[winnerName - 1];
      LL winnerCard = cards[winnerName];
      LL otherCard = cards[winnerName == 1 ? 2 : 1];
      winner.cards.push_back(winnerCard);
      winner.cards.push_back(otherCard);
    }
    int winnerName = players[0].cards.empty() ? 2 : 1;
    return make_pair(winnerName, players);
  }

  string Part1() override
  {
    ReadData();
    
    auto winData = PartOne(mPlayers);
    LL score = calculateScore(winData);
    return std::to_string(score);
  }

  string Part2() override
  {
    ReadData();
    
    auto winData = runGame(mPlayers);
    LL score = calculateScore(winData);
    return std::to_string(score);
  }

  bool Test() override
  {
    {
      mCurrentInput = "input";
      assert(Part1() == "33400");
      assert(Part2() == "33745");
    }
    return ISolutionDay::Test();
  }
};
