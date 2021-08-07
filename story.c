void CleanBoard(){
	trCounterAbort("counter");
	trClearCounterDisplay();
	trSoundPlayDialog("default", "1", -1, false, " : ", "");
	uiClearSelection();
	yDatabasePointerDefault("allUnits");
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		trDamageUnitPercent(100);
	}
	yClearDatabase("allUnits");
}

rule MissionTutorialBegin
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 1){
		xsDisableRule("MissionTutorialBegin");
		xsEnableRule("initializeBoard");
		xsEnableRule("MissionTutorialEnd");
   }
}

rule MissionTutorialEnd
highFrequency
inactive
{
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("p1commander"), true);
	bool defeat = trUnitDead();
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("p2commander"), true);
	bool victory = trUnitDead();
	if (defeat || victory){
		CleanBoard();
		setClassProgress(CLASS_ADVENTURER, 1);
		setClassProgress(CLASS_ARCANE, 1);
		dataSave();
		xsDisableRule("MissionTutorialEnd");
		xsEnableRule("Collection");
   }
}