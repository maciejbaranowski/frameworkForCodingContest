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
      auto XMAX = io.readSingle();
      auto YMAX = io.readSingle();
      int odzywienie = 1;
      int X = 1;
      int Y = YMAX;
      io.writeSingle(X);
      io.writeSingle(Y);
      io << "\n";
      auto paleta = io.readLines<int>(YMAX,XMAX);

      auto ruchE = [&] () {
        if (X != XMAX and  paleta[Y-1][X] != 0 and paleta[Y-1][X] > 0 )
        {
          odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
          paleta[Y-1][X-1] = 0;
          X++; io << ('E');
          return true;
        }
        return false;
      };
      auto ruchW = [&] () {
        if (X != 1 and  paleta[Y-1][X-2] != 0 and paleta[Y-1][X-2] > 0 )
        {
          odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
          paleta[Y-1][X-1] = 0;
          X--; io << ('W');
          return true;
        }
        return false;
      };

      auto ruchS = [&] () {
        if (Y != YMAX and  paleta[Y][X-1] != 0 and paleta[Y][X-1] > 0 )
        {
          odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
          paleta[Y-1][X-1] = 0;
          Y++; io << ('S');
          return true;
        }
        return false;
      };
      auto ruchN = [&] () {
        if (Y != 1 and  paleta[Y-2][X-1] != 0 and paleta[Y-2][X-1] > 0 )
        {
          odzywienie = odzywienie + (odzywienie % paleta[Y-1][X-1]);
          paleta[Y-1][X-1] = 0;
          Y--; io << ('N');
          return true;
        }
        return false;
      };
      int licznik = XMAX*YMAX-1;
      while (licznik>0)
      {
        for (int i = 1; i < XMAX; i++)
        {
          ruchE(); licznik--;
        }
        ruchN(); licznik--;
        for (int i = 1; i < XMAX; i++)
        {
          ruchW(); licznik--;
        }
        ruchN(); licznik--;

      }
      io << "\n";
      io.writeSingle(odzywienie);
      io << "\n";

    }
  }

  IO && io;
};
