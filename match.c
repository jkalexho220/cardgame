

rule match_00_start
highFrequency
inactive
{
	trTechGodPower(0, "spy", 2);
	int commander = 0;
	for(p=2; >0) {
		commander = CommanderToProtounit(1*trQuestVarGet("p"+p+"commanderType"));
		trQuestVarSet("p"+p+"commander", summonAtTile(1*trQuestVarGet("p"+p+"startTile"), p, commander));
		mSetVarByQV("p"+p+"commander", "spell", SPELL_COMMANDER);
		mSetVarByQV("p"+p+"commander", "action", ACTION_DONE);
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("p"+p+"commander"), true);
		spyEffect("Healing SFX");
		
		trQuestVarSet("p"+p+"drawCards", 4);
		zSetVarByIndex("tiles", "occupant", 1*trQuestVarGet("p"+p+"startTile"), 1*trQuestVarGet("p"+p+"commander"));
		
		shuffleDeck(p);
		
		trQuestVarSet("p"+p+"defeated", 0);
		if (trQuestVarGet("p"+p+"commanderType") == COMMANDER_GOD) {
			zBankInit("p"+p+"handPos", 861 + p * 15, 15);
			trQuestVarSet("p"+p+"maxHandSize", 15);
		} else {
			trQuestVarSet("p"+p+"maxHandSize", 10);
		}

		trQuestVarSet("p"+p+"lastProto", kbGetProtoUnitID("Minion"));
	}
	// Ravens
	trQuestVarSet("p1block", 869);
	trQuestVarSet("p2block", 871);
	trQuestVarSet("maxMana", 0);
	
	xsDisableRule("match_00_start");
	xsEnableRule("match_01_mulliganStart");
	xsEnableRule("gameplay_toggle_camera");
}

