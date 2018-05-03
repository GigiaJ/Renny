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
    	["W2S", "E8 ? ? ? ? 8B 46 34 83 C4 08" , 2],
    	["S2W", "81 EC ? ? ? ? A1 ? ? ? ? F3 0F 10 15 ? ? ? ?", 1],
    	
    	["W2M", "E8 ? ? ? ? 8B 5C 24 14 8A 4D 59", 2],# use tm + onloadhero
    	["M2W", "f3 0f 5c cb f3 0f 11 0b f3 0f 10 17", 1],
    	["TM", "E8 ? ? ? ? 8B C8 E8 ? ? ? ? EB 13", 2],# use "Finished Main Loop\n"
     
    	["LoadTexture", "TEXTURE: Failed to find texture", 3],
     
		["Logger","8D 44 24 14 50 FF 74 24 14 FF 74 24 14 ", 1],	
	 
    	["UpdateBuff", "E8 ? ? ? ? 80 7C 24 ? ? 74 1D ", 2],#use "ALE-DEFF93BD"
     
     
    	["InitEvent", "83 EC 4C A1 D8 12 5F 01 33 C4 89 44 24 48 53 55 56 57 8B F9 C7 47 10 00 00 00 00 8D 4F 34 C7 47", 1],#use "CreateParticleSystemManager\n";"Global/Cheats/cheats.bin" and track trough
    	["EventHandler", "83 EC 38 A1 ? ? ? ? 33 C4 89 44 24 34 53 8B D9 56 8B 74 24 48", 1],#use initevent
    	["DispatchEvent", "E8 ? ? ? ? 8B 0B 81 C1 ? ? ? ?", 2],#use "\\Code_X86_Public\\15682\\code\\Game\\LoL\\AI\\Object\\Client\\AIBaseClient.cpp"
    	["OnProcessPacket", "Received command to shut down.", 3],
    	
    	["OnLoadHero", "Received PKT_S2C_CreateHero_s, Name:%s,", 3],
    	["OnLoadChampion", "83 EC 08 E8 ? ? ? ? 68 ? ? ? ?", 1], # use OnLoadHero / "character"
    	
    	["OnTeleport", "53 55 56 57 8B 7C 24 14 8B E9 8B D7" , 1],
     
    	["SendChat", "56 6A FF FF 74 24 0C", 1],
    	["PrintChat", "E8 ? ? ? ? 8B 77 40 8B C6", 2],# use ChatClientPtr
    	["OpenChat", "game_console_chatcommand_allchat_1", 3],
     
    	["DisplayChat", "MaxChatBufferSize", 3],
    	["SetChatScale", "SetChatScaleX", 3],
     
    	["OnDisconnect", "game_messagebox_caption_disconnect", 3],
    	["OnAfk", "game_messagebox_text_afkwarningcaption", 3],
    	["SmartPing", "E8 ? ? ? ? 5E 5B 5F C2 10 00 84 DB", 2],
    	["GameUpdate", "Waiting for all players to connect", 3],
    	["ClientMain", "Invalid AttackDelayCastOffsetPercent!", 3],
     
     
    	["PlaySound", "AudioManager::PlaySoundEvent: Failed to play sound event %s.", 3],
    	
    	["HealthBarPos", "8B 81 ? ? ? ? 85 C0 74 12", 1],
    	
    	["GetAttackDelay", "57 8B 7C 24 08 8B 87 ? ? ? ? 8D 8F ? ? ? ?", 1],
    	["GetAttackCastDelay", "83 EC 0C 53 8B 5C 24 14 8B CB", 1],
    	["GetBasicAttack", "E8 ? ? ? ? 6A 41 56", 2],	
    	["GetBoundingRadius", "51 56 8B F1 8B 8E ? ? ? ? 85 C9 74 2A", 1],
    	
    	["AddRemoveBuff", "SpellToggleSlot", 3],	
    	["LevelUp", "ALE-BD06C313", 3],
    	["CreateObject", "E8 ? ? ? ? 8B 17 83 C4 1C", 2],#"GetClassID: class %d isn't present"
    	["AssignNetworkID", "GameObject Network ID is being reset for %s", 3],
    	["IdentifyObject", "E8 ? ? ? ? 8D 88 ? ? ? ? 85 C0", 2],
    	["ApplySkin", "ALE-382B05A8", 3],
    	["DeleteObject", "83 EC 10 53 55 8B 6C 24 1C 56 57 8B F9", 1],
    	["UseObject", "83 EC 44 A1 D8 12 5F 01 33 C4 89 44 24 40 53 55 8B 6C 24 50 8B D9 56 57 89 6C 24 18 E8 3F 65 FF", 1],#use pattern for jmp wrapper
    	
    	#NavMesh
    	["SetPath", "f3 0f 10 01 f3 0f 5c ?? 0f 54 c1 0f 2f d0", 1],#ALE-C92B9700
    	["CreatePath", "ALE-30FDAB23", 3],
    	["IsWallOfGrass", "Infinite loop detected", 3],
    	    	
    	["DoEmote", "A1 1C DD 5F 01 83 EC 0C 8B 48 08 E8 20 1F 0A 00 84 C0 74 08 32 C0 83 C4 0C C2 04 00 8B 0D E0 F6", 1],#"dance";"joke";"laugh";"taunt";"toggle";
    	["DoMasteryBadge", "81 EC ? ? ? ? A1 ? ? ? ? 33 C4 89 84 24 ? ? ? ? 53 8B 9C 24 ? ? ? ? 55 8B E9 8B 8C 24 ? ? ? ? ", 1],# use "ALE-A6219283"
     
    	["OnSurrenderVote", "8B 81 ? ? ? ? 8A 54 24 0C 53", 1],
    		
    	["LevelUpSpell", "ALE-89BAB541", 3],
    	["CastSpell", "ERROR: Client Tried to cast a spell from an invalid slot:", 3],
    	["UpdChargeableSpell", "E8 ? ? ? ? 8B 43 24 8B 40 34", 2],
    	["GetSpellState", "ALE-84F0B873", 3],
    	["ApplySpellCD", "ALE-42E20CB6", 3],
    	["OnProcessSpell", "83 EC 10 80 7C 24 ? ? 74 25", 1],#OnProcessSpellW
    	["OnProcessSpellW", "57 8B 7C 24 08 8B 17", 1],
		["IssueOrder","ALE-E1D3ADB6",3],
    	["StopCast", "83 EC 10 56 8B 74 24 24", 1],
		["IsSkillShotConeOrSingleTarget", "E8 ? ? ? ? 8A 4C 24 26", 2],
     
]

