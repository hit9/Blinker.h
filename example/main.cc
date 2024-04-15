#include <any>
#include <iostream>

#include "blinker.h"

int main(void) {
  blinker::Board board;

  auto taskStarted = board.NewSignal("task.started");
  auto taskEnded = board.NewSignal("task.ended");
  auto actionStarted = board.NewSignal("action.started");

  auto connection = board.Connect("task.*");

  auto callback = [&](const blinker::SignalId id, std::any data) {
    if (id == taskStarted->Id())
      std::cout << "signal taskStarted:";
    else if (id == taskEnded->Id())
      std::cout << "signal taskEnded:";
    else if (id == actionStarted->Id())
      std::cout << "signal actionStarted-:";
    std::cout << std::any_cast<int>(data) << std::endl;
  };

  for (int i = 0; i < 10; i++) {
    taskStarted->Emit(i);
    taskEnded->Emit(i);
    actionStarted->Emit(i);
    connection->Poll(callback);
    board.Flip();
  }

  return 0;
}
