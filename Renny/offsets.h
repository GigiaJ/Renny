#define fnLogger 0x17A5C0
#define fnLogUIEvents 0x17E870
#define fnCastSpell 0x534BE0
#define fnGetHealthbarPos 0x1C1DE0
#define fnEventHandler 0x243AA0
#define fnMainLoop 0x7410A0
#define fnDrawTurretRange 0x205580
#define fnLevelUpSpell 0x536F80
#define fnSetSkin 0x208750
#define fnGetSpellData 0x52A3E0
#define fnPrintChat 0x5619B0
#define fnOpenChat 0x560EE0
#define fnDisplayChat 0x550000
#define fnSendChat 0x635A00
#define fnSetChatScale 0x55F100
#define fnIssueOrder 0x1C9A40
#define fnOnMoveMouseClick 0x5A4740
#define fnCheckIfInitialClickIsAvaliable 0x75BD60
#define fnOnProcessSpell 0x52B250
#define fnOnProcessSpellW 0x535F20
#define fnOnSpellCast 0x1CFA70
#define fnOnAutoAttack 0x1E49A0
#define fnSetPath 0x2162C0
#define fnCreatePath 0x751E40
#define fnOnUpdatePath 0x8656D0
#define fnIsWallOfGrass 0x7593A0
#define fnDispatchEvent 0x2C74E0
#define fnLoadTexture 0x7EAE50
#define fnOnProcessPacket 0x32F9F0
#define fnInitEvent 0x2352C0
#define fnOnLoadHero 0x33DCF0
#define fnOnLoadChampion 0x1BDFB0
#define fnOnTeleport 0x1E7600
#define fnOnDisconnect 0x5CC230
#define fnOnAfk 0x5CC580
#define fnSmartPing 0x649EC0
#define fnGameUpdate 0x3167C0
#define fnClientMain 0x28DC20
#define fnPlaySound 0x274C40
#define fnGetBasicAttack 0x1C0FE0
#define fnGetAttackDelay 0x53AD60
#define fnGetAttackCastDelay 0x296400
#define fnUseObject 0x198B80
#define fnCreateObject 0x2E7E90
#define fnIdentifyObject 0x249C70
#define fnDeleteObject 0x2D70B0
#define fnAddRemoveBuff 0x525390
#define fnLevelUp 0x228700
#define fnAssignNetworkID 0x2E2900
#define fnUpdateBuff 0x50B140
#define fnDoEmote 0x61AF40
#define fnDoMasteryBadge 0x575670
#define fnOnSurrenderVote 0x6380B0
#define fnUpdateChargeableSpell 0x536C60
#define fnApplySpellCD 0x52E8C0
#define fnStopCast 0x5363D0
#define fnGetBoundingRadius 0x1F4180
#define fnWorldToScreen 0x7F1B60
#define fnScreenToWorld 0x7F1C40
#define fnMapToWorld 0x606B30
#define fnWorld2Map 0x28BF40
#define fnGetTacticalMap 0x1C8AF0
#define j_CReplInfo32__AddVar 0x1F7020
#define CReplInfo32_AddVar 0x205270

#define oLocalPlayer 0x2E2345C
#define oChatClientPtr 0x2E2C138
#define oObjManager 0x2E227F8
#define oRenderer 0x2E49528
#define oZoomClass 0x2E1F568
#define oUnderMouseObject 0x21CBF0C
#define oCursor 0x157AFB8
#define oMissionInfo 0x2E4ED84
#define oGameState 0x2E1FE90
#define oVersion 0x2E2A7C0
#define oNetClient 0x2E25BEC
#define oTexturePack 0x2E27718
#define oGameTime 0x2E1F614



#define pSpellBookPtr 0x1CB8

// Generated using ReClass 2016

struct Vector
{
	float x;
	float y;
	float z;

	inline bool operator!=(Vector a) {
		if (x != a.x) {
			return true;
		}
		if (y != a.y) {
			return true;
		}
		if (z != a.z) {
			return true;
		}
		return false;
	}

	inline Vector operator + (const Vector a) const { return Vector{ x + a.x, y + a.y, z + a.z }; }
	inline Vector operator - (const Vector a) const { return Vector{ x - a.x, y - a.y, z - a.z }; }

	inline Vector operator+(float a) const { return Vector{ x + a, y + a, z + a }; }

};

#define EMPTYVECTOR Vector {}


class ReClassFloat;
class object;
class objectManager;
class activeSpell;
class spellCastDataBase;
class spellData;
class oMouse;
class spellInfo;
class AIManager;
class spellInst;
class Obj_AI_Base;

