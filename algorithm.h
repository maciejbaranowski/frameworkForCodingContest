#pragma once

#include "io.h"

class Algorithm {
public:
  explicit Algorithm(IO & _io) :
  io(_io)
  {

  }
  void process() {
    auto n = io.readSingle();
    auto someIntsAsVector = io.readLine(n);
    auto someFloatsAsVector = io.readLine<float>(n);

    // ALGORITHM CODE GOES HERE!

    io.writeLine(someFloatsAsVector);
    io.writeLine(someIntsAsVector);
    io.writeSingle(n);
  }
private:
  IO & io;
};
