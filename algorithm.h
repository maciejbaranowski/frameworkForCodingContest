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
      auto liczbaSzeregowych = io.readSingle();
      auto kolejnoscWzrostu = io.readLine(liczbaSzeregowych);
      auto kolejnoscWieku = io.readLine(liczbaSzeregowych);

      vector<vector<int>> szeregiWyjsciowe;

      szeregiWyjsciowe.push_back(kolejnoscWieku);
      szeregiWyjsciowe.push_back(kolejnoscWzrostu);

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
