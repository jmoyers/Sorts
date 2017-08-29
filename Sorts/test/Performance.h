#pragma once
#include "Types.h"
#include "Test.h"
#include "Selection.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"
#include "Quick.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;

namespace SortPerformance
{

#ifdef _DEBUG
constexpr size_t MAX_INPUT_SIZE   = 1000;
constexpr size_t INPUT_STEP       = 100;
constexpr size_t ITERATION_COUNT  = 20;
#else
constexpr size_t MAX_INPUT_SIZE = 1000 * 10;
constexpr size_t INPUT_STEP = 100 * 10;
constexpr size_t ITERATION_COUNT = 20;
#endif

void measure_sorts(AlgorithmList sort_functions = AlgorithmList({
  { "Selection Sort", &selection_sort<Iterator> },
  { "Insertion Sort", &insertion_sort<Iterator> },
  { "Shell Sort", &shell_sort<Iterator> },
  { "Merge Sort", &merge_sort<Iterator> },
  { "Quick Sort", &quick_sort<Iterator> },
  { "std::sort", &std::sort<Iterator&> }
}), size_t max_input_size = MAX_INPUT_SIZE
  , size_t input_step = INPUT_STEP
  , size_t iteration_count = ITERATION_COUNT)
{
  vector<SortTimeEntry> sort_times;

  for (auto sort : sort_functions)
  {
    cout << "Start " << sort.first << endl;
    for (size_t input_size = 2; input_size < max_input_size; input_size += input_step)
    {
      vector<double> iteration;
      SortData data = SortTests::gen_fixture(input_size);

      for (size_t i = 0; i < iteration_count; i++)
      {
        auto start = std::chrono::steady_clock::now();
        sort.second(data.begin(), data.end());
        auto diff = std::chrono::steady_clock::now() - start;
        std::chrono::duration<double> sort_time(diff);
        iteration.push_back(sort_time.count());
      }

      for (auto i = iteration.begin(); i < iteration.end(); i++)
      {
        SortTime run_time{ input_size, *i };
        SortTimeEntry entry{ sort.first, run_time };
        sort_times.push_back(entry);
      }

      cout << input_size << " done." << endl;
    }
  }

  std::ofstream csv;
  csv.open("sort_times.csv");

  if (csv)
  {
    csv << "Algorithm,Input Size,Time Elapsed" << endl;
    for (auto time : sort_times)
    {
      csv << time.first << "," << time.second.first << "," << time.second.second << endl;
    }

    csv.close();
  }
  else
  {
    cout << "Cannot open sort file" << endl;
  }
}

} // SortPerformance