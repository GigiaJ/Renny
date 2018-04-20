// Generated using ReClass 2016

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
#define fnIssueOrder 0x5C8880
#define fnOnProcessSpell 0x550F70
#define fnOnProcessSpellW 0x55C3F0
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

struct Vector
{
	float x;
	float y;
	float z;
};

class object;
class objectManager;
class activeSpell;
class spellCastDataBase;
class spellData;
class spellInst;
class oMouse;
class spellInfo;
class AIManager;

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
	unsigned char pad_0x06FC[0x764]; //0x06FC
	float mPercentCooldownCapMod; //0x0E60 
	unsigned char pad_0x0E64[0xC]; //0x0E64
	float mPassiveCooldownEndTime; //0x0E70 
	unsigned char pad_0x0E74[0xC]; //0x0E74
	float mPassiveCooldownTotalTime; //0x0E80 
	unsigned char pad_0x0E84[0x2C]; //0x0E84
	float mFlatPhysicalDamageMod; //0x0EB0 
	unsigned char pad_0x0EB4[0xC]; //0x0EB4
	float mPercentPhysicalDamageMod; //0x0EC0 
	unsigned char pad_0x0EC4[0xC]; //0x0EC4
	float mFlatMagicDamageMod; //0x0ED0 
	unsigned char pad_0x0ED4[0xC]; //0x0ED4
	float mPercentMagicDamageMod; //0x0EE0 
	unsigned char pad_0x0EE4[0xC]; //0x0EE4
	float mFlatMagicReduction; //0x0EF0 
	unsigned char pad_0x0EF4[0xC]; //0x0EF4
	float mPercentMagicReduction; //0x0F00 
	unsigned char pad_0x0F04[0xC]; //0x0F04
	float mFlatCastRangeMod; //0x0F10 
	unsigned char pad_0x0F14[0xC]; //0x0F14
	float mAttackSpeedMod; //0x0F20 
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
	float mPercentBonusArmorPenetration; //0x1080 
	unsigned char pad_0x1084[0xC]; //0x1084
	float mPercentArmorPenetration; //0x1090 
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
	float mPARRegenRate; //0x1150 
	unsigned char pad_0x1154[0xC]; //0x1154
	float mPrimaryARBaseRegenRateRep; //0x1160 
	unsigned char pad_0x1164[0xC]; //0x1164
	float mSecondaryARRegenRateRep; //0x1170 
	unsigned char pad_0x1174[0xC]; //0x1174
	float mSecondaryARBaseRegenRateRep; //0x1180 
	unsigned char pad_0x1184[0xB8]; //0x1184
	float mGold; //0x123C 
	unsigned char pad_0x1240[0x8]; //0x1240
	AIManager* mAIManager; //0x1248 
	float mGoldTotal; //0x124C 
	unsigned char pad_0x1250[0xC]; //0x1250
	float mMinimumGold; //0x125C 
	unsigned char pad_0x1260[0x158]; //0x1260
	Vector mDirectionFaced; //0x13B8 
	unsigned char pad_0x13C4[0xCFC]; //0x13C4
	spellInst* mSpellInstArray[4]; //0x20C0 
	unsigned char pad_0x40D0[0x15EC]; //0x40D0
	int mEvolvePoints; //0x56BC 
	unsigned char pad_0x56C0[0xC]; //0x56C0
	int mEvolveFlag; //0x56CC 
	unsigned char pad_0x56D0[0xC]; //0x56D0
	float mExp; //0x56DC 
	unsigned char pad_0x56E0[0xC]; //0x56E0
	float mLevelRef; //0x56EC 
	unsigned char pad_0x56F0[0xC]; //0x56F0
	bool mSkillUpLevelDeltaReplicate; //0x56FC 
	unsigned char pad_0x56FD[0x903]; //0x56FD
	int mNumNeutralMinionsKilled; //0x6000 
	unsigned char pad_0x6004[0x20]; //0x6004
	int mInputLocks; //0x6024 
	unsigned char pad_0x6028[0xC]; //0x6028
	int mHealthBarCharacterIDForIcon; //0x6034 
	unsigned char pad_0x6038[0x530]; //0x6038
	float mPhysicalDamageTaken; //0x6568 
	unsigned char pad_0x656C[0xC]; //0x656C
	float mMagicDamageTaken; //0x6578 
	unsigned char pad_0x657C[0xC]; //0x657C
	float mTrueDamageTaken; //0x6588 
	unsigned char pad_0x658C[0x374]; //0x658C

	float getUnitSize() {
		return (this->mEdgePos2.x - this->mEdgePos1.x);
	}
}; //Size=0x6900

