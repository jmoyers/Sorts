#pragma once
#include "stdafx.h"
#include <utility>
#include <vector>
#include <string>
#include <map>

using SortTime = std::pair<int, double>;
using SortData = std::vector<int>;
using Iterator = std::vector<int>::iterator;
using SortTimeEntry = std::pair<std::string, SortTime>;
using AlgorithmList = std::map<std::string, void(*)(Iterator&, Iterator&)>;