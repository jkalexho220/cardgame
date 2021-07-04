rule match_test
highFrequency
active
runImmediately
{
	for(x=10; >0) {
		for(p=2; >0) {
			addCardToDeck(p, "Militia");
			addCardToDeck(p, "Anubite");
			addCardToDeck(p, "Toxotes");
			addCardToDeck(p, "Ballista");
		}
	}
	xsDisableRule("match_test");
}


rule match_00_start
highFrequency
active
{
	trQuestVarSet("p1commander", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("1,10","Dwarf",1,1,0,1,45,true);


	trQuestVarSet("p2commander", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("1,10","Dwarf",1,119,0,119,225, true);
	trArmySelect("1,10");
	trUnitConvert(2);

	trTechGodPower(0, "spy", 2);
	for(p=2; >0) {
		trUnitSelectClear();
		trUnitSelectByID(1*trQuestVarGet("p"+p+"startTile"));
		trUnitConvert(p);
		trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));

		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("p"+p+"commander"), true);
		trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"startTile"));
		trUnitChangeProtoUnit("Hero Greek Jason");
		trTechInvokeGodPower(0, "spy", xsVectorSet(1,1,1), xsVectorSet(1,1,1));


		trUnitSelectClear();
		trUnitSelectByID(1*trQuestVarGet("p"+p+"startTile"));
		trUnitConvert(0);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		trQuestVarSet("p"+p+"drawCards", 4);

		yAddToDatabase("allUnits", "p"+p+"Commander");
		yAddUpdateVar("allUnits", "spell", SPELL_COMMANDER);
		yAddUpdateVar("allUnits", "tile", trQuestVarGet("p"+p+"startTile"));
		yAddUpdateVar("allUnits", "health", 20);
		yAddUpdateVar("allUnits", "attack", 2);
		yAddUpdateVar("allUnits", "speed", 2);

		shuffleDeck(p);
	}

	xsDisableRule("match_00_start");
	xsEnableRule("match_01_mulliganStart");
}

rule match_01_mulliganStart
highFrequency
inactive
{
	if (trQuestVarGet("p1drawCards") == 0 && trQuestVarGet("p2drawCards") == 0) {
		for(p=2; >0) {
			for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
				yDatabaseNext("p"+p+"hand");
				trUnitSelectClear();
				trUnitSelectByID(1*yGetVar("p"+p+"hand", "pos"));
				trMutateSelected(kbGetProtoUnitID("Garrison Flag Sky Passage"));
			}
			trQuestVarSet("p"+p+"done", 0);
		}
		trMessageSetText("Left click to choose cards to mulligan. Right click to finish.",-1);

		xsEnaleRule("match_02_mulligan");
		xsDisableRule("match_01_mulliganStart");
	}
}

rule match_02_mulligan
highFrequency
inactive
{
	if (trQuestVarGet("p1done") == 1 && trQuestVarGet("p2done") == 1) {
		trQuestVarSet("activePlayer", 1);
		xsEnableRule("turn_00_start");
		xsDisableRule("match_02_mulligan");
	} else {
		for(p=2; >0) {
			switch(1*trQuestVarGet("p"+p+"click"))
			{
				case LEFT_CLICK:
				{
					
				}
				case RIGHT_CLICK:
				{
					
				}
			}
		}
	}
}