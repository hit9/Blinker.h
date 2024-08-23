#include "blinker.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("blinker/1", "[blinker test - simple]") {
  struct Data {
    int value = 1;
    Data(int value) : value(value) {}
  };

  blinker::Board board;

  auto signal1 = board.NewSignal("ab.cd");
  auto signal2 = board.NewSignal("ab.ef");
  auto signal3 = board.NewSignal("xy.zk");

  auto conn1 = board.Connect("ab.*");
  auto conn2 = board.Connect("ab.cd");
  auto conn3 = board.Connect("ab.ef");
  auto conn4 = board.Connect("xy.zk");
  auto conn5 = board.Connect("*");

  bool conn1CallbackCalled = false;
  bool conn2CallbackCalled = false;
  bool conn3CallbackCalled = false;
  bool conn4CallbackCalled = false;
  bool conn5CallbackCalled = false;

  auto tick = [&]() {
    signal1->Emit(std::make_shared<Data>(1));
    signal2->Emit(std::make_shared<Data>(2));
    signal3->Emit(std::make_shared<Data>(3));

    // signal1 and signal2
    conn1->Poll([&](const blinker::SignalId id, std::any data) {
      conn1CallbackCalled = true;
      auto p = std::any_cast<std::shared_ptr<Data>>(data);
      if (id == signal1->Id())
        REQUIRE(p->value == 1);
      else if (id == signal2->Id())
        REQUIRE(p->value == 2);
      else
        REQUIRE(false);
    });

    // signal1
    conn2->Poll([&](const blinker::SignalId id, std::any data) {
      conn2CallbackCalled = true;
      auto p = std::any_cast<std::shared_ptr<Data>>(data);
      if (id == signal1->Id())
        REQUIRE(p->value == 1);
      else
        REQUIRE(false);
    });

    // signal2
    conn3->Poll([&](const blinker::SignalId id, std::any data) {
      conn3CallbackCalled = true;
      auto p = std::any_cast<std::shared_ptr<Data>>(data);
      if (id == signal2->Id())
        REQUIRE(p->value == 2);
      else
        REQUIRE(false);
    });

    // signal3
    conn4->Poll([&](const blinker::SignalId id, std::any data) {
      conn4CallbackCalled = true;
      auto p = std::any_cast<std::shared_ptr<Data>>(data);
      if (id == signal3->Id())
        REQUIRE(p->value == 3);
      else
        REQUIRE(false);
    });

    // all signals
    conn5->Poll([&](const blinker::SignalId id, std::any data) {
      conn5CallbackCalled = true;
      auto p = std::any_cast<std::shared_ptr<Data>>(data);
      if (id == signal1->Id())
        REQUIRE(p->value == 1);
      else if (id == signal2->Id())
        REQUIRE(p->value == 2);
      else if (id == signal3->Id())
        REQUIRE(p->value == 3);
      else
        REQUIRE(false);
    });

    board.Flip();
  };

  tick();

  // still not called.
  REQUIRE(!conn1CallbackCalled);
  REQUIRE(!conn2CallbackCalled);
  REQUIRE(!conn3CallbackCalled);
  REQUIRE(!conn4CallbackCalled);
  REQUIRE(!conn5CallbackCalled);

  // called after flip
  tick();

  REQUIRE(conn1CallbackCalled);
  REQUIRE(conn2CallbackCalled);
  REQUIRE(conn3CallbackCalled);
  REQUIRE(conn4CallbackCalled);
  REQUIRE(conn5CallbackCalled);
}

TEST_CASE("multiple emits") {
  blinker::Board board;
  auto signal1 = board.NewSignal("a.b.c");
  auto signal2 = board.NewSignal("a.b.d");
  auto signal3 = board.NewSignal("a.c");

  auto conn1 = board.Connect("a.*");
  auto conn2 = board.Connect("a.b.*");
  auto conn3 = board.Connect("a.c");

  int conn1CalledTimes = 0, conn2CalledTimes = 0, conn3CalledTimes = 0;

  struct Data {
    int value;
    Data(int v) : value(v) {}
  };

  auto tick = [&]() {
    signal1->Emit(std::make_shared<Data>(1));
    signal2->Emit(std::make_shared<Data>(2));
    signal2->Emit(std::make_shared<Data>(2));
    signal3->Emit(std::make_shared<Data>(3));

    conn1->Poll([&](const blinker::SignalId id, std::any data) { ++conn1CalledTimes; });
    conn2->Poll([&](const blinker::SignalId id, std::any data) { ++conn2CalledTimes; });
    conn3->Poll([&](const blinker::SignalId id, std::any data) { ++conn3CalledTimes; });

    board.Flip();
  };

  tick();
  tick();

  REQUIRE(conn1CalledTimes == 1 + 2 + 1);
  REQUIRE(conn2CalledTimes == 1 + 2);
  REQUIRE(conn3CalledTimes == 1);
}
