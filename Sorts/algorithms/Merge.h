#pragma once
#include "stdafx.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstddef>

using std::vector;
using std::distance;
using std::copy;

/* *
* n log(n) worst/average/best
* dive array into two halves
* recursively sort each half
* merge two halves
* */
template <class iter>
void merge_sort(iter &begin, iter &end)
{
  using val_type = std::iterator_traits<iter>::value_type;

  size_t dis = distance(begin, end);

  if (dis <= 1) return;

  size_t mid = dis / 2;

  merge_sort(begin, begin + mid);
  merge_sort(begin + mid, end);

  // can optimize by allocating once at the top of recursion
  // and passing down iterators to the appropriate section
  vector<val_type> aux(dis);

  iter i = begin;
  iter j = begin + mid;

  for (iter k = aux.begin(); k < aux.end(); k++)
  {
    if (j >= end)
    {
      copy(i, i + 1, k);
      i++;
    }
    else if (i >= (begin + mid))
    {
      copy(j, j + 1, k);
      j++;
    }
    else if (*i < *j)
    {
      copy(i, i + 1, k);
      i++;
    }
    else
    {
      copy(j, j + 1, k);
      j++;
    }
  }

  auto aux_begin = aux.begin();
  auto aux_end = aux.end();

  copy(aux_begin, aux_end, begin);
}