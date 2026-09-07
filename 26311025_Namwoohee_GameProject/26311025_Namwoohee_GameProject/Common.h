#pragma once

// 충돌 판정을 위한 간단한 축 정렬 사각형(AABB)
struct AABB
{
	float x = 0, y = 0;      // 좌상단 좌표
	float w = 0, h = 0;      // 가로/세로 크기
};

// 두 사각형이 겹치는지 검사 (총알-적, 플레이어-적 충돌에 사용)
inline bool IsOverlap(const AABB& a, const AABB& b)
{
	return (a.x < b.x + b.w) &&
	       (a.x + a.w > b.x) &&
	       (a.y < b.y + b.h) &&
	       (a.y + a.h > b.y);
}

// 화면 해상도 (프로젝트 전역에서 공용으로 사용)
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;
