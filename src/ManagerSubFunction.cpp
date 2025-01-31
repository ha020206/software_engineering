#include "ManagerSubFunction.h"
#include "menu.h"
#include "CheckInList.h"
#include "ManagerMember.h"
#include "CheckRightValue.h"
#include "GetDate.h"
#include "InsertCoin.h"
#include "ScreenClear.h"

struct member* ChangeMember_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int userIndex,  int* sepcialKey, char* loginId) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
	printf("---------------------------------------------------------------------------------------------------------\n");

	int managerCount = 0;
	for (int i = 0; i < *memberCount; i++) {
		if (strcmp(memberBook[i].manager, "관리자") == 0) { // 관리자의 개수를 센다 -> 관리자가 0명이면 프로그램 진행 안되므로 지워지는것 방지 
			managerCount++;
		}
	}
	struct member buffer = { 0 };
	printf("... 수정할 항목?\n");
	printf("01. 이름\n02. 전화번호\n03. 주민등록번호\n04. 비밀번호\n05. 회원 구분\n");
	int Key = RightMenuKey(5);
	int again = 0;
	int key2 = 0;

	if (Key == 1) {
		printf("... 수정 할 이름? [ 현재 이름 : %s ]\n", memberBook[userIndex].name);
		RightMemberName(memberBook[userIndex].name);

		printf("... 수정 완료 !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... 메뉴로 돌아갑니다 \n");
		return memberBook;
	}
	else if (Key == 2) {
		again = 0;
		do {
			again = 0;
			printf("... 수정 할 전화번호? [ 현재 전화번호 : %s ]\n", memberBook[userIndex].num);
			strcpy(buffer.num, RightMemberNum(buffer.num));
			again = IsMemberNumInList(memberBook, * memberCount, buffer.num);
			if (again == 1) {
				printf("... 이미 가입된 전화번호가 존재합니다. \n");
				printf("... 01. 다른 전화번호 입력 \n... 02. 전화번호 입력 취소\n");
				key2 = RightMenuKey(2);
				if (key2 == 2) {
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;

				}
			}
		} while (again == 1);
		strcpy(memberBook[userIndex].num, buffer.num);
		printf("... 수정 완료 !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... 메뉴로 돌아갑니다 \n");
		return memberBook;
	}
	else if (Key == 3) {
		do {
			again = 0;
			printf("... 수정 할 주민등록번호? [ 현재 주민등록번호 : %s ]\n", memberBook[userIndex].ident);
			strcpy(buffer.ident, RightMemberIdent(buffer.ident)); // 
			again = IsMemberIdentInList(memberBook, * memberCount, buffer.ident);
			if (again == 1) {
				printf("... 이미 가입된 주민등록번호가 존재합니다. \n");
				printf("... 01. 다른 주민등록번호 입력 \n... 02. 주민등록번호 입력 취소\n");
				key2 = RightMenuKey(2);
				if (key2 == 2) {
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}
			}
		} while (again == 1);
		strcpy(memberBook[userIndex].ident, buffer.ident);
		memberBook[userIndex].age = CountAge(memberBook[userIndex].ident); //  나이 자동 변경
		printf("... 수정 완료 !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... 메뉴로 돌아갑니다 \n");
		return memberBook;

	}
	else if (Key == 4) {
		printf("... 수정 할 비밀번호? [ 현재 비밀번호 : %s ]\n", memberBook[userIndex].passWord);
		strcpy(memberBook[userIndex].passWord, RightMemberPassWord(memberBook[userIndex].passWord));

		printf("... 수정 완료 !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... 메뉴로 돌아갑니다 \n");
		return memberBook;
	}
	else if (Key == 5) {
		if (strcmp(memberBook[userIndex].manager, "일반회원") == 0) {
			printf("... 관리자 회원으로 변경 하시겠습니까? [ 예 : 1 | 아니오 : 2 ]\n");
			key2 = RightMenuKey(2);
			if (key2 == 1) {
				strcpy(memberBook[userIndex].manager, "관리자");

				printf("... 수정 완료 !\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("... 메뉴로 돌아갑니다 \n");
				return memberBook;
			}
			else {
				printf("... 메뉴로 돌아갑니다 \n");
				return memberBook;
			}
		}
		else {
			if (managerCount == 1) {
				printf("... 관리자가 1 명일 때는 관리자를 일반회원으로 수정할 수 없습니다.\n");
				printf("... 메뉴로 돌아갑니다 \n");
				return memberBook;
			}
			else {
				printf("... 일반 회원으로 변경 하시겠습니까? [ 예 : 1 | 아니오 : 2 ]\n");
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					if (userIndex == GetIndex(memberBook, *memberCount, loginId)) {
						* sepcialKey = -1;
						strcpy(memberBook[userIndex].manager, "일반회원");
						printf("... 수정 완료 !\n");
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("... 초기 메뉴로 돌아갑니다 \n");
						return memberBook;
					}
					strcpy(memberBook[userIndex].manager, "일반회원");
					printf("... 수정 완료 !\n");
					printf("---------------------------------------------------------------------------------------------------------\n");
					printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
					printf("---------------------------------------------------------------------------------------------------------\n");
					printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
					printf("---------------------------------------------------------------------------------------------------------\n");
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}
				else {
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}
			}
		}
	}
}