class ReClassFloat
{
public:
	float value; //0x0000 

}; //Size=0x0004

class object
{
public:
	unsigned char pad_0x0000[0x14]; //0x0000
	int mTeam; //0x0014 
	int mUnitType; //0x0018 
	unsigned char pad_0x001C[0x18]; //0x001C
	int mGeneralType; //0x0034 
	unsigned char pad_0x0038[0x34]; //0x0038
	int mNetworkId; //0x006C 
	unsigned char pad_0x0070[0x8]; //0x0070
	Vector mEdgePos1; //0x0078 
	Vector mEdgePos2; //0x0084 
	unsigned char pad_0x0090[0x3C]; //0x0090
	Vector mUnitPos; //0x00CC 
	unsigned char pad_0x00D8[0x18]; //0x00D8
	bool mIsDead; //0x00F0 
	unsigned char pad_0x00F1[0x1BF]; //0x00F1
	bool isVisible; //0x02B0 
	unsigned char pad_0x02B1[0x13]; //0x02B1
	float mPAR; //0x02C4 
	unsigned char pad_0x02C8[0xC]; //0x02C8
	float mMaxPAR; //0x02D4 
	unsigned char pad_0x02D8[0xC]; //0x02D8
	bool mPAREnabled; //0x02E4 
	unsigned char pad_0x02E5[0x1F]; //0x02E5
	int mPARState; //0x0304 
	unsigned char pad_0x0308[0x1C]; //0x0308
	float mSAR; //0x0324 
	unsigned char pad_0x0328[0xC]; //0x0328
	float mMaxSAR; //0x0334 
	unsigned char pad_0x0338[0xC]; //0x0338
	bool mSAREnabled; //0x0344 
	unsigned char pad_0x0345[0xF]; //0x0345
	bool mEMpoweredBitField; //0x0354 
	unsigned char pad_0x0355[0xF]; //0x0355
	int mSARState; //0x0364 
	unsigned char pad_0x0368[0x200]; //0x0368
	float mLifetime; //0x0568 
	unsigned char pad_0x056C[0xC]; //0x056C
	float mMaxLifeTime; //0x0578 
	unsigned char pad_0x057C[0xC]; //0x057C
	float mLifeTimeTicks; //0x0588 
	unsigned char pad_0x058C[0x28]; //0x058C
	float mPhysicalDamagePercentageModifier; //0x05B4 
	unsigned char pad_0x05B8[0xC]; //0x05B8
	float mMagicalDamagePercentageModifier; //0x05C4 
	unsigned char pad_0x05C8[0x1C]; //0x05C8
	bool mIsUntargetableToEnemies; //0x05E4 
	unsigned char pad_0x05E5[0xF]; //0x05E5
	bool mIsUntargetableToAllies; //0x05F4 
	unsigned char pad_0x05F5[0xF]; //0x05F5
	bool mIsTargetable; //0x0604 
	unsigned char pad_0x0605[0xF]; //0x0605
	bool mIsTargetableToTeamFlags; //0x0614 
	unsigned char pad_0x0615[0x5B]; //0x0615
	float mHP; //0x0670 
	unsigned char pad_0x0674[0xC]; //0x0674
	float mMaxHP; //0x0680 
	unsigned char pad_0x0684[0xC]; //0x0684
	float mHPMaxPenalty; //0x0690 
	unsigned char pad_0x0694[0x1C]; //0x0694
	float mAllShield; //0x06B0 
	unsigned char pad_0x06B4[0xC]; //0x06B4
	float mPhysicalShield; //0x06C0 
	unsigned char pad_0x06C4[0xC]; //0x06C4
	float mMagicalShield; //0x06D0 
	unsigned char pad_0x06D4[0xC]; //0x06D4
	float mChampSpecificHealth; //0x06E0 
	unsigned char pad_0x06E4[0xC]; //0x06E4
	int mStopShieldFade; //0x06F0 
	unsigned char pad_0x06F4[0x168]; //0x06F4
	float mNegativeCurrentCDR; //0x085C 
	unsigned char pad_0x0860[0xC]; //0x0860
	float mNegativeMaxCDR; //0x086C 
	unsigned char pad_0x0870[0x5B0]; //0x0870
	float mPercentCooldownCapMod; //0x0E20 
	unsigned char pad_0x0E24[0xC]; //0x0E24
	float mPassiveCooldownEndTime; //0x0E30 
	unsigned char pad_0x0E34[0xC]; //0x0E34
	float mPassiveCooldownTotalTime; //0x0E40 
	unsigned char pad_0x0E44[0xC]; //0x0E44
	float mPercentDamageToBarracksMinionMod; //0x0E50 
	unsigned char pad_0x0E54[0xC]; //0x0E54
	float mFlatDamageReductionFromBarracksMinionMod; //0x0E60 
	unsigned char pad_0x0E64[0xC]; //0x0E64
	float mFlatPhysicalDamageMod; //0x0E70 
	unsigned char pad_0x0E74[0xC]; //0x0E74
	float mPercentPhysicalDamageMod; //0x0E80 
	unsigned char pad_0x0E84[0x1C]; //0x0E84
	float mPercentBasePhysicalDamageAsFlatBonusMod; //0x0EA0 
	unsigned char pad_0x0EA4[0xC]; //0x0EA4
	float mFlatMagicDamageMod; //0x0EB0 
	unsigned char pad_0x0EB4[0xC]; //0x0EB4
	float mPercentMagicDamageMod; //0x0EC0 
	unsigned char pad_0x0EC4[0xC]; //0x0EC4
	float mFlatMagicReduction; //0x0ED0 
	unsigned char pad_0x0ED4[0xC]; //0x0ED4
	float mPercentMagicReduction; //0x0EE0 
	unsigned char pad_0x0EE4[0xC]; //0x0EE4
	float mFlatCastRangeMod; //0x0EF0 
	unsigned char pad_0x0EF4[0xC]; //0x0EF4
	float mAttackSpeedMod; //0x0F00 
	unsigned char pad_0x0F04[0xC]; //0x0F04
	float mPercentAttackSpeedMod; //0x0F10 
	unsigned char pad_0x0F14[0xC]; //0x0F14
	float mPercentMultiplicativeAttackSpeedMod; //0x0F20 
	unsigned char pad_0x0F24[0xC]; //0x0F24
	float mBaseAttackDamage; //0x0F30 
	unsigned char pad_0x0F34[0xC]; //0x0F34
	float mBaseAttackDamageSansPercentScale; //0x0F40 
	unsigned char pad_0x0F44[0xC]; //0x0F44
	float mFlatBaseAttackDamageMod; //0x0F50 
	unsigned char pad_0x0F54[0xC]; //0x0F54
	float mPercentBaseAttackDamageMod; //0x0F60 
	unsigned char pad_0x0F64[0xC]; //0x0F64
	float mBaseAbilityDamage; //0x0F70 
	unsigned char pad_0x0F74[0xC]; //0x0F74
	float mScaleSkinCoef; //0x0F80 
	unsigned char pad_0x0F84[0xC]; //0x0F84
	float mDodge; //0x0F90 
	unsigned char pad_0x0F94[0xC]; //0x0F94
	float mCrit; //0x0FA0 
	unsigned char pad_0x0FA4[0xC]; //0x0FA4
	float mArmor; //0x0FB0 
	unsigned char pad_0x0FB4[0xC]; //0x0FB4
	float mBonusArmor; //0x0FC0 
	unsigned char pad_0x0FC4[0xC]; //0x0FC4
	float mSpellBlock; //0x0FD0 
	unsigned char pad_0x0FD4[0xC]; //0x0FD4
	float mBonusSpellBlock; //0x0FE0 
	unsigned char pad_0x0FE4[0xC]; //0x0FE4
	float mHPRegenRate; //0x0FF0 
	unsigned char pad_0x0FF4[0xC]; //0x0FF4
	float mBaseHPRegenRate; //0x1000 
	unsigned char pad_0x1004[0xC]; //0x1004
	float mMoveSpeed; //0x1010 
	unsigned char pad_0x1014[0xC]; //0x1014
	float mMoveSpeedBaseIncrease; //0x1020 
	unsigned char pad_0x1024[0xC]; //0x1024
	float mAttackRange; //0x1030 
	unsigned char pad_0x1034[0xC]; //0x1034
	float mFlatBubbleRadiusMod; //0x1040 
	unsigned char pad_0x1044[0xC]; //0x1044
	float mPercentBubbleRadiusMod; //0x1050 
	unsigned char pad_0x1054[0xC]; //0x1054
	float mFlatArmorPenetration; //0x1060 
	unsigned char pad_0x1064[0xC]; //0x1064
	float mPhysicalLethality; //0x1070 
	unsigned char pad_0x1074[0xC]; //0x1074
	float mPercentArmorPenetration; //0x1080 
	unsigned char pad_0x1084[0xC]; //0x1084
	float mPercentBonusArmorPenetration; //0x1090 
	unsigned char pad_0x1094[0xC]; //0x1094
	float mPercentCritBonusArmorPenetration; //0x10A0 
	unsigned char pad_0x10A4[0xC]; //0x10A4
	float mPercentCritTotalArmorPenetration; //0x10B0 
	unsigned char pad_0x10B4[0xC]; //0x10B4
	float mFlatMagicPenetration; //0x10C0 
	unsigned char pad_0x10C4[0xC]; //0x10C4
	float mMagicLethality; //0x10D0 
	unsigned char pad_0x10D4[0xC]; //0x10D4
	float mPercentMagicPenetration; //0x10E0 
	unsigned char pad_0x10E4[0xC]; //0x10E4
	float mPercentBonusMagicPenetration; //0x10F0 
	unsigned char pad_0x10F4[0xC]; //0x10F4
	float mPercentLifeStealMod; //0x1100 
	unsigned char pad_0x1104[0xC]; //0x1104
	float mPercentSpellVampMod; //0x1110 
	unsigned char pad_0x1114[0x1C]; //0x1114
	float mPercentCCReduction; //0x1130 
	unsigned char pad_0x1134[0xC]; //0x1134
	float mPercentEXPBonus; //0x1140 
	unsigned char pad_0x1144[0xC]; //0x1144
	float mPrimaryARRegenRateRep; //0x1150 
	unsigned char pad_0x1154[0xC]; //0x1154
	float mPrimaryARBaseRegenRateRep; //0x1160 
	unsigned char pad_0x1164[0xC]; //0x1164
	float mSecondaryARRegenRateRep; //0x1170 
	unsigned char pad_0x1174[0xC]; //0x1174
	float mSecondaryARBaseRegenRateRep; //0x1180 
	unsigned char pad_0x1184[0xC4]; //0x1184
	float mGold; //0x1248 
	unsigned char pad_0x124C[0xC]; //0x124C
	float mGoldTotal; //0x1258 
	unsigned char pad_0x125C[0xC]; //0x125C
	float mMinimumGold; //0x1268 
	unsigned char pad_0x126C[0x164]; //0x126C
	Vector mDirectionFaced; //0x13D0 
	unsigned char pad_0x13DC[0x3B8]; //0x13DC
	Obj_AI_Base* mCharData; //0x1794 
	unsigned char pad_0x1798[0x540]; //0x1798
	activeSpell* mActiveSpell; //0x1CD8 
	unsigned char pad_0x1CDC[0x50C]; //0x1CDC
	spellInst* mSpellInstArray[4]; //0x21E8 
	spellInst* mPartOfSpellInst1; //0x21EC 
	spellInst* mPartOfSpellInst2; //0x21F0 
	spellInst* mPartOfSpellInst4; //0x21F4 
	unsigned char pad_0x21F8[0x16FC]; //0x21F8
	int mEvolvePoints; //0x38F4 
	unsigned char pad_0x38F8[0xC]; //0x38F8
	int mEvolveFlag; //0x3904 
	unsigned char pad_0x3908[0xC]; //0x3908
	float mExp; //0x3914 
	unsigned char pad_0x3918[0xC]; //0x3918
	float mLevelRef; //0x3924 
	unsigned char pad_0x3928[0xC]; //0x3928
	bool mSkillUpLevelDeltaReplicate; //0x3934 
	unsigned char pad_0x3935[0x497]; //0x3935
	float mVisionScore; //0x3DCC 
	unsigned char pad_0x3DD0[0x4B0]; //0x3DD0
	int mNumNeutralMinionsKilled; //0x4280 
	unsigned char pad_0x4284[0x20]; //0x4284
	int mInputLocks; //0x42A4 
	unsigned char pad_0x42A8[0xC]; //0x42A8
	int mHealthBarCharacterIDForIcon; //0x42B4 
	unsigned char pad_0x42B8[0x530]; //0x42B8
	float mPhysicalDamageTaken; //0x47E8 
	unsigned char pad_0x47EC[0xC]; //0x47EC
	float mMagicDamageTaken; //0x47F8 
	unsigned char pad_0x47FC[0xC]; //0x47FC
	float mTrueDamageTaken; //0x4808 
	unsigned char pad_0x480C[0x538]; //0x480C

