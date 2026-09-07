#include "SceneResult.h"
#include "CApplication.h"
#include "glc2d.h"
#include <Windows.h>
#include <iostream>

extern CApplication g_App;

int SceneResult::Init()
{
	m_texResult = g2_TextureLoad("Texture/gameResult.jpg");
	m_prevSpace = false;

	std::cout << "[SceneResult] Final score: " << g_App.GetScore() << "\n";

	return 0;
}

int SceneResult::Update()
{
	bool space = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

	if (space && !m_prevSpace)
	{
		g_App.ChangeScene(SceneID::Begin);
		return 0;
	}

	m_prevSpace = space;
	return 0;
}

int SceneResult::Render()
{
	VEC2 pos = { 0, 0 };
	g2_Draw2D(m_texResult, nullptr, &pos);

	return 0;
}

int SceneResult::Destroy()
{
	g2_TextureRelease(m_texResult);
	return 0;
}
