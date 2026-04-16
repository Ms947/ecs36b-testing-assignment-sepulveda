#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[9] = {-23, -3, 2, 9, 34, 55, 56, 60, 68};
    //int arr_untouched[9] = {-23, -3, 2, 9, 34, 55, 56, 60, 68};
    int* sorted_array = get_sorted(arr, 9);

    for (int i = 0; i < 9; i++)
    {
        EXPECT_EQ(sorted_array[i], arr[i]);
    }

    free(sorted_array);
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[12] = {650, 280, 200, 85, 67, 40, 15, 2, -1, -5, -12, -13};
    int* sorted_array = get_sorted(arr, 12);

    int answer_arr[12] = {-13, -12, -5, -1, 2, 15, 40, 67, 85, 200, 280, 650};

    for (int i = 0; i < 12; i++)
    {
        EXPECT_EQ(sorted_array[i], answer_arr[i]);
    }
    free(sorted_array);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[9] = {65, 2, 3, -9, -23, 122, -32, 8, 62};
    int* sorted_array = get_sorted(arr, 9);

    int answer_arr[9] = {-32, -23, -9, 2, 3, 8, 62, 65, 122};

    for ( int i = 0; i < 9; i++)
    {
        EXPECT_EQ(sorted_array[i], answer_arr[i]);
    }
    free(sorted_array);
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[5] = {3, 92, 0, 3, 0};
    int* sorted_array = get_sorted(arr, 5);

    int answer_arr[5] = {0, 0, 3, 3, 92};

    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(sorted_array[i], answer_arr[i]);
    }
    free(sorted_array);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[16] = {18, 7, 65, 59, 22, 84, -5, 0, -81, 22, 8, 1, 12, 101, -51, -4};
    int* sorted_array = get_sorted(arr, 16);

    int copy_original[16] = {18, 7, 65, 59, 22, 84, -5, 0, -81, 22, 8, 1, 12, 101, -51, -4};

    for (int i = 0; i < 16; i++)
    {
        EXPECT_EQ(arr[i], copy_original[i]);
    }
    free(sorted_array);
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[6] = {3, 2, -9, 50, 19, 21};
    int* sorted_array = get_sorted(arr, 6);

    for (int i = 0; i < 6; i++)
    {
        EXPECT_NE(&arr[i], &sorted_array[i]);
    }
    free(sorted_array);
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int* arr = new int[values.size()];
    copy_vector_to_array(values, arr);
    int* sorted_array = get_sorted(arr, values.size());

    for (int i = 1; i < (int)values.size(); i++)
    {
        RC_ASSERT(sorted_array[i] >= sorted_array[i - 1]);
    }

    free(sorted_array);
    delete[] arr;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int* arr = new int[values.size()];
    copy_vector_to_array(values, arr);
    int* sorted_array = get_sorted(arr, values.size());

    for (int i = 1; i < (int)values.size(); i++)
    {
        RC_ASSERT(arr[i] == values.at(i));
    }

    free(sorted_array);
    delete[] arr;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int* arr = new int[values.size()];
    copy_vector_to_array(values, arr);
    int* sorted_array = get_sorted(arr, values.size());

    for (int i = 1; i < (int)values.size(); i++)
    {
        RC_ASSERT(&arr[i - 1] != &sorted_array[i - 1]);
        RC_ASSERT(sorted_array[i] >= sorted_array[i - 1]);
    }

    free(sorted_array);
    delete[] arr;
}











