#include "algo/search.h"

// O(N) linear search
int *linear_search(const int *begin, const int *end, int target) {
  while (begin < end) {
    if (*begin == target)
      return (int *)begin;
    begin++;
  }

  return NULL;
}

// O(log N) binary search on sorted ranges
int *binary_search(const int *begin, const int *end, int target, int (*compare)(int, int)) {
  while (begin < end) {
    const int *mid = begin + ((end - begin) >> 1);

    const int cmp = compare(target, *mid);

    if (cmp < 0)
      end = mid;
    else if (cmp > 0)
      begin = mid + 1;
    else
      return (int *)mid;
  }

  return NULL;
}
