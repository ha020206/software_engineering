#pragma once
#define _CRT_SECURE_NO_WARNINGS

struct tm GetNow();
int CountAge(char* ident);
char* VideoIdMaker(int same, char* buffer, char* name);
int VideoDateMaker(void);
int VideoRentalLimitMaker(int size);
int VideoOverDayMaker(int limit);
int VideoOverRentDayMaker(int limit, int size);