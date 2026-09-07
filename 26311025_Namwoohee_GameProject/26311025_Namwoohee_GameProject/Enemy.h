#pragma once
#include "Common.h"

// 위에서 아래로 내려오는 적.
// 총알에 맞으면 격추(점수 획득), 화면 아래까지 도달하면 플레이어 생명 감소.
class Enemy
{
public:
	void Init(int textureId, float x, float y, float speed);
	void Update();
	void Render();

	bool IsActive() const { return m_active; }
	void Deactivate() { m_active = false; }
	bool ReachedBottom() const { return m_y > SCREEN_HEIGHT; }
	AABB GetBounds() const;

private:
	int m_textureId = -1;
	float m_x = 0, m_y = 0;
	float m_width = 48.0f, m_height = 48.0f;
	float m_speed = 3.0f;
	bool m_active = true;
};
