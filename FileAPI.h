#pragma once
#include "framework.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define READ GENERIC_READ
#define SHARE_READ FILE_SHARE_READ

#define WRITE GENERIC_WRITE


struct FILE {
	const char* path;
	std::vector<unsigned char> &data;
	void* buffer;
	size_t s;
	int flag;
	int shareMode;
};
bool _declspec(dllexport) readFile(FILE f);
bool _declspec(dllexport) writeFile(FILE f);
