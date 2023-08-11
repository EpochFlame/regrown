.include "macros.inc"

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.fn __ct__18JPAResourceManagerFPCvP7JKRHeap, global
/* 800984D0 00095410  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800984D4 00095414  7C 08 02 A6 */	mflr r0
/* 800984D8 00095418  90 01 00 24 */	stw r0, 0x24(r1)
/* 800984DC 0009541C  38 00 00 00 */	li r0, 0
/* 800984E0 00095420  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800984E4 00095424  7C 7F 1B 78 */	mr r31, r3
/* 800984E8 00095428  90 03 00 04 */	stw r0, 4(r3)
/* 800984EC 0009542C  38 61 00 08 */	addi r3, r1, 8
/* 800984F0 00095430  90 1F 00 08 */	stw r0, 8(r31)
/* 800984F4 00095434  B0 1F 00 0C */	sth r0, 0xc(r31)
/* 800984F8 00095438  B0 1F 00 0E */	sth r0, 0xe(r31)
/* 800984FC 0009543C  B0 1F 00 10 */	sth r0, 0x10(r31)
/* 80098500 00095440  B0 1F 00 12 */	sth r0, 0x12(r31)
/* 80098504 00095444  90 BF 00 00 */	stw r5, 0(r31)
/* 80098508 00095448  7F E5 FB 78 */	mr r5, r31
/* 8009850C 0009544C  4B FF FB CD */	bl __ct__17JPAResourceLoaderFPCUcP18JPAResourceManager
/* 80098510 00095450  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80098514 00095454  7F E3 FB 78 */	mr r3, r31
/* 80098518 00095458  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8009851C 0009545C  7C 08 03 A6 */	mtlr r0
/* 80098520 00095460  38 21 00 20 */	addi r1, r1, 0x20
/* 80098524 00095464  4E 80 00 20 */	blr 
.endfn __ct__18JPAResourceManagerFPCvP7JKRHeap

.fn getResource__18JPAResourceManagerCFUs, global
/* 80098528 00095468  A0 C3 00 0E */	lhz r6, 0xe(r3)
/* 8009852C 0009546C  54 84 04 3E */	clrlwi r4, r4, 0x10
/* 80098530 00095470  80 A3 00 04 */	lwz r5, 4(r3)
/* 80098534 00095474  38 E0 00 00 */	li r7, 0
/* 80098538 00095478  48 00 00 1C */	b .L_80098554
.L_8009853C:
/* 8009853C 0009547C  54 E0 13 BA */	rlwinm r0, r7, 2, 0xe, 0x1d
/* 80098540 00095480  7C 65 00 2E */	lwzx r3, r5, r0
/* 80098544 00095484  A0 03 00 3C */	lhz r0, 0x3c(r3)
/* 80098548 00095488  7C 04 00 40 */	cmplw r4, r0
/* 8009854C 0009548C  4D 82 00 20 */	beqlr 
/* 80098550 00095490  38 E7 00 01 */	addi r7, r7, 1
.L_80098554:
/* 80098554 00095494  54 E0 04 3E */	clrlwi r0, r7, 0x10
/* 80098558 00095498  7C 00 30 40 */	cmplw r0, r6
/* 8009855C 0009549C  41 80 FF E0 */	blt .L_8009853C
/* 80098560 000954A0  38 60 00 00 */	li r3, 0
/* 80098564 000954A4  4E 80 00 20 */	blr 
.endfn getResource__18JPAResourceManagerCFUs

.fn swapTexture__18JPAResourceManagerFPC7ResTIMGPCc, global
/* 80098568 000954A8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8009856C 000954AC  7C 08 02 A6 */	mflr r0
/* 80098570 000954B0  90 01 00 24 */	stw r0, 0x24(r1)
/* 80098574 000954B4  BF 41 00 08 */	stmw r26, 8(r1)
/* 80098578 000954B8  7C 7A 1B 78 */	mr r26, r3
/* 8009857C 000954BC  7C 9B 23 78 */	mr r27, r4
/* 80098580 000954C0  7C BC 2B 78 */	mr r28, r5
/* 80098584 000954C4  3B C0 00 00 */	li r30, 0
/* 80098588 000954C8  3B A0 00 00 */	li r29, 0
/* 8009858C 000954CC  3B E0 00 00 */	li r31, 0
/* 80098590 000954D0  48 00 00 50 */	b .L_800985E0
.L_80098594:
/* 80098594 000954D4  80 9A 00 08 */	lwz r4, 8(r26)
/* 80098598 000954D8  7F 83 E3 78 */	mr r3, r28
/* 8009859C 000954DC  7C 84 F8 2E */	lwzx r4, r4, r31
/* 800985A0 000954E0  80 84 00 44 */	lwz r4, 0x44(r4)
/* 800985A4 000954E4  38 84 00 0C */	addi r4, r4, 0xc
/* 800985A8 000954E8  48 03 21 19 */	bl strcmp
/* 800985AC 000954EC  2C 03 00 00 */	cmpwi r3, 0
/* 800985B0 000954F0  40 82 00 28 */	bne .L_800985D8
/* 800985B4 000954F4  80 7A 00 08 */	lwz r3, 8(r26)
/* 800985B8 000954F8  57 A0 10 3A */	slwi r0, r29, 2
/* 800985BC 000954FC  7F 64 DB 78 */	mr r4, r27
/* 800985C0 00095500  38 A0 00 00 */	li r5, 0
/* 800985C4 00095504  7C 63 00 2E */	lwzx r3, r3, r0
/* 800985C8 00095508  38 63 00 04 */	addi r3, r3, 4
/* 800985CC 0009550C  83 C3 00 20 */	lwz r30, 0x20(r3)
/* 800985D0 00095510  4B F9 AA B5 */	bl storeTIMG__10JUTTextureFPC7ResTIMGUc
/* 800985D4 00095514  48 00 00 18 */	b .L_800985EC
.L_800985D8:
/* 800985D8 00095518  3B FF 00 04 */	addi r31, r31, 4
/* 800985DC 0009551C  3B BD 00 01 */	addi r29, r29, 1
.L_800985E0:
/* 800985E0 00095520  A0 1A 00 12 */	lhz r0, 0x12(r26)
/* 800985E4 00095524  7C 1D 00 00 */	cmpw r29, r0
/* 800985E8 00095528  41 80 FF AC */	blt .L_80098594
.L_800985EC:
/* 800985EC 0009552C  7F C3 F3 78 */	mr r3, r30
/* 800985F0 00095530  BB 41 00 08 */	lmw r26, 8(r1)
/* 800985F4 00095534  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800985F8 00095538  7C 08 03 A6 */	mtlr r0
/* 800985FC 0009553C  38 21 00 20 */	addi r1, r1, 0x20
/* 80098600 00095540  4E 80 00 20 */	blr 
.endfn swapTexture__18JPAResourceManagerFPC7ResTIMGPCc

