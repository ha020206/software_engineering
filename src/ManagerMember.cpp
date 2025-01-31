#include "menu.h"
#include "ManagerMember.h"
#include "CheckRightValue.h"
#include "ScreenClear.h"
#include "CheckInList.h"
#include "ManagerSubFunction.h"
#include "SortStruct.h"
#include "GetDate.h"
// 회원 정보 관리 소스
//

// 관리자 전용 회원 검색 및 수정 삭제 
struct member* SearchMemberBook_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int * sepcialKey, char * loginId) {
	
	// 검색어 입력 
	char searchKey[40] = { 0 };
	int count = 0; // 검색어와 일치하는 목록의 개수 count 
	printf("... 검색 할 내용 ?\n");
	strcpy( searchKey, RightStringSize(searchKey , 40) );

	// 검색어와 일치하는 항목 갯수 카운트 (이름, 아이디, 주민번호, 전화번호, 비밀번호와 비교함)
	for (int i = 0; i < * memberCount; i++) {
		if (strstr(memberBook[i].name, searchKey) || strstr(memberBook[i].id, searchKey) || strstr(memberBook[i].ident, searchKey) || strstr(memberBook[i].num, searchKey) || strstr(memberBook[i].passWord, searchKey)) {
			count++;
		}
	}
	// 일치하는 항목이 없을 경우,, 메뉴로 돌아감 
	if(count == 0){
		printf("... 검색어와 일치하는 목록이 없습니다. \n");
		printf("... 회원 관리 메뉴로 돌아갑니다.\n");
		return memberBook;
	}
	// 일치하는 항목이 있을 경우, 프린트 
	printf("... 총 %d 개의 목록 검색 \n", count);
	int* searckIndex = (int*)malloc(sizeof(int) * count); // 동적메모리 설정 
	count = 0; // 다시 셀거니깐 초기화 
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n","번호", "이름", "전화번호", "주민등록번호", "나이",  "아이디", "비밀번호", "회원 구분", "충전 금액");
	printf("---------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < *memberCount; i++) {
		if (strstr(memberBook[i].name, searchKey) || strstr(memberBook[i].id, searchKey) || strstr(memberBook[i].ident, searchKey) || strstr(memberBook[i].num, searchKey) || strstr(memberBook[i].passWord, searchKey)) {
			searckIndex[count++] = i; // 목록의 실제 번호를 담음 
			printf(" %-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", count, memberBook[i].name , memberBook[i].num, memberBook[i].ident, memberBook[i].age , memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
		}
	}
	printf("---------------------------------------------------------------------------------------------------------\n");
	int key = 0; // 메뉴 입력받을 키
	int listIndex = 0; // 목록번호의 memberBook 에서 실제 인덱스번호를 받을 변수 
	while (key != 3) {
		memberBook = SortMemberBook(memberBook, * memberCount); // 수정시 내용이 바뀌므로 Sort
		printf("... 다음 작업? \n");
		printf("01. 회원 정보 삭제\n02. 회원 정보 수정\n03. 회원 검색 및 수정/삭제 종료\n");
		key = RightMenuKey(3);
		if (key == 1) { // 회원 삭제 메뉴
			if (count != 1) { //  항목 개수가 1이 아니면, 고르게 함 
				printf("... 삭제를 원하는 목록의 번호?\n");
			    listIndex = RightMenuKey(count) -1 ; // 선택한 번호 -1 == 배열 인덱스번호
			}

			memberBook = DelMember_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex]  , sepcialKey, loginId);
			free(searckIndex);
			searckIndex = NULL;
			return memberBook;

		}
		else if (key == 2) {
			if (count != 1) { // 회원 수정 메뉴 
				printf("... 수정을 원하는 목록의 번호?\n");
				listIndex = RightMenuKey(count) - 1;
			}
			memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex], sepcialKey, loginId);
			free(searckIndex);
			searckIndex = NULL;
			return memberBook;

		}
		else if (key == 3) {
			printf("... 회원 관리 메뉴로 돌아갑니다.\n");
			free(searckIndex);
			searckIndex = NULL;
			return memberBook;
		}
	}
}
// 사람 삭제 함수 
struct member* DelMemberBook(struct member * memberBook, int index, int * memberCount) { 

