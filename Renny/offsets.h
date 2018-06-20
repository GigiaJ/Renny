#define fnLogger 0x17ABF0
#define fnLogUIEvents 0x17ED00
#define fnCastSpell 0x54E480
#define fnGetHealthbarPos 0x1C1FB0
#define fnEventHandler 0x247EC0
#define fnMainLoop 0x75B510
#define fnDrawTurretRange 0x206720
#define fnLevelUpSpell 0x5508C0
#define fnSetSkin 0x209EA0
#define fnGetSpellData 0x543930
#define fnPrintChat 0x57B860
#define fnOpenChat 0x57AE00
#define fnDisplayChat 0x56A390
#define fnSendChat 0x64E840
#define fnSetChatScale 0x579060
#define fnIssueOrder 0x1C9B10
#define fnOnMoveMouseClick 0x5BBB80
#define fnCheckIfInitialClickIsAvaliable 0x7769D0
#define fnOnProcessSpell 0x544730
#define fnOnProcessSpellW 0x54F850
#define fnOnSpellCast 0x1CFA10
#define fnOnAutoAttack 0x1E5A40
#define fnSetPath 0x218560
#define fnCreatePath 0x76CAB0
#define fnOnUpdatePath 0x87FA60
#define fnIsWallOfGrass 0x774010
#define fnDispatchEvent 0x2C92E0
#define fnLoadTexture 0x804940
#define fnOnProcessPacket 0x331780
#define fnInitEvent 0x239D50
#define fnOnLoadHero 0x340770
#define fnOnLoadChampion 0x1BE030
#define fnOnTeleport 0x1E80F0
#define fnOnDisconnect 0x5E3A80
#define fnOnAfk 0x5E3DD0
#define fnSmartPing 0x662CC0
#define fnGameUpdate 0x317C60
#define fnClientMain 0x292160
#define fnPlaySound 0x2793E0
#define fnGetBasicAttack 0x1C1160
#define fnGetAttackDelay 0x554CE0
#define fnGetAttackCastDelay 0x29AC20
#define fnUseObject 0x199970
#define fnCreateObject 0x2E79C0
#define fnIdentifyObject 0x21D480
#define fnDeleteObject 0x2D80B0
#define fnAddRemoveBuff 0x53E6F0
#define fnLevelUp 0x22CEF0
#define fnAssignNetworkID 0x2E2710
#define fnUpdateBuff 0x5223E0
#define fnDoEmote 0x6336D0
#define fnDoMasteryBadge 0x58F610
#define fnOnSurrenderVote 0x650FD0
#define fnUpdateChargeableSpell 0x550590
#define fnApplySpellCD 0x547DE0
#define fnStopCast 0x54FD00
#define fnGetBoundingRadius 0x1F4440
#define fnWorldToScreen 0x80B6A0
#define fnScreenToWorld 0x80B780
#define fnMapToWorld 0x61E3C0
#define fnWorld2Map 0x290550
#define fnGetTacticalMap 0x1C8CF0
#define j_CReplInfo32__AddVar 0x1F72A0
#define CReplInfo32_AddVar 0x206320


#define oLocalPlayer 0x2E3B2E0
#define oChatClientPtr 0x2E442A8
#define oObjManager 0x2E3A678
#define oRenderer 0x2E616B0
#define oZoomClass 0x2E371F0
#define oUnderMouseObject 0x21E3C64
#define oCursor 0x1592CFC
#define oMissionInfo 0x2E66F04
#define oGameState 0x2E37CBC
#define oVersion 0x2E428E0
#define oNetClient 0x2E3DA78
#define oTexturePack 0x2E3F5A0
#define oGameTime 0x2E3739C




