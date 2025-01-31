#include "menu.h"
#include "PrintVideo.h"
#include "CheckRightValue.h"
#include "GetDate.h"
#include "ManagerSubFunction.h"
#include "SortStruct.h"
#include "ScreenClear.h"
#include "SortStruct.h"


struct video * PirntVideoBook_forManager(struct video* videoBook, int* videoCount, struct member* memberBook, int* memberCount) {
	int key = 0;
	while (key != 5) {
		printf("==== 02-03. 비디오 목록 출력 및 수정/삭제 ==== \n");
		videoBook = SortVideoBook(videoBook, * videoCount);


		printf("01. 전체 비디오 출력\n02. 대여 가능한 비디오 출력\n03. 대여된 비디오 출력\n04. 연체된 비디오 출력\n05. 비디오 출력 종료\n");
		key = RightMenuKey(5);
		if (key == 1) {
			printf("==== 01. 전체 비디오 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", i + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (*videoCount == 0) {
				printf("... 비디오가 없습니다. \n");
				ScreenClear();
				return videoBook;
			}
			else {
				printf("... 총 %d 항목 출력\n", *videoCount);
				printf("... 다음 작업?\n");
				printf("... 01. 비디오 삭제\n... 02. 비디오 수정\n... 03. 비디오 출력 종료\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. 비디오 삭제\n");
					int videoIndex = 0;
					if (*videoCount != 1) {
						printf("... 삭제할 비디오의 번호?\n");
						videoIndex = RightMenuKey(*videoCount) - 1;
					}
					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. 비디오 수정\n");
					int videoIndex = 0;
					if (*videoCount != 1) {
						printf("... 수정할 비디오의 번호?\n");
						videoIndex = RightMenuKey(*videoCount) - 1;
					}
					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					ScreenClear();
				}
				else {
					printf("03. 비디오 출력 종료\n");
					return videoBook;
				}
			}
		}

		else if (key == 2) {
			int count = 0;
			printf("==== 02. 대여 가능한 비디오 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "O") == 0) {
					count++;
					printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... 대여 가능한 비디오가 없습니다. \n");
				ScreenClear();
				return videoBook;

			}
			else {
				printf("... 총 %d 항목 출력\n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 비디오 삭제\n... 02. 비디오 수정\n... 03. 비디오 출력 종료\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. 비디오 삭제\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "O") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... 삭제할 비디오의 번호?\n");
						videoIndex = printIndex[RightMenuKey(*videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}
					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. 비디오 수정\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "O") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... 수정할 비디오의 번호?\n");
						videoIndex = printIndex[RightMenuKey(*videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}

					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("03. 비디오 출력 종료\n");
					return videoBook;
				}
			}
		}
		else if (key == 3) {
			int count = 0;
			printf("==== 03. 대여된 비디오 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "X") == 0) {
					count++;
					printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);

				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... 대여된 비디오가 없습니다. \n");
				ScreenClear();
				return videoBook;
			}
			else {
				printf("... 총 %d 항목 출력\n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 비디오 삭제\n... 02. 비디오 수정\n... 03. 비디오 출력 종료\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. 비디오 삭제\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "X") == 0) {
							printIndex[index] = i;
							index++;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... 삭제할 비디오의 번호?\n");
						videoIndex = printIndex[RightMenuKey( count ) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}

					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. 비디오 수정\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "X") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... 수정할 비디오의 번호?\n");
						videoIndex = printIndex[RightMenuKey(*videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}
					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("03. 비디오 출력 종료\n");
					return videoBook;
				}
			}
		}
		else if (key == 4) {
			int count = 0;
			int today = VideoDateMaker();
			printf("==== 04. 연체된 비디오 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부", "대여자(ID)", "대여일", "반납예정일");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "X") == 0) {
					if (videoBook[i].rentalLimit - today < 0) {
						count++;
						printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
					}
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... 연체된 비디오가 없습니다. \n");
				ScreenClear();
				return videoBook;
			}
			else {
				printf("... 총 %d 항목 출력\n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 비디오 삭제\n... 02. 비디오 수정\n... 03. 비디오 출력 종료\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. 비디오 삭제\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (videoBook[i].rentalLimit != 0) {
							if ((strcmp(videoBook[i].isRentaled, "X") == 0) && videoBook[i].rentalLimit - today < 0) {
								printIndex[index] = i;
								index++;
							}
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... 삭제할 비디오의 번호?\n");
						videoIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						videoIndex = printIndex[ 0 ];
					}
					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. 비디오 수정\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if ((strcmp(videoBook[i].isRentaled, "X") == 0) && videoBook[i].rentalLimit - today < 0) {
							if (videoBook[i].rentalLimit != 0) {
								printIndex[index] = i;
								index++;
							}
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... 수정할 비디오의 번호?\n");
						videoIndex = printIndex[ RightMenuKey(count) - 1 ];
					}
					else {
						videoIndex = printIndex[0];
					}

					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);

					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("03. 비디오 출력 종료\n");
					return videoBook;
				}
			}
		}
		else {
			printf("==== 05. 비디오 출력 종료 ====\n");
			return videoBook;
		}

	}
}
	



