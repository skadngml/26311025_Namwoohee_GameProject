#pragma once

// 모든 씬(화면)이 상속받는 기본 인터페이스
// - Init    : 씬 진입 시 1회 호출 (텍스처 로드 등)
// - Update  : 매 프레임 로직 갱신 (입력 처리, 이동, 충돌 등)
// - Render  : 매 프레임 그리기
// - Destroy : 씬 종료 시 1회 호출 (텍스처 해제 등)
class CScene
{
public:
	virtual int Init();
	virtual int Update();
	virtual int Render();
	virtual int Destroy();

	virtual ~CScene() = default;
};
