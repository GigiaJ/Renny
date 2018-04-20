# Author: Uhrwerk (Inspired by eb's Offsets.py)
# Version: 1.3

# Imports
from idc import BADADDR, INF_BASEADDR, SEARCH_DOWN, FUNCATTR_START, FUNCATTR_END
import idc
import idaapi
import datetime

# Settings
definePrefix = "" # Prefix for the #define Output
functionPrefix = "fn" # Prefix for Function Renaming in IDA
offsetPrefix = "o" # Prefix for Offset Renaming in IDA

# Globals
Rename = -1

# Offsets // Patterns // xref's (Type:: 1 => Pattern, 2 => Call Pattern, 3 => Reference)
Functions = [
	["Logger", "8D 44 24 14 50 FF 74 24 14 FF", 1], # Writes Debug Messages (Also printed when you attach VS Debugger)
	
	["LogUIEvents", "53 55 56 8B F1 57 8B 7C 24 18", 1], # evtPlayerAttackMoveClick
	#\x53\x55\x56\x8B\xF1\x57\x8B\x7C\x24\x18 xxxxxxxxxx
	
	["CastSpell", "83 EC 34 53 55 8B 6C 24 40", 1], # ALE-229C053F / ERROR: Client Tried to cast a spell from an invalid slot: %d
	#\x83\xEC\x34\x53\x55\x8B\x6C\x24\x40 xxxxxxxxx
	
	["GetHealthbarPos", "8B 81 ? ? ? ? 85 C0 74 12", 1],	#Can be found with "ExpirationPriorityThreshold"
	#\x8B\x81\x00\x00\x00\x00\x85\xC0\x74\x12 xx????xxxx
	
	
	
	["EventHandler", "83 EC 38 A1 ? ? ? ? 33 C4 89 44 24 34 53 8B D9 56 8B 74 24 48", 1],
	
	["MainLoop", "83 EC 08 53 8B D9 89 5C 24 04 8B 4B", 1], # Not directly the main loop, but you can hook into here (func called by the main loop)
	#\x83\xEC\x08\x53\x8B\xD9\x89\x5C\x24\x04\x8B\x4B xxxxxxxxxxxx

	["DrawTurretRange", "E8 ? ? ? ? 84 C0 75 1B 83", 2],
	#\xE8\x00\x00\x00\x00\x84\xC0\x75\x1B\x83 x????xxxxx
	
	["LevelUpSpell", "83 EC 0C 53 8B 5C 24 14 56 8B F1 85 DB", 1], #ALE-89BAB541
	#\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x85\xC0\x74\x0F\x8B x????x????xxxxx
	
	["SetSkin", "E8 ? ? ? ? 8B 0E 8B F8 8B 87", 2],
	#\xE8\x00\x00\x00\x00\x8B\x0E\x8B\xF8\x8B\x87 x????xxxxxx
	
	["GetSpellData", "E8 ? ? ? ? 66 85 C0 74 06", 2], # aka. GetSpellState
	#\xE8\x00\x00\x00\x00\x66\x85\xC0\x74\x06 x????xxxxx
	
#Chat	
	["PrintChat", "E8 ? ? ? ? C6 44 24 ? ? 85 DB 74 76 8D 44 24 14", 2], 
	#\xE8\x00\x00\x00\x00\xC6\x44\x24\x00\x00\x85\xDB\x74\x76\x8D\x44\x24\x14 x????xxx??xxxxxxxx
	
	["OpenChat", "E8 23 B3 F4 FF ? ? ? ? ? ", 2], # Can be found with "game_console_chatcommand_allchat_1"
	
	["DisplayChat", "E8 19 6B F3 FF ? ? ? ? ? ", 2], #Can be found with "MaxChatBufferSize"
	
	["SendChat", "56 6A FF FF 74", 1],
	#\x56\x6A\xFF\xFF\x74 xxxxx
	
	["SetChatScale","E8 C6 87 F6 FF ? ? ? ? ? ", 2], #Can be found with "SetChatScaleX"
	
	
	["IssueOrder", "E8 ? ? ? ? 5D 5B 5F B0 01 5E 83 C4 14 C2 1C 00 FF", 2],
	#\xE8\x00\x00\x00\x00\x5D\x5B\x5F\xB0\x01\x5E\x83\xC4\x14\xC2\x1C\x00\xFF x????xxxxxxxxxxxxx
	
	["OnProcessSpell", "83 EC 10 80 7C 24 ? ? 74 25", 1],
	
	["OnProcessSpellW", "57 8B 7C 24 08 8B 17", 1],
	
	
	#NavStuff
	["SetPath", "83 EC 10 56 8B 74 24 18 57 89 4C 24 14 ",1],
	
	["CreatePath", "ALE-30FDAB23", 3],
	
	["IsWallOfGrass", "F3 0F 10 5C 24 10 83 EC 18 F3 0F 10 6C 24 20 F3 0F 10 74 24 1C 0F 2E DB 53 8B D9 56 57 F3 0F 5C 6B 1C F3 0F 5C 73 14 9F F3 0F 11 6C 24 2C", 1],
	#Non generated sig
	
	["IsWall", "E8 99 EE F9 FF ? ? ? ? ? ", 2],
	
	
	
	
	["DispatchEvent", "83 EC 20 53 55 56 57 8B D9 8D 44 24 34 50 8D 44 24 14 ", 1], #Can be found within a caller just before the loc with ; void (__cdecl *) using "ALE-C234C67E"
	
	["LoadTexture", "TEXTURE: Failed to find texture", 3],
	
	["OnProcessPacket",	"ALE-752C285F", 3], #Also calls pretty much everything and is the second longest function size wise so you can find it in the functions window
	
	["InitEvent",	"E8 98 90 FF FF ? ? ? ? ? ", 2], #Can be found with "CloseOnEndGameDelaySeconds" and following the second function after fnLogger
	
	["OnLoadHero", "E8 49 BE 00 00 ? ? ? ? ? ", 2], #Can be found with "Creating Hero %s...\n"
	
	["OnLoadChampion", "83 EC 08 E8 38 27 64 00 ? ? ? ? ? ", 1], #Found within OnLoadHero
	
	["OnTeleport", "53 55 56 57 8B 7C 24 14 8B E9 8B D7 ", 1], #Can be found a little ways above "ALE-752C285F" in ProcessPacket with two references to objectManager between right after the ;void * and ; size_t
	
	["OnDisconnect", "E8 2F CB 28 00 ? ? ? ? ? ", 2], #Can be found with "game_messagebox_caption_disconnect"
	
	["OnAfk", "E8 27 57 28 00 ? ? ? ? ? ", 2], #Can be found with "game_messagebox_text_afkwarningcaption"
	
	["SmartPing", "83 EC 18 53 56 57 8D 4C 24 0C ", 1],
	
	["GameUpdate", "E8 7E DF FF FF ? ? ? ? ? ", 2], #Can be found with "Waiting for all players to connect\n"
	
	["ClientMain", "E8 E3 78 FF FF ? ? ? ? ? ", 2], #Can be found with "Invalid AttackDelayCastOffsetPercent! Character: %s, attack index"
	
	["PlaySound", "55 56 8B 74 24 18 8B E9 83 7E 10 00 ", 1], #Can be found with "AudioManager::PlaySoundEvent: Failed to play sound event %s."
	
	["GetBasicAttack", "57 8B F9 B8 3D CB 88 3E ? ? ? ? ? ", 1], #Caller's caller can be found with "ALE-C3418C4F" then the second call after that spot is the caller
	
	["GetAttackDelay", "E8 10 98 36 00 ? ? ? ? ? ", 2], #Can be found directly above GetAttackCastDelay
	
	["GetAttackCastDelay", "83 EC 0C 53 8B 5C 24 14 8B CB ", 1],  #Caller's caller can be found with "ALE-C3418C4F" then the second call after that spot is the caller
	
	["UseObject", "E9 05 A9 F7 FF ? ? ? ? ? ", 2], #Is caller of "Load Package - %s:%u" and is at an offset of +134 inside the subroutine of UseObject
	
	["CreateObject", "53 55 56 8B 35 1C AF E4 02 ? ? ? ? ? ? ", 1], #Can be found with "GetClassID: class %d isn't present"  "WARNING: Object %s can't be loaded!\n"
	
	["IdentifyObject", "8B 51 1C 53 8B 5C 24 08 ", 1], #Can be found by going to OnTeleport's call and checking the second call within the loc above OnTeleport's loc
	
	["DeleteObject", "83 EC 08 53 8B 5C 24 10 55 56 57 8A 83 98 00 00 00 ? ? ? ? ? ? ", 1], #Can be found by checking in OnLoadHero and looking at the last call in the loc above "game_bot_"'s loc
	
	["AddRemoveBuff", "E8 76 45 41 00 ? ? ? ? ? ", 2], #Can be found with "PersistsThroughDeath" "NonDispellable" "OnPreDamagePriority" and several others
	
	["LevelUp", "E8 64 AD 05 00 ? ? ? ? ? ", 2], #Can be found with "ALE-EC0BF512" "ALE-BD06C313" "ALE-06905997" "ALE-F65F3A49"
	
	["AssignNetworkID", "83 EC 08 56 8B F1 8B 46 74 C6 46 10 00 ", 1], #Can be found with "GameObject Network ID is being reset for %s"
	
	["UpdateBuff", "83 EC 14 53 55 56 8B 74 24 2C ", 1], #Caller can be found with "ALE-DEFF93BD" "ALE-CFFAE012", the call is in the loc after "ALE-DEFF93BD" third call from the bottom
	
	["DoEmote", "E8 30 CB 11 00 ? ? ? ? ? ", 1], #Can be found by using IDA search feature and searching "evtEmoteDance" cancelling the search and then searching next text twice, after stepping into the sub being pushed after the push 0 the sub being jumped to is DoEmote
	#Is a call within DoEmote but setting it as a pattern makes it bring up the DoEmote address
	
	["DoMasteryBadge", "E8 B7 45 F5 FF ? ? ? ? ? ", 2], #Can be found with "ALE-A6219283"
	
	["OnSurrenderVote", "E8 4B 0C 2F 00 ? ? ? ? ? ", 2], #Can be found by using the second call of PrintChat in OnProcessPacket and scrolling up until you are three locs below a local player reference
	
	["UpdateChargeableSpell", "83 EC 28 53 55 8B 6C 24 34 56 ", 1], #Can be found by looking in GameUpdate and checking the next decent sized loc above "Game Ended.  Closing after delay is satisfied." (about 4 locs up) and stepping into the call right after the cursor is being moved onto ecx
	# and in the second to last loc stepping into the second call in the loc then it is the call near the end that has a lead ecx to the spellbook ptr (also has a LocalPlayer being moved onto the ESI)
	#Can also be found by using MassSigCheck (my own script) and finding the one that calls it which also calls GetSpellState and it is the call near the end that has a lead ecx to the spellbook ptr
	
	["ApplySpellCD", "E8 23 A5 FF FF ? ? ? ? ? ", 2], #Can be found with "ALE-6213D87E" "ALE-42E20CB6"
	
	["StopCast", "83 EC 10 56 8B 74 24 24 ", 1],
	
	["GetBoundingRadius", "51 56 8B F1 83 BE 30 24 00 00 00 ? ? ? ? ? ? ? ", 1], #Can be found by tracing UseObject caller, the first call above where useobject is called 
	#Then in there the loc that moves the localplayer onto a register you can hit the second call from the bottom 
	#After there is a loc with only two operations a mov and a call, the call is a subroutine that has two callers, the caller that you didn't use to get to this point is GetBoundingRadius
	
	["WorldToScreen", "E8 79 11 26 00 ? ? ? ? ? ", 2], #A caller of one of the callers can be found with "MaxPingParticleTime". In the loc with a dword being moved onto a register the call with eax being pushed on is the caller of this method
	#in the loc where Renderer is reference you can find as the first call where eax is pushed
	
	["ScreenToWorld", "E8 5F AB 1E 00 ? ? ? ? ? ", 2], #A caller of one of the callers can be found with "MaxPingParticleTime". In the loc with a dword being moved onto a register the call with eax being pushed on is the caller of this method
	#This one is the first call in the loc that has Renderer referenced
	
	["MapToWorld", "83 EC 08 8B 44 24 0C F3 0F 10 15 84 26 F8 00 ? ? ? ? ? ? ? ? ", 1], #Caller can be found with "CapturePointUnderAttack" and then the call to it is in the second loc third caller. It is also preceded by push eax and a mov ecx, edi
	
	["World2Map", "8B 44 24 04 53 8B D9 56 57 8B 3B ", 1], #Can be found in LoadHero five locs down from the loc that calls OnLoadChampion it is the last call in this loc
	
	["GetTacticalMap", "E8 91 5F 39 00 ? ? ? ? ? ", 1], #Caller can be found with "Distance_To_Audio_Linked_Ally" and it is in the third loc from the bottom and is the second to last call in the loc
	#Is a call within GetTacticalMap but setting as a pattern so it brings up GetTacticalMap's address
	
]

