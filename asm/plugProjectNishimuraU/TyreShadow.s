.include "macros.inc"
.section .rodata  # 0x804732E0 - 0x8049E220
.balign 8
.obj lbl_8048DCA8, local
	.asciz "tyrefront"
.endobj lbl_8048DCA8
.balign 4
.obj lbl_8048DCB4, local
	.asciz "tyreback"
.endobj lbl_8048DCB4

.section .data, "wa"  # 0x8049E220 - 0x804EFC20
.balign 8
.obj __vt__Q24Game18TyreTubeShadowNode, weak
	.4byte 0
	.4byte 0
	.4byte __dt__Q24Game18TyreTubeShadowNodeFv
	.4byte getChildCount__5CNodeFv
.endobj __vt__Q24Game18TyreTubeShadowNode

.section .sdata2, "a"     # 0x80516360 - 0x80520E40
.balign 8
.obj lbl_8051D4E8, local
	.float 0.0
.endobj lbl_8051D4E8
.obj lbl_8051D4EC, local
	.float 1.0
.endobj lbl_8051D4EC
.obj lbl_8051D4F0, local
	.float 10.0
.endobj lbl_8051D4F0
.obj lbl_8051D4F4, local
	.float 5.0
.endobj lbl_8051D4F4
.obj lbl_8051D4F8, local
	.float 31.5
.endobj lbl_8051D4F8
.obj lbl_8051D4FC, local
	.float 17.5
.endobj lbl_8051D4FC
.obj lbl_8051D500, local
	.float -17.5
