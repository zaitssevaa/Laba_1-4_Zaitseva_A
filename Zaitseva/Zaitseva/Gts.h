#pragma once
#include"input.h"
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

class Gts
{
	vector<vector<int>> Edges;
public:
	bool Cyclical();

	Gts(const vector<vector<int>>& e);
};