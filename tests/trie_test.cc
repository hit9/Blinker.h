
#include <catch2/catch_test_macros.hpp>

#include "blinker.h"

TEST_CASE("trie/1", "[trie test]") {
  blinker::SignalTrie<1024> trie;
  trie.Put("ab.cd.ef", 1);
  trie.Put("ab.cd.kk", 2);
  trie.Put("ab.xy.zz", 3);
  trie.Put("tt.xx", 4);
  trie.Put("ab.cd", 5);

  auto m1 = trie.Match("ab.cd.ef");
  REQUIRE(m1.count() == 1);
  REQUIRE(m1[1]);

  auto m2 = trie.Match("ab.cd.kk");
  REQUIRE(m2.count() == 1);
  REQUIRE(m2[2]);

  auto m3 = trie.Match("ab.xy.zz");
  REQUIRE(m3.count() == 1);
  REQUIRE(m3[3]);

  auto m4 = trie.Match("ab.not.found");
  REQUIRE(m4.count() == 0);

  auto m5 = trie.Match("ab.*");
  REQUIRE(m5.count() == 4);
  REQUIRE(m5[1]);
  REQUIRE(m5[2]);
  REQUIRE(m5[3]);
  REQUIRE(m5[5]);

  auto m6 = trie.Match("*");
  REQUIRE(m6.count() == 5);
  REQUIRE(m6[1]);
  REQUIRE(m6[2]);
  REQUIRE(m6[3]);
  REQUIRE(m6[4]);
  REQUIRE(m6[5]);

  auto m7 = trie.Match("ab.cd.*");
  REQUIRE(m7.count() == 2);
  REQUIRE(m7[1]);
  REQUIRE(m7[2]);

  auto m8 = trie.Match("tt.xx.");
  REQUIRE(m8.count() == 0);

  auto m9 = trie.Match("tt.xx.*");
  REQUIRE(m9.count() == 0);

  auto m10 = trie.Match("ab.cd");
  REQUIRE(m10.count() == 1);
  REQUIRE(m10[5]);
}