.endobj lbl_8051D500

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.fn makeShadowSRT__Q24Game18TyreTubeShadowNodeFRQ24Game15JointShadowParmP7Matrixf, global
/* 803019EC 002FE92C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 803019F0 002FE930  7C 08 02 A6 */	mflr r0
/* 803019F4 002FE934  C0 02 F1 88 */	lfs f0, lbl_8051D4E8@sda21(r2)
/* 803019F8 002FE938  90 01 00 44 */	stw r0, 0x44(r1)
/* 803019FC 002FE93C  38 01 00 2C */	addi r0, r1, 0x2c
/* 80301A00 002FE940  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80301A04 002FE944  7C 7F 1B 78 */	mr r31, r3
/* 80301A08 002FE948  C0 C5 00 10 */	lfs f6, 0x10(r5)
/* 80301A0C 002FE94C  C0 E5 00 20 */	lfs f7, 0x20(r5)
/* 80301A10 002FE950  EC 46 01 B2 */	fmuls f2, f6, f6
/* 80301A14 002FE954  C0 A5 00 00 */	lfs f5, 0(r5)
/* 80301A18 002FE958  C0 25 00 0C */	lfs f1, 0xc(r5)
/* 80301A1C 002FE95C  EC 67 01 F2 */	fmuls f3, f7, f7
/* 80301A20 002FE960  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 80301A24 002FE964  EC 25 11 7A */	fmadds f1, f5, f5, f2
/* 80301A28 002FE968  C0 45 00 1C */	lfs f2, 0x1c(r5)
/* 80301A2C 002FE96C  D0 41 00 30 */	stfs f2, 0x30(r1)
/* 80301A30 002FE970  EC 43 08 2A */	fadds f2, f3, f1
/* 80301A34 002FE974  C0 25 00 2C */	lfs f1, 0x2c(r5)
/* 80301A38 002FE978  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80301A3C 002FE97C  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 80301A40 002FE980  40 81 00 14 */	ble .L_80301A54
/* 80301A44 002FE984  40 81 00 14 */	ble .L_80301A58
/* 80301A48 002FE988  FC 00 10 34 */	frsqrte f0, f2
/* 80301A4C 002FE98C  EC 40 00 B2 */	fmuls f2, f0, f2
/* 80301A50 002FE990  48 00 00 08 */	b .L_80301A58
.L_80301A54:
/* 80301A54 002FE994  FC 40 00 90 */	fmr f2, f0
.L_80301A58:
/* 80301A58 002FE998  C0 02 F1 88 */	lfs f0, lbl_8051D4E8@sda21(r2)
/* 80301A5C 002FE99C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80301A60 002FE9A0  40 81 00 18 */	ble .L_80301A78
/* 80301A64 002FE9A4  C0 02 F1 8C */	lfs f0, lbl_8051D4EC@sda21(r2)
/* 80301A68 002FE9A8  EC 00 10 24 */	fdivs f0, f0, f2
/* 80301A6C 002FE9AC  EC A5 00 32 */	fmuls f5, f5, f0
/* 80301A70 002FE9B0  EC C6 00 32 */	fmuls f6, f6, f0
/* 80301A74 002FE9B4  EC E7 00 32 */	fmuls f7, f7, f0
.L_80301A78:
/* 80301A78 002FE9B8  C0 04 00 18 */	lfs f0, 0x18(r4)
/* 80301A7C 002FE9BC  C0 22 F1 88 */	lfs f1, lbl_8051D4E8@sda21(r2)
/* 80301A80 002FE9C0  EC 65 00 32 */	fmuls f3, f5, f0
/* 80301A84 002FE9C4  EC 46 00 32 */	fmuls f2, f6, f0
/* 80301A88 002FE9C8  EC 07 00 32 */	fmuls f0, f7, f0
/* 80301A8C 002FE9CC  D0 61 00 08 */	stfs f3, 8(r1)
/* 80301A90 002FE9D0  D0 41 00 0C */	stfs f2, 0xc(r1)
/* 80301A94 002FE9D4  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 80301A98 002FE9D8  C1 24 00 10 */	lfs f9, 0x10(r4)
/* 80301A9C 002FE9DC  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 80301AA0 002FE9E0  EC 07 02 72 */	fmuls f0, f7, f9
/* 80301AA4 002FE9E4  C1 04 00 0C */	lfs f8, 0xc(r4)
/* 80301AA8 002FE9E8  EC 65 00 B2 */	fmuls f3, f5, f2
/* 80301AAC 002FE9EC  EC 86 02 32 */	fmuls f4, f6, f8
/* 80301AB0 002FE9F0  EC 46 00 B8 */	fmsubs f2, f6, f2, f0
/* 80301AB4 002FE9F4  EC 67 1A 38 */	fmsubs f3, f7, f8, f3
/* 80301AB8 002FE9F8  EC 85 22 78 */	fmsubs f4, f5, f9, f4
/* 80301ABC 002FE9FC  EC 02 00 B2 */	fmuls f0, f2, f2
/* 80301AC0 002FEA00  D0 41 00 20 */	stfs f2, 0x20(r1)
/* 80301AC4 002FEA04  EC A3 00 F2 */	fmuls f5, f3, f3
/* 80301AC8 002FEA08  EC C4 01 32 */	fmuls f6, f4, f4
/* 80301ACC 002FEA0C  D0 61 00 24 */	stfs f3, 0x24(r1)
/* 80301AD0 002FEA10  EC 00 28 2A */	fadds f0, f0, f5
/* 80301AD4 002FEA14  D0 81 00 28 */	stfs f4, 0x28(r1)
/* 80301AD8 002FEA18  EC 06 00 2A */	fadds f0, f6, f0
/* 80301ADC 002FEA1C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80301AE0 002FEA20  40 81 00 20 */	ble .L_80301B00
/* 80301AE4 002FEA24  EC 02 28 BA */	fmadds f0, f2, f2, f5
/* 80301AE8 002FEA28  EC 66 00 2A */	fadds f3, f6, f0
/* 80301AEC 002FEA2C  FC 03 08 40 */	fcmpo cr0, f3, f1
/* 80301AF0 002FEA30  40 81 00 14 */	ble .L_80301B04
/* 80301AF4 002FEA34  FC 00 18 34 */	frsqrte f0, f3
/* 80301AF8 002FEA38  EC 60 00 F2 */	fmuls f3, f0, f3
/* 80301AFC 002FEA3C  48 00 00 08 */	b .L_80301B04
.L_80301B00:
/* 80301B00 002FEA40  FC 60 08 90 */	fmr f3, f1
.L_80301B04:
/* 80301B04 002FEA44  C0 02 F1 88 */	lfs f0, lbl_8051D4E8@sda21(r2)
/* 80301B08 002FEA48  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80301B0C 002FEA4C  40 81 00 30 */	ble .L_80301B3C
/* 80301B10 002FEA50  C0 02 F1 8C */	lfs f0, lbl_8051D4EC@sda21(r2)
/* 80301B14 002FEA54  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 80301B18 002FEA58  EC 60 18 24 */	fdivs f3, f0, f3
/* 80301B1C 002FEA5C  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80301B20 002FEA60  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80301B24 002FEA64  EC 42 00 F2 */	fmuls f2, f2, f3
/* 80301B28 002FEA68  EC 21 00 F2 */	fmuls f1, f1, f3
/* 80301B2C 002FEA6C  EC 00 00 F2 */	fmuls f0, f0, f3
/* 80301B30 002FEA70  D0 41 00 20 */	stfs f2, 0x20(r1)
/* 80301B34 002FEA74  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 80301B38 002FEA78  D0 01 00 28 */	stfs f0, 0x28(r1)
.L_80301B3C:
/* 80301B3C 002FEA7C  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 80301B40 002FEA80  C0 A4 00 1C */	lfs f5, 0x1c(r4)
/* 80301B44 002FEA84  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80301B48 002FEA88  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80301B4C 002FEA8C  EC 82 01 72 */	fmuls f4, f2, f5
/* 80301B50 002FEA90  EC 61 01 72 */	fmuls f3, f1, f5
/* 80301B54 002FEA94  C0 41 00 30 */	lfs f2, 0x30(r1)
/* 80301B58 002FEA98  EC 20 01 72 */	fmuls f1, f0, f5
/* 80301B5C 002FEA9C  C0 02 F1 88 */	lfs f0, lbl_8051D4E8@sda21(r2)
/* 80301B60 002FEAA0  D0 81 00 20 */	stfs f4, 0x20(r1)
/* 80301B64 002FEAA4  80 6D 93 08 */	lwz r3, mapMgr__4Game@sda21(r13)
/* 80301B68 002FEAA8  D0 61 00 24 */	stfs f3, 0x24(r1)
/* 80301B6C 002FEAAC  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 80301B70 002FEAB0  C0 24 00 24 */	lfs f1, 0x24(r4)
/* 80301B74 002FEAB4  7C 04 03 78 */	mr r4, r0
/* 80301B78 002FEAB8  EC 22 08 2A */	fadds f1, f2, f1
/* 80301B7C 002FEABC  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80301B80 002FEAC0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80301B84 002FEAC4  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 80301B88 002FEAC8  81 83 00 04 */	lwz r12, 4(r3)
/* 80301B8C 002FEACC  81 8C 00 28 */	lwz r12, 0x28(r12)
/* 80301B90 002FEAD0  7D 89 03 A6 */	mtctr r12
/* 80301B94 002FEAD4  4E 80 04 21 */	bctrl 
/* 80301B98 002FEAD8  C0 41 00 30 */	lfs f2, 0x30(r1)
/* 80301B9C 002FEADC  C0 02 F1 88 */	lfs f0, lbl_8051D4E8@sda21(r2)
/* 80301BA0 002FEAE0  EC 22 08 28 */	fsubs f1, f2, f1
/* 80301BA4 002FEAE4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80301BA8 002FEAE8  40 80 00 10 */	bge .L_80301BB8
/* 80301BAC 002FEAEC  C0 02 F1 90 */	lfs f0, lbl_8051D4F0@sda21(r2)
/* 80301BB0 002FEAF0  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80301BB4 002FEAF4  48 00 00 10 */	b .L_80301BC4
.L_80301BB8:
/* 80301BB8 002FEAF8  C0 02 F1 94 */	lfs f0, lbl_8051D4F4@sda21(r2)
/* 80301BBC 002FEAFC  EC 00 00 72 */	fmuls f0, f0, f1
/* 80301BC0 002FEB00  D0 01 00 18 */	stfs f0, 0x18(r1)
.L_80301BC4:
/* 80301BC4 002FEB04  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 80301BC8 002FEB08  C0 01 00 08 */	lfs f0, 8(r1)
/* 80301BCC 002FEB0C  D0 03 00 00 */	stfs f0, 0(r3)
/* 80301BD0 002FEB10  C0 01 00 0C */	lfs f0, 0xc(r1)
/* 80301BD4 002FEB14  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 80301BD8 002FEB18  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 80301BDC 002FEB1C  D0 03 00 20 */	stfs f0, 0x20(r3)
/* 80301BE0 002FEB20  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 80301BE4 002FEB24  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 80301BE8 002FEB28  D0 03 00 04 */	stfs f0, 4(r3)
/* 80301BEC 002FEB2C  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 80301BF0 002FEB30  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 80301BF4 002FEB34  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80301BF8 002FEB38  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 80301BFC 002FEB3C  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 80301C00 002FEB40  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80301C04 002FEB44  D0 03 00 08 */	stfs f0, 8(r3)
/* 80301C08 002FEB48  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 80301C0C 002FEB4C  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 80301C10 002FEB50  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80301C14 002FEB54  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 80301C18 002FEB58  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 80301C1C 002FEB5C  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80301C20 002FEB60  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 80301C24 002FEB64  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 80301C28 002FEB68  D0 03 00 1C */	stfs f0, 0x1c(r3)
/* 80301C2C 002FEB6C  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 80301C30 002FEB70  D0 03 00 2C */	stfs f0, 0x2c(r3)
/* 80301C34 002FEB74  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80301C38 002FEB78  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80301C3C 002FEB7C  7C 08 03 A6 */	mtlr r0
/* 80301C40 002FEB80  38 21 00 40 */	addi r1, r1, 0x40
/* 80301C44 002FEB84  4E 80 00 20 */	blr 
.endfn makeShadowSRT__Q24Game18TyreTubeShadowNodeFRQ24Game15JointShadowParmP7Matrixf

