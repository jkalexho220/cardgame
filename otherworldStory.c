
// Otherworld Missions

rule StoryClass4Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("icons/hero g jason icon 64", "They said I could find Zenophobia here, but is he really in this dreary place?");
		CinematicAdd("icons/hero g perseus icon 64", "Halt! State your business!");
		CinematicAdd("icons/hero g jason icon 64", "What? Who are you?");
		CinematicAdd("icons/hero g perseus icon 64", "I am Anraheir, guardian of these lands. Now state your business!");
		CinematicAdd("icons/hero g jason icon 64", "I am Rogers. I need to meet with Zenophobia and request his help.");
		CinematicAdd("icons/hero g perseus icon 64", "Zenophobia you say? Well you're in luck. I'm one of his agents. I can guide you to him.");
		CinematicStart();
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
		CinematicReset();
		CinematicAdd("icons/hero g jason icon 64", "What were those? Creepy!");
		CinematicAdd("icons/hero g perseus icon 64", "They are Zombie Trees. This forest is home to many denizens of the Otherworld.");
		CinematicAdd("icons/hero g jason icon 64", "The Otherworld? What's that?");
		CinematicAdd("icons/hero g perseus icon 64", "It is the realm where madness and nightmares reside. Sometimes they cross over to our dimension.");
		CinematicAdd("icons/hero g perseus icon 64", "Fortunately, Zenophobia has established a barrier around this forest to contain them.");
		CinematicStart();
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
		CinematicReset();
		CinematicAdd("icons/hero g jason icon 64", "So where is Zenophobia?");
		CinematicAdd("icons/hero g perseus icon 64", "He is in the Otherworld.");
		CinematicAdd("icons/hero g jason icon 64", "What?! We have to go there to meet him?!");
		CinematicAdd("icons/hero g perseus icon 64", "That is correct.");
		CinematicAdd("icons/hero g jason icon 64", "Can't he come out here instead? I really don't want to face more of those things.");
		CinematicAdd("icons/hero g perseus icon 64", "It depends on his mood, really.");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 12);
		mSetVarByQV("p2commander", "attack", 1);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON));
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

rule StoryClass4Mission3
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("icons/hero g perseus icon 64", "This is bad. Night approaches. We must hurry.");
		CinematicAdd("icons/hero g jason icon 64", "What happens when night falls?");
		CinematicAdd("icons/hero g perseus icon 64", "You don't want to know. Let's just get to the portal as soon as possible.");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 20);
		mSetVarByQV("p2commander", "attack", 2);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON));
		trSetLighting("dusk", 0.1);
		xsEnableRule("StoryClass4Mission3_Decay");
		if (trQuestVarGet("missionHardmode") == 1) {
			for(x=3; >0) {
				addCardToDeck(2, "", SPELL_DOMINANCE);
				addCardToDeck(2, "Tartarian Gate");
			}
			summonAtTile(222, 2, kbGetProtoUnitID("Argus"));
			summonAtTile(223, 2, kbGetProtoUnitID("Argus"));
			shuffleDeck(2);
		}
	}
}

rule StoryClass4Mission3_Decay
highFrequency
inactive
{
	if (trQuestVarGet("activePlayer") == 2) {
		xsDisableSelf();
		OnPlay(1*trQuestVarGet("p2commander"));
		ChatLog(1, "<color={Playercolor(2)}>You have been inflicted with Decay!</color>");
	}
}


rule StoryClass4Mission4
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("icons/hero g jason icon 64", "Uhh, Anraheir? It's night time!");
		CinematicAdd("icons/hero g perseus icon 64", "The portal is just up ahead! Let's go!");
		CinematicStart();
		trSetLighting("night", 0.1);
		teleportToTile(1*trQuestVarGet("p2commander"), 128);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(230, 2, kbGetProtoUnitID("Tartarian Gate"));
			summonAtTile(254, 2, kbGetProtoUnitID("Tartarian Gate"));
			for(x=20; >0) {
				addCardToDeck(2, "Theris");
			}
			shuffleDeck(2);
		}
		
		deployAtTile(0, "Well of Urd", 128);
		trQuestVarSet("idsEyecandyEnd", trGetNextUnitScenarioNameNumber());
	}
}


rule StoryClass4Mission5
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("icons/hero g jason icon 64", "This is the Otherworld?");
		CinematicAdd("icons/hero g perseus icon 64", "Yes. Try not to make sense of anything. This place is filled with madness, after all.");
		CinematicAdd("icons/infantry g hoplite icon 64", "Yo, Anraheir! Got time for a playtest?");
		CinematicAdd("icons/hero g jason icon 64", "It's Zenophobia!");
		CinematicAdd("icons/hero g perseus icon 64", "No, that's a fake! He never asks me to playtest!");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 30);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Bireme"));
			summonAtTile(193, 2, kbGetProtoUnitID("Bireme"));
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			shuffleDeck(2);
		}
	}
}

rule StoryClass4Mission6
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("icons/hero g perseus icon 64", "No, that's a fake! He never asks me to playtest!");
		CinematicAdd("icons/hero g jason icon 64", "It's Zenophobia!");
		CinematicAdd("icons/infantry g hoplite icon 64", "Yo, Anraheir! Got time for a playtest?");
		CinematicAdd("icons/hero g perseus icon 64", "Yes. Try not to make sense of anything. This place is filled with madness, after all.");
		CinematicAdd("icons/hero g jason icon 64", "This is the Otherworld?");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 30);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(192, 2, kbGetProtoUnitID("Bireme"));
			summonAtTile(193, 2, kbGetProtoUnitID("Bireme"));
			for(x=0;<6) {
				addCardToDeck(2, "Theris");
				addCardToDeck(2, "", SPELL_DOMINANCE);
			}
			shuffleDeck(2);
		}
		xsEnableRule("StoryClass4Mission6_end");
	}
}

rule StoryClass4Mission6_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicReset();
		CinematicAdd("icons/infantry g hoplite icon 64", "Whew! Thank goodness you broke that paradox! I've been trapped for months!");
		CinematicAdd("icons/hero g perseus icon 64", "That's a lie. You were just too lazy to get out.");
		CinematicAdd("icons/infantry g hoplite icon 64", "Perhaps. But in any case, I know why you're here.");
		CinematicAdd("icons/hero g jason icon 64", "You do? Will you help me then?");
		CinematicAdd("icons/infantry g hoplite icon 64", "Certainly. It's an excellent distraction from all my unfinished work.");
		CinematicStart();
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}