rule match_test
highFrequency
inactive
runImmediately
{
	for(p=2; >0) {
		for(x=3; >0) {
			addCardToDeck(p, "Khopesh");
			addCardToDeck(p, "Villager Atlantean");
			addCardToDeck(p, "Swordsman");
			addCardToDeck(p, "Maceman");
			addCardToDeck(p, "Skraeling");
			addCardToDeck(p, "Slinger");
			addCardToDeck(p, "Toxotes");
			addCardToDeck(p, "Raiding Cavalry");
			addCardToDeck(p, "Trident Soldier");
			addCardToDeck(p, "Jarl");
			addCardToDeck(p, "Hero Greek Ajax");
			addCardToDeck(p, "Huskarl");
			addCardToDeck(p, "Peltast");
			addCardToDeck(p, "Scout");
			addCardToDeck(p, "Physician");
			
			addCardToDeck(p, "Avenger");
			addCardToDeck(p, "Hero Greek Theseus");
			addCardToDeck(p, "Mountain Giant");
			addCardToDeck(p, "", SPELL_FIRST_AID);
		}
		addCardToDeck(p, "", SPELL_WHIRLWIND);
		addCardToDeck(p, "", SPELL_BACKSTAB);
		addCardToDeck(p, "", SPELL_DUEL);
		addCardToDeck(p, "", SPELL_PARTY_UP);
		addCardToDeck(p, "", SPELL_TEAMWORK);
		addCardToDeck(p, "", SPELL_DEFENDER);
		addCardToDeck(p, "", SPELL_VICTORY);
		addCardToDeck(p, "", SPELL_HEROIC);
		addCardToDeck(p, "Archer Atlantean Hero");
		addCardToDeck(p, "Nemean Lion");
	}
	
	InitBot(BOT_PERSONALITY_DEFAULT);
	
	xsDisableRule("match_test");
}

rule match_00_start
highFrequency
inactive
{
	trTechGodPower(0, "spy", 2);
	for(p=2; >0) {
		trQuestVarSet("p"+p+"commander", summonAtTile(1*trQuestVarGet("p"+p+"startTile"), p, kbGetProtoUnitID("Hero Greek Jason")));
		mSetVarByQV("p"+p+"commander", "spell", SPELL_COMMANDER);

		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("p"+p+"commander"), true);
		trTechInvokeGodPower(0, "spy", xsVectorSet(1,1,1), xsVectorSet(1,1,1));

		trQuestVarSet("p"+p+"drawCards", 4);
		zSetVarByIndex("tiles", "occupant", 1*trQuestVarGet("p"+p+"startTile"), 1*trQuestVarGet("p"+p+"commander"));

		shuffleDeck(p);
	}

	// Ravens
	trQuestVarSet("p1block", 869);
	trQuestVarSet("p2block", 871);
	

	xsDisableRule("match_00_start");
	xsEnableRule("match_01_mulliganStart");
	xsEnableRule("gameplay_toggle_camera");
}

rule match_01_mulliganStart
highFrequency
inactive
{
	if (trQuestVarGet("p1drawCards") + trQuestVarGet("p2drawCards") == 0) {
		unitTransform("Spy Eye", "Healing SFX");
		trTechGodPower(1, "nidhogg", 1);
		trTechGodPower(2, "nidhogg", 1);
		for(p=2; >0) {
			for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
				yDatabaseNext("p"+p+"hand");
				trUnitSelectClear();
				trUnitSelectByID(1*yGetVar("p"+p+"hand", "pos"));
				trMutateSelected(kbGetProtoUnitID("Garrison Flag Sky Passage"));
				ySetVar("p"+p+"hand", "mulligan", 0);
			}
			trQuestVarSet("p"+p+"done", 0);
		}
		trMessageSetText("Left click to choose cards to mulligan. Right click to finish.",-1);
		
		if(Multiplayer){
			trCounterAddTime("counter", 21, 1, "Mulligan phase",-1);	
		} else {
			trQuestVarSet("p2done", 1);
		}

		xsEnableRule("match_02_mulligan");
		xsDisableRule("match_01_mulliganStart");
	}
}

