#pragma once

#include "io.h"
#include "utils.h"
#include <limits>
#include <algorithm>

class Algorithm {
public:
  explicit Algorithm(IO && _io) :
  io(std::move(_io)) {
    process();
  }

private:
  void process() {
    auto T = io.readSingle();
    while (T-->0)
    {
      int odzywienie = 1;
      int X = 1;
      int Y = 1;
      io.writeSingle(X);
      io.writeSingle(Y);
      io << "\n";
      auto XMAX = io.readSingle();
      auto YMAX = io.readSingle();
      auto paleta = io.readLines<int>(YMAX,XMAX);

      while (true)
      {
        for (int i = 1; i < XMAX; i++)
        {
          odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
          X++; io << ('E');
        }
        odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
        if (Y == YMAX)
          break;
        Y++; io << ('S');
        for (int i = 1; i < XMAX; i++)
        {
          odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
          X--; io << ('W');
        }
        odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
        if (Y == YMAX)
          break;
        Y++; io << ('S');

      }
      io << "\n";
      io.writeSingle(odzywienie);
      io << "\n";
    }
  }

  IO && io;
};
