// Naga Missions

rule StoryClass2Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("HeavenGames\c2m1_01", "");
		CinematicAdd("HeavenGames\c2m1_02", "");
		CinematicAdd("HeavenGames\c2m1_03", "");
		CinematicAdd("HeavenGames\c2m1_04", "");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 20);
		mSetVarByQV("p2commander", "attack", 4);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON) + Keyword(FURIOUS));
		mSetVarByQV("p2commander", "spell", SPELL_COMMANDER);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Nereid"));
			summonAtTile(223, 2, kbGetProtoUnitID("Nereid"));
		}
		xsEnableRule("StoryClass2Mission1_end");
	}
}

rule StoryClass2Mission1_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		trFadeOutAllSounds(0.0);
		CinematicReset();
		CinematicAdd("HeavenGames\c2m1_05", "");
		CinematicAdd("HeavenGames\c2m1_06", "");
		CinematicAdd("HeavenGames\c2m1_07", "");
		CinematicAdd("HeavenGames\c2m1_08", "");
		CinematicAdd("HeavenGames\c2m1_09", "");
		CinematicAdd("HeavenGames\c2m1_10", "");
		CinematicAdd("HeavenGames\c2m1_11", "");
		CinematicStart();
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass2Mission2
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("HeavenGames\c2m2_01", "");
		CinematicAdd("HeavenGames\c2m2_02", "");
		CinematicAdd("HeavenGames\c2m2_03", "");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 20);
		mSetVarByQV("p2commander", "attack", 3);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON) + Keyword(LIGHTNING));
		mSetVarByQV("p2commander", "spell", SPELL_COMMANDER);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(139, 2, kbGetProtoUnitID("Man O War"));
			summonAtTile(145, 2, kbGetProtoUnitID("Man O War"));
		}
		xsEnableRule("StoryClass2Mission2_mes");
	}
}

rule StoryClass2Mission2_mes
highFrequency
inactive
{
	if (trQuestVarGet("p1mana") == 1) {
		xsDisableSelf();
		uiMessageBox("You are underwater. Here's an Oxygen Tank.","");
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		xsEnableRule("StoryClass2Mission2_end");
	}
}

rule StoryClass2Mission2_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicReset();
		CinematicAdd("HeavenGames\c2m2_04", "");
		CinematicStart();
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass2Mission3
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("HeavenGames\c2m3_01", "");
		CinematicAdd("HeavenGames\c2m3_02", "");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 20);
		mSetVarByQV("p2commander", "attack", 4);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON));
		mSetVarByQV("p2commander", "spell", SPELL_COMMANDER);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(168, 2, kbGetProtoUnitID("Wadjet"));
			summonAtTile(169, 2, kbGetProtoUnitID("Wadjet"));
		}
		xsEnableRule("StoryClass2Mission3_mes");
	}
}

rule StoryClass2Mission3_mes
highFrequency
inactive
{
	if (trQuestVarGet("p1mana") == 1) {
		xsDisableSelf();
		uiMessageBox("Two Oxygen Tanks for current depth.","");
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		xsEnableRule("StoryClass2Mission3_end");
	}
}

rule StoryClass2Mission3_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicReset();
		CinematicAdd("HeavenGames\c2m3_03", "");
		CinematicStart();
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass2Mission4
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("HeavenGames\c2m4_01", "");
		CinematicAdd("HeavenGames\c2m4_02", "");
		CinematicAdd("HeavenGames\c2m4_03", "");
		CinematicAdd("HeavenGames\c2m4_04", "");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 20);
		mSetVarByQV("p2commander", "attack", 1);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON) + Keyword(REGENERATE));
		mSetVarByQV("p2commander", "spell", SPELL_COMMANDER);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(150, 2, kbGetProtoUnitID("Sea Turtle"));
			summonAtTile(151, 2, kbGetProtoUnitID("Sea Turtle"));
		}
		xsEnableRule("StoryClass2Mission4_mes");
	}
}

rule StoryClass2Mission4_mes
highFrequency
inactive
{
	if (trQuestVarGet("p1mana") == 1) {
		xsDisableSelf();
		uiMessageBox("Three Oxygen Tanks for current depth.","");
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
	}
}

rule StoryClass2Mission5
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("HeavenGames\c2m5_01", "");
		CinematicAdd("HeavenGames\c2m5_02", "");
		CinematicAdd("HeavenGames\c2m5_03", "");
		CinematicAdd("HeavenGames\c2m5_04", "");
		CinematicAdd("HeavenGames\c2m5_05", "");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 40);
		mSetVarByQV("p2commander", "attack", 2);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON) + Keyword(ETHEREAL));
		mSetVarByQV("p2commander", "spell", SPELL_COMMANDER);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Leviathan"));
			summonAtTile(193, 2, kbGetProtoUnitID("Leviathan"));
		}
		xsEnableRule("StoryClass2Mission5_mes");
	}
}

rule StoryClass2Mission5_mes
highFrequency
inactive
{
	if (trQuestVarGet("p1mana") == 1) {
		xsDisableSelf();
		uiMessageBox("Four Oxygen Tanks for current depth.","");
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
		addCardToHand(1, 0, SPELL_OXYGEN_TANK, false);
	}
}

