#include "FileAPI.h"
#include "pch.h"

bool __declspec(dllexport) readFile(DOC f)
{
	HANDLE file = CreateFile((LPCWSTR)f.path, f.flag, f.shareMode, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE) {
		std::cerr << "Couldn't open file:\n" << GetLastError();
		return 0;
		CloseHandle(file);
	}

	LARGE_INTEGER fSize;
	if (!GetFileSizeEx(file, &fSize)) {
		std::cerr << "Couldn't get file size:\n" << GetLastError();
		return 0;
		CloseHandle(file);
	}

	f.data.resize(fSize.QuadPart);

	DWORD bytes = 0;
	bool r = ReadFile(file, f.data.data(), fSize.QuadPart, &bytes, nullptr);

	CloseHandle(file);

	if (!r || bytes != fSize.QuadPart) {
		return 0;
	}
	else {
		return 1;
	}
}

bool __declspec(dllexport) writeFile(DOC f)
{
	HANDLE file = CreateFile((LPCWSTR)f.path, f.flag, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE) {
		std::cerr << "Couldn't open file\n" << GetLastError();
		CloseHandle(file);
		return 0;
	}

	if (!f.buffer || f.s == 0) {
		std::cerr << "No file to write to\n";
		CloseHandle(file);
		return 0;
	}

	DWORD bytes = 0;
	bool w = WriteFile(file, f.buffer, f.s, &bytes, NULL);

	if (bytes != f.s) { w = 0; }

	CloseHandle(file);

	return w;
}