# Author: Uhrwerk (Inspired by eb's Offsets.py)
# Revised by: G
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
		["j_CReplInfo32__AddVar", "6A ?? FF 74 24 ?? FF 74 24 ?? FF 74 24 ?? E8 ?? ?? ?? ?? C2 0C 00 ", 1, False],	 #SUCCESS	0x1F3C80
		["j_CReplInfo32__AddVar", "E8 ?? ?? ?? ?? 89 46 04 8B 44 24 ?? 89 46 08 8B 44 24 ?? 89 46 0C 5E C2 14 00 CC CC CC CC CC ", 2, False],	 #SUCCESS	0x1F3C80
		["j_CReplInfo32__AddVar", "E8 ?? ?? ?? ?? 89 47 04 B9 ?? ?? ?? ?? C7 47 08 08 00 00 00 ", 2, False],	 #SUCCESS	0x1F3C80
		["j_CReplInfo32__AddVar", "E8 ?? ?? ?? ?? 89 46 04 8B CD 89 5E 08 89 7E 0C 8B 74 24 ?? 68 ?? ?? ?? ?? 81 C6 90 01 00 00 56 FF 74 24 ?? E8 ?? ?? ?? ?? 89 46 04 8B CD 89 5E 08 89 7E 0C 8B 74 24 ?? 68 ?? ?? ?? ?? 81 C6 B0 01 00 00 56 FF 74 24 ?? E8 ?? ?? ?? ?? 89 46 04 ", 2, False],	 #SUCCESS	0x1F3C80
		["j_CReplInfo32__AddVar", "E8 ?? ?? ?? ?? 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 89 47 04 ", 2, False],	 #SUCCESS	0x1F3C80
		["j_CReplInfo32__AddVar", "E8 ?? ?? ?? ?? 89 46 04 8B CD 89 5E 08 89 7E 0C 8B 74 24 ?? 68 ?? ?? ?? ?? 81 C6 C0 01 00 00 56 FF 74 24 ?? E8 ?? ?? ?? ?? 89 46 04 8B CD 89 5E 08 89 7E 0C 8B 74 24 ?? 68 ?? ?? ?? ?? 81 C6 20 03 00 00 ", 2, False],	 #SUCCESS	0x1F3C80
		
]

Offsets = [
		
		
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
	
def PrintWrapper(Alias, Addr, Type, i): # Type: 1 => Function, 2 => Offset
	if Addr == BADADDR or Addr == 0 or Addr == 0x00:
		print("fn" + Alias + " -> Error")
		return
	
	if Type == 0: print("#define " + Alias + " " + DecToHex(Addr) + "\t #" + "{}".format(i))
	if Type == 1: print("#define " + functionPrefix + Alias + " " + DecToHex(Addr) + "\t #" + "{}".format(i))
	if Type == 2: print("#define " + offsetPrefix + Alias + " " + DecToHex(Addr) + "\t #" + "{}".format(i))
	
	if Rename == 1:
		if Type == 1: MakeName(Addr, str(functionPrefix + Alias))
		if Type == 2: MakeName(Addr, str(offsetPrefix + Alias))
		
	return
	
# Main
def Initialize():
	print("++ Functions")
	i = 1
	for Alias, Reference, Type, HasPrefix in Functions:
		if HasPrefix == True:
			if Type == 1: PrintWrapper(Alias, FindFuncPattern(Reference), 1, i)
			if Type == 2: PrintWrapper(Alias, FindFuncCall(Reference), 1, i)
			if Type == 3: PrintWrapper(Alias, FindFuncFirstReference(Reference), 1, i)
		else:
			if Type == 1: PrintWrapper(Alias, FindFuncPattern(Reference), 0, i)
			if Type == 2: PrintWrapper(Alias, FindFuncCall(Reference), 0, i)
			if Type == 3: PrintWrapper(Alias, FindFuncFirstReference(Reference), 0, i)
		i = i + 1
	print("")
	
	print("++ Offsets")
	i = 1
	for Alias, Reference, Type, Operand, HasPrefix in Offsets:
		if HasPrefix == True:
			if Type == 1: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2, i)
			if Type == 2: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2, i)
		else:
			if Type == 1: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 0, i)
			if Type == 2: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 0, i)
		i = i + 1
	print("")
	
Initialize()