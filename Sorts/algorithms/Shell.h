#pragma once
#include "stdafx.h"
#include <iterator>
#include <utility>
#include <vector>
#include <cstddef>
#include <set>

using std::swap;
using std::vector;
using std::set;

// https://oeis.org/A102549 - best known
const static set<int> A102549 {
  1, 4, 10, 23, 57, 132, 301, 701, 1750
};

// https://oeis.org/A108870
const static set<int> A108870{
  1, 4, 9, 20, 46, 103, 233, 525, 1182,
  2660, 5985, 13467, 30301, 68178, 153401,
  345152, 776591, 1747331, 3931496, 8845866,
  19903198, 44782196, 100759940, 226709866,
  510097200, 1147718700
};

// https://oeis.org/A033622
const static set<int> A033622{
  1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905,
  8929, 16001, 36289, 64769, 146305, 260609,
  587521, 1045505, 2354689, 4188161, 9427969,
  16764929, 37730305, 67084289, 150958081,
  268386305, 603906049, 1073643521
};

const static set<int> &selected_sequence = A102549;

/* *
* n(log(n))^2 worst/average, n log(n) best 
* choose items that are h apart (h = stride length). 
* insertion sort each one h-stride array (called an h-sorting).
* then h-sort with stride of 1 (standard insertion sort)
* values for h still researched
* */
template <class iter>
void shell_sort(iter &begin, iter &end)
{
  vector<size_t> strides{ 1 };
  auto potential_stride = selected_sequence.begin();
  size_t size = distance(begin, end);

  while (potential_stride != selected_sequence.end() && *potential_stride < size)
  {
    strides.push_back(*potential_stride);
    potential_stride++;
  }

  for (auto h = strides.rbegin(); h < strides.rend(); h++)
  {
    // because non-1 strides are a bitch with checked iterators
    auto unchecked_begin = _Unchecked(begin);
    auto unchecked_end = _Unchecked(end);

    for (auto i = unchecked_begin; i < unchecked_end; i += *h)
    {
      // left of i is already sorted
      for (auto j = (i + *h); j < unchecked_end; j += *h)
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
