#include "menu.h"
#include "LogIn.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "ScreenClear.h"

// �α��� �Լ� 
struct member * LogIn(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int * index, int * successLogin, char * loginId) {
	int again = 0; // �ݺ��� ����� ���� 
	* index = -1; // �α��� �� ����� �ε�����ȣ�� ��� ����  
	struct member user = { 0 }; // �α��� �� ���̵�� ��й�ȣ ���� ��� ���� 
	// ���̵� �Է¹޴� �κ� 
	do {
		again = 0; 
		printf("... ���̵�?\n"); //  ���̵� �Է¹��� 
		strcpy(user.id, RightStringSize(user.id, 16)); 
		again = IsMemberIdInList(memberBook, * memberCount, user.id, index); //  ��ϵ� ���̵� �ִٸ�,, again = 1 / index�� ��ġ�ϴ� ���� �ε��� ��ȣ�� ���� 
		if (again == 0) {
			printf("... ��ϵ� ���̵� �������� �ʽ��ϴ�.\n");
			printf("... 01. �ٽ� �Է�\n... 02. ���̵� ã��\n... 03. ����\n");
			int key = RightMenuKey(3);
			if (key == 2) { // ���̵� ã�� ���� 
				printf("... �̸�?\n");
				RightMemberName(user.name);
				printf("... ��ȭ��ȣ?\n");
				RightMemberNum(user.num);
				printf("... �ֹε�Ϲ�ȣ?\n");
				RightMemberIdent(user.ident);
				int i = 0;
				for (i = 0; i < * memberCount; i++) {
					if ( (strcmp(memberBook[i].name, user.name) == 0) && (strcmp(memberBook[i].num, user.num) == 0) && (strcmp(memberBook[i].ident, user.ident) == 0) ){
						* index = i; //  ��� ���� ��ġ������ ���̵� �˷��� 
					}
				}
				if ( * index == -1 ) { //  ��ġ���� ������ -1 
					printf("... ��ϵ� ȸ�� ������ �������� �ʽ��ϴ�.\n");
					printf("... �ʱ� ȭ������ ���ư��ϴ�.\n");
					ScreenClear();
					return memberBook;
				}

				printf("... %s ���� ���̵�� [ %s ] �Դϴ�.\n", user.name, memberBook[*index].id); // ��ġ�ϸ� ���̵� �˷��� 
				
				printf("... �ʱ� ȭ������ ���ư��ϴ�.\n"); //  �ٽ� �α��� ��Ŵ 
				ScreenClear();
				return memberBook;

			}
			else if (key == 3) { //  ���� ��ư Ŭ����
				ScreenClear();
				return memberBook;
			}
		}
	} while (again == 0);


	// ��й�ȣ�� �Է¹޴� �κ� 
	do {
		again = 0;
		printf("... ��й�ȣ?\n");
		strcpy(user.passWord, RightStringSize(user.passWord, 16));
		again = IsMemberPassWordInList(memberBook, * memberCount, user.passWord, *index); // ���̵� �Է� �� �޾ƿ� �ε����� ��Ī�ϴ� ��й�ȣ�� �Է��� ��й�ȣ�� �����ϸ� again = 1
		if (again == 0) {
			printf("... ��й�ȣ �����Դϴ�.\n");
			printf("... 01. �ٽ� �Է�\n... 02. ��й�ȣ ����\n... 03. ����\n");
			int key = RightMenuKey(3);
			if (key == 2) {
				printf("... �̸�?\n");
				RightMemberName(user.name);
				printf("... ��ȭ��ȣ?\n");
				RightMemberNum(user.num);
				printf("... �ֹε�Ϲ�ȣ?\n");
				RightMemberIdent(user.ident);
				if ((strcmp(memberBook[* index].name, user.name) == 0) && (strcmp(memberBook[* index].num, user.num) == 0) && (strcmp(memberBook[* index].ident, user.ident) == 0)) {
					printf("... �ٲ� ��й�ȣ?\n"); // ��й�ȣ�� �˷����� �ʰ� �ٲ���� 
					strcpy(memberBook[* index].passWord, RightMemberPassWord(memberBook[* index].passWord));
					printf("... [%s] ���� ��й�ȣ�� [ %s ] �� �����߽��ϴ�.\n", memberBook[* index].name, memberBook[* index].passWord);
					printf("... �ʱ� ȭ������ ���ư��ϴ�.\n");
					ScreenClear();
					return memberBook;
				}
				else {
					printf("... ������ ��ġ���� �ʽ��ϴ�. �ʱ� ȭ������ ���ư��ϴ�.\n");
					ScreenClear();
					return memberBook;
				}
			}
			else if (key == 3) {
				ScreenClear();
				return memberBook;
			}
		}
	} while (again == 0);

	strcpy(loginId, memberBook[*index].id);  // loginId ������ ���� �α��� ������ ȸ���� ���̵� ���� 
	*successLogin = 1; // ���� ��ġ�ϸ�,, *successLogin = 1�� ���� , ���� �޴� ���� 
	printf("\n... [%s] [%s] �� �ݰ����ϴ�.\n\n", memberBook[* index].name, memberBook[* index].manager); // �α��� ������ �˸� 
	ScreenClear();
	return memberBook;
}
