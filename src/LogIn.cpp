#include "menu.h"
#include "LogIn.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "ScreenClear.h"

// 로그인 함수 
struct member * LogIn(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int * index, int * successLogin, char * loginId) {
	int again = 0; // 반복문 재실행 변수 
	* index = -1; // 로그인 한 멤버의 인덱스번호를 담는 변수  
	struct member user = { 0 }; // 로그인 시 아이디와 비밀번호 등을 담는 변수 
	// 아이디를 입력받는 부분 
	do {
		again = 0; 
		printf("... 아이디?\n"); //  아이디 입력받음 
		strcpy(user.id, RightStringSize(user.id, 16)); 
		again = IsMemberIdInList(memberBook, * memberCount, user.id, index); //  등록된 아이디가 있다면,, again = 1 / index는 일치하는 값의 인덱스 번호를 받음 
		if (again == 0) {
			printf("... 등록된 아이디가 존재하지 않습니다.\n");
			printf("... 01. 다시 입력\n... 02. 아이디 찾기\n... 03. 종료\n");
			int key = RightMenuKey(3);
			if (key == 2) { // 아이디 찾기 실행 
				printf("... 이름?\n");
				RightMemberName(user.name);
				printf("... 전화번호?\n");
				RightMemberNum(user.num);
				printf("... 주민등록번호?\n");
				RightMemberIdent(user.ident);
				int i = 0;
				for (i = 0; i < * memberCount; i++) {
					if ( (strcmp(memberBook[i].name, user.name) == 0) && (strcmp(memberBook[i].num, user.num) == 0) && (strcmp(memberBook[i].ident, user.ident) == 0) ){
						* index = i; //  모든 값이 일치했을때 아이디를 알려줌 
					}
				}
				if ( * index == -1 ) { //  일치하지 않으면 -1 
					printf("... 등록된 회원 정보가 존재하지 않습니다.\n");
					printf("... 초기 화면으로 돌아갑니다.\n");
					ScreenClear();
					return memberBook;
				}

				printf("... %s 님의 아이디는 [ %s ] 입니다.\n", user.name, memberBook[*index].id); // 일치하면 아이디 알려줌 
				
				printf("... 초기 화면으로 돌아갑니다.\n"); //  다시 로그인 시킴 
				ScreenClear();
				return memberBook;

			}
			else if (key == 3) { //  종료 버튼 클릭시
				ScreenClear();
				return memberBook;
			}
		}
	} while (again == 0);


	// 비밀번호를 입력받는 부분 
	do {
		again = 0;
		printf("... 비밀번호?\n");
		strcpy(user.passWord, RightStringSize(user.passWord, 16));
		again = IsMemberPassWordInList(memberBook, * memberCount, user.passWord, *index); // 아이디 입력 시 받아온 인덱스가 지칭하는 비밀번호와 입력한 비밀번호가 동일하면 again = 1
		if (again == 0) {
			printf("... 비밀번호 오류입니다.\n");
			printf("... 01. 다시 입력\n... 02. 비밀번호 변경\n... 03. 종료\n");
			int key = RightMenuKey(3);
			if (key == 2) {
				printf("... 이름?\n");
				RightMemberName(user.name);
				printf("... 전화번호?\n");
				RightMemberNum(user.num);
				printf("... 주민등록번호?\n");
				RightMemberIdent(user.ident);
				if ((strcmp(memberBook[* index].name, user.name) == 0) && (strcmp(memberBook[* index].num, user.num) == 0) && (strcmp(memberBook[* index].ident, user.ident) == 0)) {
					printf("... 바꿀 비밀번호?\n"); // 비밀번호를 알려주지 않고 바꿔버림 
					strcpy(memberBook[* index].passWord, RightMemberPassWord(memberBook[* index].passWord));
					printf("... [%s] 님의 비밀번호를 [ %s ] 로 변경했습니다.\n", memberBook[* index].name, memberBook[* index].passWord);
					printf("... 초기 화면으로 돌아갑니다.\n");
					ScreenClear();
					return memberBook;
				}
				else {
					printf("... 정보가 일치하지 않습니다. 초기 화면으로 돌아갑니다.\n");
					ScreenClear();
					return memberBook;
				}
			}
			else if (key == 3) {
				ScreenClear();
				return memberBook;
			}
		}
	} while (again == 0);

	strcpy(loginId, memberBook[*index].id);  // loginId 변수에 현재 로그인 성공한 회원의 아이디를 보냄 
	*successLogin = 1; // 모든게 일치하면,, *successLogin = 1로 변경 , 이후 메뉴 실행 
	printf("\n... [%s] [%s] 님 반갑습니다.\n\n", memberBook[* index].name, memberBook[* index].manager); // 로그인 성공을 알림 
	ScreenClear();
	return memberBook;
}
