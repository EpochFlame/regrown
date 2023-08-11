.include "macros.inc"
.section .sdata2, "a"     # 0x80516360 - 0x80520E40
.balign 8
.obj lbl_80516448, local
	.float 0.017453292
.endobj lbl_80516448
.obj lbl_8051644C, local
	.float 0.0
.endobj lbl_8051644C
.balign 8
.obj lbl_80516450, local
	.double 0.0
.endobj lbl_80516450
.balign 8
.obj lbl_80516458, local
	.double 1.0
.endobj lbl_80516458
.obj lbl_80516460, local
	.float 32.0
.endobj lbl_80516460
.balign 8
.obj lbl_80516468, local
	.double -1.5707963267948966
.endobj lbl_80516468
.balign 8
.obj lbl_80516470, local
	.double 1.5707963267948966
.endobj lbl_80516470
.balign 8
.obj lbl_80516478, local
	.double 57.29577951308232
.endobj lbl_80516478

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.fn getTransformation_SRxyzT__Q27JStudio4mathFPA4_fRC3VecRC3VecRC3Vec, global
/* 80010FC4 0000DF04  94 21 FE F0 */	stwu r1, -0x110(r1)
/* 80010FC8 0000DF08  7C 08 02 A6 */	mflr r0
/* 80010FCC 0000DF0C  90 01 01 14 */	stw r0, 0x114(r1)
/* 80010FD0 0000DF10  DB E1 01 00 */	stfd f31, 0x100(r1)
/* 80010FD4 0000DF14  F3 E1 01 08 */	psq_st f31, 264(r1), 0, qr0
/* 80010FD8 0000DF18  DB C1 00 F0 */	stfd f30, 0xf0(r1)
/* 80010FDC 0000DF1C  F3 C1 00 F8 */	psq_st f30, 248(r1), 0, qr0
/* 80010FE0 0000DF20  DB A1 00 E0 */	stfd f29, 0xe0(r1)
/* 80010FE4 0000DF24  F3 A1 00 E8 */	psq_st f29, 232(r1), 0, qr0
/* 80010FE8 0000DF28  DB 81 00 D0 */	stfd f28, 0xd0(r1)
/* 80010FEC 0000DF2C  F3 81 00 D8 */	psq_st f28, 216(r1), 0, qr0
/* 80010FF0 0000DF30  DB 61 00 C0 */	stfd f27, 0xc0(r1)
/* 80010FF4 0000DF34  F3 61 00 C8 */	psq_st f27, 200(r1), 0, qr0
/* 80010FF8 0000DF38  DB 41 00 B0 */	stfd f26, 0xb0(r1)
/* 80010FFC 0000DF3C  F3 41 00 B8 */	psq_st f26, 184(r1), 0, qr0
/* 80011000 0000DF40  93 E1 00 AC */	stw r31, 0xac(r1)
/* 80011004 0000DF44  93 C1 00 A8 */	stw r30, 0xa8(r1)
/* 80011008 0000DF48  93 A1 00 A4 */	stw r29, 0xa4(r1)
/* 8001100C 0000DF4C  C0 24 00 00 */	lfs f1, 0(r4)
/* 80011010 0000DF50  7C 7D 1B 78 */	mr r29, r3
/* 80011014 0000DF54  C0 44 00 04 */	lfs f2, 4(r4)
/* 80011018 0000DF58  7C BE 2B 78 */	mr r30, r5
/* 8001101C 0000DF5C  C0 64 00 08 */	lfs f3, 8(r4)
/* 80011020 0000DF60  7C DF 33 78 */	mr r31, r6
/* 80011024 0000DF64  38 61 00 68 */	addi r3, r1, 0x68
/* 80011028 0000DF68  48 0D 97 AD */	bl PSMTXScale
/* 8001102C 0000DF6C  C0 22 80 E8 */	lfs f1, lbl_80516448@sda21(r2)
/* 80011030 0000DF70  C0 1E 00 00 */	lfs f0, 0(r30)
/* 80011034 0000DF74  C3 DE 00 08 */	lfs f30, 8(r30)
/* 80011038 0000DF78  EF 61 00 32 */	fmuls f27, f1, f0
/* 8001103C 0000DF7C  C3 FE 00 04 */	lfs f31, 4(r30)
/* 80011040 0000DF80  FC 20 D8 90 */	fmr f1, f27
/* 80011044 0000DF84  48 0B E2 71 */	bl cos
/* 80011048 0000DF88  FF A0 08 18 */	frsp f29, f1
/* 8001104C 0000DF8C  FC 20 D8 90 */	fmr f1, f27
/* 80011050 0000DF90  48 0B E7 CD */	bl sin
/* 80011054 0000DF94  C0 02 80 E8 */	lfs f0, lbl_80516448@sda21(r2)
/* 80011058 0000DF98  FF 80 08 18 */	frsp f28, f1
/* 8001105C 0000DF9C  EF E0 07 F2 */	fmuls f31, f0, f31
/* 80011060 0000DFA0  FC 20 F8 90 */	fmr f1, f31
/* 80011064 0000DFA4  48 0B E2 51 */	bl cos
/* 80011068 0000DFA8  FF 60 08 18 */	frsp f27, f1
/* 8001106C 0000DFAC  FC 20 F8 90 */	fmr f1, f31
/* 80011070 0000DFB0  48 0B E7 AD */	bl sin
/* 80011074 0000DFB4  C0 02 80 E8 */	lfs f0, lbl_80516448@sda21(r2)
/* 80011078 0000DFB8  FF E0 08 18 */	frsp f31, f1
/* 8001107C 0000DFBC  EF 40 07 B2 */	fmuls f26, f0, f30
/* 80011080 0000DFC0  FC 20 D0 90 */	fmr f1, f26
/* 80011084 0000DFC4  48 0B E2 31 */	bl cos
/* 80011088 0000DFC8  FF C0 08 18 */	frsp f30, f1
/* 8001108C 0000DFCC  FC 20 D0 90 */	fmr f1, f26
/* 80011090 0000DFD0  48 0B E7 8D */	bl sin
/* 80011094 0000DFD4  FC E0 08 18 */	frsp f7, f1
/* 80011098 0000DFD8  C0 02 80 EC */	lfs f0, lbl_8051644C@sda21(r2)
/* 8001109C 0000DFDC  EC 5B 07 B2 */	fmuls f2, f27, f30
/* 800110A0 0000DFE0  38 61 00 08 */	addi r3, r1, 8
/* 800110A4 0000DFE4  FC 20 F8 50 */	fneg f1, f31
/* 800110A8 0000DFE8  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800110AC 0000DFEC  EC DD 07 B2 */	fmuls f6, f29, f30
/* 800110B0 0000DFF0  D0 41 00 08 */	stfs f2, 8(r1)
/* 800110B4 0000DFF4  EC BC 01 F2 */	fmuls f5, f28, f7
/* 800110B8 0000DFF8  38 81 00 68 */	addi r4, r1, 0x68
/* 800110BC 0000DFFC  EC 5B 01 F2 */	fmuls f2, f27, f7
/* 800110C0 0000E000  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 800110C4 0000E004  EC 9C 06 F2 */	fmuls f4, f28, f27
/* 800110C8 0000E008  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800110CC 0000E00C  EC 7D 06 F2 */	fmuls f3, f29, f27
/* 800110D0 0000E010  38 A1 00 38 */	addi r5, r1, 0x38
/* 800110D4 0000E014  EC 26 2F FA */	fmadds f1, f6, f31, f5
/* 800110D8 0000E018  D0 41 00 18 */	stfs f2, 0x18(r1)
/* 800110DC 0000E01C  EC 45 37 FA */	fmadds f2, f5, f31, f6
/* 800110E0 0000E020  D0 81 00 2C */	stfs f4, 0x2c(r1)
/* 800110E4 0000E024  EC BD 01 F2 */	fmuls f5, f29, f7
/* 800110E8 0000E028  EC 9C 07 B2 */	fmuls f4, f28, f30
/* 800110EC 0000E02C  D0 61 00 30 */	stfs f3, 0x30(r1)
/* 800110F0 0000E030  D0 21 00 10 */	stfs f1, 0x10(r1)
/* 800110F4 0000E034  EC 64 2F F8 */	fmsubs f3, f4, f31, f5
/* 800110F8 0000E038  EC 25 27 F8 */	fmsubs f1, f5, f31, f4
/* 800110FC 0000E03C  D0 41 00 1C */	stfs f2, 0x1c(r1)
/* 80011100 0000E040  D0 61 00 0C */	stfs f3, 0xc(r1)
/* 80011104 0000E044  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80011108 0000E048  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 8001110C 0000E04C  48 0D 91 F5 */	bl PSMTXConcat
/* 80011110 0000E050  C0 3F 00 00 */	lfs f1, 0(r31)
/* 80011114 0000E054  7F A4 EB 78 */	mr r4, r29
/* 80011118 0000E058  C0 5F 00 04 */	lfs f2, 4(r31)
/* 8001111C 0000E05C  38 61 00 38 */	addi r3, r1, 0x38
/* 80011120 0000E060  C0 7F 00 08 */	lfs f3, 8(r31)
/* 80011124 0000E064  48 0D 96 65 */	bl PSMTXTransApply
/* 80011128 0000E068  E3 E1 01 08 */	psq_l f31, 264(r1), 0, qr0
/* 8001112C 0000E06C  CB E1 01 00 */	lfd f31, 0x100(r1)
/* 80011130 0000E070  E3 C1 00 F8 */	psq_l f30, 248(r1), 0, qr0
/* 80011134 0000E074  CB C1 00 F0 */	lfd f30, 0xf0(r1)
/* 80011138 0000E078  E3 A1 00 E8 */	psq_l f29, 232(r1), 0, qr0
/* 8001113C 0000E07C  CB A1 00 E0 */	lfd f29, 0xe0(r1)
/* 80011140 0000E080  E3 81 00 D8 */	psq_l f28, 216(r1), 0, qr0
/* 80011144 0000E084  CB 81 00 D0 */	lfd f28, 0xd0(r1)
/* 80011148 0000E088  E3 61 00 C8 */	psq_l f27, 200(r1), 0, qr0
/* 8001114C 0000E08C  CB 61 00 C0 */	lfd f27, 0xc0(r1)
/* 80011150 0000E090  E3 41 00 B8 */	psq_l f26, 184(r1), 0, qr0
/* 80011154 0000E094  CB 41 00 B0 */	lfd f26, 0xb0(r1)
/* 80011158 0000E098  83 E1 00 AC */	lwz r31, 0xac(r1)
/* 8001115C 0000E09C  83 C1 00 A8 */	lwz r30, 0xa8(r1)
/* 80011160 0000E0A0  80 01 01 14 */	lwz r0, 0x114(r1)
/* 80011164 0000E0A4  83 A1 00 A4 */	lwz r29, 0xa4(r1)
/* 80011168 0000E0A8  7C 08 03 A6 */	mtlr r0
/* 8001116C 0000E0AC  38 21 01 10 */	addi r1, r1, 0x110
/* 80011170 0000E0B0  4E 80 00 20 */	blr 
.endfn getTransformation_SRxyzT__Q27JStudio4mathFPA4_fRC3VecRC3VecRC3Vec

