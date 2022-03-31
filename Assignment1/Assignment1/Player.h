#pragma once
#include "Command.h"
#include "Common/d3dApp.h"

class CommandQueue;

class Player
{
public:
	Player();
	void					handleEvent(CommandQueue& commands);
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
	void					assignKey(Action action, int key);
	int						getAssignedKey(Action action) const;


private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);
	void					ResetKeyChecks();


private:
	//int a = GetAsyncKeyState((int)VK_LEFT);
	std::map<int, Action>					mKeyBinding;
	std::map<Action, Command>				mActionBinding;
	std::map<int, bool>						mKeyChecks;
#pragma endregion


};
