// YagooGame.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//
// 2023년 1월 14일 
// 개발자 : 김은범
// ver 0.9
//
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
#include <ctype.h>	// isdigit()를 위해 사용

#define GOAL_COUNT 3
#define RAND_RANGE 10
#define MIN_VAL	100
#define MAX_VAL	987
#define TERMINATE	'x'

void randomize();	// 랜덤 초기화 함수를 선언.
unsigned char GetRandomValue(int nRange);	// 랜덤값을 생성하는 함수
unsigned char CheckThisOut(void);	// 사용자가 입력한 값의 판단
unsigned short InputFromUser(void);	// 사용자로부터 숫자를 입력받는다.
unsigned short Array2Digit(unsigned char* pArr);	// 배열에 담긴 숫자를 백단위 3자리의 숫자로 변환
void ByeMessage(void);


// 전역 변수의 선언
static unsigned char nGoal[GOAL_COUNT];	// 컴퓨터가 정의한 수 (랜덤), 사용자가 맞춰야할 3개의 임의의 숫자
static unsigned char nUser[GOAL_COUNT];	// 사용자가 입력한 수

int main()
{		
	randomize();	// 랜덤 초기화 함수 호출

	do {				
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
					if (nGoal[j] != nGoal[i]) { // 이전 생성값들과 현재 생성값을 비교해서 다르면 OK
						++j;
						continue;
					}

					// 
					// 이전 생성값들과 현재 생성값을 비교해서 같으면 새로운 랜덤값을 만들어 다시 입력하고 돌아가서 비교하기를 반복 수행
					nGoal[i] = GetRandomValue(RAND_RANGE);
				}
#ifdef _DEBUG
				printf("nGoal[%u] = %u\n", i, nGoal[i]);	// 이 printf문은 값이 정상적으로 설정이 되어있는지 디버깅용 출력입니다. 추후에 주석처리 합시다.
#endif
			}
#ifdef _DEBUG

			int nRandValue = 0;
			nRandValue = Array2Digit(nGoal);
			printf("Random Value is %u\n", nRandValue);

			printf("Press x key to quit to program, or any other key to continue : \n");
			key = _getch();
		} while (key != TERMINATE);
#endif

		unsigned short nRes = 0;
		do {
			// 사용자로부터 숫자 3자리를 입력받는다.			
			nRes = InputFromUser();
			if (!nRes)
			{
				ByeMessage();
				return 0;
			}

			printf("\n입력하신 숫자는 %u 입니다. ======>> ", nRes);
				
			//
			// 사용자로부터 받은 숫자와 컴퓨터가 정한 랜덤한 숫자를 비교하여 일치하면 루프를 탈출한다.
			nRes = CheckThisOut();	// 정답이 아니면 0이 반환된다.

		} while ( nRes==0 ); // while(!nRes);
		
		printf("축하합니다!\n정답을 맞혔습니다!!!\n");
		

		// 게임을 계속 진행할것인 물어본다.
		printf("게임을 또 진행할까요?(y or x) : ");
		unsigned char ch = _getch();
		if (ch == TERMINATE)
			break;

		printf("\n\n");

	} while (1);

		
	
	ByeMessage();

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
unsigned char GetRandomValue(int nRange)
{
	return (unsigned char)(rand() % nRange); // 강제 형변환이 일어나지만 10보다 작은수가 확실하므로 괜찮다.
}

unsigned short InputFromUser(void) {
	printf("숫자를 입력하세요, 게임을 포기하시려면 언제든지 x를 눌러주세요,\n");

	unsigned char i = 0;	// 각 자릿수별로 입력을 받기위해 배열 인덱스를 초기화 한다.

	do {
		printf("%u번째 자리 숫자를 입력하세요 --->  ", i + 1);
		nUser[i] = _getch();	// 값을 입력받는다.
		if (isdigit(nUser[i])) {	// 숫자값으로 정확하게 입력했는지 검사한다.
			nUser[i] -= '0';		// ASCII 코드값을 0 ~ 9 사이의 값으로 변환해야 한다.
			printf("%u\n", nUser[i++]);	// 정상적인 입력이면 인덱스를 1증가하여 새로운 자릿수의 값을 입력받는다.
			
			if (i >= GOAL_COUNT)	// 정상적으로 3자리 숫자를 전부 입력받았으면 루프를 탈출하여 종료하고, 아니면 루프를 계속 돈다. 
				break;
			else
				continue;
		}
		else {
			// 사용자가 x 키를 눌러 종료를 원하면 더이상 입력받지 않고 종료시키기 위해 0을 반환하고 함수를 종료한다.
			if (nUser[i] == TERMINATE)
				return 0;

			// 0 ~ 9 외의 키를 눌렀을 경우에는 옳바를 입력을 유도한다.
			printf("숫자를 입력해주세요,\n");
		}
	} while (1);
		
	// 입력된 3자리 숫자를 리턴하여 종료한다.
	return Array2Digit(nUser);
}

unsigned char CheckThisOut() {

	unsigned char s = 0;	// 스트라이크 카운트 초기화
	unsigned char b = 0;	// 볼 카운트 초기화

	// 
	// 비교할수 있는 모든 경우의 수만큼 루프를 돌며, 두개의 수와 자릿수를 비교한다, 3 + 3 + 3 번의 루프를 돌아야 한다
	for (int i = 0; i < GOAL_COUNT; i++) {
		for (int j = 0; j < GOAL_COUNT; j++) {
			if (nGoal[i] == nUser[j]) {
				if (i == j)
					++s;	// 숫자가 맞고 자릿수까지 맞으면 스트라이크 증가
				else
					++b;	// 숫자는 맞지만 자릿가 다르면 볼 증가
			} // end if
		} // end for int j
	}	// end fo int i

	// s가 3이면 3자리 숫자를 맞혔다는것으로 1을 반환한다.
	if (s == GOAL_COUNT)
		return 1;

	// 정답이 아닌경우 힌트를 만들어 출력해주고 0을 반환하여 아직은 정답이 아님을 알려준다.
	printf("%u 스트라이크, %u 볼입니다.\n\n\n", s, b);

	return 0;
}


unsigned short Array2Digit(unsigned char* pArr) {
	return pArr[0] * 100 + pArr[1] * 10 + pArr[2];	// 각 자릿수에 가중치를 곱하면 3자리 숫자를 갖는 자연수를 얻을수 있다.
}

// 종료 메세지를 출력한다.
void ByeMessage(void) {
	printf("\n게임을 종료하였습니다\n이용해주셔서 감사합니다!\n");
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
