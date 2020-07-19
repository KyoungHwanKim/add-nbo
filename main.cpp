#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <netinet/in.h>
//#include <Winsock2.h>
//#pragma comment(lib, "ws2_32.lib")

void dump(void* p, size_t n) {
	uint8_t* u8 = static_cast<uint8_t*>(p);
	size_t i = 0;
	while (true) {
		printf("%02X ", *u8++);
		if (++i >= n) break;
		if (i % 8 == 0)
			printf("\n");
	}
	printf("\n");
}

void write_4660() {
	uint16_t port = 4660; // 0x1234
	printf("port number = %d\n", port);
	dump(&port, sizeof(port));
}

uint16_t my_ntohs(uint16_t n) { // 바이트 오더를 네트워크 바이트 오더로 바꾸는 함수 (16bit ver.)
	// uint16_t n1 = (n & 0xFF00) >> 8; // 0x0034
	// uint16_t n2 = (n & 0x00FF) << 8; // 0x1200
	// return n1 | n2; //0x1234
	return (n & 0xFF00) >> 8 | (n & 0x00FF) << 8;
}

uint32_t my_ntohl(uint32_t n) { // 바이트 오더를 네트워크 바이트 오더로 바꾸는 함수 (32bit ver.)
	return (n & 0xff000000) >> 24 | (n & 0x00ff0000) >> 8 | (n & 0x0000ff00) << 8 | (n & 0x000000ff) << 24;
}

void write_0x1234() {
	uint8_t network_buffer[] = { 0x12, 0x34 };
	uint16_t* p = reinterpret_cast<uint16_t*>(network_buffer);
	//uint16_t n = my_ntohs(*p); // TODO
	uint16_t n = ntohs(*p);
	printf("16 bit number=0x%x\n", n);
}

void write_0x12345678() {
	uint8_t network_buffer[] = { 0x12, 0x34, 0x56, 0x78 };
	uint32_t* p = reinterpret_cast<uint32_t*>(network_buffer);
	uint32_t n = my_ntohl(*p); // TODO
	printf("32 bit number=0x%x\n", n);
}

int main(int argc, char* argv[]) {
	//write_4660();
	//write_0x1234();
	//write_0x12345678();

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
	int c = 0x00000001;
	if ((char *) & c) { // 리틀 엔디안이라면, 변환
		b1 = my_ntohl(b1);
		b2 = my_ntohl(b2);
	}
	
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", b1, b1, b2, b2, b1 + b2, b1 + b2);
	
	return 0;
}