class objectManager
{
public:
	object** mObjectManagerArray; //0x0000 
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
	unsigned char pad_0x0004[0x4]; //0x0004
	int mSpellLevel; //0x0008 
	unsigned char pad_0x000C[0x14]; //0x000C
	short casterIndex; //0x0020 
	unsigned char pad_0x0022[0x16]; //0x0022
	Vector mStartPosition; //0x0038 
	Vector mTargetPosition; //0x0044 
	unsigned char pad_0x0050[0x18]; //0x0050
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

}; //Size=0x0840

class spellData
{
public:
	unsigned char pad_0x0000[0x34]; //0x0000
	spellInfo* mSpellInfo; //0x0034 
	unsigned char pad_0x0038[0x3CC]; //0x0038

}; //Size=0x0404

class spellInst
{
public:
	unsigned char pad_0x0000[0x1C]; //0x0000
	float mCurrentRank; //0x001C 
	unsigned char pad_0x0020[0x48]; //0x0020
	float mCurrentCDR; //0x0068 
	unsigned char pad_0x006C[0xB0]; //0x006C
	spellData* mSpellData; //0x011C 
	unsigned char pad_0x0120[0x6E4]; //0x0120

public:
	static spellInst* getSpellInst(DWORD lPlayer, int slot) {
		return (spellInst*)(lPlayer + (0x20C0 + (slot * 0x04)));
	}
}; //Size=0x0804

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
	unsigned char pad_0x0000[0xD0]; //0x0000
	float mSpellCostFirstLevel; //0x00D0 
	float mSpellCostSecondLevel; //0x00D4 
	float mSpellCostThirdLevel; //0x00D8 
	float mSpellCostFourthLevel; //0x00DC 
	float mSpellCostFifthLevel; //0x00E0 
	unsigned char pad_0x00E4[0x164]; //0x00E4
	float mCastTime; //0x0248 
	unsigned char pad_0x024C[0x20]; //0x024C
	float mCoolDownTime; //0x026C 
	unsigned char pad_0x0270[0x138]; //0x0270
	float mMaxRange; //0x03A8 
	unsigned char pad_0x03AC[0x18]; //0x03AC
	float mCastRadius; //0x03C4 
	unsigned char pad_0x03C8[0xA4]; //0x03C8
	float mMissileSpeed; //0x046C 
	unsigned char pad_0x0470[0x74]; //0x0470
	float mMissileWidth; //0x04E4 
	unsigned char pad_0x04E8[0x58]; //0x04E8

}; //Size=0x0540

class AIManager
{
public:
	unsigned char pad_0x0000[0x194]; //0x0000
	float mCurrentMovementSpeed; //0x0194 
	bool mIsMoving; //0x0198 
	unsigned char pad_0x0199[0xB]; //0x0199
	Vector mLastPosition; //0x01A4 
	Vector mNextPosition; //0x01B0 
	unsigned char pad_0x01BC[0x100]; //0x01BC
	Vector mCurrentPosition; //0x02BC 
	unsigned char pad_0x02C8[0x94]; //0x02C8
	Vector mDashEndPosition; //0x035C 
	unsigned char pad_0x0368[0x2C]; //0x0368
	bool mIsDashing; //0x0394 
	unsigned char pad_0x0395[0xEF]; //0x0395

}; //Size=0x0484

