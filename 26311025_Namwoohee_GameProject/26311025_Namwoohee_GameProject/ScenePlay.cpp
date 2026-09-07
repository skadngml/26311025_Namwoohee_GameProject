#include "ScenePlay.h"
#include "CApplication.h"
#include "Common.h"
#include "glc2d.h"
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>

extern CApplication g_App;

int ScenePlay::Init()
{
	m_texBackground = g2_TextureLoad("Texture/background.jpg");
	m_texPlayer = g2_TextureLoad("Texture/player.png");
	m_texBullet = g2_TextureLoad("Texture/bullet.png");
	m_texEnemy = g2_TextureLoad("Texture/enemy.png");

	m_player.Init(m_texPlayer);
	m_bullets.clear();
	m_enemies.clear();

	m_prevSpace = false;
	m_shootCooldown = 0;
	m_spawnTimer = 0;
	m_spawnInterval = 60;
	m_frameCount = 0;

	std::cout << "[ScenePlay] Game start!\n";

	return 0;
}

int ScenePlay::Update()
{
	m_frameCount++;

	m_player.Update();
	HandleShooting();
	SpawnEnemyIfNeeded();
	UpdateBullets();
	UpdateEnemies();
	CheckCollisions();
	CleanupInactive();

	// 시간이 지날수록 스폰 간격을 조금씩 줄여서 난이도 상승 (최소 20프레임)
	if (m_frameCount % 300 == 0 && m_spawnInterval > 20)
	{
		m_spawnInterval -= 5;
	}

	if (g_App.GetLives() <= 0)
	{
		std::cout << "[ScenePlay] Game over. Score = " << g_App.GetScore() << "\n";
		g_App.ChangeScene(SceneID::Result);
	}

	return 0;
}

int ScenePlay::Render()
{
	VEC2 bgPos = { 0, 0 };
	g2_Draw2D(m_texBackground, nullptr, &bgPos);

	m_player.Render();

	for (auto& b : m_bullets) b.Render();
	for (auto& e : m_enemies) e.Render();

	// 참고: glc2d에 텍스트 출력 함수가 있다면(g2_DrawText 등) 여기서
	// 점수/생명을 화면에 그리는 게 좋습니다. 헤더가 없어 정확한 함수명을
	// 확인하지 못해, 우선 콘솔(stdout)로 점수 변화를 출력하도록 했습니다.

	return 0;
}

int ScenePlay::Destroy()
{
	g2_TextureRelease(m_texBackground);
	g2_TextureRelease(m_texPlayer);
	g2_TextureRelease(m_texBullet);
	g2_TextureRelease(m_texEnemy);

	return 0;
}

void ScenePlay::HandleShooting()
{
	if (m_shootCooldown > 0)
	{
		m_shootCooldown--;
	}

	bool space = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

	if (space && m_shootCooldown == 0)
	{
		Bullet b;
		float bx = m_player.GetX() + 28.0f; // 플레이어 중앙에서 발사
		float by = m_player.GetY() - 10.0f;
		b.Init(m_texBullet, bx, by);
		m_bullets.push_back(b);

		m_shootCooldown = m_shootCooldownMax;
	}

	m_prevSpace = space;
}

void ScenePlay::SpawnEnemyIfNeeded()
{
	m_spawnTimer--;
	if (m_spawnTimer > 0) return;

	m_spawnTimer = m_spawnInterval;

	float x = static_cast<float>(rand() % (SCREEN_WIDTH - 48));
	float speed = 2.0f + static_cast<float>(rand() % 3); // 2~4 사이 속도

	Enemy e;
	e.Init(m_texEnemy, x, -48.0f, speed);
	m_enemies.push_back(e);
}

void ScenePlay::UpdateBullets()
{
	for (auto& b : m_bullets) b.Update();
}

void ScenePlay::UpdateEnemies()
{
	for (auto& e : m_enemies) e.Update();
}

void ScenePlay::CheckCollisions()
{
	// 총알 vs 적
	for (auto& b : m_bullets)
	{
		if (!b.IsActive()) continue;

		for (auto& e : m_enemies)
		{
			if (!e.IsActive()) continue;

			if (IsOverlap(b.GetBounds(), e.GetBounds()))
			{
				b.Deactivate();
				e.Deactivate();
				g_App.AddScore(100);
				std::cout << "[ScenePlay] Enemy destroyed! Score = " << g_App.GetScore() << "\n";
				break;
			}
		}
	}

	// 적 vs 플레이어 / 적이 바닥에 도달
	AABB playerBounds = m_player.GetBounds();
	for (auto& e : m_enemies)
	{
		if (!e.IsActive()) continue;

		if (IsOverlap(e.GetBounds(), playerBounds))
		{
			e.Deactivate();
			g_App.LoseLife();
			std::cout << "[ScenePlay] Hit! Lives = " << g_App.GetLives() << "\n";
		}
		else if (e.ReachedBottom())
		{
			e.Deactivate();
			g_App.LoseLife();
			std::cout << "[ScenePlay] Enemy passed! Lives = " << g_App.GetLives() << "\n";
		}
	}
}

void ScenePlay::CleanupInactive()
{
	m_bullets.erase(
		std::remove_if(m_bullets.begin(), m_bullets.end(),
			[](const Bullet& b) { return !b.IsActive(); }),
		m_bullets.end());

	m_enemies.erase(
		std::remove_if(m_enemies.begin(), m_enemies.end(),
			[](const Enemy& e) { return !e.IsActive(); }),
		m_enemies.end());
}
