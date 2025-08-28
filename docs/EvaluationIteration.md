
The interface between the evaluation engine and the outside world is a stack
of iterators. While the interface to these iterators is consistent, there 
are many kinds of iterators that serve different purposes.

The outside world/execution environment knows how to:
- Execute the (possibly blocking) behavior of a leaf action
- Start threads to execute behavior on branches of a parallel block

Often, several transformations are required to move from the 
user-level description of an activity to the execution-level view that
the execution environment can make use of. 

- Sequence: Holds a set of activity statements
- Repeat: Tracks execution of a repeat statement
  - Each iteration pushes the body of the repeat as an indepedent sequence

# Nested Iterators
Some iterators have a dual personality. For example, the parallel iterator. 
The first item returned by the iterator is the iterator itself. At this 
point, ownership of the iterator is relinquished by the container and 
passed to the caller. Subsequent items will be the branches of the parallel.