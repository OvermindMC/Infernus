#include "Utils.h"

std::map<uint64_t, bool> Utils::mouseState;
std::map<uint64_t, bool> Utils::keyMapping;
HMODULE Utils::hModule;

std::string Utils::DebugEnvirDir() {
	std::string filePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\\Infernus");
	if (filePath.length()) {
		if (CreateDirectoryA(filePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			return filePath;
		};
	};
	return NULL;
};

void Utils::DebugFileLog(std::string input) {
	std::string DirPath = DebugEnvirDir();
	if (DirPath.length()) {
		std::string debugFilePath = DirPath + std::string("\\Debug.txt");
		CloseHandle(CreateFileA(debugFilePath.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));
		std::ofstream fileOutput;
		fileOutput.open(debugFilePath.c_str(), std::ios_base::app);
		fileOutput << input << std::endl;
		fileOutput.close();
	};
};

void Utils::DebugFHexLog(std::string input, UINT64 inputHex) {
	std::stringstream strm;
	strm << input << " " << std::hex << inputHex;
	Utils::DebugFileLog(strm.str());
};

void Utils::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Utils::Nop(BYTE* dst, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

uintptr_t Utils::FindSignature(const char* szSignature) {
	const char* pattern = szSignature;
	uintptr_t firstMatch = 0;
	static const uintptr_t rangeStart = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
	static MODULEINFO miModInfo;
	static bool init = false;
	if (!init) {
		init = true;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	}
	static const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

	for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pattern)
			return firstMatch;

		while (*(PBYTE)pattern == ' ')
			pattern++;

		if (!*pattern)
			return firstMatch;

		if (oldPat != pattern) {
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		}

		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte)
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pattern[2])
				return firstMatch;

			pattern += 2;
		}
		else
		{
			pattern = szSignature;
			firstMatch = 0;
		}
	}
#ifdef _DEBUG
	const char* sig = szSignature;
#endif
	return 0u;
}

bool Utils::usingKey(uint64_t key) {
	return keyMapping[key];
};

std::vector<std::string> Utils::SortArrayOfStrings(std::vector<std::string> stringVecArr) {
	std::vector<std::string> stringArr;

	for (int I = 0; I < stringVecArr.size(); I++) {
		stringArr.push_back(stringVecArr.at(I));
	};

	for (int I = 0; I < stringArr.size(); I++) {
		std::string temp = stringArr[I];

		int J = I - 1;
		while (J >= 0 && temp.length() < stringArr[J].length()) {
			stringArr[J + 1] = stringArr[J];
			J--;
		}
		stringArr[J + 1] = temp;
	};
	return stringArr;
};

float Utils::distanceVec3(Vec3 A, Vec3 B) {
	float dX = A.x - B.x;
	float dY = A.y - B.y;
	float dZ = A.z - B.z;
	return sqrt(dX * dX + dY * dY + dZ * dZ);
};

int Utils::distanceVec3_i(Vec3_i A, Vec3_i B) {
	int dX = A.x - B.x;
	int dY = A.y - B.y;
	int dZ = A.z - B.z;
	return sqrt(dX * dX + dY * dY + dZ * dZ);
}