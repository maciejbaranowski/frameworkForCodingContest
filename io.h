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
    os.open(fileNameBase+"ans");
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

  template<typename T>
  IO& operator<<(const T & output)
  {
    os << output;
    return *this;
  }

  template<typename T>
  IO& operator>>(T & input)
  {
    is >> input;
    return *this;
  }

private:
  ifstream is;
  ofstream os;
};
