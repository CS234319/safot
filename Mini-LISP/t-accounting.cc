#include "accounting.h"

#include "Test.h"

TEST(accounting, init) {
 accounting.init(17); 
 EXPECT_ZZ(accounting.requested);
 EXPECT_ZZ(accounting.provided);
 EXPECT_ZZ(accounting.used);
 EXPECT_EQ(accounting.unused,17);
}
