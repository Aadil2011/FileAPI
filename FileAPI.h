#pragma once
#include "framework.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define READ GENERIC_READ
#define SHARE_READ FILE_SHARE_READ

#define WRITE GENERIC_WRITE


struct DOC {
	const char* path;
	std::vector<unsigned char> &data;
	void* buffer;
	size_t s;
	int flag;
	int shareMode;
};
bool __declspec(dllexport) readFile(DOC f);
bool __declspec(dllexport) writeFile(DOC f);
