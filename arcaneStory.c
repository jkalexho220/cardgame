

rule StoryClass1Mission1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m1_", 1, 3);
		
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(168, 2, kbGetProtoUnitID("Prisoner"));
			summonAtTile(169, 2, kbGetProtoUnitID("Monument"));
		}
		xsEnableRule("StoryClass1Mission1_end");
	}
}

rule StoryClass1Mission1_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c2m1_", 4, 8);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass1Mission2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m2_", 1, 4);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Oracle Scout"));
			summonAtTile(193, 2, kbGetProtoUnitID("Monument 2"));
		}
	}
}

rule StoryClass1Mission3
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m3_", 1, 3);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Frost Giant"));
			summonAtTile(223, 2, kbGetProtoUnitID("Monument 3"));
		}
	}
}

rule StoryClass1Mission4
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m4_", 1, 4);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(129, 2, kbGetProtoUnitID("Maceman"));
		}
	}
}

rule StoryClass1Mission5
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m5_", 1, 4);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Golem"));
			summonAtTile(223, 2, kbGetProtoUnitID("Monument 4"));
		}
	}
}

rule StoryClass1Mission6
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m6_", 1, 6);
		trPaintTerrain(0, 0, 60, 60, 0, 50, false);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Fire Giant"));
			summonAtTile(193, 2, kbGetProtoUnitID("Monument 5"));
		}

		xsEnableRule("StoryClass1Mission6_end");
	}
}

rule StoryClass1Mission6_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c2m6_", 7, 13);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}
