#include <stdio.h>

#include "CApplication.h"
#include "glc2d.h"
#include "SceneBegin.h"
#include "ScenePlay.h"
#include "SceneResult.h"

extern CApplication g_App;

int RenderApp()
{
	g_App.Render();
	return 0;
}

int UpdateApp()
{
	g_App.Update();
	return 0;
}

int CApplication::Init()
{
	g2_InitSdk();

	g2_SetFrameMove(UpdateApp);
	g2_SetRender(RenderApp);

	g2_CreateWin(m_winPos.x, m_winPos.y, m_winSize.cx, m_winSize.cy, m_winName.c_str());

	m_pScene = new SceneBegin();
	m_pScene->Init();

	return 0;
}

int CApplication::Update()
{
	if (m_pScene)
	{
		m_pScene->Update();
	}

	return 0;
}

int CApplication::Render()
{
	if (m_pScene)
	{
		m_pScene->Render();
	}

	return 0;
}

int CApplication::Destroy()
{
	if (m_pScene)
	{
		m_pScene->Destroy();
		delete m_pScene;
		m_pScene = nullptr;
	}

	g2_DestroyWin();

	return 0;
}

void CApplication::ChangeScene(SceneID id)
{
	if (m_pScene)
	{
		m_pScene->Destroy();
		delete m_pScene;
		m_pScene = nullptr;
	}

	switch (id)
	{
	case SceneID::Begin:
		m_pScene = new SceneBegin();
		break;
	case SceneID::Play:
		m_pScene = new ScenePlay();
		break;
	case SceneID::Result:
		m_pScene = new SceneResult();
		break;
	}

	if (m_pScene)
	{
		m_pScene->Init();
	}
}