struct member* DelMember_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int nowIndex, int* sepcialKey, char* loginId) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[nowIndex].name, memberBook[nowIndex].num, memberBook[nowIndex].ident, memberBook[nowIndex].age, memberBook[nowIndex].id, memberBook[nowIndex].passWord, memberBook[nowIndex].manager, memberBook[nowIndex].pay);
	printf("---------------------------------------------------------------------------------------------------------\n");

	int managerCount = 0;
	for (int i = 0; i < *memberCount; i++) {
		if (strcmp(memberBook[i].manager, "관리자") == 0) { // 관리자의 개수를 센다 -> 관리자가 0명이면 프로그램 진행 안되므로 모두가 지워지는 것을 방지함 
			managerCount++;
		}
	}
	
	if ( IsMemberIdInVideoMemberId(memberBook, *memberCount, videoBook, videoCount, memberBook[nowIndex].id) != 0 ) {
		printf(" ... 회원에게 반납하지 않은 비디오가 있는 경우 삭제가 불가능합니다.\n");
		printf("... 메뉴로 돌아갑니다.\n");
		return memberBook;
	}
	else if (strcmp(memberBook[nowIndex].manager, "관리자") == 0) {
		if ( managerCount == 1) {
			printf("... 관리자가 1 명일 때는 관리자를 삭제할 수 없습니다.\n");
			printf("... 메뉴로 돌아갑니다.\n");
			return memberBook;
		}
		else if (GetIndex(memberBook, *memberCount, loginId) == nowIndex ) { // 나 자신을 삭제하는 경우
			DelMemberBook(memberBook, nowIndex, memberCount);
			* sepcialKey = -1;
			printf("... 초기 메뉴로 돌아갑니다.\n");
			return memberBook;
		}
	}
	DelMemberBook(memberBook, nowIndex, memberCount);
	printf("... 메뉴로 돌아갑니다.\n");

	return memberBook;

}

struct video * DelVideo_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int nowIndex) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
	printf("---------------------------------------------------------------------------------------------------------\n");

	if (strcmp(videoBook[nowIndex].isRentaled, "X") == 0) {
		printf("... 대여된 비디오는 삭제할 수 없습니다.\n");
		return videoBook;
	}

	for (int i = nowIndex; i < *videoCount; i++) {
		videoBook[i] = videoBook[i + 1];
	}
	* videoCount = (*videoCount) - 1;
	printf("... 삭제 완료 !\n");
	return videoBook;

}


