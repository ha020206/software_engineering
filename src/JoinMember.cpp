#include "menu.h"
#include "JoinMember.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "GetDate.h"

// 회원가입 함수 
struct member JoinMember(struct member * memberBook, int * memberCount) {
	struct member buffer = { 0 }; //  회원을 입력받을 구조체 선언 
	int again = 0;
	if (*memberCount == 0) { // 회원이 아무도 없을때, 첫 회원은 관리자로 입력받는다. 
		printf("------------------------------\n");
		printf("--- 최초 관리자 가입 모드 ---\n");
		printf("------------------------------\n");
		strcpy(buffer.manager, "관리자" ); //  관리자로 값 설정 
	}
	else {
		printf("... 일반 회원가입 모드\n");
		strcpy(buffer.manager, "일반회원"); //  일반회원으로 값 설정 
	}
	// 이름 입력
	printf("... 이름?\n");
	strcpy(buffer.name, RightMemberName(buffer.name));
	// 전화번호 입력
	do {
		again = 0;
		printf("... 전화번호?\n");
		strcpy(buffer.num, RightMemberNum(buffer.num));
		again = IsMemberNumInList(memberBook, *memberCount, buffer.num);
		if (again == 1) {
			printf("... 이미 가입된 전화번호가 존재합니다. \n");
			printf("... 01. 다른 전화번호 입력 \n... 02. 전화번호 입력 취소\n");
			int key = RightMenuKey(2);
			if (key == 2) {
				printf("... 메뉴로 돌아갑니다. \n");
				return { 0 };
			}
		}
	} while (again == 1);

	// 주민등록번호 입력
	do {
		again = 0;
		printf("... 주민등록번호? [000000-0000000] 의 형식으로 입력하세요.\n");
		strcpy(buffer.ident, RightMemberIdent(buffer.ident)); // 
		again = IsMemberIdentInList(memberBook, *memberCount, buffer.ident);
		if (again == 1) {
			printf("... 이미 가입된 주민등록번호가 존재합니다. \n");
			printf("... 01. 다른 주민등록번호 입력 \n... 02. 주민등록번호 입력 취소\n");
			int key = RightMenuKey(2);
			if (key == 2) {
				printf("... 메뉴로 돌아갑니다. \n");
				return { 0 };
			}
		}
	} while (again == 1);

	// 주민등록번호를 통한 나이 자동 계산
	buffer.age = CountAge(buffer.ident); // 날짜 계산
	// 회원 아이디 입력
	do {
		again = 0;
		printf("... 로그인 시 아이디?\n");
		strcpy(buffer.id, RightMemberId(buffer.id));


		again = IsMemberIdInList2(memberBook, *memberCount, buffer.id);
		if (again == 1) {
			printf("... 이미 가입된 아이디가 존재합니다. \n");
			printf("... 01. 다른 아이디 입력 \n... 02. 아이디 입력 취소\n");
			int key = RightMenuKey(2);
			if (key == 2) {
				printf("... 메뉴로 돌아갑니다. \n");
				return { 0 };
			}
		}
	} while (again == 1);
	// 비밀번호 입력
	printf("... 로그인 시 비밀번호?\n");
	strcpy(buffer.passWord, RightMemberPassWord(buffer.passWord));

	// 최초가입시 지불 금액은 0 으로 초기화 
	buffer.pay = 0;
	* memberCount = ( * memberCount ) + 1;

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-15s %-15s %-15s %-10s %-15s %-15s \n", "이름", "전화번호", "주민등록번호","나이", "아이디", "비밀번호");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-15s %-15s %-15s %-10d %-15s %-15s \n", buffer.name, buffer.num, buffer.ident, buffer.age, buffer.id, buffer.passWord);
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("... 등록 완료! 메뉴로 돌아갑니다.\n");
	return buffer;
}