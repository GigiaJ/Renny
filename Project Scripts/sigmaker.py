from idc import *
from idautils import *
from Tkinter import Tk

import random
 
UA_MAXOP   = 6
MAX_XREFS = 20

def add_to_clipboard(text):
    r = Tk()
    r.withdraw()
    r.clipboard_clear()
    r.clipboard_append(text)
    r.destroy()
 
def AddBytesToSig(curSig, currentIns, size):
    for i in xrange(size):
        curSig = "%s%0.2X " % (curSig, idc.Byte(currentIns+i))
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
    patternType = 0

    foundPattern = []

    # Am I an Xref?
    xrefsFrom = list(XrefsFrom(ea))

    if len(xrefsFrom) == 2:
        ea = xrefsFrom[1].to

    # Is function or offset?
    functionName = GetFunctionName(ea)
    if functionName:
        name = functionName
        patternType = 0
    else:
        name = NameEx(BADADDR, ea)
        patternType = 1

    if patternType == 0:
        foundPattern.append(["\"" + name + "\"", "\"{}\"".format(create_pattern(ea)), patternType])

    xrefs = list(XrefsTo(ea, 0))
    xrefs = list(filter(lambda xref: SegName(xref.frm) != ".rdata", xrefs))
    
    if MAX_XREFS != -1:
        xrefs = random.sample(xrefs, min(len(xrefs), MAX_XREFS))
    b = 0
    for xref in xrefs:
        i = 0
       
        opndValue = GetOperandValue(xref.frm, i)
        while opndValue != -1 and opndValue != ea:
            i += 1
            opndValue = GetOperandValue(xref.frm, i)
        foundPattern.append(["\"{}{}\"".format(name, b), "\"{}\"".format(create_pattern(xref.frm)), 1, i])
        b = b + 1
    formattedPattern = ""

    for i, pattern in enumerate(foundPattern):
        formattedPattern += "\t\t["
        for j, v in enumerate(pattern)  :
            formattedPattern += "\n\t\t\t{}".format(v)
            if j != len(pattern) - 1:
                formattedPattern += ","
        formattedPattern += "\n\t\t]"
        if i != len(foundPattern) -1:
            formattedPattern += ","

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