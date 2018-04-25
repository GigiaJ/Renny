#define fnLogger 0x178CF0
#define fnLogUIEvents 0x17CE90
#define fnCastSpell 0x55B130
#define fnGetHealthbarPos 0x1C0950
#define fnEventHandler 0x250A30
#define fnMainLoop 0x75E890
#define fnDrawTurretRange 0x206F20
#define fnLevelUpSpell 0x55D3C0
#define fnSetSkin 0x20A0F0
#define fnGetSpellData 0x550170
#define fnPrintChat 0x58D290
#define fnOpenChat 0x58C7E0
#define fnDisplayChat 0x578AE0
#define fnSendChat 0x6583C0
#define fnSetChatScale 0x589D40
#define fnIssueOrder 0x1C8360
#define fnEventMoveMouseClick 0x5C8880
#define fnOnProcessSpell 0x550F70
#define fnOnProcessSpellW 0x55C3F0
#define fnOnSpellCast 0x1CE370
#define fnOnAutoAttack 0x1E52A0
#define fnSetPath 0x2186A0
#define fnCreatePath 0x4F06F0
#define fnIsWallOfGrass 0x5024D0
#define fnIsWall 0x501670
#define fnDispatchEvent 0x2BBFB0
#define fnLoadTexture 0x7F8430
#define fnOnProcessPacket 0x362080
#define fnInitEvent 0x23E450
#define fnOnLoadHero 0x36E4C0
#define fnOnLoadChampion 0x1BCA50
#define fnOnTeleport 0x1E7F60
#define fnOnDisconnect 0x5EE6B0
#define fnOnAfk 0x5EEA00
#define fnSmartPing 0x67EEB0
#define fnGameUpdate 0x31FA90
#define fnClientMain 0x28FFB0
#define fnPlaySound 0x279A90
#define fnGetBasicAttack 0x1BFBE0
#define fnGetAttackDelay 0x55F5D0
#define fnGetAttackCastDelay 0x55F630
#define fnUseObject 0x196F20
#define fnCreateObject 0x2EE750
#define fnIdentifyObject 0x21D220
#define fnDeleteObject 0x2DEFF0
#define fnAddRemoveBuff 0x549E00
#define fnLevelUp 0x229940
#define fnAssignNetworkID 0x2E9610
#define fnUpdateBuff 0x52D640
#define fnDoEmote 0x6423A0
#define fnDoMasteryBadge 0x59D830
#define fnOnSurrenderVote 0x65A640
#define fnUpdateChargeableSpell 0x55CFB0
#define fnApplySpellCD 0x555370
#define fnStopCast 0x55C8A0
#define fnGetBoundingRadius 0x1F46C0
#define fnWorldToScreen 0x7FF4A0
#define fnScreenToWorld 0x7FF580
#define fnMapToWorld 0x62FD50
#define fnWorld2Map 0x28DC80
#define fnGetTacticalMap 0x1C74A0

#define oLocalPlayer 0x2E4FF38
#define oChatClientPtr 0x2E570C0
#define oObjectManager 0x2E4AFE0
#define oRenderer 0x2E743A0
#define oZoomClass 0x2E47F40
#define oUnderMouseObject 0x21F1A94
#define oCursor 0x15A3B20
#define oMissionInfo 0x2E79C04
#define oVersion 0x2E556A0
#define oNetClient 0x2E4FFC8
#define oTexturePack 0x2E52388
#define oGameTime 0x2E480C4


#define pSpellBookPtr 0x1BD0
// Generated using ReClass 2016

