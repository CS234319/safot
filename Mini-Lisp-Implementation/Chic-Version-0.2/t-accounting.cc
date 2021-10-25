#import "accounting.cc"
#import "Testee.h"

TEST(accounting, init) {
 accounting.init(17); 
 EXPECT_ZZ(accounting.request);
 EXPECT_ZZ(accounting.provide);
 EXPECT_ZZ(accounting.used);
 EXPECT_EQ(accounting.unused,17);
}