rule match_02_mulligan
highFrequency
inactive
{
	if (trQuestVarGet("p1done") + trQuestVarGet("p2done") == 2 || (Multiplayer  && (trTime() > cActivationTime + 20))) {
		xsEnableRule("match_03_replace");
		xsDisableRule("match_02_mulligan");
	} else {
		int unit = -1;
		for(p=2; >0) {
			if (trQuestVarGet("p"+p+"done") == 0) {
				if (trPlayerUnitCountSpecific(p, "Nidhogg") > 0) {
					if (yFindLatestReverse("nidhoggNext", "Nidhogg", p) > 0) {
						trUnitDestroy();
					}
					trQuestVarSet("p"+p+"done", 1);
				}
				if (1*trQuestVarGet("p"+p+"click") == LEFT_CLICK) {
					unit = -1;
					for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
						yDatabaseNext("p"+p+"hand");
						if (zDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos") < 4) {
							unit = yGetPointer("p"+p+"hand");
							break;
						}
					}
					if (unit > -1) {
						if (trCurrentPlayer() == p) {
							displayCardKeywordsAndDescription(yGetUnitAtIndex("p"+p+"hand", unit));
							trSoundPlayFN("ui\scroll.wav","1",-1,"","");
						}
						ySetPointer("p"+p+"hand", unit);
						ySetVar("p"+p+"hand", "mulligan", 1 - yGetVar("p"+p+"hand", "mulligan"));
						trUnitSelectClear();
						trUnitSelectByID(1*yGetVar("p"+p+"hand", "pos"));
						if (yGetVar("p"+p+"hand", "mulligan")  == 0) {
							trMutateSelected(kbGetProtoUnitID("Garrison Flag Sky Passage"));
						} else {
							trMutateSelected(kbGetProtoUnitID("Victory Marker"));
						}
					}
				}
			}
			trQuestVarSet("p"+p+"click", 0);
		}
	}
}

rule match_03_replace
highFrequency
inactive
{
	trCounterAbort("counter");
	for(p=2; >0) {
		trPlayerKillAllGodPowers(p);
		trTechGodPower(p, "rain", 1);
		updateHandPlayable(p);
		for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
			yDatabaseNext("p"+p+"hand", true);
			if (yGetVar("p"+p+"hand", "mulligan") == 1) {
				addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("p"+p+"hand", "proto")), mGetVarByQV("p"+p+"hand", "spell"));
				trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") + 1);
				trVectorSetUnitPos("pos", "p"+p+"hand");
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trArmyDispatch("1,10","Dwarf",1,trQuestVarGet("posx"),0,trQuestVarGet("posz"),0, true);
				trUnitSelectClear();
				trArmySelect("1,10");
				trUnitChangeProtoUnit("Hero Death");
			} else {
				transferUnit("temp", "p"+p+"hand");
			}
		}
		yClearDatabase("p"+p+"hand");
		for(x=yGetDatabaseCount("temp"); >0) {
			yDatabaseNext("temp");
			transferUnit("p"+p+"hand", "temp");
		}
		yClearDatabase("temp");
		shuffleDeck(p);
	}
	trQuestVarSet("activePlayer", 2);
	xsEnableRule("turn_00_start");
	xsDisableRule("match_03_replace");
}

rule turn_00_start
highFrequency
inactive
{
	if (yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + trQuestVarGet("lightningActivate") - trQuestVarGet("lightningPop") == 0) {

		trQuestVarSet("turnEnd", 0);
		trSoundPlayFN("fanfare.wav","1",-1,"","");


		int p = 3 - trQuestVarGet("activePlayer");

		trPlayerKillAllGodPowers(p);
		trTechGodPower(p, "create gold", 1);
		trTechGodPower(p, "animal magnetism", 1);
		trTechGodPower(p, "rain", 1);
		trTechGodPower(p, "nidhogg", 1);
		
		if(Multiplayer == false && p == 2){
			trQuestVarSet("botPhase", 0);
			trQuestVarSet("botThinking", 0);
			xsEnableRule("Bot1");
		}

		xsSetContextPlayer(p);
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (mGetVarByQV("allUnits", "player") == p) {
				if (mGetVarByQV("allUnits", "stunTime") > 0) {
					mSetVarByQV("allUnits", "stunTime", mGetVarByQV("allUnits", "stunTime") - 1);
					if (mGetVarByQV("allUnits", "stunTime") == 0) {
						mSetVarByQV("allUnits", "action", ACTION_READY);
						trUnitSelectClear();
						trUnitSelect(""+1*mGetVarByQV("allUnits", "stunSFX"), true);
						trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
					} else {
						mSetVarByQV("allUnits", "action", ACTION_STUNNED);
					}
				} else {
					mSetVarByQV("allUnits", "action", ACTION_READY);
				}
				if (HasKeyword(REGENERATE, 1*mGetVarByQV("allUnits", "keywords"))) {
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
					trDamageUnitPercent(-100);
					ySetVar("allUnits", "health", 
						xsMax(mGetVarByQV("allUnits", "health"), kbUnitGetCurrentHitpoints(kbGetBlockID(""+1*trQuestVarGet("allUnits"), true))));
				}
			} else {
				mSetVarByQV("allUnits", "action", ACTION_DONE);
			}
		}


		if (p == 1) {
			trQuestVarSet("maxMana", trQuestVarGet("maxMana") + 1);
		}
		trQuestVarSet("p"+p+"mana", trQuestVarGet("maxMana"));
		trQuestVarSet("activePlayer", p);
		trQuestVarSet("p"+p+"click", 0);
		highlightReady(100);

		trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") + 1);

		if(Multiplayer){
			trCounterAddTime("turnTimer", 121, 1, "Turn end", -1);	
		}
		trCounterAddTime("mana", -1, -9999999, 
			"<color={Playercolor("+p+")}>Mana: "+1*trQuestVarGet("p"+p+"mana") + "/" + 1*trQuestVarGet("maxMana"));

		if (trQuestVarGet("activePlayer") == 1) {
			trOverlayTextColour(0, 0, 255);
		} else {
			trOverlayTextColour(255,0,0);
		}

		xsEnableRule("gameplay_01_select");
		xsEnableRule("turn_01_end");
		xsDisableRule("turn_00_start");
	}
}


