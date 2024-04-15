#include <any>
#include <iostream>

#include "blinker.h"

int main(void) {
  blinker::Board board;

  auto taskStarted = board.NewSignal("task.started");
  auto taskEnded = board.NewSignal("taskEnded");

  auto connection = board.Connect("task.*");

  auto callback = [=](const blinker::SignalId id, std::any data) {
    std::cout << "signal " << id << " => ";
    std::cout << std::any_cast<int>(data) << std::endl;
  };

  for (int i = 0; i < 10; i++) {
    taskStarted->Emit(i);
    taskEnded->Emit(i);
    connection->Poll(callback);
    board.Flip();
  }

  return 0;
}
