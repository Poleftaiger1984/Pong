#pragma once
#define PADDLE_SPEED 600

class Paddle {

public:
	Paddle(int PaddleHeight, int PaddleWidth, int PlayerY, int PlayerX);

	inline int GetPlayerScore() const { return m_PlayerScore; }
	inline int GetPaddleHeight() const { return m_PaddleHeight; }
	inline int GetPaddleWidth() const { return m_PaddleWidth; }
	inline int GetPaddleY() const { return m_PaddleY; }
	inline int GetPaddleX() const { return m_PaddleX; }
	inline void SetPlayerScore(int NewScore) { m_PlayerScore += NewScore; }

	void Player1Movement(float DeltaTime, Paddle& myPlayer, int UpperLimit, int LowerLimit);
	void Player2Movement(float DeltaTime, Paddle& myPlayer, int UpperLimit, int LowerLimit);
	void PaddleRender(Paddle& myPlayer);
	void ResetPaddle(int PaddleY);

private:
	int m_PaddleHeight{ 0 }; 
	int m_PaddleWidth{ 0 };
	int m_PaddleY{ 0 };
	int m_PaddleX{ 0 };
	int m_PlayerScore{ 0 };
};
