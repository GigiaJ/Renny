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
		["OnLoadHero", "81 EC 84 00 00 00 A1 C0 53 56 01 33 C4 89 84 24 80 00 00 00 57 8B", 1],
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
		print(Alias + " -> Error")
		return
		
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
	for Alias, Reference, Type in Functions:
		if Type == 1: PrintWrapper(Alias, FindFuncPattern(Reference), 1, i)
		if Type == 2: PrintWrapper(Alias, FindFuncCall(Reference), 1, i)
		if Type == 3: PrintWrapper(Alias, FindFuncFirstReference(Reference), 1, i)
		i = i + 1
	print("")
	
	print("++ Offsets")
	i = 1
	for Alias, Reference, Type, Operand in Offsets:
		if Type == 1: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2, i)
		if Type == 2: PrintWrapper(Alias, FindOffsetPattern(Reference, Operand), 2, i)
		i = i + 1
	print("")
	
Initialize()