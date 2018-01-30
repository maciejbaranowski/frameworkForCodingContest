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

      vector<int> wybraniA;
      vector<int> wybraniB;

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
