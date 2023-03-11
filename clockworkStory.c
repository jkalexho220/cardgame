
// Clockwork Missions

rule StoryClass3Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c4m1_", 1, 6);
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
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
		CinematicPlay("HeavenGames\c4m1_", 7, 10);
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
		CinematicPlay("HeavenGames\c4m2_", 1, 4);
		zSetVarByIndex("tiles", "occupant", mGetVarByQV("p2commander", "tile"), 0);
		teleportToTile(1*trQuestVarGet("p1commander"), 132);
		teleportToTile(1*trQuestVarGet("p2commander"), 152);
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
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
				mSetVar(siphon, "laserDirx", -70710);
				mSetVar(siphon, "laserDirz", -70710);
				trUnitSelectClear();
				trUnitSelect(""+siphon);
				trSetUnitOrientation(xsVectorSet(-0.707107,0,-0.707107), xsVectorSet(0,1,0), true);
				ChatLog(1, "<color=1.0,0,0>Opponent:<color=1,1,1> Deploy the Laser Cannon!");
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
					summonAtTile(1*trQuestVarGet("tile"), 2, kbGetProtoUnitID("Hero Norse"));
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
		mSetVarByQV("p2commander", "health", 0);
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
		CinematicPlay("HeavenGames\c4m3_", 1, 5);
		//teleportToTile(1*trQuestVarGet("p2commander"), 233);
	}
}


rule StoryClass3Mission4
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c4m4_", 1, 5);
		mSetVarByQV("p2commander", "health", 15);
		mSetVarByQV("p2commander", "maxhealth", 15);
		mSetVarByQV("p2commander", "keywords", SetBit(mGetVarByQV("p2commander", "keywords"), BEACON));
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("p2commander", "health", 20);
			mSetVarByQV("p2commander", "maxhealth", 20);
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
		} else {
			generateCard(1, 0, SPELL_FORTIFY);
			generateCard(1, 0, SPELL_SCRAP_METAL);
			generateCard(1, 0, SPELL_SCRAP_METAL);
			xsEnableRule("StoryClass3Mission4_talk");
		}
		xsEnableRule("StoryClass3Mission4_end");
	}
}

rule StoryClass3Mission4_talk
highFrequency
inactive
{
	if (trQuestVarGet("activePlayer") == 1) {
		CharacterLog(1, "Roxas", "Quick! Cast Fortify to barricade the hallways!");
		xsDisableSelf();
	}
}


rule StoryClass3Mission4_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c4m4_", 6, 10);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass3Mission5
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicPlay("HeavenGames\c4m5_", 1, 6);
		damageUnit(1*trQuestVarGet("p1commander"), 18);
		zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("p2commander", "tile"), 0);
		teleportToTile(1*trQuestVarGet("p2commander"), 219);
		xsEnableRule("StoryClass3Mission5_1");
		xsEnableRule("StoryClass3Mission5_end");
		xsEnableRule("StoryClass3Mission5_story");
		trQuestVarSet("storyMissionBotMana", 0);
		xsEnableRule("StoryClass3Mission5_fast_start");
	}
}

// skip mulligan
rule StoryClass3Mission5_fast_start
highFrequency
inactive
{
	if (trQuestVarGet("p2done") == 1) {
		trQuestVarSet("p1done", 1);
		xsDisableSelf();
	}
}

rule StoryClass3Mission5_1
highFrequency
inactive
{
	trQuestVarSet("p1drawCards", 0);
	if ((trQuestVarGet("p1mana") > trQuestVarGet("storyMissionBotMana")) &&
		(yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + yGetDatabaseCount("pushes") == 0) &&
		(trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) {
		trQuestVarCopy("storyMissionBotMana", "p1mana");
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
				mSetVar(summonAtTile(146, 2, kbGetProtoUnitID("Ape of Set")), "attack", 3);
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
				mSetVar(summonAtTile(128, 1, kbGetProtoUnitID("Throwing Axeman")), "action", ACTION_READY);
				
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
		mSetVarByQV("p2commander", "health", 0);
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
		CinematicPlay("HeavenGames\c4m5_", 7, 16);
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
		CinematicPlay("HeavenGames\c4m6_", 1, 10);
		mSetVarByQV("p2commander", "health", 30);
		mSetVarByQV("p2commander", "maxhealth", 30);
		mSetVarByQV("p2commander", "attack", 1);
		if (trQuestVarGet("missionHardmode") == 1) {
			for(x=6; >0) {
				addCardToDeck(2, "", SPELL_DOMINANCE);
				addCardToDeck(2, "", SPELL_BANHAMMER);
			}
		}
		xsEnableRule("StoryClass3Mission6_end");
	}
}

rule StoryClass3Mission6_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c4m6_", 11, 14);
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}
