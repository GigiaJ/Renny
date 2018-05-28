from idc import *
from idautils import *
from Tkinter import Tk
import idaapi
import random
import datetime
 
UA_MAXOP = 11
MAX_XREFS = 5
FILE_LOCATION = "C:\\Users\\gigia\\source\\repos\Renny\\Project Scripts\\"


def replaceBetween(s, newstring, index1, index2, nofail=False):
	# raise an error if index is outside of the string
	if not nofail and index1 not in xrange(len(s)):
		raise ValueError("index outside given string")
		return
	if not nofail and index2 not in xrange(len(s)):
		raise ValueError("index outside given string")
		return
	if index1 < 0:
		raise ValueError("index outside given string")
		return
	if index2 > len(s):
		raise ValueError("index outside given string")
		return
	if index1 == 0:
		return newstring + s[index2:]
	if index2 == len(s):
		return s[:index1] + newstring
	
	# insert the new string between "slices" of the original
	return s[:index1] + newstring + s[index2:]

def getBetween(s, index1, index2, nofail=False):
	# raise an error if index is outside of the string
	if not nofail and index1 not in xrange(len(s)):
		raise ValueError("index outside given string")
		return
	if not nofail and index2 not in xrange(len(s)):
		raise ValueError("index outside given string")
		return
	if index1 < 0:
		raise ValueError("index outside given string")
		return
	if index2 > len(s):
		raise ValueError("index outside given string")
		return
	if index1 == 0:
		return s[:index2]
	if index2 == len(s):
		return s[index1:] 
	# insert the new string between "slices" of the original
	return s[index1:index2]
	
def insertAt(s, newstring, index, nofail=False):	
	# raise an error if index is outside of the string
	if not nofail and index not in xrange(len(s)):
		raise ValueError("index outside given string")
		return

	if index < 0:
		raise ValueError("index outside given string")
		return
	if index == 0:
		return newstring + s[index:]
		
	# insert the new string between "slices" of the original
	return s[:index] + newstring + s[index + 1:]
	
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

def PrintWrapper(Alias, Addr, Type, i): # Type: 1 => Function, 2 => Offset
	if Addr == BADADDR or Addr == 0 or Addr == 0x00:
		print(Alias + " -> Error")
		return
	
	if Type == 0: print("#define " + Alias + " " + DecToHex(Addr) + "\t #" + "{}".format(i))
	if Type == 1: print("#define " + functionPrefix + Alias + " " + DecToHex(Addr) + "\t #" + "{}".format(i))
	if Type == 2: print("#define " + offsetPrefix + Alias + " " + DecToHex(Addr) + "\t #" + "{}".format(i))
		
	return	
	
