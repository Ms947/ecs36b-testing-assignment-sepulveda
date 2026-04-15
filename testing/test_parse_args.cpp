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
    auto string_generator =  rc::gen::container<std::string>(letter_generator);
    return string_generator;
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */

    std::vector<std::string> vector_of_strings;

    for (int i = 0; i < (int)numbers.size(); i++)
    {
        vector_of_strings.push_back(std::to_string(numbers[i]));
    }

    return vector_of_strings;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    int argc = 5;
    const char* argv[5] = {"hello", "90", "36", "22", "8"};
    int* ar_out = NULL;
    int len_out = 1;

    parse_args(argc, argv, ar_out, &len_out);

    ASSERT_NE(ar_out, nullptr);
    ASSERT_EQ(len_out, 4);

    EXPECT_EQ(ar_out[1], 90);
    EXPECT_EQ(ar_out[2], 36);
    EXPECT_EQ(ar_out[3], 22);
    EXPECT_EQ(ar_out[4], 8);

    free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */

    int argc = 1;
    const char* argv[1] = {"name_of_prog"};
    int* ar_out = NULL;
    int len_out = 10;

    parse_args(argc, argv, ar_out, &len_out);

    ASSERT_EQ(ar_out, nullptr);
    ASSERT_EQ(len_out, 0);

    free(ar_out);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */

    // Setting up vector of inputs.
    std::vector<std::string> argv_vector;
    std::vector<std::string> argv_generated_numbers;

    std::string argv1 = *word_generator().as("argv1");
    argv_vector.push_back(argv1);
    for (int i = 0; i < (int)argv_generated_numbers.size(); i++)
    {
        argv_vector.push_back(argv_generated_numbers.at(i));
    }

    // making the vector into an array
    const char** argv = new const char*[argv_vector.size()];
    for (int i = 0; i < (int)argv_vector.size(); i++)
    {
        argv[i] = argv_vector.at(i).c_str();
    }

    // defining the rest of the variables
    int argc = argv_generated_numbers.size() + 1;
    int* ar_out = NULL;
    int len_out = argc + 25;

    // Test starts here
    parse_args(argc, argv, ar_out, &len_out);

    RC_ASSERT(ar_out != nullptr);
    RC_ASSERT(len_out == (int)argv_generated_numbers.size());

    for (int i = 0; i < (int)argv_generated_numbers.size(); i++)
    {
        RC_ASSERT(ar_out[i] == std::stoi(argv_generated_numbers.at(i)));
    }

    delete[] argv;
    free(ar_out);
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    std::vector<std::string> argv_vector;
    std::string argv1 = *word_generator().as("argv1");
    argv_vector.push_back(argv1);

    const char** argv = new const char*[argv_vector.size()];
    argv[0] = argv_vector.at(0).c_str();

    int argc = 1;
    int* ar_out = NULL;
    int len_out = 20;

    parse_args(argc, argv, ar_out, &len_out);

    RC_ASSERT(ar_out == nullptr);
    RC_ASSERT(len_out == 0);

    delete[] argv;
    free(ar_out);
}
