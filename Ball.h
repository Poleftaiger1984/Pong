#pragma once
#include "raylib.h"

class Paddle;

class Ball {

public:
	Ball(int BallPosX, int BallPosY, int BallHeight, int BallWidth);
		
	
	inline int GetBallPositionX() const { return m_BallX; }
	inline int GetBallPositionY() const { return m_BallY; }
	inline int GetBallHeight() const { return m_BallHeight; }
	inline int GetBallWidth() const { return m_BallWidth; }

	void BallMovement();
	void BallReset(int BallPosX, int BallPosY);
	void BallRender(Ball& myBall);
	bool CollisionChecker(Paddle& myPlayer);
	void CollisionMovement(Paddle& myPlayer);
	void WallCollisionChecker(int MaxHeight, const Sound& SoundToPlay);
	void Serve(bool IsPlayer1Serving);

private:
	int m_BallHeight{ 0 };
	int m_BallWidth{ 0 };
	int m_BallX{ 0 };
	int m_BallY{ 0 };
	int m_BallDX{ 0 };
	int m_BallDY{ 0 };
};