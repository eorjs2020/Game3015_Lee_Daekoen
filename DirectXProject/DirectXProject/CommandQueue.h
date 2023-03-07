#pragma once

#include "Command.h"
#include "queue"
/// This class is use to hold all the commands 
class CommandQueue
{
public:
	void						push(const Command& command);
	Command						pop();
	bool						isEmpty() const;

private:
	std::queue<Command>			mQueue;
};
