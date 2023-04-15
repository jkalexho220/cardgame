
// Otherworld Missions

rule StoryClass4Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c5m1_", 1, 8);
		mSetVarByQV("p1commander", "attack", 2);
		mSetVarByQV("p1commander", "health", 12);
		mSetVarByQV("p1commander", "maxhealth", 12);
		mSetVarByQV("p1commander", "keywords", mGetVarByQV("p1commander", "keywords") + Keyword(BEACON));

		mSetVarByQV("p2commander", "health", 12);
		mSetVarByQV("p2commander", "maxhealth", 12);
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
		
		mSetVarByQV("p1commander", "keywords", SetBit(mGetVarByQV("p1commander", "keywords"), BEACON));
		mSetVarByQV("p1commander", "attack", 1);
		mSetVarByQV("p1commander", "health", 12);
		mSetVarByQV("p1commander", "maxhealth", 12);
		xsEnableRule("StoryClass4Mission3_end");
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
			summonAtTile(194, 2, kbGetProtoUnitID("Tartarian Gate"));
			summonAtTile(195, 2, kbGetProtoUnitID("Tartarian Gate"));
			for(i=6; >0) {
				addCardToDeck(2, "Anubite");
				addCardToDeck(2, "Theocrat");
				addCardToDeck(2, "", SPELL_DEATH_DOOR);
				addCardToDeck(2, "", SPELL_DEVOUR);
			}
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
		
		xsEnableRule("StoryClass4Mission4_end");
		teleportToTile(1*trQuestVarGet("p2commander"), 255, true);

		xsEnableRule("StoryClass4Mission4_explain");
		xsEnableRule("StoryClass4Mission4_win");

		if (trQuestVarGet("missionHardmode") == 1) {
			for(x=6; >0) {
				addCardToDeck(2, "Tartarian Gate");
				addCardToDeck(2, "Theris");
				addCardToDeck(2, "Mummy");
			}
			shuffleDeck(2);
		}
	}
}

rule StoryClass4Mission4_explain
highFrequency
inactive
{
	if (trQuestVarGet("p1mana") > 0) {
		uiMessageBox("Destroy all the Mouths of Chaos to win!");
		xsDisableSelf();
	}
}

rule StoryClass4Mission4_win
inactive
highFrequency
{
	if (trCountUnitsInArea("128", 2, "Tartarian Gate", 45) == 0) {
		mSetVarByQV("p2commander", "health", 0);
		xsDisableSelf();
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
			for(i=3; >0) {
				addCardToDeck(2, "Apep");
				addCardToDeck(2, "Bear");
				addCardToDeck(2, "", SPELL_TAVERN_BRAWL);
				addCardToDeck(2, "", SPELL_FINAL_FRENZY);
			}
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
		mSetVarByQV("p2commander", "maxhealth", 30);
		mSetVarByQV("p2commander", "health", 30);
		mSetVarByQV("p2commander", "attack", 3);
		mSetVarByQV("p2commander", "keywords", SetBit(mGetVarByQV("p2commander", "keywords"), BEACON));
		generateCard(2, kbGetProtoUnitID("Tartarian Gate"));
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Tartarian Gate"));
			summonAtTile(193, 2, kbGetProtoUnitID("Tartarian Gate"));
			for(i=3; >0) {
				addCardToDeck(2, "", SPELL_SPIDER_LAIR);
				addCardToDeck(2, "", SPELL_DOMINANCE);
				addCardToDeck(2, "", SPELL_AQUARIUS);
			}
			shuffleDeck(2);
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
		}
		xsEnableRule("StoryClass4Mission6_end");
		xsEnableRule("StoryClass4Mission6_Decay");
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

