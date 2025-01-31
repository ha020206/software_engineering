#include "menu.h"
#include "CheckInList.h"
// id �� ��Ͽ� �ִ��� �˷��ְ�, �ε���!!! �� �˷��ִ� �Լ�
int IsMemberIdInList(struct member* memberBook, int memberCount, char * buffer, int * index) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].id, buffer) == 0) {
			* index = i;
			return 1;
		}
	}
	return 0;
}

// ���̵� �׸� �ִ��� �˷��ִ� �Լ� 2(�ε��� �� �ȹ���) 
int IsMemberIdInList2(struct member* memberBook, int memberCount, char* buffer) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].id, buffer) == 0) {
			return 1;
		}
	}
	return 0;
}
// ���̵��� ���� �ε�����ȣ�� ���� �ϴ� �Լ�
int GetIndex(struct member* memberBook, int memberCount, char* buffer ) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].id, buffer) == 0) {
			return i;
		}
	}
	return 0;
}
// ���̵� �뿩�� ��Ͽ� �ִ��� �˻��ϴ� �Լ� 
int IsMemberIdInVideoMemberId(struct member* memberBook, int memberCount, struct video* videoBook, int videoCount, char* buffer) {
	for (int i = 0; i < videoCount ; i++) {
		if (strcmp(videoBook[i].memberId, buffer) == 0) {
			return 1;
		}
	}
	return 0;
} 

// ���̵� ������ ��, �´� ��ȣ ���� ã���ִ� �Լ� 
int IsMemberPassWordInList(struct member* memberBook, int memberCount, char* buffer, int index) {
	if (strcmp(memberBook[index].passWord, buffer) == 0) {
		return 1;
	}
	return 0;
}
// ��ȭ��ȣ�� ���� �׸� �ִ��� �˷��ִ� �Լ� 
int IsMemberNumInList(struct member* memberBook, int memberCount, char* buffer) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].num, buffer) == 0) {
			return 1;
		}
	}
	return 0;
}
// �ֹε�Ϲ�ȣ�� ���� �׸� �ִ��� �˷��ִ� �Լ� 
int IsMemberIdentInList(struct member* memberBook, int memberCount, char* buffer) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].ident, buffer) == 0) {
			return 1;
		}
	}
	return 0;
}

// ������ ��ȭ ��& ������ ���� ���� �̹� ����Ʈ�� �ִ��� �˷��ִ� �Լ� 
int IsVideoNameMakerInList(struct video* videoBook, int videoCount, char* buffer1, char* buffer2) {
	int count = 0;
	for (int i = 0; i < videoCount; i++) {
		if (strcmp(videoBook[i].name, buffer1) == 0 && strcmp(videoBook[i].maker, buffer2) == 0) {
			count++;
		}
	}
	return count;
}
