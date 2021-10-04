
// Clockwork Missions

rule StoryClass3Mission1
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
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
		}
		xsEnableRule("StoryClass3Mission1_end");
	}	
}

rule StoryClass3Mission1_end
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


rule StoryClass3Mission2
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
		teleportToTile(1*trQuestVarGet("p1commander"), 132);
		teleportToTile(1*trQuestVarGet("p2commander"), 152);
		if (trQuestVarGet("missionHardmode") == 1) {
			for(x=0; <6) {
				addCardToDeck(2, "", SPELL_METEOR);
				addCardToDeck(2, "Crossbowman");
			}
		}
		xsEnableRule("StoryClass3Mission2_deploy");
		xsEnableRule("StoryClass3Mission2_end");
	}	
}

rule StoryClass3Mission2_deploy
highFrequency
inactive
{
	if (trQuestVarGet("p2mana") > trQuestVarGet("storyMissionBotMana")) {
		trQuestVarCopy("storyMissionBotMana", "p2mana");
		if (trQuestVarGet("storyMissionBotMana") == 5) {
			if (zGetVarByIndex("tiles", "occupant", 255) == 0) {
				int siphon = summonAtTile(255, 2, kbGetProtoUnitID("Fire Siphon"));
				mSetVar(siphon, "laserDirx", -0.707107);
				mSetVar(siphon, "laserDirz", -0.707107);
				trUnitSelectClear();
				trUnitSelect(""+siphon);
				trSetUnitOrientation(xsVectorSet(-0.707107,0,0.707107), xsVectorSet(0,1,0), true);
				ChatLog(1, "<color=1.0,0,0>Opponent:</color> Deploy the Laser Cannon!");
			}
		}
		trQuestVarSetFromRand("rand", 1, 1*trQuestVarGet("storyMissionBotMana"), true);
		if (trQuestVarGet("missionHardmode") == 0) {
			trQuestVarSetFromRand("rand2", 1, 1*trQuestVarGet("storyMissionBotMana"), true);
			if (trQuestVarGet("rand2") < trQuestVarGet("rand")) {
				trQuestVarCopy("rand", "rand2");
			}
		}
		for(x=trQuestVarGet("rand"); >0) {
			trQuestVarSetFromRand("tile", 255, 296, true);
			if (zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("tile")) == 0) {
				if (x == 4) {
					summonAtTile(1*trQuestVarGet("tile"), 2, kbGetProtoUnitID("Javelin Cavalry"));
				} else if (x == 5) {
					summonAtTile(1*trQuestVarGet("tile"), 2, kbGetProtoUnitID("Chieroballista"));
				} else if (x == 6) {
					summonAtTile(1*trQuestVarGet("tile"), 2, kbGetProtoUnitID("Colossus"));
				} else {
					summonAtTile(1*trQuestVarGet("tile"), 2, kbGetProtoUnitID("Maceman Hero"));
				}
			}
		}
	}
}


rule StoryClass3Mission2_end
highFrequency
inactive
{
	if (trQuestVarGet("p2mana") >= 10) {
		damageUnit(1*trQuestVarGet("p2commander"), 999);
		removeDeadUnits();
		xsDisableSelf();
		xsDisableRule("StoryClass3Mission2_deploy");
	} else if (mGetVarByQV("objectiveObelisk", "health") <= 0) {
		damageUnit(1*trQuestVarGet("p1commander"), 999);
		removeDeadUnits();
		xsDisableSelf();
		xsDisableRule("StoryClass3Mission2_deploy");
	} else if (mGetVarByQV("p1commander", "health") <= 0) {
		xsDisableSelf();
		xsDisableRule("StoryClass3Mission2_deploy");
	}
}


rule StoryClass3Mission3
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
		teleportToTile(1*trQuestVarGet("p2commander"), 233);
	}	
}


rule StoryClass3Mission4
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
		mSetVarByQV("p2commander", "health", 20);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(128, 2, kbGetProtoUnitID("Tower Mirror"));
		}
	}	
}

