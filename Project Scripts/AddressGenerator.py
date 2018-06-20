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

FILE_LOCATION = "C:\\Users\\gigia\\source\\repos\Renny\\Project Scripts\\"

Functions = []
Objects = []

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

	input = open(FILE_LOCATION + "Signatures.txt", "r")
	lines = input.readlines()
	position = 1
	for x in lines:
		if x.find("\", 1, True]") != -1 or x.find("\", 2, True]") != -1 or x.find("\", 1, False]") != -1 or x.find("\", 2, False]") != -1:
			x = x.replace("\"", "")
			index = x.find("[\"") + 1
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
			index = x.find("[\"") + 1
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

			Objects.append(object)
			position = position + 1
			
	input.close()

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
		print("fn" + Alias + " -> Error")
		return
	
	if Type == 0: print("#define " + Alias + " " + DecToHex(Addr))
	if Type == 1: print("#define " + functionPrefix + Alias + " " + DecToHex(Addr))
	if Type == 2: print("#define " + offsetPrefix + Alias + " " + DecToHex(Addr))
		
	if Rename == 1:
		if Type == 0: MakeName(Addr, str(Alias))
		if Type == 1: MakeName(Addr, str(functionPrefix + Alias))
		if Type == 2: MakeName(Addr, str(offsetPrefix + Alias))
		
	return
	
# Main
def GenerateAddresses():
	SignatureSearch()
	global Rename
	Rename = idc.AskYN(0, "Automaticly Update Names? (sub_549570 => PrintChat)")
	if Rename == -1:
		print("Exiting...")
		return
		
	print("")
	print("++ Offsets (%s)" % datetime.datetime.now())
	print("Why do they keep breaking...")
	print("")
	
	print("++ Functions")
	for x in Functions:
		if x.HasPrefix == True:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindFuncPattern(x.Reference), 1)
			if int(x.Type) == 2: PrintWrapper(x.Alias, FindFuncCall(x.Reference), 1)
			if int(x.Type) == 3: PrintWrapper(x.Alias, FindFuncFirstReference(x.Reference), 1)
		else:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindFuncPattern(x.Reference), 0)
			if int(x.Type) == 2: PrintWrapper(x.Alias, FindFuncCall(x.Reference), 0)
			if int(x.Type) == 3: PrintWrapper(x.Alias, FindFuncFirstReference(x.Reference), 0)
	print("")
	
	print("++ Objects")
	for x in Objects:
		if x.HasPrefix == True:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindOffsetPattern(x.Reference, int(x.Operand)), 2)
		else:
			if int(x.Type) == 1: PrintWrapper(x.Alias, FindOffsetPattern(x.Reference, int(x.Operand)), 0)
	print("")
	
GenerateAddresses()
	