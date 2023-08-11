#include "Game/Entities/WaterOtakara.h"
#include "LoadResource.h"

namespace Game {
namespace WaterOtakara {

namespace {
static const char* cOtakaraChangeTexName = "/enemy/data/WaterOtakara/otakara_blue_s3tc.bti";
} // namespace

/*
 * --INFO--
 * Address:	802B86E0
 * Size:	000050
 */
Mgr::Mgr(int objLimit, u8 modelType)
    : OtakaraBase::Mgr(objLimit, modelType)
{
	mName = "水オタカラムシマネージャ"; // water otakara manager
}

/*
 * --INFO--
 * Address:	802B8730
 * Size:	000048
 */
void Mgr::doAlloc() { init(new OtakaraBase::Parms); }

/*
 * --INFO--
 * Address:	802B8778
 * Size:	000060
 */
void Mgr::createObj(int count) { mObj = new Obj[count]; }

/*
 * --INFO--
 * Address:	802B88C8
 * Size:	000010
 */
EnemyBase* Mgr::getEnemy(int index) { return &mObj[index]; }

/*
 * --INFO--
 * Address:	802B88D8
 * Size:	000080
 */
void Mgr::loadTexData()
{
	mChangeTexture = nullptr;
	LoadResource::Arg loadArg(cOtakaraChangeTexName);
	LoadResource::Node* resource = gLoadResourceMgr->load(loadArg);
	if (resource) {
		mChangeTexture = static_cast<ResTIMG*>(resource->mFile);
	}
	P2ASSERTLINE(83, mChangeTexture);
}

} // namespace WaterOtakara
} // namespace Game
