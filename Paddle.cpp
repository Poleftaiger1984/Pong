#include "Paddle.h"
#include "raylib.h"

Paddle::Paddle(int PaddleHeight, int PaddleWidth, int PlayerY, int PlayerX)
	: m_PaddleHeight(PaddleHeight), m_PaddleWidth(PaddleWidth), m_PaddleY(PlayerY), m_PaddleX(PlayerX)
{

}

void Paddle::Player1Movement(float DeltaTime, Paddle& myPlayer, int UpperLimit, int LowerLimit)
{
	if (IsKeyDown(KEY_W) && myPlayer.m_PaddleY > UpperLimit)
	{
		myPlayer.m_PaddleY += -PADDLE_SPEED * DeltaTime;
	}

	if (IsKeyDown(KEY_S) && myPlayer.m_PaddleY < LowerLimit)
	{
		myPlayer.m_PaddleY += PADDLE_SPEED * DeltaTime;
	}
}

void Paddle::Player2Movement(float DeltaTime, Paddle& myPlayer, int UpperLimit, int LowerLimit)
{
	if (IsKeyDown(KEY_UP) && myPlayer.m_PaddleY > UpperLimit)
	{
		myPlayer.m_PaddleY += -PADDLE_SPEED * DeltaTime;
	}

	if (IsKeyDown(KEY_DOWN) && myPlayer.m_PaddleY < LowerLimit)
	{
		myPlayer.m_PaddleY += PADDLE_SPEED * DeltaTime;
	}
}

void Paddle::PaddleRender(Paddle& myPlayer)
{
	DrawRectangle(myPlayer.GetPaddleX(), myPlayer.GetPaddleY(), myPlayer.GetPaddleWidth(), myPlayer.GetPaddleHeight(), RAYWHITE);
}

void Paddle::ResetPaddle(int PaddleY)
{
	m_PaddleY = PaddleY;
}

