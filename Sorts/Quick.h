#pragma once
#pragma once
#include "stdafx.h"
#include <utility>

using std::swap;

template <class iter>
iter partition(iter &begin, iter &end)
{  
  auto p = begin;
  auto l = p + 1;
  auto r = end - 1;

  for (;;)
  {    
    while (l < r && *p >= *l)
    {
      l++;
    }
    
    while (r >= l && *p < *r)
    {
      r--;
    }

    if (l >= r) break;
    
    swap(*r, *l);    
  }
  
  swap(*p, *r);
  return r;
}

/* *
* n^2 worst (not shuffled), n log n best/avg
*
* partion the array into two halves
* quick sort each half recursively
* */
template <class iter>
void quick_sort(iter &begin, iter &end)
{
  if (begin == end) return;
  
  auto p = partition(begin, end);  
  
  quick_sort(begin, p);  
  quick_sort(p + 1, end);
}


