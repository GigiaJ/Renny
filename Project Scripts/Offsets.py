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
	["Logger", "8D ?? 24 ?? 50 FF ?? 24 ?? FF ?? 24 ?? FF ?? 24 ?? FF ?? 24 ?? E8 ?? ?? ?? ?? ?? C4 ?? C3 ", 1, True], # Writes Debug Messages (Also printed when you attach VS Debugger)
	
	["LogUIEvents", "53 55 56 8B F1 57 8B ?? 24 ?? ?? 6E ?? 3B FD ", 1, True], # evtPlayerAttackMoveClick
	
	["CastSpell", "83 EC ?? 53 55 56 8B 74 24 ?? 8B E9 57 83 BE ?? ?? 00 00 00 ", 1, True], # ALE-229C053F / ERROR: Client Tried to cast a spell from an invalid slot: %d
	
	["GetHealthbarPos", "8B ?? ?? ?? ?? ?? 85 C0 74 12 FF 74 24 ?? ", 1, True],	#Can be found with "ExpirationPriorityThreshold"	
	
	["EventHandler", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 53 8B D9 56 8B 74 24 ?? ", 1, True],
	
	["MainLoop", "E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 85 C0 74 07 8B 10 8B C8 FF 52 10 ", 2, True],

	["DrawTurretRange", "E8 ?? ?? ?? ?? 84 C0 75 1B 83 BE ?? ?? 00 00 00 ", 2, True],
	
	["LevelUpSpell", "83 EC ?? 53 8B 5C 24 ?? 56 8B F1 85 DB 78 05 ", 1, True],	 #ALE-89BAB541
	
	["SetSkin", "E8 ?? ?? ?? ?? 83 C4 ?? 89 44 24 ?? 8B C8 8B 10 ", 2, True],	
	
	["GetSpellData", "8B 44 24 ?? 83 EC ?? 53 8B ?? ?? ?? ?? ?? 00 ", 1, True], # aka. GetSpellState
	
#Chat	
	["PrintChat", "E8 ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? 6A 01 E8 ?? ?? ?? ?? B0 01 ", 2, True],	
	
	["OpenChat", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 53 57 8B F9 33 DB 89 5C 24 ?? ", 1, True], # Can be found with "game_console_chatcommand_allchat_1"
	
	["DisplayChat", "E8 ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? 85 C9 0F ?? ?? ?? ?? ?? C2 08 00 ", 2, True], #Can be found with "MaxChatBufferSize"
	
	["SendChat", "56 6A FF FF 74 24 ?? 8B F1 ", 1, True],
	
	["SetChatScale", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? F3 ?? ?? ?? ?? ?? 8D 04 24 56 ", 1, True], #Can be found with "SetChatScaleX"
	
	["IssueOrder", "81 EC ?? ?? 00 00 53 8B D9 C7 ?? ?? ?? ?? ?? ?? ?? 8B 83 ?? ?? 00 00 ", 1, True], #Can be found in EventMoveMouseClick, the caller of the caller of CreatePath
	
	["OnMoveMouseClick", "E8 ?? ?? ?? ?? 5D 5B 5F B0 01 5E 83 C4 ?? C2 1C 00 FF 74 24 ?? ", 2, True],
	
	["CheckIfInitialClickIsAvaliable", "83 EC ?? F3 ?? ?? ?? ?? ?? 8B C1 53 ", 1, True], #Can be found in CreatePath, returns a bool and returns a true on clicking a wall
		
	["OnProcessSpell", "E8 ?? ?? ?? ?? 8B F0 83 C4 ?? 8B CE 8B 16 57 ", 2, True], #Called by OnProcessSpellW
	
	["OnProcessSpellW", "57 8B 7C 24 ?? 8B 17 85 D2 ", 1, True], #Called by OnSpellCast and OnAutoAttack
	
	["OnSpellCast", "81 EC ?? ?? 00 00 A1 ?? ?? ?? ?? 33 C4 89 84 24 ?? ?? 00 00 53 8B ?? ?? ?? ?? ?? 00 55 56 8B E9 89 5C 24 ?? 57 8D 4C 24 30 ", 1, True],
	
	["OnAutoAttack", "E8 ?? ?? ?? ?? 8D 4C 24 ?? 8A D8 E8 ?? ?? ?? ?? 8A C3 E9 D4 02 00 00 ", 2, True],
	
	#NavStuff
	["SetPath", "83 EC ?? 56 8B 74 24 ?? 57 89 4C 24 ?? 8B 46 ?? ", 1, True],
	
	["CreatePath", "F3 0F 7E 00 8B 40 ?? 89 44 24 ?? 8B 45 10 ", 1, True], #Can be found with "ALE-30FDAB23"
	
	["OnUpdatePath", "55 8B EC 51 53 56 57 8B 7D 08 33 DB ", 1, True],
	
	["IsWallOfGrass", "F3 ?? ?? ?? ?? ?? 83 EC ?? F3 ?? ?? ?? ?? ?? F3 ?? ?? ?? ?? ?? 0F 2E ?? ", 1, True],
	
	["DispatchEvent", "83 EC ?? 53 55 56 57 8B D9 8D 44 24 ?? 50 8D 44 24 14 ", 1, True], #Can be found within a caller just before the loc with ; void (__cdecl *) using "ALE-C234C67E"
	
	["LoadTexture", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 8B 44 24 ?? 53 55 56 57 8B 7C 24 ?? 8B E9 ", 1, True], #Can be found with "TEXTURE: Failed to find texture"
	
	["OnProcessPacket", "81 EC ?? ?? 00 00 A1 ?? ?? ?? ?? 33 C4 89 84 24 ?? ?? 00 00 53 55 8B AC 24 ?? ?? 00 00 56 57 8B F1 89 6C 24 ?? ", 1, True], #Can be found with "ALE-752C285F" Also calls pretty much everything and is the second longest function size wise so you can find it in the functions window 
	
	["InitEvent", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 53 55 56 57 8B ?? ?? ?? ?? ?? 00 00 00 8D 4F 34 ", 1, True], #Can be found with "CloseOnEndGameDelaySeconds" and following the jump if not zero  first call and then the second function within that call is InitEvent
	
	["OnLoadHero", "FF 74 24 ?? 0F 43 44 24 ?? FF 74 24 ?? ", 1, True], #Can be found with {:5s}| {#channel!} Spawn Champion Request {ChampionName} [{#Summo
	
	["OnLoadChampion", "83 EC ?? E8 ?? ?? ?? ?? 68 ?? ?? ?? ?? ", 1, True], #Found within OnLoadHero
	
	["OnTeleport", "53 55 56 57 8B 7C 24 ?? 8B E9 8B D7 ", 1, True], #Can be found a little ways above "ALE-752C285F" in ProcessPacket with two references to objectManager between right after the ;void * and ; size_t
	
	["OnDisconnect", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 56 8B F1 C7 ?? ?? ?? ?? ?? ?? ?? 8D 44 24 ?? 89 74 24 ?? 50 C7 ?? ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? ?? ?? 89 44 24 ?? E8 ?? ?? ?? ?? 8B 4C 24 28 85 C9 74 12 8B 11 8D 44 24 ?? 3B C8 0F 95 C0 0F B6 C0 50 FF 52 10 6A 22 ", 1, True], #Can be found with "game_messagebox_caption_disconnect"

	["OnAfk", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 56 8B F1 C7 ?? ?? ?? ?? ?? ?? ?? 8D 44 24 ?? 89 74 24 ?? 50 C7 ?? ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? ?? ?? 89 44 24 ?? E8 ?? ?? ?? ?? 8B 4C 24 28 85 C9 74 12 8B 11 8D 44 24 ?? 3B C8 0F 95 C0 0F B6 C0 50 FF 52 10 6A 26 ", 1, True], #Can be found with "game_messagebox_text_afkwarningcaption"
	
	["SmartPing", "E8 ?? ?? ?? ?? 5E 5B 5F C2 10 00 84 DB ", 2, True],
	
	["GameUpdate", "E8 ?? ?? ?? ?? A1 ?? ?? ?? ?? 85 C0 74 14 ", 2, True], #Can be found with "Waiting for all players to connect\n"
	
	["ClientMain", "E8 ?? ?? ?? ?? 83 C6 28 43 ", 2, True], #Can be found with "Invalid AttackDelayCastOffsetPercent! Character: %s, attack index"
	
	["PlaySound", "55 56 8B 74 24 ?? 8B E9 83 7E 10 00 75 11 ", 1, True], #Can be found with "AudioManager::PlaySoundEvent: Failed to play sound event %s."
	
	["GetBasicAttack", "E8 ?? ?? ?? ?? 8B E8 ?? ?? ?? ?? 02 FF 75 6C ", 2, True], #Caller's caller can be found with "ALE-C3418C4F" then the second call after that spot is the caller then in it, it is the call before GetAttackCastDelay
	
	["GetAttackDelay", "83 EC ?? F3 ?? ?? ?? ?? ?? C7 ?? ?? ?? ?? ?? ?? 57 ", 1, True], #Can be found directly above GetAttackCastDelay
	
	["GetAttackCastDelay", "83 EC ?? 53 8B 5C 24 ?? 8B CB 56 ", 1, True],  #Caller's caller can be found with "ALE-C3418C4F" then the second call after that spot is the caller
	#####
	["UseObject", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? 53 55 8B 6C 24 ?? 8B D9 56 57 89 6C 24 ?? E8 ?? ?? ?? ?? ", 1, True], #Is caller of "8B 44 24 04 56 8B F1 89 46 48 ", 1 (only has 3 callers and one is issueorder, one is unknonwn, and one is useobject
	
	["CreateObject", "53 56 8B ?? ?? ?? ?? ?? 57 85 F6 75 27 ", 1, True], #Can be found with "GetClassID: class %d isn't present"  "WARNING: Object %s can't be loaded!\n"
	
	["IdentifyObject", "E8 ?? ?? ?? ?? 85 C0 74 15 8D ?? ?? ?? ?? ?? 8B 01 ", 2, True], #Can be found by going to OnTeleport's call and checking the second call within the loc above OnTeleport's loc
	
	["DeleteObject", "83 EC ?? 53 55 8B 6C 24 ?? 56 57 8B ?? ?? ?? ?? ?? 00 00 84 C0 ", 1, True], #Can be found by checking in OnLoadHero and looking at the last call in the loc above "game_bot_"'s loc
	
	["AddRemoveBuff", "56 6A 00 6A 00 6A 00 6A 00 6A 04 68 ?? ?? ?? ?? 6A 00 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 68 4C 8A 60 BE ", 1, True], #Can be found with "PersistsThroughDeath" "NonDispellable" "OnPreDamagePriority" and several others
	
	["LevelUp", "F3 ?? ?? ?? ?? ?? 0F 57 C9 0F 2F C1 56 57 ", 1, True], #Can be found with "ALE-EC0BF512" "ALE-BD06C313" "ALE-06905997" "ALE-F65F3A49"
	
	["AssignNetworkID", "74 2D 89 44 24 ?? ", 1, True],	 #SUCCESS	0x2E24D0 #Can be found with "GameObject Network ID is being reset for %s"
	
	["UpdateBuff", "83 EC ?? 53 55 8B 6C 24 ?? 56 8B F1 89 74 24 ?? 57 85 ED ", 1, True], #Caller can be found with "ALE-DEFF93BD" "ALE-CFFAE012", the call is in the loc after "ALE-DEFF93BD" third call from the bottom
	
	["DoEmote", "A1 ?? ?? ?? ?? 83 EC ?? 8B 48 08 E8 ?? ?? ?? ?? 84 C0 74 08 32 C0 83 C4 ?? C2 04 00 8B ?? ?? ?? ?? ?? ", 1, True], #Can be found by using IDA search feature and searching "evtEmoteDance" cancelling the search and then searching next text twice, after stepping into the sub being pushed after the push 0 the sub being jumped to is DoEmote
	#Is a call within DoEmote but setting it as a pattern makes it bring up the DoEmote address
	
	["DoMasteryBadge", "81 EC ?? ?? 00 00 A1 ?? ?? ?? ?? 33 C4 89 84 24 ?? ?? 00 00 53 8B 9C 24 ?? ?? 00 00 55 8B E9 8B 8C 24 ?? ?? 00 00 ", 1, True], #Can be found with "ALE-A6219283"
	
	["OnSurrenderVote", "8B 81 ?? ?? 00 00 8A 54 24 0C 53 ", 1, True], #Can be found by using the second call of PrintChat in OnProcessPacket and scrolling up until you are three locs below a local player reference
	
	["UpdateChargeableSpell", "83 EC 28 53 55 8B 6C 24 34 56 ", 1, True], #Can be found by looking in GameUpdate and checking the next decent sized loc above "Game Ended.  Closing after delay is satisfied." (about 4 locs up) and stepping into the call right after the cursor is being moved onto ecx
	# and in the second to last loc stepping into the second call in the loc then it is the call near the end that has a lead ecx to the spellbook ptr (also has a LocalPlayer being moved onto the ESI)
	#Can also be found by using MassSigCheck (my own script) and finding the one that calls it which also calls GetSpellState and it is the call near the end that has a lead ecx to the spellbook ptr
	
	["ApplySpellCD", "FF 74 24 ?? 8B ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 85 C9 ", 1, True], #Can be found with "ALE-6213D87E" "ALE-42E20CB6"
	
	["StopCast", "83 EC ?? 56 8B 74 24 ?? 8D 44 24 ?? 57 50 8D 54 24 14 ", 1, True],
	
	["GetBoundingRadius", "D9 54 24 ?? F3 ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? ", 1, True], #Can be found by tracing UseObject caller, the first call above where useobject is called ## Calls this func ["sub", "E8 ?? ?? ?? ?? D9 54 24 04 F3 0F 10 44 24 04 ", 2, True]
	#Then in there the loc that moves the localplayer onto a register you can hit the second call from the bottom 
	#After there is a loc with only two operations a mov and a call, the call is a subroutine that has two callers, the caller that you didn't use to get to this point is GetBoundingRadius
	
	["WorldToScreen", "83 EC ?? A1 ?? ?? ?? ?? 33 C4 89 44 24 ?? A1 ?? ?? ?? ?? 8D 54 24 08 ", 1, True], #A caller of one of the callers can be found with "MaxPingParticleTime". In the loc with a dword being moved onto a register the call with eax being pushed on is the caller of this method
	#in the loc where Renderer is reference you can find as the first call where eax is pushed
	
	["ScreenToWorld", "81 EC ?? ?? 00 00 A1 ?? ?? ?? ?? F3 0F ?? ?? ?? ?? ?? ?? ", 1, True], #A caller of one of the callers can be found with "MaxPingParticleTime". In the loc with a dword being moved onto a register the call with eax being pushed on is the caller of this method
	#This one is the first call in the loc that has Renderer referenced
	
	["MapToWorld", "E8 ?? ?? ?? ?? 8B 75 0C 8D 44 24 ?? ", 2, True], #Caller can be found with "CapturePointUnderAttack" and then the call to it is in the second loc third caller. It is also preceded by push eax and a mov ecx, edi
	
	["World2Map", "8B 44 24 ?? 53 8B D9 56 57 8B 3B ", 1, True], #Can be found in LoadHero five locs down from the loc that calls OnLoadChampion it is the last call in this loc
	
	["GetTacticalMap", "E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B 4C 24 18 85 C9 74 1A ", 2, True], #Caller can be found with "Distance_To_Audio_Linked_Ally" and it is in the third loc from the bottom and is the second to last call in the loc
	#Is a call within GetTacticalMap but setting as a pattern so it brings up GetTacticalMap's address
	
	
	
	
	["j_CReplInfo32__AddVar", "6A ?? FF 74 24 ?? FF 74 24 ?? FF 74 24 ?? E8 ?? ?? ?? ?? C2 0C 00 ", 1, False],
	
]

Offsets = [
	["LocalPlayer", "8B ?? ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? 00 00 89 44 24 ?? 8D 44 24 ?? ", 1, 1, True],

	["ChatClientPtr", "B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? A1 ?? ?? ?? ?? 89 44 24 ?? ", 1, 1, True],
	
	["ObjectManager", "B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B F0 85 F6 74 36 ", 1, 1, True], # ALE-DFB7B379 (below mov eax, ObjectManager)
	
	["Renderer", "8B ?? ?? ?? ?? ?? 6A ?? 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? 6A ?? 56 ", 1, 1, True],	  # SkinnedMesh_SOLID_COLOR_PS (above mox ecx, Renderer) / %1_WEIGHT%2 (below call sub .. mov ecx, Renderer)["oRenderer", "83 3D BC 2D E4 02 00 ? ? ? ? ? ? ? 56 ", 2],	 #SUCCESS	0x2E42DBC
	
	["ZoomClass", "A3 ?? ?? ?? ?? 8D 4C 24 ?? E8 ?? ?? ?? ?? A1 ?? ?? ?? ?? 5E 8B 4C 24 ?? 89 47 40 ", 1, 0, True], # Globals/CameraConfig_CLASSIC (above cmp ZoomBase, 0)
	
	["UnderMouseObject", "C7 ?? ?? ?? ?? ?? ?? ?? 00 00 E8 ?? ?? ?? ?? 83 C4 ?? FF B4 24 ?? 00 00 00 ", 1, 0, True],
	
	["Cursor", "8B ?? ?? ?? ?? ?? 8B 49 34 E8 ?? ?? ?? ?? 85 C0 ", 1, 1, True], # evtCameraSnap .. Leads to Mouse Position (8.4: ] + 0x14] + 0x10 = Vec3 of Mouse Position)
	
	["MissionInfo", "C7 ?? ?? ?? ?? ?? ?? ?? 00 00 5B 74 0E ", 1, 0, True], #Caller of a sub using it can be found with "EndSnapshotCapture" and the sub using it is the first call in that loc. Within that sub it's the first dword in the sub (move edi, dword_whatever)
	
	["GameState", "8B ?? ?? ?? ?? ?? 8D 04 ?? 6A 03 50 6A 04 E8 ?? ?? ?? ?? 8D 0C 24 E8 ?? ?? ?? ?? 8B 8C 24 ?? ?? 00 00 33 CC ", 1, 1, True], #Can be found in GameUpdate above the loc with "Game Ended.  Closing after delay..." and 3 renderer references
	
	["Version", "68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 ?? 8D 4C 24 ?? E8 ?? ?? ?? ?? 5E ", 1, 0, True],	 #Function referencing it can be found with "Build Version: %s ChangeList: %u\n", it is the function in the loc with "Build Version: %s ChangeList: %u\n" that has eax pushed on as an arg
	
	["NetClient", "8B ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 85 C0 ", 1, 1, True], #Can be found with "Build Version: %s ChangeList: %u\n" it is the dword in the loc directly above the loc in which "Build Version: %s ChangeList: %u\n" is used
	
	["TexturePack", "C7 ?? ?? ?? ?? ?? ?? ?? 00 00 8D 04 ?? C7 ?? ?? ?? ?? ?? ?? 50 ", 1, 0, True], #Can be found with "%.4f    %.4f    %.4f\n" and is the dword used in this sub
	
	["GameTime", "F3 0F ?? ?? ?? ?? ?? ?? 8B 48 08 E8 ?? ?? ?? ?? 51 ", 1, 0, True], #Should be found via the caller of the subroutine that uses this. 
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
	
	if Type == 0: print("#define " + Alias + " " + DecToHex(Addr))
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
	for Alias, Reference, Type, HasPrefix in Functions:
		if HasPrefix == True:
			if Type == 1: PrintWrapper(Alias, FindFuncPattern(Reference), 1)
			if Type == 2: PrintWrapper(Alias, FindFuncCall(Reference), 1)
			if Type == 3: PrintWrapper(Alias, FindFuncFirstReference(Reference), 1)
		else: 
			if Type == 1: PrintWrapper(Alias, FindFuncPattern(Reference), 0)
			if Type == 2: PrintWrapper(Alias, FindFuncCall(Reference), 0)
			if Type == 3: PrintWrapper(Alias, FindFuncFirstReference(Reference), 0)
	print("")
	
	print("++ Offsets")
	for Alias, Reference, Type, Operand, HasPrefix in Offsets:
		if HasPrefix == True:
			if Type == 1: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2)
			if Type == 2: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2)
		else:
			if Type == 1: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 0)
			if Type == 2: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 0)
	print("")
	
Initialize()