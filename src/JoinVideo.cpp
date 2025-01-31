#include "menu.h"
#include "JoinVideo.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "GetDate.h"

// ���� ��� 
struct video JoinVideo(struct video* videoBook, int* videoCount) {

	struct video buffer = { 0 };
	// ���� �̸� �߰� 
	printf("... ���� �̸� ? \n");
	strcpy(buffer.name, RightVideoName(buffer.name));
	// ���� ���� �߰�
	printf("... ���� ���� ? \n");
	int countSameVideo = 0;
	strcpy(buffer.maker, RightVideoMaker(buffer.maker));

	// ���� �׸� ���� �˻� ����
	countSameVideo = IsVideoNameMakerInList(videoBook, *videoCount, buffer.name, buffer.maker);
	if (countSameVideo != 0) {
		printf("... �̹� ��ϵ� ������ ��ȭ�� �����մϴ�. \n");
		printf("... 01. ���� �׸��� ���� ��� ����\n... 02. ���� ��� ���\n");
		if (RightMenuKey(2) == 2) {
			return{ 0 };
		}
	}
	// ���� �뿩����  �߰�
	printf("... ���� �뿩 ���� ? (�Ϸ��) \n");
	buffer.price = RightVideoPrice( );

	//
	printf("... ���� ���� ���� ���ɴ� ? (���ͽ� ��ü �������� ���) \n");
	buffer.age = RightVideoAge();

	strcpy(buffer.id, VideoIdMaker(countSameVideo, buffer.id, buffer.name)); // ���̵� �ڵ� ���� �Լ� 
	buffer.upDate = VideoDateMaker(); // ������Ʈ ��¥ �ڵ� ���� �Լ� 

	strcpy(buffer.isRentaled, "O"); // ��Ż ���� O ����
	strcpy(buffer.memberId, "-"); // ������� ����
	buffer.rentalDate = 0; // ������¥ ����
	buffer.rentalLimit = 0; // �ݳ� ��¥ ���� 
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-25s %-10s %-10s %-10s \n", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-25s %-10d %-10d %-10d \n", buffer.name, buffer.maker, buffer.id, buffer.upDate, buffer.price, buffer.age);
	printf("---------------------------------------------------------------------------------------------------------\n");

	*videoCount = (*videoCount) + 1;

	return buffer;

}