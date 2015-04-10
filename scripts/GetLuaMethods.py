
#---------------------------------------------------------------------
# TESO Lua register methods labler gatherer script
# Version 1.0 March 2014
# Author: Sirmabus
#---------------------------------------------------------------------
from idaapi import *
import csv

"""
TESO API list:
http://wiki.esoui.com/w/index.php?title=API&oldid=81#Global
"""

print "\n----------- Lua method function labler gatherer -----------"
RegisterMethodFuncName = "RegisterLuaAPI_Func00"
RegisterMethodFuncPat  = "55 8B EC 81 EC ?? ?? ?? ?? A1 ?? ?? ?? ?? 33 C5 89 45 FC 8B 45 0C 53 56 8B 75 08 6A 00 56 8B D9 8B 53 08 8B 4D 10 6A 00 50 52 89 75 B0 89 45 AC 89 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 43 08 56 68 ?? ?? ?? ?? 50 E8 ?? ?? ?? ?? 8B 83 ?? ?? ?? ?? 83 C4 20 83 F8 03 74 05 83 F8 01 75 5F 8B 4D AC 57 56 8D 55 BC 6A 40 52 89 45 B4 89 4D B8 E8 ?? ?? ?? ?? 8B 45 B0 B9 ?? ?? ?? ?? 8D 75 B4 8D BD ?? ?? ?? ?? 50 F3 A5 E8 ?? ?? ?? ?? 83 C4 10 8D 8D ?? ?? ?? ?? 51 8D 55 B0 52 8D 8B ?? ?? ?? ?? 89 45 B0 E8 ?? ?? ?? ?? 8D 45 B4 50 8D 4D AC 51 8D 8B ?? ?? ?? ?? E8 ?? ?? ?? ?? 5F 8B 4D FC 5E C7 83 ?? ?? ?? ?? ?? ?? ?? ?? 33 CD 5B E8 ?? ?? ?? ?? 8B E5 5D C2 0C 00"

# Find the register function
pRegisterFunction = find_binary(idc.MinEA(), idc.MaxEA(), RegisterMethodFuncPat, 16, idc.SEARCH_DOWN)
print "%s() @ %08X" % (RegisterMethodFuncName, pRegisterFunction)
assert(pRegisterFunction != BADADDR)
print
# Name it
set_name(pRegisterFunction, RegisterMethodFuncName, (SN_NON_AUTO | SN_NOWARN))

print "Working.."
aFunction = {}

# Walk crefs
i = 0
cr = get_first_cref_to(pRegisterFunction)
while (cr != BADADDR):
	#msg("%08X [%u] \n" % (cr, i))
	i += 1

	# To push #1, the name
	pl = prev_head(cr,0) # "mov ecx,e??"
	pl = prev_head(pl,0) # "push offset name"
	# Should be pointing to a name string
	addr = DecodeInstruction(pl).Operands[0].value
	assert(addr > 0)
	funcName = GetString(addr)
	assert(funcName != "")
	# Strip line feed
	# funcName = funcName[:-2]

	# Prefix '_' to the few redundant ones
	while funcName in aFunction:
		funcName = ("_" + funcName)
		#msg("Redundant: %s\n" % funcName)
		
	# To push #2, the function
	pl = prev_head(pl,0) # "push offset sub_xxxx"
	addr = DecodeInstruction(pl).Operands[0].value
	assert(addr > 0)
	# Name the function w/Lua tag
	set_name(addr, (funcName + "_lua"), (SN_NON_AUTO | SN_NOWARN))	
	aFunction[funcName] = addr 

	cr = get_next_cref_to(pRegisterFunction, cr)

# Write out sorted to csv for study
csvf	= open('eso_lua_methods.csv', 'wb')
assert(csvf)
csvh = csv.writer(csvf, delimiter = ',',	quotechar =	'"', quoting =	csv.QUOTE_MINIMAL)
csvh.writerow(['name', 'address'])
for k in sorted(aFunction.keys()):	
	csvh.writerow([k, hex(aFunction[k])])
	msg("%08X %s\n" % (aFunction[k], k))
csvf.close()
msg("Count: %d\n" % len(aFunction))

refresh_idaview_anyway()
print "Done.\n"



