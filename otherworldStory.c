
// Otherworld Missions

rule StoryClass4Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c5m1_", 1, 8);
		if (trQuestVarGet("missionHardmode") == 1) {
			addCardToDeck(2, "", SPELL_TAVERN_BRAWL);
			addCardToDeck(2, "", SPELL_TAVERN_BRAWL);
			addCardToDeck(2, "", SPELL_TAVERN_BRAWL);
		}
		xsEnableRule("StoryClass4Mission1_end");
	}
}

rule StoryClass4Mission1_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c5m1_", 9, 13);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass4Mission2
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c5m2_", 1, 5);
		mSetVarByQV("p2commander", "health", 12);
		mSetVarByQV("p2commander", "maxhealth", 12);
		mSetVarByQV("p2commander", "attack", 1);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON));
		xsEnableRule("StoryClass4Mission2_end");
		if (trQuestVarGet("missionHardmode") == 1) {
			for(x=3; >0) {
				trQuestVarSetFromRand("temp", trQuestVarGet("ztilesstart"), trQuestVarGet("ztilesend") - 1, true);
				int tile = trQuestVarGet("temp");
				while (zGetVarByIndex("tiles", "occupant", tile) + zGetVarByIndex("tiles", "terrain", tile) > 0) {
					trQuestVarSetFromRand("temp", trQuestVarGet("ztilesstart"), trQuestVarGet("ztilesend") - 1, true);
					tile = trQuestVarGet("temp");
				}
				summonAtTile(tile, 2, kbGetProtoUnitID("Spider Egg"));
				addCardToDeck(2, "", SPELL_DOMINANCE);
			}
			shuffleDeck(2);
		}
	}
}

rule StoryClass4Mission2_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c5m2_", 6, 7);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass4Mission3
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c5m3_", 1, 8);
		
		trSetLighting("dusk", 0.1);
		xsEnableRule("StoryClass4Mission3_end");
		if (trQuestVarGet("missionHardmode") == 1) {
			shuffleDeck(2);
		}
	}
}

rule StoryClass4Mission3_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c5m3_", 9, 15);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}




rule StoryClass4Mission4
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c5m4_", 1, 3);
		trSetLighting("night", 0.1);
		xsEnableRule("StoryClass4Mission4_end");

		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(230, 2, kbGetProtoUnitID("Tartarian Gate"));
			summonAtTile(254, 2, kbGetProtoUnitID("Tartarian Gate"));
			for(x=20; >0) {
				addCardToDeck(2, "Theris");
			}
			shuffleDeck(2);
		}
	}
}

rule StoryClass4Mission4_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c5m4_", 4, 15);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}



rule StoryClass4Mission5
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c5m5_", 1, 3);
		xsEnableRule("StoryClass4Mission5_end");
		if (trQuestVarGet("missionHardmode") == 1) {
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			shuffleDeck(2);
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
		}
	}
}

rule StoryClass4Mission5_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c5m5_", 4, 10);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}


rule StoryClass4Mission6
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c5m6_", 1, 9);
		mSetVarByQV("p2commander", "health", 30);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Bireme"));
			summonAtTile(193, 2, kbGetProtoUnitID("Bireme"));
			for(x=0;<6) {
				addCardToDeck(2, "Theris");
				addCardToDeck(2, "", SPELL_DOMINANCE);
			}
			shuffleDeck(2);
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
		}
		xsEnableRule("StoryClass4Mission6_end");
	}
}

rule StoryClass4Mission6_Decay
highFrequency
inactive
{
	if (trQuestVarGet("activePlayer") == 2) {
		xsDisableSelf();
		OnPlay(1*trQuestVarGet("p2commander"));
		ChatLog(1, "<color={Playercolor(2)}>You have been inflicted with Decay!</color>");
	}
}

rule StoryClass4Mission6_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c5m6_", 10, 11);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

