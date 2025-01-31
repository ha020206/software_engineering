#include "menu.h"
#include "GetDate.h"

// 날짜 계산 함수 
struct tm GetNow() {
	time_t getTime = time(NULL);
	struct tm nowTime = *localtime(&getTime);
	return nowTime;
}
// 나이 계산 함수
int CountAge(char * ident){
	struct tm nowTime = GetNow(); // 현재 년도 얻기 ( -1900)
	char identYear[3] = { 0 };
	strncpy(identYear, ident, 2); // 앞의 두자리만 복사하는 함수
	int identYearInt = atoi(identYear);
	if (ident[7] == '3' || ident[7] == '4') {
		identYearInt += 2000;
	}
	else {
		identYearInt += 1900;
	}

	return (nowTime.tm_year + 1900 - identYearInt + 1);

}
// 영화 id 만들기 함수 
char* VideoIdMaker(int same, char* buffer, char* name) { 

	struct tm nowTime = GetNow();
	char splitName[3] = { 0 };
	strncat(splitName, name, 2);
	int year = (nowTime.tm_year + 1900) - 2000;
	int month = (nowTime.tm_mon) + 1;
	int day = (nowTime.tm_mday);
	int hour = (nowTime.tm_hour);
	int min = (nowTime.tm_min);
	int sec = (nowTime.tm_sec);
	sprintf(buffer, "%2s.%02d%02d%02d%02d%02d%02d.%02d", splitName, year, month, day, hour, min, sec, same);

	return buffer;

}
// 현재 시간 구하기 함수
int VideoDateMaker(void) { // 시간 구하기 함수

	struct tm nowTime = GetNow();
	int sum = 0;
	sum += (nowTime.tm_year + 1900) * pow(10, 4);
	sum += (nowTime.tm_mon + 1) * pow(10, 2);
	sum += (nowTime.tm_mday);

	return sum;

}
// + size 일 추가시 몇일일까? 함수 
int VideoRentalLimitMaker(int size) {
	int monthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	struct tm nowTime = GetNow();
	int sum = 0;
	int year = (nowTime.tm_year + 1900);
	if (year % 100 != 0 && year % 400 == 0 && year % 4 == 0) {
		monthDay[1] = 29;
	}
	int month = (nowTime.tm_mon + 1);
	int day = (nowTime.tm_mday) + size;

	if (day > monthDay[month - 1]) {
		day -= monthDay[month - 1];
		month++;
		if (month > 12) {
			month -= 12;
			year++;
		}
	}
	return year * pow(10, 4) + month * pow(10, 2) + day;

}

int VideoOverDayMaker(int limit) { // 연체 일수 확인 함수 
	int monthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int limitYear = (limit / 10000);
	if (limitYear % 100 != 0 && limitYear % 400 == 0 && limitYear % 4 == 0) {
		monthDay[1] = 29;
	}
	int limitMonth = (limit % 10000) / 100;
	int limitday = (limit % 10000) % 100;
	int limitSum = 0;
	for (int i = 1; i < limitMonth ; i++) {
		limitSum += monthDay[i];
	}
	limitSum += limitday;

	struct tm nowTime = GetNow();
	int sum = 0;
	int year = (nowTime.tm_year + 1900);
	for (int i = limitYear; i < year; i++) {
		if (i % 100 != 0 && i % 400 == 0 && i % 4 == 0) {
			sum += 366;
		}
		else {
			sum += 365;
		}
	}
	if (year % 100 != 0 && year % 400 == 0 && year % 4 == 0) {
		monthDay[1] = 29;
	}
	else {
		monthDay[1] = 28;
	}
	int month = (nowTime.tm_mon + 1);
	for (int i = 1; i < month; i++) {
		sum += monthDay[i];
	}
	int day = (nowTime.tm_mday);
	sum += day;

	return sum - limitSum ;
}

int VideoOverRentDayMaker(int limit, int size) { // 날짜 연장 함수 
	int monthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int limitYear = (limit / 10000);
	int limitMonth = (limit % 10000) / 100;
	int limitday = (limit % 10000) % 100;

	if (limitYear % 100 != 0 && limitYear % 400 == 0 && limitYear % 4 == 0) {
		monthDay[1] = 29;
	}
	limitday += size;
	if ( limitday > monthDay[limitMonth - 1]) {
		limitday -= monthDay[limitMonth - 1];
		limitMonth += 1;

		if (limitMonth > 12) {
			limitMonth -= 12;
			limitYear++;
		}
	}


	return limitYear * pow(10, 4) + limitMonth * pow(10, 2) + limitday;
}