rule match_01_mulliganStart
highFrequency
inactive
{
	if (trQuestVarGet("p1drawCards") + trQuestVarGet("p2drawCards") == 0) {
		trTechGodPower(1, "rain", 1);
		trTechGodPower(2, "rain", 1);
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
		trMessageSetText("Left click to choose cards to mulligan. Enter to finish.",-1);
		
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
	if ((trQuestVarGet("p1done") + trQuestVarGet("p2done") == 2) || (Multiplayer  && (trTime() > cActivationTime + 20))) {
		xsEnableRule("match_03_replace");
		xsDisableRule("match_02_mulligan");
	} else {
		int unit = -1;
		for(p=2; >0) {
			if (trQuestVarGet("p"+p+"done") == 0) {
				if (trCheckGPActive("rain", p)) {
					trQuestVarSet("p"+p+"done", 1);
				}
				if (1*trQuestVarGet("p"+p+"click") == LEFT_CLICK) {
					unit = -1;
					for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
						yDatabaseNext("p"+p+"hand");
						if (trDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos") < 4) {
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
		updateHandPlayable(p);
		for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
			yDatabaseNext("p"+p+"hand", true);
			if (yGetVar("p"+p+"hand", "mulligan") == 1) {
				addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("p"+p+"hand", "proto")), mGetVarByQV("p"+p+"hand", "spell"));
				trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") + 1);
				trVectorSetUnitPos("pos", "p"+p+"hand");
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("pos"),0,trVectorQuestVarGetZ("pos"),0, true);
				trUnitSelectClear();
				trArmySelect("1,10");
				trUnitChangeProtoUnit("Hero Death");
				zSetVarByIndex("p"+p+"handPos", "occupied", 1*yGetVar("p"+p+"hand", "pos"), 0);
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
	xsEnableRule("gameplay_select_show_keywords");
	trQuestVarSet("activePlayer", 2);
	xsEnableRule("turn_00_start");
	xsDisableRule("match_03_replace");
}

rule turn_00_start
highFrequency
inactive
{
	if ((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + trQuestVarGet("bossSpell") + trQuestVarGet("chainReactionDeath") == 0) && (trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) {
		int p = trQuestVarGet("activePlayer");
		if (trQuestVarGet("p"+p+"borrowedTime") > 0) {
			trQuestVarSet("p"+p+"borrowedTime", trQuestVarGet("p"+p+"borrowedTime") - 1);
		} else {
			p = 3 - p;
			if ((p == 1) && (trQuestVarGet("maxMana") < 10)) {
				trQuestVarSet("maxMana", trQuestVarGet("maxMana") + 1);
			}
		}
		trQuestVarSet("activePlayer", p);
		trQuestVarSet("turnEnd", 0);
		trPlayerKillAllGodPowers(p);
		yClearDatabase("turnStart");
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
					mSetVarByQV("allUnits", "health", mGetVarByQV("allUnits", "maxHealth"));
				}
				// Start of turn effects
				yAddToDatabase("turnStart", "allUnits");
			} else {
				mSetVarByQV("allUnits", "action", ACTION_DONE);
			}
		}
		
		/*
		Guardian of the Sea expires
		*/
		if (trQuestVarGet("p"+p+"guardianOfTheSea") == 1) {
			trQuestVarSet("p"+p+"guardianOfTheSea", 0);
			mSetVarByQV("p"+p+"commander", "keywords", ClearBit(1*mGetVarByQV("p"+p+"commander", "keywords"), ARMORED));
		}
		trQuestVarSet("turnStartDelay", trTimeMS() + 500);
		xsEnableRule("turn_01_resolve_turn_start");
		xsDisableRule("turn_00_start");
	}
}


rule turn_01_resolve_turn_start
highFrequency
inactive
{
	if (trTimeMS() > trQuestVarGet("turnStartDelay")) {
		int p = trQuestVarGet("activePlayer");
		int tile = 0;
		bool delay = false;
		for(x=yGetDatabaseCount("turnStart"); >0) {
			yDatabaseNext("turnStart");
			yRemoveFromDatabase("turnStart");
			if(OnTurnStart(1*trQuestVarGet("turnStart")) == true){
				delay = true;
				break;
			}
		}
		// electroballs
		for(x=yGetDatabaseCount("electroballs"); >0) {
			yDatabaseNext("electroballs");
			if (yGetVar("electroballs", "player") == p) {
				tile = yGetVar("electroballs", "tile");
				if (zGetVarByIndex("tiles", "occupant", tile) > 0) {
					damageUnit(1*zGetVarByIndex("tiles", "occupant", tile), 1);
				}
			}
		}
		// Leo discount
		for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
			yDatabaseNext("p"+p+"hand");
			if (kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet("p"+p+"hand"))) == kbGetProtoUnitID("Golden Lion")) {
				mSetVarByQV("p"+p+"hand", "cost", xsMax(0, mGetVarByQV("p"+p+"hand", "cost") - 1));
			}
		}
		if(delay){
			trQuestVarSet("turnStartDelay", trTimeMS() + 500);
		} else {
			trSoundPlayFN("fanfare.wav","1",-1,"","");
			
			trTechGodPower(p, "create gold", 1);
			trTechGodPower(p, "animal magnetism", 1);
			trTechGodPower(p, "rain", 1);
			
			if(Multiplayer){
				trCounterAddTime("turnTimer", 121, 1, "Turn end", -1);
			} else if (p == 2) {
				trQuestVarSet("botPhase", 0);
				trQuestVarSet("botThinking", 0);
				xsEnableRule("Bot_00_turn_start");
			}
			
			
			
			trQuestVarSet("p"+p+"mana", xsMax(0, trQuestVarGet("maxMana") - trQuestVarGet("p"+p+"manaTax")));
			trQuestVarSet("p"+p+"manaTax", 0);

			trQuestVarSet("p"+p+"click", 0);
			highlightReady(100);
			
			trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") + 1);
			
			updateMana();
			removeDeadUnits();
			updateAuras();
			xsEnableRule("gameplay_01_select");
			xsEnableRule("turn_02_end");
			xsDisableRule("turn_01_resolve_turn_start");
		}
	}
	
}


