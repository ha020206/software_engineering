#include "menu.h"
#include "GetDate.h"
#include "CheckRightValue.h"

// �޴� Ű ����ó��
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
		printf("... �޴��� �´� ���ڸ� �ٽ� �Է��ϼ���.\n");
	}
}
// ���ڿ� ũ�� ����ó�� 
char* RightStringSize(char * buffer, int size) {
	while (1) {
		char word = 0;
		char string[40] = { 0 };
		scanf("%[^\n]s", string );
		do {
			word = getchar();
		} while (word != '\n');
		if (strstr(string, " ")) {
			printf("... ������ �Է��� �� �����ϴ�.\n");

		}else if ( strlen(string) < size ) {
			strcpy(buffer, string);
			return buffer;
		}
		printf("... ��Ȯ�� ���� �ٽ� �Է��ϼ���.\n");
	}
}
// ��� �̸� ����ó�� 
char* RightMemberName(char* buffer) {
	while (1) {
		int korCount = 0;
		int engCount = 0;
		strcpy(buffer, RightStringSize(buffer, 40)); // ũ�� Ȯ��
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		else {
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // �ѱ��� �Է� ���� �� ����
					korCount++;
				}
				else if (isalpha(buffer[i])) { // ����� �Է� ���� �� ����
					engCount++;
				}
			}
			if ((engCount == strlen(buffer)) || (korCount == strlen(buffer))) {

				return buffer;
			}
			printf("...  ���ڿ� Ư����ȣ�� �Է��� �� �����ϴ�.\n");
		}
	}
}
// ��ȭ��ȣ ����ó��
char* RightMemberNum(char* buffer){
	while (1) { 
		strcpy(buffer, RightStringSize(buffer, 12)); // ũ�� Ȯ��
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		else {
			int count = 0;
			int again = 0;
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // �ѱ��� �Է� ���� �� ����
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
			printf("... ���� �̿��� ���� �Է��� �� �����ϴ�.\n");
		}
	}
}
// �ֹε�Ϲ�ȣ ����ó�� 
char* RightMemberIdent(char* buffer) {
	while (1) {
		int again = 0;
		RightStringSize(buffer, 15); // ũ�� Ȯ��
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		else if ( buffer[6] != '-') {
			printf("... ����� ���� ! �ֹε�Ϲ�ȣ�� ���·� �Է��ϼ���.\n");
		}
		else{
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // �ѱ��� �Է� ���� �� ����
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
					printf("... �����ڵ� ����! �ֹε�Ϲ�ȣ�� ���·� �Է��ϼ���.\n");
				}
			}
			else {
				printf("... �ֹε�Ϲ�ȣ�� ���·� �Է��ϼ���.\n");
			}
		}
	}
}

// id ����ó�� 
char* RightMemberId(char* buffer) {
	while (1) {
		strcpy(buffer, RightStringSize(buffer, 16));
		int i = 0;
		int alphaCount = 0;
		int numCount = 0;
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		int again = 0;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (buffer[i] & 0x80) { // �ѱ��� �Է� ���� �� ����
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
		printf("... ���̵�� ����� ������ ȥ�����θ� �Է��ϼ���. \n");

	}
}
// ��й�ȣ ����ó�� 
char* RightMemberPassWord(char* buffer) {
	while (1) {
		strcpy(buffer, RightStringSize(buffer, 16));
		int i = 0;
		int alphaCount = 0;
		int numCount = 0;
		int uniCount = 0;
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		else {
			int again = 0;
			for (i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // �ѱ��� �Է� ���� �� ����
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
		printf("... ��й�ȣ�� ����, ����, Ư����ȣ�� ȥ������ �Է��ϼ���.\n");

	}
}
// ��ȭ ���� ����ó��
char* RightVideoName(char* buffer) {
	int again = 0;
	do {
		again = 0;
		strcpy(buffer, RightStringSize(buffer , 40));
		if (strstr(buffer, " ") || strlen(buffer) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
			again = 1;
		}
	} while (again != 0);
	return buffer;
}
// ��ȭ ���� ����ó��
char* RightVideoMaker(char* buffer) {
	while(1){
		int korCount = 0;
		int engCount = 0;
		strcpy(buffer, RightStringSize(buffer, 40));

		if (strstr(buffer, " ") || strlen(buffer ) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		else {
			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] & 0x80) { // �ѱ��� �Է� ���� �� ����
					korCount++;
				}
				else if (isalpha(buffer[i] )) { // ����� �Է� ���� �� ����
					engCount++;
				}
			}
			if ((engCount == strlen(buffer)) || (korCount == strlen(buffer)) ) {
				return buffer;
			}
			else {
				printf("... ������ �̸��� �ѱ� �Ǵ� ����θ� �Է��� �� �ֽ��ϴ�. \n");
			}
		}
	} 
}
// ���� ���� ����ó��
int RightVideoPrice( ) {
	while (1) {
		int again = 0;
		int price = 0;
		int i = 0;
		int numCount = 0;
		char bufferPrice[7] = { 0 };
		strcpy(bufferPrice, RightStringSize(bufferPrice, 7));
		if (strstr(bufferPrice, " ") || strlen(bufferPrice) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		else {
			for (int i = 0; bufferPrice[i] != '\0'; i++) {
				if (bufferPrice[i] & 0x80 || isalpha(bufferPrice[i]) ) { // �ѱ��� �Է� ���� �� ����
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
		printf("... ���� �뿩 ������, 0���� 999999 ������ ������ �Է� �����մϴ�. \n");
	}
}
// ���ɰ� ����ó�� 
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
			if (bufferNum[i] & 0x80 || isalpha(bufferNum[i])) { // �ѱ��� �Է� ���� �� ����
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
		printf("... ���� ���� ���� ���ɴ��, 0���� 100������ ������ �Է� �����մϴ�. \n");
	}
}