rule StoryClass3Mission5
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
		damageUnit(1*trQuestVarGet("p1commander"), 18);
		zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p2commander", "tile"), 0);
		teleportToTile(1*trQuestVarGet("p2commander"), 219);
		xsEnableRule("StoryClass3Mission5_1");
		xsEnableRule("StoryClass3Mission5_end");
		xsEnableRule("StoryClass3Mission5_story");
		trQuestVarSet("storyMissionBotMana", 0);
	}
}

rule StoryClass3Mission5_1
highFrequency
inactive
{
	trQuestVarSet("p1drawCards", 0);
	if ((trQuestVarGet("maxmana") > trQuestVarGet("storyMissionBotMana")) &&
		(yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + yGetDatabaseCount("pushes") == 0) && 
		(trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) {
		trQuestVarCopy("storyMissionBotMana", "maxmana");
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (mGetVarByQV("allUnits", "spell") == SPELL_NONE) {
				mSetVarByQV("allUnits", "OnDeath", 0);
				damageUnit(1*trQuestVarGet("allUnits"), 999);
			}
		}
		trSoundPlayFN("favordump.wav","1",-1,"","");
		removeDeadUnits();
		trMessageSetText("Survive this turn!", -1);
		switch(1*trQuestVarGet("storyMissionBotMana"))
		{
			case 1:
			{
				SummonLaser(135, 129);
			}
			case 2:
			{
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 128);
				SummonLaser(139, 130);
				SummonLaser(141, 131);
				SummonLaser(146, 134);
				SummonLaser(137, 134);
				SummonLaser(143, 132);
				SummonLaser(145, 134);
			}
			case 3:
			{
				trMessageSetText("Survive this turn! (Check your hand)", -1);
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 128);
				SummonLaser(146, 145);
				SummonLaser(137, 134);
				SummonLaser(135, 129);
				SummonLaser(136, 130);
				SummonLaser(138, 139);
				addCardToHand(1, kbGetProtoUnitID("Minion"), 0, true);
				addCardToHand(1, 0, SPELL_ZENOS_PARADOX, true);
			}
			case 4:
			{
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 145);
				SummonLaser(146, 145);
				SummonLaser(137, 134);
				SummonLaser(135, 129);
				SummonLaser(136, 130);

				SummonLaser(144, 145);
				SummonLaser(143, 133);
				SummonLaser(142, 132);
				SummonLaser(141, 131);
				addCardToHand(1, kbGetProtoUnitID("Minion"), 0, true);
				addCardToHand(1, 0, SPELL_ZENOS_PARADOX, true);
			}
			case 5:
			{
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 132);
				SummonLaser(144, 145);
				SummonLaser(137, 134);
				SummonLaser(129, 128);
				SummonLaser(136, 130);
				SummonLaser(140, 139);
				mSetVar(summonAtTile(130, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				mSetVar(summonAtTile(141, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				addCardToHand(1, kbGetProtoUnitID("Minion"), 0, true);
				addCardToHand(1, kbGetProtoUnitID("Battle Boar"), 0, true);
			}
			case 6:
			{
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 128);
				SummonLaser(146, 145);
				for (x=145; >=134) {
					mSetVar(summonAtTile(x, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				}
				addCardToHand(1, kbGetProtoUnitID("Minion"), 0, true);
				addCardToHand(1, kbGetProtoUnitID("Sphinx"), 0, true);
				addCardToHand(1, 0, SPELL_ZENOS_PARADOX, true);
			}
			case 7:
			{
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 142);
				SummonLaser(137, 134);
				SummonLaser(136, 130);
				mSetVar(summonAtTile(135, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);

				mSetVar(summonAtTile(133, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				mSetVar(summonAtTile(143, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				mSetVar(summonAtTile(131, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				mSetVar(summonAtTile(141, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				addCardToHand(1, 0, SPELL_ZENOS_PARADOX, true);
				addCardToHand(1, 0, SPELL_ZENOS_PARADOX, true);
				addCardToHand(1, kbGetProtoUnitID("Minion"), 0, true);
				addCardToHand(1, kbGetProtoUnitID("Ape of Set"), 0, true);
				addCardToHand(1, kbGetProtoUnitID("Battle Boar"), 0, true);
			}
			case 8:
			{
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 135);
				mSetVar(summonAtTile(129,2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				mSetVar(summonAtTile(136,2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				mSetVar(summonAtTile(137,2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				SummonLaser(146, 137);
				SummonLaser(138, 136);
				SummonLaser(142, 132);
				summonAtTile(128, 1, kbGetProtoUnitID("Throwing Axeman"));
				addCardToHand(1, 0, SPELL_EXPLOSION, true);
				addCardToHand(1, 0, SPELL_DOUBLEBLAST, true);
				addCardToHand(1, kbGetProtoUnitID("Oracle Scout"), 0, true);
				addCardToHand(1, kbGetProtoUnitID("Oracle Scout"), 0, true);
				addCardToHand(1, 0, SPELL_ZENOS_PARADOX, true);
			}
			case 9:
			{
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p1commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 132);
				SummonLaser(135, 132);
				SummonLaser(129, 132);
				SummonLaser(128, 132);
				for (x=146; >=136) {
					mSetVar(summonAtTile(x,2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
				}
				addCardToHand(1, kbGetProtoUnitID("Minion"), 0, true);
				addCardToHand(1, kbGetProtoUnitID("Ape of Set"), 0, true);
				addCardToHand(1, kbGetProtoUnitID("Battle Boar"), 0, true);
				addCardToHand(1, 0, SPELL_DUEL, true);
				addCardToHand(1, 0, SPELL_BLOOD_PRICE, true);
			}
			case 10:
			{
				xsDisableSelf();
			}
		}
		for(x=yGetDatabaseCount("p1hand"); >0) {
			yDatabaseNext("p1hand");
			mSetVarByQV("p1hand", "keywords", SetBit(1*mGetVarByQV("p1hand", "keywords"), FLEETING));
		}
		updateHandPlayable(1);
		trDelayedRuleActivation("StoryClass3Mission5_2");
	}
}

rule StoryClass3Mission5_2
highFrequency
inactive
{
	if (trTime() > cActivationTime) {
		xsDisableSelf();
		unitTransform("Generic Corpse", "Cinematic Block");
	}
}

rule StoryClass3Mission5_end
highFrequency
inactive
{
	if (PlayerDefeated(1)) {
		xsDisableSelf();
		xsDisableRule("StoryClass3Mission5_1");
		xsDisableRule("StoryClass3Mission5_2");
	} else if (trQuestVarGet("maxMana") == 10) {
		damageUnit(1*trQuestVarGet("p2commander"), 9999);
		xsDisableSelf();
		xsDisableRule("StoryClass3Mission5_1");
		xsDisableRule("StoryClass3Mission5_2");
	}
}

rule StoryClass3Mission5_story
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("icons/hero g jason icon 64", "They said I could find Zenophobia here, but is he really in this dreary place?");
		CinematicAdd("icons/hero g perseus icon 64", "Halt! State your business!");
		CinematicAdd("icons/hero g jason icon 64", "What? Who are you?");
		CinematicAdd("icons/hero g perseus icon 64", "I am Anraheir, guardian of these lands. Now state your business!");
		CinematicAdd("icons/hero g jason icon 64", "I am Rogers. I need to meet with Zenophobia and request his help.");
		CinematicAdd("icons/hero g perseus icon 64", "Zenophobia you say? Well you're in luck. I'm one of his agents. I can guide you to him.");
		CinematicStart();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}


rule StoryClass3Mission6
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
		mSetVarByQV("p2commander", "health", 30);
		mSetVarByQV("p2commander", "attack", 1);
		if (trQuestVarGet("missionHardmode") == 1) {
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
		}
		xsEnableRule("StoryClass3Mission6_end");
	}	
}

rule StoryClass3Mission6_end
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