rule turn_02_end
highFrequency
inactive
{
	int p = trQuestVarGet("activePlayer");
	if ((trCheckGPActive("rain", p) || (Multiplayer && (trTime() > cActivationTime + 120))) && (trQuestVarGet("castDone") != CASTING_DONE)) {
		ChatLogShow();
		trQuestVarSet("p"+p+"manaflow", trQuestVarGet("p"+p+"mana") + trQuestVarGet("p"+p+"extraManaflow"));
		trQuestVarSet("p"+p+"mana", -1);
		trQuestVarSet("p"+p+"extraManaflow", 0);
		updateHandPlayable(p);
		
		trPlayerKillAllGodPowers(p);
		trCounterAbort("mana");
		trCounterAbort("handAndDeck");
		trCounterAbort("turnTimer");
		
		trQuestVarSet("turnEnd", 1);
		
		trQuestVarSet("apocalypse", trQuestVarGet("apocalypse") - 1);
		if (trQuestVarGet("apocalypse") == 0) {
			musicToggleBattleMode();
		}
		
		/*
		End of turn effects
		*/
		trQuestVarSet("mindflayerDamage", trCountUnitsInArea("128",p,"Argus",45));
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
			if (HasKeyword(DECAY, 1*mGetVarByQV("allUnits", "keywords"))) {
				if (mGetVarByQV("allUnits", "player") == p) {
					damageUnit(1*trQuestVarGet("allUnits"), 1);
				}
				damageUnit(1*trQuestVarGet("allUnits"), trQuestVarGet("mindflayerDamage"));
			}
			
			if (mGetVarByQV("allUnits", "proto") == kbGetProtoUnitID("Hero Chinese Immortal")){
				if(mGetVarByQV("allUnits", "player") == p){
					mSetVarByQV("allUnits", "range", 2);
				} else {
					mSetVarByQV("allUnits", "range", 1);
				}
			}
			
			if (1*mGetVarByQV("allUnits", "player") == p) {
				switch(1*mGetVarByQV("allUnits", "proto"))
				{
					case kbGetProtoUnitID("Guild"):
					{
						if (yGetDatabaseCount("p"+p+"hand") < 10) {
							addCardToHand(p, kbGetProtoUnitID("Automaton SPC"));
						}
						damageUnit(1*trQuestVarGet("allUnits"), 2);
					}
					case kbGetProtoUnitID("Argus"):
					{
						trUnitSelectClear();
						trUnitSelect(""+1*trQuestVarGet("allUnits"));
						trUnitOverrideAnimation(40,0,false,true,-1);
					}
					case kbGetProtoUnitID("Petsuchos"):
					{
						mSetVarByQV("allUnits", "range", 0);
					}
				}
			}
		}
		
		mSetVarByQV("p"+p+"commander", "attack", mGetVarByQV("p"+p+"commander", "attack") - trQuestVarGet("p"+p+"yeebBonus"));
		trQuestVarSet("p"+p+"yeebbonus", 0);
		
		/*
		Meteors
		*/
		trQuestVarSet("sound", 0);
		for(x=yGetDatabaseCount("meteors"); >0) {
			yDatabaseNext("meteors", true);
			ySetVar("meteors", "time", yGetVar("meteors", "time") - 1);
			if (yGetVar("meteors", "time") == 0) {
				trQuestVarSet("sound", 1);
				trUnitChangeProtoUnit("Meteor");
				deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("meteors", "tile"));
				trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVar("meteors", "tile")));
				for(y=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "tile") == yGetVar("meteors", "tile")) {
						damageUnit(1*trQuestVarGet("allUnits"), 6 + trQuestVarGet("p"+(3-p)+"spellDamage"));
					} else if (trDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit(1*trQuestVarGet("allUnits"), 2 + trQuestVarGet("p"+(3-p)+"spellDamage"));
					}
				}
				yRemoveFromDatabase("meteors");
			}
		}
		
		if (trQuestVarGet("sound") == 1) {
			trSoundPlayFN("meteorbighit.wav","1",-1,"","");
			trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
		}
		
		removeDeadUnits();
		
		// Discard fleeting cards
		bool fleeting = false;
		int type = 0;
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
				trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("pos"),0,trVectorQuestVarGetZ("pos"),0, true);
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
				zSetVarByIndex("p"+p+"handPos", "occupied", 1*yGetVar("p"+p+"hand", "pos"), 0);
				yRemoveFromDatabase("p"+p+"hand");
			}
		}
		if (fleeting && trCurrentPlayer() == p) {
			trSoundPlayFN("olympustemplesfx.wav","1",-1,"","");
		}
		trDelayedRuleActivation("turn_00_start");
		xsDisableRule("turn_02_end");
	}
}

rule match_end
highFrequency
inactive
{
	if (Multiplayer) {
		// multiplayer stuff
		map("mouse1down", "game", "uiSelectionButtonDown");
		map("mouse2up", "game", "");
		map("space", "game", "uiLookAtSelection");
		map("enter", "game", "gadgetReal(\"chatInput\") uiIgnoreNextKey");
	} else {
		xsEnableRule("MissionEnd");
	}
	xsDisableSelf();
}
