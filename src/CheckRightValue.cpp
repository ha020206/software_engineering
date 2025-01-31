#include "menu.h"
#include "GetDate.h"
#include "CheckRightValue.h"

// 메뉴 키 예외처리
int RightMenuKey(int size) {
	while (1) {
		int key = 0;
		char word = 0;
		scanf("%d", &key);
		do {
			word = getchar();
		} while (word != '\n');
		for (int i = 1; i <= size; i++) {
			if (i == key) {
				return i;
			}
		}
		printf("... 메뉴에 맞는 숫자를 다시 입력하세요.\n");
	}
}
// 문자열 크기 예외처리 
char* RightStringSize(char * buffer, int size) {
	while (1) {
		char word = 0;
		char string[40] = { 0 };
		scanf("%[^\n]s", string );
		do {
			word = getchar();
		} while (word != '\n');
		if (strstr(string, " ")) {
			printf("... 공백은 입력할 수 없습니다.\n");

		}else if ( strlen(string) < size ) {
			strcpy(buffer, string);
			return buffer;
		}
		printf("... 정확한 값을 다시 입력하세요.\n");
	}
}
// 사람 이름 예외처리 
char* RightMemberName(char* buffer) {
	while (1) {
		int korCount = 0;
		int engCount = 0;
		strcpy(buffer, RightStringSize(buffer, 40)); // 크기 확인
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		else {
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // 한글은 입력 받을 수 있음
					korCount++;
				}
				else if (isalpha(buffer[i])) { // 영어는 입력 받을 수 있음
					engCount++;
				}
			}
			if ((engCount == strlen(buffer)) || (korCount == strlen(buffer))) {

				return buffer;
			}
			printf("...  숫자와 특수기호는 입력할 수 없습니다.\n");
		}
	}
}
// 전화번호 예외처리
char* RightMemberNum(char* buffer){
	while (1) { 
		strcpy(buffer, RightStringSize(buffer, 12)); // 크기 확인
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		else {
			int count = 0;
			int again = 0;
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // 한글은 입력 받을 수 있음
					again = 1;
				}
			}
			if (again != 1) {
				for (int i = 0; buffer[i] != '\0'; i++) {
					if (isdigit(buffer[i])) {
						count++;
					}
				}
				if (count == strlen(buffer)) {
					return buffer;
				}
			}
			printf("... 숫자 이외의 값은 입력할 수 없습니다.\n");
		}
	}
}
// 주민등록번호 예외처리 
char* RightMemberIdent(char* buffer) {
	while (1) {
		int again = 0;
		RightStringSize(buffer, 15); // 크기 확인
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		else if ( buffer[6] != '-') {
			printf("... 언더바 오류 ! 주민등록번호의 형태로 입력하세요.\n");
		}
		else{
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // 한글은 입력 받을 수 있음
					again = 1;
				}
			}
			if (again != 1) {
				int count = 0;
				for (int i = 0; i < 14; i++) {
					if (isdigit(buffer[i])) {
						count++;
					}
				}
				if (count == 13) {
					if (buffer[7] == '3' || buffer[7] == '4') {
						char now[7] = { 0 };
						sprintf(now, "%d", VideoDateMaker() - 20000000);
						if (strcmp("000101", buffer) <= 0 && strcmp(buffer, now) <= 0) {
							return buffer;
						}
					}
					else if (buffer[7] == '1' || buffer[7] == '2') {
						return buffer;
					}
					printf("... 성별코드 오류! 주민등록번호의 형태로 입력하세요.\n");
				}
			}
			else {
				printf("... 주민등록번호의 형태로 입력하세요.\n");
			}
		}
	}
}

