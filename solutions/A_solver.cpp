#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

const int MAX_N = 1000000;

int main(int argc, char **)
{
	int cases;
	scanf("%d", &cases);
	while (cases--)
	{
		int n;
		scanf("%d", &n);
		assert(1 <= n && n <= MAX_N);
		vector<int> index(n + 1);
		vector<int> revIndex(n + 1);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &index[i]);
			revIndex[index[i]] = i;
		}
		
		vector<int> v(n + 1);
		for (int i = 1; i <= n; ++i)
		{
			int x;
			scanf("%d", &x);
			v[i] = revIndex[x];
		}
		
		vector<vector<int> > res;
		for (int i = 1; i <= n; ++i)
		{
			const int u = v[i];
			
			// find the place
			int left = -1;
			int right = (int)res.size();
			while (left + 1 < right)
			{
				const int mid = (left + right) / 2;
				if (res[mid].back() < u)
				{
					right = mid;
				}
				else
				{
					left = mid;
				}
			}
			
			// insert the value
			if (right == (int)res.size())
			{
				res.push_back(vector<int>());
			}
			res[right].push_back(u);
		}
		
		printf("%d\n", (int)res.size());
		for (unsigned i = 0; i < res.size(); ++i)
		{
			printf("%d", (int)res[i].size());
			for (unsigned j = 0; j < res[i].size(); ++j)
			{
				printf(" %d", index[res[i][j]]);
			}
			printf("\n");
		}
	}
	return 0;
}
