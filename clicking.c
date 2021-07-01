rule detectClick
highFrequency
active
{
	for (p=2; >0) {
		if (trPlayerGetPopulation(p) > 9000) {
			trUnitSelectClear();
			yFindLatestReverse("vision", "Vision Revealer", p);
			trVectorSetUnitPos("p"+p+"clickPos", "vision", true);
			trQuestVarSet("p"+p+"click", 2);
			trUnitDestroy();
			trTechGodPower(p, "Vision", 1);
		} else if (trPlayerUnitCountSpecific(p, "Animal Attractor") >= 1) {
			yFindLatest("magnet", "Animal Attractor", p);
			trVectorSetUnitPos("p"+p+"clickPos", "magnet", true);
			trQuestVarSet("p"+p+"click", 1);
			trUnitDestroy();
			trTechGodPower(p, "Animal magnetism", 1);
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
	trTechGodPower(1, "Vision", 1);
	trTechGodPower(2, "Vision", 1);
	map("mouse1down", "game", "uiSetSpecialPower(227) uiSpecialPowerAtPointer");
	map("mouse2up", "game", "uiSetSpecialPower(220) uiSpecialPowerAtPointer");
	xsDisableRule("initializeClick");
}