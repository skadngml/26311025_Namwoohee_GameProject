#pragma once
#include <Windows.h>
#include <string>
#include "CScene.h"

// 씬을 식별하기 위한 열거형.
// SceneBegin -> ScenePlay -> SceneResult -> (다시 SceneBegin) 순으로 순환
enum class SceneID
{
	Begin,
	Play,
	Result
};

class CApplication
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

	// 씬 전환. 기존 씬은 Destroy 후 해제하고 새 씬을 Init 한다.
	void ChangeScene(SceneID id);

	// 게임 진행 상태 (여러 씬에서 공유해야 하는 값들)
	int GetScore() const { return m_score; }
	void AddScore(int value) { m_score += value; }
	void ResetScore() { m_score = 0; }

	int GetLives() const { return m_lives; }
	void SetLives(int lives) { m_lives = lives; }
	void LoseLife() { m_lives--; }

protected:
	CScene* m_pScene = nullptr;

	// window
	POINT m_winPos{ 100, 100 };
	SIZE  m_winSize{ 1024, 768 };
	std::string m_winName = "Sky Defender - 26311025 Namwoohee";

	int m_score = 0;
	int m_lives = 3;
};
