#include <string.h>
#include <gtest/gtest.h>
#include "test.h"
/**
 *  Test global and local a-list
 */


static S x("x");
static S y("y");
extern S evaluate_cond(S s);
extern S lookup(S id);
extern S alist();
extern S defun(S name, S parameters, S body);


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
     * Thus, all the lookup MUST throw UNDEFINED error for all the
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
                    list(NULL, list(SET, b_1.q(), x.q())),
                    x.q()
            ),
            list(
                    list(NULL, list(ERROR, b_2.q(), b_2)),
                    x.q()
            )
    );

    // Evaluate cond on the list:
    EXPECT_EXCEPTION(s.eval(), list(S("ERROR"), b_2.q(), b_2), b_2);

    // Check if b0, b1, b2 are defined:
    EXPECT_EXCEPTION(lookup(b_0), b_0, UNDEFINED);
    EXPECT_EXCEPTION(lookup(b_1), b_1, UNDEFINED);
}

TEST(AlistGlobalLocal, SetArgumentsBeforeFunction) {
    /*
     * Check if set is properly done before calling a function
     */
    // Define variables:
    S f("F"), a("A"), b("B"), p("P"), v("V");

    // Define simple function:
    defun(f, list(x, y), a);

    // Define s-expression that will set a and b during the evaluation:
    S s = list(f,
               list(SET, a.q(), p.q()),
               list(SET, b.q(), v.q())
    );
    EXPECT_EQ(s.eval(), p);

    // Check if a and b still defined:
    s = list(f, a, b);
    EXPECT_EQ(s.eval(), p);
}
