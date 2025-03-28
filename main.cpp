#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"

#define WINDOWHEIGHT 720
#define WINDOWWIDTH 1280
#define SCREEN_PADDING 2

enum GameState : int
{
	Start,
	Serving,
	Play,
	Victory
};
GameState State = GameState::Start;

//Paddles
Paddle Player1((WINDOWHEIGHT / 6), (WINDOWWIDTH / 40), 50, 30);
Paddle Player2((WINDOWHEIGHT / 6), (WINDOWWIDTH / 40), (WINDOWHEIGHT - (50 + (WINDOWHEIGHT / 6))), WINDOWWIDTH - 60);
bool IsPlayer1Serving = true;

//Ball
Ball myBall((WINDOWWIDTH / 2), (WINDOWHEIGHT / 2), 15, 15);

void UpdateDrawFrame(const Font& customFont, const Sound(&mySounds)[3]);
void DisplayFPS();

int main()
{
	InitWindow(WINDOWWIDTH, WINDOWHEIGHT, "Pong");
	InitAudioDevice();
	SetTargetFPS(60);
	Font myFont = LoadFontEx("PressStart2P-vaV7.ttf", 8, nullptr, 0);	
	Sound sounds[3];
	sounds[0] = LoadSound("sounds/Paddle_Hit.wav");
	sounds[1] = LoadSound("sounds/Score.wav");
	sounds[2] = LoadSound("sounds/Wall_Hit.wav");


	while (!WindowShouldClose())
	{
		UpdateDrawFrame(myFont, sounds);
	}

	CloseAudioDevice();
	CloseWindow();
	
	return 0;
}

void UpdateDrawFrame(const Font& customFont, const Sound (&mySounds)[3])
{
	if (IsKeyPressed(KEY_ESCAPE)) CloseWindow();
	if (IsKeyPressed(KEY_ENTER))
	{
		if(State == GameState::Start)
			State = GameState::Serving;

		else if (State == GameState::Serving)
		{
			myBall.Serve(IsPlayer1Serving);
			State = GameState::Play;
		}

		else if (State == GameState::Victory)
		{
			State = GameState::Start;
			myBall.BallReset(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);
			Player1.SetPlayerScore(-Player1.GetPlayerScore());
			Player2.SetPlayerScore(-Player2.GetPlayerScore());
			Player1.ResetPaddle(50);
			Player2.ResetPaddle((WINDOWHEIGHT - (50 + (WINDOWHEIGHT / 6))));

		}
	}
	DisplayFPS();

	float DT = GetFrameTime();

	BeginDrawing();

	ClearBackground(Color{ 40, 45, 52, 255 });

	DrawTextEx(customFont, TextFormat("%d", Player1.GetPlayerScore()), Vector2{ WINDOWWIDTH / 2 - 100, WINDOWHEIGHT / 3 }, 64, 2, RAYWHITE);
	DrawTextEx(customFont, TextFormat("%d", Player2.GetPlayerScore()), Vector2{ WINDOWWIDTH / 2 + 60, WINDOWHEIGHT / 3 }, 64, 2, RAYWHITE);

	//Left paddle
	Player1.PaddleRender(Player1);

	//Right paddle
	Player2.PaddleRender(Player2);

	//Ball
	myBall.BallRender(myBall);

	if (State == GameState::Start)
	{
		DrawTextEx(customFont, "Hello Pong!", Vector2{ WINDOWWIDTH / 2 - 90, 20 }, 16, 2, RAYWHITE);
		DrawTextEx(customFont, "Press Enter to Start", Vector2{ WINDOWWIDTH / 2 - 160, 40 }, 16, 2, RAYWHITE);
	}

	if (State == GameState::Serving)
	{
		if (IsPlayer1Serving)
		{
			DrawTextEx(customFont, "Player1 Serves!", Vector2{ WINDOWWIDTH / 2 - 110, 20 }, 16, 2, RAYWHITE);
			DrawTextEx(customFont, "Press Enter to Serve", Vector2{ WINDOWWIDTH / 2 - 160, 40 }, 16, 2, RAYWHITE);
		}

		if (!IsPlayer1Serving)
		{
			DrawTextEx(customFont, "Player2 Serves!", Vector2{ WINDOWWIDTH / 2 - 110, 20 }, 16, 2, RAYWHITE);
			DrawTextEx(customFont, "Press Enter to Serve", Vector2{ WINDOWWIDTH / 2 - 160, 40 }, 16, 2, RAYWHITE);
		}
		
	}

	if (State == GameState::Play)
	{
		Player1.Player1Movement(DT, Player1, SCREEN_PADDING, WINDOWHEIGHT - Player1.GetPaddleHeight() - SCREEN_PADDING);
		Player2.Player2Movement(DT, Player2, SCREEN_PADDING, WINDOWHEIGHT - Player2.GetPaddleHeight() - SCREEN_PADDING);
		myBall.BallMovement();
		myBall.WallCollisionChecker(WINDOWHEIGHT, mySounds[2]);

		if (myBall.CollisionChecker(Player1))
		{
			PlaySound(mySounds[0]);
			myBall.CollisionMovement(Player1);
		}
		if (myBall.CollisionChecker(Player2))
		{
			PlaySound(mySounds[0]);
			myBall.CollisionMovement(Player2);
		}

		if (myBall.GetBallPositionX() < 0 + myBall.GetBallWidth())
		{
			PlaySound(mySounds[1]);
			Player2.SetPlayerScore(1);
			myBall.BallReset(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);
			IsPlayer1Serving = true;
			State = GameState::Serving;
		}
		if (myBall.GetBallPositionX() > WINDOWWIDTH)
		{
			PlaySound(mySounds[1]);
			Player1.SetPlayerScore(1);
			myBall.BallReset(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);
			IsPlayer1Serving = false;
			State = GameState::Serving;
		}

		if (Player1.GetPlayerScore() == 10 || Player2.GetPlayerScore() == 10)
		{
			State = GameState::Victory;
		}
	}

	if (State == GameState::Victory)
	{
		if (Player1.GetPlayerScore() == 10)
		{
			DrawTextEx(customFont, "Player1 Wins!", Vector2{ WINDOWWIDTH / 2 - 110, 20 }, 20, 2, RAYWHITE);
			DrawTextEx(customFont, "Press Enter to Reset", Vector2{ WINDOWWIDTH / 2 - 160, 50 }, 16, 2, RAYWHITE);
			IsPlayer1Serving = false;
		}

		if (Player2.GetPlayerScore() == 10)
		{
			DrawTextEx(customFont, "Player2 Wins!", Vector2{ WINDOWWIDTH / 2 - 110, 20 }, 20, 2, RAYWHITE);
			DrawTextEx(customFont, "Press Enter to Reset", Vector2{ WINDOWWIDTH / 2 - 160, 50 }, 16, 2, RAYWHITE);
			IsPlayer1Serving = true;
		}
	}

	EndDrawing();
}

void DisplayFPS()
{
	DrawText(TextFormat("%d", GetFPS()), 10, 10, 4, RAYWHITE);
}