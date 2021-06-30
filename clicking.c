rule detectClick
highFrequency
active
{
	for (p=2; >0) {
		if (trPlayerGetPopulation(p) > 9000) {
			trUnitSelectClear();
			yFindLatestReverse("magnet", "Animal Attractor", p);
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
	map("mouse1down", "game", "uiSetSpecialPower(227) uiSpecialPowerAtPointer");
	map("mouse2up", "game", "uiSetSpecialPower(227) uiSpecialPowerAtPointer");
	xsDisableRule("initializeClick");
}