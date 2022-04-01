#pragma region step 2
#include "Player.h"
#include "CommandQueue.h"
#include "Aircraft.h"


#include <map>
#include <string>
#include <algorithm>
#include <iostream>


struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz)
		: velocity(vx, vy, vz)
	{
	}

	void operator() (Aircraft& aircraft,const GameTimer&) const
	{
		aircraft.accelerate(velocity);
	}

	XMFLOAT3 velocity;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[VK_LEFT] = MoveLeft;
	mKeyBinding[VK_RIGHT] = MoveRight;
	mKeyBinding[VK_UP] = MoveUp;
	mKeyBinding[VK_DOWN] = MoveDown;

	// Set initial action bindings
	initializeActions();

	ResetKeyChecks();

	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::ResetKeyChecks()
{
	mKeyChecks.clear();
	for (auto pair : mKeyBinding)
	{
		mKeyChecks[pair.first] = false;
	}
}

void Player::handleEvent(CommandQueue& commands)
{
	//if (event.type == sf::Event::KeyPressed)
	//{
	//	// Check if pressed key appears in key binding, trigger command if so
	//	auto found = mKeyBinding.find(event.key.code);
	//	if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
	//		commands.push(mActionBinding[found->second]);
	//}


	for (auto pair : mKeyBinding)
	{
		if (!isRealtimeAction(pair.second))
		{
			if (mKeyChecks[pair.first])
			{
				if (!GetAsyncKeyState(pair.first))
				{
					mKeyChecks[pair.first] = false;
				}
			}
			else
			{
				if (GetAsyncKeyState(pair.first) & 0x8000)
				{
					mKeyChecks[pair.first] = true;
					commands.push(mActionBinding[pair.second]);
				}
			}
		}
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (auto pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (GetAsyncKeyState(pair.first) & 0x8000 && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, char key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

char Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return 0x00;
}

void Player::initializeActions()
{
	const float playerSpeed = 200.f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, 0.f, -playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, 0.f, +playerSpeed));
	/*
	mActionBinding[GetPosition].action = [](SceneNode& s, GameTimer) {
		std::cout << s.getWorldPosition().x << "," << s.getWorldPosition().y << "\n";
	};
	*/
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}

#pragma endregion