.fn __ct__Q34Game4Tyre13TyreShadowMgrFPQ34Game4Tyre3Obj, global
/* 80301C48 002FEB88  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80301C4C 002FEB8C  7C 08 02 A6 */	mflr r0
/* 80301C50 002FEB90  C0 02 F1 8C */	lfs f0, lbl_8051D4EC@sda21(r2)
/* 80301C54 002FEB94  90 01 00 14 */	stw r0, 0x14(r1)
/* 80301C58 002FEB98  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80301C5C 002FEB9C  7C 9F 23 78 */	mr r31, r4
/* 80301C60 002FEBA0  93 C1 00 08 */	stw r30, 8(r1)
/* 80301C64 002FEBA4  7C 7E 1B 78 */	mr r30, r3
/* 80301C68 002FEBA8  93 E3 00 0C */	stw r31, 0xc(r3)
/* 80301C6C 002FEBAC  38 60 00 20 */	li r3, 0x20
/* 80301C70 002FEBB0  D0 1E 00 00 */	stfs f0, 0(r30)
/* 80301C74 002FEBB4  4B D2 22 31 */	bl __nw__FUl
/* 80301C78 002FEBB8  7C 60 1B 79 */	or. r0, r3, r3
/* 80301C7C 002FEBBC  41 82 00 10 */	beq .L_80301C8C
/* 80301C80 002FEBC0  7F E4 FB 78 */	mr r4, r31
/* 80301C84 002FEBC4  4B F3 F5 F9 */	bl __ct__Q24Game19JointShadowRootNodeFPQ24Game8Creature
/* 80301C88 002FEBC8  7C 60 1B 78 */	mr r0, r3
.L_80301C8C:
/* 80301C8C 002FEBCC  90 1E 00 10 */	stw r0, 0x10(r30)
/* 80301C90 002FEBD0  38 60 00 24 */	li r3, 0x24
/* 80301C94 002FEBD4  4B D2 22 11 */	bl __nw__FUl
/* 80301C98 002FEBD8  7C 7F 1B 79 */	or. r31, r3, r3
/* 80301C9C 002FEBDC  41 82 00 18 */	beq .L_80301CB4
/* 80301CA0 002FEBE0  38 80 00 02 */	li r4, 2
/* 80301CA4 002FEBE4  4B F3 F6 39 */	bl __ct__Q24Game15JointShadowNodeFi
/* 80301CA8 002FEBE8  3C 60 80 4D */	lis r3, __vt__Q24Game18TyreTubeShadowNode@ha
/* 80301CAC 002FEBEC  38 03 7A B0 */	addi r0, r3, __vt__Q24Game18TyreTubeShadowNode@l
/* 80301CB0 002FEBF0  90 1F 00 00 */	stw r0, 0(r31)
.L_80301CB4:
/* 80301CB4 002FEBF4  93 FE 00 14 */	stw r31, 0x14(r30)
/* 80301CB8 002FEBF8  38 00 00 02 */	li r0, 2
/* 80301CBC 002FEBFC  80 7E 00 14 */	lwz r3, 0x14(r30)
/* 80301CC0 002FEC00  90 03 00 18 */	stw r0, 0x18(r3)
/* 80301CC4 002FEC04  80 7E 00 10 */	lwz r3, 0x10(r30)
/* 80301CC8 002FEC08  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 80301CCC 002FEC0C  48 10 F7 3D */	bl add__5CNodeFP5CNode
/* 80301CD0 002FEC10  38 60 00 24 */	li r3, 0x24
/* 80301CD4 002FEC14  4B D2 21 D1 */	bl __nw__FUl
/* 80301CD8 002FEC18  7C 7F 1B 79 */	or. r31, r3, r3
/* 80301CDC 002FEC1C  41 82 00 18 */	beq .L_80301CF4
/* 80301CE0 002FEC20  38 80 00 02 */	li r4, 2
/* 80301CE4 002FEC24  4B F3 F5 F9 */	bl __ct__Q24Game15JointShadowNodeFi
/* 80301CE8 002FEC28  3C 60 80 4D */	lis r3, __vt__Q24Game18TyreTubeShadowNode@ha
/* 80301CEC 002FEC2C  38 03 7A B0 */	addi r0, r3, __vt__Q24Game18TyreTubeShadowNode@l
/* 80301CF0 002FEC30  90 1F 00 00 */	stw r0, 0(r31)
.L_80301CF4:
/* 80301CF4 002FEC34  93 FE 00 18 */	stw r31, 0x18(r30)
/* 80301CF8 002FEC38  38 00 00 02 */	li r0, 2
/* 80301CFC 002FEC3C  80 7E 00 18 */	lwz r3, 0x18(r30)
/* 80301D00 002FEC40  90 03 00 18 */	stw r0, 0x18(r3)
/* 80301D04 002FEC44  80 7E 00 10 */	lwz r3, 0x10(r30)
/* 80301D08 002FEC48  80 9E 00 18 */	lwz r4, 0x18(r30)
/* 80301D0C 002FEC4C  48 10 F6 FD */	bl add__5CNodeFP5CNode
/* 80301D10 002FEC50  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80301D14 002FEC54  7F C3 F3 78 */	mr r3, r30
/* 80301D18 002FEC58  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80301D1C 002FEC5C  83 C1 00 08 */	lwz r30, 8(r1)
/* 80301D20 002FEC60  7C 08 03 A6 */	mtlr r0
/* 80301D24 002FEC64  38 21 00 10 */	addi r1, r1, 0x10
/* 80301D28 002FEC68  4E 80 00 20 */	blr 
.endfn __ct__Q34Game4Tyre13TyreShadowMgrFPQ34Game4Tyre3Obj

