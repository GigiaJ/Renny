from idc import *
from idautils import *
from Tkinter import Tk
import idaapi
import random
import datetime
 
UA_MAXOP   = 6
MAX_XREFS = 50

Functions = []

def replacer(s, newstring, index, amount, nofail=False):
    # raise an error if index is outside of the string
    if not nofail and index not in xrange(len(s)):
        raise ValueError("index outside given string")

    # if not erroring, but the index is still not in the correct range..
    if index < 0:  # add it to the beginning
        return newstring + s
    if index > len(s):  # add it to the end
        return s + newstring

    # insert the new string between "slices" of the original
    return s[:index] + newstring + s[index + 1 + amount:]

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
def DecToHex(addr):
	return "0x%0.2X" % addr


def add_to_clipboard(text):
	r = Tk()
	r.withdraw()
	r.clipboard_clear()
	r.clipboard_append(text)
	r.destroy()
 
def AddBytesToSig(curSig, currentIns, size):
	for i in xrange(size):	
		curSig = "%s%0.2X " % (curSig, idc.Byte(currentIns+i))
	while curSig.count("E8 ") != curSig.count("E8 ?"):
		curSig = replacer(curSig, "E8 ?", curSig.find("E8 "), 14)
	return curSig
 
def AddWhiteSpacesToSig(curSig, size):
	for i in xrange(size):
		curSig = "%s? " % curSig
	return curSig
 
def GetCurrentOpcodeSize(ea):
	inslen = DecodeInstruction(ea)
	for i in range(0, UA_MAXOP):
		if idaapi.cmd.Operands[i].type == o_void:
			return 0
		if idaapi.cmd.Operands[i].offb != 0:
			return idaapi.cmd.Operands[i].offb
	return 0
 
def MatchOperands(ea):
	if idaapi.get_first_dref_from(ea) != BADADDR:
		return False
	if idaapi.get_first_cref_from(ea) != BADADDR:
		return False
	return True
 
 
def AddInsToSig(curSig, ea):
	uiSize = GetCurrentOpcodeSize(ea)
	size = ItemSize(ea)
	
	# If the instruction doesn't have any useful operand info, then just add the raw bytes
	if size < 5:
		curSig = AddBytesToSig(curSig, ea, size)
		return (curSig,size)
 
 
	if uiSize == 0:
		curSig = AddBytesToSig(curSig, ea, size)
	else:
		curSig = AddBytesToSig(curSig, ea, uiSize)
 
	if MatchOperands(ea):
		curSig = AddBytesToSig(curSig, ea + uiSize, size - uiSize)
	else:
		curSig = AddWhiteSpacesToSig(curSig, size - uiSize)
 
	#Fixes the calls so they are ignored since their data is unstable for signatures
 	if curSig.find("??") != -1:
		curSig = curSig.replace("E8 ?? ", "E8 ? ")
	
	if curSig.find("E8 ? ? ? ? ?") != -1:
		curSig = curSig.replace("E8 ? ? ? ? ? ", "E8 ? ? ? ? ")
	############
		
	return (curSig, size)
 
def IsUniquePattern(pattern):
	if pattern == "":
		return False
	ea = FindBinary(0, SEARCH_DOWN, pattern)
	if ea == BADADDR:
		return True
	else:
		# Search again, starting 1 byte further so we can keep going until we get a unique pattern.
		if FindBinary(ea+1, SEARCH_DOWN, pattern) == BADADDR:
			return True
		else:
			return False
 
def CreatePattern():
	ea = ScreenEA()
	patternType = 1

	foundPattern = []

	# Am I an Xref?
	xrefsFrom = list(XrefsFrom(ea))

	if len(xrefsFrom) == 2:
		ea = xrefsFrom[1].to

	# Is function or offset?
	functionName = GetFunctionName(ea)
	if functionName:
		name = functionName
		patternType = 1
	else:
		name = NameEx(BADADDR, ea)
		patternType = 2
	
	Addr = []
		
	if patternType == 1:
		if name.find("fn") != -1:
			name = name.replace("fn", "")
		if name.find("o" + name.replace("o", "", 1)) != -1:
			name = name.replace("o", "")	
		currentpattern = create_pattern(ea)
		Addr.append(FindFuncPattern(currentpattern))
		foundPattern.append(["\"" + name + "\"", "\"{}\"".format(currentpattern), patternType])
	xrefs = list(XrefsTo(ea, 0))
	xrefs = list(filter(lambda xref: SegName(xref.frm) != ".rdata", xrefs))
	if MAX_XREFS != -1:
		xrefs = random.sample(xrefs, min(len(xrefs), MAX_XREFS))
	x = 1
	for xref in xrefs:
		i = 0
	   
		opndValue = GetOperandValue(xref.frm, i)
		while opndValue != -1 and opndValue != ea:
			i += 1
			opndValue = GetOperandValue(xref.frm, i)
		if name.find("fn") != -1:
			name = name.replace("fn", "")
		if name.find("o" + name.replace("o", "", 1)) != -1:
			name = name.replace("o", "")	
		currentpattern = create_pattern(xref.frm)
		Addr.append(FindFuncCall(currentpattern))
		foundPattern.append(["\"{}\"".format(name), "\"{}\"".format(currentpattern), 2])
		x = x + 1
	formattedPattern = ""
	
	z = 0
	for i, pattern in enumerate(foundPattern):
		formattedPattern += "\t\t["
		for j, v in enumerate(pattern)  :
			formattedPattern += "{}".format(v)
			if j != len(pattern) - 1:
				formattedPattern += ", "
		formattedPattern += "],"
		if Addr[z] == BADADDR or Addr[z] == 0 or Addr[z] == 0x00:
			formattedPattern += "\t #FAIL\t" + DecToHex(Addr[z])
		else:
			formattedPattern += "\t #SUCCESS\t" + DecToHex(Addr[z])
		formattedPattern += "\n"
		z = z + 1
	value = "# {}".format(name)
	value += "\nPATTERN_DESCRIPTIONS.append({})".format("[\n\t\"{}\",\n\t{},\n\t[\n{}\n\t]\n]".format(name, patternType, formattedPattern))

	add_to_clipboard(value)
	print(value)

def create_pattern(ea):
	curSig, len = AddInsToSig("", ea)
	ea = ea + len
	while not IsUniquePattern(curSig):
		curSig, len = AddInsToSig(curSig, ea)
		ea = ea + len
	return curSig
 
def hotkey_pressed():
	CreatePattern()

try:
	hotkey_ctx
	if idaapi.del_hotkey(hotkey_ctx):
		print("CreateSignature hotkey unregistered!")
		del hotkey_ctx
	else:
		print("Failed to delete CreateSignature hotkey!")
except:
	hotkey_ctx = idaapi.add_hotkey("Ctrl+Shift+Alt+S", hotkey_pressed)
	if hotkey_ctx is None:
		print("Failed to register CreateSignature hotkey!")
		del hotkey_ctx
	else:
		print("CreateSignature hotkey registered to Ctrl+Shift+Alt+S!")