// id 예외처리 
char* RightMemberId(char* buffer) {
	while (1) {
		strcpy(buffer, RightStringSize(buffer, 16));
		int i = 0;
		int alphaCount = 0;
		int numCount = 0;
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		int again = 0;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (buffer[i] & 0x80) { // 한글은 입력 받을 수 없음
				again = 1;
			}
		}
		if (again != 1){
			for (i = 0; buffer[i] != '\0'; i++) {
				if (isdigit(buffer[i])) {
					numCount++;
				}
				else if (isalpha(buffer[i])) {
					alphaCount++;
				}
			}
			if ((alphaCount + numCount) == strlen(buffer) && (alphaCount >= 1) && (numCount >= 1)) {
				return buffer;
			}
		}
		printf("... 아이디는 영어와 숫자의 혼합으로만 입력하세요. \n");

	}
}
// 비밀번호 예외처리 
char* RightMemberPassWord(char* buffer) {
	while (1) {
		strcpy(buffer, RightStringSize(buffer, 16));
		int i = 0;
		int alphaCount = 0;
		int numCount = 0;
		int uniCount = 0;
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		else {
			int again = 0;
			for (i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // 한글은 입력 받을 수 없음
					again = 1;
				}
			}
			if ( again != 1 ) {
				for (i = 0; buffer[i] != '\0'; i++) {
					if (isdigit(buffer[i])) {
						numCount++;
					}
					else if (isalpha(buffer[i])) {
						alphaCount++;
					}
					else {
						uniCount++;
					}
				}
				
				if (((alphaCount + numCount + uniCount) == strlen(buffer)) && (alphaCount >= 1) && (numCount >= 1) && (uniCount >= 1)) {
					return buffer;
				}
			}
		}
		printf("... 비밀번호는 영어, 숫자, 특수기호의 혼합으로 입력하세요.\n");

	}
}
// 영화 제목 예외처리
char* RightVideoName(char* buffer) {
	int again = 0;
	do {
		again = 0;
		strcpy(buffer, RightStringSize(buffer , 40));
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
			again = 1;
		}
	} while (again != 0);
	return buffer;
}
// 영화 감독 예외처리
char* RightVideoMaker(char* buffer) {
	while(1){
		int korCount = 0;
		int engCount = 0;
		strcpy(buffer, RightStringSize(buffer, 40));

		if (strstr(buffer, " ") || strlen(buffer ) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		else {
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // 한글은 입력 받을 수 있음
					korCount++;
				}
				else if (isalpha(buffer[i] )) { // 영어는 입력 받을 수 있음
					engCount++;
				}
			}
			if ((engCount == strlen(buffer)) || (korCount == strlen(buffer)) ) {
				return buffer;
			}
			else {
				printf("... 감독의 이름은 한글 또는 영어로만 입력할 수 있습니다. \n");
			}
		}
	} 
}
// 비디오 가격 예외처리
int RightVideoPrice( ) {
	while (1) {
		int again = 0;
		int price = 0;
		int i = 0;
		int numCount = 0;
		char bufferPrice[7] = { 0 };
		strcpy(bufferPrice, RightStringSize(bufferPrice, 7));
		if (strstr(bufferPrice, " ") || strlen(bufferPrice) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		else {
			for (int i = 0; bufferPrice[i] != '\0'; i++) {
				if (bufferPrice[i] & 0x80 || isalpha(bufferPrice[i]) ) { // 한글은 입력 받을 수 없음
					again = 1;
					break;
				}
				else if (isdigit(bufferPrice[i]) ) {
					numCount++;
				}
			}
			if (again != 1) {
				if ( strlen(bufferPrice) == numCount ) {
					price = atoi(bufferPrice);
					for (i = 0; i <= 999999; i++) {
						if (i == price) {
							return price;
						}
					}
				}
			}
		}
		printf("... 비디오 대여 가격은, 0에서 999999 까지의 정수만 입력 가능합니다. \n");
	}
}
// 연령가 예외처리 
int RightVideoAge( ) {
	int again = 0;
	int age = 0;
	while(1) {
		again = 0;
		age = 0;
		int i = 0;
		int numCount = 0;
		char bufferNum[4] = { 0 };
		strcpy(bufferNum, RightStringSize(bufferNum, 4));
		for (i = 0; bufferNum[i] != '\0'; i++) {
			if (bufferNum[i] & 0x80 || isalpha(bufferNum[i])) { // 한글은 입력 받을 수 없음
				again = 1;
				break;
			}
			else if (isdigit(bufferNum[i])) {
				numCount++;
			}
		}
		if (again != 1) {
			if (strlen(bufferNum) == 0) {
				return 0;
			}
			else if (strlen(bufferNum) == numCount) {
				age = atoi(bufferNum);
				for (i = 0; i <= 100; i++) {
					if (i == age) {
						return age;
					}
				}
			}
		}
		printf("... 비디오 관람 가능 연령대는, 0에서 100까지의 정수만 입력 가능합니다. \n");
	}
}
