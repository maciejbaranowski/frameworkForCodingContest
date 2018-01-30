#pragma once

#include "io.h"

class Algorithm {
public:
  explicit Algorithm(IO & _io) :
  io(_io) {}

  void process() {
    auto liczbaTestow = io.readSingle();
    while (liczbaTestow--)
    {
      auto liczbaPoslow = io.readSingle();
      auto liczbaKandydatowA = io.readSingle();
      auto liczbaKandydatowB = io.readSingle();
      auto glosPerPosel = io.readLines(liczbaPoslow,4);

      vector<int> glosPerKandydatA(liczbaKandydatowA);
      vector<int> glosPerKandydatB(liczbaKandydatowB);
      for (auto glos : glosPerPosel)
      {
        if(glos[0] == 1)
        {
          glosPerKandydatA[glos[1]]++;
        }
        else
        {
          glosPerKandydatB[glos[1]]++;
        }
        if(glos[2] == 1)
        {
          glosPerKandydatA[glos[3]]--;
        }
        else
        {
          glosPerKandydatB[glos[3]]--;
        }

      }

      vector<int> wybraniA;
      vector<int> wybraniB;

      for (unsigned i = 0; i < liczbaKandydatowA; i++)
      {
        if (glosPerKandydatA[i] > 0)
        {
          wybraniA.push_back(i);
        }
      }
      for (unsigned i = 0; i < liczbaKandydatowB; i++)
      {
        if (glosPerKandydatB[i] > 0)
        {
          wybraniB.push_back(i);
        }
      }
      io.writeSingle(wybraniA.size());
      io.os << endl;
      io.writeLine(wybraniA);
      io.writeSingle(wybraniB.size());
      io.os << endl;
      io.writeLine(wybraniB);
    }
  }

private:
  IO & io;
};
