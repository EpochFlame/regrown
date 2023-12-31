#include "Game/Entities/Hanachirashi.h"
#include "Game/EnemyAnimKeyEvent.h"
#include "Game/EnemyFunc.h"
#include "Game/MapMgr.h"

namespace Game {
namespace Hanachirashi {
/*
 * --INFO--
 * Address:	8029F228
 * Size:	000480
 */
void FSM::init(EnemyBase* enemy)
{
	create(HANACHIRASHI_StateCount);
	registerState(new StateDead);
	registerState(new StateWait);
	registerState(new StateMove);
	registerState(new StateChase);
	registerState(new StateChaseInside);
	registerState(new StateAttack);
	registerState(new StateFall);
	registerState(new StateLand);
	registerState(new StateGround);
	registerState(new StateTakeOff);
	registerState(new StateFlyFlick);
	registerState(new StateGroundFlick);
}

/*
 * --INFO--
 * Address:	8029F6A8
 * Size:	0000AC
 */
void StateDead::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->disableEvent(0, EB_IsCullable);
	hanachirashi->disableEvent(0, EB_IsDamageAnimAllowed);
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->deathProcedure();

	if (hanachirashi->isFlying()) {
		hanachirashi->startMotion(0, nullptr);
	} else {
		hanachirashi->startMotion(1, nullptr);
	}

	hanachirashi->enableEvent(0, EB_IsFlying);
	hanachirashi->startDeadEffect();
}

/*
 * --INFO--
 * Address:	8029F754
 * Size:	0000B8
 */
void StateDead::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	if (!hanachirashi->getCurrAnimIndex()) {
		if (hanachirashi->getMotionFrame() > 45.0f) {
			hanachirashi->subShadowRadius();
		}
	}

	else if (hanachirashi->getMotionFrame() > 45.0f) {
		hanachirashi->subShadowRadius();
	}

	if (hanachirashi->mCurAnim->mIsPlaying && hanachirashi->mCurAnim->mType == KEYEVENT_END) {
		hanachirashi->throwupItem();
		hanachirashi->finishWindEffect();
		hanachirashi->kill(nullptr);
	}
}

/*
 * --INFO--
 * Address:	8029F80C
 * Size:	000004
 */
void StateDead::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	8029F810
 * Size:	000054
 */
void StateWait::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi             = OBJ(enemy);
	hanachirashi->_2C4            = 0.0f;
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->enableEvent(0, EB_IsFlying);
	hanachirashi->startMotion(5, nullptr);
}

/*
 * --INFO--
 * Address:	8029F864
 * Size:	000138
 */
void StateWait::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->setHeightVelocity();

	Creature* target = hanachirashi->getSearchedPikmin();
	if (!target) {
		target = hanachirashi->isAttackable();
	}

	if (target) {
		hanachirashi->mTargetCreature = target;
		transit(hanachirashi, HANACHIRASHI_Chase, nullptr);

	} else if (hanachirashi->_2C4 > CG_PROPERPARMS(hanachirashi).mFp03.mValue) {
		transit(hanachirashi, HANACHIRASHI_Move, nullptr);
	}

	hanachirashi->_2C4 += sys->mDeltaTime;

	StateID nextState = hanachirashi->getFlyingNextState();

	if (nextState >= 0) {
		transit(hanachirashi, nextState, nullptr);
		return;
	}

	if (hanachirashi->mCurAnim->mIsPlaying && hanachirashi->mCurAnim->mType == KEYEVENT_END) {
		transit(hanachirashi, HANACHIRASHI_Wait, nullptr);
	}
}

/*
 * --INFO--
 * Address:	8029F99C
 * Size:	000004
 */
void StateWait::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	8029F9A0
 * Size:	00004C
 */
void StateMove::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->setRandTarget();
	hanachirashi->_2C4            = 0.0f;
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->enableEvent(0, EB_IsFlying);
}

/*
 * --INFO--
 * Address:	8029F9EC
 * Size:	0001A0
 */
void StateMove::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->setHeightVelocity();

	// this bit is being weird
	Vector3f pos       = hanachirashi->getPosition();
	f32 sqrDist        = sqrDistanceXZ(pos, hanachirashi->mTargetPosition);
	Vector3f targetPos = hanachirashi->mTargetPosition;

	Creature* target = hanachirashi->getSearchedPikmin();
	if (target) {
		hanachirashi->mTargetCreature = target;
		transit(hanachirashi, HANACHIRASHI_Chase, nullptr);
	} else if (sqrDist < 10000.0f || hanachirashi->_2C4 > 7.5f) {
		hanachirashi->mTargetVelocity = Vector3f(0.0f);
		hanachirashi->finishMotion();
	} else {
		EnemyFunc::walkToTarget(hanachirashi, targetPos, CG_PARMS(hanachirashi)->mGeneral.mMoveSpeed.mValue,
		                        CG_PARMS(hanachirashi)->mGeneral.mRotationalAccel.mValue,
		                        CG_PARMS(hanachirashi)->mGeneral.mRotationalSpeed.mValue);
	}

	hanachirashi->_2C4 += sys->mDeltaTime;

	StateID nextState = hanachirashi->getFlyingNextState();

	if (nextState >= 0) {
		transit(hanachirashi, nextState, nullptr);
		return;
	}

	if (hanachirashi->mCurAnim->mIsPlaying && hanachirashi->mCurAnim->mType == KEYEVENT_END) {
		transit(hanachirashi, HANACHIRASHI_Wait, nullptr);
	}
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stfd     f31, 0x30(r1)
	psq_st   f31, 56(r1), 0, qr0
	stw      r31, 0x2c(r1)
	stw      r30, 0x28(r1)
	mr       r31, r4
	mr       r30, r3
	mr       r3, r31
	bl       setHeightVelocity__Q34Game12Hanachirashi3ObjFv
	mr       r4, r31
	addi     r3, r1, 8
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f0, 0x10(r1)
	mr       r3, r31
	lfs      f5, 0x2e0(r31)
	lfs      f1, 0x2d8(r31)
	fsubs    f2, f0, f5
	lfs      f0, 8(r1)
	lfs      f4, 0x2dc(r31)
	fsubs    f3, f0, f1
	fmuls    f0, f2, f2
	stfs     f1, 0x14(r1)
	stfs     f4, 0x18(r1)
	fmadds   f31, f3, f3, f0
	stfs     f5, 0x1c(r1)
	bl       getSearchedPikmin__Q34Game12Hanachirashi3ObjFv
	cmplwi   r3, 0
	beq      lbl_8029FA98
	stw      r3, 0x230(r31)
	mr       r3, r30
	mr       r4, r31
	li       r5, 3
	lwz      r12, 0(r30)
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_8029FAEC

