#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <MinHook.h>

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

#define PI 3.14159265359

struct Vec2 {
	union {
		struct {
			float x, y;
		};
		float arr[2];
	};
	Vec2() { x = y = 0; };
	Vec2(float x, float y) { this->x = x, this->y = y; };

	bool operator == (Vec2 compVec) { return compVec.x == x && compVec.y == y; };
	bool operator != (Vec2 compVec) { return compVec.x != x || compVec.y != y; };
};

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float arr[3];
	};
	Vec3() { x = y = z = 0; };
	Vec3(float x, float y, float z) { this->x = x, this->y = y, this->z = z; };

	bool operator == (Vec3 compVec) { return compVec.x == x && compVec.y == y && compVec.z == z; };
	bool operator != (Vec3 compVec) { return compVec.x != x || compVec.y != y || compVec.z != z; };

	Vec3 floor() {
		return Vec3(floorf(x), floorf(y), floorf(z));
	};

	Vec3 div(float f) {
		return Vec3(x / f, y / f, z / f);
	};

	Vec3 sub(const Vec3 &compVec) const {
		return Vec3(x - compVec.x, y - compVec.y, z - compVec.z);
	};

	float magnitude() const { return sqrtf(x * x + y * y + z * z); };
	float magnitudexy() const { return sqrtf(x * x + y * y); };
	float magnitudexz() const { return sqrtf(x * x + z * z); };

	Vec3 normalize() {
		return div(magnitude());
	};
};

struct Vec3_i {
	union {
		struct {
			int x, y, z;
		};
		int arr[3];
	};
	Vec3_i() { x = y = z = 0; };
	Vec3_i(int x, int y, int z) { this->x = x, this->y = y, this->z = z; };

	bool operator == (Vec3_i compVec) { return compVec.x == x && compVec.y == y && compVec.z == z; };
	bool operator != (Vec3_i compVec) { return compVec.x != x || compVec.y != y || compVec.z != z; };

	Vec3_i(const Vec3& copy) {
		x = (int)copy.x, y = (int)copy.y, z = (int)copy.z;
	};

	Vec3_i sub(int vx, int vy, int vz) const {
		return Vec3_i(x - vx, y - vy, z - vz);
	};

	Vec3_i sub(const Vec3_i& v) {
		return Vec3_i(x - v.x, y - v.y, z - v.z);
	};
};

struct Vec4 {
	union {
		struct {
			float x, y, z, w;
		};
		float arr[4];
	};
	Vec4() { x = y = z = w = 0; };
	Vec4(float x, float y, float z, float w) { this->x = x, this->y = y, this->z = z, this->w = w; };

	bool operator == (Vec4 compVec) { return compVec.x == x && compVec.y == y && compVec.z == z && compVec.w == w; };
	bool operator != (Vec4 compVec) { return compVec.z != x || compVec.y == y || compVec.z == z || compVec.w == w; };
};

class Utils {
public:
	/* String/File related bs */

	static std::string DebugEnvirDir();
	static void DebugFileLog(std::string input);
	static void DebugFHexLog(std::string input, UINT64 inputHex);

	/* Advanced Utility Functions */
	static void Patch(BYTE* dst, BYTE* src, unsigned int size);
	static void Nop(BYTE* dst, unsigned int size);
	static uintptr_t FindSignature(const char* szSignature);
	static bool usingKey(uint64_t key);
	static std::vector<std::string> SortArrayOfStrings(std::vector<std::string> stringVecArr);
	static float distanceVec3(Vec3, Vec3);
	static int distanceVec3_i(Vec3_i, Vec3_i);

	/* Other */
	static std::map<uint64_t, bool> mouseState;
	static std::map<uint64_t, bool> keyMapping;
	static HMODULE hModule;
};