def SignatureSearch():
	class Function:	

		def __init__(self):
			self.Alias = ""
			self.Reference = ""
			self.Type = 0
			self.HasPrefix = False
			self.Position = 0
		
		def setAlias(self, Alias):
			self.Alias = Alias
		def setReference(self, Reference):
			self.Reference = Reference
		def setType(self, Type):
			self.Type = Type
		def setHasPrefix(self, HasPrefix):
			self.HasPrefix = HasPrefix
		def setPosition(self, Position):
			self.Position = Position
				
	class Offset:	
		def __init__(self):
			self.Alias = ""
			self.Reference = ""
			self.Type = 0
			self.Operand = 0
			self.HasPrefix = False
			self.Position = 0
		
		def setAlias(self, Alias):
			self.Alias = Alias
		def setReference(self, Reference):
			self.Reference = Reference
		def setType(self, Type):
			self.Type = Type
		def setOperand(self, Operand):
			self.Operand = Operand
		def setHasPrefix(self, HasPrefix):
			self.HasPrefix = HasPrefix
		def setPosition(self, Position):
			self.Position = Position

	Functions = []
	Offsets = []
	input = open(FILE_LOCATION + "SigMakeCheckSigs.txt", "r")
	lines = input.readlines()
	position = 1
	for x in lines:
		if x.find("\", 1, True]") != -1 or x.find("\", 2, True]") != -1 or x.find("\", 1, False]") != -1 or x.find("\", 2, False]") != -1:
			x = x.replace("\"", "")
			index = x.find("[\"") + 2
			object = Function()
			count = 0
			while count != x.count(","):
				index = index + 2
				temp = x[index:]
				newIndex = temp.find(",")
				tempIndex = index + newIndex
				
				if count == 0:
					object.setPosition(position)
					object.setAlias(x[index:tempIndex])
					
				if count == 1:
					object.setReference(x[index:tempIndex])
					
				if count == 2:
					object.setType(x[index:tempIndex])
					
				if count == 3:
					hasPrefix = x[index:tempIndex - 1]
					if hasPrefix == "False":
						object.setHasPrefix(False)
					if hasPrefix == "True":
						object.setHasPrefix(True)
				
				
				index = tempIndex
				count = count + 1	

			Functions.append(object)
			position = position + 1
		if x.find(", 1, 0, True]") != -1 or x.find(", 1, 1, True]") != -1 or x.find(", 1, 0, False]") != -1 or x.find(", 1, 1, False]") != -1:
			x = x.replace("\"", "")
			index = x.find("[\"") + 2
			object = Offset()
			count = 0
			while count != x.count(","):
				index = index + 2
				temp = x[index:]
				newIndex = temp.find(",")
				tempIndex = index + newIndex
				
				if count == 0:
					object.setPosition(position)
					object.setAlias(x[index:tempIndex])
					
				if count == 1:
					object.setReference(x[index:tempIndex])
					
				if count == 2:
					object.setType(x[index:tempIndex])
				
				if count == 3:
					object.setOperand(x[index:tempIndex])
					
				if count == 4:
					hasPrefix = x[index:tempIndex - 1]
					if hasPrefix == "False":
						object.setHasPrefix(False)
					if hasPrefix == "True":
						object.setHasPrefix(True)
						
				index = tempIndex
				count = count + 1	

			Offsets.append(object)
			position = position + 1
			
	input.close()
	print("++ Functions")
	for x in Functions:
		if x.HasPrefix == True:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindFuncPattern(x.Reference), 1, x.Position)
			if int(x.Type) == 2: PrintWrapper(x.Alias, FindFuncCall(x.Reference), 1, x.Position)
			if int(x.Type) == 3: PrintWrapper(x.Alias, FindFuncFirstReference(x.Reference), 1, x.Position)
		else:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindFuncPattern(x.Reference), 0, x.Position)
			if int(x.Type) == 2: PrintWrapper(x.Alias, FindFuncCall(x.Reference), 0, x.Position)
			if int(x.Type) == 3: PrintWrapper(x.Alias, FindFuncFirstReference(x.Reference), 0, x.Position)
	print("")
	
	print("++ Offsets")
	for x in Offsets:
		if x.HasPrefix == True:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindOffsetPattern(x.Reference, int(x.Operand)), 2, x.Position)
			#if x.Type == "2": PrintWrapper(x.Alias, FindOffsetPattern(x.Reference, x.Operand), 2, i)
		else:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindOffsetPattern(x.Reference, int(x.Operand)), 0, x.Position)
			#if x.Type == "2": PrintWrapper(x.Alias, FindOffsetPattern(x.Reference, x.Operand), 0, i)
	print("")

def add_to_clipboard(text):
	r = Tk()
	r.withdraw()
	r.clipboard_clear()
	r.clipboard_append(text)
	r.destroy()
 
