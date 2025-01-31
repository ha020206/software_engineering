#include "SortStruct.h"
#include "menu.h"
#include "GetDate.h"

struct video * SortVideoBook(struct video * videoBook, int videoCount) {
	struct video buffer = { 0 };
	for (int i = 0; i < videoCount; i++) {
		for (int j = 0; j < i; j++) {
			if ( strcmp( videoBook[i].name, videoBook[j].name ) < 0) {
				buffer = videoBook[i];
				videoBook[i] = videoBook[j];
				videoBook[j] = buffer;
			}
		}
	}
	return videoBook;

}

struct video* SortVideoBook_byDate(struct video* videoBook, int videoCount) {
	struct video buffer = { 0 };
	for (int i = 0; i < videoCount; i++) {
		for (int j = 0 ; j < i; j++) {
			if (videoBook[i].upDate > videoBook[j].upDate) {
				buffer = videoBook[i];
				videoBook[i] = videoBook[j];
				videoBook[j] = buffer;
			}
		}
	}
	return videoBook;
}


struct member* SortMemberBook(struct member* memberBook, int memberCount) {
	struct member buffer = { 0 };
	for (int i = 0; i < memberCount; i++) {
		for (int j = 0; j < i; j++) {
			if ( strcmp(memberBook[i].name, memberBook[j].name) < 0) {
				buffer = memberBook[i];
				memberBook[i] = memberBook[j];
				memberBook[j] = buffer;
			}
		}
	}
	return memberBook;
}

struct member* ReAge(struct member* memberBook, int memberCount) {


	for (int i = 0; i < memberCount; i++) {
		memberBook[i].age = CountAge(memberBook[i].ident);
	}
	return memberBook;

}