.fn registRes__18JPAResourceManagerFP11JPAResource, global
/* 80098604 00095544  A0 03 00 0E */	lhz r0, 0xe(r3)
/* 80098608 00095548  80 A3 00 04 */	lwz r5, 4(r3)
/* 8009860C 0009554C  54 00 10 3A */	slwi r0, r0, 2
/* 80098610 00095550  7C 85 01 2E */	stwx r4, r5, r0
/* 80098614 00095554  A0 83 00 0E */	lhz r4, 0xe(r3)
/* 80098618 00095558  38 04 00 01 */	addi r0, r4, 1
/* 8009861C 0009555C  B0 03 00 0E */	sth r0, 0xe(r3)
/* 80098620 00095560  4E 80 00 20 */	blr 
.endfn registRes__18JPAResourceManagerFP11JPAResource

.fn registTex__18JPAResourceManagerFP10JPATexture, global
/* 80098624 00095564  A0 03 00 12 */	lhz r0, 0x12(r3)
/* 80098628 00095568  80 A3 00 08 */	lwz r5, 8(r3)
/* 8009862C 0009556C  54 00 10 3A */	slwi r0, r0, 2
/* 80098630 00095570  7C 85 01 2E */	stwx r4, r5, r0
/* 80098634 00095574  A0 83 00 12 */	lhz r4, 0x12(r3)
/* 80098638 00095578  38 04 00 01 */	addi r0, r4, 1
/* 8009863C 0009557C  B0 03 00 12 */	sth r0, 0x12(r3)
/* 80098640 00095580  4E 80 00 20 */	blr 
.endfn registTex__18JPAResourceManagerFP10JPATexture

.fn getResUserWork__18JPAResourceManagerCFUs, global
/* 80098644 00095584  A0 E3 00 0E */	lhz r7, 0xe(r3)
/* 80098648 00095588  54 84 04 3E */	clrlwi r4, r4, 0x10
/* 8009864C 0009558C  80 A3 00 04 */	lwz r5, 4(r3)
/* 80098650 00095590  38 60 00 00 */	li r3, 0
/* 80098654 00095594  38 C0 00 00 */	li r6, 0
/* 80098658 00095598  48 00 00 20 */	b .L_80098678
.L_8009865C:
/* 8009865C 0009559C  54 C0 13 BA */	rlwinm r0, r6, 2, 0xe, 0x1d
/* 80098660 000955A0  7D 05 00 2E */	lwzx r8, r5, r0
/* 80098664 000955A4  A0 08 00 3C */	lhz r0, 0x3c(r8)
/* 80098668 000955A8  7C 04 00 40 */	cmplw r4, r0
/* 8009866C 000955AC  40 82 00 08 */	bne .L_80098674
/* 80098670 000955B0  48 00 00 18 */	b .L_80098688
.L_80098674:
/* 80098674 000955B4  38 C6 00 01 */	addi r6, r6, 1
.L_80098678:
/* 80098678 000955B8  54 C0 04 3E */	clrlwi r0, r6, 0x10
/* 8009867C 000955BC  7C 00 38 40 */	cmplw r0, r7
/* 80098680 000955C0  41 80 FF DC */	blt .L_8009865C
/* 80098684 000955C4  39 00 00 00 */	li r8, 0
.L_80098688:
/* 80098688 000955C8  28 08 00 00 */	cmplwi r8, 0
/* 8009868C 000955CC  4D 82 00 20 */	beqlr 
/* 80098690 000955D0  80 68 00 2C */	lwz r3, 0x2c(r8)
/* 80098694 000955D4  80 63 00 00 */	lwz r3, 0(r3)
/* 80098698 000955D8  80 63 00 0C */	lwz r3, 0xc(r3)
/* 8009869C 000955DC  4E 80 00 20 */	blr 
.endfn getResUserWork__18JPAResourceManagerCFUs