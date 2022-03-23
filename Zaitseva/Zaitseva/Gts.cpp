#include "Gts.h"

bool DepthFirstSearch(int v, vector<char>& cl, vector<int>& p, int& cycle_st, int& cycle_end, const vector<vector<int>>& g) {
	cl[v] = 1;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			if (DepthFirstSearch(to, cl, p, cycle_st, cycle_end, g))  return true;
		}
		else if (cl[to] == 1) {
			cycle_end = v;
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}

bool Gts::Cyclical()
{
	int n = Edges.size();
	vector<char> cl;
	vector<int> p;
	int cycle_st, cycle_end;
	p.assign(n, -1);
	cl.assign(n, 0);
	cycle_st = -1;
	for (int i = 0; i < n; ++i)
		if (DepthFirstSearch(i, cl, p, cycle_st, cycle_end, Edges))
			break;
	if (cycle_st == -1)
		return false;
	else
		return true;
}

Gts::Gts(const vector<vector<int>>& e)
{
	Edges = e;
}