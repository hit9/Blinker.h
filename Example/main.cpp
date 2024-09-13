#include <any>
#include <iostream>

#include "Blinker.h"

int main(void)
{
	// Creates a board.
	Blinker::Board board;

	// Creates signals.
	auto taskStarted = board.NewSignal("task.started");
	auto taskEnded = board.NewSignal("task.ended");
	auto actionStarted = board.NewSignal("action.started");

	// Creates connection to match some signals.
	auto connection = board.Connect("task.*");

	// Callback to be called on signal fire.
	auto callback = [&](const Blinker::SignalId id, std::any data) {
		if (id == taskStarted->Id())
			std::cout << "signal taskStarted:";
		else if (id == taskEnded->Id())
			std::cout << "signal taskEnded:";
		else if (id == actionStarted->Id())
			std::cout << "signal actionStarted-:";
		std::cout << std::any_cast<int>(data) << std::endl;
	};

	// Assuming your main tick function here.
	for (int i = 0; i < 3; i++)
	{
		// Emit some signals (to backend).
		taskStarted->Emit(i);
		taskEnded->Emit(i);
		actionStarted->Emit(i);

		// Poll from frontend.
		connection->Poll(callback);

		// Flip double buffers.
		board.Flip();
	}

	return 0;
}
