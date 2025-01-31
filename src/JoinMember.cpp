#include "menu.h"
#include "JoinMember.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "GetDate.h"

// ȸ������ �Լ� 
struct member JoinMember(struct member * memberBook, int * memberCount) {
	struct member buffer = { 0 }; //  ȸ���� �Է¹��� ����ü ���� 
	int again = 0;
	if (*memberCount == 0) { // ȸ���� �ƹ��� ������, ù ȸ���� �����ڷ� �Է¹޴´�. 
		printf("------------------------------\n");
		printf("--- ���� ������ ���� ��� ---\n");
		printf("------------------------------\n");
		strcpy(buffer.manager, "������" ); //  �����ڷ� �� ���� 
	}
	else {
		printf("... �Ϲ� ȸ������ ���\n");
		strcpy(buffer.manager, "�Ϲ�ȸ��"); //  �Ϲ�ȸ������ �� ���� 
	}
	// �̸� �Է�
	printf("... �̸�?\n");
	strcpy(buffer.name, RightMemberName(buffer.name));
	// ��ȭ��ȣ �Է�
	do {
		again = 0;
		printf("... ��ȭ��ȣ?\n");
		strcpy(buffer.num, RightMemberNum(buffer.num));
		again = IsMemberNumInList(memberBook, *memberCount, buffer.num);
		if (again == 1) {
			printf("... �̹� ���Ե� ��ȭ��ȣ�� �����մϴ�. \n");
			printf("... 01. �ٸ� ��ȭ��ȣ �Է� \n... 02. ��ȭ��ȣ �Է� ���\n");
			int key = RightMenuKey(2);
			if (key == 2) {
				printf("... �޴��� ���ư��ϴ�. \n");
				return { 0 };
			}
		}
	} while (again == 1);

	// �ֹε�Ϲ�ȣ �Է�
	do {
		again = 0;
		printf("... �ֹε�Ϲ�ȣ? [000000-0000000] �� �������� �Է��ϼ���.\n");
		strcpy(buffer.ident, RightMemberIdent(buffer.ident)); // 
		again = IsMemberIdentInList(memberBook, *memberCount, buffer.ident);
		if (again == 1) {
			printf("... �̹� ���Ե� �ֹε�Ϲ�ȣ�� �����մϴ�. \n");
			printf("... 01. �ٸ� �ֹε�Ϲ�ȣ �Է� \n... 02. �ֹε�Ϲ�ȣ �Է� ���\n");
			int key = RightMenuKey(2);
			if (key == 2) {
				printf("... �޴��� ���ư��ϴ�. \n");
				return { 0 };
			}
		}
	} while (again == 1);

	// �ֹε�Ϲ�ȣ�� ���� ���� �ڵ� ���
	buffer.age = CountAge(buffer.ident); // ��¥ ���
	// ȸ�� ���̵� �Է�
	do {
		again = 0;
		printf("... �α��� �� ���̵�?\n");
		strcpy(buffer.id, RightMemberId(buffer.id));


		again = IsMemberIdInList2(memberBook, *memberCount, buffer.id);
		if (again == 1) {
			printf("... �̹� ���Ե� ���̵� �����մϴ�. \n");
			printf("... 01. �ٸ� ���̵� �Է� \n... 02. ���̵� �Է� ���\n");
			int key = RightMenuKey(2);
			if (key == 2) {
				printf("... �޴��� ���ư��ϴ�. \n");
				return { 0 };
			}
		}
	} while (again == 1);
	// ��й�ȣ �Է�
	printf("... �α��� �� ��й�ȣ?\n");
	strcpy(buffer.passWord, RightMemberPassWord(buffer.passWord));

	// ���ʰ��Խ� ���� �ݾ��� 0 ���� �ʱ�ȭ 
	buffer.pay = 0;
	* memberCount = ( * memberCount ) + 1;

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-15s %-15s %-15s %-10s %-15s %-15s \n", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ","����", "���̵�", "��й�ȣ");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-15s %-15s %-15s %-10d %-15s %-15s \n", buffer.name, buffer.num, buffer.ident, buffer.age, buffer.id, buffer.passWord);
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("... ��� �Ϸ�! �޴��� ���ư��ϴ�.\n");
	return buffer;
}