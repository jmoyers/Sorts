#pragma once
#include "stdafx.h"
#include "Types.h"
#include "Merge.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <cstddef>

using std::cout;
using std::endl;

namespace SortTests
{

template<class iter>
bool test_sort(iter sorted_data, iter original_data)
{
  for (auto n : original_data)
  {
    cout << n << " ";
  }

  cout << endl;

  for (auto n : sorted_data)
  {
    cout << n << " ";
  }

  bool is_sorted = std::is_sorted(sorted_data.begin(), sorted_data.end());
  bool is_permutation = std::is_permutation(sorted_data.begin(), sorted_data.end(), original_data.begin());

  cout << endl;
  cout << "is permutation: ";
  cout << std::boolalpha << is_permutation;
  cout << endl;
  cout << "is sorted: ";
  cout << std::boolalpha << is_sorted;
  cout << endl;

  return is_sorted && is_permutation;
}

SortData gen_fixture(size_t input_size)
{
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<int> dis(0, 100);
  SortData data;

  for (size_t i = 0; i < input_size; i++)
  {
    data.push_back(dis(eng));
  }

  return data;
}

SortData gen_sorted_fixture(size_t input_size)
{
  auto data = gen_fixture(input_size);
  merge_sort(data.begin(), data.end());
  return data;
}

SortData gen_nearly_sorted_fixture(size_t input_size)
{
  auto data = gen_sorted_fixture(input_size);
  return data;
}

void test_with_input(size_t size, void(*fn)(Iterator&, Iterator&))
{
  constexpr int ENTER = 10;

  do {
    auto fixture = gen_fixture(size);
    auto orig(fixture);

    fn(fixture.begin(), fixture.end());
    test_sort(fixture, orig);
  } while (std::cin.get() == ENTER);
}

} // SortTests