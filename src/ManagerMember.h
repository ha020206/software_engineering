#pragma once
struct member* SearchMemberBook_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int* userIndex, char * loginId);
struct member* ChangeMemberBook_forMember(struct member* memberBook, int index, int* memberCount);
struct member* DelMemberBook(struct member* memberBook, int index, int* memberCount);