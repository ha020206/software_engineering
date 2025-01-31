#include "menu.h"
#include "FileReadAndWrite.h"
// ������ �� ���� ����ϴ� �Լ� 
int ReadFileLine(FILE* book) { //  ������ �� ���� �д´�.
	int lineCount = 0;
	char buffer = 0;
	for (int i = 0; (buffer = fgetc(book)) != EOF; i++) {
		if (buffer == '\n') {
			lineCount++;
		}
	}
	return lineCount;
}

// ������ �� ���� �д� �Լ� 
void ReadFile(int * memberCount, int * videoCount ) {

	FILE* fileMemberBook = { 0 };
	fileMemberBook = fopen("memberlist.txt", "a+");
	* memberCount = ReadFileLine(fileMemberBook);
	fclose(fileMemberBook);

	FILE* fileVideoBook = { 0 };
	fileVideoBook = fopen("videolist.txt", "a+");
	* videoCount = ReadFileLine(fileVideoBook);
	fclose(fileVideoBook);

}

// ������ ������ �д� �Լ� 
void WriteBook(struct member * memberBook, int memberCount, struct video * videoBook, int videoCount ) {
	// 
	FILE* fileMemberBook = { 0 };
	fileMemberBook = fopen("memberlist.txt", "a+");

	for (int i = 0;i < memberCount ;i++) {
		fscanf(fileMemberBook, "%s / %s / %s / %s / %d / %s / %s / %d / \n",  memberBook[i].id,  memberBook[i].passWord,  memberBook[i].name,  memberBook[i].ident,  & memberBook[i].age,  memberBook[i].num,  memberBook[i].manager, & memberBook[i].pay);
	}
	printf("... 'memberlist.txt' ������ �б� �Ϸ� !\n");
	fclose(fileMemberBook);
	//
	FILE* fileVideoBook = { 0 };
	fileVideoBook = fopen("videolist.txt", "a+");

	for (int i = 0;i < videoCount;i++) {
		fscanf(fileVideoBook, "%s / %s / %s / %d / %d / %d / %s / %s / %d / %d / \n",  videoBook[i].name,  videoBook[i].maker,   videoBook[i].id,  & videoBook[i].upDate, & videoBook[i].price,  & videoBook[i].age,  videoBook[i].isRentaled , videoBook[i].memberId , & videoBook[i].rentalDate , & videoBook[i].rentalLimit );
	}
	printf("... 'videolist.txt' ������ �б� �Ϸ� !\n");
	fclose(fileVideoBook);
	//


}

// ���Ͽ� ���� �Լ�
void WriteFile(struct member * memberBook, int memberCount, struct video * videoBook, int videoCount) {
	// 
	FILE* fileMemberBook = { 0 };
	fileMemberBook = fopen("memberlist.txt", "w+");

	for (int i = 0;i < memberCount;i++) {
		fprintf(fileMemberBook, "%s / %s / %s / %s / %d / %s / %s / %d / \n", memberBook[i].id, memberBook[i].passWord, memberBook[i].name, memberBook[i].ident, memberBook[i].age, memberBook[i].num, memberBook[i].manager, memberBook[i].pay);
		
	}
	printf("... 'memberlist.txt' ������ ���� �Ϸ� !\n");
	fclose(fileMemberBook);
	//
	FILE* fileVideoBook = { 0 };
	fileVideoBook = fopen("videolist.txt", "w+");

	for (int i = 0;i < videoCount;i++) {
		fprintf(fileVideoBook, "%s / %s / %s / %d / %d / %d / %s / %s / %d / %d / \n", videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
	}
	printf("... 'videolist.txt' ������ ���� �Ϸ� !\n");
	fclose(fileVideoBook);
	//


}