.fn init__Q34Game4Tyre13TyreShadowMgrFv, global
/* 80301D2C 002FEC6C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80301D30 002FEC70  7C 08 02 A6 */	mflr r0
/* 80301D34 002FEC74  90 01 00 14 */	stw r0, 0x14(r1)
/* 80301D38 002FEC78  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80301D3C 002FEC7C  93 C1 00 08 */	stw r30, 8(r1)
/* 80301D40 002FEC80  7C 7E 1B 78 */	mr r30, r3
/* 80301D44 002FEC84  3C 60 80 49 */	lis r3, lbl_8048DCA8@ha
/* 80301D48 002FEC88  80 BE 00 0C */	lwz r5, 0xc(r30)
/* 80301D4C 002FEC8C  38 83 DC A8 */	addi r4, r3, lbl_8048DCA8@l
/* 80301D50 002FEC90  83 E5 01 74 */	lwz r31, 0x174(r5)
/* 80301D54 002FEC94  7F E3 FB 78 */	mr r3, r31
/* 80301D58 002FEC98  48 13 D2 8D */	bl getJoint__Q28SysShape5ModelFPc
/* 80301D5C 002FEC9C  48 12 7B 45 */	bl getWorldMatrix__Q28SysShape5JointFv
/* 80301D60 002FECA0  3C 80 80 49 */	lis r4, lbl_8048DCB4@ha
/* 80301D64 002FECA4  90 7E 00 04 */	stw r3, 4(r30)
/* 80301D68 002FECA8  38 84 DC B4 */	addi r4, r4, lbl_8048DCB4@l
/* 80301D6C 002FECAC  7F E3 FB 78 */	mr r3, r31
/* 80301D70 002FECB0  48 13 D2 75 */	bl getJoint__Q28SysShape5ModelFPc
/* 80301D74 002FECB4  48 12 7B 2D */	bl getWorldMatrix__Q28SysShape5JointFv
/* 80301D78 002FECB8  90 7E 00 08 */	stw r3, 8(r30)
/* 80301D7C 002FECBC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80301D80 002FECC0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80301D84 002FECC4  83 C1 00 08 */	lwz r30, 8(r1)
/* 80301D88 002FECC8  7C 08 03 A6 */	mtlr r0
/* 80301D8C 002FECCC  38 21 00 10 */	addi r1, r1, 0x10
/* 80301D90 002FECD0  4E 80 00 20 */	blr 
.endfn init__Q34Game4Tyre13TyreShadowMgrFv

