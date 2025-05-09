#include <bits/stdc++.h>

using namespace std;

void printGrouped(string str)
{
	unordered_map<char, int> cache;
	for(const auto& c : str)
		cache[c]++;
	
	// Printout occurrence in order
	unordered_set<char> set;
	for(const auto& c : str)
	{
		if(!set.count(c))
		{
			set.insert(c);
			while(cache[c]--) cout << c;
		}
	}
	cout << "\n";	
}


int main()
{
	printGrouped("occurrence");
	printGrouped("cdab");
	return 0;
}
