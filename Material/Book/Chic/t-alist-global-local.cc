#import  <string.h>
#import  <gtest/gtest.h>
#import  "test.h"
/**
 *  Test global and local a-list
 */


static S x("x"); 
namespace Engine { namespace Inner {
  extern S evaluate_cond(S s);
}}
using Engine::lookup;


TEST(AlistGlobalLocal, SetWithNoError) {
    /*
     * Set 3 variables inside cond, locally,
     * and after the function return, all of them should
     * be in the a-list.
     */
    // unique variables names:
    int total_variables = 3;
    std::string unique_names[total_variables];
    for (int i=0; i < total_variables; i++) {
        unique_names[i] = "v_" + std::to_string(i);
    }

    // Test:
    int var_idx = 0;

    // Define S names:
    S v_0(unique_names[var_idx++].c_str());
    S v_1(unique_names[var_idx++].c_str());
    S v_2(unique_names[var_idx++].c_str());

    // Define cond:
    S s = list(COND,
        list(
                list(NULL, list(SET, v_0.q(), x.q())),
                x.q()
        ),
        list(
                list(NULL, list(SET, v_1.q(), x.q())),
                x.q()
        ),
        list(
                list(NULL, list(SET, v_2.q(), x.q())),
                x.q()
        )
    );

    // Evaluate cond on the list:
    s.eval();

    // Check if v0, v1, v2 are defined:
    EXPECT_EQ(lookup(v_0), x);
    EXPECT_EQ(lookup(v_1), x);
    EXPECT_EQ(lookup(v_2), x);
}


TEST(AlistGlobalLocal, SetWithError) {
    /*
     * Same as before, but we call error in the third condition.
     * Thus, all the lookup MUST throw UNDEFINED_ATOM error for all the
     * variables defined by set in the cond function.
     *
     */
    // unique variables names:
    int total_variables = 3;
    std::string unique_names[total_variables];
    for (int i=0; i < total_variables; i++) {
        unique_names[i] = "b_" + std::to_string(i);
    }

    // Test:
    int var_idx = 0;

    // Define S names:
    S b_0(unique_names[var_idx++].c_str());
    S b_1(unique_names[var_idx++].c_str());
    S b_2(unique_names[var_idx++].c_str());

    // Define cond:
    S s = list(COND,
            list(
                    list(NULL, list(SET, b_0.q(), x.q())),
                    x.q()
            ),
            list(
                    list(NULL, list(ERROR, b_2.q(), b_2.q())),
                    x.q()
            ),
            list(
                    list(NULL, list(SET, b_1.q(), x.q())),
                    x.q()
            )
    );

    // Evaluate cond on the list:
    EXPECT_EXCEPTION(s.eval(), list(b_2), b_2);

    // Check if b0, b1, b2 are defined:
    EXPECT_EQ(lookup(b_0), x);
    EXPECT_EXCEPTION(lookup(b_1), b_1, UNDEFINED_ATOM);
}
