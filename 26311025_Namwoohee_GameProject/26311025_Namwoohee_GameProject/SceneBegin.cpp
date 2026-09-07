#include "SceneBegin.h"
#include "CApplication.h"
#include "glc2d.h"
#include <Windows.h>

extern CApplication g_App;

int SceneBegin::Init()
{
	m_texStart = g2_TextureLoad("Texture/gameStart.jpg");
	m_prevSpace = false;

	return 0;
}

int SceneBegin::Update()
{
	bool space = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

	// 키를 "누르는 순간"에만 반응 (edge trigger)
	if (space && !m_prevSpace)
	{
		g_App.ResetScore();
		g_App.SetLives(3);
		g_App.ChangeScene(SceneID::Play);
		return 0; // 씬이 교체되었으므로 즉시 리턴
	}

	m_prevSpace = space;
	return 0;
}

int SceneBegin::Render()
{
	VEC2 pos = { 0, 0 };
	g2_Draw2D(m_texStart, nullptr, &pos);

	return 0;
}

int SceneBegin::Destroy()
{
	g2_TextureRelease(m_texStart);
	return 0;
}
