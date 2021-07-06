rule match_test
highFrequency
active
runImmediately
{
	for(x=3; >0) {
		for(p=2; >0) {
			addCardToDeck(p, "Swordsman");
			addCardToDeck(p, "Maceman");
			addCardToDeck(p, "Skraeling");
			addCardToDeck(p, "Slinger");
			addCardToDeck(p, "Toxotes");
			addCardToDeck(p, "Raiding Cavalry");
			addCardToDeck(p, "Trident Soldier");
			addCardToDeck(p, "Jarl");
			addCardToDeck(p, "Behemoth");
			addCardToDeck(p, "Wadjet");
			addCardToDeck(p, "Avenger");
			addCardToDeck(p, "Archer Atlantean Hero");
		}
	}
	xsDisableRule("match_test");
}

rule match_00_start
highFrequency
active
{
	trQuestVarSet("p1commander", trGetNextUnitScenarioNameNumber());
	addCardToHand(1, kbGetProtoUnitID("Hero Greek Jason"), SPELL_COMMANDER);


	trQuestVarSet("p2commander", trGetNextUnitScenarioNameNumber());
	addCardToHand(2, kbGetProtoUnitID("Hero Greek Jason"), SPELL_COMMANDER);

	trTechGodPower(0, "spy", 2);
	for(p=2; >0) {

		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("p"+p+"commander"), true);
		trTechInvokeGodPower(0, "spy", xsVectorSet(1,1,1), xsVectorSet(1,1,1));

		yDatabaseNext("p"+p+"hand");
		teleportToTile("p"+p+"hand", 1*trQuestVarGet("p"+p+"startTile"));
		transferUnit("allUnits", "p"+p+"hand");
		yClearDatabase("p"+p+"hand");
		trQuestVarSet("p"+p+"drawCards", 4);


		zSetVarByIndex("tiles", "occupied", 1*trQuestVarGet("p"+p+"startTile"), TILE_OCCUPIED);

		shuffleDeck(p);
	}

	// Ravens

	trUnitSelectClear();
	trUnitSelectByID(870);
	trMutateSelected(kbGetProtoUnitID("Raven"));
	trSetSelectedScale(0,0,0);

	trUnitSelectClear();
	trUnitSelectByID(872);
	trMutateSelected(kbGetProtoUnitID("Raven"));
	trSetSelectedScale(0,0,0);

	uiFindType("Raven");
	uiCreateNumberGroup(1);

	trQuestVarSet("p1raven", 870);
	trQuestVarSet("p1block", 869);
	trQuestVarSet("p2raven", 872);
	trQuestVarSet("p2block", 871);
	
	uiClearSelection();

	xsDisableRule("match_00_start");
	xsEnableRule("match_01_mulliganStart");
	xsEnableRule("gameplay_toggle_camera");
}

rule match_01_mulliganStart
highFrequency
inactive
{
	if (trQuestVarGet("p1drawCards") == 0 && trQuestVarGet("p2drawCards") == 0) {
		unitTransform("Spy Eye", "Hero Birth");
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

		trCounterAddTime("counter", 21, 1, "Mulligan phase",-1);

		xsEnableRule("match_02_mulligan");
		xsDisableRule("match_01_mulliganStart");
	}
}

rule match_02_mulligan
highFrequency
inactive
{
	if (trQuestVarGet("p1done") + trQuestVarGet("p2done") == 2 || trTime() > cActivationTime + 20) {
		xsEnableRule("match_03_replace");
		xsDisableRule("match_02_mulligan");
	} else {
		int unit = -1;
		for(p=2; >0) {
			if (trQuestVarGet("p"+p+"done") == 0) {
				switch(1*trQuestVarGet("p"+p+"click"))
				{
					case LEFT_CLICK:
					{
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
								displayCardKeywordsAndDescription("p"+p+"hand", unit);
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
					case RIGHT_CLICK:
					{
						trQuestVarSet("p"+p+"done", 1);
						if (trCurrentPlayer() == p) {
							trSoundPlayFN("favordump.wav","1",-1,"","");
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
		updateHandPlayable(p);
		for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
			yDatabaseNext("p"+p+"hand", true);
			if (yGetVar("p"+p+"hand", "mulligan") == 1) {
				trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") + 1);
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
	}
	trQuestVarSet("activePlayer", 2);
	xsEnableRule("turn_00_start");
	xsDisableRule("match_03_replace");
}

rule turn_00_start
highFrequency
inactive
{
	if (trQuestVarGet("attacking") == 0) {

		trQuestVarSet("turnEnd", 0);
		trSoundPlayFN("fanfare.wav","1",-1,"","");


		int p = 3 - trQuestVarGet("activePlayer");

		xsSetContextPlayer(p);
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (yGetVar("allUnits", "player") == p) {
				ySetVar("allUnits", "action", ACTION_READY);
				if (HasKeyword(REGENERATE, 1*yGetVar("allUnits", "keywords"))) {
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
					trDamageUnitPercent(-100);
					ySetVar("allUnits", "health", 
						xsMax(yGetVar("allUnits", "health"), kbUnitGetCurrentHitpoints(kbGetBlockID(""+1*trQuestVarGet("allUnits"), true))));
				}
			} else {
				ySetVar("allUnits", "action", ACTION_DONE);
			}
		}


		if (p == 1) {
			trQuestVarSet("maxMana", trQuestVarGet("maxMana") + 1);
		}
		trQuestVarSet("p"+p+"mana", trQuestVarGet("maxMana"));
		trQuestVarSet("activePlayer", p);
		trQuestVarSet("p"+p+"click", 0);

		trTechGodPower(p, "rain", 1);

		trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") + 1);

		trCounterAddTime("turnTimer", 91, 1, "Turn end", -1);
		trCounterAddTime("mana", -1, -91, 
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
	if (trCheckGPActive("rain", p) == true || trTime() > cActivationTime + 90) {
		trQuestVarSet("p"+p+"manaflow", trQuestVarGet("p"+p+"mana"));
		
		trPlayerKillAllGodPowers(p);
		trTechGodPower(p, "vision", 1);
		trTechGodPower(p, "animal magnetism", 1);
		trCounterAbort("turnTimer");

		trQuestVarSet("turnEnd", 1);
		trDelayedRuleActivation("turn_00_start");
		xsDisableRule("turn_01_end");
	}
}
