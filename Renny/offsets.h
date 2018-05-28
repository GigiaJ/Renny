#define fnLogger 0x17A740
#define fnLogUIEvents 0x17EE10
#define fnCastSpell 0x540720
#define fnGetHealthbarPos 0x1C2290
#define fnEventHandler 0x2450B0
#define fnMainLoop 0x74D0A0
#define fnDrawTurretRange 0x206400
#define fnLevelUpSpell 0x542C70
#define fnSetSkin 0x2095D0
#define fnGetSpellData 0x536080
#define fnPrintChat 0x56CD30
#define fnOpenChat 0x56C280
#define fnDisplayChat 0x55B380
#define fnSendChat 0x641AB0
#define fnSetChatScale 0x56A4A0
#define fnIssueOrder 0x1C9EA0
#define fnOnMoveMouseClick 0x5AFF60
#define fnCheckIfInitialClickIsAvaliable 0x767FF0
#define fnOnProcessSpell 0x536E90
#define fnOnProcessSpellW 0x541B50
#define fnOnSpellCast 0x1CFE50
#define fnOnAutoAttack 0x1E55A0
#define fnSetPath 0x217F20
#define fnCreatePath 0x75E0D0
#define fnOnUpdatePath 0x870190
#define fnIsWallOfGrass 0x765630
#define fnDispatchEvent 0x2BBE30
#define fnLoadTexture 0x7F5E90
#define fnOnProcessPacket 0x3312B0
#define fnInitEvent 0x2369B0
#define fnOnLoadHero 0x341060
#define fnOnLoadChampion 0x1BE470
#define fnOnTeleport 0x1E8250
#define fnOnDisconnect 0x5D6870
#define fnOnAfk 0x5D6BC0
#define fnSmartPing 0x654CA0
#define fnGameUpdate 0x318110
#define fnClientMain 0x28F830
#define fnPlaySound 0x275C20
#define fnGetBasicAttack 0x1C1490
#define fnGetAttackDelay 0x546A40
#define fnGetAttackCastDelay 0x297ED0
#define fnUseObject 0x199100
#define fnCreateObject 0x2E9D90
#define fnIdentifyObject 0x24B3B0
#define fnDeleteObject 0x2D8BB0
#define fnAddRemoveBuff 0x530EE0
#define fnLevelUp 0x229C80
#define fnAssignNetworkID 0x2E4520
#define fnUpdateBuff 0x516110
#define fnDoEmote 0x62BF70
#define fnDoMasteryBadge 0x581500
#define fnOnSurrenderVote 0x643D30
#define fnUpdateChargeableSpell 0x542890
#define fnApplySpellCD 0x53A4E0
#define fnStopCast 0x542000
#define fnGetBoundingRadius 0x1F5190
#define fnWorldToScreen 0x7FCE30
#define fnScreenToWorld 0x7FCF10
#define fnMapToWorld 0x618DE0
#define fnWorld2Map 0x28D790
#define fnGetTacticalMap 0x1C8FA0
#define j_CReplInfo32__AddVar 0x1F7910
#define CReplInfo32_AddVar 0x2060F0


#define oLocalPlayer 0x2E2FEF8
#define oChatClientPtr 0x2E36EB8
#define oObjManager 0x2E2D650
#define oRenderer 0x2E54250
#define oZoomClass 0x2E2A408
#define oUnderMouseObject 0x21D3DEC
#define oCursor 0x1585E18
#define oMissionInfo 0x2E59AAC
#define oGameState 0x2E2AD08
#define oVersion 0x2E355C0
#define oNetClient 0x2E31958
#define oTexturePack 0x2E32578
#define oGameTime 0x2E2A48C



