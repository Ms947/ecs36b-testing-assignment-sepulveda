# Google Test And Debugging Writeup

## Things I Thought To Test
1. For function "swap", test:
   1. Two numbers that are the same value.
   2. One negative and one positive number.
   3. Two negative numbers.
   4. Two positive numbers.
2. For function "copy_array", test:
   1. Inputting an array and length which is smaller than the array length.
   2. Inputting an array and length with is larger than the array length.
   3. Inputting an array with its length.
3. For function "min_index_of_array", test:
   1. An array with all the same numbers.
   2. An array with repeating numbers, mixed with different numbers
   3. An array with all negative numbers.
   4. An array with all kinds of number, positive and negative, no repeating numbers.
   5. An array with all positive numbers.
4. For function "make_sorted", test:
   1. An already sorted array.
   2. An oppositely sorted array (largest to smallest).
   3. A random array.
   4. The same inputs from the "min_index_of_array" tests.
5. For "get_sorted", test:
   1. All the same tests of "make_sorted".
6. For "parse_args", test:
   1. No arguments.
   2. One argument.
   3. A large set of arguments, 100 for example.

## Bugs

### Bug 1

### Location

Lines 66 - 68

```c++
 int* temp = a;
  a = b;
  b = temp;
```

### How the bug was located

I found the bug when I was writing the test_swap.cpp tests.

### Description

This code attempts to swap a and b. It creates a pointer
temp that points to a. a then points to b, and b points to temp.

### Fix

To fix the bug, I made temp into a normal integer whose
value was a (dereferenced a when initializing temp). 
I also dereferenced a and b when assigning their new values.

```c++
  int temp = *a;
  *a = *b;
  *b = temp;
```

### Bug 2

### Location

lines 36 and 37

```c++
  int* copy = ar;
  return copy;
```

### How the bug was located

I found the bug because the code wouldn't build, and the
builder showed me specifically that this function (copy_array) was
causing an error.

### Description

It is trying to make a copy of ar, but does it incorrectly
so it doesn't work. It tries to make a pointer called copy
that points to ar.

### Fix 

I completely rewrote the function so that memory was
allocated to the copy, and then assigned each index of
copy to be a copy of the indeces of ar.

```c++
  int* copy = (int*)malloc(sizeof(int) * len);
  for (int i = 0; i < len; i++)
  {
    copy[i] = ar[i];
  }

  return copy;
```

### Bug 3

### Location

Lines 51 - 56 in sorting.cpp

```c++
for (int i = 1; i < len; ++i) {
    if (ar[i] > ar[min_index]) {
      min_index = i;
    }
  }
  return ar[min_index];
```

### How the bug was located

I found this bug while writing the test_min_index_of_array.cpp
tests. I was looking through the min_index_of_array() function 
to make sure I was writing the tests correctly.

### Description

The if statement uses the wrong comparison sign
and the function returns the element at the minimum index,
when it should return the minimum index number.

### Fix

I made the greater than sign in the if statement into a less than sign,
then I made the function return min_index.

```c++
  for (int i = 1; i < len; ++i) {
    if (ar[i] < ar[min_index]) {
      min_index = i;
    }
  }
  return min_index;
```
