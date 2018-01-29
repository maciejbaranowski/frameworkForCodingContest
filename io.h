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