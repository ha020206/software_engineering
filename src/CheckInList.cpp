#include "menu.h"
#include "CheckInList.h"
// id 가 목록에 있는지 알려주고, 인덱스!!! 를 알려주는 함수
int IsMemberIdInList(struct member* memberBook, int memberCount, char * buffer, int * index) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].id, buffer) == 0) {
			* index = i;
			return 1;
		}
	}
	return 0;
}

// 아이디가 항목에 있는지 알려주는 함수 2(인덱스 값 안받음) 
int IsMemberIdInList2(struct member* memberBook, int memberCount, char* buffer) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].id, buffer) == 0) {
			return 1;
		}
	}
	return 0;
}
// 아이디의 현재 인덱스번호를 리턴 하는 함수
int GetIndex(struct member* memberBook, int memberCount, char* buffer ) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].id, buffer) == 0) {
			return i;
		}
	}
	return 0;
}
// 아이디가 대여자 목록에 있는지 검사하는 함수 
int IsMemberIdInVideoMemberId(struct member* memberBook, int memberCount, struct video* videoBook, int videoCount, char* buffer) {
	for (int i = 0; i < videoCount ; i++) {
		if (strcmp(videoBook[i].memberId, buffer) == 0) {
			return 1;
		}
	}
	return 0;
} 

// 아이디를 구했을 때, 맞는 암호 값을 찾아주는 함수 
int IsMemberPassWordInList(struct member* memberBook, int memberCount, char* buffer, int index) {
	if (strcmp(memberBook[index].passWord, buffer) == 0) {
		return 1;
	}
	return 0;
}
// 전화번호가 기존 항목에 있는지 알려주는 함수 
int IsMemberNumInList(struct member* memberBook, int memberCount, char* buffer) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].num, buffer) == 0) {
			return 1;
		}
	}
	return 0;
}
// 주민등록번호가 기존 항목에 있는지 알려주는 함수 
int IsMemberIdentInList(struct member* memberBook, int memberCount, char* buffer) {
	for (int i = 0; i < memberCount; i++) {
		if (strcmp(memberBook[i].ident, buffer) == 0) {
			return 1;
		}
	}
	return 0;
}

// 동일한 영화 명& 동일한 감독 명이 이미 리스트에 있는지 알려주는 함수 
int IsVideoNameMakerInList(struct video* videoBook, int videoCount, char* buffer1, char* buffer2) {
	int count = 0;
	for (int i = 0; i < videoCount; i++) {
		if (strcmp(videoBook[i].name, buffer1) == 0 && strcmp(videoBook[i].maker, buffer2) == 0) {
			count++;
		}
	}
	return count;
}
