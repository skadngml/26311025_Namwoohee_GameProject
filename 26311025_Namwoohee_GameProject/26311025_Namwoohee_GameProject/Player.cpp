#include "Player.h"
#include "glc2d.h"
#include <Windows.h>

void Player::Init(int textureId)
{
	m_textureId = textureId;
	m_x = SCREEN_WIDTH / 2.0f - m_width / 2.0f;
	m_y = SCREEN_HEIGHT - 100.0f;
}

void Player::Update()
{
	// 참고: glc2d.h 에 별도의 입력 함수가 없을 수 있어
	// 여기서는 표준 Win32 API인 GetAsyncKeyState를 사용했습니다.
	// 만약 glc2d가 자체 입력 함수(g2_ 접두사)를 제공한다면 그걸로 교체하는 게 더 좋습니다.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_x -= m_speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_x += m_speed;
	}

	// 화면 밖으로 나가지 않도록 제한
	if (m_x < 0) m_x = 0;
	if (m_x > SCREEN_WIDTH - m_width) m_x = SCREEN_WIDTH - m_width;
}

void Player::Render()
{
	VEC2 pos = { m_x, m_y };
	g2_Draw2D(m_textureId, nullptr, &pos);
}

AABB Player::GetBounds() const
{
	// 판정을 살짝 작게 잡아 체감 난이도를 낮춤 (그래픽 크기보다 살짝 작은 판정)
	return AABB{ m_x + 8, m_y + 8, m_width - 16, m_height - 16 };
}
