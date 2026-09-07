#pragma once
#include <vector>
#include "CScene.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

// 실제 게임 플레이가 이루어지는 씬.
// - 플레이어 이동/발사
// - 적 스폰 및 이동
// - 총알-적, 적-플레이어 충돌 처리
// - 생명이 0이 되면 SceneResult 로 전환
class ScenePlay : public CScene
{
public:
	int Init() override;
	int Update() override;
	int Render() override;
	int Destroy() override;

private:
	void HandleShooting();
	void SpawnEnemyIfNeeded();
	void UpdateBullets();
	void UpdateEnemies();
	void CheckCollisions();
	void CleanupInactive();

private:
	int m_texBackground = -1;
	int m_texPlayer = -1;
	int m_texBullet = -1;
	int m_texEnemy = -1;

	Player m_player;
	std::vector<Bullet> m_bullets;
	std::vector<Enemy> m_enemies;

	bool m_prevSpace = false;
	int m_shootCooldown = 0;      // 남은 발사 쿨다운 (프레임 단위)
	const int m_shootCooldownMax = 12;

	int m_spawnTimer = 0;         // 다음 적 스폰까지 남은 프레임
	int m_spawnInterval = 60;     // 대략 1초에 한 마리 (60fps 가정)
	int m_frameCount = 0;         // 시간이 지날수록 난이도를 올리기 위한 카운터
};
