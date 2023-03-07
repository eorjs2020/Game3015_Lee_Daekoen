#include "CommandQueue.h"
#include "SceneNode.hpp"
/// To push command into queue
/// 
/// @param: const Command&
void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}
/// To remove first command from the queue
Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}
/// To check is the queue empty
bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
