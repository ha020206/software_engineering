#pragma once

int IsMemberIdInList(struct member* memberBook, int memberCount, char* buffer, int* index);
int IsMemberPassWordInList(struct member* memberBook, int memberCount, char* buffer, int index);
int IsMemberNumInList(struct member* memberBook, int memberCount, char* buffer);
int IsMemberIdentInList(struct member* memberBook, int memberCount, char* buffer);
int IsMemberIdInList2(struct member* memberBook, int memberCount, char* buffer);
int IsVideoNameMakerInList(struct video* videoBook, int videoCount, char* buffer1, char* buffer2);
int GetIndex(struct member* memberBook, int memberCount, char* buffer);
int IsMemberIdInVideoMemberId(struct member* memberBook, int memberCount, struct video* videoBook, int videoCount, char* buffer);
