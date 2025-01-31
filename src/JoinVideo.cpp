#include "menu.h"
#include "JoinVideo.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "GetDate.h"

// 비디오 등록 
struct video JoinVideo(struct video* videoBook, int* videoCount) {

	struct video buffer = { 0 };
	// 비디오 이름 추가 
	printf("... 비디오 이름 ? \n");
	strcpy(buffer.name, RightVideoName(buffer.name));
	// 비디오 감독 추가
	printf("... 비디오 감독 ? \n");
	int countSameVideo = 0;
	strcpy(buffer.maker, RightVideoMaker(buffer.maker));

	// 동일 항목에 대한 검사 진행
	countSameVideo = IsVideoNameMakerInList(videoBook, *videoCount, buffer.name, buffer.maker);
	if (countSameVideo != 0) {
		printf("... 이미 등록된 동일한 영화가 존재합니다. \n");
		printf("... 01. 동일 항목의 비디오 등록 진행\n... 02. 비디오 등록 취소\n");
		if (RightMenuKey(2) == 2) {
			return{ 0 };
		}
	}
	// 비디오 대여가격  추가
	printf("... 비디오 대여 가격 ? (하루당) \n");
	buffer.price = RightVideoPrice( );

	//
	printf("... 비디오 관람 가능 연령대 ? (엔터시 전체 연령으로 기록) \n");
	buffer.age = RightVideoAge();

	strcpy(buffer.id, VideoIdMaker(countSameVideo, buffer.id, buffer.name)); // 아이디 자동 생성 함수 
	buffer.upDate = VideoDateMaker(); // 업데이트 날짜 자동 지정 함수 

	strcpy(buffer.isRentaled, "O"); // 렌탈 가능 O 설정
	strcpy(buffer.memberId, "-"); // 빌린사람 없음
	buffer.rentalDate = 0; // 빌린날짜 없음
	buffer.rentalLimit = 0; // 반납 날짜 없음 
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-25s %-10s %-10s %-10s \n", "비디오이름", "감독", "비디오고유번호", "등록날짜", "비디오가격", "제한연령");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-20s %-10s %-25s %-10d %-10d %-10d \n", buffer.name, buffer.maker, buffer.id, buffer.upDate, buffer.price, buffer.age);
	printf("---------------------------------------------------------------------------------------------------------\n");

	*videoCount = (*videoCount) + 1;

	return buffer;

}