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
	printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
	printf("---------------------------------------------------------------------------------------------------------\n");

	int managerCount = 0;
	for (int i = 0; i < *memberCount; i++) {
		if (strcmp(memberBook[i].manager, "������") == 0) { // �������� ������ ���� -> �����ڰ� 0���̸� ���α׷� ���� �ȵǹǷ� �������°� ���� 
			managerCount++;
		}
	}
	struct member buffer = { 0 };
	printf("... ������ �׸�?\n");
	printf("01. �̸�\n02. ��ȭ��ȣ\n03. �ֹε�Ϲ�ȣ\n04. ��й�ȣ\n05. ȸ�� ����\n");
	int Key = RightMenuKey(5);
	int again = 0;
	int key2 = 0;

	if (Key == 1) {
		printf("... ���� �� �̸�? [ ���� �̸� : %s ]\n", memberBook[userIndex].name);
		RightMemberName(memberBook[userIndex].name);

		printf("... ���� �Ϸ� !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... �޴��� ���ư��ϴ� \n");
		return memberBook;
	}
	else if (Key == 2) {
		again = 0;
		do {
			again = 0;
			printf("... ���� �� ��ȭ��ȣ? [ ���� ��ȭ��ȣ : %s ]\n", memberBook[userIndex].num);
			strcpy(buffer.num, RightMemberNum(buffer.num));
			again = IsMemberNumInList(memberBook, * memberCount, buffer.num);
			if (again == 1) {
				printf("... �̹� ���Ե� ��ȭ��ȣ�� �����մϴ�. \n");
				printf("... 01. �ٸ� ��ȭ��ȣ �Է� \n... 02. ��ȭ��ȣ �Է� ���\n");
				key2 = RightMenuKey(2);
				if (key2 == 2) {
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;

				}
			}
		} while (again == 1);
		strcpy(memberBook[userIndex].num, buffer.num);
		printf("... ���� �Ϸ� !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... �޴��� ���ư��ϴ� \n");
		return memberBook;
	}
	else if (Key == 3) {
		do {
			again = 0;
			printf("... ���� �� �ֹε�Ϲ�ȣ? [ ���� �ֹε�Ϲ�ȣ : %s ]\n", memberBook[userIndex].ident);
			strcpy(buffer.ident, RightMemberIdent(buffer.ident)); // 
			again = IsMemberIdentInList(memberBook, * memberCount, buffer.ident);
			if (again == 1) {
				printf("... �̹� ���Ե� �ֹε�Ϲ�ȣ�� �����մϴ�. \n");
				printf("... 01. �ٸ� �ֹε�Ϲ�ȣ �Է� \n... 02. �ֹε�Ϲ�ȣ �Է� ���\n");
				key2 = RightMenuKey(2);
				if (key2 == 2) {
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}
			}
		} while (again == 1);
		strcpy(memberBook[userIndex].ident, buffer.ident);
		memberBook[userIndex].age = CountAge(memberBook[userIndex].ident); //  ���� �ڵ� ����
		printf("... ���� �Ϸ� !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... �޴��� ���ư��ϴ� \n");
		return memberBook;

	}
	else if (Key == 4) {
		printf("... ���� �� ��й�ȣ? [ ���� ��й�ȣ : %s ]\n", memberBook[userIndex].passWord);
		strcpy(memberBook[userIndex].passWord, RightMemberPassWord(memberBook[userIndex].passWord));

		printf("... ���� �Ϸ� !\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... �޴��� ���ư��ϴ� \n");
		return memberBook;
	}
	else if (Key == 5) {
		if (strcmp(memberBook[userIndex].manager, "�Ϲ�ȸ��") == 0) {
			printf("... ������ ȸ������ ���� �Ͻðڽ��ϱ�? [ �� : 1 | �ƴϿ� : 2 ]\n");
			key2 = RightMenuKey(2);
			if (key2 == 1) {
				strcpy(memberBook[userIndex].manager, "������");

				printf("... ���� �Ϸ� !\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("... �޴��� ���ư��ϴ� \n");
				return memberBook;
			}
			else {
				printf("... �޴��� ���ư��ϴ� \n");
				return memberBook;
			}
		}
		else {
			if (managerCount == 1) {
				printf("... �����ڰ� 1 ���� ���� �����ڸ� �Ϲ�ȸ������ ������ �� �����ϴ�.\n");
				printf("... �޴��� ���ư��ϴ� \n");
				return memberBook;
			}
			else {
				printf("... �Ϲ� ȸ������ ���� �Ͻðڽ��ϱ�? [ �� : 1 | �ƴϿ� : 2 ]\n");
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					if (userIndex == GetIndex(memberBook, *memberCount, loginId)) {
						* sepcialKey = -1;
						strcpy(memberBook[userIndex].manager, "�Ϲ�ȸ��");
						printf("... ���� �Ϸ� !\n");
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("... �ʱ� �޴��� ���ư��ϴ� \n");
						return memberBook;
					}
					strcpy(memberBook[userIndex].manager, "�Ϲ�ȸ��");
					printf("... ���� �Ϸ� !\n");
					printf("---------------------------------------------------------------------------------------------------------\n");
					printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
					printf("---------------------------------------------------------------------------------------------------------\n");
					printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].manager, memberBook[userIndex].pay);
					printf("---------------------------------------------------------------------------------------------------------\n");
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}
				else {
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}
			}
		}
	}
}


