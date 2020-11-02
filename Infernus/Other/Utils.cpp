#include "Utils.h"

Vec2 Utils::mousePos(0, 0);
std::map<uint64_t, bool> Utils::mouseState;
std::map<uint64_t, bool> Utils::keyMapping;
HMODULE Utils::hModule;

std::string Utils::DebugEnvirDir() {
	std::string filePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Infernus");
	if (filePath.length()) {
		if (CreateDirectoryA(filePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			return filePath;
		};
	};
	return NULL;
};

std::string Utils::PacketsDir() {
	std::string filePath = DebugEnvirDir();
	if (filePath.length()) {
		filePath += "\\Packets";
		if (CreateDirectoryA(filePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			return filePath;
		};
	};
	return NULL;
};

std::string Utils::ModuleDir() {
	std::string filePath = DebugEnvirDir();
	if (filePath.length()) {
		filePath += "\\Modules";
		if (CreateDirectoryA(filePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			return filePath;
		};
	};
	return NULL;
};

void Utils::DeleteDebugFile() {
	std::string DirPath = DebugEnvirDir();
	if (DirPath.length()) {
		std::remove(std::string(DirPath + std::string("\\Debug.txt")).c_str());
	};
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

bool Utils::FileExists(const std::string& filePath) {
	struct stat buffer;
	return (stat(filePath.c_str(), &buffer) == 0);
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
};

uintptr_t Utils::FindAddress(uintptr_t ptrAddr, std::vector<unsigned int> offsets) {
	uintptr_t addr = NULL;
	if (ptrAddr != NULL) {
		addr = ptrAddr;
		for (unsigned int I = 0; I < offsets.size(); I++) {
			addr = *(uintptr_t*)(addr += offsets[I]);
			if (addr == NULL) {
				Utils::DebugFileLog("Error, Address is NULL at offset index: " + std::to_string(I));
				break;
			};
		};
	}
	return addr;
};

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

int Utils::distanceVec2(Vec2 A, Vec2 B) {
	int dX = A.x - B.x;
	int dY = A.y - B.y;
	return sqrt(dX * dX + dY * dY);
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
};

float Utils::randomFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<>dis(min, max);
	return dis(gen);
};

bool Utils::isStringFloat(std::string str) {
	std::istringstream iss(str);
	float f;
	iss >> std::noskipws >> f;
	return iss.eof() && !iss.fail();
};

std::string strToUpper(std::string str) {
	if (str.length() > 0) {
		str[0] = std::toupper(str[0]);
	};
	return str;
}