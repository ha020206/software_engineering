#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // �⺻ �����
#include <string.h> // ���ڿ�
#include <stdlib.h> // �����޸�
#include <windows.h> // ��ũ�� Ŭ����
#include <time.h> // �ð� ���ϱ� 
#include <ctype.h> // ������ �� �Ǻ�
#include "math.h" // pow �Լ� ���


struct member {
	char id[16]; // �ߺ� Ȯ���� ���̵� -> ȸ�� �������� ������ 
	char passWord[16]; // ��й�ȣ -> �ߺ�ó�� ����
	char name[40]; // �ߺ� Ȯ�� ����
	char ident[15]; // �ֹε�Ϲ�ȣ �ߺ� Ȯ�� 
	int age; // �ֹε�Ϲ�ȣ ���� �ڵ� ���
	char num[12]; // ��ȭ��ȣ �ߺ� Ȯ�� -> �̹� ���Ե� ȸ�� ������ �����մϴ�.
	char manager[10]; // �������� ���, �ش� ���� "������"
	int pay; // �� ���� �ݾ��� �ۼ�
};
struct video {
	char name[40];
	char maker[40]; // ����
	char id[25]; // �ߺ� Ȯ���� ���̵� -> ���� �������� ������
	int upDate; // ������ ���Կ� ��ϵ� ��¥
	int price; // ���� ����(�Ϸ��)
	int age; // ���� ���� ���� ���ɴ� 
	char isRentaled[4]; // ���� �뿩 ���� ���� Ȯ��
	char memberId[16]; // ���ȴٸ� ������� ���̵�
	int rentalDate; // ���ȴٸ� ���� ��¥
	int rentalLimit; // ���ȴٸ� �ݳ� ���� ��¥�� ����
};
