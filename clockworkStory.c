
// Clockwork Missions

rule StoryClass3Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0) {
		xsDisableSelf();
		CinematicReset();
		CinematicAdd("icons\infantry g hoplite icon 64", "Insert image of clockwork landscape.");
		CinematicAdd("HeavenGames\rogers", "Next up is Yeebaagooon...");
		CinematicAdd("HeavenGames\roxas", "Did you just say Yeebaagooon? What business do you have with that villain?");
		CinematicAdd("HeavenGames\rogers", "Villain? The Yeebaagooon I know isn't a villain.");
		CinematicAdd("HeavenGames\roxas", "Oh, you must be working for him then. Die!");
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
		CinematicAdd("HeavenGames\roxas", "Dammit! How could this be?");
		CinematicAdd("HeavenGames\rogers", "I'm not going to kill you. Just explain this villain business.");
		CinematicAdd("HeavenGames\roxas", "What? Aren't you here to assassinate me?");
		CinematicAdd("HeavenGames\rogers", "No! I just need Yeebaagooon's help with something.");
		CinematicAdd("HeavenGames\roxas", "Does that involve Yeebaagooon leaving to join you?");
		CinematicAdd("HeavenGames\rogers", "Uh, probably.");
		CinematicAdd("HeavenGames\roxas", "Excellent! I will help you reach Yeebaagooon.");
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
		CinematicAdd("HeavenGames\roxas", "This land was once a lush green valley. But then Yeebaagooon came and estabilshed the Evil Profit Company.");
		CinematicAdd("HeavenGames\roxas", "Now, it is a wasteland filled with factories that build his robot army.");
		CinematicAdd("HeavenGames\roxas", "But strangely, some of us have gained sentience and have formed a resistance. This is one of our bases.");
		CinematicAdd("HeavenGames\robot", "Commander Roxas! We have trouble! The Profit Patrol are attacking!");
		CinematicAdd("HeavenGames\roxas", "What? To battle stations!");
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
				mSetVar(siphon, "laserDirx", -70710);
				mSetVar(siphon, "laserDirz", -70710);
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
		CinematicAdd("HeavenGames\roxas", "You have proven your strength and honesty. I will lead you to Yeebaagooon.");
		CinematicAdd("icons\infantry g hoplite icon 64", "Insert image of the tower entrance.");
		CinematicAdd("HeavenGames\roxas", "This is the incinerator of the Evil Profit Company.");
		CinematicAdd("HeavenGames\roxas", "No one guards this place. We can sneak in if we're careful.");
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
		CinematicAdd("icons\infantry g hoplite icon 64", "Insert panel introducing throwaway villain");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 20);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(128, 2, kbGetProtoUnitID("Tower Mirror"));
		}
		xsEnableRule("StoryClass3Mission4_end");
	}
}


rule StoryClass3Mission4_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicReset();
		CinematicAdd("HeavenGames\underling", "Boss! The tower has been infiltrated by a robot and a swordsman!");
		CinematicAdd("HeavenGames\yeebaagooon", "Hm, that swordsman looks familiar. What was his name again? Royce? Ronald?");
		CinematicAdd("HeavenGames\underling", "Are they your guests sir?");
		CinematicAdd("HeavenGames\yeebaagooon", "No. But let's send them an invitation anyway.");
		CinematicStart();
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
		CinematicReset();
		CinematicAdd("icons\infantry g hoplite icon 64", "insert image of yeebaagooon screen");
		CinematicAdd("HeavenGames\yeebaagooon", "Welcome, Ronald! And you, robot man, whatever your name is.");
		CinematicAdd("HeavenGames\rogers", "It's Rogers, actually.");
		CinematicAdd("HeavenGames\roxas", "You bastard! Show yourself instead of hiding behind that screen!");
		CinematicAdd("HeavenGames\yeebaagooon", "How rude. I'm inviting you to a match of Minigames Z. Enjoy!");
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
		CinematicAdd("HeavenGames\yeebaagooon", "Well done! You can take the elevator straight to the presidential suite.");
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
		CinematicAdd("HeavenGames\yeebaagooon", "Welcome, Royce!");
		CinematicAdd("HeavenGames\roxas", "Yeebaagooon! At last, I will topple your rein-");
		CinematicAdd("icons\infantry g hoplite icon 64", "Insert image of yeeb zapping roxas");
		CinematicAdd("HeavenGames\yeebaagooon", "Dispose of him.");
		CinematicAdd("HeavenGames\underling", "Yessir");
		CinematicAdd("HeavenGames\rogers", "What? Wait! Don't kill him! He's a playable character!");
		CinematicAdd("HeavenGames\yeebaagooon", "Foolish. Not even playable characters are safe from me.");
		CinematicAdd("HeavenGames\yeebaagooon", "If you want me to spare him, then prove yourself.");
		CinematicStart();
		mSetVarByQV("p2commander", "health", 30);
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
		CinematicReset();
		CinematicAdd("HeavenGames\yeebaagooon", "Congratulations. The annoying robot lives another day.");
		CinematicAdd("HeavenGames\rogers", "Alright. Will you hear me out now? I need your help to save the world.");
		CinematicAdd("HeavenGames\yeebaagooon", "Saving the world? From what?");
		CinematicAdd("HeavenGames\rogers", "Insert thing we are trying to stop here");
		CinematicAdd("HeavenGames\yeebaagooon", "Well this won't do. Can't have some upstart trying to destroy the world before I do.");
		CinematicAdd("HeavenGames\yeebaagooon", "I shall assist you in this endeavor. Rejoice.");
		CinematicStart();
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}
