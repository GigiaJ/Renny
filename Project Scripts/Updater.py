from OffsetGenerator import *
from AddressGenerator import *

j_CReplInfo32Address = 0x1F7910
CReplInfo32Address = 0x2060F0


IgnoreOffsetList = ["mReplicatedSpellCanCastBitsUpper1", "mMaxMP", "mMP", "mReplicatedSpellCanCastBitsLower1", "ReplicatedSecondWordSpellCanCastBitsLower1"]

def CreateAddresses():
	GenerateAddresses()

def CreateCharDataOffsets():
	GenerateList(j_CReplInfo32Address)
	GenerateList(CReplInfo32Address)
	temp = OrderedDict(sorted(Offsets.items(), key=lambda t: t[1]))
	
	IntegerOffsets = ["mEvolveFlag", "mEvolvePoints", "mNumNeutralMinionsKilled", "mInputLocks", "mHealthBarCharacterIDForIcon", "mSARState", "mPARState", "mNetworkId", "mTeam"]
	BoolOffsets = ["mIsDead", "isVisible", "mPAREnabled", "mSAREnabled", "mEmpoweredBitField", "mIsUntargetableToEnemies", "mIsUntargetableToAllies", "mIsTargetable", "mIsTargetableToTeamFlags", "mSkillUpLevelDeltaReplicate"]
	
	print("class object ")
	print("{")
	print("public:")
	lastValue = 0
	counter = 0
	for key,val in temp.items():
		if key not in IgnoreOffsetList:
			padAmount = val - lastValue
			if padAmount > 4:
				print("\t" + "unsigned char pad_{}".format(counter) + "[0x" + "%0.2X" % padAmount + "]")
				counter = counter + 1
			if key in IntegerOffsets:
				print("\t" + "int " + key + " 0x" + "%0.2X " % val)
			elif key in BoolOffsets:
				print("\t" + "bool " + key + " 0x" + "%0.2X " % val)
			else:
				print("\t" + "float " + key + " 0x" + "%0.2X " % val)
			lastValue = val
			
	
def Initialize():
	CreateAddresses()
	CreateCharDataOffsets()
	
Initialize()