struct Vector
{
	float x;
	float y;
	float z;
};



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
	unsigned char pad_0x0038[0x3C]; //0x0038
	DWORD mNetworkId; //0x0074 
	unsigned char pad_0x0078[0x8]; //0x0078
	Vector mEdgePos1; //0x0080 
	Vector mEdgePos2; //0x008C 
	unsigned char pad_0x0098[0x3C]; //0x0098
	Vector mUnitPos; //0x00D4 
	unsigned char pad_0x00E0[0x18]; //0x00E0
	bool mIsDead; //0x00F8 
	unsigned char pad_0x00F9[0x1BF]; //0x00F9
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
	float mLifetimeTicks; //0x0570 
	unsigned char pad_0x0574[0x48]; //0x0574
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
	unsigned char pad_0x06FC[0x72C]; //0x06FC
	float mNegativeCurrentCDR; //0x0E28 
	unsigned char pad_0x0E2C[0xC]; //0x0E2C
	float mNegativeMaxCDR; //0x0E38 
	unsigned char pad_0x0E3C[0x1C]; //0x0E3C
	float mPercentCooldownCapMod; //0x0E58 
	unsigned char pad_0x0E5C[0xC]; //0x0E5C
	float mPassiveCooldownEndTime; //0x0E68 
	unsigned char pad_0x0E6C[0xC]; //0x0E6C
	float mPassiveCooldownTotalTime; //0x0E78 
	unsigned char pad_0x0E7C[0x2C]; //0x0E7C
	float mFlatPhysicalDamageMod; //0x0EA8 
	unsigned char pad_0x0EAC[0xC]; //0x0EAC
	float mPercentPhysicalDamageMod; //0x0EB8 
	unsigned char pad_0x0EBC[0xC]; //0x0EBC
	float mFlatMagicDamageMod; //0x0EC8 
	unsigned char pad_0x0ECC[0xC]; //0x0ECC
	float mPercentMagicDamageMod; //0x0ED8 
	unsigned char pad_0x0EDC[0xC]; //0x0EDC
	float mFlatMagicReduction; //0x0EE8 
	unsigned char pad_0x0EEC[0xC]; //0x0EEC
	float mPercentMagicReduction; //0x0EF8 
	unsigned char pad_0x0EFC[0xC]; //0x0EFC
	float mFlatCastRangeMod; //0x0F08 
	unsigned char pad_0x0F0C[0xC]; //0x0F0C
	float mAttackSpeedMod; //0x0F18 
	unsigned char pad_0x0F1C[0xC]; //0x0F1C
	float mBaseAttackDamage; //0x0F28 
	unsigned char pad_0x0F2C[0xC]; //0x0F2C
	float mBaseAttackDamageSansPercentScale; //0x0F38 
	unsigned char pad_0x0F3C[0xC]; //0x0F3C
	float mFlatBaseAttackDamageMod; //0x0F48 
	unsigned char pad_0x0F4C[0xC]; //0x0F4C
	float mPercentBaseAttackDamageMod; //0x0F58 
	unsigned char pad_0x0F5C[0xC]; //0x0F5C
	float mBaseAbilityDamage; //0x0F68 
	unsigned char pad_0x0F6C[0xC]; //0x0F6C
	float mScaleSkinCoef; //0x0F78 
	unsigned char pad_0x0F7C[0xC]; //0x0F7C
	float mDodge; //0x0F88 
	unsigned char pad_0x0F8C[0xC]; //0x0F8C
	float mCrit; //0x0F98 
	unsigned char pad_0x0F9C[0xC]; //0x0F9C
	float mArmor; //0x0FA8 
	unsigned char pad_0x0FAC[0xC]; //0x0FAC
	float mBonusArmor; //0x0FB8 
	unsigned char pad_0x0FBC[0xC]; //0x0FBC
	float mSpellBlock; //0x0FC8 
	unsigned char pad_0x0FCC[0xC]; //0x0FCC
	float mBonusSpellBlock; //0x0FD8 
	unsigned char pad_0x0FDC[0xC]; //0x0FDC
	float mHPRegenRate; //0x0FE8 
	unsigned char pad_0x0FEC[0xC]; //0x0FEC
	float mBaseHPRegenRate; //0x0FF8 
	unsigned char pad_0x0FFC[0xC]; //0x0FFC
	float mMoveSpeed; //0x1008 
	unsigned char pad_0x100C[0xC]; //0x100C
	float mMoveSpeedBaseIncrease; //0x1018 
	unsigned char pad_0x101C[0xC]; //0x101C
	float mAttackRange; //0x1028 
	unsigned char pad_0x102C[0xC]; //0x102C
	float mFlatBubbleRadiusMod; //0x1038 
	unsigned char pad_0x103C[0xC]; //0x103C
	float mPercentBubbleRadiusMod; //0x1048 
	unsigned char pad_0x104C[0xC]; //0x104C
	float mFlatArmorPenetration; //0x1058 
	unsigned char pad_0x105C[0xC]; //0x105C
	float mPhysicalLethality; //0x1068 
	unsigned char pad_0x106C[0xC]; //0x106C
	float mPercentBonusArmorPenetration; //0x1078 
	unsigned char pad_0x107C[0xC]; //0x107C
	float mPercentArmorPenetration; //0x1088 
	unsigned char pad_0x108C[0xC]; //0x108C
	float mPercentCritBonusArmorPenetration; //0x1098 
	unsigned char pad_0x109C[0xC]; //0x109C
	float mPercentCritTotalArmorPenetration; //0x10A8 
	unsigned char pad_0x10AC[0xC]; //0x10AC
	float mFlatMagicPenetration; //0x10B8 
	unsigned char pad_0x10BC[0xC]; //0x10BC
	float mMagicLethality; //0x10C8 
	unsigned char pad_0x10CC[0xC]; //0x10CC
	float mPercentMagicPenetration; //0x10D8 
	unsigned char pad_0x10DC[0xC]; //0x10DC
	float mPercentBonusMagicPenetration; //0x10E8 
	unsigned char pad_0x10EC[0xC]; //0x10EC
	float mPercentLifeStealMod; //0x10F8 
	unsigned char pad_0x10FC[0xC]; //0x10FC
	float mPercentSpellVampMod; //0x1108 
	unsigned char pad_0x110C[0x1C]; //0x110C
	float mPercentCCReduction; //0x1128 
	unsigned char pad_0x112C[0xC]; //0x112C
	float mPercentEXPBonus; //0x1138 
	unsigned char pad_0x113C[0xC]; //0x113C
	float mPARRegenRate; //0x1148 
	unsigned char pad_0x114C[0xC]; //0x114C
	float mPrimaryARBaseRegenRateRep; //0x1158 
	unsigned char pad_0x115C[0xC]; //0x115C
	float mSecondaryARRegenRateRep; //0x1168 
	unsigned char pad_0x116C[0xC]; //0x116C
	float mSecondaryARBaseRegenRateRep; //0x1178 
	unsigned char pad_0x117C[0xC4]; //0x117C
	AIManager* mAIManager; //0x1240 
	float mGold; //0x1244 
	unsigned char pad_0x1248[0xC]; //0x1248
	float mGoldTotal; //0x1254 
	unsigned char pad_0x1258[0xC]; //0x1258
	float mMinimumGold; //0x1264 
	unsigned char pad_0x1268[0x168]; //0x1268
	Vector mDirectionFaced; //0x13D0 
	unsigned char pad_0x13DC[0x814]; //0x13DC
	activeSpell* mActiveSpell; //0x1BF0 
	unsigned char pad_0x1BF4[0x50C]; //0x1BF4
	spellInst* mSpellInstArray[4]; //0x2100 
	spellInst* mPartOfSpellInst1; //0x2104 
	spellInst* mPartOfSpellInst2; //0x2108 
	spellInst* mPartOfSpellInst4; //0x210C 
	unsigned char pad_0x2110[0x14D4]; //0x2110
	int mEvolvePoints; //0x35E4 
	unsigned char pad_0x35E8[0xC]; //0x35E8
	int mEvolveFlag; //0x35F4 
	unsigned char pad_0x35F8[0xC]; //0x35F8
	float mExp; //0x3604 
	unsigned char pad_0x3608[0xC]; //0x3608
	float mLevelRef; //0x3614 
	unsigned char pad_0x3618[0xC]; //0x3618
	bool mSkillUpLevelDeltaReplicate; //0x3624 
	unsigned char pad_0x3625[0x903]; //0x3625
	int mNumNeutralMinionsKilled; //0x3F28 
	unsigned char pad_0x3F2C[0x20]; //0x3F2C
	int mInputLocks; //0x3F4C 
	unsigned char pad_0x3F50[0xC]; //0x3F50
	int mHealthBarCharacterIDForIcon; //0x3F5C 
	unsigned char pad_0x3F60[0x530]; //0x3F60
	float mPhysicalDamageTaken; //0x4490 
	unsigned char pad_0x4494[0xC]; //0x4494
	float mMagicDamageTaken; //0x44A0 
	unsigned char pad_0x44A4[0xC]; //0x44A4
	float mTrueDamageTaken; //0x44B0 
	unsigned char pad_0x44B4[0x3B4]; //0x44B4

	float getUnitSize() {
		return (this->mEdgePos2.x - this->mEdgePos1.x);
	}
}; //Size=0x4868

