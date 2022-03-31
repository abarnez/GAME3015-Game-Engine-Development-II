#pragma once
#include "Command.h"
#include "Common/d3dApp.h"

class CommandQueue;

class Player
{
public:
	Player();
	void					handleEvent(const sf::Event& event, CommandQueue& commands);
	void					handleRealtimeInput(CommandQueue& commands);
#pragma region step 1
	//static const float		PlayerSpeed;
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		GetPosition,
		ActionCount
	};
	void					assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key		getAssignedKey(Action action) const;


private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);


private:
	//int a = GetAsyncKeyState((int)VK_LEFT);
	std::map<int, Action>		mKeyBinding;
	std::map<Action, Command>				mActionBinding;
#pragma endregion


};
