#ifndef _GAME_CURRTRIINFO_H
#define _GAME_CURRTRIINFO_H

#include "Vector3.h"

namespace Sys {
struct Triangle;
struct TriangleTable;
} // namespace Sys

namespace Game {
struct CurrTriInfo {
	CurrTriInfo()
	{
		mTriangle = nullptr;

		mMaxY = FLOAT_DIST_MAX;
		mMinY = FLOAT_DIST_MIN;

		mTable = nullptr;

		mNormalVec = Vector3f(0.0f, 1.0f, 0.0f);

		_0C = true;
		_0D = false;
	}

	Vector3f mPosition;         // _00
	bool _0C;                   // _0C
	bool _0D;                   // _0D
	u8 _0E;                     // _0E
	u8 _0F;                     // _0F
	Sys::TriangleTable* mTable; // _10
	Sys::Triangle* mTriangle;   // _14
	f32 mMaxY;                  // _18
	f32 mMinY;                  // _1C
	Vector3f mNormalVec;        // _20
};
} // namespace Game

#endif