.fn update__Q34Game4Tyre13TyreShadowMgrFv, global
/* 80301D94 002FECD4  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80301D98 002FECD8  7C 08 02 A6 */	mflr r0
/* 80301D9C 002FECDC  90 01 00 54 */	stw r0, 0x54(r1)
/* 80301DA0 002FECE0  93 E1 00 4C */	stw r31, 0x4c(r1)
/* 80301DA4 002FECE4  7C 7F 1B 78 */	mr r31, r3
/* 80301DA8 002FECE8  38 61 00 08 */	addi r3, r1, 8
/* 80301DAC 002FECEC  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 80301DB0 002FECF0  81 84 00 00 */	lwz r12, 0(r4)
/* 80301DB4 002FECF4  81 8C 00 08 */	lwz r12, 8(r12)
/* 80301DB8 002FECF8  7D 89 03 A6 */	mtctr r12
/* 80301DBC 002FECFC  4E 80 04 21 */	bctrl 
/* 80301DC0 002FED00  C0 82 F1 88 */	lfs f4, lbl_8051D4E8@sda21(r2)
/* 80301DC4 002FED04  38 81 00 14 */	addi r4, r1, 0x14
/* 80301DC8 002FED08  C0 41 00 08 */	lfs f2, 8(r1)
/* 80301DCC 002FED0C  C0 21 00 0C */	lfs f1, 0xc(r1)
/* 80301DD0 002FED10  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 80301DD4 002FED14  C0 62 F1 8C */	lfs f3, lbl_8051D4EC@sda21(r2)
/* 80301DD8 002FED18  D0 41 00 14 */	stfs f2, 0x14(r1)
/* 80301DDC 002FED1C  C0 42 F1 98 */	lfs f2, lbl_8051D4F8@sda21(r2)
/* 80301DE0 002FED20  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80301DE4 002FED24  C0 22 F1 9C */	lfs f1, lbl_8051D4FC@sda21(r2)
/* 80301DE8 002FED28  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80301DEC 002FED2C  C0 02 F1 A0 */	lfs f0, lbl_8051D500@sda21(r2)
/* 80301DF0 002FED30  D0 81 00 20 */	stfs f4, 0x20(r1)
/* 80301DF4 002FED34  D0 61 00 24 */	stfs f3, 0x24(r1)
/* 80301DF8 002FED38  D0 81 00 28 */	stfs f4, 0x28(r1)
/* 80301DFC 002FED3C  C0 7F 00 00 */	lfs f3, 0(r31)
/* 80301E00 002FED40  EC 42 00 F2 */	fmuls f2, f2, f3
/* 80301E04 002FED44  D0 81 00 34 */	stfs f4, 0x34(r1)
/* 80301E08 002FED48  EC 21 00 F2 */	fmuls f1, f1, f3
/* 80301E0C 002FED4C  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 80301E10 002FED50  D0 41 00 2C */	stfs f2, 0x2c(r1)
/* 80301E14 002FED54  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 80301E18 002FED58  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 80301E1C 002FED5C  80 BF 00 04 */	lwz r5, 4(r31)
/* 80301E20 002FED60  4B FF FB CD */	bl makeShadowSRT__Q24Game18TyreTubeShadowNodeFRQ24Game15JointShadowParmP7Matrixf
/* 80301E24 002FED64  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 80301E28 002FED68  38 81 00 14 */	addi r4, r1, 0x14
/* 80301E2C 002FED6C  80 BF 00 08 */	lwz r5, 8(r31)
/* 80301E30 002FED70  4B FF FB BD */	bl makeShadowSRT__Q24Game18TyreTubeShadowNodeFRQ24Game15JointShadowParmP7Matrixf
/* 80301E34 002FED74  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80301E38 002FED78  83 E1 00 4C */	lwz r31, 0x4c(r1)
/* 80301E3C 002FED7C  7C 08 03 A6 */	mtlr r0
/* 80301E40 002FED80  38 21 00 50 */	addi r1, r1, 0x50
/* 80301E44 002FED84  4E 80 00 20 */	blr 
.endfn update__Q34Game4Tyre13TyreShadowMgrFv

