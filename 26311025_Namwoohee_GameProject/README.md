# Sky Defender

26311025 남우희 - C++ 2D 슈팅 게임 프로젝트

## 게임 소개
화면 하단의 우주선을 좌우로 조종하며, 위에서 내려오는 적을 총알로 격추하는 클래식 세로 스크롤 슈팅 게임입니다.

- **← / → 방향키**: 우주선 좌우 이동
- **스페이스바**: 총알 발사 (시작/재시작 화면에서는 다음 화면으로 진행)
- 적과 부딪히거나, 적이 화면 아래까지 도달하면 생명(목숨) 1개 감소
- 생명이 모두 소진되면 결과 화면으로 전환, 최종 점수 확인 가능

## 화면 흐름
`SceneBegin (시작 화면)` → `ScenePlay (게임 플레이)` → `SceneResult (결과 화면)` → 다시 시작 화면으로 순환

## 프로젝트 구조
```
26311025_Namwoohee_GameProject/
├─ 26311025_Namwoohee_GameProject.sln
└─ 26311025_Namwoohee_GameProject/
   ├─ _main.cpp            # 진입점
   ├─ CApplication.h/.cpp  # 앱 부트스트랩 + 씬 전환/점수/생명 관리
   ├─ CScene.h/.cpp        # 씬 공통 인터페이스
   ├─ SceneBegin.h/.cpp    # 시작 화면
   ├─ ScenePlay.h/.cpp     # 실제 게임 플레이 (스폰/충돌/점수 로직)
   ├─ SceneResult.h/.cpp   # 결과 화면
   ├─ Player.h/.cpp        # 플레이어 우주선
   ├─ Bullet.h/.cpp        # 총알
   ├─ Enemy.h/.cpp         # 적
   ├─ Common.h             # AABB 충돌 판정 등 공용 유틸
   ├─ packages.config      # glc2d, DXSDK.D3DX NuGet 패키지
   └─ Texture/             # 이미지 리소스 (임시 플레이스홀더)
```

## 빌드 방법
1. Visual Studio 2022에서 `26311025_Namwoohee_GameProject.sln` 열기
2. NuGet 패키지 복원 (자동으로 되지 않으면 우클릭 → "NuGet 패키지 복원")
3. 빌드 후 실행 (Debug|x64 권장)

## 참고 / TODO
- `Texture/` 폴더의 이미지는 임시로 만든 플레이스홀더입니다. 실제 게임에 어울리는 그림으로 교체해서 사용하세요.
- glc2d 헤더(`glc2d.h`)에 자체 입력 처리 함수(`g2_` 접두사)가 있는지 확인하지 못해, 키보드 입력은 표준 Win32 API인 `GetAsyncKeyState`로 처리했습니다. 만약 수업에서 안내받은 전용 입력 함수가 있다면 `Player.cpp`, `ScenePlay.cpp`, `SceneBegin.cpp`, `SceneResult.cpp`의 해당 부분을 교체하세요.
- 화면에 점수/생명을 텍스트로 표시하는 부분은 glc2d의 텍스트 출력 함수명을 확인하지 못해 우선 콘솔(stdout) 출력으로 대체했습니다. `g2_DrawText` 같은 함수가 있다면 `ScenePlay::Render()`에 추가하면 됩니다.
- 난이도(적 스폰 간격, 속도, 총알 쿨다운 등)는 `ScenePlay.h`의 멤버 변수에서 조정할 수 있습니다.
