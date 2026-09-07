#pragma once
#include "Common.h"

// 플레이어가 조종하는 우주선
// - 좌/우 방향키로 이동
// - 스페이스바로 총알 발사 (발사 자체는 ScenePlay에서 처리하고,
//   Player는 위치/이동 속도/애니메이션 등 자기 자신의 상태만 관리)
class Player
{
public:
	void Init(int textureId);
	void Update();
	void Render();

	AABB GetBounds() const;

	float GetX() const { return m_x; }
	float GetY() const { return m_y; }

private:
	int m_textureId = -1;
	float m_x = SCREEN_WIDTH / 2.0f - 32.0f;
	float m_y = SCREEN_HEIGHT - 100.0f;
	float m_speed = 6.0f;     // 초당 이동량이 아니라 프레임당 이동량 (간단화)
	float m_width = 64.0f;
	float m_height = 64.0f;
};