def CorrectBytes(curSig, opcode, numberOfOpCodes, checkForAddress):
	index = 0
	counter = 0
	index = curSig.find(opcode + " ")
	while counter != curSig.count(opcode + " "):
		i = 0
		xCount = 0
		while i != numberOfOpCodes:
			instanceIndex = index
			if checkForAddress == True:
				lastTwoBytes = ""
				if index + (numberOfOpCodes * 3) - 1 <= len(curSig):
					lastTwoBytes = getBetween(curSig, index + (numberOfOpCodes * 3) - 3, index + (numberOfOpCodes * 3) - 1)
					if instanceIndex - 1 < len(curSig):
						blankCheck = 1
						find = ""
						while blankCheck - 1 != numberOfOpCodes:
							find = getBetween(curSig, index + (blankCheck * 3) - 3, index + (blankCheck * 3) - 1)
							if find == "??":
								break
							blankCheck = blankCheck + 1
						if find == "??":
							break
						if lastTwoBytes == "01" or lastTwoBytes == "02" or lastTwoBytes == "00" or lastTwoBytes == "03":
							xCount = xCount + 1
						else:
							break
					else:
						break
				else:
					return curSig
			else:
				if index + (numberOfOpCodes * 3) - 1 <= len(curSig):
					if instanceIndex < len(curSig):
						xCount = xCount + 1
					else: 
						break
				else:
					return curSig
			i = i + 1
			instanceIndex = index + (3 * i)
					
		replaceX = ""
		z = 0
		while z != xCount and xCount != 0:
			if z == 0:
				replaceX += opcode 
			if z > 0 and z != xCount:
				replaceX += " XX"
			if z == xCount and z != 0:
				replaceX += " XX"
			z = z + 1
			
		if xCount != 0:
			if xCount != numberOfOpCodes:
				curSig = replaceBetween(curSig, replaceX, index, index + (xCount * 3))
			else:
				curSig = replaceBetween(curSig, replaceX, index, index + (xCount * 3) - 1)
				
		index = index + (numberOfOpCodes * 3)
		temp = curSig[index:]
		newindex = temp.find(opcode + " ")
		index = index + newindex
		counter	= counter + 1
	return curSig
 
def CorrectDefinedOffsets(curSig, opcode, indexToFix1, indexToFix2):
	index = curSig.find(opcode)
	counter = 0
	while counter < curSig.count(opcode):
		if indexToFix1 != -1:
			curSig = replaceBetween(curSig, "XX", index + (indexToFix1 * 3) - 3, index + (indexToFix1* 3) - 1)	
		if indexToFix2 != -1:
			curSig = replaceBetween(curSig, "XX", index + (indexToFix2 * 3) - 3, index + (indexToFix2 * 3) - 1)	
		
		index = index + (indexToFix2 * 3)
		temp = curSig[index:]
		newindex = temp.find(opcode + " ")
		index = index + newindex
		counter = counter + 1
	return curSig
 
 