.fn __dt__Q24Game18TyreTubeShadowNodeFv, weak
/* 80301E48 002FED88  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80301E4C 002FED8C  7C 08 02 A6 */	mflr r0
/* 80301E50 002FED90  90 01 00 14 */	stw r0, 0x14(r1)
/* 80301E54 002FED94  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80301E58 002FED98  7C 9F 23 78 */	mr r31, r4
/* 80301E5C 002FED9C  93 C1 00 08 */	stw r30, 8(r1)
/* 80301E60 002FEDA0  7C 7E 1B 79 */	or. r30, r3, r3
/* 80301E64 002FEDA4  41 82 00 38 */	beq .L_80301E9C
/* 80301E68 002FEDA8  3C 80 80 4D */	lis r4, __vt__Q24Game18TyreTubeShadowNode@ha
/* 80301E6C 002FEDAC  38 04 7A B0 */	addi r0, r4, __vt__Q24Game18TyreTubeShadowNode@l
/* 80301E70 002FEDB0  90 1E 00 00 */	stw r0, 0(r30)
/* 80301E74 002FEDB4  41 82 00 18 */	beq .L_80301E8C
/* 80301E78 002FEDB8  3C A0 80 4C */	lis r5, __vt__Q24Game15JointShadowNode@ha
/* 80301E7C 002FEDBC  38 80 00 00 */	li r4, 0
/* 80301E80 002FEDC0  38 05 1A 34 */	addi r0, r5, __vt__Q24Game15JointShadowNode@l
/* 80301E84 002FEDC4  90 1E 00 00 */	stw r0, 0(r30)
/* 80301E88 002FEDC8  48 10 F7 01 */	bl __dt__5CNodeFv
.L_80301E8C:
/* 80301E8C 002FEDCC  7F E0 07 35 */	extsh. r0, r31
/* 80301E90 002FEDD0  40 81 00 0C */	ble .L_80301E9C
/* 80301E94 002FEDD4  7F C3 F3 78 */	mr r3, r30
/* 80301E98 002FEDD8  4B D2 22 1D */	bl __dl__FPv
.L_80301E9C:
/* 80301E9C 002FEDDC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80301EA0 002FEDE0  7F C3 F3 78 */	mr r3, r30
/* 80301EA4 002FEDE4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80301EA8 002FEDE8  83 C1 00 08 */	lwz r30, 8(r1)
/* 80301EAC 002FEDEC  7C 08 03 A6 */	mtlr r0
/* 80301EB0 002FEDF0  38 21 00 10 */	addi r1, r1, 0x10
/* 80301EB4 002FEDF4  4E 80 00 20 */	blr 
.endfn __dt__Q24Game18TyreTubeShadowNodeFv