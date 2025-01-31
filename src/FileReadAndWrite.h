#pragma once
#define _CRT_SECURE_NO_WARNINGS

int ReadFileLine(FILE* book);
void ReadFile(int* memberCount, int* videoCount);

void WriteBook(struct member* memberBook, int memberCount, struct video* videoBook, int videoCount);
void WriteFile(struct member* memberBook, int memberCount, struct video* videoBook, int videoCount);