Offsets = [
	["LocalPlayer","39 3D 38 FF E4 02 ? ? ? ? ? ? ", 1, 0], #All the other ones start with 8B or A1, no sigs from prev version are the same, but the one starting with 3 will make a valid sig

	["ChatClientPtr", "A1 ? ? ? ? 85 C0 74 32", 1, 1],
	#\xA1\x00\x00\x00\x00\x85\xC0\x74\x32 x????xxxx
	["ObjectManager", "A1 ?? ?? ?? ?? 8B 0C 88 85 C9 74 0E 39 71 08 75 09 6A 01", 1, 1], # ALE-DFB7B379 (below mov eax, ObjectManager)
	
	["Renderer", "A1 A0 43 E7 02 ? ? ? ? ? 8B 80 E0 95 0C 00 ? ? ? ? ? ? ", 1, 1], # SkinnedMesh_SOLID_COLOR_PS (above mox ecx, Renderer) / %1_WEIGHT%2 (below call sub .. mov ecx, Renderer)
		
	["ZoomClass", "A3 ? ? ? ? 8D 4C 24 20", 1, 0], # Globals/CameraConfig_CLASSIC (above cmp ZoomBase, 0)
	
	["UnderMouseObject", "C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 04 FF B4", 1, 0],
	#\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xFF\xB4 xx????????x????xxxxx
	
	["Cursor", "A1 ? ? ? ? 8B 40 14 85", 1, 1], # evtCameraSnap .. Leads to Mouse Position (8.4: ] + 0x14] + 0x10 = Vec3 of Mouse Position)
	#\xA1\x00\x00\x00\x00\x8B\x40\x14\x85 x????xxxx
	
	["MissionInfo", "8B 35 04 9C E7 02 ? ? ? ? ? ? ", 1,1], #Caller of a sub using it can be found with "EndSnapshotCapture" and the sub using it is the first call in that loc. Within that sub it's the first dword in the sub (move edi, dword_whatever)
	
	["Version", "B8 A0 56 E5 02 ? ? ? ? ? ", 1, 1], #Function referencing it can be found with "Build Version: %s ChangeList: %u\n", it is the function in the loc with "Build Version: %s ChangeList: %u\n" that has eax pushed on as an arg
	
	["NetClient", "89 1D C8 FF E4 02 ? ? ? ? ? ? ", 1, 0], #Can be found with "Build Version: %s ChangeList: %u\n" it is the dword in the loc directly above the loc in which "Build Version: %s ChangeList: %u\n" is used
	
	["TexturePack", "83 3D 88 23 E5 02 00 ? ? ? ? ? ? ? ",1,0], #Can be found with "%.4f    %.4f    %.4f\n" and is the dword used in this sub
	
	["GameTime", "F3 0F 5C 0D C4 80 E4 02 ? ? ? ? ? ? ? ? ", 1,	1], #Should be found via the caller of the subroutine that uses this. 
	#Caller of the using sub can be searched with "GAMESTATE_GAMELOOP UpdateVis\n" and it is at the top of the loc prior to this phrase
	
	
	]

