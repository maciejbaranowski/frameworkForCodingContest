#pragma once

#include "io.h"
#include "utils.h"

class Algorithm {
public:
  explicit Algorithm(IO && _io) :
  io(std::move(_io)) {
    process();
  }

private:
  void process() {
    // ALGORITHM CODE GOES HERE!

    auto n = io.readSingle();
    auto someIntsAsVector = io.readLine(n);
    auto someFloatsAsVector = io.readLine<float>(n);
    auto threeLinesAsVectors = io.readLines(3, n);


    time("Some operations" ,[&](){
      for (int i = 0; i < 10000; i++)
      {
        n += i*i;
      }
    });

    int someIntegerAccessedDirectly, anotherInteger;
    io >> someIntegerAccessedDirectly >> anotherInteger;
    io << anotherInteger << " " << someIntegerAccessedDirectly;

    io.writeLine(someFloatsAsVector);
    io.writeLine(someIntsAsVector);
    io.writeLine(threeLinesAsVectors[1]);
    io.writeSingle(n);
  }

  IO && io;
};