#define pSpellBookPtr 0x1CA0



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
	float mLifetimeTicks; //0x0568 
	unsigned char pad_0x056C[0x48]; //0x056C
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
	unsigned char pad_0x06F4[0x150]; //0x06F4
	float mNegativeCurrentCDR; //0x0844 
	unsigned char pad_0x0848[0xC]; //0x0848
	float mNegativeMaxCDR; //0x0854 
	unsigned char pad_0x0858[0x5B0]; //0x0858
	float mPercentCooldownCapMod; //0x0E08 
	unsigned char pad_0x0E0C[0xC]; //0x0E0C
	float mPassiveCooldownEndTime; //0x0E18 
	unsigned char pad_0x0E1C[0xC]; //0x0E1C
	float mPassiveCooldownTotalTime; //0x0E28 
	unsigned char pad_0x0E2C[0xC]; //0x0E2C
	float mPercentDamageToBarracksMinionMod; //0x0E38 
	unsigned char pad_0x0E3C[0xC]; //0x0E3C
	float mFlatDamageReductionFromBarracksMinionMod; //0x0E48 
	unsigned char pad_0x0E4C[0xC]; //0x0E4C
	float mFlatPhysicalDamageMod; //0x0E58 
	unsigned char pad_0x0E5C[0xC]; //0x0E5C
	float mPercentPhysicalDamageMod; //0x0E68 
	unsigned char pad_0x0E6C[0x1C]; //0x0E6C
	float mPercentBasePhysicalDamageAsFlatBonusMod; //0x0E88 
	unsigned char pad_0x0E8C[0xC]; //0x0E8C
	float mFlatMagicDamageMod; //0x0E98 
	unsigned char pad_0x0E9C[0xC]; //0x0E9C
	float mPercentMagicDamageMod; //0x0EA8 
	unsigned char pad_0x0EAC[0xC]; //0x0EAC
	float mFlatMagicReduction; //0x0EB8 
	unsigned char pad_0x0EBC[0xC]; //0x0EBC
	float mPercentMagicReduction; //0x0EC8 
	unsigned char pad_0x0ECC[0xC]; //0x0ECC
	float mFlatCastRangeMod; //0x0ED8 
	unsigned char pad_0x0EDC[0xC]; //0x0EDC
	float mAttackSpeedMod; //0x0EE8 
	unsigned char pad_0x0EEC[0xC]; //0x0EEC
	float mPercentAttackSpeedMod; //0x0EF8 
	unsigned char pad_0x0EFC[0xC]; //0x0EFC
	float mPercentMultiplicativeAttackSpeedMod; //0x0F08 
	unsigned char pad_0x0F0C[0xC]; //0x0F0C
	float mBaseAttackDamage; //0x0F18 
	unsigned char pad_0x0F1C[0xC]; //0x0F1C
	float mBaseAttackDamageSansPercentScale; //0x0F28 
	unsigned char pad_0x0F2C[0xC]; //0x0F2C
	float mFlatBaseAttackDamageMod; //0x0F38 
	unsigned char pad_0x0F3C[0xC]; //0x0F3C
	float mPercentBaseAttackDamageMod; //0x0F48 
	unsigned char pad_0x0F4C[0xC]; //0x0F4C
	float mBaseAbilityDamage; //0x0F58 
	unsigned char pad_0x0F5C[0xC]; //0x0F5C
	float mScaleSkinCoef; //0x0F68 
	unsigned char pad_0x0F6C[0xC]; //0x0F6C
	float mDodge; //0x0F78 
	unsigned char pad_0x0F7C[0xC]; //0x0F7C
	float mCrit; //0x0F88 
	unsigned char pad_0x0F8C[0xC]; //0x0F8C
	float mArmor; //0x0F98 
	unsigned char pad_0x0F9C[0xC]; //0x0F9C
	float mBonusArmor; //0x0FA8 
	unsigned char pad_0x0FAC[0xC]; //0x0FAC
	float mSpellBlock; //0x0FB8 
	unsigned char pad_0x0FBC[0xC]; //0x0FBC
	float mBonusSpellBlock; //0x0FC8 
	unsigned char pad_0x0FCC[0xC]; //0x0FCC
	float mHPRegenRate; //0x0FD8 
	unsigned char pad_0x0FDC[0xC]; //0x0FDC
	float mBaseHPRegenRate; //0x0FE8 
	unsigned char pad_0x0FEC[0xC]; //0x0FEC
	float mMoveSpeed; //0x0FF8 
	unsigned char pad_0x0FFC[0xC]; //0x0FFC
	float mMoveSpeedBaseIncrease; //0x1008 
	unsigned char pad_0x100C[0xC]; //0x100C
	float mAttackRange; //0x1018 
	unsigned char pad_0x101C[0xC]; //0x101C
	float mFlatBubbleRadiusMod; //0x1028 
	unsigned char pad_0x102C[0xC]; //0x102C
	float mPercentBubbleRadiusMod; //0x1038 
	unsigned char pad_0x103C[0xC]; //0x103C
	float mFlatArmorPenetration; //0x1048 
	unsigned char pad_0x104C[0xC]; //0x104C
	float mPhysicalLethality; //0x1058 
	unsigned char pad_0x105C[0xC]; //0x105C
	float mPercentArmorPenetration; //0x1068 
	unsigned char pad_0x106C[0xC]; //0x106C
	float mPercentBonusArmorPenetration; //0x1078 
	unsigned char pad_0x107C[0xC]; //0x107C
	float mPercentCritBonusArmorPenetration; //0x1088 
	unsigned char pad_0x108C[0xC]; //0x108C
	float mPercentCritTotalArmorPenetration; //0x1098 
	unsigned char pad_0x109C[0xC]; //0x109C
	float mFlatMagicPenetration; //0x10A8 
	unsigned char pad_0x10AC[0xC]; //0x10AC
	float mMagicLethality; //0x10B8 
	unsigned char pad_0x10BC[0xC]; //0x10BC
	float mPercentMagicPenetration; //0x10C8 
	unsigned char pad_0x10CC[0xC]; //0x10CC
	float mPercentBonusMagicPenetration; //0x10D8 
	unsigned char pad_0x10DC[0xC]; //0x10DC
	float mPercentLifeStealMod; //0x10E8 
	unsigned char pad_0x10EC[0xC]; //0x10EC
	float mPercentSpellVampMod; //0x10F8 
	unsigned char pad_0x10FC[0x1C]; //0x10FC
	float mPercentCCReduction; //0x1118 
	unsigned char pad_0x111C[0xC]; //0x111C
	float mPercentEXPBonus; //0x1128 
	unsigned char pad_0x112C[0xC]; //0x112C
	float mPrimaryARRegenRateRep; //0x1138 
	unsigned char pad_0x113C[0xC]; //0x113C
	float mPrimaryARBaseRegenRateRep; //0x1148 
	unsigned char pad_0x114C[0xC]; //0x114C
	float mSecondaryARRegenRateRep; //0x1158 
	unsigned char pad_0x115C[0xC]; //0x115C
	float mSecondaryARBaseRegenRateRep; //0x1168 
	unsigned char pad_0x116C[0xC4]; //0x116C
	float mGold; //0x1230 
	unsigned char pad_0x1234[0xC]; //0x1234
	float mGoldTotal; //0x1240 
	unsigned char pad_0x1244[0xC]; //0x1244
	float mMinimumGold; //0x1250 
	unsigned char pad_0x1254[0x164]; //0x1254
	Vector mDirectionFaced; //0x13B8 
	unsigned char pad_0x13C4[0x3B8]; //0x13C4
	Obj_AI_Base* mCharData; //0x177C 
	unsigned char pad_0x1780[0x540]; //0x1780
	activeSpell* mActiveSpell; //0x1CC0 
	unsigned char pad_0x1CC4[0x50C]; //0x1CC4
	spellInst* mSpellInstArray[4]; //0x21D0 
	spellInst* mPartOfSpellInst1; //0x21D4 
	spellInst* mPartOfSpellInst2; //0x21D8 
	spellInst* mPartOfSpellInst4; //0x21DC 
	unsigned char pad_0x21E0[0x14D4]; //0x21E0
	int mEvolvePoints; //0x36B4 
	unsigned char pad_0x36B8[0xC]; //0x36B8
	int mEvolveFlag; //0x36C4 
	unsigned char pad_0x36C8[0xC]; //0x36C8
	float mExp; //0x36D4 
	unsigned char pad_0x36D8[0xC]; //0x36D8
	float mLevelRef; //0x36E4 
	unsigned char pad_0x36E8[0xC]; //0x36E8
	bool mSkillUpLevelDeltaReplicate; //0x36F4 
	unsigned char pad_0x36F5[0x903]; //0x36F5
	int mNumNeutralMinionsKilled; //0x3FF8 
	unsigned char pad_0x3FFC[0x20]; //0x3FFC
	int mInputLocks; //0x401C 
	unsigned char pad_0x4020[0xC]; //0x4020
	int mHealthBarCharacterIDForIcon; //0x402C 
	unsigned char pad_0x4030[0x530]; //0x4030
	float mPhysicalDamageTaken; //0x4560 
	unsigned char pad_0x4564[0xC]; //0x4564
	float mMagicDamageTaken; //0x4570 
	unsigned char pad_0x4574[0xC]; //0x4574
	float mTrueDamageTaken; //0x4580 
	unsigned char pad_0x4584[0x3B4]; //0x4584

	float getUnitSize() {
		return (this->mEdgePos2.x - this->mEdgePos1.x);
	}
}; //Size=0x4938

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

class spellData
{
public:
	unsigned char pad_0x0000[0x34]; //0x0000
	spellInfo* mSpellInfo; //0x0034 
	unsigned char pad_0x0038[0x3CC]; //0x0038

}; //Size=0x0404

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

class oMouse
{
public:
	unsigned char pad_0x0000[0x90]; //0x0000
	Vector mMousePos; //0x0090 
	unsigned char pad_0x009C[0x3A4]; //0x009C

}; //Size=0x0440



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