	float getUnitSize() {
		return (this->mEdgePos2.x - this->mEdgePos1.x);
	}
}; //Size=0x4D44

class objectManager
{
public:
	unsigned char pad_0x0000[0x8]; //0x0000
	object* *mObjectManagerArray; //0x0008 
	int mArrayMaxSize; //0x000C 
	int mArrayCurrentUsedIndex; //0x0010 
	int mArrayHighestIndex; //0x0014 
	unsigned char pad_0x0018[0xC]; //0x0018

}; //Size=0x0024

class activeSpell
{
public:
	unsigned char pad_0x0000[0x804]; //0x0000

}; //Size=0x0804

class spellCastDataBase
{
public:
	spellData * mSpellData; //0x0000 
	unsigned char pad_0x0004[0x14]; //0x0004
	int mSpellRank; //0x0018 
	unsigned char pad_0x001C[0x4]; //0x001C
	short mCasterIndex; //0x0020 
	unsigned char pad_0x0022[0x16]; //0x0022
	Vector mStartPosition; //0x0038 
	Vector mTargetPosition; //0x0044 
	unsigned char pad_0x0050[0xC]; //0x0050
	Vector mDirectionFacedAtCast; //0x005C 
	bool mHasTarget; //0x0068 
	unsigned char pad_0x0069[0x3]; //0x0069
	short mTargetIndex; //0x006C 
	unsigned char pad_0x006E[0x3FE]; //0x006E
	float mWindUpTime; //0x046C 
	unsigned char pad_0x0470[0xC]; //0x0470
	float mAnimationTime; //0x047C 
	float mSpellCoolDown; //0x0480 
	unsigned char pad_0x0484[0x4]; //0x0484
	__int8 mIsSpellCast; //0x0488 
	unsigned char pad_0x0489[0x4]; //0x0489
	__int8 mIsAutoAttack; //0x048D 
	unsigned char pad_0x048E[0x6]; //0x048E
	float mSpellSlot; //0x0494 
	unsigned char pad_0x0498[0x4]; //0x0498
	float mManaCost; //0x049C 
	unsigned char pad_0x04A0[0x460]; //0x04A0