class objectManager
{
public:
	object * *mObjectManagerArray; //0x0000 
	int mArrayMaxSize; //0x0004 
	int mArrayCurrentUsedIndex; //0x0008 
	int mArrayHighestIndex; //0x000C 
	unsigned char pad_0x0010[0x4]; //0x0010

}; //Size=0x0014

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
	unsigned char pad_0x006E[0x33E]; //0x006E
	float mWindUpTime; //0x03AC 
	unsigned char pad_0x03B0[0xC]; //0x03B0
	float mAnimationTime; //0x03BC 
	float mSpellCoolDown; //0x03C0 
	unsigned char pad_0x03C4[0x4]; //0x03C4
	bool mIsSpellCast; //0x03C8 
	unsigned char pad_0x03C9[0x4]; //0x03C9
	bool mIsAutoAttack; //0x03CD 
	unsigned char pad_0x03CE[0x6]; //0x03CE
	float mSpellSlot; //0x03D4 
	unsigned char pad_0x03D8[0x4]; //0x03D8
	float mManaCost; //0x03DC 
	unsigned char pad_0x03E0[0x460]; //0x03E0

	int getSpellRank() {
		return this->mSpellRank + 1;
	}
}; //Size=0x0840

class spellData
{
public:
	unsigned char pad_0x0000[0x34]; //0x0000
	spellInfo* mSpellInfo; //0x0034 
	unsigned char pad_0x0038[0x3CC]; //0x0038

}; //Size=0x0404

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
	unsigned char pad_0x01FC[0x7C]; //0x01FC
	ReClassFloat mCoolDownTime[7]; //0x0278 
	unsigned char pad_0x0294[0x104]; //0x0294
	ReClassFloat mMaxRangeForPlacement[7]; //0x0398 
	ReClassFloat mMaxRange[7]; //0x03B4 
	ReClassFloat mCastRadius[7]; //0x03D0 
	unsigned char pad_0x03EC[0x8C]; //0x03EC
	float mMissileSpeed; //0x0478 
	unsigned char pad_0x047C[0x74]; //0x047C
	float mMissileWidth; //0x04F0 
	unsigned char pad_0x04F4[0x4]; //0x04F4

}; //Size=0x04F8

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
	unsigned char pad_0x0395[0xEF]; //0x0395

}; //Size=0x0484

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
		return (spellInst*)(unit + (0x2100 + (slot * 0x04)));
	}
}; //Size=0x054C

