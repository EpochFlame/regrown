#ifndef _EBI_TMAINTITLEMGR_H
#define _EBI_TMAINTITLEMGR_H

#include "ebi/Screen/TTitleMenu.h"
#include "ebi/Screen/TPressStart.h"
#include "ebi/Screen/TTMBack.h"
#include "ebi/Screen/TNintendoLogo.h"
#include "ebi/Option.h"
#include "ebi/Omake.h"

struct Controller;

namespace ebi {
struct TMainTitleMgr {

	enum StateID { Standby, Opening, PressStart, MainMenu, Exiting };

	// Vs and Challenge are strangely swapped from the actual menu order
	enum MenuSelects { Select_NULL = -1, Select_Story, Select_Challenge, Select_Vs, Select_Options, Select_HiScore, Select_Bonus };

	TMainTitleMgr();

	void setMode(long);
	void loadResource();
	void setController(Controller*);
	void start();
	void startMenuSet(long, long);
	void forceQuit();
	bool isFinish();
	bool isAnyKey();
	int getSelectedMenu();
	void update();
	void draw();
	void showInfo();

	Screen::TTitleMenu mTitleMenu;   // _0000
	Screen::TPressStart mPressStart; // _137C
	Screen::TTMBack mTMBack;         // _160C
	Screen::TNintendoLogo mLogo;     // _1624
	u8 _1634;                        // _1634
	u8 _1635;                        // _1634
	u8 _1636;                        // _1634
	u8 _1637;                        // _1634
	u8 mAlpha;                       // _1638
	int mDrawState;                  // _163C
	u32 mOpenMenuCounter;            // _1640
	u32 mOpenMenuCounterMax;         // _1644
	Controller* mController;         // _1648
	int _164C;                       // _164C
	int mState;                      // _1650
	bool mDoEndBGM;                  // _1654
	bool mIsForceSelect;             // _1655
	int mSelectedMenuOption;         // _1658
	u32 mExitMenuCounter;            // _165C
	u32 mExitMenuCounterMax;         // _1660

	static f32 kFadeoutTime; // 1.0f
	static f32 kFadeTime;    // 0.5f
};
} // namespace ebi

#endif
