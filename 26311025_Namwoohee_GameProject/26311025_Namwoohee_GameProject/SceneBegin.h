#pragma once
#include "CScene.h"

// 시작 화면: 타이틀 이미지를 보여주고 스페이스바 입력을 기다린다.
class SceneBegin : public CScene
{
public:
	int Init() override;
	int Update() override;
	int Render() override;
	int Destroy() override;

protected:
	int m_texStart = -1;
	bool m_prevSpace = false; // 키를 누르고 있는 동안 여러 번 전환되지 않도록 edge 검사용
};
