#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <type_traits>

using namespace std;

class IO
{
public:
  IO()
  {
    is.basic_ios<char>::rdbuf(cin.rdbuf());
    os.basic_ios<char>::rdbuf(cout.rdbuf());
  }

  IO(string problemName, string testCase)
  {
    cerr << "** Problem: " << problemName << " testcase: " << testCase << " started" << endl;
    string fileNameBase{problemName+testCase+"."};
    os.open(fileNameBase+"out");
    if (!os.good())
    {
      cerr << "** WARNING! Could not open output file!";
    }
    is.open(fileNameBase+"in");
    if (!is.good())
    {
      cerr << "** WARNING! Could not open input file!";
    }
  }

  ~IO()
  {
    os.close();
    is.close();
  }

  IO(const IO& srcIo)
  {
    is.basic_ios<char>::rdbuf(srcIo.is.rdbuf());
    os.basic_ios<char>::rdbuf(srcIo.os.rdbuf());
  }

  template<typename T = int>
  vector<vector<T>> readLines(unsigned numberOfLines, unsigned numberOfElements)
  {
    vector<vector<T>> output;
    output.reserve(numberOfLines);
    while (numberOfLines--)
    {
      output.push_back(readLine<T>(numberOfElements));
    }
    return output;
  }

  template<typename T = int>
  vector<T> readLine(unsigned numberOfElements)
  {
    vector<T> output;
    output.reserve(numberOfElements);
    while (numberOfElements--)
    {
      output.push_back(readSingle<T>());
    }
    return output;
  }

  template<typename T = int>
  T readSingle()
  {
    static_assert(is_fundamental<T>::value, "Wrong type provided");
    T value;
    is >> value;
    return value;
  }

  template<typename T>
  void writeLine(const vector<T>& output)
  {
    for (auto element : output)
    {
      writeSingle(element);
    }
    os << endl;
  }

  template<typename T>
  void writeSingle(T output)
  {
    static_assert(is_fundamental<T>::value, "Wrong type provided");
    os << output << " ";
  }

  ifstream is;
  ofstream os;
};

const vector<string> allTestCases = {"01","02","03","04","05","06","07","08","09","10"};

vector<IO> buildIoControllers(int argc, char** argv)
{
  vector<IO> result = {};
  if (argc > 1)
  {
    string problemName{argv[1]};
    if (argc > 2)
    {
      for (auto i = 2u; i < argc; ++i)
      {
        result.emplace_back(problemName, argv[i]);
      }
    }
    else
    {
      for (auto testCase : allTestCases)
      {
        result.emplace_back(problemName, testCase);
      }
    }
  }
  else
  {
    result.emplace_back();
  }
  return result;
}
