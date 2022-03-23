#pragma once
#include"input.h"
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class Gts
{
	vector<vector<int>> ribs;

public:

	void TopologicalSort(const unordered_map<int, int>& VerticesIndex);

	Gts(const vector<vector<int>>& e);
};

