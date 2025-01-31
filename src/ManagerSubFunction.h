#pragma once

struct member* DelMember_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int nowIndex, int* sepcialKey, char* loginId);

struct video* ChangeVideo_forManager(struct member* memberBook, int * memberCount, struct video* videoBook, int * videoCount, int nowIndex);
struct video* DelVideo_forManager(struct member* memberBook, int * memberCount, struct video * videoBook, int* videoCount, int nowIndex);

struct member* ChangeMember_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int nowIndex, int* sepcialKey, char* loginId);
struct video* RentVideo_forMember(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int nowIndex, int userIndex);