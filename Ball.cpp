#include "Ball.h"
#include <ctime>
#include <algorithm>
#include "raylib.h"
#include "Paddle.h"

Ball::Ball(int BallPosX, int BallPosY, int BallHeight, int BallWidth)
	: m_BallX(BallPosX), m_BallY(BallPosY), m_BallHeight(BallHeight), m_BallWidth(BallWidth)
{
	SetRandomSeed(std::time(nullptr));
}

void Ball::BallMovement()
{
	float DT = GetFrameTime();

	m_BallX += m_BallDX * DT;
	m_BallY += m_BallDY * DT;
}

void Ball::BallReset(int BallPosX, int BallPosY)
{
	m_BallX = BallPosX;
	m_BallY = BallPosY;
}

void Ball::BallRender(Ball& myBall)
{
	DrawRectangle(myBall.GetBallPositionX(), myBall.GetBallPositionY(), myBall.GetBallWidth(), myBall.GetBallHeight(), RAYWHITE);
}

bool Ball::CollisionChecker(Paddle& myPlayer)
{
	int PlayerY = myPlayer.GetPaddleY();
	int PlayerX = myPlayer.GetPaddleX();
	int PlayerHeight = myPlayer.GetPaddleHeight();
	int PlayerWidth = myPlayer.GetPaddleWidth();

	if (m_BallX > PlayerX + PlayerWidth || m_BallX + m_BallWidth < PlayerX) return false;
		
	if (m_BallY > PlayerY + PlayerHeight || m_BallY + m_BallHeight < PlayerY) return false;

	else return true;
}

void Ball::CollisionMovement(Paddle& myPlayer)
{
	m_BallDX = std::min(-m_BallDX * 1.04, 900.2); 

	if (m_BallX > myPlayer.GetPaddleX())
	{
		m_BallX = myPlayer.GetPaddleX() + myPlayer.GetPaddleWidth();
		m_BallDY = GetRandomValue(-300, 300);
	}
	else if (m_BallX < myPlayer.GetPaddleX())
	{
		m_BallX = myPlayer.GetPaddleX() - m_BallWidth;
		m_BallDY = GetRandomValue(-300, 300);
	}
}

void Ball::WallCollisionChecker(int MaxHeight, const Sound& SoundToPlay)
{
	if (m_BallY <= 0)
	{
		PlaySound(SoundToPlay);
		m_BallY = 0;
		m_BallDY = -m_BallDY;
	}

	if (m_BallY + m_BallWidth >= MaxHeight)
	{
		PlaySound(SoundToPlay);
		m_BallY = MaxHeight - m_BallWidth;
		m_BallDY = -m_BallDY;
	}

}

void Ball::Serve(bool IsPlayer1Serving)
{
	if (IsPlayer1Serving == true)
	{
		m_BallDX = 400;
		m_BallDY = GetRandomValue(-50, 50) * 3;
	}
	else if (IsPlayer1Serving == false)
	{
		m_BallDX = -400;
		m_BallDY = GetRandomValue(-50, 50) * 3;
	}
}