	for (int i = index; i < (* memberCount); i++) {
		memberBook[i] = memberBook[i + 1];
	}
	* memberCount = (* memberCount) - 1;
	printf("... 회원 삭제 완료 !\n");
	return memberBook;
}




// 회원 전용 정보 수정 
struct member* ChangeMemberBook_forMember(struct member* memberBook, int index, int* memberCount) {
	int key = 0;
	struct member buffer = { 0 };
	while (key != 5) {
		int again = 0;
		int key2 = 0;
		printf("... 수정 할 항목?\n");
		printf("01. 이름\n02. 전화번호 \n03. 주민등록번호\n04. 비밀번호\n");
		key = RightMenuKey(4);
		if (key == 1) {
			printf("... 수정 할 이름? [ 현재 이름 : %s ]\n", memberBook[index].name);
			RightMemberName(memberBook[index].name);
			printf("\n... 수정한 회원 정보를 출력합니다. \n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "충전 금액", "회원 구분");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
			printf("---------------------------------------------------------------------------------------------------------\n");
			return memberBook;
		}
		else if (key == 2) {
			again = 0;
			do {
				key2 = 0;
				again = 0;
				printf("\n... 수정 할 전화번호? [ 현재 전화번호 : %s ]\n", memberBook[index].num);
				strcpy(buffer.num, RightMemberNum(buffer.num));
				again = IsMemberNumInList(memberBook, *memberCount, buffer.num);
				if (again == 1) {
					printf("... 이미 가입된 전화번호가 존재합니다. \n");
					printf("... 01. 다른 전화번호 입력 \n... 02. 전화번호 입력 취소\n");
					key2 = RightMenuKey(2);
					if (key2 == 2) {
						printf("... 메뉴로 돌아갑니다. \n");
						again = 0;
						return memberBook;
					}
				}
			} while (again == 1);
			if (key2 == 0) {
				strcpy(memberBook[index].num, buffer.num);
				printf("\n... 수정 완료! \n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "충전 금액", "회원 구분");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("... 메뉴로 돌아갑니다. \n");
				return memberBook;
			}
		}
		else if (key == 3) {
			do {
				key2 = 0;
				again = 0;
				printf("... 수정 할 주민등록번호? [ 현재 주민등록번호 : %s ]\n", memberBook[index].ident);
				strcpy(buffer.ident, RightMemberIdent(buffer.ident)); // 
				again = IsMemberIdentInList(memberBook, *memberCount, buffer.ident);
				if (again == 1) {
					printf("... 이미 가입된 주민등록번호가 존재합니다. \n");
					printf("... 01. 다른 주민등록번호 입력 \n... 02. 주민등록번호 입력 취소\n");
					key2 = RightMenuKey(2);
					if (key2 == 2) {
						printf("... 메뉴로 돌아갑니다. \n");
						again = 0;
						return memberBook;	
					}
				}
			} while (again == 1);
			if (key2 == 0) {
				strcpy(memberBook[index].ident, buffer.ident);
				memberBook[index].age = CountAge(memberBook[index].ident);

				printf("\n... 수정 완료! \n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "충전 금액", "회원 구분");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("... 메뉴로 돌아갑니다. \n");
				return memberBook;
			}
		}
		else if (key == 4) {
			printf("... 수정 할 비밀번호? [ 현재 비밀번호 : %s ]\n", memberBook[index].passWord);
			strcpy(memberBook[index].passWord, RightMemberPassWord(memberBook[index].passWord));
			printf("\n... 수정 완료! \n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "충전 금액", "회원 구분");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("... 메뉴로 돌아갑니다. \n");
			return memberBook;
		}
	}
}

