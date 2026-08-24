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
static inline const int *get_mid(const int *begin, const int *end) {
  return begin + ((end - begin) >> 1);
}

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

static inline const int *clamp(const int *pos, const int *low, const int *high) {
  if (pos < low)
    return low;
  if (pos >= high)
    return high - 1;
  return pos;
}

static inline const int *interpolate(const int *low, const int *high, int target) {
  const long long range = 0LL + *(high - 1) - *low;
  if (range == 0)
    return NULL;

  const long long dist = 0LL + target - *low;
  const long long span = high - low;
  return clamp(low + (dist * span) / range, low, high);
}

// O(log N) average on uniform distribution
// O(N) worst case
int *interpolation_search(const int *begin, const int *end, int target, compare_fn compare) {
  while (begin < end) {
    if (compare(target, *begin) < 0 || compare(target, *(end - 1)) > 0)
      break;

    const int *pos = interpolate(begin, end, target);
    if (!pos) {
      if (*begin == target)
        return (int *)begin;
      return NULL;
    }

    const int cmp = compare(target, *pos);

    if (cmp < 0)
      end = pos;
    else if (cmp > 0)
      begin = pos + 1;
    else
      return (int *)pos;
  }

  return begin == end || *begin != target ? NULL : (int *)begin;
}
