#include <iostream>
#include <string>
#include <array>

#include "algorithm.h"

const array<string, 10> allTestCases = {"01","02","03","04","05","06","07","08","09","10"};

int main(int argc, char** argv)
{
  if (argc > 1)
  {
    string problemName{argv[1]};
    if (argc > 2)
    {
      for (auto i = 2; i < argc; ++i)
      {
        Algorithm({problemName, argv[i]});
      }
    }
    else
    {
      for (auto testCase : allTestCases)
      {
        Algorithm({problemName, testCase});
      }
    }
  }
  else
  {
    Algorithm({});
  }
  return 0;
}