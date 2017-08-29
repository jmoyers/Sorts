#pragma once
#include "stdafx.h"
#include <utility>

using std::swap;

/* *
* n^2 worst/average, n best (already in order)
* for each i, store j = i, increment j, find any smaller, swap left until sorted
* */
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
