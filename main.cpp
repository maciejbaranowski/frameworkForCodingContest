#include <iostream>
#include <vector>

using namespace std;


class IO
{
public:
  template<typename T = int>
	static vector<T> readLine(unsigned numberOfElements)
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
	static T readSingle()
	{
    T value;
    cin >> value;
    return value;
	}

  template<typename T>
  static void writeLine(const vector<T>& output)
  {
    for (auto element : output)
    {
      writeSingle(element);
    }
    cout << endl;
  }

  template<typename T>
  static void writeSingle(T output)
  {
    cout << output << " ";
  }
};

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