	int getSpellRank() {
		return this->mSpellRank + 1;
	}
}; //Size=0x0900

class spellData
{
public:
	unsigned char pad_0x0000[0x38]; //0x0000
	spellInfo* mSpellInfo; //0x0038 
	unsigned char pad_0x003C[0x3CC]; //0x003C

}; //Size=0x0408

class oMouse
{
public:
	unsigned char pad_0x0000[0x90]; //0x0000
	Vector mMousePos; //0x0090 
	unsigned char pad_0x009C[0x3A4]; //0x009C

}; //Size=0x0440

class spellInfo
{
public:
	unsigned char pad_0x0000[0x1F4]; //0x0000
	float mAnimationTime; //0x01F4 
	float mCastTime; //0x01F8 
	unsigned char pad_0x01FC[0x78]; //0x01FC
	ReClassFloat mCoolDownTime[7]; //0x0274 
	unsigned char pad_0x0290[0x100]; //0x0290
	ReClassFloat mMaxRangeForPlacement[7]; //0x0390 
	ReClassFloat mMaxRange[7]; //0x03AC 
	ReClassFloat mCastRadius[7]; //0x03C8 
	unsigned char pad_0x03E4[0x48]; //0x03E4
	float mMissileSpeed; //0x042C 
	unsigned char pad_0x0430[0x30]; //0x0430
	float mMissileWidth; //0x0460 
	unsigned char pad_0x0464[0x20C]; //0x0464

}; //Size=0x0670

