
// Space Missions

rule StoryClass5Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		mSetVarByQV("p2commander", "attack", 2);
		mSetVarByQV("p2commander", "health", 20);
		mSetVarByQV("p2commander", "maxhealth", 20);
		mSetVarByQV("p2commander", "keywords", mGetVarByQV("p2commander", "keywords") + Keyword(BEACON));
		CinematicPlay("HeavenGames\c6m1_", 1, 12);
		trMusicPlay("cinematics\28_in\music.mp3", "24", 0.0);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", 30);
			mSetVarByQV("p2commander", "maxhealth", 30);
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
		trMusicPlay("cinematics\16_in\music.mp3", "20", 0.0);
		mSetVarByQV("p2commander", "health", 20);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", 30);
			mSetVarByQV("p2commander", "maxhealth", 30);
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
		trMusicPlay("xpack\xcinematics\5_b\music.mp3", "16", 0.0);
		mSetVarByQV("p2commander", "health", 30);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", 45);
			mSetVarByQV("p2commander", "maxhealth", 45);
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
		trMusicPlay("cinematics\31_out\music.mp3", "34", 0.0);
		mSetVarByQV("p2commander", "health", 30);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", 45);
			mSetVarByQV("p2commander", "maxhealth", 45);
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
		trMusicPlay("cinematics\9_out\music.mp3", "29", 0.0);
		mSetVarByQV("p2commander", "health", 40);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", 60);
			mSetVarByQV("p2commander", "maxhealth", 60);
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
		trMusicPlay("cinematics\35_out\music.mp3", "29", 0.0);
		mSetVarByQV("p2commander", "health", 80);
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", 120);
			mSetVarByQV("p2commander", "maxhealth", 120);
		}
	}
}