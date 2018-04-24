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


]

Offsets = [
		[
			"fnIssueOrder0",
			"E8 18 F9 BF FF ? ? ? ? ? ",
			1,
			0
		],		[
			"fnIssueOrder1",
			"E8 CE FB FF FF ? ? ? ? ? 5F ",
			1,
			0
		],		[
			"fnIssueOrder2",
			"E8 95 F6 BF FF ? ? ? ? ? ",
			1,
			0
		],		[
			"fnIssueOrder3",
			"E8 B3 E4 BF FF ? ? ? ? ? ",
			1,
			0
		],		[
			"fnIssueOrder4",
			"E8 36 FC FF FF ? ? ? ? ? 5F ",
			1,
			0
		],		[
			"fnIssueOrder5",
			"E8 7F FE FF FF ? ? ? ? ? 8B 84 24 C8 00 00 00 ? ? ? ? ? ? ? ",
			1,
			0
		],		[
			"fnIssueOrder6",
			"E8 E0 FB BF FF ? ? ? ? ? ",
			1,
			0
		],		[
			"fnIssueOrder7",
			"E8 DF EA BF FF ? ? ? ? ? ",
			1,
			0
		],		[
			"fnIssueOrder8",
			"E8 3D FD BF FF ? ? ? ? ? ",
			1,
			0
		],		[
			"fnIssueOrder9",
			"E8 04 FC FF FF ? ? ? ? ? 5F ",
			1,
			0
		]
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