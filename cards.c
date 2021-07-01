rule initializeCards
highFrequency
active
{
	/* Rogers */
	trStringQuestVarSet("commander1name", "(C) phdorogers4 <2>");
	trStringQuestVarSet("commander1keywords", "");
	trStringQuestVarSet("commander1description", "");
	trQuestVarSet("commander1proto", kbGetProtoUnitID("Hero Greek Jason"));
	trQuestVarSet("commander1cost", 0);
	trQuestVarSet("commander1attack", 2);
	trQuestVarSet("commander1health", 20);
	trQuestVarSet("commander1speed", 2);
	trQuestVarSet("commander1range", 1);

	/* Militia */
	trStringQuestVarSet("card1name", "(1) Militia <2>");
	trStringQuestVarSet("card1keywords", "");
	trStringQuestVarSet("card1description", "");
	trQuestVarSet("card1proto", kbGetProtoUnitID("Militia"));
	trQuestVarSet("card1cost", 1);
	trQuestVarSet("card1attack", 1);
	trQuestVarSet("card1health", 1);
	trQuestVarSet("card1speed", 2);
	trQuestVarSet("card1range", 1);

	xsDisableRule("initializeCards");
}