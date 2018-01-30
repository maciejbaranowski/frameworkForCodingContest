#pragma once

#include "io.h"
#include <algorithm>

class Algorithm {
public:
  explicit Algorithm(IO & _io) :
  io(_io) {}

  struct Szeregowy {
    int id;
    int wzrost;
    int wiek;
    Szeregowy(int _id, int _wzrost, int _wiek) :
      id(_id),
      wzrost(_wzrost),
      wiek(_wiek)
    {};
    bool operator<(const Szeregowy & s) const
    {
      return this->wiek < s.wiek && this->wzrost < s.wzrost;
    }
    bool operator>(const Szeregowy & s) const
    {
      return this->wiek > s.wiek && this->wzrost > s.wzrost;
    }
  };

  void process() {
    auto liczbaTestow = io.readSingle();
    while (liczbaTestow--)
    {
      auto liczbaSzeregowych = io.readSingle();
      auto dane = io.readLines(2, liczbaSzeregowych);
      vector<Szeregowy> szeregowi;
      szeregowi.reserve(liczbaSzeregowych);
      for (unsigned i = 0; i < liczbaSzeregowych; i++)
      {
        szeregowi.emplace_back(i, dane[0][i], dane[1][i]);
      }

      vector<vector<int>> szeregiWyjsciowe;

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
