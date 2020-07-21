#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
//#include <netinet/in.h>

uint32_t my_ntohl(uint32_t n) { // 바이트 오더를 네트워크 바이트 오더로 바꾸는 함수 (32bit ver.)
	return (n & 0xff000000) >> 24 | (n & 0x00ff0000) >> 8 | (n & 0x0000ff00) << 8 | (n & 0x000000ff) << 24;
}

int main(int argc, char* argv[]) {

	if (argc != 3) return 0;

	FILE* fp1 = fopen(argv[1], "r");
	FILE* fp2 = fopen(argv[2], "r");
	
	// 예외처리
	if (fp1 == NULL || fp2 == NULL) {
		printf("파일 읽기 중 오류");
		return 0;
	}
	
	uint32_t b1, b2;
	
	fread(&b1, sizeof(b1), 1, fp1);
	fread(&b2, sizeof(b2), 1, fp2);

	fclose(fp1);
	fclose(fp2);

	//빅 엔디안, 리틀 엔디안 체크.
	int i = 0x00000001;
	char* c = (char*) &i;
	if (*c & 1) { // 리틀 엔디안이라면, 변환
		b1 = my_ntohl(b1);
		b2 = my_ntohl(b2);
	}
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", b1, b1, b2, b2, b1 + b2, b1 + b2);
	
	return 0;
}
