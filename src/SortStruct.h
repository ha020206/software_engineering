#pragma once
struct video* SortVideoBook(struct video* videoBook, int videoCount);
struct member* SortMemberBook(struct member* memberBook, int memberCount);
struct member* ReAge(struct member* memberBook, int memberCount);
struct video* SortVideoBook_byDate(struct video* videoBook, int videoCount);