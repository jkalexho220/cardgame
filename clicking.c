const int RIGHT_CLICK = 2;
const int LEFT_CLICK = 1;

rule detectClick
highFrequency
active
{
	for (p=2; >0) {
		trUnitSelectClear();
		if (trCheckGPActive("create gold", p) && yFindLatest("vision"+p, "Gold Mine Dwarven", 0) > 0) {
			if (trQuestVarGet("p"+p+"mine") == 0) {
				trQuestVarSet("p"+p+"mine", 1);
				trVectorSetUnitPos("p"+p+"clickPos", "vision"+p, true);
				trQuestVarSet("p"+p+"click", RIGHT_CLICK);
				trUnitDestroy();
				trTechGodPower(p, "create gold", 1);
			}
		} else if (trPlayerUnitCountSpecific(p, "Animal Attractor") >= 1) {
			yFindLatest("magnet"+p, "Animal Attractor", p);
			trVectorSetUnitPos("p"+p+"clickPos", "magnet"+p, true);
			trQuestVarSet("p"+p+"click", LEFT_CLICK);
			trUnitDestroy();
			trTechGodPower(p, "Animal magnetism", 1);
		} else if (trQuestVarGet("p"+p+"mine") == 1) {
			trQuestVarSet("p"+p+"mine", 0);
		}
	}
}

rule initializeClick
highFrequency
active
runImmediately
{
	trTechGodPower(1, "Animal magnetism", 1);
	trTechGodPower(2, "Animal magnetism", 1);
	trTechGodPower(1, "create gold", 1);
	trTechGodPower(2, "create gold", 1);
	map("mouse1down", "game", "uiSetSpecialPower(227) uiSpecialPowerAtPointer");	// animal magnetism for left click
	map("mouse2up", "game", "uiSetSpecialPower(84) uiSpecialPowerAtPointer");		// dwarven mine for right click
	map("space", "game", "uiSetSpecialPower(156) uiSpecialPowerAtPointer");			// rain for space (look at hand)
	map("enter", "game", "uiSetSpecialPower(235) uiSpecialPowerAtPointer");			// nidhogg for enter (end turn)

	xsDisableRule("initializeClick");
}