rule StoryClass0Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c1m1_", 1, 2);
		
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Wolf"));
			summonAtTile(193, 2, kbGetProtoUnitID("Wolf"));
		}
	}
}

rule StoryClass0Mission2
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c1m2_", 1, 5);
		xsEnableRule("StoryClass0Mission2_end");

		if (trQuestVarGet("missionHardmode") == 1) {
			
		}
	}
}

rule StoryClass0Mission2_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c1m2_", 6, 8);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass0Mission3
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c1m3_", 1, 3);
		
		if (trQuestVarGet("missionHardmode") == 1) {
			for (x=6; >0) {
				addCardToDeck(2, "Hero Greek Ajax");
			}
			summonAtTile(168, 2, kbGetProtoUnitID("Swordsman"));
			summonAtTile(169, 2, kbGetProtoUnitID("Swordsman"));
		}
	}
}

rule StoryClass0Mission4
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c1m4_", 1, 8);
		//trShowImageDialog("icons\Scenario Kemsyt Icon 64", "Ah perfect, something to plunder! We got stuck in this swamp and we were getting bored!");
		trSoundPlayFN("kemsytattack1.wav","1",-1,"","");
		xsEnableRule("StoryClass0Mission4_end");
	}
}

rule StoryClass0Mission4_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c1m4_", 9, 11);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass0Mission5
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c1m5_", 1, 4);
		xsEnableRule("StoryClass0Mission5_end");
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Bondi"));
			summonAtTile(193, 2, kbGetProtoUnitID("Bondi"));
		}
	}
}

rule StoryClass0Mission5_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c1m5_", 5, 8);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass0Mission6
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c1m6_", 1, 3);
		xsEnableRule("StoryClass0Mission6_end");
	}
}

rule StoryClass0Mission6_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c1m6_", 4, 15);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}