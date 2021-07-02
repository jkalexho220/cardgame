import os
import sys

FILE_1 = None
FILE_2 = None
NAME = None
named = False
comment = False

try:
	FILE_1 = sys.argv[1]
	FILE_2 = sys.argv[1][:-2] + '.xml'
	if len(sys.argv) > 2:
		NAME = sys.argv[2]
		named = True
except IndexError:
	sys.exit("A file must be specified for xmlification!")

def checkQuestVarSet(templine, ln):
	tokens = templine.replace('(', ' ( ').replace(')', ' ) ').replace(',', ' , ').split(' ')
	findComma = False
	foundComma = False
	depth = 0
	for x in tokens:
		if (x == 'trQuestVarSet'):
			findComma = True
		if findComma:
			if (depth == 1):
				if x == ',':
					foundComma = True
				elif x == ')' and not foundComma:
					print("trQuestVarSet instead of trQuestVarGet")
					print("Line " + str(ln) + ":\n    " + line)
			if (x == '('):
				depth = depth + 1
			elif (x == ')'):
				depth = depth - 1

def checkUnknownFunctions(templine, ln):
	tokens = templine.replace('=', ' ').replace(';', ' ').replace('(', ' ( ').replace(')', ' ) ').replace('*', ' ').replace('+', ' ').replace(',', ' ').replace('"', ' " ').replace('-', ' ').replace('/', ' ').replace('<', ' ').replace('>', ' ').split(' ')
	if (tokens[0] == 'void' or tokens[0] == 'int' or tokens[0] == 'string' or tokens[0] == 'vector' or tokens[0] == 'float' or tokens[0] == 'bool') and tokens[2] == '(':
		functions.add(tokens[1])
	else:
		ignore = False

		for t in range(len(tokens)):
			if '"' in tokens[t]:
				ignore = not ignore
			if not ignore:
				if t > 0 and tokens[t] == '(':
					if (not tokens[t-1] in functions) and (not tokens[t-1].isspace()):
						print("Unknown function")
						print("Line " + str(ln) + ":\n    " + tokens[t-1])
						if not tokens[t-1] in unknowns:
							unknowns.add(tokens[t-1])


print("xmlification start!")

functions = {' ', 'xsPow', 'trQuestVarGet', 'trQuestVarSet', '', 'trSetDisableGPBlocking', 'kbIsPlayerHuman', 
			'trDamageUnitsInArea', 'trCameraCut', 'trUnitSetAnimation', 'trPlayerTechTreeEnabledGodPowers', 
			'trGetUnitScenarioNameNumber', 'trUnitIsOwnedBy', 'trCounterAddTime', 'trMutateSelected', 'xsMin', 
			'trChatSend', 'trUnitIsSelected', 'kbGetProtoUnitName', 'trUnitSetStance', 'trForceNonCinematicModels', 
			'trLetterBox', 'trUnitDead', 'Math_atan', 'trUnitPercentDamaged', 'trDamageUnitPercent', 'trCamTrackLoad', 
			'trTechGodPower', 'xsCos', 'trModifyProtounit', 'Math_cos', 'while', 'trPlayerSetDiplomacy', 
			'trSetUnitOrientation', 'trMessageSetText', 'kbUnitGetAnimationActionType', 'trUnitHighlight', 'trUnitConvert', 
			'xsVectorSet', 'trVectorQuestVarGetZ', 'map', 'if', 'trSetUnitIdleProcessing', 
			'trCountUnitsInArea', 'trArmyDispatch', 'trTime', 'xsEnableRule', 'trUnitDestroy', 'trPlayerUnitCountSpecific', 
			'xsSetContextPlayer', 'trVectorQuestVarGetX', 'trSetCivAndCulture', 'xsAbs', 
			'trUnitSelect', 'kbUnitGetActionType', 'trSoundPlayFN', 'trUnitTeleport', 'trUnitOverrideAnimation', 
			'trCameraShake', 'trCamTrackPlay', 'kbGetProtoUnitID', 'trDamageUnit', 'trGetStatValue', 'xsDisableRule', 
			'xsSqrt', 'trSetLighting', 'for', 'trVectorQuestVarSet', 'trTechInvokeGodPower', 'aiSet', 'trCheckGPActive', 
			'trGetNextUnitScenarioNameNumber', 'trMusicPlay', 'xsSin', 'trPlayerGetPopulation', 
			'trDelayedRuleActivation', 'trStringQuestVarGet', 'kbGetBlockID', 'trCurrentPlayer', 'trPlayerGrantResources', 
			'trPaintTerrain', 'trPlayerResourceCount', 'trCounterAbort', 'return', 'unitTransform', 'trPlayerKillAllGodPowers', 
			'sunColor', 'trSetCounterDisplay', 'trUnitSelectClear', 'trArmySelect', 'kbGetBlockPosition', 
			'trQuestVarSetFromRand', 'vector', 'trTechSetStatus', 'trRevealEntireMap', 'trSetObscuredUnits', 
			'kbUnitGetTargetUnitID', 'ambientColor', 'trUIFadeToColor', 'trClearCounterDisplay', 'trUnitChangeProtoUnit', 
			'switch', 'trVectorQuestVarGetY', 'trQuestVarCopy', 'trUnitAlive', 'trSetSelectedScale', 'trUnitDoWorkOnUnit', 
			'kbGetUnitBaseTypeID', 'trImmediateUnitGarrison', 'trStringQuestVarSet', 'trOverlayTextColour', 'trUnitSelectByID', 
			'trOverlayText', 'Math_sin', 'trUnitMoveToPoint', 'trSetFogAndBlackmap', 'xsMax', 'trForbidProtounit', 'xsGetContextPlayer', 
			'trSetPlayerWon', 'trEndGame', 'trSetPlayerDefeated', 'trUnitChangeName', 'trChatSendSpoofed', 'trUnitSetAnimationPath',
			'trMusicPlayCurrent', 'trVectorQuestVarGet', 'trUnitEjectContained', 'trObjectiveSetID', 'trUIFlash', 'kbUnitGetCurrentHitpoints', 
			'trMusicStop', 'uiFindType', 'xsRound', 'xsFloor', 'trChatHistoryClear', 'trSetCivilizationNameOverride', 'kbIsPlayerResigned',
			'trSoundPlayDialog', 'trChangeTerrainHeight', 'trRenderSky', 'trFadeOutAllSounds', 'aiIsMultiplayer', 'trShowWinLose', 
			'gadgetUnreal', 'trGetScenarioUserData'}