rule turn_01_end
highFrequency
inactive
{
	int p = trQuestVarGet("activePlayer");
	if ((trPlayerUnitCountSpecific(p, "Nidhogg") > 0) || (Multiplayer && (trTime() > cActivationTime + 120))) {
		if (yFindLatestReverse("nidhoggNext", "Nidhogg", p) > 0) {
			trUnitDestroy();
		}
		ChatLogShow();
		trQuestVarSet("p"+p+"manaflow", trQuestVarGet("p"+p+"mana"));
		trQuestVarSet("p"+p+"mana", -1);
		updateHandPlayable(p);
		
		trPlayerKillAllGodPowers(p);
		trTechGodPower(p, "rain", 1);
		trCounterAbort("mana");
		trCounterAbort("turnTimer");

		trQuestVarSet("turnEnd", 1);

		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (mGetVarByQV("allUnits", "victory") > 0) {
				mSetVarByQV("allUnits", "attack", mGetVarByQV("allUnits", "attack") - mGetVarByQV("allUnits", "victory"));
				mSetVarByQV("allUnits", "victory", 0);
				if (mGetVarByQV("allUnits", "victoryAmbush") == 0) {
					mSetVarByQV("allUnits", "keywords", ClearBit(1*mGetVarByQV("allUnits", "keywords"), AMBUSH));
				}
				mSetVarByQV("allUnits", "victoryAmbush", 0);
			}
		}

		// Discard fleeting cards
		bool fleeting = false;
		int type = 0;
		yDatabasePointerDefault("p"+p+"hand");
		for (x=yGetDatabaseCount("p"+p+"hand"); >0) {
			yDatabaseNext("p"+p+"hand");
			if (HasKeyword(FLEETING, 1*mGetVarByQV("p"+p+"hand", "keywords"))) {
				trVectorSetUnitPos("pos", "p"+p+"hand");
				fleeting = true;
				trUnitSelectClear();
				trUnitSelectByID(1*yGetVar("p"+p+"hand", "pos"));
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("p"+p+"hand"), true);
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trArmyDispatch("1,10","Dwarf",1,trQuestVarGet("posx"),0,trQuestVarGet("posz"),0, true);
				trUnitSelectClear();
				trArmySelect("1,10");
				trUnitChangeProtoUnit("Hero Death");
				if (mGetVarByQV("p"+p+"hand", "spell") == SPELL_NONE) {
					type = mGetVarByQV("p"+p+"hand", "proto");
					ChatLog(p, "Discarded " + trStringQuestVarGet("card_" + type + "_name"));
				} else {
					type = mGetVarByQV("p"+p+"hand", "spell");
					ChatLog(p, "Discarded " + trStringQuestVarGet("spell_" + type + "_name"));
				}
				removeUnit("p"+p+"hand");
			}
		}
		if (fleeting && trCurrentPlayer() == p) {
			trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
		}
		trDelayedRuleActivation("turn_00_start");
		xsDisableRule("turn_01_end");
	}
}
