#include "menu.h"
#include "GetDate.h"
#include "FileReadAndWrite.h"
#include "CheckInList.h"
#include "CheckRightValue.h"
#include "JoinMember.h"
#include "JoinVideo.h"
#include "LogIn.h"
#include "ManagerMember.h"
#include "ManagerVideo.h"
#include "PrintMember.h"
#include "PrintVideo.h"
#include "ScreenClear.h"
#include "InsertCoin.h"
#include "SortStruct.h"
#include "ReturnVideo.h"
// 202322371 하승연 소프트웨어공학 2차과제
// 작업 환경 : VisualStudio 2022
// ! 첫 회원가입 대상은 관리자로 지정됩니다. 비밀번호, 아이디 잃지 않도록 주의를 부탁드립니다. 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	printf("... 비디오 대여 프로그램을 시작합니다. \n");
	for (int i = 0; i < 3; i++) {
		printf("%c", '.');
		Sleep(800); // 0.2초씩 3번 점을 출력하여 화면이 바로 지워지는것을 방지함 
	}
	printf("\n");
	// 파일의 줄 수를 담을 변수 선언
	int memberCount = 0;
	int videoCount = 0;

	// 파일의 줄 수를 읽는 함수
	ReadFile( &memberCount, &videoCount); 
	
	// 동적 메모리 설정
	struct member * memberBook = (struct member *) malloc(sizeof(struct member) * memberCount);
	struct video * videoBook = (struct video*)malloc(sizeof(struct video) * videoCount);

	// 파일의 내용을 읽는 함수 
	WriteBook(memberBook, memberCount, videoBook, videoCount);
	
	memberBook = ReAge(memberBook, memberCount); // 나이 재설정 (년도 바뀌면,, )

	printf("\n... 계속 하려면 아무 키나 눌러주세요. \n");
	getchar();
	system("cls");
	
	
	int key = 0;
	do  {
		SortMemberBook(memberBook, memberCount); // 회원 목록을 이름순으로 정렬
		SortVideoBook(videoBook , videoCount); // 비디오 목록을 이름순으로 정렬

		printf(" ==== 비디오 대여 프로그램 ==== \n");
		printf("01. 로그인\n02. 회원가입\n03. 프로그램 종료\n");
		char loginId[16] = { 0 }; // 로그인 시 로그인 한 아이디를 담는 변수 
		int specialKey = 0; // 관리자 회원이 자신을 지웠을 때 , 자동 로그아웃 하게 하는 스페셜키 변수 
		key = RightMenuKey(3); 
		if (key == 1) {
			struct member user = { 0 };
			int userIndex = -1;
			int successLogin = 0; // 로그인이 성공했을 때 1로 변함 
			memberBook = LogIn(memberBook, &memberCount, videoBook, &videoCount, &userIndex, & successLogin, loginId); // 로그인 함수
			if (successLogin == 1) { // 로그인에 성공했을때 키가 1

				int key2 = 0; // 상위 메뉴
				int key3 = 0; //  하위 메뉴
				if (strcmp(memberBook[userIndex].manager, "관리자") == 0) {
					do {
						userIndex = GetIndex(memberBook, memberCount, loginId); // 관리자의 경우 sort 함수 때문에 인덱스 번호가 바뀔 수 있음, 아이디를 이용해 인덱스 번호를 다시 구함 
						printf(" [%s][%s] 님 \n\n", memberBook[userIndex].manager, memberBook[userIndex].name );
						printf("==== 관리자 모드 ====\n");
						printf("01. 회원 관리\n02. 비디오 관리\n03. 관리자 모드 종료\n");
						key2 = RightMenuKey(3);
						key3 = 0;
						if (key2 == 1) {
							do {
								printf("== 01. 회원 관리 ==\n");
								printf("01. 회원 추가\n02. 회원 검색 및 수정/삭제\n03. 회원 목록 출력 및 수정/삭제\n04. 회원 관리 종료\n");
								key3 = RightMenuKey(4);
								if (key3 == 1) {
									printf("==== 01-01. 회원 추가 ==== \n");
									int beforeCount = memberCount;
									memberBook = (struct member*)realloc(memberBook, sizeof(struct member) * (( memberCount) + 1));
									memberBook[beforeCount] = JoinMember(memberBook, & memberCount); // 회원가입과 동일 
									ScreenClear();

								}
								else if (key3 == 2) {

									printf("==== 01-02. 회원 검색 및 수정/삭제 ==== \n");
									memberBook = SortMemberBook(memberBook, memberCount); // 정렬 
									memberBook = SearchMemberBook_forManager(memberBook, & memberCount,  videoBook, videoCount, & specialKey , loginId);
									ScreenClear();
									if ( specialKey == -1) { // 관리자가 자기자신을 삭제하거나 관리자에서 일반 회원으로 수정하는 경우 -> 로그아웃 
										key2 = 3;
										key3 = 4;
										break;
									}
									
								}
								else if (key3 == 3) {

									// printf("==== 01-03. 회원 목록 출력 및 수정/삭제==== \n");
									memberBook = PirntMemberBook_forManager(memberBook, & memberCount, videoBook, & videoCount, & specialKey, loginId);
									ScreenClear();
									if (specialKey == -1) {
										key2 = 3;
										key3 = 4;
										break;
									}
									
								}
								else {
									printf("==== 01-04. 회원 관리 종료 ==== \n");
									ScreenClear();
									break; 
								}
							}while (key3 != 4);
						}
						else if (key2 == 2) {
							do {
								printf("==== 02. 비디오 관리 ====\n");
								printf("01. 비디오 추가\n02. 비디오 검색 및 수정/삭제\n03. 비디오 목록 출력 및 수정/삭제\n04. 비디오 관리 종료\n");
								key3 = RightMenuKey(4);
								if (key3 == 1) {

									printf("==== 02-01. 비디오 추가 ==== \n");
									int beforeCount = videoCount;
									videoBook = (struct video*)realloc(videoBook, sizeof(struct video) * ((videoCount) + 1));
									videoBook[beforeCount] = JoinVideo(videoBook, & videoCount);
									ScreenClear();
								}
								else if (key3 == 2) {
									printf("==== 02-02. 비디오 검색 및 수정/삭제 ==== \n");
									videoBook = SearchvideoBook_forManager(videoBook, & videoCount, memberBook, & memberCount);
									ScreenClear();
								}
								else if (key3 == 3) {

									// printf("==== 02-03. 비디오 목록 출력 및 수정/삭제 ==== \n");
									
									videoBook = PirntVideoBook_forManager(videoBook, & videoCount, memberBook, & memberCount);
									ScreenClear();
								}
								else {
									printf("==== 02-04. 비디오 관리 종료 ==== \n");
									ScreenClear();
									break;
								}
							} while (key3 != 4);
						}
						else if(key2 == 3){
							printf("==== 03. 관리자 모드 종료 ====\n");
							ScreenClear();
							break; 
						}

					} while (key2 != 3);
				} 
				else {
					do {
						userIndex = GetIndex(memberBook, memberCount, loginId);
						printf(" [%s][%s] 님 , 나의 현재 금액 : %-d \n\n", memberBook[userIndex].manager, memberBook[userIndex].name, memberBook[userIndex].pay);
						printf("==== 회원 모드 ==== \n");
						printf("01. 개인정보 관리\n02. 비디오 대여와 반납\n03. 금액 충전\n04. 로그아웃\n");
						key2 = RightMenuKey(4);
						if (key2 == 1) {
							do {
								printf("==== 01. 개인 정보 관리 ==== \n");
								printf("... 현재 정보를 출력합니다.\n");
								printf("---------------------------------------------------------------------------------------------------------\n");
								printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-20s %-5s \n", "이름", "전화번호", "주민등록번호", "나이", "아이디", "비밀번호", "현재금액", "회원 구분");
								printf("---------------------------------------------------------------------------------------------------------\n");
								printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-20d %-5s \n", memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].pay, memberBook[userIndex].manager);
								printf("---------------------------------------------------------------------------------------------------------\n");

								printf("... 다음 작업?\n");
								printf("01. 회원 탈퇴\n02. 회원 정보 수정\n03. 회원 정보 관리 종료\n");
								key3 = RightMenuKey(3);

								if (key3 == 1) {
									printf("==== 01 - 01. 회원 탈퇴 ==== \n");
									int i = 0;
									for (i = 0; i < videoCount; i++) {
										if (strcmp(memberBook[userIndex].id, videoBook[i].memberId) == 0) {
											printf(" ... 반납하지 않은 비디오가 있는 경우 탈퇴가 불가능합니다.\n");
											printf(" ... 메뉴로 돌아갑니다.\n");
											ScreenClear();
											break;
										}
									}
									if (i == videoCount) {
										memberBook = DelMemberBook(memberBook, userIndex, &memberCount);
										key3 = 3;
										key2 = 3;
										printf(" ... 초기 메뉴로 돌아갑니다.\n");
										ScreenClear();
										break;
									}

								}
								else if (key3 == 2) {
									// printf("==== 01 - 02. 회원 정보 수정 ==== \n");
									memberBook = ChangeMemberBook_forMember(memberBook, userIndex, &memberCount);
									ScreenClear();
								}
								else if (key3 == 3) {
									printf("==== 01 - 03. 회원 정보 관리 종료 ==== \n");
									ScreenClear();
									break;
								}
							} while (key3 != 3);
						}
						else if (key2 == 2) {
							do {
								printf("==== 02. 비디오 대여와 반납 ==== \n");
								printf("01. 비디오 둘러보기\n02. 비디오 검색 및 대여\n03. 비디오 출력 및 대여\n04. 비디오 반납\n05. 비디오 대여와 반납 종료\n");
								key3 = RightMenuKey(5);
								if (key3 == 1) {
									int uniVideoCount = 0;
									printf("==== 01. 비디오 둘러보기 ==== \n"); // 비디오 목록 중에서 중복을 제외한 순수 비디오 종류만 출력 
									printf("... 우리 가게 소장 비디오 둘러보기\n");
									printf("---------------------------------------------------------------------------------------------------------\n");
									printf("%-3s %-20s %-10s \n", "번호", "비디오이름", "감독");
									printf("---------------------------------------------------------------------------------------------------------\n");
									for (int i = 0; i < videoCount; i++) {
										if (IsVideoNameMakerInList(videoBook, i, videoBook[i].name, videoBook[i].maker) == 0) {
											printf("%-3d %-20s %-10s \n", ++ uniVideoCount, videoBook[i].name, videoBook[i].maker);
										}
									}
									printf("---------------------------------------------------------------------------------------------------------\n");
									if (uniVideoCount == 0) {
										printf("... 가게에 소장한 비디오가 없습니다. \n");
									}
									else {
										printf("... 총 %d 종류 비디오 소장중\n", uniVideoCount);
									}
									ScreenClear();
								}
								else if (key3 == 2) {
									printf("==== 02. 비디오 검색 및 대여 ==== \n");
									videoBook = SearchvideoBook_forMember(videoBook, &videoCount, memberBook, &memberCount, userIndex);
									ScreenClear();
								}
								else if (key3 == 3) {
									// printf("==== 03. 비디오 출력 및 대여 ==== \n");
									videoBook = PirntVideoBook_forMember(videoBook, videoCount, memberBook, memberCount, userIndex);
									ScreenClear();
								}
								else if (key3 == 4) {
									// printf("==== 04. 비디오 반납 ==== \n");
									videoBook = ReturnVideo_forMember(memberBook, &memberCount, videoBook, videoCount, loginId, userIndex);
									ScreenClear();

								}
								else if (key3 == 5) {
									printf("==== 05. 비디오 대여와 반납 종료 ==== \n");
									ScreenClear();
									break;
								}
							} while (key3 != 4);

						}
						else if (key2 == 3) {
							printf("==== 03. 금액 충전 ==== \n");
							memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
						
							ScreenClear();

						}
						else if (key2 == 4) {
							printf("==== 04. 로그아웃 ==== \n");
							ScreenClear();
							break;
						}
					} while (key2 != 4);
				}
			}
		}
		else if (key == 2) {
			int beforeCount = memberCount;
			memberBook = (struct member *)realloc(memberBook, sizeof( struct member ) * ( memberCount + 1) );
			memberBook[beforeCount] = JoinMember(memberBook, & memberCount);
			ScreenClear();
		}
		else if (key == 3) {
			printf("\n... 비디오 대여 프로그램을 종료합니다. \n");
			WriteFile( memberBook, memberCount, videoBook , videoCount);
			printf("\n... 계속 하려면 아무 키나 눌러주세요. \n");
			getchar();

			free(memberBook);
			free(videoBook);
			return 0;
		}
	}while (key != 3);
}