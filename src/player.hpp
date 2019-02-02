#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <queue>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include "global.hpp"
#include "menu.hpp"
#include "particle.hpp"

class Player
{
	private:
		// Player dimensions
		static const int PLAYER_WIDTH = 30;
		static const int PLAYER_HEIGHT = 40;
		const float FOLLOW_DISTANCE = 28.0f;		// Follow distanse
		const float COLLISION_DISTANCE = 20.0f;		// The distance at which a collision occurs
		const float ANALOG_DEADZONE = 0.2f;			// Analog stick deadzone

		//float xPos, yPos;	// Player coordinates
		//float rotation;		// Player rotation angle in radians ( 0 is up )
		
		float PLAYER_SET_SPEED;				// The speed set by the difficulty
		float PLAYER_SET_ROTATION_SPEED;	// The rotation set by the difficulty
		float speed;						// Player current speed

		std::vector <vec3> snakeParts;

		// Controls
		SceCtrlData pad;

	public:
		Player();

		bool isClose;		// Is snake close to the collectable

		void setDifficulty();

		void handleInput();

		void follow();

		void move();

		bool checkCollision();		// Tail collision

		bool wallDeath();			// Die from touching a wall

		void render();

		void resetPos();

		vec3 get_pos();

		void addParts( int i );
		void setSize( int i );
};


#endif // PLAYER_HPP