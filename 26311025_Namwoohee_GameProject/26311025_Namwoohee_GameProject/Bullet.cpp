#include "Bullet.h"
#include "glc2d.h"

void Bullet::Init(int textureId, float x, float y)
{
	m_textureId = textureId;
	m_x = x;
	m_y = y;
	m_active = true;
}

void Bullet::Update()
{
	if (!m_active) return;

	m_y -= m_speed;

	if (m_y + m_height < 0)
	{
		m_active = false;
	}
}

void Bullet::Render()
{
	if (!m_active) return;

	VEC2 pos = { m_x, m_y };
	g2_Draw2D(m_textureId, nullptr, &pos);
}

AABB Bullet::GetBounds() const
{
	return AABB{ m_x, m_y, m_width, m_height };
}
