#include "Game/Entities/OtakaraBase.h"
#include "Game/Entities/Bomb.h"
#include "Game/EnemyFunc.h"
#include "Game/generalEnemyMgr.h"
#include "Game/ConditionNotStick.h"
#include "efx/TOta.h"

namespace Game {
namespace OtakaraBase {

/*
 * --INFO--
 * Address:	802B624C
 * Size:	000130
 */
Obj::Obj()
{
	mAnimator = new ProperAnimator();
	setFSM(new FSM);
}

/*
 * --INFO--
 * Address:	802B637C
 * Size:	000004
 */
void Obj::setInitialSetting(EnemyInitialParamBase*) { }

/*
 * --INFO--
 * Address:	802B6380
 * Size:	000104
 */
void Obj::onInit(CreatureInitArg* initArg)
{
	EnemyBase::onInit(initArg);

	mNextState = OTA_Null;
	_2C4       = 0.0f;
	resetTreasure();
	_2D0            = 0;
	_2C8            = 12800.0f;
	mEscapeSfxTimer = 0.0f;
	setupEffect();

	if (getEnemyTypeID() == EnemyTypeID::EnemyID_BombOtakara) {
		disableEvent(0, EB_LifegaugeVisible);
		disableEvent(0, EB_ToLeaveCarcass);

		if (mDropGroup == EDG_None) {
			initBombOtakara();
		}

		mFsm->start(this, 11, nullptr);
		return;
	}

	_2E8 = 12800.0f;
	mFsm->start(this, 2, nullptr);
}

/*
 * --INFO--
 * Address:	802B6490
 * Size:	00005C
 */
void Obj::onKill(CreatureKillArg* killArg)
{
	fallTreasure(true);
	finishChargeEffect();
	EnemyBase::onKill(killArg);
}

/*
 * --INFO--
 * Address:	802B64EC
 * Size:	000034
 */
void Obj::doUpdate() { mFsm->exec(this); }

/*
 * --INFO--
 * Address:	802B6520
 * Size:	0000F0
 */
void Obj::doUpdateCommon()
{
	EnemyBase::doUpdateCommon();
	if (_2C8 < 1.0f) {
		_2C8 += sys->mDeltaTime;
		startDisChargeSE();
		attackTarget();
	}

	if (getEnemyTypeID() == EnemyTypeID::EnemyID_BombOtakara) {
		if (mTargetCreature) {
			if (!mTargetCreature->isAlive()) {
				mTargetCreature = nullptr;
				mHealth         = 0.0f;
			} else if (mTargetCreature->isStickTo()) {
				mTargetCreature->endCapture();
				mTargetCreature = nullptr;
				mHealth         = 0.0f;
			}
		} else {
			mHealth = 0.0f;
		}
	}
}

/*
 * --INFO--
 * Address:	802B6614
 * Size:	00007C
 */
void Obj::doAnimationCullingOff()
{
	EnemyBase::doAnimationCullingOff();
	if (mTreasure) {
		if (!mTreasure->isAlive()) {
			fallTreasure(false);
		} else {
			Matrixf mtx;
			PSMTXIdentity(mtx.mMatrix.mtxView);
			mtx.mMatrix.structView.ty = mBodyHeightOffset;
			mTreasure->updateCapture(mtx);
		}
	}
}

/*
 * --INFO--
 * Address:	802B6690
 * Size:	000004
 */
void Obj::doDirectDraw(Graphics&) { }

/*
 * --INFO--
 * Address:	802B6694
 * Size:	000020
 */
void Obj::doDebugDraw(Graphics& gfx) { EnemyBase::doDebugDraw(gfx); }

/*
 * --INFO--
 * Address:	802B66B4
 * Size:	00004C
 */
void Obj::setFSM(FSM* fsm)
{
	mFsm = fsm;
	mFsm->init(this);
	mCurrentLifecycleState = nullptr;
}

/*
 * --INFO--
 * Address:	802B6700
 * Size:	0000EC
 */
void Obj::getShadowParam(ShadowParam& shadowParam)
{
	Matrixf* mat          = mModel->getJoint("otakara")->getWorldMatrix();
	shadowParam.mPosition = Vector3f(mat->mMatrix.mtxView[0][3], mat->mMatrix.mtxView[1][3], mat->mMatrix.mtxView[2][3]);
	shadowParam.mPosition.y -= 5.0f;

	shadowParam.mBoundingSphere.mPosition = Vector3f(0.0f, 1.0f, 0.0f);

	if (mTreasure) {
		shadowParam.mBoundingSphere.mRadius = 30.0f;
	} else {
		shadowParam.mBoundingSphere.mRadius = 50.0f;
	}

	if (isEvent(1, EB2_IsEarthquake)) {
		shadowParam.mBoundingSphere.mRadius += 25.0f;
	}

	if (getEnemyTypeID() == EnemyTypeID::EnemyID_BombOtakara) {
		shadowParam.mSize = 12.5f;
	} else {
		shadowParam.mSize = 5.0f;
	}
}

/*
 * --INFO--
 * Address:	802B67EC
 * Size:	000034
 */
bool Obj::damageCallBack(Creature* creature, f32 damage, CollPart* collpart)
{
	if (collpart) {
		damageTreasure(damage);
		return true;
	}
	return false;
}

/*
 * --INFO--
 * Address:	802B6820
 * Size:	000078
 */
bool Obj::hipdropCallBack(Creature* creature, f32 damage, CollPart* collpart)
{
	if (collpart) {
		if (mTreasure) {
			damageTreasure(C_PARMS->mProperParms.mFp01.mValue);
		} else {
			damageTreasure(damage);
		}
	}

	return EnemyBase::hipdropCallBack(creature, 0.0f, collpart);
}

/*
 * --INFO--
 * Address:	802B6898
 * Size:	000070
 */
bool Obj::earthquakeCallBack(Creature* creature, f32 damage)
{
	if (mTreasure) {
		damageTreasure(C_PARMS->mProperParms.mFp01.mValue);
	}
	return EnemyBase::earthquakeCallBack(creature, damage);
}

/*
 * --INFO--
 * Address:	802B6908
 * Size:	000024
 */
bool Obj::bombCallBack(Game::Creature* creature, Vector3f& vec, f32 damage)
{
	damageTreasure(damage);
	return true;
}

/*
 * --INFO--
 * Address:	802B692C
 * Size:	00004C
 */
void Obj::doStartStoneState()
{
	EnemyBase::doStartStoneState();
	fallTreasure(true);
	finishChargeEffect();
}

/*
 * --INFO--
 * Address:	802B6978
 * Size:	00004C
 */
void Obj::doFinishStoneState()
{
	EnemyBase::doFinishStoneState();
	if (_2D0 != 0) {
		startChargeEffect();
	}
}

/*
 * --INFO--
 * Address:	802B69C4
 * Size:	00004C
 */
void Obj::doStartEarthquakeState(f32 p1)
{
	EnemyBase::doStartEarthquakeState(p1);
	fallTreasure(true);
	finishChargeEffect();
}

/*
 * --INFO--
 * Address:	802B6A10
 * Size:	00004C
 */
void Obj::doFinishEarthquakeState()
{
	EnemyBase::doFinishEarthquakeState();
	if (_2D0 != 0) {
		startChargeEffect();
	}
}

/*
 * --INFO--
 * Address:	802B6A5C
 * Size:	00004C
 */
void Obj::doStartEarthquakeFitState()
{
	EnemyBase::doStartEarthquakeFitState();
	fallTreasure(true);
	finishChargeEffect();
}

/*
 * --INFO--
 * Address:	802B6AA8
 * Size:	00004C
 */
void Obj::doFinishEarthquakeFitState()
{
	EnemyBase::doFinishEarthquakeFitState();
	if (_2D0 != 0) {
		startChargeEffect();
	}
}

/*
 * --INFO--
 * Address:	802B6AF4
 * Size:	000040
 */
void Obj::doStartWaitingBirthTypeDrop()
{
	EnemyBase::doStartWaitingBirthTypeDrop();
	effectDrawOff();
}

/*
 * --INFO--
 * Address:	802B6B38
 * Size:	000064
 */
void Obj::doFinishWaitingBirthTypeDrop()
{
	EnemyBase::doFinishWaitingBirthTypeDrop();
	effectDrawOn();
	if (getEnemyTypeID() == EnemyTypeID::EnemyID_BombOtakara) {
		initBombOtakara();
	}
}

/*
 * --INFO--
 * Address:	802B6BA0
 * Size:	000028
 */
void Obj::startCarcassMotion() { EnemyBase::startMotion(11, nullptr); }

/*
 * --INFO--
 * Address:	802B6BC8
 * Size:	00002C
 */
void Obj::doStartMovie() { effectDrawOff(); }

/*
 * --INFO--
 * Address:	802B6BF4
 * Size:	00002C
 */
void Obj::doEndMovie() { effectDrawOn(); }

/*
 * --INFO--
 * Address:	802B6C20
 * Size:	000140
 */
bool OtakaraBase::Obj::isMovePositionSet(bool ignoringTreasures)
{
	Creature* target = nullptr;
	if (!ignoringTreasures && (_2E8 > C_PARMS->mProperParms.mFp21.mValue)) {
		target = getNearestTreasure();
	} else {
		_2E8 += sys->mDeltaTime;
	}

	if (target) {
		mMovePosition   = target->getPosition();
		mTargetCreature = target;
	} else {
		ConditionNotStickClientAndItem condition(this, mTreasure);
		Parms* parms = C_PARMS;
		target = EnemyFunc::getNearestPikminOrNavi(this, parms->mGeneral.mViewAngle.mValue, parms->mGeneral.mSightRadius.mValue, nullptr,
		                                           nullptr, &condition);
		if (target) {
			mMovePosition = getTargetPosition(target);
		}
		mTargetCreature = nullptr;
	}

	if (target) {
		return true;
	} else {
		return false;
	}
}

/*
 * --INFO--
 * Address:	802B6D60
 * Size:	000148
 */
Pellet* OtakaraBase::Obj::getNearestTreasure()
{
	Pellet* treasure = nullptr;
	f32 sightRadius  = C_PARMS->mGeneral.mSightRadius.mValue;
	f32 minDist      = sightRadius * sightRadius;
	PelletIterator iterator;
	CI_LOOP(iterator)
	{
		Pellet* pellet = (Pellet*)(*iterator);
		if (pellet->isAlive() && (pellet->mCaptureMatrix == nullptr && pellet->isPickable())) {
			Vector3f position = pellet->getPosition();
			if (sqrDistanceXZ(position, mHomePosition) < SQUARE(*C_PARMS->mGeneral.mTerritoryRadius())) {
				Vector3f sep2 = mPosition;
				sep2 -= position;
				f32 dist2D = SQUARE(sep2.x) + SQUARE(sep2.z);
				if (dist2D < minDist) {
					treasure = pellet;
					minDist  = dist2D;
				}
			}
		}
	}
	return treasure;
}

/*
 * --INFO--
 * Address:	802B6EA8
 * Size:	0001C8
 */
Vector3f Obj::getTargetPosition(Creature* target)
{
	Vector3f otakaraPosition = getPosition();
	Vector3f targetPosition  = target->getPosition();
	Vector3f homePos         = mHomePosition;

	Vector3f sep = otakaraPosition - targetPosition;
	sep.y        = 0.0f;
	_normalise(sep);

	sep *= C_PARMS->mGeneral.mMoveSpeed.mValue;
	sep += otakaraPosition;

	f32 territory = C_PARMS->mGeneral.mTerritoryRadius.mValue;
	if (sqrDistanceXZ(sep, homePos) > SQUARE(territory)) {
		sep -= homePos;
		sep.y = 0.0f;
		_normalise(sep);
		sep *= territory;
		sep += homePos;
	}
	return sep;
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	stw      r0, 0x64(r1)
	stfd     f31, 0x50(r1)
	psq_st   f31, 88(r1), 0, qr0
	stfd     f30, 0x40(r1)
	psq_st   f30, 72(r1), 0, qr0
	stfd     f29, 0x30(r1)
	psq_st   f29, 56(r1), 0, qr0
	stw      r31, 0x2c(r1)
	stw      r30, 0x28(r1)
	stw      r29, 0x24(r1)
	lwz      r12, 0(r4)
	mr       r29, r3
	mr       r30, r4
	mr       r31, r5
	lwz      r12, 8(r12)
	addi     r3, r1, 0x14
	mtctr    r12
	bctrl
	mr       r4, r31
	addi     r3, r1, 8
	lwz      r12, 0(r31)
	lfs      f30, 0x14(r1)
	lwz      r12, 8(r12)
	lfs      f31, 0x18(r1)
	lfs      f29, 0x1c(r1)
	mtctr    r12
	bctrl
	lfs      f0, 0x10(r1)
	lfs      f2, 8(r1)
	fsubs    f1, f29, f0
	lfs      f0, lbl_8051C290@sda21(r2)
	fsubs    f8, f30, f2
	lfs      f5, 0x198(r30)
	lfs      f6, 0x19c(r30)
	fmuls    f3, f1, f1
	fmadds   f2, f8, f8, f0
	lfs      f7, 0x1a0(r30)
	fadds    f3, f3, f2
	fcmpo    cr0, f3, f0
	ble      lbl_802B6F60
	ble      lbl_802B6F64
	frsqrte  f2, f3
	fmuls    f3, f2, f3
	b        lbl_802B6F64

lbl_802B6F60:
	fmr      f3, f0

lbl_802B6F64:
	lfs      f2, lbl_8051C290@sda21(r2)
	fcmpo    cr0, f3, f2
	ble      lbl_802B6F84
	lfs      f2, lbl_8051C298@sda21(r2)
	fdivs    f2, f2, f3
	fmuls    f8, f8, f2
	fmuls    f0, f0, f2
	fmuls    f1, f1, f2

lbl_802B6F84:
	lwz      r3, 0xc0(r30)
	lfs      f2, 0x2e4(r3)
	lfs      f9, 0x35c(r3)
	fmuls    f1, f1, f2
	fmuls    f8, f8, f2
	fmuls    f0, f0, f2
	fadds    f1, f1, f29
	fadds    f8, f8, f30
	fmuls    f2, f9, f9
	fsubs    f3, f1, f7
	fsubs    f4, f8, f5
	fadds    f0, f0, f31
	fmuls    f3, f3, f3
	fmadds   f3, f4, f4, f3
	fcmpo    cr0, f3, f2
	ble      lbl_802B7030
	fsubs    f1, f1, f7
	lfs      f0, lbl_8051C290@sda21(r2)
	fsubs    f8, f8, f5
	fmuls    f3, f1, f1
	fmadds   f2, f8, f8, f0
	fadds    f3, f3, f2
	fcmpo    cr0, f3, f0
	ble      lbl_802B6FF4
	ble      lbl_802B6FF8
	frsqrte  f2, f3
	fmuls    f3, f2, f3
	b        lbl_802B6FF8

lbl_802B6FF4:
	fmr      f3, f0

lbl_802B6FF8:
	lfs      f2, lbl_8051C290@sda21(r2)
	fcmpo    cr0, f3, f2
	ble      lbl_802B7018
	lfs      f2, lbl_8051C298@sda21(r2)
	fdivs    f2, f2, f3
	fmuls    f8, f8, f2
	fmuls    f0, f0, f2
	fmuls    f1, f1, f2

lbl_802B7018:
	fmuls    f8, f8, f9
	fmuls    f0, f0, f9
	fmuls    f1, f1, f9
	fadds    f8, f8, f5
	fadds    f0, f0, f6
	fadds    f1, f1, f7

lbl_802B7030:
	stfs     f8, 0(r29)
	stfs     f0, 4(r29)
	stfs     f1, 8(r29)
	psq_l    f31, 88(r1), 0, qr0
	lfd      f31, 0x50(r1)
	psq_l    f30, 72(r1), 0, qr0
	lfd      f30, 0x40(r1)
	psq_l    f29, 56(r1), 0, qr0
	lfd      f29, 0x30(r1)
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	lwz      r0, 0x64(r1)
	lwz      r29, 0x24(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

/*
 * --INFO--
 * Address:	802B7070
 * Size:	000094
 */
void Obj::resetTreasure()
{
	mTreasure         = nullptr;
	mTreasureHealth   = 0.0f;
	mBodyHeightOffset = 0.0f;
	mCellRadius       = C_PARMS->mGeneral.mCellRadius.mValue;

	CollPart* collpart  = mCollTree->getCollPart('body');
	collpart->mRadius   = 10.0f;
	collpart->mOffset.y = 0.0f;

	CollPart* basepart  = mCollTree->mPart;
	basepart->mRadius   = 20.0f;
	basepart->mOffset.y = 0.0f;

	EnemyFunc::flickStickPikmin(this, 1.0f, 0.0f, 0.0f, -1000.0f, nullptr);
}

/*
 * --INFO--
 * Address:	802B7104
 * Size:	00010C
 */
bool Obj::isTakeTreasure()
{
	Pellet* target = static_cast<Pellet*>(mTargetCreature);
	if (target) {
		Vector3f targetPos = target->getPosition();
		f32 radius         = 20.0f + target->getPickRadius();
		if (radius < 50.0f) {
			radius = 50.0f;
		}

		if (_distanceBetween2(targetPos, mPosition) < radius) {
			return true;
		}
	}
	return false;
}

/*
 * --INFO--
 * Address:	802B7210
 * Size:	00024C
 */
bool Obj::takeTreasure()
{
	Creature* target = mTargetCreature;
	if (target) {
		bool check;
		if (target->isAlive() && !target->mCaptureMatrix && target->isPellet() && static_cast<Pellet*>(target)->isPickable()
		    && isTakeTreasure()) {
			mTreasure         = target;
			mTreasureHealth   = C_PROPERPARMS.mFp01.mValue;
			mBodyHeightOffset = 0.5f * static_cast<Pellet*>(target)->getCylinderHeight();
			mCellRadius       = static_cast<Pellet*>(target)->getPickRadius();

			CollPart* bodyPart  = mCollTree->getCollPart('body');
			bodyPart->mRadius   = static_cast<Pellet*>(target)->getPickRadius();
			bodyPart->mOffset.y = mBodyHeightOffset;

			CollPart* basePart  = mCollTree->mPart;
			basePart->mRadius   = 10.0f + static_cast<Pellet*>(target)->getPickRadius();
			basePart->mOffset.y = mBodyHeightOffset;
			mCellRadius += 10.0f;
			check = true;
		} else {
			check = false;
		}

		if (check) {
			mTreasure->startCapture(mModel->getJoint("otakara")->getWorldMatrix());
			return true;
		}
	}
	return false;
}

/*
 * --INFO--
 * Address:	802B745C
 * Size:	0000F8
 */
bool Obj::fallTreasure(bool check)
{
	if (mTreasure) {
		mTreasure->endCapture();
		if (check) {
			Vector3f velocity(0.0f, 100.0f, 0.0f);
			mTreasure->setVelocity(velocity);
		}

		createTreasureFallEffect();
		resetTreasure();
		return true;
	}
	return false;
}

/*
 * --INFO--
 * Address:	802B7554
 * Size:	000028
 */
bool Obj::isDropTreasure()
{
	// != 0.0f gives incorrect asm smh
	if ((mTreasureHealth) && (mTreasureHealth > 0.0f)) {
		return false;
	}
	return true;
}

/*
 * --INFO--
 * Address:	802B757C
 * Size:	000054
 */
void Obj::damageTreasure(f32 damage)
{
	if (mTreasure) {
		mTreasureHealth -= damage;
		if (mTreasureHealth < 0.0f) {
			mTreasureHealth = 0.0f;
		}
		return;
	}

	addDamage(damage, 1.0f);
}

/*
 * --INFO--
 * Address:	802B75D0
 * Size:	0001A8
 */
void Obj::attackTarget()
{
	f32 maxRange = getMaxAttackHeight();
	f32 minRange = getMinAttackHeight();
	f32 radius   = C_PARMS->mGeneral.mAttackRadius.mValue;

	f32 dist = SQUARE(radius);

	Sys::Sphere sphere;
	sphere.mPosition = mPosition;
	sphere.mRadius   = radius;

	CellIteratorArg iterArg(sphere);
	iterArg._1C = 1;
	CellIterator iter(iterArg);

	CI_LOOP(iter)
	{
		Creature* target = static_cast<Creature*>(*iter);
		if (target->isAlive() && (target->isNavi() || target->isPiki())) {
			Vector3f targetPos = target->getPosition();
			if (maxRange > targetPos.y && minRange < targetPos.y && sqrDistanceXZ(mPosition, targetPos) < dist) {
				interactCreature(target);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	802B777C
 * Size:	000134
 */
void Obj::createTreasureFallEffect()
{
	Matrixf* mtx         = mModel->getJoint("center")->getWorldMatrix();
	Vector3f translation = Vector3f(mtx->mMatrix.structView.tx, mtx->mMatrix.structView.ty, mtx->mMatrix.structView.tz);

	f32 scale = 0.0285f * (mCellRadius - 10.0f);
	if (scale < 1.0f) {
		scale = 0.5f * (1.0f + scale);
	}

	efx::ArgScale arg(translation, scale);
	efx::TOtaPartsoff treasureFallFX;

	treasureFallFX.create(&arg);
	getJAIObject()->startSound(PSSE_EN_OTAKARA_DROP_ITEM, 0);
}

/*
 * --INFO--
 * Address:	802B78B0
 * Size:	000088
 */
void Obj::startEscapeSE()
{
	if (mTargetCreature == nullptr) {
		if (mEscapeSfxTimer > 3.0f) {
			getJAIObject()->startSound(PSSE_EN_OTAKARA_STANDUP, 0);
			mEscapeSfxTimer = 0.0f;
		} else {
			mEscapeSfxTimer += sys->mDeltaTime;
		}
	}
}

/*
 * --INFO--
 * Address:	802B7938
 * Size:	0000FC
 */
void Obj::initBombOtakara()
{
	if (mTargetCreature != nullptr) {
		return;
	}

	Bomb::Mgr* mgr = static_cast<Bomb::Mgr*>(generalEnemyMgr->getEnemyMgr(EnemyTypeID::EnemyID_Bomb));
	if (!mgr) {
		return;
	}

	EnemyBirthArg birthArg;
	birthArg.mFaceDir = mFaceDir;
	mTargetCreature   = mgr->birth(birthArg);
	if (mTargetCreature) {
		mTargetCreature->init(nullptr);
		mTargetCreature->startCapture(mModel->getJoint("otakara")->getWorldMatrix());
		static_cast<Bomb::Obj*>(mTargetCreature)->mOtakara = this;
		mBodyHeightOffset                                  = 10.0f;
		mCellRadius                                        = 25.0f;

		CollPart* collpart  = mCollTree->getCollPart('body');
		collpart->mRadius   = 15.0f;
		collpart->mOffset.y = mBodyHeightOffset;

		CollPart* basepart  = mCollTree->mPart;
		basepart->mRadius   = 25.0f;
		basepart->mOffset.y = mBodyHeightOffset;
	}
}

/*
 * --INFO--
 * Address:	802B7A34
 * Size:	000068
 */
bool Obj::isTransitChaseState()
{
	if (isEvent(0, EB_HasCollisionOccurred) || isEvent(0, EB_IsTakingDamage) || (mStuckPikminCount != 0)) {
		return true;
	}

	Parms* parms = C_PARMS;
	Navi* navi = EnemyFunc::getNearestNavi(this, parms->mGeneral.mViewAngle.mValue, parms->mGeneral.mSightRadius.mValue, nullptr, nullptr);
	return (navi != nullptr);
}

/*
 * --INFO--
 * Address:	802B7A9C
 * Size:	00008C
 */
bool Obj::stimulateBomb()
{
	_2E8 += sys->mDeltaTime;
	if ((_2E8 > 1.5f) && (mTargetCreature != nullptr) && (mTargetCreature->isAlive())) {
		disableEvent(0, EB_IsCullable);
		static_cast<Bomb::Obj*>(mTargetCreature)->forceBomb();
	}

	return isEvent(0, EB_IsCullable);
}

/*
 * --INFO--
 * Address:	802B7B28
 * Size:	000038
 */
Creature* Obj::getChaseTargetCreature()
{
	return EnemyFunc::getNearestPikminOrNavi(this, C_PARMS->mGeneral.mViewAngle.mValue, C_PARMS->mGeneral.mSightRadius.mValue, nullptr,
	                                         nullptr, nullptr);
}
} // namespace OtakaraBase
} // namespace Game
