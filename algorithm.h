#pragma once

#include "io.h"
#include <algorithm>

class Algorithm {
public:
  explicit Algorithm(IO & _io) :
  io(_io) {}

  void process() {
    auto liczbaTestow = io.readSingle();
    while (liczbaTestow--)
    {
      auto liczbaSzeregowych = io.readSingle();
      auto kolejnosc1 = io.readLine(liczbaSzeregowych);
      auto kolejnosc2 = io.readLine(liczbaSzeregowych);

      vector<vector<int>> szeregiWyjsciowe;

      for (auto kolejnosc1element : kolejnosc1)
      {
        auto dodane = false;
        for (auto& szereg : szeregiWyjsciowe)
        {
          auto czyMoznaDodac = all_of(szereg.begin(), szereg.end(),[&](const auto szeregowy){
            return find(kolejnosc2.begin(), kolejnosc2.end(), szeregowy) < find(kolejnosc2.begin(), kolejnosc2.end(), kolejnosc1element);
          });
          if (czyMoznaDodac)
          {
            szereg.push_back(kolejnosc1element);
            dodane = true;
            break;
          }
        }
        if(!dodane)
        {
          szeregiWyjsciowe.push_back({kolejnosc1element});
        }
      }
      io.writeSingle(szeregiWyjsciowe.size());
      io.os << endl;
      for (auto szereg : szeregiWyjsciowe)
      {
        io.writeSingle(szereg.size());
        io.writeLine(szereg);
      }
    }
  }

private:
  IO & io;
};
