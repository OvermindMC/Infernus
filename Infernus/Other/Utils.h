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
	
	Vec2 sub(const Vec2& vec) {
		return Vec2(x - vec.x, y - vec.y);
	};

	Vec2 normalAngles() {
		float x = this->x;
		float y = this->y;
		while (x > 90.0f)
			x -= 180.0f;
		while (x < -90.0f)
			x += 180.0f;
		while (y > 180.0f)
			y -= 360.0f;
		while (y < -180.0f)
			y += 360.0f;
		return Vec2(x, y);
	};
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

	Vec3 add(float x1, float y1, float z1) {
		return Vec3(this->x + x1, this->y + y1, this->z + z1);
	};

	float magnitude() const { return sqrtf(x * x + y * y + z * z); };
	float magnitudexy() const { return sqrtf(x * x + y * y); };
	float magnitudexz() const { return sqrtf(x * x + z * z); };

	Vec3 normalize() {
		return div(magnitude());
	};

	Vec2 calcAngle(Vec3 vec) {
		float degreeRadian = 180.0f / PI;
		Vec3 diff = vec.sub(*this);
		Vec2 angles;
		angles.x = asinf(diff.y) * -degreeRadian;
		angles.y = (float)-atan2f(diff.x, diff.z) * degreeRadian;
		return angles;
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
	static std::string PacketsDir();
	static std::string ModuleDir();
	static std::string KeybindsDir();
	static void DeleteDebugFile();
	static void DebugFileLog(std::string input);
	static void DebugFHexLog(std::string input, UINT64 inputHex);
	static bool FileExists(const std::string&);

	/* Advanced Utility Functions */
	static void Patch(BYTE* dst, BYTE* src, unsigned int size);
	static void Nop(BYTE* dst, unsigned int size);
	static uintptr_t FindAddress(uintptr_t, std::vector<unsigned int>);
	static uintptr_t FindSignature(const char* szSignature);
	static bool usingKey(uint64_t key);
	static std::vector<std::string> SortArrayOfStrings(std::vector<std::string> stringVecArr);
	static int distanceVec2(Vec2, Vec2);
	static float distanceVec3(Vec3, Vec3);
	static int distanceVec3_i(Vec3_i, Vec3_i);
	static float randomFloat(float, float);
	static bool isStringFloat(std::string);
	static std::string strToUpper(std::string);

	/* Other */
	static Vec2 mousePos;
	static std::map<uint64_t, bool> mouseState;
	static std::map<uint64_t, bool> keyMapping;
	static HMODULE hModule;
};


/* View Matrix Stuff */

struct glmatrixf {
	union {
		float v[16];
		float v_nested[4][4];
	};

	__forceinline float operator[](int i) const { return v[i]; }
	__forceinline float& operator[](int i) { return v[i]; }

#define MULMAT(row, col) v[col + row] = x[row] * y[col] + x[row + 4] * y[col + 1] + x[row + 8] * y[col + 2] + x[row + 12] * y[col + 3];

	template <class XT, class YT>
	void mul(const XT x[16], const YT y[16]) {
		MULMAT(0, 0);
		MULMAT(1, 0);
		MULMAT(2, 0);
		MULMAT(3, 0);
		MULMAT(0, 4);
		MULMAT(1, 4);
		MULMAT(2, 4);
		MULMAT(3, 4);
		MULMAT(0, 8);
		MULMAT(1, 8);
		MULMAT(2, 8);
		MULMAT(3, 8);
		MULMAT(0, 12);
		MULMAT(1, 12);
		MULMAT(2, 12);
		MULMAT(3, 12);
	}

#undef MULMAT

	glmatrixf* correct() {
		glmatrixf* newMatPtr = new glmatrixf;

		for (int i = 0; i < 4; i++) {
			newMatPtr->v[i * 4 + 0] = v[0 + i];
			newMatPtr->v[i * 4 + 1] = v[4 + i];
			newMatPtr->v[i * 4 + 2] = v[8 + i];
			newMatPtr->v[i * 4 + 3] = v[12 + i];
		}
		return newMatPtr;
	};