struct member* DelMember_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int nowIndex, int* sepcialKey, char* loginId) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", 1, memberBook[nowIndex].name, memberBook[nowIndex].num, memberBook[nowIndex].ident, memberBook[nowIndex].age, memberBook[nowIndex].id, memberBook[nowIndex].passWord, memberBook[nowIndex].manager, memberBook[nowIndex].pay);
	printf("---------------------------------------------------------------------------------------------------------\n");

	int managerCount = 0;
	for (int i = 0; i < *memberCount; i++) {
		if (strcmp(memberBook[i].manager, "������") == 0) { // �������� ������ ���� -> �����ڰ� 0���̸� ���α׷� ���� �ȵǹǷ� ��ΰ� �������� ���� ������ 
			managerCount++;
		}
	}
	
	if ( IsMemberIdInVideoMemberId(memberBook, *memberCount, videoBook, videoCount, memberBook[nowIndex].id) != 0 ) {
		printf(" ... ȸ������ �ݳ����� ���� ������ �ִ� ��� ������ �Ұ����մϴ�.\n");
		printf("... �޴��� ���ư��ϴ�.\n");
		return memberBook;
	}
	else if (strcmp(memberBook[nowIndex].manager, "������") == 0) {
		if ( managerCount == 1) {
			printf("... �����ڰ� 1 ���� ���� �����ڸ� ������ �� �����ϴ�.\n");
			printf("... �޴��� ���ư��ϴ�.\n");
			return memberBook;
		}
		else if (GetIndex(memberBook, *memberCount, loginId) == nowIndex ) { // �� �ڽ��� �����ϴ� ���
			DelMemberBook(memberBook, nowIndex, memberCount);
			* sepcialKey = -1;
			printf("... �ʱ� �޴��� ���ư��ϴ�.\n");
			return memberBook;
		}
	}
	DelMemberBook(memberBook, nowIndex, memberCount);
	printf("... �޴��� ���ư��ϴ�.\n");

	return memberBook;

}

struct video * DelVideo_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int nowIndex) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
	printf("---------------------------------------------------------------------------------------------------------\n");

	if (strcmp(videoBook[nowIndex].isRentaled, "X") == 0) {
		printf("... �뿩�� ������ ������ �� �����ϴ�.\n");
		return videoBook;
	}

	for (int i = nowIndex; i < *videoCount; i++) {
		videoBook[i] = videoBook[i + 1];
	}
	* videoCount = (*videoCount) - 1;
	printf("... ���� �Ϸ� !\n");
	return videoBook;

}


