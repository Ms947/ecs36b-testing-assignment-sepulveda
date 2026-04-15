#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    auto letter_generator = rc::gen::inRange<char>('a', 'z' + 1);
    return rc::gen::container<std::string>(letter_generator);

}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    //auto vector_of_strings = rc::gen::container<std::vector>(word_generator());
    // How do I make vector numbers into a vector of letters
    // First we know we can assign each number a letter
    // but how do we copy a vector to another vector?
    //auto vector_of_strings = //??
    std::vector<std::string> vector_of_strings;

    for (int i = 0; i < (int)numbers.size(); i++)
    {
        vector_of_strings[i] = numbers[i]; //but somehow make that index be turned into a string
        // alternatively, use pushback.
    }


}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    //parse_args()
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
}
