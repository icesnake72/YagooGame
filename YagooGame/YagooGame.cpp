// YagooGame.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 숫자 야구 게임입니다.
// 컴퓨터가 3자리의 숫자를 임의로 생각하고
// 사용자가 컴퓨터가 정한 숫자를 찾아가는 게임입니다.
// 
// 숫자를 찾기위해 컴퓨터는 힌트를 제공합니다.
// 사용자가 숫자를 입력하면 컴퓨터는 입력된 숫자를 판단해서
// 자리수와 숫자가 일치하면 strike, 숫자만 일치하고 자리수가 틀렸을 경우에는 ball로 알려줍니다.
//
// 일치하는게 숫자가 없으면 out입니다
// 예를들어 3자리의 숫자중 1개의 수가 자리수와 숫자가 일치하고 1개의 수는 숫자만 맞췄을 경우 1스트라이크 1볼이라고 알려줍니다.
// 3자리 모두 맞추면 성공이며 게임을 종료합니다.
// 


// 327
/*
* 123	// 1s 1b
* 124	// 1s  ---> 1또는 2가 맞으며, 3은 확실한데 자리가 틀리고, 4는 아님 확정
* 145	// out ---> 1,4,5 다 아님
* 323	// 2s
* 326	// 2S
* 327	// BINGO!!! CONGRATULATIONS!!! You have done at 6th time.
*/


//
// 사용할 API(또는 Library)가 정의된 헤더파일을 먼저 지정해 주어야 한다.
#include <stdio.h>
#include <time.h>	// time()함수를 위해 사용
#include <stdlib.h>	// srand(), rand()함수를 위해 사용
#include <conio.h>	// _getch()를 위해 사용

#define GOAL_COUNT 3
#define RAND_RANGE 10

void randomize();	// 랜덤 초기화 함수를 선언.
int GetRandomValue(int nRange);	// 랜덤값을 생성하는 함수

int main()
{	
	randomize();	// 랜덤 초기화 함수 호출

	//
	// 사용자가 맞춰야할 3개의 임의의 숫자
	unsigned char nGoal[GOAL_COUNT];
#ifdef _DEBUG
	int key = 0;
	do {
#endif
		// 3자리의 랜덤 숫자를 생성한다.
		for (int i = 0; i < GOAL_COUNT; i++) {
			nGoal[i] = GetRandomValue(RAND_RANGE);	// 0~9의 랜덤한 숫자를 생성한다.
		
			//
			// 이번에 생성된 난수가 이전의 생성된 난수와 겹치는지 조사하고 겹치면 새로운 난수 생성 // for (int j = 0; j < i; j++) 루프를 사용할 수도 있다.
			int j = 0;
			while (j < i) {
				if (nGoal[j] != nGoal[i]) { 
					++j;
					continue;
				}

				nGoal[i] = GetRandomValue(RAND_RANGE);
			}
#ifdef _DEBUG
			printf("nGoal[%u] = %u\n", i, nGoal[i]);	// 이 printf문은 값이 정상적으로 설정이 되어있는지 디버깅용 출력입니다. 추후에 주석처리 합시다.
#endif
		}
#ifdef _DEBUG
		printf("Press x key to quit to program, or any other key to continue : \n");
		key = _getch();
	} while (key != 'x');
#endif


	//int nNum = 0;
	//do {
	//	int nRet = scanf_s("%d", nNum);

	//} while (1);
	
	

	// 위의 for()루프 구문은 다음과 같이 while(), do~while() 구문으로 바꿔서 쓸 수 있다.
	/*
	int i = 0;
	while (i < 3) {
		nGoal[i++] = rand() % 10;
		//... 이하 생략
	}
	
	int j = 0;
	do {
		nGoal[i++] = rand() % 10;
		//... 이하 생략
	} while (j >= 3);
	*/

	
	return 0;
}


//
// 랜덤 초기화를 수행하는 함수(를 구현)
void randomize() {

	//
	// 랜덤 초기화, 
	// srand()함수는 sdtlib.h에 정의되어 있고, 
	// time()함수는 time.h에 정의되어 있다.
	srand((unsigned int)time(NULL));

	return;
}

//
// 0에서부터 nRange 범위의 수까지 랜덤한 값을 생성하여 리턴한다.
int GetRandomValue(int nRange)
{
	return rand() % nRange;
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