# Finder Functions
def FindFuncPattern(Pattern): # Find's Func. by Pattern
	addr = idc.FindBinary(0, SEARCH_DOWN, Pattern)
	if addr == BADADDR: return 0
	
	try:
		return idaapi.get_func(addr).startEA
	except Exception:
		return 0
		
def FindFuncCall(Pattern): # Find's Func. by Pattern to a Call
	addr = idc.FindBinary(0, SEARCH_DOWN, Pattern)
	if addr == BADADDR: return 0
	return idc.GetOperandValue(addr, 0)
	
def FindFuncFirstReference(Reference): # Find's Func. by Reference, Returns first 
	addr = idc.FindBinary(0, SEARCH_DOWN, "\"" + Reference + "\"")
	if addr == BADADDR: return 0
	
	dword = -1
	xrefs = XrefsTo(addr)
	for xref in xrefs:
		dword = xref.frm
		
	try:
		return idaapi.get_func(dword).startEA
	except Exception:
		return 0

def FindStringByReference(Reference): # Extracts String out of Reference (//addr)
	addr = idc.FindBinary(0, SEARCH_DOWN, "\"" + Reference + "\"")
	if addr == BADADDR: return 0
	return idc.GetString(addr)
	
def FindOffsetPattern(Pattern, Operand): # Find Offset by Pattern
	addr = idc.FindBinary(0, SEARCH_DOWN, Pattern)
	if addr == BADADDR: return 0
	
	return idc.GetOperandValue(addr, Operand)
	
