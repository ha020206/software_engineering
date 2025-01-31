#pragma once
struct video* PirntVideoBook_forManager(struct video * videoBook, int* videoCount, struct member * memberBook, int * memberCount);
struct video * PirntVideoBook_forMember(struct video* videoBook, int videoCount, struct member * memberBook, int memberCount, int userIndex);
