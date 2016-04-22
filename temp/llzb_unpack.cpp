// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 
// #include "malloc-2.8.3.h"
// 
// unsigned int least_bit1(unsigned int x)
// {
// 	unsigned int nx = (unsigned int)(-(signed int)x);
// 	return x & nx;
// }
// 
// unsigned int left_bits1(unsigned int x)
// {
// 	unsigned int nx = (unsigned int)(-(signed int)(x<<1));
// 	return((x << 1) | nx);
// }
// 
// unsigned int  same_or_left_bits1(unsigned int x)
// {
// 	unsigned int nx = (unsigned int)(-(signed int)x);
// 	return ((x) | nx);
// }
// 
// void bb(size_t X)
// {
//   unsigned int Y = X - 1;
//   unsigned int K = Y >> (16-4) & 16;
//   unsigned int N = K;        Y >>= K;
//   N += K = Y >> (8-3) &  8;  Y >>= K;
//   N += K = Y >> (4-2) &  4;  Y >>= K;
//   N += K = Y >> (2-1) &  2;  Y >>= K;
//   N += K = Y >> (1-0) &  1;  Y >>= K;
//   size_t I = (N + Y);
// }
// void aa(size_t S)
// {
// 	size_t I;
// 	size_t X = S >> 8;
// 	if (X == 0)
// 		I = 0;
// 	else if (X > 0xFFFF)
// 		I = 32 - 1;
// 	else {
// 		unsigned int Y = (unsigned int)X;
// 		unsigned int N = ((Y - 0x100) >> 16) & 8;
// 		unsigned int K = (((Y <<= N) - 0x1000) >> 16) & 4;
// 		N += K;
// 		N += K = (((Y <<= K) - 0x4000) >> 16) & 2;
// 		K = 14 - N + ((Y <<= K) >> 15);
// 		I = (K << 1) + ((S >> (K + (8 - 1)) & 1));
// 	}
// }
void mkdirs(char *muldir)
{
	int i, len;
	char str[512];
	strncpy_s(str, muldir, 512);
	len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '/' || str[i] == '\\')
		{
			str[i] = '\0';
			_mkdir(str);
			str[i] = '/';
		}
	}
	return;
}

struct fileTableEntry
{
	char filePath[260]; // 260 byte
	int fileDataOffset:32;
	int fileDataDecompressedSize : 32;
	int fileDataCompressedSize : 32;
	int unknown : 32;
};

int main()
{
// 	unsigned int a = least_bit1(0x10);
// 	unsigned int b = left_bits1(0x10);
// 	unsigned int c = same_or_left_bits1(0x10);
// 
// // 	bb(0x600000);
// // 	aa(0x600000);
// // 	aa(75536);
// 
// 	void* p1 = dlmalloc(241);
// 	void* p2 = dlmalloc(241);
// 	void* p3 = dlmalloc(241);
// 	dlfree(p2);
// 
// 	void* p4 = dlmalloc(280);
	const char* nname = "arts";

	char in[260];
	sprintf_s(in, "d:\\%s.png", nname);

	FILE* fp;
	fopen_s(&fp, in, "rb");

	
	int entryCount;
	fseek(fp, -8, SEEK_END);
	fread(&entryCount, 4, 1, fp);

	int fileTableOffset;
	fseek(fp, -272, SEEK_END);
	fread(&fileTableOffset, 4, 1, fp);
	
	int KEY1 = 1654979041;
	int KEY2 = 891339733;
	fileTableOffset = fileTableOffset  ^ KEY1;
	fseek(fp, fileTableOffset, SEEK_SET);

	fileTableEntry* fileTable = new fileTableEntry[entryCount];

	for (int i = 0; i < entryCount; i++)
	{
		int entrySize1;
		fread(&entrySize1, 4, 1, fp);
		entrySize1 = entrySize1 ^ KEY1;
		int entrySize2;
		fread(&entrySize2, 4, 1, fp);
		entrySize1 = entrySize2 ^ KEY2;

		char cbuf[1024];
		fread(&cbuf, entrySize1, 1, fp);

		char ubuf[1024];
		int usize;
		int err = uncompress((Bytef*)ubuf, (uLongf*)&usize, (Bytef*)cbuf, entrySize1);

		memcpy(&fileTable[i], ubuf, usize);
	}

	for (int i = 0; i < entryCount; i++)
	{
		fileTableEntry fe = fileTable[i];
		fseek(fp, fe.fileDataOffset, SEEK_SET);

		char* cbuf = new char[fe.fileDataCompressedSize];
		fread(cbuf, fe.fileDataCompressedSize, 1, fp);

		char* ubuf = new char[fe.fileDataDecompressedSize];
		int usize;
		int err = uncompress((Bytef*)ubuf, (uLongf*)&usize, (Bytef*)cbuf, fe.fileDataCompressedSize);

		char path[260];
		sprintf_s(path, "d:\\%s\\%s", nname, fe.filePath);
		mkdirs(path);
		FILE* wfp;
		fopen_s(&wfp, path, "wb");
		if (wfp != NULL)
		{
			fwrite(ubuf, usize, 1, wfp);
			fclose(wfp);
		}
		else
		{
			fprintf(stderr, "can open file %s to write.", path);
		}

		delete[] cbuf;
		delete[] ubuf;
	}

	fclose(fp);

	delete[] fileTable;

	return 0;
}
