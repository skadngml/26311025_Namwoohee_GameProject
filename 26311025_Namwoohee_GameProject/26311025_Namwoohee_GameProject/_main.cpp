// include the 2d game header file
#include "glc2d.h"
#include <stdio.h>
#include "CApplication.h"

CApplication g_App; // 앱 인스턴스 전역 선언

int main()
{
	g_App.Init();   // 초기화 (윈도우 생성, 첫 씬 로드)

	g2_Run();       // 메인 루프 실행

	g_App.Destroy(); // 자원 해제

	return 0;
}
