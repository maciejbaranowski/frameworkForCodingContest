#include <iostream>
#include "io.h"

int main(int argc, char** argv)
{
  //example usage:
  auto n = IO::readSingle();
  auto someIntsAsVector = IO::readLine(n);
  auto someFloatsAsVector = IO::readLine<float>(n);
  IO::writeLine(someFloatsAsVector);
  IO::writeLine(someIntsAsVector);
  IO::writeSingle(n);
	return 0;
}