# Helpers
def DecToHex(Addr):
	return "0x%0.2X" % Addr
	
def PrintWrapper(Alias, Addr, Type): # Type: 1 => Function, 2 => Offset
	if Addr == BADADDR or Addr == 0 or Addr == 0x00:
		print(Alias + " -> Error")
		return
		
	if Type == 1: print("#define " + functionPrefix + Alias + " " + DecToHex(Addr))
	if Type == 2: print("#define " + offsetPrefix + Alias + " " + DecToHex(Addr))
	
	if Rename == 1:
		if Type == 1: MakeName(Addr, str(functionPrefix + Alias))
		if Type == 2: MakeName(Addr, str(offsetPrefix + Alias))
		
	return
	
# Main
def Initialize():
	global Rename
	Rename = idc.AskYN(0, "Automaticly Update Names? (sub_549570 => PrintChat)")
	if Rename == -1:
		print("Exiting...")
		return
		
	print("")
	print("++ Uhrwerk: Offsets (%s)" % datetime.datetime.now())
	print("Why do they keep breaking...")
	print("")
	
	print("++ Functions")
	for Alias, Reference, Type in Functions:
		if Type == 1: PrintWrapper(Alias, FindFuncPattern(Reference), 1)
		if Type == 2: PrintWrapper(Alias, FindFuncCall(Reference), 1)
		if Type == 3: PrintWrapper(Alias, FindFuncFirstReference(Reference), 1)
	print("")
	
	print("++ Offsets")
	for Alias, Reference, Type, Operand in Offsets:
		if Type == 1: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2)
		if Type == 2: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2)
	print("")
	
Initialize()