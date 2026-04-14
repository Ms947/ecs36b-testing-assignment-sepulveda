#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[13] = {4, 2, 6, 8, 63, 2, 6, 2, 52, 1, 23, 423, -23};
    int* copied_array = copy_array(arr, 13);

    for (int i = 0; i < 13; i++)
    {
        EXPECT_EQ(copied_array[i], arr[i]);
    }
    free(copied_array);

}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int original_uncalled[13] = {4, 2, 6, 8, 63, 2, 6, 2, 52, 1, 23, 423, -23};
    int arr[13] = {4, 2, 6, 8, 63, 2, 6, 2, 52, 1, 23, 423, -23};
    int* copied_array = copy_array(arr, 13);

    for (int i = 0; i < 13; i++)
    {
        EXPECT_EQ(original_uncalled[i], arr[i]);
    }
    free(copied_array);

}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[13] = {4, 2, 6, 8, 63, 2, 6, 2, 52, 1, 23, 423, -23};
    int* copied_array = copy_array(arr, 13);

    for (int i = 0; i < 13; i++)
    {
        EXPECT_NE(&copied_array[i], &arr[i]);
    }
    free(copied_array);

}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    //int* array_values = malloc(values.size() * sizeof(int));

    int* array_values = new int[values.size()];
    copy_vector_to_array(values, array_values);

    int* copied_array = copy_array(array_values, values.size());
    for (int i = 0; i < (int)values.size(); i++)
    {
        RC_ASSERT(copied_array[i] == values.at(i));
    }
    free(copied_array);
    delete[] array_values;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    //int* array_values = malloc(values.size() * sizeof(int));

    int* array_values = new int[values.size()];
    copy_vector_to_array(values, array_values);
    //int array[values.size()];
    //for (int i = 0; i < values.size(); i++)
    //{
    //    array[i] = values[i];
    //}
    int* copied_array = copy_array(array_values, values.size());

    for (int i = 0; i < values.size(); i++)
    {
        RC_ASSERT(array_values[i] == values.at(i));
    }
    free(copied_array);
    delete[] array_values;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
    //int* array_values = malloc(values.size() * sizeof(int));

    int* array_values = new int[values.size()];
    copy_vector_to_array(values, array_values);

    int* copied_array = copy_array(array_values, values.size());

    for (int i = 0; i < values.size(); i++)
    {
        RC_ASSERT(&copied_array[i] != &array_values[i]);
    }
    free(copied_array);
    delete[] array_values;
}



