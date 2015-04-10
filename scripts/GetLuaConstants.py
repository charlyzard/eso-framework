
#---------------------------------------------------------------------
# TESO Lua register constants gatherer script
# Version 1.0 March 2014
# Author: Sirmabus
#---------------------------------------------------------------------
from idaapi import *
import csv

"""
TESO API events and global constants:
http://wiki.esoui.com/Main_Page
"""

print "\n----------- Lua constatns gatherer -----------"
RegisterConstFuncName = "RegisterLuaConst_Func00"
RegisterConstFuncPat  = "55 8B EC 8B 51 08 DB 45 0C 8B 42 24 C7 00 ?? ?? ?? ?? DD 58 08 83 C0 10 89 42 24 8B 45 08 8B 49 08 50 68 ?? ?? ?? ?? 51 E8 ?? ?? ?? ?? 83 C4 0C 5D C2 08 00"

# Find the register function
pRegisterFunction = find_binary(idc.MinEA(), idc.MaxEA(), RegisterConstFuncPat, 16, idc.SEARCH_DOWN)
print "%s() @ %08X" % (RegisterConstFuncName, pRegisterFunction)
assert(pRegisterFunction != BADADDR)
print
# Name it
set_name(pRegisterFunction, RegisterConstFuncName, (SN_NON_AUTO | SN_NOWARN))

print "Working.."
aConst = {}

# Walk crefs
i = 0
cr = get_first_cref_to(pRegisterFunction)
while (cr != BADADDR):
	#msg("%08X [%u] \n" % (cr, i))
	i += 1

	# To push #1, the label
	pl = prev_head(cr,0) # "mov ecx,e??"
	pl = prev_head(pl,0) # "push offset label"
	# Should be pointing to a label string
	addr = DecodeInstruction(pl).Operands[0].value
	assert(addr > 0)
	constLabel = GetString(addr)
	assert(constLabel != "")
	# Strip line feed
	# constLabel = constLabel[:-2]

	# Prefix '_' to any redundant ones
	while constLabel in aConst:
		constLabel = ("_" + constLabel)
		#msg("Redundant: \"%s\" @ %08X\n" % (constLabel, cr))
		
	# To push #2, the number value
	pl = prev_head(pl,0) # "push ??"
	op = DecodeInstruction(pl).Operands[0]
	v = op.value
	# One of the register ones?
	if op.type != idaapi.o_imm:
		#msg("%08X %d %d\n" % (pl, op.type, op.reg))
		assert(op.type == idaapi.o_reg)
		# One of the start/0 ones?
		if op.reg == 0:
			v = 0
		# Should be an OR value
		else:
			assert(op.reg == 1)
			pl = prev_head(pl,0) # "or reg,value"
			inst = DecodeInstruction(pl)
			op = inst.Operands[0]
			#msg("  %08X %d %d %X\n" % (pl, op.type, op.reg, inst.Operands[1].value))
			assert((op.type == 1) and (op.reg == 1))
			v = inst.Operands[1].value
	aConst[constLabel] = v 

	cr = get_next_cref_to(pRegisterFunction, cr)

# Write out sorted to csv for study
csvf	= open('eso_lua_constants.csv', 'wb')
assert(csvf)
csvh = csv.writer(csvf, delimiter = ',',	quotechar =	'"', quoting =	csv.QUOTE_MINIMAL)
csvh.writerow(['label', 'value'])
for k in sorted(aConst.keys()):	
	csvh.writerow([k, aConst[k]])
	#msg("%s %d\n" % (k, aConst[k]))
csvf.close()
msg("Count: %d\n" % len(aConst))

refresh_idaview_anyway()
print "Done.\n"



