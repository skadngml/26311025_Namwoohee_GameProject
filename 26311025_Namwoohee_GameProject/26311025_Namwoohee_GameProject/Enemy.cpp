#include "Enemy.h"
#include "glc2d.h"

void Enemy::Init(int textureId, float x, float y, float speed)
{
	m_textureId = textureId;
	m_x = x;
	m_y = y;
	m_speed = speed;
	m_active = true;
}

void Enemy::Update()
{
	if (!m_active) return;

	m_y += m_speed;
}

void Enemy::Render()
{
	if (!m_active) return;

	VEC2 pos = { m_x, m_y };
	g2_Draw2D(m_textureId, nullptr, &pos);
}

AABB Enemy::GetBounds() const
{
	return AABB{ m_x + 4, m_y + 4, m_width - 8, m_height - 8 };
}
