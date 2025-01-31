#pragma once
struct video* SearchvideoBook_forManager(struct video* videoBook, int* videoCount, struct member* memberBook, int* memberCount);
struct video* SearchvideoBook_forMember(struct video* videoBook, int* videoCount, struct member* memberBook, int* memberCount, int userIndex);