Offsets = [
    	["LocalPlayer", "8B ? ? ? ? ? 83 F8 01 8A 5C 24 10 0F 94 C7 85 C9 74 28", 1, 1],
    	["ObjManager", "B9 ? ? ? ? E8 ? ? ? ? 8B F8 85 FF 75 E3", 1, 1],	
    	["ChatClientPtr", "B9 ? ? ? ? 50 E8 ? ? ? ? 8B 0D ? ? ? ? 6A 03", 1, 1],	
    	["GameTime", "F3 0F 5C 0D ? ? ? ? 0F 2F C1", 1, 1],
    	["Renderer", "8B 0D ? ? ? ? 85 C9 74 14 8B 46 28", 1, 1],
    	["ZoomBase", "A3 ? ? ? ? 8D 4C 24 20", 1, 0],# "Globals/CameraConfig_CLASSIC"
    	["UnderMouseObj", "C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 04 FF B4 24 ? ? ? ?", 1, 0],
    	["NetClient", "C7 05 ? ? ? ? ? ? ? ? 85 C9 74 05", 1, 0],
    	["MissionInfo", "89 35 ? ? ? ? C7 06 ? ? ? ? C7 46 ? ? ? ? ? C7 46 ? ? ? ? ? C7 46 ? ? ? ? ?", 1, 0],##might be incorrect use TM to get correct
    	["GameState", "A1 ? ? ? ? 8B 70 08 E8 ? ? ? ? ", 1, 1],# "Demacia event failed."; "game.gameState"
    	["Version", "68 ? ? ? ? E8 ? ? ? ? 83 C4 20 8D 4C 24 04", 1, 0],# "Version %s (%s/%s) [%s] <%s>%s"
    	["MousePointer", "8B 35 ? ? ? ? FF 75 08", 1, 1],# use fnIssueOrder
    	#Textures
    	["TexturePack", "A1 ? ? ? ? 85 C0 74 13 50 E8 ? ? ? ? 83 C4 04 C7 05 ? ? ? ? ? ? ? ? 8D 04 24", 1, 1]
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