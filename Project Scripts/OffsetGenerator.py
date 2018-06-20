from idc import *
from idautils import *
from Tkinter import Tk
from operator import itemgetter
from collections import OrderedDict
import idaapi
import random

MAX_XREFS = 500

Offsets = {}

BaseOffsets = {}

def FindCallOffsetValue(address):
	trueOffset = None

	baseOffset = ""
	subOffset = ""
	leadAddy = ""
	secondReg = ""
	thirdReg = ""
	i = 0
	while i < 15:
		address = idc.prev_head(address, minea=0)
		currentInstruction = generate_disasm_line(address, 0)
		if i == 1:
			leadAddy = print_operand(address, 0)

		if currentInstruction.find("mov    " + leadAddy) != -1:
			secondReg = print_operand(address, 1)

		if currentInstruction.find("call") != -1:
			currentInstruction = currentInstruction.replace("call", "")
			currentInstruction = currentInstruction.replace("  ", "")
			nameOfAddress = get_name_ea_simple(currentInstruction)
			z = 0
			while z < 8:
				currentInstruction = generate_disasm_line(nameOfAddress, 0)
				
				if currentInstruction.find("lea    " + secondReg) != -1:
					temp = print_operand(nameOfAddress, 1)
					additionSignIndex = temp.find("+")
					thirdReg = temp[:additionSignIndex].replace("[", "")
					subOffset = temp[additionSignIndex + 1:].replace("h]", "")
					
				nameOfAddress = idc.next_head(nameOfAddress)
				z = z + 1
			
			if thirdReg != "":
				q = 0
				currentAddress = address
				while q < 8:
					currentInstruction = generate_disasm_line(currentAddress, 0)
					if currentInstruction.find("lea     " + thirdReg) != -1 or currentInstruction.find("lea    " + thirdReg) != -1:
						temp = print_operand(currentAddress, 1)
						additionSignIndex = temp.find("+") + 1
						baseOffset = temp[additionSignIndex:].replace("h]", "")
						break
					
					currentAddress = idc.prev_head(currentAddress, minea=0)
					q = q + 1
		i = i + 1
	try:
		trueOffset = int(baseOffset, 16) + int(subOffset, 16)
	except ValueError:
		pass
	return trueOffset
	
def FindBaseOffsetValue(address, subOffset):
	ea = get_name_ea_simple(get_func_name(address))
	
	xrefs = list(XrefsTo(ea, 0))
	xrefs = list(filter(lambda xref: SegName(xref.frm) != ".rdata", xrefs))
	if MAX_XREFS != -1:
		xrefs = random.sample(xrefs, min(len(xrefs), MAX_XREFS))
	
	trueOffset =  None
	baseOffset = ""
	leadAddy = ""

	if len(xrefs) < 4:
		for xref in xrefs:
			caller = xref.frm
			i = 0
			while i < 300:
				caller = idc.prev_addr(caller)
				currentInstruction = print_insn_mnem(caller) + " " + print_operand(caller, 0)
				if i == 1:
					leadAddy = print_operand(caller, 0)
				if currentInstruction.find("lea " + leadAddy) != -1:
					temp = print_operand(caller, 1)
					additionSignIndex = temp.find("+") + 1
					baseOffset = temp[additionSignIndex:].replace("h]", "")
					break	
				i = i + 1
		BaseOffsets[ea] = baseOffset
		try:
			trueOffset = int(baseOffset, 16) + int(subOffset, 16)
		except ValueError:
			pass
		
	return trueOffset

def CreateOffsets(address, currentAddress, leadAddy, i, checkPoint):
	offset = None
	nameOfOffset = ""
	lastInstruction = ""
	while i < 8:
		address = idc.prev_head(address, minea=0)
		currentInstruction = generate_disasm_line(address, 0)
		if lastInstruction == "align 10h":
			if currentInstruction == "retn    4":
				break
		lastInstruction = currentInstruction
					
		if currentInstruction.find("push    offset ") != -1:
			currentInstruction = currentInstruction.replace("push    offset ", "")
			endIndex = currentInstruction.find(";")
			currentInstruction = currentInstruction[:endIndex]
			addressOfName = get_name_ea_simple(currentInstruction)
			nameOfOffset = GetString(addressOfName, -1, 0)
		
		if i == checkPoint:
			if currentInstruction.find("push    edi") == -1 and currentInstruction.find("push    esi") == -1 and currentInstruction.find("push    ebp") == -1 and currentInstruction.find("push    ebx") == -1 and currentInstruction.find("push    esp") == -1:
				checkPoint = checkPoint + 1
			else:
				instructionBeforeLine = generate_disasm_line(idc.prev_head(address, minea=0), 0)
				if instructionBeforeLine.find("push    edi") == -1 and instructionBeforeLine.find("push    esi") == -1 and instructionBeforeLine.find("push    ebp") == -1 and instructionBeforeLine.find("push    ebx") == -1 and instructionBeforeLine.find("push    esp") == -1:			
					leadAddy = print_operand(address, 0)
				else:
					checkPoint = checkPoint + 1
					
							
		
		if currentInstruction.find("add     ") != -1:
			temp = print_operand(address, 1)
			additionSignIndex = temp.find("+") + 1
			subOffset = temp[additionSignIndex:].replace("h", "") 
			functionAddress = get_name_ea_simple(get_func_name(address))
			trueOffset = None
			if int(subOffset, 16) < 1024:
				if functionAddress in BaseOffsets:
					try:
						trueOffset = int(BaseOffsets.get(functionAddress), 16) + int(subOffset, 16)
					except ValueError:
						pass
					if trueOffset != None:
						offset = trueOffset
				if trueOffset == None:
					offset = FindBaseOffsetValue(address, subOffset)
			else:
				offset = int(subOffset, 16)
				
		if currentInstruction.find("lea     " + leadAddy) != -1:
			temp = print_operand(address, 1)
			additionSignIndex = temp.find("+") + 1
			if currentInstruction.find("h") != -1:				
				offset = temp[additionSignIndex:].replace("h]", "")
				offset = int(offset, 16)	
			else: 
				break
		
		if get_first_fcref_to(address) != 4294967295: 
			testAddressForCall = get_first_fcref_to(address)
			if generate_disasm_line(testAddressForCall, 0).find("call") == -1:
				if offset == None or nameOfOffset == "":
					CreateOffsets(testAddressForCall, testAddressForCall, leadAddy, i, checkPoint)
				elif offset != None and nameOfOffset != "":
					break
		
		i = i + 1
	
	if nameOfOffset == "":
		nameOfOffset = "NO NAME"
	if offset == None:
		if nameOfOffset != "NO NAME":
			offset = FindCallOffsetValue(currentAddress)
		if offset == None:
			offset = 65535
	if nameOfOffset not in Offsets:
		if nameOfOffset != "NO NAME":
			if offset != 65535:
				Offsets[nameOfOffset] = offset
	else:
		if nameOfOffset != "NO NAME":
			if Offsets.get(nameOfOffset) == 65535:
				Offsets[nameOfOffset] = offset
			if offset != 65535:
				Offsets[nameOfOffset] = offset

def GenerateList(ea):
	xrefs = list(XrefsTo(ea, 0))
	xrefs = list(filter(lambda xref: SegName(xref.frm) != ".rdata", xrefs))

	for xref in xrefs:
		address = xref.frm
		currentAddress = address
		checkPoint = 1
		i = 0		
		leadAddy = ""
		CreateOffsets(address, currentAddress, leadAddy, i, checkPoint)