lbl_8029FA98:
	lfs      f0, lbl_8051BD64@sda21(r2)
	fcmpo    cr0, f31, f0
	blt      lbl_8029FAB4
	lfs      f1, 0x2c4(r31)
	lfs      f0, lbl_8051BD68@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_8029FAD0

lbl_8029FAB4:
	lfs      f0, lbl_8051BD58@sda21(r2)
	mr       r3, r31
	stfs     f0, 0x1d4(r31)
	stfs     f0, 0x1d8(r31)
	stfs     f0, 0x1dc(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv
	b        lbl_8029FAEC

lbl_8029FAD0:
	lwz      r5, 0xc0(r31)
	mr       r3, r31
	addi     r4, r1, 0x14
	lfs      f1, 0x2e4(r5)
	lfs      f2, 0x30c(r5)
	lfs      f3, 0x334(r5)
	bl "walkToTarget__Q24Game9EnemyFuncFPQ24Game9EnemyBaseR10Vector3<f>fff"

lbl_8029FAEC:
	lwz      r4, sys@sda21(r13)
	mr       r3, r31
	lfs      f1, 0x2c4(r31)
	lfs      f0, 0x54(r4)
	fadds    f0, f1, f0
	stfs     f0, 0x2c4(r31)
	bl       getFlyingNextState__Q34Game12Hanachirashi3ObjFv
	or.      r5, r3, r3
	blt      lbl_8029FB30
	lwz      r12, 0(r30)
	mr       r3, r30
	mr       r4, r31
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_8029FB6C

lbl_8029FB30:
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_8029FB6C
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 0x3e8
	bne      lbl_8029FB6C
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 1
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_8029FB6C:
	psq_l    f31, 56(r1), 0, qr0
	lwz      r0, 0x44(r1)
	lfd      f31, 0x30(r1)
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	8029FB8C
 * Size:	000004
 */
void StateMove::cleanup(EnemyBase* enemy) { }

/*
 * --INFO--
 * Address:	8029FB90
 * Size:	000030
 */
void StateChase::init(EnemyBase* enemy, StateArg* stateArg)
{
	enemy->enableEvent(0, EB_IsFlying);
	enemy->setEmotionExcitement();
}

/*
 * --INFO--
 * Address:	8029FBC0
 * Size:	000530
 */
void StateChase::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->setHeightVelocity();

	if (!hanachirashi->isFinishMotion()) {
		Creature* target = hanachirashi->mTargetCreature;
		if (target) {
			// need to decomp this bit
		}

		Creature* attackTarget = hanachirashi->isAttackable();
		if (attackTarget) {
			hanachirashi->mTargetCreature = attackTarget;
			hanachirashi->mTargetVelocity = Vector3f(0.0f);
			hanachirashi->finishMotion();
		}
	}

	StateID nextState = hanachirashi->getFlyingNextState();

	if (nextState >= 0) {
		transit(hanachirashi, nextState, nullptr);
		return;
	}

	if (hanachirashi->mCurAnim->mIsPlaying && hanachirashi->mCurAnim->mType == KEYEVENT_END) {
		if (hanachirashi->mTargetCreature) {
			transit(hanachirashi, HANACHIRASHI_Attack, nullptr);
		} else {
			transit(hanachirashi, HANACHIRASHI_Wait, nullptr);
		}
	}
	/*
	stwu     r1, -0x130(r1)
	mflr     r0
	stw      r0, 0x134(r1)
	stfd     f31, 0x120(r1)
	psq_st   f31, 296(r1), 0, qr0
	stfd     f30, 0x110(r1)
	psq_st   f30, 280(r1), 0, qr0
	stfd     f29, 0x100(r1)
	psq_st   f29, 264(r1), 0, qr0
	stfd     f28, 0xf0(r1)
	psq_st   f28, 248(r1), 0, qr0
	stfd     f27, 0xe0(r1)
	psq_st   f27, 232(r1), 0, qr0
	stfd     f26, 0xd0(r1)
	psq_st   f26, 216(r1), 0, qr0
	stfd     f25, 0xc0(r1)
	psq_st   f25, 200(r1), 0, qr0
	stfd     f24, 0xb0(r1)
	psq_st   f24, 184(r1), 0, qr0
	stfd     f23, 0xa0(r1)
	psq_st   f23, 168(r1), 0, qr0
	stfd     f22, 0x90(r1)
	psq_st   f22, 152(r1), 0, qr0
	stw      r31, 0x8c(r1)
	stw      r30, 0x88(r1)
	stw      r29, 0x84(r1)
	mr       r31, r4
	mr       r30, r3
	mr       r3, r31
	bl       setHeightVelocity__Q34Game12Hanachirashi3ObjFv
	mr       r3, r31
	bl       isFinishMotion__Q24Game9EnemyBaseFv
	clrlwi.  r0, r3, 0x18
	bne      lbl_8029FFE8
	lwz      r29, 0x230(r31)
	cmplwi   r29, 0
	beq      lbl_8029FFBC
	mr       r4, r31
	addi     r3, r1, 0x50
	lwz      r12, 0(r31)
	lfs      f28, 0x198(r31)
	lwz      r12, 8(r12)
	lfs      f27, 0x1a0(r31)
	mtctr    r12
	bctrl
	mr       r4, r29
	addi     r3, r1, 0x44
	lwz      r12, 0(r29)
	lfs      f26, 0x50(r1)
	lwz      r12, 8(r12)
	lfs      f25, 0x58(r1)
	mtctr    r12
	bctrl
	lfs      f5, 0x44(r1)
	lfs      f6, 0x4c(r1)
	fsubs    f3, f26, f5
	lfs      f1, lbl_8051BD58@sda21(r2)
	fsubs    f4, f25, f6
	fmadds   f0, f3, f3, f1
	fmuls    f2, f4, f4
	fadds    f2, f2, f0
	fcmpo    cr0, f2, f1
	ble      lbl_8029FCCC
	ble      lbl_8029FCD0
	frsqrte  f0, f2
	fmuls    f2, f0, f2
	b        lbl_8029FCD0

lbl_8029FCCC:
	fmr      f2, f1

lbl_8029FCD0:
	lfs      f0, lbl_8051BD58@sda21(r2)
	fcmpo    cr0, f2, f0
	ble      lbl_8029FCEC
	lfs      f0, lbl_8051BD6C@sda21(r2)
	fdivs    f0, f0, f2
	fmuls    f3, f3, f0
	fmuls    f4, f4, f0

lbl_8029FCEC:
	lwz      r4, 0xc0(r31)
	lis      r3, atanTable___5JMath@ha
	addi     r3, r3, atanTable___5JMath@l
	lfs      f0, 0x564(r4)
	fmuls    f3, f3, f0
	fmuls    f4, f4, f0
	fadds    f24, f5, f3
	fadds    f23, f6, f4
	fsubs    f1, f24, f26
	fsubs    f2, f23, f25
	bl       "atan2___Q25JMath18TAtanTable<1024,f>CFff"
	lwz      r12, 0(r29)
	fmr      f29, f1
	lwz      r5, 0xc0(r31)
	mr       r4, r29
	lwz      r12, 8(r12)
	addi     r3, r1, 0x20
	lfs      f30, 0x334(r5)
	lfs      f31, 0x30c(r5)
	mtctr    r12
	bctrl
	mr       r4, r31
	lfs      f2, 0x20(r1)
	lwz      r12, 0(r31)
	addi     r3, r1, 0x2c
	lfs      f1, 0x24(r1)
	lfs      f0, 0x28(r1)
	lwz      r12, 8(r12)
	stfs     f2, 8(r1)
	stfs     f1, 0xc(r1)
	stfs     f0, 0x10(r1)
	mtctr    r12
	bctrl
	lfs      f5, 0x2c(r1)
	lis      r3, atanTable___5JMath@ha
	lfs      f3, 0x34(r1)
	addi     r3, r3, atanTable___5JMath@l
	lfs      f1, 8(r1)
	lfs      f0, 0x10(r1)
	lfs      f4, 0x30(r1)
	fsubs    f1, f1, f5
	fsubs    f2, f0, f3
	stfs     f5, 0x14(r1)
	stfs     f4, 0x18(r1)
	stfs     f3, 0x1c(r1)
	bl       "atan2___Q25JMath18TAtanTable<1024,f>CFff"
	bl       roundAng__Ff
	lwz      r12, 0(r31)
	fmr      f22, f1
	mr       r3, r31
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fmr      f2, f1
	fmr      f1, f22
	bl       angDist__Fff
	fmuls    f31, f1, f31
	lfs      f0, lbl_8051BD74@sda21(r2)
	lfs      f1, lbl_8051BD70@sda21(r2)
	fmuls    f0, f0, f30
	fabs     f2, f31
	fmuls    f1, f1, f0
	frsp     f0, f2
	fcmpo    cr0, f0, f1
	ble      lbl_8029FE08
	lfs      f0, lbl_8051BD58@sda21(r2)
	fcmpo    cr0, f31, f0
	ble      lbl_8029FE04
	fmr      f31, f1
	b        lbl_8029FE08

lbl_8029FE04:
	fneg     f31, f1

lbl_8029FE08:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fadds    f1, f31, f1
	bl       roundAng__Ff
	fsubs    f3, f25, f23
	stfs     f1, 0x1fc(r31)
	fsubs    f4, f26, f24
	lfs      f0, lbl_8051BD78@sda21(r2)
	lfs      f2, 0x1fc(r31)
	fmuls    f1, f3, f3
	stfs     f2, 0x1a8(r31)
	fmadds   f1, f4, f4, f1
	fcmpo    cr0, f1, f0
	ble      lbl_8029FF1C
	lfs      f0, lbl_8051BD58@sda21(r2)
	lwz      r4, 0xc0(r31)
	fcmpo    cr0, f29, f0
	lfs      f3, 0x2e4(r4)
	bge      lbl_8029FE8C
	lfs      f0, lbl_8051BD7C@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f29, f0
	fctiwz   f0, f0
	stfd     f0, 0x60(r1)
	lwz      r0, 0x64(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f2, f0
	b        lbl_8029FEB0

lbl_8029FE8C:
	lfs      f0, lbl_8051BD80@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f29, f0
	fctiwz   f0, f0
	stfd     f0, 0x68(r1)
	lwz      r0, 0x6c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f2, r3, r0

lbl_8029FEB0:
	lfs      f0, lbl_8051BD58@sda21(r2)
	fmuls    f3, f3, f2
	lfs      f1, 0x1d4(r31)
	lfs      f2, 0x1d8(r31)
	fcmpo    cr0, f29, f0
	lfs      f0, 0x1dc(r31)
	stfs     f1, 0x38(r1)
	stfs     f2, 0x3c(r1)
	stfs     f0, 0x40(r1)
	bge      lbl_8029FEDC
	fneg     f29, f29

lbl_8029FEDC:
	lfs      f0, lbl_8051BD80@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	lfs      f1, 0x2e4(r4)
	fmuls    f0, f29, f0
	fctiwz   f0, f0
	stfd     f0, 0x70(r1)
	lwz      r0, 0x74(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r3, r0
	lfs      f0, 4(r3)
	stfs     f3, 0x1d4(r31)
	fmuls    f0, f1, f0
	stfs     f2, 0x1d8(r31)
	stfs     f0, 0x1dc(r31)
	b        lbl_8029FF2C

lbl_8029FF1C:
	lfs      f0, lbl_8051BD58@sda21(r2)
	stfs     f0, 0x1d4(r31)
	stfs     f0, 0x1d8(r31)
	stfs     f0, 0x1dc(r31)

lbl_8029FF2C:
	fsubs    f1, f25, f27
	lwz      r3, 0xc0(r31)
	fsubs    f2, f26, f28
	lfs      f0, 0x35c(r3)
	fmuls    f1, f1, f1
	fmuls    f0, f0, f0
	fmadds   f1, f2, f2, f1
	fcmpo    cr0, f1, f0
	ble      lbl_8029FF74
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 4
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_8029FFBC

lbl_8029FF74:
	mr       r3, r31
	bl       isTargetLost__Q34Game12Hanachirashi3ObjFv
	clrlwi.  r0, r3, 0x18
	beq      lbl_8029FFBC
	mr       r3, r31
	bl       getSearchedPikmin__Q34Game12Hanachirashi3ObjFv
	cmplwi   r3, 0
	beq      lbl_8029FF9C
	stw      r3, 0x230(r31)
	b        lbl_8029FFBC

lbl_8029FF9C:
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 1
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_8029FFBC:
	mr       r3, r31
	bl       isAttackable__Q34Game12Hanachirashi3ObjFv
	cmplwi   r3, 0
	beq      lbl_8029FFE8
	stw      r3, 0x230(r31)
	mr       r3, r31
	lfs      f0, lbl_8051BD58@sda21(r2)
	stfs     f0, 0x1d4(r31)
	stfs     f0, 0x1d8(r31)
	stfs     f0, 0x1dc(r31)
	bl       finishMotion__Q24Game9EnemyBaseFv

lbl_8029FFE8:
	mr       r3, r31
	bl       getFlyingNextState__Q34Game12Hanachirashi3ObjFv
	or.      r5, r3, r3
	blt      lbl_802A0018
	lwz      r12, 0(r30)
	mr       r3, r30
	mr       r4, r31
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A0084

lbl_802A0018:
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_802A0084
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 0x3e8
	bne      lbl_802A0084
	lwz      r0, 0x230(r31)
	cmplwi   r0, 0
	beq      lbl_802A0064
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 5
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A0084

lbl_802A0064:
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 1
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802A0084:
	psq_l    f31, 296(r1), 0, qr0
	lfd      f31, 0x120(r1)
	psq_l    f30, 280(r1), 0, qr0
	lfd      f30, 0x110(r1)
	psq_l    f29, 264(r1), 0, qr0
	lfd      f29, 0x100(r1)
	psq_l    f28, 248(r1), 0, qr0
	lfd      f28, 0xf0(r1)
	psq_l    f27, 232(r1), 0, qr0
	lfd      f27, 0xe0(r1)
	psq_l    f26, 216(r1), 0, qr0
	lfd      f26, 0xd0(r1)
	psq_l    f25, 200(r1), 0, qr0
	lfd      f25, 0xc0(r1)
	psq_l    f24, 184(r1), 0, qr0
	lfd      f24, 0xb0(r1)
	psq_l    f23, 168(r1), 0, qr0
	lfd      f23, 0xa0(r1)
	psq_l    f22, 152(r1), 0, qr0
	lfd      f22, 0x90(r1)
	lwz      r31, 0x8c(r1)
	lwz      r30, 0x88(r1)
	lwz      r0, 0x134(r1)
	lwz      r29, 0x84(r1)
	mtlr     r0
	addi     r1, r1, 0x130
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A00F0
 * Size:	000024
 */
void StateChase::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802A0114
 * Size:	000124
 */
void StateChaseInside::init(EnemyBase* enemy, StateArg* stateArg)
{
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stfd     f31, 0x30(r1)
	psq_st   f31, 56(r1), 0, qr0
	stfd     f30, 0x20(r1)
	psq_st   f30, 40(r1), 0, qr0
	stw      r31, 0x1c(r1)
	mr       r31, r4
	lwz      r4, 0x230(r4)
	lfs      f31, 0x198(r31)
	cmplwi   r4, 0
	lfs      f0, 0x19c(r31)
	lfs      f30, 0x1a0(r31)
	beq      lbl_802A01F4
	lwz      r12, 0(r4)
	addi     r3, r1, 8
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f6, 8(r1)
	lfs      f7, 0x10(r1)
	fsubs    f3, f31, f6
	lfs      f4, lbl_8051BD58@sda21(r2)
	fsubs    f5, f30, f7
	lfs      f2, 0xc(r1)
	fmadds   f0, f3, f3, f4
	fmuls    f1, f5, f5
	fadds    f1, f1, f0
	fcmpo    cr0, f1, f4
	ble      lbl_802A01A0
	ble      lbl_802A01A4
	frsqrte  f0, f1
	fmuls    f1, f0, f1
	b        lbl_802A01A4

lbl_802A01A0:
	fmr      f1, f4

lbl_802A01A4:
	lfs      f0, lbl_8051BD58@sda21(r2)
	fcmpo    cr0, f1, f0
	ble      lbl_802A01C4
	lfs      f0, lbl_8051BD6C@sda21(r2)
	fdivs    f0, f0, f1
	fmuls    f3, f3, f0
	fmuls    f4, f4, f0
	fmuls    f5, f5, f0

lbl_802A01C4:
	lwz      r3, 0xc0(r31)
	lfs      f0, 0x3d4(r3)
	fmuls    f3, f3, f0
	fmuls    f4, f4, f0
	fmuls    f5, f5, f0
	fadds    f0, f6, f3
	fadds    f2, f2, f4
	fadds    f1, f7, f5
	stfs     f0, 0x2d8(r31)
	stfs     f2, 0x2dc(r31)
	stfs     f1, 0x2e0(r31)
	b        lbl_802A0200

lbl_802A01F4:
	stfs     f31, 0x2d8(r31)
	stfs     f0, 0x2dc(r31)
	stfs     f30, 0x2e0(r31)

lbl_802A0200:
	lwz      r0, 0x1e0(r31)
	mr       r3, r31
	ori      r0, r0, 4
	stw      r0, 0x1e0(r31)
	bl       setEmotionExcitement__Q24Game9EnemyBaseFv
	psq_l    f31, 56(r1), 0, qr0
	lfd      f31, 0x30(r1)
	psq_l    f30, 40(r1), 0, qr0
	lfd      f30, 0x20(r1)
	lwz      r0, 0x44(r1)
	lwz      r31, 0x1c(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A0238
 * Size:	00037C
 */
void StateChaseInside::exec(EnemyBase* enemy)
{
	/*
	stwu     r1, -0xe0(r1)
	mflr     r0
	stw      r0, 0xe4(r1)
	stfd     f31, 0xd0(r1)
	psq_st   f31, 216(r1), 0, qr0
	stfd     f30, 0xc0(r1)
	psq_st   f30, 200(r1), 0, qr0
	stfd     f29, 0xb0(r1)
	psq_st   f29, 184(r1), 0, qr0
	stfd     f28, 0xa0(r1)
	psq_st   f28, 168(r1), 0, qr0
	stfd     f27, 0x90(r1)
	psq_st   f27, 152(r1), 0, qr0
	stfd     f26, 0x80(r1)
	psq_st   f26, 136(r1), 0, qr0
	stfd     f25, 0x70(r1)
	psq_st   f25, 120(r1), 0, qr0
	stw      r31, 0x6c(r1)
	stw      r30, 0x68(r1)
	mr       r31, r4
	mr       r30, r3
	mr       r3, r31
	bl       setHeightVelocity__Q34Game12Hanachirashi3ObjFv
	mr       r4, r31
	addi     r3, r1, 0x44
	lwz      r12, 0(r31)
	lwz      r12, 8(r12)
	mtctr    r12
	bctrl
	lfs      f31, 0x4c(r1)
	lfs      f29, 0x2e0(r31)
	lfs      f28, 0x44(r1)
	fsubs    f1, f31, f29
	lfs      f30, 0x2d8(r31)
	lfs      f0, lbl_8051BD64@sda21(r2)
	fsubs    f2, f28, f30
	fmuls    f1, f1, f1
	fmadds   f1, f2, f2, f1
	fcmpo    cr0, f1, f0
	bge      lbl_802A02FC
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 3
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A04F8

lbl_802A02FC:
	lwz      r4, 0x230(r31)
	cmplwi   r4, 0
	beq      lbl_802A0418
	lwz      r12, 0(r4)
	addi     r3, r1, 0x20
	lwz      r5, 0xc0(r31)
	lwz      r12, 8(r12)
	lfs      f26, 0x334(r5)
	lfs      f27, 0x30c(r5)
	mtctr    r12
	bctrl
	mr       r4, r31
	lfs      f2, 0x20(r1)
	lwz      r12, 0(r31)
	addi     r3, r1, 0x2c
	lfs      f1, 0x24(r1)
	lfs      f0, 0x28(r1)
	lwz      r12, 8(r12)
	stfs     f2, 8(r1)
	stfs     f1, 0xc(r1)
	stfs     f0, 0x10(r1)
	mtctr    r12
	bctrl
	lfs      f5, 0x2c(r1)
	lis      r3, atanTable___5JMath@ha
	lfs      f3, 0x34(r1)
	addi     r3, r3, atanTable___5JMath@l
	lfs      f1, 8(r1)
	lfs      f0, 0x10(r1)
	lfs      f4, 0x30(r1)
	fsubs    f1, f1, f5
	fsubs    f2, f0, f3
	stfs     f5, 0x14(r1)
	stfs     f4, 0x18(r1)
	stfs     f3, 0x1c(r1)
	bl       "atan2___Q25JMath18TAtanTable<1024,f>CFff"
	bl       roundAng__Ff
	lwz      r12, 0(r31)
	fmr      f25, f1
	mr       r3, r31
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fmr      f2, f1
	fmr      f1, f25
	bl       angDist__Fff
	fmuls    f27, f1, f27
	lfs      f0, lbl_8051BD74@sda21(r2)
	lfs      f1, lbl_8051BD70@sda21(r2)
	fmuls    f0, f0, f26
	fabs     f2, f27
	fmuls    f1, f1, f0
	frsp     f0, f2
	fcmpo    cr0, f0, f1
	ble      lbl_802A03F0
	lfs      f0, lbl_8051BD58@sda21(r2)
	fcmpo    cr0, f27, f0
	ble      lbl_802A03EC
	fmr      f27, f1
	b        lbl_802A03F0

lbl_802A03EC:
	fneg     f27, f1

lbl_802A03F0:
	mr       r3, r31
	lwz      r12, 0(r31)
	lwz      r12, 0x64(r12)
	mtctr    r12
	bctrl
	fadds    f1, f27, f1
	bl       roundAng__Ff
	stfs     f1, 0x1fc(r31)
	lfs      f0, 0x1fc(r31)
	stfs     f0, 0x1a8(r31)

lbl_802A0418:
	fsubs    f1, f30, f28
	lis      r3, atanTable___5JMath@ha
	fsubs    f2, f29, f31
	addi     r3, r3, atanTable___5JMath@l
	bl       "atan2___Q25JMath18TAtanTable<1024,f>CFff"
	lfs      f0, lbl_8051BD58@sda21(r2)
	lwz      r4, 0xc0(r31)
	fcmpo    cr0, f1, f0
	lfs      f4, 0x2e4(r4)
	bge      lbl_802A046C
	lfs      f0, lbl_8051BD7C@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0x50(r1)
	lwz      r0, 0x54(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f0, r3, r0
	fneg     f3, f0
	b        lbl_802A0490

lbl_802A046C:
	lfs      f0, lbl_8051BD80@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0x58(r1)
	lwz      r0, 0x5c(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	lfsx     f3, r3, r0

lbl_802A0490:
	lfs      f0, lbl_8051BD58@sda21(r2)
	fmuls    f4, f4, f3
	lfs      f2, 0x1d4(r31)
	lfs      f3, 0x1d8(r31)
	fcmpo    cr0, f1, f0
	lfs      f0, 0x1dc(r31)
	stfs     f2, 0x38(r1)
	stfs     f3, 0x3c(r1)
	stfs     f0, 0x40(r1)
	bge      lbl_802A04BC
	fneg     f1, f1

lbl_802A04BC:
	lfs      f0, lbl_8051BD80@sda21(r2)
	lis      r3, sincosTable___5JMath@ha
	addi     r3, r3, sincosTable___5JMath@l
	lfs      f2, 0x2e4(r4)
	fmuls    f0, f1, f0
	fctiwz   f0, f0
	stfd     f0, 0x60(r1)
	lwz      r0, 0x64(r1)
	rlwinm   r0, r0, 3, 0x12, 0x1c
	add      r3, r3, r0
	lfs      f0, 4(r3)
	stfs     f4, 0x1d4(r31)
	fmuls    f0, f2, f0
	stfs     f3, 0x1d8(r31)
	stfs     f0, 0x1dc(r31)

lbl_802A04F8:
	mr       r3, r31
	bl       getFlyingNextState__Q34Game12Hanachirashi3ObjFv
	or.      r5, r3, r3
	blt      lbl_802A0528
	lwz      r12, 0(r30)
	mr       r3, r30
	mr       r4, r31
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A0564

lbl_802A0528:
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_802A0564
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 0x3e8
	bne      lbl_802A0564
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 1
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802A0564:
	psq_l    f31, 216(r1), 0, qr0
	lfd      f31, 0xd0(r1)
	psq_l    f30, 200(r1), 0, qr0
	lfd      f30, 0xc0(r1)
	psq_l    f29, 184(r1), 0, qr0
	lfd      f29, 0xb0(r1)
	psq_l    f28, 168(r1), 0, qr0
	lfd      f28, 0xa0(r1)
	psq_l    f27, 152(r1), 0, qr0
	lfd      f27, 0x90(r1)
	psq_l    f26, 136(r1), 0, qr0
	lfd      f26, 0x80(r1)
	psq_l    f25, 120(r1), 0, qr0
	lfd      f25, 0x70(r1)
	lwz      r31, 0x6c(r1)
	lwz      r0, 0xe4(r1)
	lwz      r30, 0x68(r1)
	mtlr     r0
	addi     r1, r1, 0xe0
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A05B4
 * Size:	000024
 */
void StateChaseInside::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802A05D8
 * Size:	000090
 */
void StateAttack::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->disableEvent(0, EB_IsCullable);
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->enableEvent(0, EB_IsFlying);
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->setEmotionExcitement();
	hanachirashi->startMotion(9, nullptr);
	hanachirashi->_2C0 = -1;
	hanachirashi->_310 = 0;
	hanachirashi->_30C = 0.0f;
	hanachirashi->createSuckEffect();
}

/*
 * --INFO--
 * Address:	802A0668
 * Size:	00011C
 */
void StateAttack::exec(EnemyBase* enemy)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	mr       r30, r3
	mr       r3, r31
	bl       setHeightVelocity__Q34Game12Hanachirashi3ObjFv
	lbz      r0, 0x310(r31)
	cmplwi   r0, 0
	beq      lbl_802A06B0
	mr       r3, r31
	bl       windTarget__Q34Game12Hanachirashi3ObjFv
	clrlwi.  r0, r3, 0x18
	beq      lbl_802A06B0
	li       r0, 0xc
	stw      r0, 0x2c0(r31)

lbl_802A06B0:
	lfs      f1, 0x200(r31)
	lfs      f0, lbl_8051BD58@sda21(r2)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802A06E8
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 0
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A076C

lbl_802A06E8:
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_802A076C
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 2
	bne      lbl_802A0718
	li       r0, 1
	mr       r3, r31
	stb      r0, 0x310(r31)
	bl       startWindEffect__Q34Game12Hanachirashi3ObjFv
	b        lbl_802A076C

lbl_802A0718:
	cmplwi   r0, 0x3e8
	bne      lbl_802A076C
	lwz      r5, 0x2c0(r31)
	cmpwi    r5, 0
	blt      lbl_802A074C
	lwz      r12, 0(r30)
	mr       r3, r30
	mr       r4, r31
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A076C

lbl_802A074C:
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 1
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802A076C:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A0784
 * Size:	000054
 */
void StateAttack::cleanup(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->enableEvent(0, EB_IsCullable);
	hanachirashi->setEmotionCaution();
	hanachirashi->_310 = 0;
	hanachirashi->_30C = 0.0f;
	hanachirashi->finishWindEffect();
}

/*
 * --INFO--
 * Address:	802A07D8
 * Size:	000068
 */
void StateFall::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi             = OBJ(enemy);
	hanachirashi->_2C4            = 0.0f;
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->enableEvent(0, EB_IsFlying);
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->setEmotionExcitement();
	hanachirashi->startMotion(8, nullptr);
}

/*
 * --INFO--
 * Address:	802A0840
 * Size:	0001A4
 */
void StateFall::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	if (hanachirashi->isFlying()) {
		hanachirashi->setHeightVelocity();
	} else {
		Vector3f pos = hanachirashi->getPosition();
		Vector3f vel = hanachirashi->getVelocity();

		f32 fallSpeed = vel.y;

		f32 heightDiff = pos.y - mapMgr->getMinY(pos);
		if (heightDiff < 50.0f || fallSpeed > 0.0f) {
			hanachirashi->finishMotion();
		}

		hanachirashi->addShadowOffset();
	}

	if (hanachirashi->_2C4 > 0.75f) {
		hanachirashi->disableEvent(0, EB_IsFlying);
	}

	hanachirashi->_2C4 += sys->mDeltaTime;

	if (hanachirashi->mHealth <= 0.0f) {
		transit(hanachirashi, HANACHIRASHI_Dead, nullptr);
		return;
	}

	if (hanachirashi->mCurAnim->mIsPlaying && hanachirashi->mCurAnim->mType == KEYEVENT_END) {
		transit(hanachirashi, HANACHIRASHI_Land, nullptr);
	}
}

/*
 * --INFO--
 * Address:	802A09E4
 * Size:	000038
 */
void StateFall::cleanup(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->setShadowOffsetMax();
	hanachirashi->setEmotionCaution();
}

/*
 * --INFO--
 * Address:	802A0A1C
 * Size:	000070
 */
void StateLand::init(EnemyBase* enemy, StateArg* stateArg)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	lfs      f0, lbl_8051BD58@sda21(r2)
	stw      r0, 0x14(r1)
	li       r0, 0
	stw      r31, 0xc(r1)
	mr       r31, r4
	mr       r3, r31
	stfs     f0, 0x2c4(r4)
	stw      r0, 0x230(r4)
	lwz      r0, 0x1e0(r4)
	rlwinm   r0, r0, 0, 0x1e, 0x1c
	stw      r0, 0x1e0(r4)
	stfs     f0, 0x1d4(r4)
	stfs     f0, 0x1d8(r4)
	stfs     f0, 0x1dc(r4)
	bl       setEmotionExcitement__Q24Game9EnemyBaseFv
	mr       r3, r31
	li       r4, 6
	li       r5, 0
	bl       startMotion__Q24Game9EnemyBaseFiPQ28SysShape14MotionListener
	mr       r3, r31
	bl       createDownEffect__Q34Game12Hanachirashi3ObjFv
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A0A8C
 * Size:	000080
 */
void StateLand::exec(EnemyBase* enemy)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	lfs      f0, lbl_8051BD58@sda21(r2)
	stw      r0, 0x14(r1)
	lfs      f1, 0x200(r4)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802A0AC8
	lwz      r12, 0(r3)
	li       r5, 0
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A0AFC

lbl_802A0AC8:
	lwz      r5, 0x188(r4)
	lbz      r0, 0x24(r5)
	cmplwi   r0, 0
	beq      lbl_802A0AFC
	lwz      r0, 0x1c(r5)
	cmplwi   r0, 0x3e8
	bne      lbl_802A0AFC
	lwz      r12, 0(r3)
	li       r5, 8
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802A0AFC:
	lwz      r0, 0x14(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A0B0C
 * Size:	000024
 */
void StateLand::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802A0B30
 * Size:	000068
 */
void StateGround::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi             = OBJ(enemy);
	hanachirashi->_2C4            = 0.0f;
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->disableEvent(0, EB_IsFlying);
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->setEmotionExcitement();
	hanachirashi->startMotion(4, nullptr);
}

/*
 * --INFO--
 * Address:	802A0B98
 * Size:	000114
 */
void StateGround::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	if (hanachirashi->mStuckPikminCount == 0 || hanachirashi->_2C4 > CG_PROPERPARMS(hanachirashi).mFp10.mValue) {
		hanachirashi->finishMotion();
	}

	hanachirashi->_2C4 += sys->mDeltaTime;

	if (hanachirashi->mHealth <= 0.0f) {
		transit(hanachirashi, HANACHIRASHI_Dead, nullptr);
		return;
	}

	if (hanachirashi->mCurAnim->mIsPlaying && hanachirashi->mCurAnim->mType == KEYEVENT_END) {
		if (hanachirashi->mStuckPikminCount) {
			transit(hanachirashi, HANACHIRASHI_GroundFlick, nullptr);
		} else {
			transit(hanachirashi, HANACHIRASHI_TakeOff, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	802A0CAC
 * Size:	000024
 */
void StateGround::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802A0CD0
 * Size:	000064
 */
void StateTakeOff::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi             = OBJ(enemy);
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->disableEvent(0, EB_IsFlying);
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->setEmotionExcitement();
	hanachirashi->startMotion(7, nullptr);
}

/*
 * --INFO--
 * Address:	802A0D34
 * Size:	0000EC
 */
void StateTakeOff::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	if (hanachirashi->isFlying()) {
		hanachirashi->setHeightVelocity();
		hanachirashi->subShadowOffset();
	}

	if (hanachirashi->mHealth <= 0.0f) {
		transit(hanachirashi, HANACHIRASHI_Dead, nullptr);
		return;
	}

	if (hanachirashi->mCurAnim->mIsPlaying) {
		if (hanachirashi->mCurAnim->mType == KEYEVENT_2) {
			hanachirashi->enableEvent(0, EB_IsFlying);
		} else if (hanachirashi->mCurAnim->mType == KEYEVENT_END) {
			transit(hanachirashi, HANACHIRASHI_Wait, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	802A0E20
 * Size:	000038
 */
void StateTakeOff::cleanup(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->resetShadowOffset();
	hanachirashi->setEmotionCaution();
}

/*
 * --INFO--
 * Address:	802A0E58
 * Size:	000064
 */
void StateFlyFlick::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi             = OBJ(enemy);
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->enableEvent(0, EB_IsFlying);
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->setEmotionExcitement();
	hanachirashi->startMotion(2, nullptr);
}

/*
 * --INFO--
 * Address:	802A0EBC
 * Size:	0000E4
 */
void StateFlyFlick::exec(EnemyBase* enemy)
{
	Obj* hanachirashi = OBJ(enemy);
	hanachirashi->setHeightVelocity();

	if (hanachirashi->mHealth <= 0.0f) {
		transit(hanachirashi, HANACHIRASHI_Dead, nullptr);
		return;
	}

	if (hanachirashi->mCurAnim->mIsPlaying) {
		if (hanachirashi->mCurAnim->mType == KEYEVENT_2) {
			EnemyFunc::flickStickPikmin(hanachirashi, CG_PARMS(hanachirashi)->mGeneral.mShakeRateMaybe.mValue,
			                            CG_PARMS(hanachirashi)->mGeneral.mShakeKnockback.mValue,
			                            CG_PARMS(hanachirashi)->mGeneral.mShakeDamage.mValue, -1000.0f, nullptr);
			hanachirashi->mToFlick = 0.0f;

		} else if (hanachirashi->mCurAnim->mType == KEYEVENT_END) {
			transit(hanachirashi, HANACHIRASHI_Wait, nullptr);
		}
	}
}

/*
 * --INFO--
 * Address:	802A0FA0
 * Size:	000024
 */
void StateFlyFlick::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802A0FC4
 * Size:	000064
 */
void StateGroundFlick::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi             = OBJ(enemy);
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->disableEvent(0, EB_IsFlying);
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->setEmotionExcitement();
	hanachirashi->startMotion(3, nullptr);
}

/*
 * --INFO--
 * Address:	802A1028
 * Size:	000100
 */
void StateGroundFlick::exec(EnemyBase* enemy)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	lfs      f0, lbl_8051BD58@sda21(r2)
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	lfs      f1, 0x200(r4)
	fcmpo    cr0, f1, f0
	cror     2, 0, 2
	bne      lbl_802A106C
	lwz      r12, 0(r3)
	li       r5, 0
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A1114

lbl_802A106C:
	lwz      r5, 0x188(r31)
	lbz      r0, 0x24(r5)
	cmplwi   r0, 0
	beq      lbl_802A1114
	lwz      r0, 0x1c(r5)
	cmplwi   r0, 2
	bne      lbl_802A10F4
	lwz      r5, 0xc0(r31)
	mr       r3, r31
	lfs      f4, lbl_8051BD8C@sda21(r2)
	li       r4, 0
	lfs      f1, 0x514(r5)
	lfs      f2, 0x4c4(r5)
	lfs      f3, 0x4ec(r5)
	bl
"flickNearbyNavi__Q24Game9EnemyFuncFPQ24Game8CreatureffffP23Condition<Q24Game4Navi>"
	lwz      r5, 0xc0(r31)
	mr       r3, r31
	lfs      f4, lbl_8051BD8C@sda21(r2)
	li       r4, 0
	lfs      f1, 0x514(r5)
	lfs      f2, 0x4c4(r5)
	lfs      f3, 0x4ec(r5)
	bl
"flickNearbyPikmin__Q24Game9EnemyFuncFPQ24Game8CreatureffffP23Condition<Q24Game4Piki>"
	lwz      r5, 0xc0(r31)
	mr       r3, r31
	lfs      f4, lbl_8051BD8C@sda21(r2)
	li       r4, 0
	lfs      f1, 0x53c(r5)
	lfs      f2, 0x4c4(r5)
	lfs      f3, 0x4ec(r5)
	bl
"flickStickPikmin__Q24Game9EnemyFuncFPQ24Game8CreatureffffP23Condition<Q24Game4Piki>"
	lfs      f0, lbl_8051BD58@sda21(r2)
	stfs     f0, 0x20c(r31)
	b        lbl_802A1114

lbl_802A10F4:
	cmplwi   r0, 0x3e8
	bne      lbl_802A1114
	lwz      r12, 0(r3)
	li       r5, 9
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802A1114:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A1128
 * Size:	000024
 */
void StateGroundFlick::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }

/*
 * --INFO--
 * Address:	802A114C
 * Size:	000068
 */
void StateLaugh::init(EnemyBase* enemy, StateArg* stateArg)
{
	Obj* hanachirashi             = OBJ(enemy);
	hanachirashi->_2C4            = 0.0f;
	hanachirashi->mTargetVelocity = Vector3f(0.0f);
	hanachirashi->mTargetCreature = nullptr;
	hanachirashi->enableEvent(0, EB_IsFlying);
	hanachirashi->setEmotionExcitement();
	hanachirashi->startMotion(10, nullptr);
}

/*
 * --INFO--
 * Address:	802A11B4
 * Size:	0000DC
 */
void StateLaugh::exec(EnemyBase* enemy)
{
	/*
	stwu     r1, -0x10(r1)
	mflr     r0
	stw      r0, 0x14(r1)
	stw      r31, 0xc(r1)
	mr       r31, r4
	stw      r30, 8(r1)
	mr       r30, r3
	mr       r3, r31
	bl       setHeightVelocity__Q34Game12Hanachirashi3ObjFv
	lwz      r3, 0x188(r31)
	lbz      r0, 0x24(r3)
	cmplwi   r0, 0
	beq      lbl_802A1278
	lwz      r0, 0x1c(r3)
	cmplwi   r0, 0x3e8
	bne      lbl_802A1278
	mr       r3, r31
	bl       getFlyingNextState__Q34Game12Hanachirashi3ObjFv
	or.      r5, r3, r3
	blt      lbl_802A1224
	lwz      r12, 0(r30)
	mr       r3, r30
	mr       r4, r31
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A1278

lbl_802A1224:
	mr       r3, r31
	bl       isAttackable__Q34Game12Hanachirashi3ObjFv
	cmplwi   r3, 0
	beq      lbl_802A1258
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 5
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl
	b        lbl_802A1278

lbl_802A1258:
	mr       r3, r30
	mr       r4, r31
	lwz      r12, 0(r30)
	li       r5, 1
	li       r6, 0
	lwz      r12, 0x1c(r12)
	mtctr    r12
	bctrl

lbl_802A1278:
	lwz      r0, 0x14(r1)
	lwz      r31, 0xc(r1)
	lwz      r30, 8(r1)
	mtlr     r0
	addi     r1, r1, 0x10
	blr
	*/
}

/*
 * --INFO--
 * Address:	802A1290
 * Size:	000024
 */
void StateLaugh::cleanup(EnemyBase* enemy) { enemy->setEmotionCaution(); }
} // namespace Hanachirashi
} // namespace Game
