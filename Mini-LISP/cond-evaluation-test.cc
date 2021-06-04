/*
 * cond evaluation: normal evaluation + lazy evaluation
 * (default in Lisp: eager evaluation, which can be prevented by quote ')
 *
 * Example of test case:
 *
 * a-list before:
 * --------------
 * our a-list:  t -> nil
 *              |     |
 *              t     nil
 *
 * Evaluate cond:
 * --------------
 * (cond
 *     ((null (set 'a 'x))  'a)
 *     ((atom (set 'b 'y))  'b)
 *     ((null (set 'c 'z))  'c)
 * )
 *
 *
 * a-list After: (expected)
 * -------------
 * our a-list:  b -> a -> t -> nil
 *              |    |    |     |
 *              y    x    t    nil
 *
 * (without "c")
 *
 */

#include <string.h>
#include <gtest/gtest.h>
#include "test.h"

void getUniqueNames(std::string *unique_names, int size) {
    for (int i=0; i < size; i++) {
        unique_names[i] = "v_" + std::to_string(i);
    }
}

// ----------------------------
// Test:
TEST(CondEvaluationOrder, CondEvaluationOrder) {
    // unique variables names:
    int total_variables = 6;
    std::string unique_names[total_variables];
    getUniqueNames(unique_names, total_variables);

    // Test:
    int var_idx = 0;
    int total_defined = 3; // should evaluate the first 3
    eval(parse("(cond "
                 "((null (set '" + unique_names[var_idx++] + " 'x))  'x)  " // v_0 in a_list
                 "((null (set '" + unique_names[var_idx++] + " 'x))  'x)  " // v_1 in a_list
                 "((atom (set '" + unique_names[var_idx++] + " 'x))  'x)  " // v_2 in a_list
                 "((null (set '" + unique_names[var_idx++] + " 'x))  'x)  " // v_3 NOT in a_list
                 "((atom (set '" + unique_names[var_idx++] + " 'x))  'x)  " // v_4 NOT in a_list
                 "((null (set '" + unique_names[var_idx++] + " 'x))  'x)  " // v_5 NOT in a_list
                 ")"));
    for (int i=0; i < total_defined; i++) {
        EXPECT_EQ(eval(S(unique_names[i].c_str())), S("NIL"));
    }
    for (int i=total_defined; i < total_variables; i++) {
        ASSERT_NE(eval(S(unique_names[i].c_str())), S("NIL"));
    }
}

