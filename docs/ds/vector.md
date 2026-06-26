## Design Decisions

### Capacity Shrinkage: Performance vs Theoretical Space Complexity

In academic textbooks (such as CLRS), dynamic tables are often designed to automatically shrink by half when they fall to 1/4 capacity to guarantee strict $\Theta(\text{size})$ space complexity.

In this repository, **I chose to follow the industry-standard behavior of `std::vector` (C++) and `std::vec` (Rust)**:

- The vector **never** automatically shrinks during `pop_back()`, `erase()`, or `resize()`
- This avoids expensive, unpredictable $O(N)$ system reallocation calls during standard deletion operations
- Memory reclamation is left as an explicit, conscious developer choice via `shrink_to_fit()`