unknowns = {''}
ln = 1
if FILE_1 == 'all':
	files = ['shared.c', 'board.c', 'prologue.c', 'cards.c', 'clicking.c']
	named = True
	FILE_2 = 'cardGameAll.xml'
	NAME = " Card Game"
else:
	files = [FILE_1]
try:
	with open(FILE_2, 'w') as file_data_2:
		with open("template.txt", 'r') as template:
			line = template.readline()
			while line:
				file_data_2.write(line)
				line = template.readline()
		file_data_2.write('\n<Effect name="'+ NAME +'">\n')
		for f in files:
			FILE_1 = f
			ln = 1
			print("parsing " + FILE_1 + "...")
			with open(FILE_1, 'r') as file_data_1:
				line = file_data_1.readline()
				while line:
					if not line.isspace():
						if ('/*' in line):
							comment = True
						
						if (not comment):
							templine = line.strip()
							checkQuestVarSet(templine, ln)
							checkUnknownFunctions(templine, ln)
							if ('if ' in templine or 'if(' in templine) and ('yGetVar' in templine or 'trQuestVarGet' in templine) and not ('=' in templine or '>' in templine or '<' in templine or 'ySetContains' in templine or 'trUnitIsOwnedBy' in templine or 'cWatchActive' in templine or 'yDatabaseContains' in templine or 'trCheckGPActive' in templine):
								print("Missing equality statement")
								print("Line " + str(ln) + ":\n    " + line)
							if not (templine[-1] == ';' or '//' in templine or templine[-1] == '{' or templine[-1] == '}' or templine[-2:] == '||' or templine[-2:] == '&&' or templine[-1] == ',' or templine[-4:] == 'else' or templine[0:4] == 'rule' or templine == 'highFrequency' or templine == 'runImmediately' or templine[-1] == '/' or templine[-6:] == 'active' or templine[0:11] == 'minInterval' or templine[0:4] == 'case' or templine[0:7] == 'switch('):
								print("Missing semicolon")
								print("Line " + str(ln) + ":\n    " + line)
							if '{' in templine and not 'else' in templine and not 'if' in templine and not 'for' in templine and not 'while' in templine and ')' in templine and not '{P' in templine:
								equalCount = templine.count('string', templine.index('(')) + templine.count('int', templine.index('(')) + templine.count('float', templine.index('(')) + templine.count('bool', templine.index('('))
								if equalCount > templine.count('='):
									print("Needs equals sign")
									print("Line " + str(ln) + ":\n    " + line)
							if 'return' in templine and not '(' in templine:
								print("Needs parenthesis")
								print("Line " + str(ln) + ":\n    " + line)
							if 'for' in templine and '";' in templine:
								print("Wrong parenthesis")
								print("Line " + str(ln) + ":\n    " + line)
							if 'for' in templine and not ';' in templine and not '//':
								print("Missing semicolon in for statement")
								print("Line " + str(ln) + ":\n    " + line)
							if 'trMutateSelected("' in templine:
								print("Needs kbGetProtoUnitID()")
								print("Line " + str(ln) + ":\n    " + line)
							if '<' in line or '&' in line or '|' in line:
								file_data_2.write('<Command><![CDATA[' + line.rstrip() + ']]></Command>\n')
							else:
								file_data_2.write('<Command>' + line.rstrip() + '</Command>\n')
						if ('*/' in line):
							comment = False
					else:
						file_data_2.write('\n')
					line = file_data_1.readline()
					ln = ln + 1
		file_data_2.write('</Effect>\n')
		file_data_2.write('</Effects>\n')
		file_data_2.write('</trigger>')
except IOError:
	sys.exit("Files not found!")

print("Done!")
if (len(unknowns) > 1):
	print("Unknowns: ")
	print(unknowns)
"""
#"""