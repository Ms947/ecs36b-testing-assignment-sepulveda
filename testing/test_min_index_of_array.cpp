#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int arr[6] = {-345, 3, 29, -23, 13, 567};

    int min = min_index_of_array(arr, 6);
    EXPECT_EQ(min, 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int arr[6] = {85, 2, 91, 8, 39, -567};

    int min = min_index_of_array(arr, 6);
    EXPECT_EQ(min, 5);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int arr[6] = {22, 3, 29, 1, 77, 567};

    int min = min_index_of_array(arr, 6);
    EXPECT_EQ(min, 3);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int arr[10] = {22, -45, 67, 81, -23, -45, 2, 13, 0, 567};

    int min = min_index_of_array(arr, 10);
    EXPECT_EQ(min, 1);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int arr[6] = {-345, 3, 29, -23, 13, 567};
    int arr_stable[6] = {-345, 3, 29, -23, 13, 567};

    int min = min_index_of_array(arr, 6);
    for (int i = 0; i < 6; i++)
    {
        EXPECT_EQ(arr_stable[i], arr[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              ()) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    // Produce random array
    //int array[] =
    for (int i = 0; i < array.size(); i++)
    {
        RC_ASSERT(min_index <= array[i]);
    }
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              ()) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    // Produce random array
    // Create copy of array
    for (int i = 0; i < array.size(); i++)
    {
        RC_ASSERT(array[i] == array_stable[i]);
    }
}
