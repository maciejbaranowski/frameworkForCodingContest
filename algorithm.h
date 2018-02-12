#pragma once

#include "io.h"
#include "utils.h"

class Algorithm {
public:
  explicit Algorithm(IO & _io) :
  io(_io) {}

  void process() {
    auto n = io.readSingle();
    auto someIntsAsVector = io.readLine(n);
    auto someFloatsAsVector = io.readLine<float>(n);
    auto threeLinesAsVectors = io.readLines(3, n);

    // ALGORITHM CODE GOES HERE!
    // if accessing stream directly seems more convenient than provided functions use:
    // io.is >> input;
    // io.os << output;
    time("Some operations" ,[&](){
      for (int i = 0; i < 100; i++)
      {
        io.os << i*i << endl;
      }
    });

    io.writeLine(someFloatsAsVector);
    io.writeLine(someIntsAsVector);
    io.writeLine(threeLinesAsVectors[1]);
    io.writeSingle(n);
  }

private:
  IO & io;
};
