#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
    //int x = 9;
    //int y = 3;
    int a = 9;
    int b = 3;
    swap(&a, &b);

    EXPECT_EQ(b, 9);
    EXPECT_EQ(a, 3);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int x[3] = {5, 2, 7};

    //int* a = &x;
    //swap(*(a + 1), *(a + 2));
    swap(&x[1], &x[2]);
    int swapped_x[3] = {5, 7, 2};

    int new_length = sizeof(x) / sizeof(x[0]);
    EXPECT_EQ(3, new_length);
    for (int i = 0; i < 3; i++)
    {
        EXPECT_EQ(x[i], swapped_x[i]) << "x:" << x[i] << "and expected:" << swapped_x[i] << "differ at index" << i;
    }

}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a_final = b_start;
    int b_final = a_start;
    swap(&a_start, &b_start);
    RC_ASSERT(a_start == a_final); // << a_start << "is not correct, it should be" << a_final;
    RC_ASSERT(b_start == b_final); // << b_start << "is not correct, it should be" << b_final;
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */

    int length = values.size();
    int* array = new int[length];
    copy_vector_to_array(values, array);
    /*
    *int array_copy[length];
    *for (int i = 0; i < length; i++)
    *{
    *    array_copy[i] = values[i];
    *}
    */
    //RC_ASSERT(length >= 2);
    int swapped1 = rand() % length;
    int swapped2 = rand() % length;
    swap(&array[swapped1], &array[swapped2]);

    int array_length = sizeof(*array) / sizeof(array[0]);
    RC_ASSERT(array_length == (int)values.size());
    for (int i = 0; i < length; i++)
    {
        if (i == swapped1 || i == swapped2) continue;
        RC_ASSERT(values[i] == values.at(i));
    }

    RC_ASSERT(array[swapped1] == values.at(swapped2));
    RC_ASSERT(array[swapped2] == values.at(swapped1));

    delete[] array;
}