class AIManager
{
public:
	unsigned char pad_0x0000[0x194]; //0x0000
	float mCurrentMovementSpeed; //0x0194 
	bool mIsMoving; //0x0198 
	unsigned char pad_0x0199[0xB]; //0x0199
	Vector mLastPosition; //0x01A4 
	Vector mNextPosition; //0x01B0 
	unsigned char pad_0x01BC[0x1A0]; //0x01BC
	Vector mDashEndPosition; //0x035C 
	unsigned char pad_0x0368[0x2C]; //0x0368
	bool mIsDashing; //0x0394 
	unsigned char pad_0x0395[0x26F]; //0x0395

}; //Size=0x0604

class spellInst
{
public:
	unsigned char pad_0x0000[0x1C]; //0x0000
	int mCurrentRank; //0x001C 
	unsigned char pad_0x0020[0xFC]; //0x0020
	spellData* mSpellData; //0x011C 
	unsigned char pad_0x0120[0x42C]; //0x0120

	float  getCoolDown(object* unit) {
		return this->mSpellData->mSpellInfo->mCoolDownTime[this->mCurrentRank + 1].value - (this->mSpellData->mSpellInfo->mCoolDownTime[this->mCurrentRank + 1].value * (-unit->mNegativeCurrentCDR));
	}

	static spellInst* getSpellInst(DWORD unit, int slot) {
		return (spellInst*)(unit + (0x20C0 + (slot * 0x04)));
	}
}; //Size=0x054C

class Obj_AI_Base
{
public:
	unsigned char pad_0x0000[0x4]; //0x0000
	AIManager* AIHeroClient; //0x0004 

}; //Size=0x0008

