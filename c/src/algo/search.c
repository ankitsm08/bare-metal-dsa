#include "algo/search.h"
#include "utils/compare.h"

// O(N) linear search
int *linear_search(const int *begin, const int *end, int target) {
  while (begin < end) {
    if (*begin == target)
      return (int *)begin;
    begin++;
  }

  return NULL;
}

// middle element getter helper
inline const int *get_mid(const int *begin, const int *end) { return begin + ((end - begin) >> 1); }

// O(log N) binary search on sorted ranges
int *binary_search(const int *begin, const int *end, int target, compare_fn compare) {
  while (begin < end) {
    const int *mid = get_mid(begin, end);

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

int *lower_bound(const int *begin, const int *end, int target, compare_fn compare) {
  while (begin < end) {
    const int *mid = get_mid(begin, end);

    if (compare(target, *mid) <= 0)
      end = mid;
    else
      begin = mid + 1;
  }

  return (int *)begin;
}

int *upper_bound(const int *begin, const int *end, int target, compare_fn compare) {
  while (begin < end) {
    const int *mid = get_mid(begin, end);
    if (compare(target, *mid) < 0)
      end = mid;
    else
      begin = mid + 1;
  }

  return (int *)begin;
}
