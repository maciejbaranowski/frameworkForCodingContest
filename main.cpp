#include <iostream>
#include "io.h"
#include "algorithm.h"

int main(int argc, char** argv)
{
  auto ios = buildIoControllers(argc, argv);
  for (auto& io : ios)
  {
    auto a = Algorithm{io};
    a.process();
  }
	return 0;
}