def ApplyCorrections(curSig):
	#########################################################	
	curSig = CorrectBytes(curSig, "0F", 7, True)
	if curSig.find("0F") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("0F 2E") != -1:
		curSig = CorrectDefinedOffsets(curSig, "0F 2E", -1, 3)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("0F 28") != -1:
		curSig = CorrectDefinedOffsets(curSig, "0F 28", -1, 3)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("0F 43") != -1:
		curSig = CorrectDefinedOffsets(curSig, "0F 43", -1, 5)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("0F 85") != -1:
		curSig = CorrectBytes(curSig, "0F", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("0F B6") != -1:
		curSig = CorrectDefinedOffsets(curSig, "0F B6", -1, 4)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	#########################################################	
	if curSig.find("6A") != -1:
		curSig = CorrectDefinedOffsets(curSig, "6A", -1, 2)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	#########################################################	
	curSig = CorrectBytes(curSig, "68", 5, True)
	if curSig.find("68") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	#########################################################
	if curSig.find("80 7C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "80 7C", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
			# cmp     [esp+0Ch+var_1], 0
	#########################################################
	if curSig.find("81 C1") != -1:
		curSig = CorrectDefinedOffsets(curSig, "81 C4", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("81 C4") != -1:
		curSig = CorrectDefinedOffsets(curSig, "81 C4", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("81 EC") != -1:
		curSig = CorrectDefinedOffsets(curSig, "81 EC", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	curSig = CorrectBytes(curSig, "81", 10, True)
	if curSig.find("81") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	#########################################################
	if curSig.find("83 78") != -1:
		curSig = CorrectDefinedOffsets(curSig, "83 78", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("83 7C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "83 7C", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("83 BD") != -1:
		curSig = CorrectDefinedOffsets(curSig, "83 BD", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("83 BE") != -1:
		curSig = CorrectDefinedOffsets(curSig, "83 BE", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("83 C4") != -1:
		curSig = CorrectDefinedOffsets(curSig, "83 C4", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")		
	if curSig.find("83 EC") != -1:
		curSig = CorrectDefinedOffsets(curSig, "83 EC", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	curSig = CorrectBytes(curSig, "83", 7, True)
	if curSig.find("83") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	#########################################################	
	if curSig.find("89 44") != -1:
		curSig = CorrectDefinedOffsets(curSig, "89 44", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("89 4C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "89 4C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("89 5C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "89 5C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("89 6C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "89 6C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("89 74") != -1:
		curSig = CorrectDefinedOffsets(curSig, "89 74", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("89 7C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "89 7C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("89 84") != -1:
		curSig = CorrectDefinedOffsets(curSig, "89 84", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	#########################################################
	if curSig.find("8A 43") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8A 43", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	#########################################################		
	if curSig.find("8B 40") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 40", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 41") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 41", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 44") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 44", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 45") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 45", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
			#mov     eax, [ebp+40h]
	if curSig.find("8B 46") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 46", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 48") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 48", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 4B") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 4B", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 4C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 4C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 4F") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 4F", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 51") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 51", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")				
	if curSig.find("8B 5C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 5C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B 6C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 6C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8B 6E") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 6E", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")		
	if curSig.find("8B 7C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 7C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")			
	if curSig.find("8B 74") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 74", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B 81") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 81", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B 83") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 83", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")		
	if curSig.find("8B 87") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 87", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B 8C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 8C", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B 8E") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 8E", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B 9C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B 9C", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B AC") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B AC", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B BC") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8B BC", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")				
	#########################################################		
	if curSig.find("8D 04") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8D 04", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8D 14") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8D 14", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
			#lea     edx, [esp+18h+var_18]
	if curSig.find("8D 44") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8D 44", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")
	if curSig.find("8D 4C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8D 4C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")		
	if curSig.find("8D 6C") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8D 6C", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8D 74") != -1:
		curSig = CorrectDefinedOffsets(curSig, "8D 74", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	#########################################################			
	if curSig.find("89") != -1:
		curSig = CorrectBytes(curSig, "89", 6, True)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8B") != -1:
		curSig = CorrectBytes(curSig, "8B", 6, True)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("8D") != -1:
		curSig = CorrectBytes(curSig, "8D", 6, True)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")		
	#########################################################
	curSig = CorrectBytes(curSig, "A1", 5, True)
	if curSig.find("A1") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")					
	#########################################################
	curSig = CorrectBytes(curSig, "A3", 5, True)
	if curSig.find("A3") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	#########################################################
	if curSig.find("B9") != -1:
		curSig = CorrectDefinedOffsets(curSig, "B9", 2, 3)
		curSig = CorrectDefinedOffsets(curSig, "B9", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	#########################################################	
	if curSig.find("C6 46") != -1:
		curSig = CorrectDefinedOffsets(curSig, "C6 46", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("C6 46") != -1:
		curSig = CorrectDefinedOffsets(curSig, "C6 46", 4, 5)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")			
	#########################################################
	if curSig.find("C7 04 24") != -1:
		curSig = CorrectBytes(curSig, "C7", 7, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("C7 46") != -1:
		curSig = CorrectBytes(curSig, "C7", 7, True)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	curSig = CorrectBytes(curSig, "C7", 8, True)
	if curSig.find("C7") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	#########################################################
	if curSig.find("D9 54") != -1:
		curSig = CorrectDefinedOffsets(curSig, "D9 54", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")		
	#########################################################	
	curSig = CorrectBytes(curSig, "E8", 5, False)
	if curSig.find("E8") != -1:
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	#########################################################	
	if curSig.find("F3 0F 10 0D") != -1:
		curSig = CorrectBytes(curSig, "F3", 8, True)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("F3 0F 10 44") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("F3 0F 10 4C") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("F3 0F 10 54") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")	
	if curSig.find("F3 0F 10 5C") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 10 6C") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 10 74") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 11 44") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 11 46") != -1:
		curSig = CorrectBytes(curSig, "F3", 5, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 11 4C") != -1:
		curSig = CorrectBytes(curSig, "F3", 6, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 11 4E") != -1:
		curSig = CorrectBytes(curSig, "F3", 5, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 5E 51") != -1:
		curSig = CorrectBytes(curSig, "F3", 5, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	if curSig.find("F3 0F 11 5E") != -1:
		curSig = CorrectBytes(curSig, "F3", 5, False)
		if (curSig.find("XX") != -1):
			curSig = curSig.replace("XX", "??")
	
	#########################################################	
	if curSig.find("FF 50") != -1:
		curSig = CorrectDefinedOffsets(curSig, "FF 50", -1, 3)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")		
	if curSig.find("FF B4") != -1:
		curSig = CorrectDefinedOffsets(curSig, "FF B4", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")			
	if curSig.find("FF 74") != -1:
		curSig = CorrectDefinedOffsets(curSig, "FF 74", -1, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	if curSig.find("FF 90") != -1:
		curSig = CorrectDefinedOffsets(curSig, "FF 90", 3, 4)
		if curSig.find("XX") != -1:
			curSig = curSig.replace("XX", "??")	
	#########################################################
	
	
	
	return curSig
	
def AddBytesToSig(curSig, currentIns, size):
	for i in xrange(size):	
		curSig = "%s%0.2X " % (curSig, idc.Byte(currentIns+i))
	curSig = ApplyCorrections(curSig)
	return curSig
 
 
def AddWhiteSpacesToSig(curSig, size):
	for i in xrange(size):
		curSig = "%s?? " % curSig
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
	
	if size < 11:
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
	
	curSig = ApplyCorrections(curSig)
	
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
	OffsetPattern = []
	HasPrefix = []
	hasPrefix = "False"
	
	if patternType == 1:
		if name.find("fn") == 0:
			name = name.replace("fn", "", 1)
			hasPrefix = "True"
		if name.find("o") == 0:
			name = name.replace("o", "", 1)	
			hasPrefix = "True"
		HasPrefix.append(hasPrefix)
		currentpattern = create_pattern(ea)	
		Addr.append(FindFuncPattern(currentpattern))
		OffsetPattern.append(currentpattern)
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
		if name.find("fn") == 0:
			name = name.replace("fn", "", 1)
			hasPrefix = "True"
		if name.find("o") == 0:
			name = name.replace("o", "", 1)	
			hasPrefix = "True"
		HasPrefix.append(hasPrefix)
		currentpattern = create_pattern(xref.frm)
		Addr.append(FindFuncCall(currentpattern))
		OffsetPattern.append(currentpattern)
		foundPattern.append(["\"{}\"".format(name), "\"{}\"".format(currentpattern), 2])
		x = x + 1
	formattedPattern = ""
	
	z = 0
	for i, pattern in enumerate(foundPattern):
		formattedPattern += "\t\t["
		for j, v in enumerate(pattern)  :
			if Addr[z] == 0x01 and len("{}".format(v)) == 1:
				formattedPattern += "1, 1"
			else:
				formattedPattern += "{}".format(v)
			if j != len(pattern) - 1:
				formattedPattern += ", "
		formattedPattern += ", " + HasPrefix[i]
		formattedPattern += "],"
		
		if Addr[z] == 0x01:
			Addr[z] = FindFuncPattern(OffsetPattern[z])
			if Addr[z] == BADADDR or Addr[z] == 0 or Addr[z] == 0x00:
				formattedPattern += "\t #FAIL\t" + DecToHex(Addr[z])
			else:
				formattedPattern += "\t #SUCCESS\t" + DecToHex(Addr[z])
			Addr[z] = FindOffsetPattern(OffsetPattern[z], 1)
			formattedPattern += "\t" +  DecToHex(Addr[z])
		else:
			if Addr[z] == BADADDR or Addr[z] == 0 or Addr[z] == 0x00:
				Addr[z] = FindFuncPattern(OffsetPattern[z])
				formattedPattern += "\t #FAIL\t" + DecToHex(Addr[z])
			else:
				formattedPattern += "\t #SUCCESS\t" + DecToHex(Addr[z])
		
		formattedPattern += "\n"
		z = z + 1
		
	output = open(FILE_LOCATION + "SigMakeCheckSigs.txt", "w+")
	output.write(formattedPattern)
	output.close()
	
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
		
try:
	hotkey_scs
	if idaapi.del_hotkey(hotkey_scs):
		print("SearchSignature hotkey unregistered!")
		del hotkey_scs
	else:
		print("Failed to delete SearchSignature hotkey!")
except:
	hotkey_scs = idaapi.add_hotkey("Ctrl+Shift+Alt+D", SignatureSearch)
	if hotkey_scs is None:
		print("Failed to register SearchSignature hotkey!")
		del hotkey_scs
	else:
		print("SearchSignature hotkey registered to Ctrl+Shift+Alt+D!")