.fn getFromTransformation_SRxyzT__Q27JStudio4mathFP3VecP3VecP3VecPA4_Cf, global
/* 80011174 0000E0B4  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80011178 0000E0B8  7C 08 02 A6 */	mflr r0
/* 8001117C 0000E0BC  90 01 00 84 */	stw r0, 0x84(r1)
/* 80011180 0000E0C0  DB E1 00 70 */	stfd f31, 0x70(r1)
/* 80011184 0000E0C4  F3 E1 00 78 */	psq_st f31, 120(r1), 0, qr0
/* 80011188 0000E0C8  DB C1 00 60 */	stfd f30, 0x60(r1)
/* 8001118C 0000E0CC  F3 C1 00 68 */	psq_st f30, 104(r1), 0, qr0
/* 80011190 0000E0D0  DB A1 00 50 */	stfd f29, 0x50(r1)
/* 80011194 0000E0D4  F3 A1 00 58 */	psq_st f29, 88(r1), 0, qr0
/* 80011198 0000E0D8  DB 81 00 40 */	stfd f28, 0x40(r1)
/* 8001119C 0000E0DC  F3 81 00 48 */	psq_st f28, 72(r1), 0, qr0
/* 800111A0 0000E0E0  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800111A4 0000E0E4  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800111A8 0000E0E8  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800111AC 0000E0EC  93 81 00 30 */	stw r28, 0x30(r1)
/* 800111B0 0000E0F0  7C DF 33 78 */	mr r31, r6
/* 800111B4 0000E0F4  7C 7C 1B 78 */	mr r28, r3
/* 800111B8 0000E0F8  C0 46 00 00 */	lfs f2, 0(r6)
/* 800111BC 0000E0FC  7C 9D 23 78 */	mr r29, r4
/* 800111C0 0000E100  C0 26 00 10 */	lfs f1, 0x10(r6)
/* 800111C4 0000E104  7C BE 2B 78 */	mr r30, r5
/* 800111C8 0000E108  C0 06 00 20 */	lfs f0, 0x20(r6)
/* 800111CC 0000E10C  38 61 00 20 */	addi r3, r1, 0x20
/* 800111D0 0000E110  D0 41 00 20 */	stfs f2, 0x20(r1)
/* 800111D4 0000E114  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 800111D8 0000E118  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800111DC 0000E11C  48 0D 9D 65 */	bl PSVECMag
/* 800111E0 0000E120  D0 3C 00 00 */	stfs f1, 0(r28)
/* 800111E4 0000E124  38 61 00 14 */	addi r3, r1, 0x14
/* 800111E8 0000E128  C0 5F 00 04 */	lfs f2, 4(r31)
/* 800111EC 0000E12C  C0 3F 00 14 */	lfs f1, 0x14(r31)
/* 800111F0 0000E130  C0 1F 00 24 */	lfs f0, 0x24(r31)
/* 800111F4 0000E134  D0 41 00 14 */	stfs f2, 0x14(r1)
/* 800111F8 0000E138  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 800111FC 0000E13C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80011200 0000E140  48 0D 9D 41 */	bl PSVECMag
/* 80011204 0000E144  D0 3C 00 04 */	stfs f1, 4(r28)
/* 80011208 0000E148  38 61 00 08 */	addi r3, r1, 8
/* 8001120C 0000E14C  C0 5F 00 08 */	lfs f2, 8(r31)
/* 80011210 0000E150  C0 3F 00 18 */	lfs f1, 0x18(r31)
/* 80011214 0000E154  C0 1F 00 28 */	lfs f0, 0x28(r31)
/* 80011218 0000E158  D0 41 00 08 */	stfs f2, 8(r1)
/* 8001121C 0000E15C  D0 21 00 0C */	stfs f1, 0xc(r1)
/* 80011220 0000E160  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 80011224 0000E164  48 0D 9D 1D */	bl PSVECMag
/* 80011228 0000E168  D0 3C 00 08 */	stfs f1, 8(r28)
/* 8001122C 0000E16C  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 80011230 0000E170  C0 3F 00 1C */	lfs f1, 0x1c(r31)
/* 80011234 0000E174  D0 1E 00 00 */	stfs f0, 0(r30)
/* 80011238 0000E178  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8001123C 0000E17C  D0 3E 00 04 */	stfs f1, 4(r30)
/* 80011240 0000E180  C9 42 80 F0 */	lfd f10, lbl_80516450@sda21(r2)
/* 80011244 0000E184  D0 1E 00 08 */	stfs f0, 8(r30)
/* 80011248 0000E188  C0 02 80 EC */	lfs f0, lbl_8051644C@sda21(r2)
/* 8001124C 0000E18C  FD 60 50 90 */	fmr f11, f10
/* 80011250 0000E190  C0 3C 00 00 */	lfs f1, 0(r28)
/* 80011254 0000E194  FC 80 50 90 */	fmr f4, f10
/* 80011258 0000E198  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8001125C 0000E19C  41 82 00 0C */	beq .L_80011268
/* 80011260 0000E1A0  C8 02 80 F8 */	lfd f0, lbl_80516458@sda21(r2)
/* 80011264 0000E1A4  FD 40 08 24 */	fdiv f10, f0, f1
.L_80011268:
/* 80011268 0000E1A8  C0 02 80 EC */	lfs f0, lbl_8051644C@sda21(r2)
/* 8001126C 0000E1AC  C0 3C 00 04 */	lfs f1, 4(r28)
/* 80011270 0000E1B0  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 80011274 0000E1B4  41 82 00 0C */	beq .L_80011280
/* 80011278 0000E1B8  C8 02 80 F8 */	lfd f0, lbl_80516458@sda21(r2)
/* 8001127C 0000E1BC  FD 60 08 24 */	fdiv f11, f0, f1
.L_80011280:
/* 80011280 0000E1C0  C0 02 80 EC */	lfs f0, lbl_8051644C@sda21(r2)
/* 80011284 0000E1C4  C0 3C 00 08 */	lfs f1, 8(r28)
/* 80011288 0000E1C8  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8001128C 0000E1CC  41 82 00 0C */	beq .L_80011298
/* 80011290 0000E1D0  C8 02 80 F8 */	lfd f0, lbl_80516458@sda21(r2)
/* 80011294 0000E1D4  FC 80 08 24 */	fdiv f4, f0, f1
.L_80011298:
/* 80011298 0000E1D8  C0 1F 00 20 */	lfs f0, 0x20(r31)
/* 8001129C 0000E1DC  3C 60 80 51 */	lis r3, __float_epsilon@ha
/* 800112A0 0000E1E0  C0 5F 00 28 */	lfs f2, 0x28(r31)
/* 800112A4 0000E1E4  FF E0 02 B2 */	fmul f31, f0, f10
/* 800112A8 0000E1E8  C0 22 81 00 */	lfs f1, lbl_80516460@sda21(r2)
/* 800112AC 0000E1EC  C0 03 48 DC */	lfs f0, __float_epsilon@l(r3)
/* 800112B0 0000E1F0  FD 02 01 32 */	fmul f8, f2, f4
/* 800112B4 0000E1F4  C0 FF 00 24 */	lfs f7, 0x24(r31)
/* 800112B8 0000E1F8  C8 62 80 F8 */	lfd f3, lbl_80516458@sda21(r2)
/* 800112BC 0000E1FC  ED 21 00 32 */	fmuls f9, f1, f0
/* 800112C0 0000E200  C0 5F 00 14 */	lfs f2, 0x14(r31)
/* 800112C4 0000E204  C0 DF 00 10 */	lfs f6, 0x10(r31)
/* 800112C8 0000E208  C0 9F 00 00 */	lfs f4, 0(r31)
/* 800112CC 0000E20C  FC 3F 18 28 */	fsub f1, f31, f3
/* 800112D0 0000E210  FC 00 48 50 */	fneg f0, f9
/* 800112D4 0000E214  C0 BF 00 04 */	lfs f5, 4(r31)
/* 800112D8 0000E218  FC E7 02 F2 */	fmul f7, f7, f11
/* 800112DC 0000E21C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800112E0 0000E220  FC 42 02 F2 */	fmul f2, f2, f11
/* 800112E4 0000E224  FF A6 02 B2 */	fmul f29, f6, f10
/* 800112E8 0000E228  FC 25 02 F2 */	fmul f1, f5, f11
/* 800112EC 0000E22C  FF C4 02 B2 */	fmul f30, f4, f10
/* 800112F0 0000E230  4C 41 13 82 */	cror 2, 1, 2
/* 800112F4 0000E234  40 82 00 1C */	bne .L_80011310
/* 800112F8 0000E238  FC 20 08 50 */	fneg f1, f1
/* 800112FC 0000E23C  48 0B E6 91 */	bl atan2
/* 80011300 0000E240  FF 80 08 90 */	fmr f28, f1
/* 80011304 0000E244  C8 62 81 08 */	lfd f3, lbl_80516468@sda21(r2)
/* 80011308 0000E248  CB A2 80 F0 */	lfd f29, lbl_80516450@sda21(r2)
/* 8001130C 0000E24C  48 00 00 54 */	b .L_80011360
.L_80011310:
/* 80011310 0000E250  FC 1F 18 2A */	fadd f0, f31, f3
/* 80011314 0000E254  FC 00 48 40 */	fcmpo cr0, f0, f9
/* 80011318 0000E258  4C 40 13 82 */	cror 2, 0, 2
/* 8001131C 0000E25C  40 82 00 18 */	bne .L_80011334
/* 80011320 0000E260  48 0B E6 6D */	bl atan2
/* 80011324 0000E264  FF 80 08 90 */	fmr f28, f1
/* 80011328 0000E268  C8 62 81 10 */	lfd f3, lbl_80516470@sda21(r2)
/* 8001132C 0000E26C  CB A2 80 F0 */	lfd f29, lbl_80516450@sda21(r2)
/* 80011330 0000E270  48 00 00 30 */	b .L_80011360
.L_80011334:
/* 80011334 0000E274  FC 20 38 90 */	fmr f1, f7
/* 80011338 0000E278  FC 40 40 90 */	fmr f2, f8
/* 8001133C 0000E27C  48 0B E6 51 */	bl atan2
/* 80011340 0000E280  FF 80 08 90 */	fmr f28, f1
/* 80011344 0000E284  FC 20 E8 90 */	fmr f1, f29
/* 80011348 0000E288  FC 40 F0 90 */	fmr f2, f30
/* 8001134C 0000E28C  48 0B E6 41 */	bl atan2
/* 80011350 0000E290  FF A0 08 90 */	fmr f29, f1
/* 80011354 0000E294  FC 20 F8 50 */	fneg f1, f31
/* 80011358 0000E298  48 0B E6 15 */	bl asin
/* 8001135C 0000E29C  FC 60 08 90 */	fmr f3, f1
.L_80011360:
/* 80011360 0000E2A0  C8 02 81 18 */	lfd f0, lbl_80516478@sda21(r2)
/* 80011364 0000E2A4  FF 9C 00 32 */	fmul f28, f28, f0
/* 80011368 0000E2A8  FC 63 00 32 */	fmul f3, f3, f0
/* 8001136C 0000E2AC  FF BD 00 32 */	fmul f29, f29, f0
/* 80011370 0000E2B0  FC 40 E0 18 */	frsp f2, f28
/* 80011374 0000E2B4  FC 20 18 18 */	frsp f1, f3
/* 80011378 0000E2B8  FC 00 E8 18 */	frsp f0, f29
/* 8001137C 0000E2BC  D0 5D 00 00 */	stfs f2, 0(r29)
/* 80011380 0000E2C0  D0 3D 00 04 */	stfs f1, 4(r29)
/* 80011384 0000E2C4  D0 1D 00 08 */	stfs f0, 8(r29)
/* 80011388 0000E2C8  E3 E1 00 78 */	psq_l f31, 120(r1), 0, qr0
/* 8001138C 0000E2CC  CB E1 00 70 */	lfd f31, 0x70(r1)
/* 80011390 0000E2D0  E3 C1 00 68 */	psq_l f30, 104(r1), 0, qr0
/* 80011394 0000E2D4  CB C1 00 60 */	lfd f30, 0x60(r1)
/* 80011398 0000E2D8  E3 A1 00 58 */	psq_l f29, 88(r1), 0, qr0
/* 8001139C 0000E2DC  CB A1 00 50 */	lfd f29, 0x50(r1)
/* 800113A0 0000E2E0  E3 81 00 48 */	psq_l f28, 72(r1), 0, qr0
/* 800113A4 0000E2E4  CB 81 00 40 */	lfd f28, 0x40(r1)
/* 800113A8 0000E2E8  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800113AC 0000E2EC  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800113B0 0000E2F0  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800113B4 0000E2F4  80 01 00 84 */	lwz r0, 0x84(r1)
/* 800113B8 0000E2F8  83 81 00 30 */	lwz r28, 0x30(r1)
/* 800113BC 0000E2FC  7C 08 03 A6 */	mtlr r0
/* 800113C0 0000E300  38 21 00 80 */	addi r1, r1, 0x80
/* 800113C4 0000E304  4E 80 00 20 */	blr 
.endfn getFromTransformation_SRxyzT__Q27JStudio4mathFP3VecP3VecP3VecPA4_Cf