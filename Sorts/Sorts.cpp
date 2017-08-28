// Sorts.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <utility>
#include <numeric>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>

#include <random>
#include <chrono>
#include <fstream>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::swap;
using std::pair;
using std::make_pair;
using std::map;
using std::chrono::high_resolution_clock;

/* * *
* std::sort
*  RandomAccessIterator shall point to a type for which swap is properly 
*  defined and which is both move-constructible and move-assignable.
* 
*  std::swap looks like this in c++11 and above
*  https://stackoverflow.com/a/25286610/128581
*/


// selection sort
//  always n^2
//  find smallest remaining, swap
//  left of i = final order
template <class iter>
void selection_sort(iter &begin, iter &end)
{  
  for (iter start_range = begin; start_range < end; start_range++)
  {
    auto min = start_range;

    for (iter curr = start_range; curr < end; curr++)
    {
      if (*min > *curr)
      {
        min = curr;
      }
    }

    swap(*start_range, *min);
  }
}


// insertion sort
//  n^2 worst/average, n best (already in order)
//  for each i, store j = i, increment j, find any smaller, swap left until sorted
template <class iter>
void insertion_sort(iter &begin, iter &end)
{
  for (iter i = begin; i < end; i++)
  {
    for (iter j = i + 1; j < end; j++)
    {
      if (*i > *j)
      {
        swap(*i, *j);
        
        for (j = i; j > begin; j--)
        {
          if (*j < *(j - 1))
          {
            swap(*j, *(j - 1));
          }
          else
          {
            break;
          }
        }

        break;
      }
    }
  }
}

// shellsort
//  n(log(n))^2 worst/average, n log(n) best 
//  choose items that are h apart (stride length). 
//  for instance = 9 items, h of 3 = 3 sublists
//  sublist 1 = {0, 3, 6}
//  sublist 2 = {1, 4, 7}
//  sublist 3 = {2, 5, 8}
//  insertion sort each one (called an h-sorting).
//  then h-sort with stride of 1 (standard insertion sort)
//  this reduces the over all swap count
//  the actual increment sequence for h is still being researched
//  knuth suggested 3x + 1, we'll go with that
template <class iter>
void shell_sort(iter &begin, iter &end)
{
  vector<size_t> strides{ 1 };
  size_t size = distance(begin, end);
  
  while ((3 * strides.back() + 1) < size)
  {
    strides.push_back(3 * strides.back() + 1);
  }

  for (auto h = strides.rbegin(); h < strides.rend(); h++)
  { 
    // because non-1 strides are a bitch with checked iterators
    auto unchecked_begin = _Unchecked(begin);
    auto unchecked_end = _Unchecked(end);

    for (auto i = unchecked_begin; i < unchecked_end; i+=*h)
    {
      // left of i is already sorted
      for (auto j = (i + *h); j < unchecked_end; j+=*h)
      {
        if (*j < *i)
        { 
          // start swapping back until we're in place
          swap(*j, *(j - *h));

          for (j = (j - *h); j > unchecked_begin; j -= *h)
          {
            if (*j < *(j - *h))
            {
              swap(*j, *(j - *h));
            }
            else
            {
              break;
            }
          }
        }    
      }
    }
  }
}

template<class iter>
void debug_sort(iter sorted_data, iter original_data)
{
  for (auto n : sorted_data)
  {
    cout << n << " ";
  }

  cout << endl;
  cout << "is permutation: ";
  cout << std::boolalpha << std::is_permutation(sorted_data.begin(), sorted_data.end(), original_data.begin());
  cout << endl;
  cout << "is sorted: ";
  cout << std::boolalpha << std::is_sorted(sorted_data.begin(), sorted_data.end());
  cout << endl;
}

int main()
{
  constexpr size_t MAX_INPUT_SIZE = 250;
  constexpr size_t INPUT_STEP = 10;
  constexpr size_t ITERATION_COUNT = 50;

  std::default_random_engine eng;
  std::uniform_int_distribution<int> dis(0, 100);

  using SortTime = pair<int, double>;
  using SortData = vector<int>;
  using Iterator = vector<int>::iterator;
  using SortTimeEntry = pair<string, SortTime>;
  
  map<string, void(*)(Iterator&, Iterator&)> sort_functions {
    {"Selection Sort", &selection_sort<Iterator>},
    {"Insertion Sort", &insertion_sort<Iterator>},
    {"Shell Sort", &shell_sort<Iterator>}
  };

  vector<SortTimeEntry> sort_times;
  
  for (auto sort : sort_functions)
  {
    cout << "Start " << sort.first << endl;
    for (size_t input_size = 2; input_size < MAX_INPUT_SIZE; input_size += INPUT_STEP)
    {
      vector<double> iteration;
      SortData data;

      for (size_t i = 0; i < input_size; i++)
      {
        data.push_back(dis(eng));
      }

      for (size_t i = 0; i < ITERATION_COUNT; i++)
      {
        auto start = high_resolution_clock::now();
        sort.second(data.begin(), data.end());
        std::chrono::duration<double> sort_time = high_resolution_clock::now() - start;
        iteration.push_back(sort_time.count());
      }

      //double average_run_time = std::accumulate(iteration.begin(), iteration.end(), 0.0) / iteration.size();

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

    cout << "CSV of time elapsed written" << endl;
  }
  else
  {
    cout << "Cannot open sort file" << endl;
  }

  cin.get();

  return 0;
}

