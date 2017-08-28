#pragma once
#include "stdafx.h"
#include <utility>

using std::swap;

/* *
* always n^2
* find smallest remaining, swap
* left of i = final order
* */
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
