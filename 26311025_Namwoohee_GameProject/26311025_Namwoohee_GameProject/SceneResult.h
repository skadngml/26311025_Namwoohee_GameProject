#pragma once
#include "CScene.h"

// 결과 화면: 게임 오버 이미지를 보여주고, 스페이스바를 누르면 시작 화면으로 복귀.
class SceneResult : public CScene
{
public:
	int Init() override;
	int Update() override;
	int Render() override;
	int Destroy() override;

protected:
	int m_texResult = -1;
	bool m_prevSpace = false;
};
