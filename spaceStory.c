
// Space Missions

rule StoryClass5Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c6m1_", 1, 12);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", mGetVarByQV("p2commander", "health")*2);
		}
	}
}

rule StoryClass5Mission2
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c6m2_", 1, 4);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", mGetVarByQV("p2commander", "health")*2);
		}
	}
}

rule StoryClass5Mission3
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c6m3_", 1, 1);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", mGetVarByQV("p2commander", "health")*2);
		}
	}
}

rule StoryClass5Mission4
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c6m4_", 1, 8);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", mGetVarByQV("p2commander", "health")*2);
		}
	}
}

rule StoryClass5Mission5
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c6m5_", 1, 1);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", mGetVarByQV("p2commander", "health")*2);
		}
	}
}

rule StoryClass5Mission6
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c6m6_", 1, 6);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", mGetVarByQV("p2commander", "health")*2);
		}
	}
}