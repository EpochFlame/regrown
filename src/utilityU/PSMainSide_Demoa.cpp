#include "PSM/Demo.h"
#include "SoundID.h"
#include "utilityU.h"
#include "PSM/Scene.h"
#include "PSSystem/PSGame.h"
#include "PSM/ObjCalc.h"

static inline bool streq(const char* a, const char* b)
{
	if (a == nullptr || b == nullptr)
		return false;
	if (strcmp(a, b) == 0)
		return true;
	else
		return false;
}

namespace PSM {

/*
 * --INFO--
 * Address:	........
 * Size:	000074
 */
void DemoInitiator::equalSetStream(const char* buffer, u32 AST_ID, u8 byte)
{
	mSongChosen = false;
	bool check  = false;
	if (mByte && mName) {
		check = true;
	}
	P2ASSERTLINE(41, check);

	*mAST_ID = AST_ID;
	strcpy((char*)buffer, "");
	*mByte = byte;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void DemoInitiator::setDefault(const char* comp, u8 byte, u32 id)
{
	if (!mSongChosen) {
		if (strcmp(mName, comp) == 0) {
			mSongChosen = true;
			*mAST_ID    = id;
			*mByte      = byte;
		}
	}
}

/*
 * --INFO--
 * Address:	80463FE8
 * Size:	00005C
 */
Demo::Demo()
{
	_18               = 0;
	mDoStartWithAudio = 1;
	mSoundID          = (SoundID)-1;
	mSystemSE         = (SoundID)-1;
	mFuncptr          = nullptr;
};

/*
 * --INFO--
 * Address:	80464384
 * Size:	001DA4
 */
PSSystem::BgmSeq* Demo::initiate(DemoArg demoArg, u8* unk)
{
	DemoInitiator init            = DemoInitiator(unk, demoArg.mName);
	JAInter::SoundInfo audio_info = { 0x00000000, 0x7F030000, 0x3F800000, 0x3C000000 };

	char buffer[0x20];
	buffer[0]  = '\0';
	u32 AST_ID = -1;

	PSSystem::BgmSeq* seq = nullptr;
	P2ASSERTLINE(256, init.mName);

	// TODO
	init.mAST_ID = &AST_ID;
	init.equalSetStream(buffer, -1, -1);

	init.setDefault("s02_dayend_result", -1, 0xc0011012);
	init.setDefault("s01_dayend", -1, demoArg.mBgmID);
	init.setDefault("s03_orimadown", -1, 0xc0011005);
	init.setDefault("s05_pikminzero", -1, 0xc0011006);
	init.setDefault("s11_dope_first_b", -1, 0xc0011001);
	init.setDefault("s11_dope_first_r", -1, 0xc0011001);
	init.setDefault("s11_dopebin_first_b", -1, 0xc0011008);
	init.setDefault("s11_dopebin_first_r", -1, 0xc0011008);

	if (!streq("s01_dayend", init.mName)) {
		bool is_key     = (demoArg.mPelletName != nullptr) && streq(demoArg.mPelletName, "key");
		bool not_is_key = !is_key;

		u32 demo_arg = demoArg.mBgmID;
		if (not_is_key) {
			init.setDefault("s17_suck_equipment", -1, demo_arg);
		}
		if (is_key) {
			init.setDefault("s17_suck_equipment", -1, 0xc0011007);
		}

		demo_arg = demoArg.mBgmID;
		if (not_is_key) {
			init.setDefault("s22_cv_suck_equipment", -1, demo_arg);
		}
		if (is_key) {
			init.setDefault("s22_cv_suck_equipment", -1, 0xc0011007);
		}

		if (not_is_key) {
			init.setDefault("s10_suck_treasure", -1, 0xc0011001);
		}
		if (is_key) {
			init.setDefault("s10_suck_treasure", -1, 0xc0011007);
		}

		if (is_key) {
			init.setDefault("s22_cv_suck_treasure", -1, 0xc0011007);
		}
		if (not_is_key) {
			init.setDefault("s22_cv_suck_treasure", -1, 0xc0011001);
		}
	}

	init.setDefault("s04_dayend_orimadown", -1, 0xc001101d);
	init.setDefault("s06_dayend_pikminzero", -1, 0xc001101d);

	init.setDefault("g1A_red_doping", -1, 0xc0011009);
	init.setDefault("g1A_red_doping", -1, 0xc0011009);
	init.setDefault("g1B_black_doping", -1, 0xc0011047);
	init.setDefault("g02_boot_onyonR", -1, 0xc001100c);
	init.setDefault("g1E_boot_onyonY", -1, 0xc001100c);
	init.setDefault("g20_boot_onyonB", -1, 0xc001100c);
	init.setDefault("g03_meet_redpikmin", -1, 0xc001100d);
	init.setDefault("g1F_meet_yellowpikmin", -1, 0xc001100d);
	init.setDefault("g21_meet_bluepikmin", -1, 0xc001100d);
	init.setDefault("g24_meet_blackpikmin", -1, 0xc001100d);
	init.setDefault("g27_meet_whitepikmin", -1, 0xc001100d);
	init.setDefault("g33_camera_demo", -1, 0xc0011024);

	if (PSMGetGameSceneA()->isCave()) {
		init.setDefault("s09_holein", -1, 0xc0011046);
	} else {
		init.setDefault("s09_holein", -1, 0xc0011026);
	}

	init.setDefault("s16_find_item_00", -1, 0xc0011027);
	init.setDefault("s16_find_item_01", -1, 0xc0011027);
	init.setDefault("s16_find_item_02", -1, 0xc0011027);
	init.setDefault("s16_find_item_03", -1, 0xc0011027);
	init.setDefault("s16_find_item_04", -1, 0xc0011027);
	init.setDefault("s16_find_item_05", -1, 0xc0011027);
	init.setDefault("s16_find_item_06", -1, 0xc0011027);
	init.setDefault("s16_find_item_07", -1, 0xc0011027);
	init.setDefault("s16_find_item_08", -1, 0xc0011027);
	init.setDefault("s16_find_item_09", -1, 0xc0011027);
	init.setDefault("s16_find_item_10", -1, 0xc0011027);
	init.setDefault("s16_find_item_11", -1, 0xc0011027);
	init.setDefault("s16_find_item_12", -1, 0xc0011027);

	init.setDefault("s0C_cv_escape", -1, 0xc0011028);

	init.setDefault("g01_pick_me", -1, 0xc0011029);

	init.setDefault("g04_find_treasure", -1, 0xc0011027);

	init.setDefault("g05_find_cave_f_01", -1, 0xc0011029);
	init.setDefault("g05_find_cave_f_02", -1, 0xc0011029);
	init.setDefault("g05_find_cave_f_03", -1, 0xc0011029);
	init.setDefault("g05_find_cave_f_04", -1, 0xc0011029);
	init.setDefault("g05_find_cave_l_01", -1, 0xc0011029);
	init.setDefault("g05_find_cave_l_02", -1, 0xc0011029);
	init.setDefault("g05_find_cave_l_03", -1, 0xc0011029);
	init.setDefault("g05_find_cave_l_04", -1, 0xc0011029);
	init.setDefault("g05_find_cave_t_01", -1, 0xc0011029);
	init.setDefault("g05_find_cave_t_02", -1, 0xc0011029);
	init.setDefault("g05_find_cave_t_03", -1, 0xc0011029);
	init.setDefault("g05_find_cave_t_04", -1, 0xc0011029);
	init.setDefault("g05_find_cave_y_01", -1, 0xc0011029);
	init.setDefault("g05_find_cave_y_02", -1, 0xc0011029);
	init.setDefault("g05_find_cave_y_03", -1, 0xc0011029);
	init.setDefault("g05_find_cave_y_04", -1, 0xc0011029);

	init.setDefault("g0A_cv_find_hole", -1, 0xc0011029);
	init.setDefault("g0B_cv_find_fountain", -1, 0xc0011029);

	init.setDefault("g18_find_gate", -1, 0xc001102a);
	init.setDefault("g19_find_rock", -1, 0xc0011029);
	init.setDefault("g2D_red_extract", -1, 0xc0011027);
	init.setDefault("g2E_black_extract", -1, 0xc0011027);
	init.setDefault("g34_yellow_extract", -1, 0xc001102b);
	init.setDefault("g37_get_louie", -1, 0xc0011027);
	init.setDefault("g38_find_whitepom", -1, 0xc0011029);
	init.setDefault("g39_find_blackpom", -1, 0xc0011029);

	init.setDefault("x01_gamestart", -1, 0xc001102c);
	init.setDefault("x02_watch_red_pikmin", -1, 0xc001102d);
	init.setDefault("x06_join", -1, 0xc001102e);
	init.setDefault("x12_drain_water", -1, 0xc001102a);
	init.setDefault("x10_find_yellow_onyon", -1, 0xc001102f);
	init.setDefault("x11_find_blue_onyon", -1, 0xc0011030);
	init.setDefault("x16_hiba", -1, 0xc0011031);
	init.setDefault("x13_exp_leafchappy", -1, 0xc001102a);
	init.setDefault("x20_blackman", -1, 0xc0011032);

	init.setDefault("s13_pikmin_supply", -1, 0xc0011033);
	init.setDefault("s0B_cv_coursein", -1, 0xc0011036);
	init.setDefault("s0E_return_cave", -1, 0xc0011037);

	init.setDefault("e00_E3_cavestart", -1, 0xc0011039);

	init.setDefault("g07_cv_gamestart", -1, 0xc001103a);
	init.setDefault("g08_first_return", -1, 0xc001103b);
	init.setDefault("g09_first_sunset", -1, 0xc0011033);
	init.setDefault("g16_100_pikmin", -1, 0xc0011033);
	init.setDefault("g16_95_pikmin", -1, 0xc0011033);
	init.setDefault("g26_inout_black", -1, 0xc001104a);
	init.setDefault("g29_inout_white", -1, 0xc0011048);
	init.setDefault("g2B_white_poison", -1, 0xc0011031);
	init.setDefault("g2C_inout_red", -1, 0xc0011033);
	init.setDefault("g36_find_louie", -1, 0xc0011031);

	init.setDefault("x01_coursein_forest", -1, 0xc0011034);
	init.setDefault("x01_coursein_yakushima", -1, 0xc0011034);
	init.setDefault("x01_coursein_last", -1, 0xc0011034);
	init.setDefault("x04_exp_y", -1, 0xc0011049);
	init.setDefault("x05_louiestart", -1, 0xc0011035);
	init.setDefault("x07_first_recovery", -1, 0xc0011049);
	init.setDefault("x08_cv_suck_carcass", -1, 0xc0011033);
	init.setDefault("x09_exp_detector", -1, 0xc0011033);
	init.setDefault("x14_white_dig", -1, 0xc0011033);

	init.setDefault("g32_get_map", -1, 0xc0011048);
	init.setDefault("g35_president_gamestart", -1, 0xc0011033);

	init.setDefault("x15_exp_x", -1, 0xc0011033);
	init.setDefault("x17_join_guide", -1, 0xc0011033);
	init.setDefault("x18_exp_pellet", -1, 0xc0011033);

	init.setDefault("x03_find_red_onyon", -1, 0xc001103c);

	init.mSongChosen = streq("s02_dayend_result", init.mName);
	if (init.mSongChosen) {
		audio_info.volume.v2 -= 0xf;
	}

	if (streq("s10_suck_treasure", init.mName) || streq("s11_dope_first_b", init.mName) || streq("s11_dope_first_r", init.mName)
	    || streq("s11_dopebin_first_b", init.mName) || streq("s11_dopebin_first_r", init.mName) || streq("s17_suck_equipment", init.mName)
	    || streq("s22_cv_suck_equipment", init.mName) || streq("s22_cv_suck_treasure", init.mName) || streq("x19_vs_bedama", init.mName)) {
		mDoStartWithAudio = false;
		mSoundID          = PSSE_EV_HOME_PELLET_BACUUM;
	} else if (streq("g2F_appear_hole", init.mName)) {
		mSoundID = PSSE_SY_WORK_FINISH;
		mFuncptr = PSChangeBgm_ChallengeGame;
	} else if (streq("g30_appear_fountain", init.mName)) {
		mFuncptr = PSChangeBgm_ChallengeGame;
	} else if (streq("x20_blackman", init.mName) || streq("x03_find_red_onyon", init.mName)) {
		mDoStartWithAudio = false;
	} else if (streq("s01_dayend", init.mName)) {
		switch ((u32)demoArg.mPelletName) {
		case 1:
			mSoundID = PSSE_PL_DAYEND_KAISAN_LUI;
			break;
		case 2:
			mSoundID = PSSE_PL_DAYEND_KAISAN_SHA;
			break;
		default:
		case 0:
			mSoundID = PSSE_PL_DAYEND_KAISAN_ORI;
			break;
		}
	}

	if (streq("x20_blackman", init.mName)) {
		mSoundID = PSSE_EN_TIRE_FALL;
	}

	if (AST_ID != -1) {
		PSGame::PikSceneMgr* scene_mgr = (PSGame::PikSceneMgr*)PSSystem::getSceneMgr();
		PSSystem::checkSceneMgr(scene_mgr);

		seq  = scene_mgr->newStreamBgm(AST_ID, audio_info);
		*unk = -1;

	} else if (buffer[0] != 0) {
		PSGame::PikSceneMgr* scene_mgr = (PSGame::PikSceneMgr*)PSSystem::getSceneMgr();
		PSSystem::checkSceneMgr(scene_mgr);

		seq = scene_mgr->newBgmSeq(buffer, audio_info);
		P2ASSERTLINE(632, seq);
	}

	return seq;
}

} // namespace PSM
