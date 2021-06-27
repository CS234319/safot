extern Knob pop();
TEST(pop, 1) { 
  heapify();
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(heap.handle(),1);
  auto s1 = pop().handle();
  EXPECT_EQ(heap.handle(),2);
  EXPECT_EQ(s1,1);
  EXPECT_FF(corrupted.asymmetric());
  EXPECT_EQ(length(), $P_n$-1);
  EXPECT_EQ(length(), accounting.unused);
}

TEST(Crude, almostExhausted) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().handle();
  EXPECT_FF(heap.x());
  EXPECT_EQ(accounting.unused, 1);
}

TEST(Crude, exhausted) { 
  heapify();
  EXPECT_EQ(accounting.unused, $P_n$); 
  for (auto i = 1; i <= $P_n$; ++i) {
    auto const s = crude().handle();
    EXPECT_EQ(i, s);
    EXPECT_EQ(accounting.unused, $P_n$ - i); 
    EXPECT_ZZ(accounting.items); // This black box test corrupts the heap,
  }
  EXPECT_TT(heap.x());
  EXPECT_ZZ(accounting.unused);
}

TEST(Crude, last) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().handle();
  crude();
}

TEST(Crude, lastCorrect) { 
  heapify();
  for (auto i = 1; i < $P_n$; ++i)
    crude().handle();
  crude();
  EXPECT_TT(heap.x());
  EXPECT_ZZ(accounting.unused);
}