rule StoryClass2Mission6
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("HeavenGames\c2m6_01", "");
		CinematicAdd("HeavenGames\c2m6_02", "");
		CinematicAdd("HeavenGames\c2m6_03", "");
		CinematicAdd("HeavenGames\c2m6_04", "");
		CinematicAdd("HeavenGames\c2m6_05", "");
		CinematicAdd("HeavenGames\c2m6_06", "");
		CinematicAdd("HeavenGames\c2m6_07", "");
		CinematicAdd("HeavenGames\c2m6_08", "");
		CinematicAdd("HeavenGames\c2m6_09", "");
		CinematicAdd("HeavenGames\c2m6_10", "");
		CinematicAdd("HeavenGames\c2m6_11", "");
		CinematicAdd("HeavenGames\c2m6_12", "");
		CinematicAdd("HeavenGames\c2m6_13", "");
		CinematicAdd("HeavenGames\c2m6_14", "");
		CinematicAdd("HeavenGames\c2m6_15", "");
		CinematicAdd("HeavenGames\c2m6_16", "");
		CinematicAdd("HeavenGames\c2m6_17", "");
		CinematicAdd("HeavenGames\c2m6_18", "");
		CinematicAdd("HeavenGames\c2m6_19", "");
		CinematicAdd("HeavenGames\c2m6_20", "");
		CinematicAdd("HeavenGames\c2m6_21", "");
		CinematicAdd("HeavenGames\c2m6_22", "");
		CinematicStart();
		trQuestVarSet("companion", summonAtTile(283, 1, kbGetProtoUnitID("Archer Atlantean Hero")));
		teleportToTile(1*trQuestVarGet("p1commander"), 281);
		teleportToTile(1*trQuestVarGet("p2commander"), 255);
		zSetVarByIndex("tiles", "occupant", 282, 0);
		zSetVarByIndex("tiles", "occupant", 219, 0);
		deployAtTile(0, "Sky Passage", 255);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(129, 2, kbGetProtoUnitID("Tower Mirror"));
			summonAtTile(133, 2, kbGetProtoUnitID("Tower Mirror"));
			summonAtTile(131, 2, kbGetProtoUnitID("Tower Mirror"));
			summonAtTile(134, 2, kbGetProtoUnitID("Oracle Scout"));
			summonAtTile(130, 2, kbGetProtoUnitID("Oracle Scout"));
			summonAtTile(128, 2, kbGetProtoUnitID("Priest"));
			summonAtTile(132, 2, kbGetProtoUnitID("Priest"));
			summonAtTile(268, 2, kbGetProtoUnitID("Golem"));
			summonAtTile(289, 2, kbGetProtoUnitID("Golem"));
			summonAtTile(296, 2, kbGetProtoUnitID("Golem"));
			summonAtTile(275, 2, kbGetProtoUnitID("Golem"));
		} else {
			summonAtTile(128, 2, kbGetProtoUnitID("Tower Mirror"));
			summonAtTile(133, 2, kbGetProtoUnitID("Oracle Scout"));
			summonAtTile(131, 2, kbGetProtoUnitID("Priest"));
			summonAtTile(268, 2, kbGetProtoUnitID("Nemean Lion"));
			summonAtTile(289, 2, kbGetProtoUnitID("Nemean Lion"));
			summonAtTile(296, 2, kbGetProtoUnitID("Nemean Lion"));
			summonAtTile(275, 2, kbGetProtoUnitID("Nemean Lion"));
		}
		trQuestVarSet("idsEyecandyEnd", trGetNextUnitScenarioNameNumber());
		xsEnableRule("StoryClass2Mission6_mes");
	}
}

rule StoryClass2Mission6_mes
highFrequency
inactive
{
	if (trQuestVarGet("p1mana") == 1) {
		xsDisableSelf();
		uiMessageBox("Objective: Out Reach and Scragins must survive and get near the exit.","");
		xsEnableRule("StoryClass2Mission6_end");
	}
}

rule StoryClass2Mission6_end
highFrequency
inactive
{
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet("p2commander")));
	if (trDistanceToVectorSquared("p1commander", "pos") < 64 && trDistanceToVectorSquared("companion", "pos") < 64) {
		damageUnit(1*trQuestVarGet("p2commander"), 999);
		removeDeadUnits();
		trQuestVarSet("p2defeated", 1);
		xsEnableRule("match_end");
		trUIFadeToColor(0,0,0,900,0,true);
		xsEnableRule("StoryClass2Mission6_end2");
		xsDisableSelf();
	} else if (mGetVarByQV("companion", "health") <= 0) {
		damageUnit(1*trQuestVarGet("p1commander"), 999);
		removeDeadUnits();
		xsDisableSelf();
	} else if (mGetVarByQV("p1commander", "health") <= 0) {
		xsDisableSelf();
	}
}

rule StoryClass2Mission6_end2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 2) {
		CinematicReset();
		CinematicAdd("HeavenGames\c2m6_23", "");
		CinematicAdd("HeavenGames\c2m6_24", "");
		CinematicAdd("HeavenGames\c2m6_25", "");
		CinematicAdd("HeavenGames\c2m6_26", "");
		CinematicAdd("HeavenGames\c2m6_27", "");
		CinematicStart();
		xsDisableSelf();
	}
}
