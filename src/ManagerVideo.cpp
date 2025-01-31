#include "menu.h"
#include "ManagerVideo.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "GetDate.h"
#include "InsertCoin.h"
#include "ManagerSubFunction.h"
#include "SortStruct.h"

// 관리자 전용 비디오 삭제 및 수정
	struct video * SearchvideoBook_forManager(struct video * videoBook, int * videoCount, struct member * memberBook , int * memberCount ) {

		char searchKey[40] = { 0 };
		int index = 0; // 검색하는 항목을 관리하는 인덱스
		printf("... 검색 할 내용 ?\n");
		strcpy(searchKey, RightStringSize(searchKey, 40));
		videoBook = SortVideoBook(videoBook, * videoCount);
		for (int i = 0; i < *videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey) || strstr(videoBook[i].memberId, searchKey) ) {
				index++;
			}
		}

		if (index == 0) {
			printf("... 검색어와 일치하는 목록이 없습니다. \n");
			printf("... 메뉴로 돌아갑니다.\n");
			return videoBook;
		}

		printf("... 총 %d 개의 목록 검색 \n", index);
		int* searckIndex = (int*)malloc(sizeof(int) * index);
		index = 0;
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < *videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey))  {
				searckIndex[index++] = i;
				printf("%3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n",index, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
			}
		}
		printf("---------------------------------------------------------------------------------------------------------\n");

		int key = 0;
		int listIndex = index - 1;
		while (key != 3) {
			videoBook = SortVideoBook(videoBook, *videoCount);
			printf("... 다음 작업? \n");
			printf("01. 비디오 삭제\n02. 비디오 정보 수정\n03. 비디오 검색 및 수정/삭제 종료\n");
			key = RightMenuKey(3);

			if (key == 1) {
				if (index != 1) {
					printf("... 삭제를 원하는 목록의 번호?\n");
					listIndex = RightMenuKey(index) - 1;
				}

				videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex]);
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;
			}
			else if (key == 2) {
				if (index != 1) {
					printf("... 수정을 원하는 목록의 번호?\n");
					listIndex = RightMenuKey(index) - 1;
				}
				videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex]);
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;
				
			}
			else if (key == 3) {
				printf("03. 비디오 검색 및 수정/삭제 종료\n");
				free(searckIndex);
				searckIndex = NULL;
				printf("... 메뉴로 돌아갑니다.\n");
				return videoBook;
			}
		}
	}

	// 회원 전용 비디오 탐색 함수 
	struct video * SearchvideoBook_forMember(struct video* videoBook, int* videoCount, struct member* memberBook, int* memberCount, int userIndex ) {

		char searchKey[40] = { 0 };
		int count = 0;
		printf("... 검색 할 내용 ?\n");
		strcpy(searchKey, RightStringSize(searchKey, 40));

		for (int i = 0; i < *videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey)) {
				count++;
			}
		}
		if (count == 0) {
			printf("... 검색어와 일치하는 목록이 없습니다. \n");
			printf("... 메뉴로 돌아갑니다.\n");
			return videoBook;
		}
		int* searckIndex = (int*)malloc(sizeof(int) * count);
		printf("... 총 %d 개의 목록 검색 \n", count);
		count = 0;
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s  \n","번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < * videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey)) {
				searckIndex[count++] = i;
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s  \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled );
			}
		}
		printf("---------------------------------------------------------------------------------------------------------\n");
		int key = 0;
		while (key != 2) {
			printf("... 다음 작업? \n");
			printf("01. 비디오 대여\n02. 비디오 검색 및 대여 종료\n");
			key = RightMenuKey(2);

			if (key == 1) {
				printf("== 01. 비디오 대여 == \n");
				int listIndex = 0;
				if (count != 1) {
					printf("... 대여를 원하는 목록의 번호?\n");
					listIndex = RightMenuKey(count) - 1;
				}
				videoBook = RentVideo_forMember(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex], userIndex);
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;

			}
			else
			{
				printf("== 02. 비디오 검색 및 대여 종료 == \n");
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;

			}
		}
	}