struct video* ChangeVideo_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int nowIndex) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
	printf("---------------------------------------------------------------------------------------------------------\n");

	int again = 0;
	int key = 0;
	printf("... ������ �׸�?\n");
	printf("01. ���� �̸�\n02. ���� ����\n03. ���� �뿩 ����\n04. ���� ���� ���� ���ɴ�\n05. ���� �뿩 ���� ����\n06. ���� �ݳ� ��¥ ����\n");
	key = RightMenuKey(6);
	struct video buffer = { 0 };
	if (key == 1) {
		printf("... ���� �̸� ? [ ���� �̸� : %s ] \n", videoBook[nowIndex].name);
		strcpy(buffer.name, RightVideoName(buffer.name));
		if ( IsVideoNameMakerInList( videoBook, *videoCount , buffer.name, videoBook[nowIndex].maker) != 0) {
			printf("... �̹� ��ϵ� ������ ��ȭ�� �����մϴ�. \n");
			printf("... 01. ���� �׸��� ���� ��� ����\n... 02. ���� ��� ���\n");
			if ( RightMenuKey(2) == 2) {
				printf("... �޴��� ���ư��ϴ�.\n");
				return videoBook;
			}
		}

		strcpy(videoBook[nowIndex].name, buffer.name);
		printf("... ������ ����\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... �޴��� ���ư��ϴ�.\n");

		return videoBook;
	}
	else if (key == 2) {

		printf("... ���� ���� ? [ ���� ���� : %s ] \n", videoBook[nowIndex].maker);
		strcpy(buffer.maker, RightVideoMaker(buffer.maker));

		if (IsVideoNameMakerInList(videoBook, *videoCount, videoBook[nowIndex].name, buffer.maker) != 0) {
			printf("... �̹� ��ϵ� ������ ��ȭ�� �����մϴ�. \n");
			printf("... 01. ���� �׸��� ���� ��� ����\n... 02. ���� ��� ���\n");
			if (RightMenuKey(2) == 2) {
				printf("... �޴��� ���ư��ϴ�.\n");
				return videoBook;
			}
		}
		strcpy(videoBook[nowIndex].maker, buffer.maker);

		printf("... ������ ����\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... �޴��� ���ư��ϴ�.\n");

		return videoBook;
	}
	else if (key == 3) {
		printf("... ���� �뿩 �ݾ� ?  [ ���� �ݾ� : %d ] \n", videoBook[nowIndex].price);
		videoBook[nowIndex].price = RightVideoPrice();
		printf("... ������ ����\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... �޴��� ���ư��ϴ�.\n");

		return videoBook;

	}
	else if (key == 4) {

		printf("... ���� ���� ���� ���ɴ� ? (���ͽ� ��ü �������� ���) [ ���� ���ɴ� : %d ] \n", videoBook[nowIndex].age);
		videoBook[nowIndex].age = RightVideoAge();
		printf("... ������ ����\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");

		printf("... �޴��� ���ư��ϴ�.\n");

		return videoBook;
	}
	else if (key == 5) {
		int key3 = 0;
		if (strcmp(videoBook[nowIndex].isRentaled, "X") == 0) {
			printf("... �ݳ��� ������ ���� �Ͻðڽ��ϱ�? [ �� : 1 | �ƴϿ� : 2 ] \n");
			key3 = RightMenuKey(2);
			if (key3 == 1) {
				int changeIndex = 0;
				IsMemberIdInList(memberBook, *memberCount, videoBook[nowIndex].memberId, &changeIndex); // ȸ���� �ε��� ��ȣ ã�� 
				printf("... [ID : %s][�̸� : %s] ȸ���� �ݳ��� �����մϴ�. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
				if(videoBook[nowIndex].rentalLimit - VideoDateMaker() < 0 ){ //  ���� ��ü ? 
					int overDay = VideoOverDayMaker(videoBook[nowIndex].rentalLimit);
					printf("... ��ü�� �ϼ� [ %d ]�� ���� ��ü�ᰡ �ֽ��ϴ�.\n", overDay);
					int change = overDay * videoBook[nowIndex].price;
				
					
					printf("------- ������ -------\n");
					printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[nowIndex].price);
					printf("... �� [ %d ] �� ��ü \n", overDay) ;
					printf("... ���� ���� �ݾ� [%d]��\n",  change);
					printf("----------------------\n");
					
					printf("... [ ȸ���� �����ݾ� :%d ��]\n", memberBook[changeIndex].pay);

					while (memberBook[changeIndex].pay - change < 0) {
						printf("... ȸ���� ���� �ݾ��� �����մϴ�. ȸ�� �ݾ� ���� �������� �̵��մϴ�.\n");
						memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
					}
					printf("... [ID : %s][�̸� : %s] ȸ������ [ %d ] �� �޽��ϴ�.\n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
					memberBook[changeIndex].pay -= change;
					printf("... ���� �Ϸ�! [ ȸ���� �ܾ� :%d ��]\n", memberBook[changeIndex].pay);
				}


				strcpy(videoBook[nowIndex].isRentaled, "O");
				strcpy(videoBook[nowIndex].memberId, "-");
				videoBook[nowIndex].rentalDate = 0;
				videoBook[nowIndex].rentalLimit = 0;
				printf("... �ݳ� �Ϸ� !\n");
				printf("... ������ ����\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");


				printf("... �޴��� ���ư��ϴ�.\n");

				return videoBook;
			}
			else {
				printf("... �޴��� ���ư��ϴ�.\n");

				return videoBook;
			}
		}
		else {
			printf("... �뿩�� ������ ���� �Ͻðڽ��ϱ�? [ �� : 1 | �ƴϿ� : 2 ]\n");
			key3 = RightMenuKey(2);
			if (key3 == 1) {
				int key4 = 0;
				do {
					key4 = 0;
					again = 0;
					printf("... �뿩�� ID? \n");
					strcpy(buffer.id, RightMemberId(buffer.id));

					again = IsMemberIdInList2(memberBook, *memberCount, buffer.id);
					if (again != 1) {
						printf("... ���Ե� ���̵� �������� �ʽ��ϴ�. \n");
						printf("... 01. �ٸ� ���̵� �Է� \n... 02. ���̵� �Է� ���\n");
						key4 = RightMenuKey(2);
						if (key4 == 2) {
							printf("... �޴��� ���ư��ϴ�. \n");

							return videoBook;
						}
					}
				} while (again != 1 || key4 != 0);
				int changeIndex = 0;
				IsMemberIdInList(memberBook, *memberCount, buffer.id, &changeIndex);
				if (memberBook[changeIndex].age < videoBook[nowIndex].age) {
					printf("... �� �� ���� ���ɰ��� ������ �뿩�� �� �����ϴ�.\n");
					printf("... �޴��� ���ư��ϴ�.\n");

					return videoBook;
				}
				strcpy(videoBook[nowIndex].memberId, buffer.id);
				int rentalDay = 0;
				printf("... �뿩 �ϼ� ? ( �뿩�� 1�� ~ 14�� ���� �����մϴ�. )\n");
				rentalDay = RightMenuKey(14);
				// ȸ�� ���� ���� ����
				int change = rentalDay * videoBook[nowIndex].price;
				printf("... [ID : %s][�̸� : %s] ȸ���� �뿩�� �����մϴ�. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
				printf("------- ������ -------\n");
				printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[nowIndex].price);
				printf("... �� [ %d ] �� �뿩 \n", rentalDay);
				printf("... ���� ���� �ݾ� [%d]��\n", change);
				printf("----------------------\n");
				printf("... [ ȸ���� �����ݾ� :%d ��]\n", memberBook[changeIndex].pay);
				while (memberBook[changeIndex].pay - change < 0) {
					printf("... ȸ���� ���� �ݾ��� �����մϴ�. ȸ�� �ݾ� ���� �������� �̵��մϴ�.\n");
					memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
				}
				memberBook[changeIndex].pay -= change;
				printf("... [ID : %s][�̸� : %s] ȸ������ [ %d ] �� �޽��ϴ�. \n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
				printf("... ���� �Ϸ�! [ ȸ���� �ܾ� :%d ��]\n", memberBook[changeIndex].pay);
				videoBook[nowIndex].rentalLimit = VideoRentalLimitMaker(rentalDay);
				videoBook[nowIndex].rentalDate = VideoDateMaker();
				strcpy(videoBook[nowIndex].isRentaled , "X");

				printf("... ������ ����\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");

				printf("... �޴��� ���ư��ϴ�.\n");

				return videoBook;
			}
		}
	}
else if (key == 6) {
	if ( strcmp(videoBook[nowIndex].isRentaled , "X") == 0) {
		int changeIndex = 0;
		IsMemberIdInList(memberBook, *memberCount, videoBook[nowIndex].memberId, &changeIndex); // ȸ���� �ε��� ��ȣ ã�� 
		int change = 0;
		int rentalDay = 0;
		if (videoBook[nowIndex].rentalLimit - VideoDateMaker() < 0) {
			int overDay = 0;
			printf("... ��ü�� �ϼ� [ %d ]�� ���� ��ü�ᰡ �ֽ��ϴ�.\n", overDay = VideoOverDayMaker(videoBook[nowIndex].rentalLimit));
			printf("... [ID : %s][�̸� : %s] ȸ���� ��ü�� �ΰ��� �����մϴ�. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
			change = overDay * videoBook[nowIndex].price;
			
			printf("------- ������ -------\n");
			printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[nowIndex].price);
			printf("... �� [ %d ] �� ��ü \n", overDay);
			printf("... ���� ���� �ݾ� [%d]��\n", change);
			printf("----------------------\n");
			printf("... [ ȸ���� �����ݾ� :%d ��]\n", memberBook[changeIndex].pay);
			while (memberBook[changeIndex].pay - change < 0) {
				printf("... ȸ���� ���� �ݾ��� �����մϴ�. ȸ�� �ݾ� ���� �������� �̵��մϴ�.\n");
				memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
			}
			printf("... [ID : %s][�̸� : %s] ȸ������ [ %d ] �� �޽��ϴ�. \n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
		
			memberBook[changeIndex].pay -= change;
			printf("... ���� �Ϸ�! [ ȸ���� �ܾ� :%d ��]\n", memberBook[changeIndex].pay);
			videoBook[nowIndex].rentalLimit = VideoRentalLimitMaker(0);
			rentalDay = 0;
		}
		printf("... ������ �뿩 �ϼ� ? ( �뿩�� 1�� ~ 14�� ���� �����մϴ�. ) [ ���� �ݳ� ������ : %d ]\n", videoBook[nowIndex].rentalLimit);
		rentalDay = RightMenuKey(14);
		change = rentalDay * videoBook[nowIndex].price;		
		printf("... [ID : %s][�̸� : %s] ȸ���� �뿩 ������ �����մϴ�. \n", memberBook[changeIndex].id, memberBook[changeIndex].name);
		printf("------- ������ -------\n");
		printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[nowIndex].price);
		printf("... �� [ %d ] �� �뿩 ���� \n", rentalDay);
		printf("... ���� ���� �ݾ� [%d]��\n", change);
		printf("----------------------\n");
		printf("... [ ȸ���� �����ݾ� :%d ��]\n", memberBook[changeIndex].pay);
		while (memberBook[changeIndex].pay - change < 0) {
			printf("... ȸ���� ���� �ݾ��� �����մϴ�. ȸ�� �ݾ� ���� �������� �̵��մϴ�.\n");
			memberBook[changeIndex].pay += InsertCoin(changeIndex, memberBook);
		}
		memberBook[changeIndex].pay -= change;
		printf("... [ID : %s][�̸� : %s] ȸ������ [ %d ] �� �޽��ϴ�. \n", memberBook[changeIndex].id, memberBook[changeIndex].name, change);
		printf("... ���� �Ϸ�! [ ȸ���� �ܾ� :%d ��]\n", memberBook[changeIndex].pay);
		videoBook[nowIndex].rentalLimit = VideoOverRentDayMaker(videoBook[nowIndex].rentalLimit, rentalDay);
		printf("... ������ ����\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[nowIndex].name, videoBook[nowIndex].maker, videoBook[nowIndex].id, videoBook[nowIndex].upDate, videoBook[nowIndex].price, videoBook[nowIndex].age, videoBook[nowIndex].isRentaled, videoBook[nowIndex].memberId, videoBook[nowIndex].rentalDate, videoBook[nowIndex].rentalLimit);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("... �޴��� ���ư��ϴ�.\n");
	}
	else {
		printf("... ������ �뿩 ���°� �ƴմϴ�.\n");
	}
	return videoBook;
	}
}

struct video* RentVideo_forMember(struct member* memberBook, int * memberCount, struct video * videoBook, int* videoCount, int videoIndex, int userIndex) {

	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", videoBook[videoIndex].name, videoBook[videoIndex].maker, videoBook[videoIndex].id, videoBook[videoIndex].upDate, videoBook[videoIndex].price, videoBook[videoIndex].age, videoBook[videoIndex].isRentaled);
	printf("---------------------------------------------------------------------------------------------------------\n");

	if (strcmp(videoBook[videoIndex].isRentaled, "X") == 0) {
		printf("... �뿩�� ������ �뿩�� �� �����ϴ�.\n");
		printf("... �޴��� ���ư��ϴ�.\n");

		return videoBook;
	}
	else if (memberBook[userIndex].age < videoBook[videoIndex].age) {
		printf("... �� �� ���� ���ɰ��� ������ �뿩�� �� �����ϴ�.\n");
		printf("... �޴��� ���ư��ϴ�.\n");

		return videoBook;

	}


	strcpy(videoBook[videoIndex].memberId, memberBook[userIndex].id);
	int rentalDay = 0;
	printf("... �뿩 �ϼ� ? ( �뿩�� 1�� ~ 14�� ���� �����մϴ�. )\n");
	rentalDay = RightMenuKey(14);
	// ȸ�� ���� ���� ����
	int change = rentalDay * videoBook[videoIndex].price;
	
	printf("------- ������ -------\n");
	printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[videoIndex].price);
	printf("... �� [ %d ] �� �뿩\n", rentalDay);
	printf("... ���� ���� �ݾ� [%d]��\n", change);
	printf("----------------------\n");
	printf("... ���� �����ݾ� [%d]�� \n", memberBook[userIndex].pay);
	while (memberBook[userIndex].pay - change < 0) {
		printf("... ���� �ݾ��� �����մϴ�. �ݾ� ���� �������� �̵��մϴ�.\n");
		memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
	}
	memberBook[userIndex].pay -= change;
	videoBook[videoIndex].rentalLimit = VideoRentalLimitMaker(rentalDay);
	videoBook[videoIndex].rentalDate = VideoDateMaker();
	strcpy(videoBook[videoIndex].isRentaled, "X");

	printf("... [%d]�� ����\n", change);
	printf("... ���� �ܾ� [%d]�� \n", memberBook[userIndex].pay);
	printf("... ���� �뿩 ���� ! ��ü�� ��ü�ᰡ �ΰ��˴ϴ�. \n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)",  "�뿩��", "�ݳ�������");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", videoBook[videoIndex].name, videoBook[videoIndex].maker, videoBook[videoIndex].id, videoBook[videoIndex].upDate, videoBook[videoIndex].price, videoBook[videoIndex].age, videoBook[videoIndex].isRentaled, videoBook[videoIndex].memberId, videoBook[videoIndex].rentalDate, videoBook[videoIndex].rentalLimit);
	printf("---------------------------------------------------------------------------------------------------------\n");

	printf("... �޴��� ���ư��ϴ�.\n");

	return videoBook;

}



