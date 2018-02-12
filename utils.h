#include <functional>
#include <chrono>

using namespace std;

void time(const string & operationName, const function<void()> & callback)
{
	auto start = chrono::system_clock::now();
	callback();
	auto end = chrono::system_clock::now();
	auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
	cerr << operationName << " took " << elapsed.count() << " us" << endl;
}

