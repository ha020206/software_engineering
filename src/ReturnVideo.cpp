#include "ReturnVideo.h"
#include "menu.h"
#include "CheckRightValue.h"
#include "GetDate.h"
#include "InsertCoin.h"
#include "ScreenClear.h"

struct video * ReturnVideo_forMember(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, char * loginId, int userIndex) {

	int key = 0;
	while (key != 3) {
		printf("==== 04. 비디오 반납 ==== \n");
		printf("... 대여한 비디오 목록을 출력합니다.\n");
		int count = 0;
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여자ID", "반납예정일");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < videoCount; i++) {
			if (strcmp(videoBook[i].memberId, loginId) == 0) {
				count++;
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].memberId, videoBook[i].rentalLimit);
			}
		}
		printf("---------------------------------------------------------------------------------------------------------\n");

		if (count == 0) {
			printf("... 대여한 비디오가 없습니다.\n");
			printf("... 메뉴로 돌아갑니다.\n");
			return videoBook;
		}

		printf("... 총 %d 개의 항목 출력\n", count);
		printf("... 다음 작업?\n");
		printf("01. 비디오 대여 연장\n02. 비디오 반납\n03. 비디오 반납 종료\n");
		int key2 = RightMenuKey(3);
		int listIndex = 0;
		if (key2 == 1) {
			printf("== 01. 비디오 대여 연장 == \n");
			int* returnIndex = (int*)malloc(sizeof(int) * count);
			int index = 0;
			for (int i = 0; i < videoCount; i++) {
				if (strcmp(videoBook[i].memberId, loginId) == 0) {
					returnIndex[index++] = i;
				}
			}

			if (count != 1) {

				printf("... 대여를 연장할 항목의 번호를 선택하세요.\n");
				listIndex = returnIndex[ RightMenuKey(count) - 1 ];

				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여자ID", "반납예정일");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[listIndex].name, videoBook[listIndex].maker, videoBook[listIndex].id, videoBook[listIndex].upDate, videoBook[listIndex].price, videoBook[listIndex].age, videoBook[listIndex].memberId, videoBook[listIndex].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");
			}
			else {
				listIndex = returnIndex[0];
			}


			if (videoBook[listIndex].rentalLimit - VideoDateMaker() < 0) {
				int overDay = 0;
				printf("... 연체된 일수 [ %d ]에 대한 연체료가 있습니다.\n", overDay = VideoOverDayMaker(videoBook[listIndex].rentalLimit));
				int change = overDay * videoBook[listIndex].price;
				printf("... [ 나의 충전금액 :%d 원]\n", memberBook[userIndex].pay);
				printf("------- 영수증 -------\n");
				printf("... 하루 대여료 [%d]원\n", videoBook[listIndex].price);
				printf("... 총 [ %d ] 일 연체 \n", overDay);
				printf("... 결제 예정 금액 [%d]원\n", change);
				printf("----------------------\n");
				while (memberBook[userIndex].pay - change < 0) {
					printf("... 보유 금액이 부족합니다. 회원 금액 충전 페이지로 이동합니다.\n");
					memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
				}
				memberBook[userIndex].pay -= change;
				printf("... 결제 완료! [ 나의 잔액 :%d 원]\n", memberBook[userIndex].pay);
				videoBook[listIndex].rentalLimit = VideoRentalLimitMaker(0);
			}

			printf("... 연장할 대여 일수 ? ( 대여는 1일 ~ 14일 까지 가능합니다. ) [ 현재 반납 예정일 : %d ]\n", videoBook[listIndex].rentalLimit);
			int rentalDay = RightMenuKey(14);

			int change = rentalDay * videoBook[listIndex].price;
			printf("... [ 나의 충전금액 :%d 원]\n", memberBook[userIndex].pay);
			printf("------- 영수증 -------\n");
			printf("... 하루 대여료 [%d]원\n", videoBook[listIndex].price);
			printf("... 총 [ %d ] 일 대여 연장 \n", rentalDay);
			printf("... 결제 예정 금액 [%d]원\n", change);
			printf("----------------------\n");

			while (memberBook[userIndex].pay - change < 0) {
				printf("... 회원의 보유 금액이 부족합니다. 회원 금액 충전 페이지로 이동합니다.\n");
				memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
			}

			memberBook[userIndex].pay -= change;
			printf("... 결제 완료! [ 회원의 잔액 :%d 원]\n", memberBook[userIndex].pay);

			videoBook[listIndex].rentalLimit = VideoOverRentDayMaker(videoBook[listIndex].rentalLimit, rentalDay);

			printf("... 연장 완료 !\n");

			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여자ID", "반납예정일");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[listIndex].name, videoBook[listIndex].maker, videoBook[listIndex].id, videoBook[listIndex].upDate, videoBook[listIndex].price, videoBook[listIndex].age, videoBook[listIndex].memberId, videoBook[listIndex].rentalLimit);
			printf("---------------------------------------------------------------------------------------------------------\n");
			
			free(returnIndex);
			returnIndex = NULL;
			ScreenClear();


		}
		else if (key2 == 2) {
			printf("== 02. 비디오 반납 == \n");
			int * returnIndex = (int*)malloc(sizeof(int) * count);
			int index = 0;
			for (int i = 0; i < videoCount; i++) {
				if (strcmp(videoBook[i].memberId, loginId) == 0) {
					returnIndex[index++] = i;
				}
			}

			if (count != 1) {

				printf("... 반납할 항목의 번호를 선택하세요.\n");
				listIndex  = RightMenuKey(count) - 1;

				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여자ID", "반납예정일");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[returnIndex[listIndex]].name, videoBook[returnIndex[listIndex]].maker, videoBook[returnIndex[listIndex]].id, videoBook[returnIndex[listIndex]].upDate, videoBook[returnIndex[listIndex]].price, videoBook[returnIndex[listIndex]].age, videoBook[returnIndex[listIndex]].memberId, videoBook[returnIndex[listIndex]].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");
			}

			printf("... 반납을 진행합니다.\n");
			if ( (videoBook[returnIndex[listIndex]].rentalLimit - VideoDateMaker() ) < 0 ) {
				int overDay = VideoOverDayMaker(videoBook[returnIndex[listIndex]].rentalLimit) ;
				int overPrice = videoBook[returnIndex[listIndex]].price * overDay;
				printf("... 반납 기한이 지났습니다.\n");
				printf("... 연체료가 부과됩니다.\n");
				printf("... [ 나의 충전금액 :%d 원]\n", memberBook[userIndex].pay);
				printf("------- 영수증 -------\n");
				printf("... 하루 대여료 [%d]원\n", videoBook[returnIndex[listIndex]].price);
				printf("... 총 [ %d ] 일 초과 대여\n", overDay);
				printf("... 결제 예정 금액 [%d]원\n", overPrice);
				printf("----------------------\n");

				while (memberBook[userIndex].pay - overPrice < 0) {
					printf("... 보유 금액이 부족합니다. 금액 충전 페이지로 이동합니다.\n");
					memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);

				}
				memberBook[userIndex].pay -= overPrice;
				printf("... [%d]원 결제\n", overPrice);
				printf("... 나의 잔액 [%d]원 \n", memberBook[userIndex].pay);

			}
			
			videoBook[returnIndex[listIndex]].rentalLimit = 0;
			videoBook[returnIndex[listIndex]].rentalDate = 0;
			strcpy(videoBook[returnIndex[listIndex]].isRentaled, "O");
			strcpy(videoBook[returnIndex[listIndex]].memberId, "-");
			printf("... 반납 완료 !\n");


			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여자ID", "반납예정일");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[returnIndex[listIndex]].name, videoBook[returnIndex[listIndex]].maker, videoBook[returnIndex[listIndex]].id, videoBook[returnIndex[listIndex]].upDate, videoBook[returnIndex[listIndex]].price, videoBook[returnIndex[listIndex]].age, videoBook[returnIndex[listIndex]].memberId, videoBook[returnIndex[listIndex]].rentalLimit);
			printf("---------------------------------------------------------------------------------------------------------\n");
			
			free(returnIndex);
			returnIndex = NULL;
			ScreenClear();
		}
		else {
			printf("... 메뉴로 돌아갑니다.\n");
			return videoBook;
		
		}
	}
}