struct video * PirntVideoBook_forMember(struct video * videoBook, int videoCount, struct member * memberBook, int memberCount, int userIndex ) {

	int key = 0;
	while (key != 4) {

		printf("==== 03. 비디오 출력 및 대여 ==== \n");

		printf("01. 전체 비디오 출력\n02. 대여 가능한 비디오 출력\n03. 최신 비디오 출력\n04. 비디오 출력 종료\n");
		key = RightMenuKey(4);
		if (key == 1) {
			printf("==== 01. 전체 비디오 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < videoCount; i++) {
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", i + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (videoCount == 0) {
				printf("...  비디오가 없습니다. \n");
				printf("...  메뉴로 돌아갑니다. \n");
				return videoBook;
			}
			else {
				printf("... 총 %d 항목 출력\n", videoCount);
				printf("... 다음 작업?\n");
				printf("... 01. 비디오 대여\n... 02. 비디오 출력 종료\n");
				int key2 = 0;
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					printf("01. 비디오 대여\n");
					int videoIndex = 0;
					if (videoCount != 1) {
						printf("... 대여할 비디오의 번호?\n");
						videoIndex = RightMenuKey(videoCount) - 1;
					}
					videoBook = RentVideo_forMember(memberBook, &memberCount, videoBook, &videoCount, videoIndex, userIndex);
					ScreenClear();
				}
				else {
					printf("02. 비디오 출력 종료\n");
					return videoBook;
				}
			}
		}
		else if (key == 2) {
			int count = 0;
			printf("==== 02. 대여 가능한 비디오 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "O") == 0) {
					printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", count + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled);
					count++;
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... 대여 가능한 비디오가 없습니다. \n");
				printf("...  메뉴로 돌아갑니다. \n");
				return videoBook;
			}
			else {
				printf("... 총 %d 항목 출력\n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 비디오 대여\n... 02. 비디오 출력 종료\n");
				int key2 = 0;
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					printf("02. 비디오 대여\n");
					int index = 0;

					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "O") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... 대여할 비디오의 번호?\n");
						videoIndex =  printIndex[RightMenuKey(videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}
					videoBook = RentVideo_forMember(memberBook, &memberCount, videoBook, &videoCount, videoIndex, userIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("02. 비디오 출력 종료\n");
					return videoBook;
				}
			}
		}
		else if (key == 3) {
			int count = 0;
			printf("==== 03. 최신 비디오 출력 ====\n");
			videoBook = SortVideoBook_byDate(videoBook, videoCount);
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "번호", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령", "대여가능여부");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < videoCount; i++) {
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", i + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (videoCount == 0) {
				printf("...  비디오가 없습니다. \n");
				printf("...  메뉴로 돌아갑니다. \n");
				videoBook = SortVideoBook(videoBook, videoCount);
				return videoBook;
			}
			else {
				printf("... 총 %d 항목 출력\n", videoCount);
				printf("... 다음 작업?\n");
				printf("... 01. 비디오 대여\n... 02. 비디오 출력 종료\n");
				int key2 = 0;
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					printf("01. 비디오 대여\n");
					int videoIndex = 0;
					if (videoCount != 1) {
						printf("... 대여할 비디오의 번호?\n");
						videoIndex = RightMenuKey(videoCount) - 1;
					}
					videoBook = RentVideo_forMember(memberBook, &memberCount, videoBook, &videoCount, videoIndex, userIndex);
					ScreenClear();
				}
				else {
					printf("02. 비디오 출력 종료\n");
					videoBook = SortVideoBook(videoBook, videoCount);
					return videoBook;
				}
			}
		}
		else {
			printf("04. 비디오 출력 종료\n");
			return videoBook;
		}

	}
}