#define pSpellBookPtr 0x1CD8

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
	unsigned char pad_0x0000[0x8]; //0x0000
	short mIndex; //0x0008 
	short mNextIndex; //0x000A 
	unsigned char pad_0x000C[0x8]; //0x000C
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
	unsigned char pad_0x00F1[0x13]; //0x00F1
	spellData* mSpellData; //0x0104 
	unsigned char pad_0x0108[0x1C]; //0x0108
	short mCasterIndex; //0x0124 
	unsigned char pad_0x0126[0x16]; //0x0126
	Vector mStartPosition; //0x013C 
	Vector mTargetPosition; //0x0148 
	unsigned char pad_0x0154[0xC]; //0x0154
	Vector mSpellDirection; //0x0160 
	unsigned char pad_0x016C[0x14C]; //0x016C
	bool isVisible; //0x02B8 
	unsigned char pad_0x02B9[0x13]; //0x02B9
	float mPAR; //0x02CC 
	unsigned char pad_0x02D0[0xC]; //0x02D0
	float mMaxPAR; //0x02DC 
	unsigned char pad_0x02E0[0xC]; //0x02E0
	bool mPAREnabled; //0x02EC 
	unsigned char pad_0x02ED[0x1F]; //0x02ED
	int mPARState; //0x030C 
	unsigned char pad_0x0310[0x1C]; //0x0310
	float mSAR; //0x032C 
	unsigned char pad_0x0330[0xC]; //0x0330
	float mMaxSAR; //0x033C 
	unsigned char pad_0x0340[0xC]; //0x0340
	bool mSAREnabled; //0x034C 
	unsigned char pad_0x034D[0xF]; //0x034D
	bool mEMpoweredBitField; //0x035C 
	unsigned char pad_0x035D[0xF]; //0x035D
	int mSARState; //0x036C 
	unsigned char pad_0x0370[0x200]; //0x0370
	float mLifetime; //0x0570 
	unsigned char pad_0x0574[0xC]; //0x0574
	float mMaxLifeTime; //0x0580 
	unsigned char pad_0x0584[0xC]; //0x0584
	float mLifeTimeTicks; //0x0590 
	unsigned char pad_0x0594[0x28]; //0x0594
	float mPhysicalDamagePercentageModifier; //0x05BC 
	unsigned char pad_0x05C0[0xC]; //0x05C0
	float mMagicalDamagePercentageModifier; //0x05CC 
	unsigned char pad_0x05D0[0x1C]; //0x05D0
	bool mIsUntargetableToEnemies; //0x05EC 
	unsigned char pad_0x05ED[0xF]; //0x05ED
	bool mIsUntargetableToAllies; //0x05FC 
	unsigned char pad_0x05FD[0xF]; //0x05FD
	bool mIsTargetable; //0x060C 
	unsigned char pad_0x060D[0xF]; //0x060D
	bool mIsTargetableToTeamFlags; //0x061C 
	unsigned char pad_0x061D[0x5B]; //0x061D
	float mHP; //0x0678 
	unsigned char pad_0x067C[0xC]; //0x067C
	float mMaxHP; //0x0688 
	unsigned char pad_0x068C[0xC]; //0x068C
	float mHPMaxPenalty; //0x0698 
	unsigned char pad_0x069C[0x1C]; //0x069C
	float mAllShield; //0x06B8 
	unsigned char pad_0x06BC[0xC]; //0x06BC
	float mPhysicalShield; //0x06C8 
	unsigned char pad_0x06CC[0xC]; //0x06CC
	float mMagicalShield; //0x06D8 
	unsigned char pad_0x06DC[0xC]; //0x06DC
	float mChampSpecificHealth; //0x06E8 
	unsigned char pad_0x06EC[0xC]; //0x06EC
	int mStopShieldFade; //0x06F8 
	unsigned char pad_0x06FC[0x168]; //0x06FC
	float mNegativeCurrentCDR; //0x0864 
	unsigned char pad_0x0868[0xC]; //0x0868
	float mNegativeMaxCDR; //0x0874 
	unsigned char pad_0x0878[0x5B0]; //0x0878
	float mPercentCooldownCapMod; //0x0E28 
	unsigned char pad_0x0E2C[0xC]; //0x0E2C
	float mPassiveCooldownEndTime; //0x0E38 
	unsigned char pad_0x0E3C[0xC]; //0x0E3C
	float mPassiveCooldownTotalTime; //0x0E48 
	unsigned char pad_0x0E4C[0xC]; //0x0E4C
	float mPercentDamageToBarracksMinionMod; //0x0E58 
	unsigned char pad_0x0E5C[0xC]; //0x0E5C
	float mFlatDamageReductionFromBarracksMinionMod; //0x0E68 
	unsigned char pad_0x0E6C[0xC]; //0x0E6C
	float mFlatPhysicalDamageMod; //0x0E78 
	unsigned char pad_0x0E7C[0xC]; //0x0E7C
	float mPercentPhysicalDamageMod; //0x0E88 
	unsigned char pad_0x0E8C[0x1C]; //0x0E8C
	float mPercentBasePhysicalDamageAsFlatBonusMod; //0x0EA8 
	unsigned char pad_0x0EAC[0xC]; //0x0EAC
	float mFlatMagicDamageMod; //0x0EB8 
	unsigned char pad_0x0EBC[0xC]; //0x0EBC
	float mPercentMagicDamageMod; //0x0EC8 
	unsigned char pad_0x0ECC[0xC]; //0x0ECC
	float mFlatMagicReduction; //0x0ED8 
	unsigned char pad_0x0EDC[0xC]; //0x0EDC
	float mPercentMagicReduction; //0x0EE8 
	unsigned char pad_0x0EEC[0xC]; //0x0EEC
	float mFlatCastRangeMod; //0x0EF8 
	unsigned char pad_0x0EFC[0xC]; //0x0EFC
	float mAttackSpeedMod; //0x0F08 
	unsigned char pad_0x0F0C[0xC]; //0x0F0C
	float mPercentAttackSpeedMod; //0x0F18 
	unsigned char pad_0x0F1C[0xC]; //0x0F1C
	float mPercentMultiplicativeAttackSpeedMod; //0x0F28 
	unsigned char pad_0x0F2C[0xC]; //0x0F2C
	float mBaseAttackDamage; //0x0F38 
	unsigned char pad_0x0F3C[0xC]; //0x0F3C
	float mBaseAttackDamageSansPercentScale; //0x0F48 
	unsigned char pad_0x0F4C[0xC]; //0x0F4C
	float mFlatBaseAttackDamageMod; //0x0F58 
	unsigned char pad_0x0F5C[0xC]; //0x0F5C
	float mPercentBaseAttackDamageMod; //0x0F68 
	unsigned char pad_0x0F6C[0xC]; //0x0F6C
	float mBaseAbilityDamage; //0x0F78 
	unsigned char pad_0x0F7C[0xC]; //0x0F7C
	float mScaleSkinCoef; //0x0F88 
	unsigned char pad_0x0F8C[0xC]; //0x0F8C
	float mDodge; //0x0F98 
	unsigned char pad_0x0F9C[0xC]; //0x0F9C
	float mCrit; //0x0FA8 
	unsigned char pad_0x0FAC[0xC]; //0x0FAC
	float mArmor; //0x0FB8 
	unsigned char pad_0x0FBC[0xC]; //0x0FBC
	float mBonusArmor; //0x0FC8 
	unsigned char pad_0x0FCC[0xC]; //0x0FCC
	float mSpellBlock; //0x0FD8 
	unsigned char pad_0x0FDC[0xC]; //0x0FDC
	float mBonusSpellBlock; //0x0FE8 
	unsigned char pad_0x0FEC[0xC]; //0x0FEC
	float mHPRegenRate; //0x0FF8 
	unsigned char pad_0x0FFC[0xC]; //0x0FFC
	float mBaseHPRegenRate; //0x1008 
	unsigned char pad_0x100C[0xC]; //0x100C
	float mMoveSpeed; //0x1018 
	unsigned char pad_0x101C[0xC]; //0x101C
	float mMoveSpeedBaseIncrease; //0x1028 
	unsigned char pad_0x102C[0xC]; //0x102C
	float mAttackRange; //0x1038 
	unsigned char pad_0x103C[0xC]; //0x103C
	float mFlatBubbleRadiusMod; //0x1048 
	unsigned char pad_0x104C[0xC]; //0x104C
	float mPercentBubbleRadiusMod; //0x1058 
	unsigned char pad_0x105C[0xC]; //0x105C
	float mFlatArmorPenetration; //0x1068 
	unsigned char pad_0x106C[0xC]; //0x106C
	float mPhysicalLethality; //0x1078 
	unsigned char pad_0x107C[0xC]; //0x107C
	float mPercentArmorPenetration; //0x1088 
	unsigned char pad_0x108C[0xC]; //0x108C
	float mPercentBonusArmorPenetration; //0x1098 
	unsigned char pad_0x109C[0xC]; //0x109C
	float mPercentCritBonusArmorPenetration; //0x10A8 
	unsigned char pad_0x10AC[0xC]; //0x10AC
	float mPercentCritTotalArmorPenetration; //0x10B8 
	unsigned char pad_0x10BC[0xC]; //0x10BC
	float mFlatMagicPenetration; //0x10C8 
	unsigned char pad_0x10CC[0xC]; //0x10CC
	float mMagicLethality; //0x10D8 
	unsigned char pad_0x10DC[0xC]; //0x10DC
	float mPercentMagicPenetration; //0x10E8 
	unsigned char pad_0x10EC[0xC]; //0x10EC
	float mPercentBonusMagicPenetration; //0x10F8 
	unsigned char pad_0x10FC[0xC]; //0x10FC
	float mPercentLifeStealMod; //0x1108 
	unsigned char pad_0x110C[0xC]; //0x110C
	float mPercentSpellVampMod; //0x1118 
	unsigned char pad_0x111C[0x1C]; //0x111C
	float mPercentCCReduction; //0x1138 
	unsigned char pad_0x113C[0xC]; //0x113C
	float mPercentEXPBonus; //0x1148 
	unsigned char pad_0x114C[0xC]; //0x114C
	float mPrimaryARRegenRateRep; //0x1158 
	unsigned char pad_0x115C[0xC]; //0x115C
	float mPrimaryARBaseRegenRateRep; //0x1168 
	unsigned char pad_0x116C[0xC]; //0x116C
	float mSecondaryARRegenRateRep; //0x1178 
	unsigned char pad_0x117C[0xC]; //0x117C
	float mSecondaryARBaseRegenRateRep; //0x1188 
	unsigned char pad_0x118C[0xC4]; //0x118C
	float mGold; //0x1250 
	unsigned char pad_0x1254[0xC]; //0x1254
	float mGoldTotal; //0x1260 
	unsigned char pad_0x1264[0xC]; //0x1264
	float mMinimumGold; //0x1270 
	unsigned char pad_0x1274[0x164]; //0x1274
	Vector mDirectionFaced; //0x13D8 
	unsigned char pad_0x13E4[0x3D0]; //0x13E4
	Obj_AI_Base* mCharData; //0x17B4 
	unsigned char pad_0x17B8[0x540]; //0x17B8
	activeSpell* mActiveSpell; //0x1CF8 
	unsigned char pad_0x1CFC[0x50C]; //0x1CFC
	spellInst* mSpellInstArray[4]; //0x2208 
	spellInst* mPartOfSpellInst1; //0x220C 
	spellInst* mPartOfSpellInst2; //0x2210 
	spellInst* mPartOfSpellInst4; //0x2214 
	unsigned char pad_0x2218[0x16FC]; //0x2218
	int mEvolvePoints; //0x3914 
	unsigned char pad_0x3918[0xC]; //0x3918
	int mEvolveFlag; //0x3924 
	unsigned char pad_0x3928[0xC]; //0x3928
	float mExp; //0x3934 
	unsigned char pad_0x3938[0xC]; //0x3938
	float mLevelRef; //0x3944 
	unsigned char pad_0x3948[0xC]; //0x3948
	bool mSkillUpLevelDeltaReplicate; //0x3954 
	unsigned char pad_0x3955[0x497]; //0x3955
	float mVisionScore; //0x3DEC 
	unsigned char pad_0x3DF0[0x4B0]; //0x3DF0
	int mNumNeutralMinionsKilled; //0x42A0 
	unsigned char pad_0x42A4[0x20]; //0x42A4
	int mInputLocks; //0x42C4 
	unsigned char pad_0x42C8[0xC]; //0x42C8
	int mHealthBarCharacterIDForIcon; //0x42D4 
	unsigned char pad_0x42D8[0x530]; //0x42D8
	float mPhysicalDamageTaken; //0x4808 
	unsigned char pad_0x480C[0xC]; //0x480C
	float mMagicDamageTaken; //0x4818 
	unsigned char pad_0x481C[0xC]; //0x481C
	float mTrueDamageTaken; //0x4828 
	unsigned char pad_0x482C[0x538]; //0x482C

	float getUnitSize() {
		return (this->mEdgePos2.x - this->mEdgePos1.x);
	}
}; //Size=0x4D64

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
	unsigned char pad_0x0000[0x18]; //0x0000
	char* mSpellName; //0x0018 
	unsigned char pad_0x001C[0x1C]; //0x001C
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
	unsigned char pad_0x0000[0x200]; //0x0000
	float mAnimationTime; //0x0200 
	float mCastTime; //0x0204 
	unsigned char pad_0x0208[0x78]; //0x0208
	ReClassFloat mCoolDownTime[7]; //0x0280 
	unsigned char pad_0x029C[0x100]; //0x029C
	ReClassFloat mMaxRangeForPlacement[7]; //0x039C 
	ReClassFloat mMaxRange[7]; //0x03B8 
	ReClassFloat mCastRadius[7]; //0x03D4 
	unsigned char pad_0x03F0[0x48]; //0x03F0
	float mMissileSpeed; //0x0438 
	unsigned char pad_0x043C[0x30]; //0x043C
	float mMissileWidth; //0x046C 
	unsigned char pad_0x0470[0x20C]; //0x0470

}; //Size=0x067C

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