struct video* ChangeVideo_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int nowIndex) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
	printf("---------------------------------------------------------------------------------------------------------\n");

	int again = 0;
	int key = 0;
	printf("... 수정할 항목?\n");
	printf("01. 비디오 이름\n02. 비디오 감독\n03. 비디오 대여 가격\n04. 비디오 관람 가능 연령대\n05. 비디오 대여 가능 여부\n06. 비디오 반납 날짜 연장\n");
	key = RightMenuKey(6);
	struct video buffer = { 0 };
	if (key == 1) {
		printf("... 비디오 이름 ? [ 현재 이름 : %s ] \n", videoBook[nowIndex].name);
		strcpy(buffer.name, RightVideoName(buffer.name));
		if ( IsVideoNameMakerInList( videoBook, *videoCount , buffer.name, videoBook[nowIndex].maker) != 0) {
			printf("... 이미 등록된 동일한 영화가 존재합니다. \n");
			printf("... 01. 동일 항목의 비디오 등록 진행\n... 02. 비디오 등록 취소\n");
			if ( RightMenuKey(2) == 2) {
				printf("... 메뉴로 돌아갑니다.\n");
				return videoBook;
			}
		}

		strcpy(videoBook[nowIndex].name, buffer.name);
		printf("... 수정된 내용\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... 메뉴로 돌아갑니다.\n");

		return videoBook;
	}
	else if (key == 2) {

		printf("... 비디오 감독 ? [ 현재 감독 : %s ] \n", videoBook[nowIndex].maker);
		strcpy(buffer.maker, RightVideoMaker(buffer.maker));

		if (IsVideoNameMakerInList(videoBook, *videoCount, videoBook[nowIndex].name, buffer.maker) != 0) {
			printf("... 이미 등록된 동일한 영화가 존재합니다. \n");
			printf("... 01. 동일 항목의 비디오 등록 진행\n... 02. 비디오 등록 취소\n");
			if (RightMenuKey(2) == 2) {
				printf("... 메뉴로 돌아갑니다.\n");
				return videoBook;
			}
		}
		strcpy(videoBook[nowIndex].maker, buffer.maker);

		printf("... 수정된 내용\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... 메뉴로 돌아갑니다.\n");

		return videoBook;
	}
	else if (key == 3) {
		printf("... 비디오 대여 금액 ?  [ 현재 금액 : %d ] \n", videoBook[nowIndex].price);
		videoBook[nowIndex].price = RightVideoPrice();
		printf("... 수정된 내용\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... 메뉴로 돌아갑니다.\n");

		return videoBook;

	}
	else if (key == 4) {

		printf("... 비디오 관람 가능 연령대 ? (엔터시 전체 연령으로 기록) [ 현재 연령대 : %d ] \n", videoBook[nowIndex].age);
		videoBook[nowIndex].age = RightVideoAge();
		printf("... 수정된 내용\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... 메뉴로 돌아갑니다.\n");

		return videoBook;
	}
	else if (key == 5) {
		int key3 = 0;
		if (strcmp(videoBook[nowIndex].isRentaled, "X") == 0) {
			printf("... 반납된 비디오로 변경 하시겠습니까? [ 예 : 1 | 아니오 : 2 ] \n");
			key3 = RightMenuKey(2);
			if (key3 == 1) {
				int changeIndex = 0;
				IsMemberIdInList(memberBook, *memberCount, videoBook[nowIndex].memberId, &changeIndex); // 회원의 인덱스 번호 찾기 
				printf("... [ID : %s][이름 : %s] 회원의 반납을 진행합니다. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
				if(videoBook[nowIndex].rentalLimit - VideoDateMaker() < 0 ){ //  만약 연체 ? 
					int overDay = VideoOverDayMaker(videoBook[nowIndex].rentalLimit);
					printf("... 연체된 일수 [ %d ]에 대한 연체료가 있습니다.\n", overDay);
					int change = overDay * videoBook[nowIndex].price;
				
					
					printf("------- 영수증 -------\n");
					printf("... 하루 대여료 [%d]원\n", videoBook[nowIndex].price);
					printf("... 총 [ %d ] 일 연체 \n", overDay) ;
					printf("... 결제 예정 금액 [%d]원\n",  change);
					printf("----------------------\n");
					
					printf("... [ 회원의 충전금액 :%d 원]\n", memberBook[changeIndex].pay);

					while (memberBook[changeIndex].pay - change < 0) {
						printf("... 회원의 보유 금액이 부족합니다. 회원 금액 충전 페이지로 이동합니다.\n");
						memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
					}
					printf("... [ID : %s][이름 : %s] 회원에게 [ %d ] 원 받습니다.\n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
					memberBook[changeIndex].pay -= change;
					printf("... 결제 완료! [ 회원의 잔액 :%d 원]\n", memberBook[changeIndex].pay);
				}


				strcpy(videoBook[nowIndex].isRentaled, "O");
				strcpy(videoBook[nowIndex].memberId, "-");
				videoBook[nowIndex].rentalDate = 0;
				videoBook[nowIndex].rentalLimit = 0;
				printf("... 반납 완료 !\n");
				printf("... 수정된 내용\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");


				printf("... 메뉴로 돌아갑니다.\n");

				return videoBook;
			}
			else {
				printf("... 메뉴로 돌아갑니다.\n");

				return videoBook;
			}
		}
		else {
			printf("... 대여된 비디오로 변경 하시겠습니까? [ 예 : 1 | 아니오 : 2 ]\n");
			key3 = RightMenuKey(2);
			if (key3 == 1) {
				int key4 = 0;
				do {
					key4 = 0;
					again = 0;
					printf("... 대여자 ID? \n");
					strcpy(buffer.id, RightMemberId(buffer.id));

					again = IsMemberIdInList2(memberBook, *memberCount, buffer.id);
					if (again != 1) {
						printf("... 가입된 아이디가 존재하지 않습니다. \n");
						printf("... 01. 다른 아이디 입력 \n... 02. 아이디 입력 취소\n");
						key4 = RightMenuKey(2);
						if (key4 == 2) {
							printf("... 메뉴로 돌아갑니다. \n");

							return videoBook;
						}
					}
				} while (again != 1 || key4 != 0);
				int changeIndex = 0;
				IsMemberIdInList(memberBook, *memberCount, buffer.id, &changeIndex);
				if (memberBook[changeIndex].age < videoBook[nowIndex].age) {
					printf("... 볼 수 없는 연령가의 비디오는 대여할 수 없습니다.\n");
					printf("... 메뉴로 돌아갑니다.\n");

					return videoBook;
				}
				strcpy(videoBook[nowIndex].memberId, buffer.id);
				int rentalDay = 0;
				printf("... 대여 일수 ? ( 대여는 1일 ~ 14일 까지 가능합니다. )\n");
				rentalDay = RightMenuKey(14);
				// 회원 지불 가격 수정
				int change = rentalDay * videoBook[nowIndex].price;
				printf("... [ID : %s][이름 : %s] 회원의 대여를 진행합니다. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
				printf("------- 영수증 -------\n");
				printf("... 하루 대여료 [%d]원\n", videoBook[nowIndex].price);
				printf("... 총 [ %d ] 일 대여 \n", rentalDay);
				printf("... 결제 예정 금액 [%d]원\n", change);
				printf("----------------------\n");
				printf("... [ 회원의 충전금액 :%d 원]\n", memberBook[changeIndex].pay);
				while (memberBook[changeIndex].pay - change < 0) {
					printf("... 회원의 보유 금액이 부족합니다. 회원 금액 충전 페이지로 이동합니다.\n");
					memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
				}
				memberBook[changeIndex].pay -= change;
				printf("... [ID : %s][이름 : %s] 회원에게 [ %d ] 원 받습니다. \n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
				printf("... 결제 완료! [ 회원의 잔액 :%d 원]\n", memberBook[changeIndex].pay);
				videoBook[nowIndex].rentalLimit = VideoRentalLimitMaker(rentalDay);
				videoBook[nowIndex].rentalDate = VideoDateMaker();
				strcpy(videoBook[nowIndex].isRentaled , "X");

				printf("... 수정된 내용\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");

				printf("... 메뉴로 돌아갑니다.\n");

				return videoBook;
			}
		}
	}
else if (key == 6) {
	if ( strcmp(videoBook[nowIndex].isRentaled , "X") == 0) {
		int changeIndex = 0;
		IsMemberIdInList(memberBook, *memberCount, videoBook[nowIndex].memberId, &changeIndex); // 회원의 인덱스 번호 찾기 
		int change = 0;
		int rentalDay = 0;
		if (videoBook[nowIndex].rentalLimit - VideoDateMaker() < 0) {
			int overDay = 0;
			printf("... 연체된 일수 [ %d ]에 대한 연체료가 있습니다.\n", overDay = VideoOverDayMaker(videoBook[nowIndex].rentalLimit));
			printf("... [ID : %s][이름 : %s] 회원의 연체료 부과를 진행합니다. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
			change = overDay * videoBook[nowIndex].price;
			
			printf("------- 영수증 -------\n");
			printf("... 하루 대여료 [%d]원\n", videoBook[nowIndex].price);
			printf("... 총 [ %d ] 일 연체 \n", overDay);
			printf("... 결제 예정 금액 [%d]원\n", change);
			printf("----------------------\n");
			printf("... [ 회원의 충전금액 :%d 원]\n", memberBook[changeIndex].pay);
			while (memberBook[changeIndex].pay - change < 0) {
				printf("... 회원의 보유 금액이 부족합니다. 회원 금액 충전 페이지로 이동합니다.\n");
				memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
			}
			printf("... [ID : %s][이름 : %s] 회원에게 [ %d ] 원 받습니다. \n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
		
			memberBook[changeIndex].pay -= change;
			printf("... 결제 완료! [ 회원의 잔액 :%d 원]\n", memberBook[changeIndex].pay);
			videoBook[nowIndex].rentalLimit = VideoRentalLimitMaker(0);
			rentalDay = 0;
		}
		printf("... 연장할 대여 일수 ? ( 대여는 1일 ~ 14일 까지 가능합니다. ) [ 현재 반납 예정일 : %d ]\n", videoBook[nowIndex].rentalLimit);
		rentalDay = RightMenuKey(14);
		change = rentalDay * videoBook[nowIndex].price;		
		printf("... [ID : %s][이름 : %s] 회원의 대여 연장을 진행합니다. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
		printf("------- 영수증 -------\n");
		printf("... 하루 대여료 [%d]원\n", videoBook[nowIndex].price);
		printf("... 총 [ %d ] 일 대여 연장 \n", rentalDay);
		printf("... 결제 예정 금액 [%d]원\n", change);
		printf("----------------------\n");
		printf("... [ 회원의 충전금액 :%d 원]\n", memberBook[changeIndex].pay);
		while (memberBook[changeIndex].pay - change < 0) {
			printf("... 회원의 보유 금액이 부족합니다. 회원 금액 충전 페이지로 이동합니다.\n");
			memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
		}
		memberBook[changeIndex].pay -= change;
		printf("... [ID : %s][이름 : %s] 회원에게 [ %d ] 원 받습니다. \n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
		printf("... 결제 완료! [ 회원의 잔액 :%d 원]\n", memberBook[changeIndex].pay);
		videoBook[nowIndex].rentalLimit = VideoOverRentDayMaker(videoBook[nowIndex].rentalLimit, rentalDay);
		printf("... 수정된 내용\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... 메뉴로 돌아갑니다.\n");
	}
	else {
		printf("... 비디오가 대여 상태가 아닙니다.\n");
	}
	return videoBook;
	}
}

struct video* RentVideo_forMember(struct member* memberBook, int * memberCount, struct video * videoBook, int* videoCount, int videoIndex, int userIndex) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", videoBook[videoIndex].name, videoBook[videoIndex].maker, videoBook[videoIndex].id, videoBook[videoIndex].upDate, videoBook[videoIndex].price, videoBook[videoIndex].age, videoBook[videoIndex].isRentaled);
	printf("---------------------------------------------------------------------------------------------------------\n");

	if (strcmp(videoBook[videoIndex].isRentaled, "X") == 0) {
		printf("... 대여된 비디오는 대여할 수 없습니다.\n");
		printf("... 메뉴로 돌아갑니다.\n");

		return videoBook;
	}
	else if (memberBook[userIndex].age < videoBook[videoIndex].age) {
		printf("... 볼 수 없는 연령가의 비디오는 대여할 수 없습니다.\n");
		printf("... 메뉴로 돌아갑니다.\n");

		return videoBook;

	}


	strcpy(videoBook[videoIndex].memberId, memberBook[userIndex].id);
	int rentalDay = 0;
	printf("... 대여 일수 ? ( 대여는 1일 ~ 14일 까지 가능합니다. )\n");
	rentalDay = RightMenuKey(14);
	// 회원 지불 가격 수정
	int change = rentalDay * videoBook[videoIndex].price;
	
	printf("------- 영수증 -------\n");
	printf("... 하루 대여료 [%d]원\n", videoBook[videoIndex].price);
	printf("... 총 [ %d ] 일 대여\n", rentalDay);
	printf("... 결제 예정 금액 [%d]원\n", change);
	printf("----------------------\n");
	printf("... 나의 충전금액 [%d]원 \n", memberBook[userIndex].pay);
	while (memberBook[userIndex].pay - change < 0) {
		printf("... 보유 금액이 부족합니다. 금액 충전 페이지로 이동합니다.\n");
		memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
	}
	memberBook[userIndex].pay -= change;
	videoBook[videoIndex].rentalLimit = VideoRentalLimitMaker(rentalDay);
	videoBook[videoIndex].rentalDate = VideoDateMaker();
	strcpy(videoBook[videoIndex].isRentaled, "X");

	printf("... [%d]원 결제\n", change);
	printf("... 나의 잔액 [%d]원 \n", memberBook[userIndex].pay);
	printf("... 비디오 대여 성공 ! 연체시 연체료가 부가됩니다. \n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)",  "대여일", "반납예정일");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[videoIndex].name, videoBook[videoIndex].maker, videoBook[videoIndex].id, videoBook[videoIndex].upDate, videoBook[videoIndex].price, videoBook[videoIndex].age, videoBook[videoIndex].isRentaled, videoBook[videoIndex].memberId, videoBook[videoIndex].rentalDate, videoBook[videoIndex].rentalLimit);
	printf("---------------------------------------------------------------------------------------------------------\n");

	printf("... 메뉴로 돌아갑니다.\n");

	return videoBook;

}



