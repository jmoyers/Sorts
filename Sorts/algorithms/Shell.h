#pragma once
#include "stdafx.h"
#include <iterator>
#include <utility>
#include <vector>
#include <cstddef>

using std::swap;
using std::vector;

/* *
* n(log(n))^2 worst/average, n log(n) best 
* choose items that are h apart (h = stride length). 
* insertion sort each one h-stride array (called an h-sorting).
* then h-sort with stride of 1 (standard insertion sort)
* values for h still researched
* knuth stride = 3x + 1
* */
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