	inline bool OWorldToScreen(Vec3 origin, Vec3 pos, Vec2& screen, Vec2 fov, Vec2 displaySize) {
		pos = pos.sub(origin);

		float x = transformx(pos);
		float y = transformy(pos);
		float z = transformz(pos);

		if (z > 0)
			return false;

		float mX = (float)displaySize.x / 2.0F;
		float mY = (float)displaySize.y / 2.0F;

		screen.x = mX + (mX * x / -z * fov.x);
		screen.y = mY - (mY * y / -z * fov.y);

		return true;
	}

	inline void mul(const glmatrixf& x, const glmatrixf& y) {
		mul(x.v, y.v);
	}

	inline void translate(float x, float y, float z) {
		v[12] += x;
		v[13] += y;
		v[14] += z;
	}

	inline void translate(const Vec3& o) {
		translate(o.x, o.y, o.z);
	}

	inline void scale(float x, float y, float z) {
		v[0] *= x;
		v[1] *= x;
		v[2] *= x;
		v[3] *= x;
		v[4] *= y;
		v[5] *= y;
		v[6] *= y;
		v[7] *= y;
		v[8] *= z;
		v[9] *= z;
		v[10] *= z;
		v[11] *= z;
	}

	inline void invertnormal(Vec3& dir) const {
		Vec3 n(dir);
		dir.x = n.x * v[0] + n.y * v[1] + n.z * v[2];
		dir.y = n.x * v[4] + n.y * v[5] + n.z * v[6];
		dir.z = n.x * v[8] + n.y * v[9] + n.z * v[10];
	}

	inline void invertvertex(Vec3& pos) const {
		Vec3 p(pos);
		p.x -= v[12];
		p.y -= v[13];
		p.z -= v[14];
		pos.x = p.x * v[0] + p.y * v[1] + p.z * v[2];
		pos.y = p.x * v[4] + p.y * v[5] + p.z * v[6];
		pos.z = p.x * v[8] + p.y * v[9] + p.z * v[10];
	}

	inline void transform(const Vec3& in, Vec4& out) const {
		out.x = transformx(in);
		out.y = transformy(in);
		out.z = transformz(in);
		out.w = transformw(in);
	}

	__forceinline float transformx(const Vec3& p) const {
		return p.x * v[0] + p.y * v[4] + p.z * v[8] + v[12];
	}

	__forceinline float transformy(const Vec3& p) const {
		return p.x * v[1] + p.y * v[5] + p.z * v[9] + v[13];
	}

	__forceinline float transformz(const Vec3& p) const {
		return p.x * v[2] + p.y * v[6] + p.z * v[10] + v[14];
	}

	__forceinline float transformw(const Vec3& p) const {
		return p.x * v[3] + p.y * v[7] + p.z * v[11] + v[15];
	}

	__forceinline Vec3 gettranslation() const {
		return Vec3(v[12], v[13], v[14]);
	}

	//assault cube world2screen
	Vec3 transform(glmatrixf* matrix, Vec3& totransform) {
		return Vec3(matrix->transformx(totransform),
			matrix->transformy(totransform),
			matrix->transformz(totransform))
			.div(matrix->transformw(totransform));
	}

	///pos should be the exact center of the enemy model for scaling to work properly
	Vec3 WorldToScreen(Vec3 pos, int width, int height) {
		//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
		Vec4 clipCoords;
		clipCoords.x = pos.x * v[0] + pos.y * v[4] + pos.z * v[8] + v[12];
		clipCoords.y = pos.x * v[1] + pos.y * v[5] + pos.z * v[9] + v[13];
		clipCoords.z = pos.x * v[2] + pos.y * v[6] + pos.z * v[10] + v[14];
		clipCoords.w = pos.x * v[3] + pos.y * v[7] + pos.z * v[11] + v[15];

		//perspective division, dividing by clip.W = Normalized Device Coordinates
		Vec3 NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;

		//viewport tranform to screenCooords

		Vec3 playerscreen;
		playerscreen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
		playerscreen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);

		return playerscreen;
	}
};