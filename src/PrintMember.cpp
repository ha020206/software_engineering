#include "menu.h"
#include "PrintMember.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "ManagerSubFunction.h"
#include "GetDate.h"
#include "SortStruct.h"
#include "ScreenClear.h"


struct member* PirntMemberBook_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int* sepcialKey, char* loginId) {
	int key = 0;
	while (key != 6) {
		printf("==== 01-03. 회원 목록 출력 및 수정/삭제==== \n");
		memberBook = SortMemberBook(memberBook, * memberCount);
		printf("01. 전체 회원 출력\n02. 대여 회원 출력\n03. 연체 회원 출력\n04. 일반 회원 출력\n05. 관리자 회원 출력\n06. 출력 종료\n");
		int key = RightMenuKey(6);
		if (key == 1) {
			printf("==== 01. 전체 회원 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이" , "아이디", "비밀번호", "회원 구분", "충전 금액");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", i + 1, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id , memberBook[i].passWord,  memberBook[i].manager, memberBook[i].pay);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");

			if (*memberCount == 0) {
				printf("... 회원이 없습니다. \n");
				printf("... 메뉴로 돌아갑니다 \n");
				return memberBook;
			}
			else {
				printf("... 총 %d 개의 목록 검색 \n", *memberCount);
				printf("... 다음 작업?\n");
				printf("... 01. 회원 삭제\n... 02. 회원 정보 수정\n... 03. 회원 출력 종료\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. 회원 삭제 ==\n");
					int memberIndex = 0;  
					if (*memberCount != 1) {
						printf("... 삭제할 회원의 번호?\n");
						memberIndex = RightMenuKey(*memberCount) - 1;
					}
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					if (* sepcialKey == -1) {
						return memberBook;
					}
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("== 02. 회원 정보 수정 ==\n");
					int memberIndex = 0;
					if (*memberCount != 1) {
						printf("... 수정할 회원의 번호?\n");
						memberIndex = RightMenuKey(*memberCount) - 1;
					}
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					if (* sepcialKey == -1) {
						return memberBook;
					}
					ScreenClear();
				}
				else {
					printf("== 03. 회원 출력 종료 ==\n");
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}
			}
		}
		else if (key == 2) {
			int count = 0;
			printf("==== 02. 대여 회원 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				int find = 0;
				for (int j = 0; j < *videoCount; j++) {
					if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
						find++;
						if (find == 1) {
							printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
						}
						printf("%14s [%s][%s] 반납 예정일 : [%d]\n", " ", videoBook[j].name, videoBook[j].id, videoBook[j].rentalLimit);

					}
				}
			}

			printf("---------------------------------------------------------------------------------------------------------\n");

			if (count == 0) {
				printf("... 대여한 회원이 없습니다. \n");
				printf("... 출력을 종료합니다. \n");
				return memberBook;
			}
			else {
				printf("... 총 %d 개의 목록 검색 \n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 회원 삭제\n... 02. 회원 정보 수정\n... 03. 회원 출력 종료\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. 회원 삭제 ==\n");
					int memberIndex = 0;
					int index = 0;
					int find = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								find++;
								if (find == 1) {
									printIndex[index] = i;
									index++;
								}

							}
						}
					}
					if (count != 1) {
						printf("... 삭제할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (* sepcialKey == -1) {
						return memberBook;
					}
					
				}
				else if (key2 == 2) {
					printf("== 02. 회원 정보 수정 ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								find++;
								if (find == 1) {
									printIndex[index] = i;
									index++;
								}
							}
						}
					}
					if (count != 1) {
						printf("... 수정할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (* sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. 회원 출력 종료 ==\n");
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}

			}
		}
		else if (key == 3) {
			int count = 0;
			printf("==== 03. 연체 회원 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				int find = 0;
				for (int j = 0; j < *videoCount; j++) {
					if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
						if ( strcmp(videoBook[j].isRentaled, "X") == 0 && videoBook[j].rentalLimit - VideoDateMaker() < 0) {
							find++;
							if (find == 1) {
								printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
							}
							printf("%14s [%s][%s] 연체일수 : [%d]\n", " ", videoBook[j].name, videoBook[j].id, VideoOverDayMaker( videoBook[j].rentalLimit ) );

						}
					}
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");

			if (count == 0) {
				printf("... 연체한 회원이 없습니다. \n");
				printf("... 출력을 종료합니다. \n");
				return memberBook;
			}
			else {
				printf("... 총 %d 개의 목록 검색 \n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 회원 삭제\n... 02. 회원 정보 수정\n... 03. 회원 출력 종료\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. 회원 삭제 ==\n");
					int memberIndex = 0;
					int index = 0;
					int find = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);

					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								if (strcmp(videoBook[j].isRentaled, "X") == 0 && videoBook[j].rentalLimit - VideoDateMaker() < 0) {
									find++;
									if (find == 1) {
										printIndex[index ++ ] = i;
									}

								}
							}
						}
					}
					if (count != 1) {
						printf("... 삭제할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}

				else if (key2 == 2) {
					printf("== 02. 회원 정보 수정 ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								if (strcmp(videoBook[j].isRentaled, "X") == 0 && videoBook[j].rentalLimit - VideoDateMaker() < 0) {
									find++;
									if (find == 1) {
										printIndex[index ++] = i;
									}

								}
							}
						}
					}
					if (count != 1) {
						printf("... 수정할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. 회원 출력 종료 ==\n");
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}


			}

		}
		else if (key == 4) {
			int count = 0;
			printf("==== 04. 일반 회원 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				if (strcmp(memberBook[i].manager, "일반회원") == 0) {
					printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");

			if (count == 0) {
				printf("... 회원이 없습니다. \n");
				printf("... 출력을 종료합니다. \n");
				return memberBook;
			}
			else {
				printf("... 총 %d 개의 목록 검색 \n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 회원 삭제\n... 02. 회원 정보 수정\n... 03. 회원 출력 종료\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. 회원 삭제 ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "일반회원") == 0) {
							printIndex[index++] = i;
						}
					}

					if (count != 1) {
						printf("... 삭제할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
				
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else if (key2 == 2) {
					printf("== 02. 회원 정보 수정 ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "일반회원") == 0) {
							printIndex[index++] = i;
						}
					}
					if (count != 1) {
						printf("... 수정할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. 회원 출력 종료 ==\n");
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}

			}
		}
		else if (key == 5) {
			int count = 0;
			printf("==== 05. 관리자 회원 출력 ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "번호", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "회원 구분", "충전 금액");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				if (strcmp(memberBook[i].manager, "관리자") == 0) {
					printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... 회원이 없습니다. \n");
				printf("... 출력을 종료합니다. \n");
				return memberBook;
			}
			else {
				printf("... 총 %d 개의 목록 검색 \n", count);
				printf("... 다음 작업?\n");
				printf("... 01. 회원 삭제\n... 02. 회원 정보 수정\n... 03. 회원 출력 종료\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. 회원 삭제 ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "관리자") == 0) {
							printIndex[index++] = i;
						}
					}

					if (count != 1) {
						printf("... 삭제할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else if (key2 == 2) {
					printf("== 01. 회원 정보 수정 ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "관리자") == 0) {
							printIndex[index++] = i;
						}
					}
					if (count != 1) {
						printf("... 수정할 회원의 번호?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. 회원 출력 종료 ==\n");
					printf("... 메뉴로 돌아갑니다 \n");
					return memberBook;
				}

			}
		}
		else {
			printf("== 06. 회원 출력 종료 ==\n");
			printf("... 메뉴로 돌아갑니다 \n");
			return memberBook;
		}


	}
}
