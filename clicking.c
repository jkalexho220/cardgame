const int RIGHT_CLICK = 2;
const int LEFT_CLICK = 1;

rule detectClick
highFrequency
active
{
	for (p=2; >0) {
		if (trPlayerGetPopulation(p) > 9000) {
			trUnitSelectClear();
			yFindLatestReverse("vision"+p, "Vision Revealer", p);
			trVectorSetUnitPos("p"+p+"clickPos", "vision"+p, true);
			trQuestVarSet("p"+p+"click", RIGHT_CLICK);
			trUnitDestroy();
			trTechGodPower(p, "Vision", 1);
		} else if (trPlayerUnitCountSpecific(p, "Animal Attractor") >= 1) {
			yFindLatest("magnet"+p, "Animal Attractor", p);
			trVectorSetUnitPos("p"+p+"clickPos", "magnet"+p, true);
			trQuestVarSet("p"+p+"click", LEFT_CLICK);
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
	map("mouse2doubleup", "game", "uiSetSpecialPower(220) uiSpecialPowerAtPointer");
	map("mouse2doubleup", "game", "uiSetSpecialPower(220) uiSpecialPowerAtPointer");
	map("space", "game", "uiSetSpecialPower(156) uiSpecialPowerAtPointer");
	xsDisableRule("initializeClick");
}