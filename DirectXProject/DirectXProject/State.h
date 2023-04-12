#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP


#include "../../Common/d3dApp.h"

#include <memory>

class StateStack;
class Player;
class Game;

namespace States
{
	enum ID
	{
		None,
		Title,
		Menu,
		Game,
		Loading,
		Pause
	};
}
//This class is the base class for creating states
class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Player& player, Game* game);

		Player* player;
		Game* mGame;
	};

public:
	State(StateStack& stack, Context context);
	virtual	~State();
	virtual void draw() = 0;
	virtual bool update(const GameTimer& gt) = 0;
	virtual bool handleEvent() = 0;
	virtual void BuildScene() = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

	StateStack* mStack;
	Game* mGame;
private:

	Context mContext;
};

#endif // BOOK_STATE_HPP