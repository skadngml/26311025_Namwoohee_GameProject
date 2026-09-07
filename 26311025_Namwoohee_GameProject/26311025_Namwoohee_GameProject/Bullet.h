#pragma once
#include "Common.h"

// 플레이어가 발사하는 총알. 위로 일정 속도로 이동하다가
// 화면 밖으로 나가거나 적과 충돌하면 비활성화(m_active = false) 됨.
class Bullet
{
public:
	void Init(int textureId, float x, float y);
	void Update();
	void Render();

	bool IsActive() const { return m_active; }
	void Deactivate() { m_active = false; }
	AABB GetBounds() const;

private:
	int m_textureId = -1;
	float m_x = 0, m_y = 0;
	float m_width = 8.0f, m_height = 20.0f;
	float m_speed = 12.0f;
	bool m_active = true;
};
