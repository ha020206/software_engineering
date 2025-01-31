#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // 기본 입출력
#include <string.h> // 문자열
#include <stdlib.h> // 동적메모리
#include <windows.h> // 스크린 클리어
#include <time.h> // 시간 구하기 
#include <ctype.h> // 데이터 값 판별
#include "math.h" // pow 함수 사용


struct member {
	char id[16]; // 중복 확인할 아이디 -> 회원 데이터의 고유값 
	char passWord[16]; // 비밀번호 -> 중복처리 안함
	char name[40]; // 중복 확인 안함
	char ident[15]; // 주민등록번호 중복 확인 
	int age; // 주민등록번호 에서 자동 계산
	char num[12]; // 전화번호 중복 확인 -> 이미 가입된 회원 정보가 존재합니다.
	char manager[10]; // 관리자의 경우, 해당 값이 "관리자"
	int pay; // 총 충전 금액을 작성
};
struct video {
	char name[40];
	char maker[40]; // 감독
	char id[25]; // 중복 확인할 아이디 -> 비디오 데이터의 고유값
	int upDate; // 비디오가 가게에 등록된 날짜
	int price; // 비디오 가격(하루당)
	int age; // 비디오 관람 가능 연령대 
	char isRentaled[4]; // 비디오 대여 가능 여부 확인
	char memberId[16]; // 빌렸다면 빌린사람 아이디
	int rentalDate; // 빌렸다면 빌린 날짜
	int rentalLimit; // 빌렸다면 반납 예정 날짜를 적음
};
