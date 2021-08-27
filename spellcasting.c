
const int CAST_UNIT = 0;
const int CAST_TARGET = 1;
const int CAST_SING = 2;
const int CAST_BACKSTAB = 3;
const int CAST_CONVERT = 4;

const int CAST_TILE = 10;
const int CAST_ADJACENT_TILE = 11;
const int CAST_DIRECTION = 12;
const int CAST_SUMMON_LOCATIONS = 13;

const int CASTING_NOTHING = 0;
const int CASTING_IN_PROGRESS = 1;
const int CASTING_DONE = 2;
const int CASTING_CANCEL = 3;


void castReset() {
	trQuestVarSet("castPush", 0);
	trQuestVarSet("castPop", 0);
	trQuestVarSet("castDone", CASTING_NOTHING);
}

/*
int p = the player of the unit being selected. 0 = any player
string qv = the name of the quest var to store the unit selected by the player

This function doesn't do anything on its own. It adds a selection request to the queue.
The spellcast_ set of triggers will process these requests one by one and store the results
in the quest vars.
*/
void castAddUnit(string qv = "", int p = 0, bool commander = true) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	if (commander) {
		trQuestVarSet("cast"+x+"commander", SPELL_COMMANDER);
	} else {
		trQuestVarSet("cast"+x+"commander", SPELL_NONE);
	}
	trQuestVarSet("cast"+x+"type", CAST_UNIT);
	trQuestVarSet("cast"+x+"player", p);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

void castAddBackstabUnit(string qv = "", int p = 0) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	
	trQuestVarSet("cast"+x+"type", CAST_BACKSTAB);
	trQuestVarSet("cast"+x+"player", p);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

void castAddSing(string qv = "", int p = 0) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	trQuestVarSet("cast"+x+"type", CAST_SING);
	trQuestVarSet("cast"+x+"player", p);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

void castAddConvertUnit(string qv = "", int p = 0) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	
	trQuestVarSet("cast"+x+"type", CAST_CONVERT);
	trQuestVarSet("cast"+x+"player", p);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

/*
qv = name of the quest var to store the selected tile
ghost = true if ignore impassable terrain
*/
void castAddTile(string qv = "", bool ghost = false) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	trQuestVarSet("cast"+x+"type", CAST_TILE);
	trStringQuestVarSet("cast"+x+"qv", qv);
	if (ghost) {
		trQuestVarSet("cast"+x+"terrain", 0);
	} else {
		trQuestVarSet("cast"+x+"terrain", 1);
	}
}

/*
qv = name of the quest var to store the selected tile
*/
void castAddSummonLocations(string qv = "") {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	trQuestVarSet("cast"+x+"type", CAST_SUMMON_LOCATIONS);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

/*
qv = name of the quest var to store the selected tile
src = name of quest var holding the unit at the center
*/
void castAddAdjacentTile(string qv = "", string src = "") {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	trQuestVarSet("cast"+x+"type", CAST_ADJACENT_TILE);
	trStringQuestVarSet("cast"+x+"qv", qv);
	trQuestVarSet("cast"+x+"unit", 1*trQuestVarGet(src));

}

/*
qv = name of the quest var to store the selected unit
attacker = name of quest var holding the index of the attacking unit. This will
only highlight targets that are within range of the attacker.
*/
void castAddTarget(string qv = "", string attacker = "") {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	trQuestVarSet("cast"+x+"type", CAST_TARGET);
	trStringQuestVarSet("cast"+x+"start", attacker);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

/*
qv = name of the quest var to store the selected tile
start = name of quest var holding the starting tile
unit = if set to true, start becomes the name of the quest var holding the index of the starting unit
in the allUnits database.
*/
void castAddDirection(string qv = "", string start = "", bool unit = false) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	trQuestVarSet("cast"+x+"type", CAST_DIRECTION);
	if (unit) {
		trQuestVarSet("cast"+x+"unit", 1);
	} else {
		trQuestVarSet("cast"+x+"unit", 0);
	}
	trStringQuestVarSet("cast"+x+"qv", qv);
	trStringQuestVarSet("cast"+x+"start", start);
}

/*
called after any of the castAddX functions above to attach a string to it
*/
void castInstructions(string inst = "") {
	int x = trQuestVarGet("castPush");
	trStringQuestVarSet("cast"+x+"instructions", inst);
}

void castStart() {
	trQuestVarSet("castDone", CASTING_IN_PROGRESS);
	xsEnableRule("spellcast_00_process");
}

void castRestoreWard() {
	for(x=yGetDatabaseCount("wardUnits"); >0) {
		yDatabaseNext("wardUnits");
		yAddToDatabase("allUnits", "wardUnits");
	}
	yClearDatabase("wardUnits");
}

void castEnd() {
	castRestoreWard();
	removeDeadUnits();
	updateAuras();
	xsEnableRule("gameplay_01_select");
	highlightReady(999999);
	int cost = 0;

	if (trQuestVarGet("selectedCard") >= 0) {
		int p = trQuestVarGet("activePlayer");
		int unit = yGetUnitAtIndex("p"+p+"hand", 1*trQuestVarGet("selectedCard"));
		trUnitSelectClear();
		trUnitSelect(""+unit);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		mSetVar(unit, "played", 0);
		cost = mGetVar(unit, "cost") - trQuestVarGet("p"+p+"spellDiscount");
		if (HasKeyword(OVERFLOW, 1*mGetVar(unit, "keywords"))) {
			cost = cost - trQuestVarGet("p"+p+"manaflow");
		}
		// if the commander is out reach
		if (trQuestVarGet("p"+p+"commanderType") == 4) {
			trQuestVarSet("p"+p+"extraManaflow", cost + trQuestVarGet("p"+p+"extraManaflow"));
		}
		trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") - xsMax(0, cost));
		updateMana();
		ySetPointer("p"+p+"hand", 1*trQuestVarGet("selectedCard"));
		yRemoveFromDatabase("p"+p+"hand");
		yRemoveUpdateVar("p"+p+"hand", "pos");

		updateHandPlayable(p);

		/*
		Effects that occur whenever a spell is cast
		*/
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits", true);
			if (mGetVarByQV("allUnits", "player") == p) {
				switch(1*mGetVarByQV("allUnits", "proto"))
				{
					case kbGetProtoUnitID("Swordsman Hero"):
					{
						spyEffect("Einheriar Boost SFX");
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
					}
					case kbGetProtoUnitID("Petsuchos"):
					{
						spyEffect("Einheriar Boost SFX");
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
					}
					case kbGetProtoUnitID("Hero Greek Bellerophon"):
					{
						if (mGetVarByQV("allUnits", "action") < ACTION_SLEEPING) {
							mSetVarByQV("allUnits", "action", ACTION_READY);
							deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
					case kbGetProtoUnitID("Pharaoh of Osiris"):
					{
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
						trQuestVarSet("p"+p+"yeebbonus", 1 + trQuestVarGet("p"+p+"yeebbonus"));
					}
				}
			}
		}
	}
	trQuestVarSet("castDone", CASTING_NOTHING);
}


rule spellcast_00_process
highFrequency
inactive
{
	if (trQuestVarGet("castPop") < trQuestVarGet("castPush")) {
		trQuestVarSet("castPop", trQuestVarGet("castPop") + 1);
		int x = trQuestVarGet("castPop");
		int p = trQuestVarGet("activePlayer");
		int tile = 0;
		yClearDatabase("castTargets");
		yClearDatabase("castTiles");
		if (trQuestVarGet("cast"+x+"type") < CAST_TILE) {
			trQuestVarSet("gameplayPhase", GAMEPLAY_SPELL_UNIT);
		} else {
			trQuestVarSet("gameplayPhase", GAMEPLAY_SPELL_TILE);
		}
		if (trCurrentPlayer() == p) {
			trMessageSetText(trStringQuestVarGet("cast"+x+"instructions"), -1);
		}
		switch(1*trQuestVarGet("cast"+x+"type"))
		{
			case CAST_UNIT:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
						if (mGetVarByQV("allUnits", "spell") <= trQuestVarGet("cast"+x+"commander")) {
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("allUnits"));
							yAddToDatabase("castTargets", "allUnits");
							if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
								trUnitHighlight(999999, false);
							}
						}
					}
				}
			}
			case CAST_SING:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
						if ((mGetVarByQV("allUnits", "action") >= ACTION_DONE) && (mGetVarByQV("allUnits", "action") < ACTION_SLEEPING)) {
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("allUnits"));
							yAddToDatabase("castTargets", "allUnits");
							if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
								trUnitHighlight(999999, false);
							}
						}
					}
				}
			}
			case CAST_CONVERT:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
						if (mGetVarByQV("allUnits", "cost") <= trQuestVarGet("p"+1*trQuestVarGet("activePlayer")+"manaflow")) {
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("allUnits"));
							yAddToDatabase("castTargets", "allUnits");
							if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
								trUnitHighlight(999999, false);
							}
						}
					}
				}
			}
			case CAST_BACKSTAB:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "player") == p) {
						if (trCountUnitsInArea(""+1*trQuestVarGet("allUnits"), p, "Unit", 8) > 1) {
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("allUnits"));
							yAddToDatabase("castTargets", "allUnits");
							if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
								trUnitHighlight(999999, false);
							}
						}
					}
				}
			}
			case CAST_TILE:
			{
				for (z=zGetBankCount("tiles"); >0) {
					zBankNext("tiles");
					if (zGetVar("tiles", "terrain") * trQuestVarGet("cast"+x+"terrain") == 0) {
						if (zGetVar("tiles", "ward") == 0) {
							yAddToDatabase("castTiles", "tiles");
							if (trCurrentPlayer() == p) {
								highlightTile(1*trQuestVarGet("tiles"), 999999);
							}
						}
					}
				}
			}
			case CAST_SUMMON_LOCATIONS:
			{
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "player") == p && HasKeyword(BEACON, 1*mGetVarByQV("allUnits", "keywords"))) {
						tile = mGetVarByQV("allUnits", "tile");
						findAvailableTiles(tile, 1, "castTiles");
					}
				}
				yDatabasePointerDefault("castTiles");
				for(x=yGetDatabaseCount("castTiles"); >0) {
					yDatabaseNext("castTiles");
					if (zGetVarByIndex("tiles", "ward", 1*trQuestVarGet("castTiles")) == 1) {
						yRemoveFromDatabase("castTiles");
					} else {
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("casttiles"), 999999);
						}
					}
				}
			}
			case CAST_ADJACENT_TILE:
			{
				tile = mGetVarByQV("cast"+x+"unit", "tile");
				findAvailableTiles(tile, 1, "castTiles", false);
				for(z=yGetDatabaseCount("castTiles"); >0) {
					yDatabaseNext("castTiles");
					if (zGetVarByIndex("tiles", "ward", 1*trQuestVarGet("castTiles")) == 1) {
						yRemoveFromDatabase("castTiles");
					} else {
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("casttiles"), 999999);
						}
					}
				}
			}
			case CAST_TARGET:
			{
				findTargets(1*trQuestVarGet(trStringQuestVarGet("cast"+x+"start")), "castTargets");
				trUnitSelectClear();
				yDatabaseSelectAll("castTargets");
				if (trCurrentPlayer() == p) {
					trUnitHighlight(999999, false);
				}
			}
			case CAST_DIRECTION:
			{
				if (trQuestVarGet("cast"+x+"unit") == 1) {
					trQuestVarSet("start", mGetVarByQV(trStringQuestVarGet("cast"+x+"start"), "tile"));
				} else {
					trQuestVarSet("start", trQuestVarGet(trStringQuestVarGet("cast"+x+"start")));
				}
				bool found = true;
				tile = 0;
				// For each direction...
				for(d=0; < zGetVarByIndex("tiles", "neighborCount", 1*trQuestVarGet("start"))) {
					trVectorSetUnitPos("pos", "start");
					trVectorQuestVarSet("target", kbGetBlockPosition(""+1*zGetVarByIndex("tiles", "neighbor"+d, 1*trQuestVarGet("start"))));
					trVectorQuestVarSet("step", zGetUnitVector("pos", "target", 6.0));
					trQuestVarSet("posx", trQuestVarGet("posx") + trQuestVarGet("stepx"));
					trQuestVarSet("posz", trQuestVarGet("posz") + trQuestVarGet("stepz"));
					tile = trQuestVarGet("start");
					found = true;
					while(found) {
						found = false;
						// Travel down the line and highlight tiles
						for(z=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
							trVectorQuestVarSet("current", kbGetBlockPosition(""+1*zGetVarByIndex("tiles", "neighbor"+z, tile)));
							if (zDistanceBetweenVectorsSquared("current", "pos") < 1) {
								tile = zGetVarByIndex("tiles", "neighbor"+z, tile);
								trQuestVarSet("currentTile", tile);
								yAddToDatabase("castTiles", "currentTile");
								trQuestVarSet("posx", trQuestVarGet("currentx") + trQuestVarGet("stepx"));
								trQuestVarSet("posz", trQuestVarGet("currentz") + trQuestVarGet("stepz"));
								if (trCurrentPlayer() == p) {
									highlightTile(tile, 999999);
								}
								found = true;
								break;
							}
						}
					}
				}
			}
		}
		xsEnableRule("spellcast_01_select");
	} else {
		trQuestVarSet("castDone", CASTING_DONE);
	}


	xsDisableRule("spellcast_00_process");
}

void spellcastClearHighlights(int x = 0) {
	/*
	castTargets can be either a tile or a unit.
	The behavior of this function differs based on type.
	*/
	if (trCurrentPlayer() == 1*trQuestVarGet("activePlayer")) {
		if (trQuestVarGet("cast"+x+"type") >= CAST_TILE) {
			for(z=yGetDatabaseCount("castTiles"); >0) {
				yDatabaseNext("castTiles");
				highlightTile(1*trQuestVarGet("castTiles"), 0.1);
			}
		} else {
			for (z=yGetDatabaseCount("castTargets"); >0) {
				yDatabaseNext("castTargets", true);
				trUnitHighlight(0.1, false);
			}
		}
	}
	
	yClearDatabase("castTargets");
}


rule spellcast_01_select
highFrequency
inactive
{
	int p = trQuestVarGet("activePlayer");
	int x = trQuestVarGet("castPop");
	if (trQuestVarGet("turnEnd") == 1) {
		spellcastClearHighlights(x);
		castReset();
		trQuestVarSet("castDone", CASTING_CANCEL);
	} else {
		switch(1*trQuestVarGet("p"+p+"click"))
		{
			case LEFT_CLICK:
			{
				bool selected = false;
				if (trQuestVarGet("cast"+x+"type") < CAST_TILE) {
					for(z=yGetDatabaseCount("castTargets"); >0) {
						yDatabaseNext("castTargets");
						
						if (zDistanceToVectorSquared("castTargets", "p"+p+"clickPos") < 8) {
							trQuestVarCopy(trStringQuestVarGet("cast"+x+"qv"), "castTargets");
							selected = true;
							break;
						}
					}
				} else {
					for(z=yGetDatabaseCount("castTiles"); >0) {
						yDatabaseNext("castTiles");
						
						if (zDistanceToVectorSquared("castTiles", "p"+p+"clickPos") < 8) {
							trQuestVarCopy(trStringQuestVarGet("cast"+x+"qv"), "castTiles");
							selected = true;
							break;
						}
					}
				}
				if (selected) {
					spellcastClearHighlights(x);
					trQuestVarSet("p"+p+"click", 0);
					xsEnableRule("spellcast_00_process");
					xsDisableRule("spellcast_01_select");
				} else {
					/*
					If the player selected another card in hand, we abort. Otherwise, we shame
					the player for making such a rookie mistake.
					We don't set click back to 0 if they selected another card in hand.
					*/
					for(z=yGetDatabaseCount("p"+p+"hand"); >0) {
						yDatabaseNext("p"+p+"hand");
						if (zDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos") < 2) {
							spellcastClearHighlights(x);
							castReset();
							trQuestVarSet("castDone", CASTING_CANCEL);
							xsEnableRule("gameplay_01_select");
							highlightReady(999999);
							xsDisableRule("spellcast_01_select");
							break;
						}
					}
					if (z == 0) {
						trQuestVarSet("p"+p+"click", 0);
						if (trCurrentPlayer() == p) {
							trSoundPlayFN("cantdothat.wav","1",-1,"","");
						}
					}
				}
			}
			case RIGHT_CLICK:
			{
				trQuestVarSet("p"+p+"click", 0);
				spellcastClearHighlights(x);
				castRestoreWard();
				castReset();
				trQuestVarSet("castDone", CASTING_CANCEL);
				xsEnableRule("gameplay_01_select");
				highlightReady(999999);
				xsDisableRule("spellcast_01_select");
			}
		}
	}
}

/*
Given an integer for a spell, prompt the player to select a target
and get ready to cast the spell.
card = the index of the card in hand that will be removed when the spell is cast. If -1, then no
card is removed.
*/
void chooseSpell(int spell = 0, int card = -1) {
	trQuestVarSet("currentSpell", spell);
	trQuestVarSet("selectedCard", card);
	// If the card is a spell
	if (card > -1) {
		yDatabasePointerDefault("allUnits");
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (HasKeyword(WARD, 1*mGetVarByQV("allUnits", "keywords"))) {
				yAddToDatabase("wardUnits", "allUnits");
				yRemoveFromDatabase("allUnits");
			}
		}
	}
	castReset();
	int p = trQuestVarGet("activePlayer");
	switch(spell)
	{
		case SPELL_SPARK:
		{
			castAddUnit("spellTarget", 0);
			castInstructions("Choose any unit. Right click to cancel.");
		}
		case SPELL_FOOD:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion to give +1 attack and health to.");
		}
		case SPELL_SING:
		{
			castAddSing("spellTarget", p);
			castInstructions("Choose an allied minion that has already acted. Right click to cancel.");
		}
		case SPELL_MAP:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
		}
		case SPELL_BACKSTAB:
		{
			castAddBackstabUnit("spellTarget", 3 - p);
			castInstructions("Choose an enemy that is adjacent to another enemy. Right click to cancel.");
		}
		case SPELL_DUEL:
		{
			castAddUnit("allyTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
			castAddUnit("enemyTarget", 3 - p, false);
			castInstructions("Choose an enemy minion. Right click to cancel.");
		}
		case SPELL_PARTY_UP:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_TEAMWORK:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy minion. Right click to cancel.");
		}
		case SPELL_DEFENDER:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
		}
		case SPELL_VICTORY:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right clickto cancel.");
		}
		case SPELL_WHIRLWIND:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
		}
		case SPELL_HEROIC:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
		}
		case SPELL_WOLF:
		{
			castAddAdjacentTile("spellTarget", "summonedUnit");
			castInstructions("Choose a tile to summon a 1|1 Loyal Wolf with Guard.");
		}
		case SPELL_PING:
		{
			castAddUnit("spellTarget", 0);
			castInstructions("Choose a unit to deal 1 damage to.");
		}
		case SPELL_FIRST_AID:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
			castAddAdjacentTile("tileTarget", "p"+p+"commander");
			castInstructions("Choose a tile to teleport it to. Right click to cancel.");
		}
		case SPELL_CLASS_TIME:
		{
			castAddTile("spellTile", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_SNIPE:
		{
			castAddUnit("spellShooter", p, true);
			castInstructions("Choose an allied minion. Right click to cancel.");
			castAddTarget("spellTarget", "spellShooter");
			castInstructions("Choose an enemy within range to attack. Right click to cancel.");
		}
		case SPELL_EXPLOSION:
		{
			castAddTile("spellTarget", true);
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_DOUBLEBLAST:
		{
			castAddUnit("spellTarget1", 3 - p, true);
			castInstructions("Choose the first target. Right click to cancel.");
			castAddUnit("spellTarget2", 3 - p, true);
			castInstructions("Choose the second target. Right click to cancel.");
		}
		case SPELL_ELECTROSURGE:
		{
			castAddUnit("spellTarget", 3 - p, true);
			castInstructions("Choose an enemy. Right click to cancel.");
		}
		case SPELL_RUNE_OF_FLAME:
		{
			castAddSummonLocations("spellTarget");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_RUNE_OF_ICE:
		{
			castAddSummonLocations("spellTarget");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_FIRE_AND_ICE:
		{
			castAddSummonLocations("spellTargetFire");
			castInstructions("Choose a tile to summon the Blaze Elemental. Right click to cancel.");
			castAddSummonLocations("spellTargetIce");
			castInstructions("Choose a tile to summon the Frost Elemental. Right click to cancel.");
		}
		case SPELL_VALKYRIE_HEAL:
		{
			castAddUnit("spellTarget", p);
			castInstructions("Choose an ally to restore 3 health to.");
		}
		case SPELL_COPY_HOMEWORK:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_METEOR:
		{
			castAddTile("spellTarget", true);
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_FINAL_EXAM:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_SHAPESHIFT:
		{
			castAddUnit("transformTarget", 0, false);
			castInstructions("Choose a minion to transform.");
			castAddUnit("copyTarget", 0, false);
			castInstructions("Choose a minion to copy.");
		}
		case SPELL_APOCALYPSE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_MIRROR_IMAGE:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a minion. Right click to cancel.");
		}
		case SPELL_MEDUSA_STUN:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy to stun.");
		}
		case SPELL_LAMPADES_CONVERT:
		{
			castAddConvertUnit("spellTarget", 3 - p);
			castInstructions("Choose an enemy that costs {Manaflow} or less to convert.");
		}
		case SPELL_WATER_CANNON:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose a unit. Right click to cancel.");
			castAddDirection("spellDirection", "spellTarget", true);
			castInstructions("Choose a direction. Right click to cancel.");
		}
		case SPELL_RUNE_OF_WATER:
		{
			castAddSummonLocations("spellTarget");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_TIDAL_WAVE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_FLUSH:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_DEEP_DIVE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_SEA_EMBRACE:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
		}
		case SPELL_TELETIDE:
		{
			castAddUnit("spellTarget", p, true);
			castInstructions("Choose an allied minion. Right click to cancel.");
			castAddTile("spellDestination", false);
			castInstructions("Choose a tile to teleport it to. Right click to cancel.");
		}
		case SPELL_GUARDIAN_OF_SEA:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_WRATH_OF_SEA:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_CLEANSING_WATERS:
		{
			castAddTile("spellTarget", true);
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_DROWN:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a minion. Right click to cancel.");
		}
		case SPELL_DEMON_EAT:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose a minion to devour.");
		}
		case SPELL_SCORPION_STING:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a minion to give Decay to.");
		}
		case SPELL_WORLD_SPLITTER:
		{
			// If commander is Zenophobia
			if (trQuestVarGet("p"+p+"commanderType") == 10) {
				castAddUnit("spellTarget", p, true);
				castInstructions("Choose an ally. Right click to cancel.");
			} else {
				castAddUnit("spellTarget", p, false);
				castInstructions("Choose a minion. Right click to cancel.");
			}
			castAddDirection("spellDirection", "spellTarget", true);
			castInstructions("Choose a direction. Right click to cancel.");
		}
		case SPELL_SOUL_SIPHON:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
		}
		case SPELL_BLOOD_PRICE:
		{
			castAddUnit("allyTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
			castAddUnit("enemyTarget", 3-p, true);
			castInstructions("Choose an enemy. Right click to cancel.");
		}
		case SPELL_DEATH_APPROACHES:
		{
			castAddAdjacentTile("spellTarget", "p"+(3-p)+"commander");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_DOOM:
		{
			castAddUnit("spellTarget", 0, true);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_SHADOWSTEP:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied minion. Right click to cancel.");
		}
		case SPELL_FINAL_FRENZY:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a minion. Right click to cancel.");
		}
		case SPELL_CORPSE_PARTY:
		{
			castAddSummonLocations("spellTarget1");
			castInstructions("Choose a tile (1/3). Right click to cancel.");
			castAddSummonLocations("spellTarget1");
			castInstructions("Choose a tile (2/3). Right click to cancel.");
			castAddSummonLocations("spellTarget1");
			castInstructions("Choose a tile (3/3). Right click to cancel.");
		}
		case SPELL_UNDEATH:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
	}
	castStart();
	xsEnableRule("spell_cast");
}

rule spell_cast
highFrequency
inactive
{
	if (trQuestVarGet("turnEnd") == 1) {
		xsDisableRule("spell_cast");
	} else if (trQuestVarGet("castDone") == CASTING_DONE) {
		xsDisableRule("spell_cast");
		castRestoreWard();
		int spell = trQuestVarGet("currentspell");
		bool done = true;
		int activeUnit = 0;
		int target = 0;
		int tile = 0;
		int p = trQuestVarGet("activePlayer");
		int proto = 0;
		float dist = 0;
		int neighbor = 0;
		trSoundPlayFN("godpower.wav","1",-1,"","");
		bool battlecry = false;
		trQuestVarSet("p"+p+"spellDamage", trCountUnitsInArea("128",p,"Oracle Scout",45));
		switch(spell)
		{
			case SPELL_SPARK:
			{
				damageUnit(1*trQuestVarGet("spellTarget"), 1 + trQuestVarGet("p"+p+"spellDamage"));
				deployAtTile(0, "Tartarian Gate flame", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_BACKSTAB:
			{
				damageUnit(1*trQuestVarGet("spellTarget"), 2 + trQuestVarGet("p"+p+"spellDamage"));
				deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("spellTarget", "tile"));
				deployAtTile(0, "Hero Birth", 1*mGetVarByQV("spellTarget", "tile"));
				trSoundPlayFN("tributereceived.wav","1",-1,"","");
			}
			case SPELL_FOOD:
			{
				battlecry = true;
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "attack", 1 + mGetVar(target, "attack"));
				mSetVar(target, "health", 1 + mGetVar(target, "health"));
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
				trSoundPlayFN("colossuseat.wav","1",-1,"","");
				trSoundPlayFN("researchcomplete.wav","1",-1,"","");
				trUnitSelectClear();
				trUnitSelect(""+target);
				spyEffect("Einheriar Boost SFX");
			}
			case SPELL_SING:
			{
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "action", ACTION_READY);
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
				trSoundPlayFN("restorationbirth.wav","1",-1,"","");
			}
			case SPELL_MAP:
			{
				trSoundPlayFN("researchcomplete.wav","1",-1,"","");
				trSoundPlayFN("ui\scroll.wav","1",-1,"","");
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "speed", 1 + mGetVar(target, "speed"));
				mSetVar(target, "keywords", SetBit(1*mGetVar(target, "keywords"), ETHEREAL));
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
			}
			case SPELL_DUEL:
			{
				trSoundPlayFN("specialist.wav","1",-1,"","");
				activeUnit = trQuestVarGet("allyTarget");
				target = trQuestVarGet("enemyTarget");
				target = checkGuard(target);

				startAttack(activeUnit, target, HasKeyword(AMBUSH, 1*mGetVar(activeUnit, "keywords")), true);
				startAttack(target, activeUnit, false, true);
				done = false;
				xsEnableRule("spell_attack_complete");
			}
			case SPELL_PARTY_UP:
			{
				trSoundPlayFN("barracks.wav","1",-1,"","");
				xsEnableRule("spell_party_up_activate");
			}
			case SPELL_TEAMWORK:
			{
				trSoundPlayFN("specialist.wav","1",-1,"","");
				trSoundPlayFN("battlecry2.wav","1",-1,"","");
				trVectorSetUnitPos("pos", "spellTarget");
				trQuestVarSet("spellTarget", checkGuard(1*trQuestVarGet("spellTarget")));
				for(x=yGetDatabaseCount("allUnits"); >0) {
					activeUnit = yDatabaseNext("allUnits");
					if (mGetVar(activeUnit, "player") == p) {
						dist = zDistanceToVectorSquared("allUnits", "pos");
						if (dist < xsPow(mGetVar(activeUnit, "range") * 6 + 1, 2)) {
							startAttack(activeUnit, 1*trQuestVarGet("spellTarget"), false, true);
						}
					}
				}
				done = false;
				xsEnableRule("spell_attack_complete");
			}
			case SPELL_DEFENDER:
			{
				trSoundPlayFN("fortress.wav","1",-1,"","");
				trSoundPlayFN("researchcomplete.wav","1",-1,"","");
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "health", 2 + mGetVar(target, "health"));
				mSetVar(target, "keywords", SetBit(1*mGetVar(target, "keywords"), GUARD));
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
				refreshGuardAll();
			}
			case SPELL_WOLF:
			{
				battlecry = true;
				trSoundPlayFN("mythcreate.wav","1",-1,"","");
				activeUnit = summonAtTile(1*trQuestVarGet("spellTarget"),p,kbGetProtoUnitID("Wolf"));
				mSetVar(activeUnit, "action", ACTION_SLEEPING);
			}
			case SPELL_VICTORY:
			{
				trSoundPlayFN("battlecry1.wav","1",-1,"","");
				trSoundPlayFN("herocreation.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((mGetVarByQV("allUnits", "spell") == SPELL_NONE) &&
						(mGetVarByQV("allUnits", "player") == p)) {
						mSetVarByQV("allUnits", "victory", 1 + mGetVarByQV("allUnits", "victory"));
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						if ((mGetVarByQV("allUnits", "victory") == 1) &&
							HasKeyword(AMBUSH, 1*mGetVarByQV("allUnits", "keywords"))) {
							mSetVarByQV("allUnits", "victoryAmbush", 1);
						}
						mSetVarByQV("allUnits", "keywords", SetBit(1*mGetVarByQV("allUnits", "keywords"), AMBUSH));
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
					}
				}
			}
			case SPELL_HEROIC:
			{
				trSoundPlayFN("herocreation.wav","1",-1,"","");
				trSoundPlayFN("researchcomplete.wav","1",-1,"","");
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "attack", 1 + mGetVar(target, "attack"));
				mSetVar(target, "keywords", SetBit(1*mGetVar(target, "keywords"), FURIOUS));
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
			}
			case SPELL_WHIRLWIND:
			{
				done = false;
				deployAtTile(0, "Tremor", 1*mGetVarByQV("spellTarget", "tile"));
				trQuestVarSet("spellNext", trTimeMS());
				trQuestVarSet("spellEnd", trTimeMS() + 1000);
				trSoundPlayFN("sphinxspecialattack.wav","1",-1,"","");
				trSoundPlayFN("ui\thunder1.wav","1",-1,"","");
				trQuestVarSet("spellAngle", 0);
				for(x=3; >0) {
					trQuestVarSet("proj"+x, deployAtTile(0, "Petosuchus Projectile", 1*mGetVarByQV("spellTarget", "tile")));
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("proj"+x), true);
					trSetSelectedScale(8.0, 0, 10.0);
					trUnitHighlight(2.0, false);
				}
				xsEnableRule("spell_whirlwind_sfx");
			}
			case SPELL_PING:
			{
				trSoundPlayFN("cinematics\23_in\arrow1.mp3","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), 1);
				deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("spellTarget", "tile"));
				battlecry = true;
			}
			case SPELL_FIRST_AID:
			{
				trSoundPlayFN("villagercreate.wav","1",-1,"","");
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("spellTarget", "tile"), 0);
				teleportToTile(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("tileTarget"));
				healUnit(1*trQuestVarGet("spellTarget"), 2);
			}
			case SPELL_CLASS_TIME:
			{
				trSoundPlayFN("townbell.wav","1",-1,"","");
				trSoundPlayFN("temple.wav","1",-1,"","");
				xsEnableRule("spell_class_time_activate");
			}
			case SPELL_SNIPE:
			{
				trSoundPlayFN("petsuchosattack.wav","1",-1,"","");
				mSetVarByQV("spellshooter", "attack", mGetVarByQV("spellshooter", "attack") + mGetVarByQV("spellshooter", "range"));
				trQuestVarSet("spelltarget", checkGuard(1*trQuestVarGet("spellTarget")));
				startAttack(1*trQuestVarGet("spellshooter"), 1*trQuestVarGet("spelltarget"), false, true);
				done = false;
				xsEnableRule("spell_snipe_complete");
			}
			case SPELL_EXPLOSION:
			{
				trSoundPlayFN("ui\thunder5.wav","1",-1,"","");
				trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
				deployAtTile(0, "Olympus Temple SFX", 1*trQuestVarGet("spelltarget"));
				trVectorSetUnitPos("pos", "spellTarget");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "player") == 3 - p) {
						if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
							damageUnit(1*trQuestVarGet("allUnits"), 1 + trQuestVarGet("p"+p+"spellDamage"));
						}
					}
				}
			}
			case SPELL_DOUBLEBLAST:
			{
				trSoundPlayFN("fireball fall 2.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget1"), 1 + trQuestVarGet("p"+p+"spellDamage"));
				damageUnit(1*trQuestVarGet("spellTarget2"), 1 + trQuestVarGet("p"+p+"spellDamage"));
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Meteorite", 1*mGetVarByQV("spelltarget1", "tile")), true);
				trDamageUnitPercent(100);
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Meteorite", 1*mGetVarByQV("spelltarget2", "tile")), true);
				trDamageUnitPercent(100);
				trQuestVarSet("p"+p+"drawCards", 1);
			}
			case SPELL_ELECTROSURGE:
			{
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				trTechInvokeGodPower(0, "bolt", xsVectorSet(0,0,0), xsVectorSet(0,0,0));
				lightning(1*trQuestVarGet("spellTarget"), 2 + trQuestVarGet("p"+p+"spellDamage"), false);
				done = false;
				xsEnableRule("spell_attack_complete");
			}
			case SPELL_RUNE_OF_FLAME:
			{
				activeUnit = summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Fire Giant"));
				mSetVar(activeUnit, "action", ACTION_SLEEPING);
				trSoundPlayFN("mythcreate.wav","1",-1,"","");
				trSoundPlayFN("fireball fall 1.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("p"+p+"commander"),6 + trQuestVarGet("p"+p+"spellDamage"));
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Meteorite", 1*mGetVarByQV("p"+p+"commander", "tile")), true);
				trDamageUnitPercent(100);
			}
			case SPELL_RUNE_OF_ICE:
			{
				activeUnit = summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Frost Giant"));
				mSetVar(activeUnit, "action", ACTION_SLEEPING);
				trSoundPlayFN("mythcreate.wav","1",-1,"","");
				trSoundPlayFN("frostgiantattack.wav","1",-1,"","");
				stunUnit(1*trQuestVarGet("p"+p+"commander"));
			}
			case SPELL_FIRE_AND_ICE:
			{
				if (trQuestVarGet("spellTargetFire") == trQuestVarGet("spellTargetIce")) {
					if (trCurrentPlayer() == p) {
						trSoundPlayFN("cantdothat.wav","1",-1,"","");
					}
					done = false;
					battlecry = true;
					chooseSpell(SPELL_FIRE_AND_ICE, 1*trQuestVarGet("selectedCard"));
				} else {
					trSoundPlayFN("mythcreate.wav","1",-1,"","");
					activeUnit = summonAtTile(1*trQuestVarGet("spellTargetIce"), p, kbGetProtoUnitID("Frost Giant"));
					mSetVar(activeUnit, "action", ACTION_SLEEPING);
					activeUnit = summonAtTile(1*trQuestVarGet("spellTargetFire"), p, kbGetProtoUnitID("Fire Giant"));
					mSetVar(activeUnit, "action", ACTION_SLEEPING);
				}
			}
			case SPELL_VALKYRIE_HEAL:
			{
				battlecry = true;
				trVectorSetUnitPos("healerPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTarget");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(zGetUnitVector("healerPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(50, 0, 0, 1, -1);
				deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("spellTarget", "tile"));
				healUnit(1*trQuestVarGet("spellTarget"), 3);
			}
			case SPELL_COPY_HOMEWORK:
			{
				trSoundPlayFN("ui\scroll.wav","1",-1,"","");
				trSoundPlayFN("spybirth.wav","1",-1,"","");
				xsEnableRule("spell_copy_homework_activate");
			}
			case SPELL_METEOR:
			{
				trSoundPlayFN("townattacked.wav","1",-1,"","");
				trQuestVarSet("next", deployAtTile(0, "Relic", 1*trQuestVarGet("spellTarget")));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("next"), true);
				trMutateSelected(kbGetProtoUnitID("Hero Birth"));
				yAddToDatabase("meteors", "next");
				yAddUpdateVar("meteors", "time", 2);
				yAddUpdateVar("meteors", "tile", trQuestVarGet("spellTarget"));
			}
			case SPELL_FINAL_EXAM:
			{
				trSoundPlayFN("cinematics\15_in\gong.wav","1",-1,"","");
				trSoundPlayFN("pestilencebirth.wav","1",-1,"","");
				trQuestVarSet("p1drawCards", 2);
				trQuestVarSet("p2drawCards", 2);
			}
			case SPELL_SHAPESHIFT:
			{
				battlecry = true;
				trSoundPlayFN("changeunit.wav","1",-1,"","");
				target = trQuestVarGet("copyTarget");
				activeUnit = trQuestVarGet("transformTarget");
				mSetVar(activeUnit, "proto", mGetVar(target, "proto"));
				mSetVar(activeUnit, "spell", mGetVar(target, "spell"));
				mSetVar(activeUnit, "cost", mGetVar(target, "cost"));
				mSetVar(activeUnit, "attack", mGetVar(target, "attack"));
				mSetVar(activeUnit, "health", mGetVar(target, "health"));
				mSetVar(activeUnit, "speed", mGetVar(target, "speed"));
				mSetVar(activeUnit, "range", mGetVar(target, "range"));
				mSetVar(activeUnit, "keywords", mGetVar(target, "keywords"));
				mSetVar(activeUnit, "onAttack", mGetVar(target, "onAttack"));
				mSetVar(activeUnit, "onDeath", mGetVar(target, "onDeath"));
				mSetString(activeUnit, "ability", mGetString(target, "ability"));
				deployAtTile(0, "Kronny Birth SFX", 1*mGetVar(activeUnit, "tile"));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trUnitOverrideAnimation(39,0,0,1,-1);
				trUnitSelectClear();
				trUnitSelect(""+activeUnit);
				trUnitChangeProtoUnit(kbGetProtoUnitName(1*mGetVar(activeUnit, "proto")));
				damageUnit(activeUnit, 0);
				updateAuras();
			}
			case SPELL_APOCALYPSE:
			{
				trSoundPlayFN("meteorapproach.wav","1",-1,"","");
				
				trQuestVarSet("apocalypse", 2);
				musicToggleBattleMode();
				xsEnableRule("spell_apocalypse_activate");
			}
			case SPELL_MIRROR_IMAGE:
			{
				trSoundPlayFN("recreation.wav","1",-1,"","");
				deployAtTile(0, "Vortex start linked", 1*mGetVarByQV("spellTarget", "tile"));
				addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("spellTarget", "proto")));
				// if commander is nottud
				if (trQuestVarGet("p"+p+"commanderType") == 3) {
					addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("spellTarget", "proto")));
				}
				shuffleDeck(p);
				xsEnableRule("spell_mirror_image_activate");
			}
			case SPELL_MEDUSA_STUN:
			{
				battlecry = true;
				trVectorSetUnitPos("casterPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTarget");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(zGetUnitVector("casterPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(40, 0, 0, 1, -1);
				stunUnit(1*trQuestVarGet("spellTarget"));
			}
			case SPELL_LAMPADES_CONVERT:
			{
				battlecry = true;
				trVectorSetUnitPos("casterPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTarget");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(zGetUnitVector("casterPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(37, 0, 0, 1, -1);
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				trUnitConvert(p);
				mSetVarByQV("spellTarget", "player", p);
				mSetVarByQV("spellTarget", "action", ACTION_SLEEPING);
			}
			case SPELL_RUNE_OF_WATER:
			{
				trSoundPlayFN("mythcreate.wav","1",-1,"","");
				trSoundPlayFN("healingspringbirth.wav","1",-1,"","");
				activeUnit = summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Servant"));
				mSetVar(activeUnit, "action", ACTION_SLEEPING);
				healUnit(1*trQuestVarGet("p"+(3-p)+"commander"), 6);
				deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+(3-p)+"commander", "tile"));
			}
			case SPELL_WATER_CANNON:
			{
				trSoundPlayFN("shipdeathsplash.wav","1",-1,"","");
				trSoundPlayFN("shockwave.wav","1",-1,"","");
				deployAtTile(0, "Meteor Impact Water", 1*mGetVarByQV("spellTarget", "tile"));
				done = false;
				trVectorSetUnitPos("start", "spellTarget");
				trVectorSetUnitPos("end", "spellDirection");
				trVectorQuestVarSet("dir", zGetUnitVector("start", "end"));
				pushUnit(1*trQuestVarGet("spellTarget"), "dir");
				xsEnableRule("spell_attack_complete");
			}
			case SPELL_TIDAL_WAVE:
			{
				trSoundPlayFN("meteorsplash.wav","1",-1,"","");
				for (x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "cost") < trQuestVarGet("p"+p+"manaflow") && mGetVarByQV("allUnits", "spell") == 0) {
						stunUnit(1*trQuestVarGet("allUnits"));
						deployAtTile(0, "Meteor Impact Water", 1*mGetVarByQV("allUnits", "tile"));
					}
				}
			}
			case SPELL_FLUSH:
			{
				trSoundPlayFN("shipmove1.wav","1",-1,"","");
				trSoundPlayFN("shockwave.wav","1",-1,"","");
				tile = mGetVarByQV("p"+p+"commander", "tile");
				deployAtTile(0, "Meteor Impact Water", tile);
				trVectorSetUnitPos("center", "p"+p+"commander");
				for(x=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
					target = zGetVarByIndex("tiles", "neighbor"+x, tile);
					activeUnit = zGetVarByIndex("tiles", "occupant", target);
					if ((activeUnit > 0) && (mGetVar(activeUnit, "spell") == SPELL_NONE)) {
						trVectorQuestVarSet("pos", kbGetBlockPosition(""+activeUnit));
						trVectorQuestVarSet("dir", zGetUnitVector("center", "pos"));
						pushUnit(activeUnit, "dir");
					}
				}
				done = false;
				xsEnableRule("spell_attack_complete");
			}
			case SPELL_DEEP_DIVE:
			{
				trSoundPlayFN("meteorsplash.wav","1",-1,"","");
				trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") + xsFloor(0.5*trQuestVarGet("p"+p+"manaflow")));
			}
			case SPELL_SEA_EMBRACE:
			{
				trSoundPlayFN("healingspringbirth.wav","1",-1,"","");
				tile = mGetVarByQV("spellTarget", "tile");
				deployAtTile(0, "Regeneration SFX", tile);
				healUnit(1*trQuestVarGet("spellTarget"), 3);
				tile = mGetVarByQV("p"+p+"commander", "tile");
				deployAtTile(0, "Regeneration SFX", tile);
				healUnit(1*trQuestVarGet("p"+p+"commander"), 3);
			}
			case SPELL_TELETIDE:
			{
				trSoundPlayFN("shipmove2.wav","1",-1,"","");
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("spellTarget", "tile"), 0);
				teleportToTile(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("spellDestination"));
			}
			case SPELL_GUARDIAN_OF_SEA:
			{
				trSoundPlayFN("ageadvance.wav","1",-1,"","");
				trSoundPlayFN("bronzebirth.wav","1",-1,"","");
				mSetVarByQV("p"+p+"commander", "keywords", SetBit(1*mGetVarByQV("p"+p+"commander", "keywords"), GUARD));
				mSetVarByQV("p"+p+"commander", "keywords", SetBit(1*mGetVarByQV("p"+p+"commander", "keywords"), ARMORED));
				trQuestVarSet("p"+p+"guardianOfTheSea", 1);
			}
			case SPELL_WRATH_OF_SEA:
			{
				trSoundPlayFN("herobirth2.wav","1",-1,"","");
				trSoundPlayFN("arkantosspecial2.wav","1",-1,"","");
				trQuestVarSet("p"+p+"yeebbonus", 2*mGetVarByQV("p"+p+"commander", "attack"));
				mSetVarByQV("p"+p+"commander", "attack", 2*mGetVarByQV("p"+p+"commander", "attack"));
			}
			case SPELL_DROWN:
			{
				trSoundPlayFN("shipdeathsplash.wav","1",-1,"","");
				deployAtTile(0, "Meteor Impact Water", 1*mGetVarByQV("spellTarget", "tile"));
				addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("spellTarget", "proto")));
				shuffleDeck(p);
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("spellTarget", "tile"), 0);
				for(x=yGetDatabaseCount("allUnits"); >0) {
					if (yDatabaseNext("allUnits") == trQuestVarGet("spellTarget")) {
						yRemoveFromDatabase("allUnits");
						break;
					}
				}
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
			}
			case SPELL_CLEANSING_WATERS:
			{
				trSoundPlayFN("healingspringbirth.wav","1",-1,"","");
				trQuestVarSet("next", deployAtTile(0, "UI Range Indicator Norse SFX", 1*trQuestVarGet("spelltarget")));
				zSetVarByIndex("tiles", "ward", 1*trQuestVarGet("spellTarget"), 1);
				yAddToDatabase("tileWardSFX", "next");
				for(x=0; < zGetVarByIndex("tiles", "neighborCount", 1*trQuestVarGet("spellTarget"))) {
					target = zGetVarByIndex("tiles", "neighbor"+x, 1*trQuestVarGet("spellTarget"));
					zSetVarByIndex("tiles", "ward", target, 1);
					trQuestVarSet("next", deployAtTile(0, "UI Range Indicator Norse SFX", target));
					yAddToDatabase("tileWardSFX", "next");
				}
				// remove ignite
				trVectorSetUnitPos("center", "spellTarget");
				for(x=yGetDatabaseCount("ignite"); >0) {
					yDatabaseNext("ignite", true);
					if (zDistanceToVectorSquared("ignite", "center") < 40) {
						trUnitChangeProtoUnit("Lightning sparks");
						yRemoveFromDatabase("ignite");
						yRemoveUpdateVar("ignite", "tile");
					}
				}
			}
			case SPELL_DEMON_EAT:
			{
				trSoundPlayFN("tartarianspawnbirth1.wav","1",-1,"","");
				mSetVarByQV("spellCaster", "health", mGetVarByQV("spellCaster", "health") + mGetVarByQV("spellTarget", "health"));
				mSetVarByQV("spellCaster", "attack", mGetVarByQV("spellCaster", "attack") + mGetVarByQV("spellTarget", "attack"));
				mSetVarByQV("spellTarget", "health", 0);
				damageUnit(1*trQuestVarGet("spellTarget"),10);
			}
			case SPELL_SCORPION_STING:
			{
				battlecry = true;
				trVectorSetUnitPos("casterPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTarget");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(zGetUnitVector("casterPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(39, 0, 0, 1, -1);
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				spyEffect("Poison SFX");
				mSetVarByQV("spellTarget", "keywords", SetBit(1*mGetVarByQV("spellTarget", "keywords"), DECAY));
				trSoundPlayFN("lampadesblood.wav","1",-1,"","");
				trSoundPlayFN("carnivorabirth.wav","1",-1,"","");
			}
			case SPELL_WORLD_SPLITTER:
			{
				trVectorSetUnitPos("laserstart", "spellTarget");
				trVectorSetUnitPos("laserend", "spellDirection");
				trVectorQuestVarSet("dir", zGetUnitVector("laserstart", "laserend"));
				trQuestVarSet("posx", trQuestVarGet("laserstartx") + 6.0*trQuestVarGet("dirx"));
				trQuestVarSet("posz", trQuestVarGet("laserstartz") + 6.0*trQuestVarGet("dirz"));
				tile = mGetVarByQV("spellTarget", "tile");
				
				while(done) {
					done = false;
					// Travel down the line and find stopping tile
					for(z=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
						neighbor = zGetVarByIndex("tiles", "neighbor"+z, tile);
						if (neighbor < trQuestVarGet("ztilesend")) {
							trVectorQuestVarSet("current", kbGetBlockPosition(""+neighbor));
							if (zDistanceBetweenVectorsSquared("current", "pos") < 1) {
								trQuestVarSet("occupant", zGetVarByIndex("tiles", "occupant", neighbor));
								if (trQuestVarGet("occupant") > 0) {
									yAddToDatabase("worldSplitterHit", "occupant");
								}
								tile = neighbor;
								trQuestVarSet("posx", trQuestVarGet("currentx") + 6.0*trQuestVarGet("dirx"));
								trQuestVarSet("posz", trQuestVarGet("currentz") + 6.0*trQuestVarGet("dirz"));
								done = true;
								break;
							}
						}
					}
				}

				trVectorQuestVarSet("laserEnd", kbGetBlockPosition(""+tile));
				
				tile = mGetVarByQV("spellTarget", "tile");

				trQuestVarSet("laserProj", deployAtTile(p, "Dwarf", tile));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserProj"), true);
				trMutateSelected(kbGetProtoUnitID("Relic"));

				trQuestVarSet("laserAimer", deployAtTile(p, "Dwarf", tile));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserAimer"), true);
				trMutateSelected(kbGetProtoUnitID("Hero Greek Achilles"));

				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserProj"), true);
				trImmediateUnitGarrison(""+1*trQuestVarGet("laserAimer"));
				trMutateSelected(kbGetProtoUnitID("Petosuchus Projectile"));

				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserAimer"), true);
				trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));

				trQuestVarSet("laserPhoenix", deployAtTile(p, "Phoenix", tile));
				trVectorSetUnitPos("phoenixPos", "laserPhoenix");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserPhoenix"), true);
				trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(15,0,1,1,-1);
				trMutateSelected(kbGetProtoUnitID("Hero Greek Ajax"));

				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				trMutateSelected(kbGetProtoUnitID("Relic"));
				trImmediateUnitGarrison(""+1*trQuestVarGet("laserPhoenix"));
				trMutateSelected(1*mGetVarByQV("spellTarget", "proto"));

				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserPhoenix"), true);
				trMutateSelected(kbGetProtoUnitID("Phoenix"));

				trQuestVarSet("laserMeteorite", deployAtTile(p, "Dwarf", tile));
				trMutateSelected(kbGetProtoUnitID("Meteorite"));
				trUnitOverrideAnimation(6,0,1,1,-1);
				trMutateSelected(kbGetProtoUnitID("Relic"));

				trQuestVarSet("laserGround", deployAtTile(p, "Dwarf", tile));
				trMutateSelected(kbGetProtoUnitID("Hero Greek Achilles"));

				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserMeteorite"), true);
				trImmediateUnitGarrison(""+1*trQuestVarGet("laserGround"));
				trMutateSelected(kbGetProtoUnitID("Meteorite"));

				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserGround"), true);
				trMutateSelected(kbGetProtoUnitID("Rocket"));
				trSoundPlayFN("attackwarning.wav","1",-1,"","");
				trSoundPlayFN("phoenixselect2.wav","1",-1,"","");
				// laser stuff
				
				trQuestVarSet("laserStartY", 10.0);

				trQuestVarSet("laserStepx", 2.0*trQuestVarGet("dirX"));
				trQuestVarSet("laserStepz", 2.0*trQuestVarGet("dirZ"));
				trQuestVarSet("laserNormalX", trQuestVarGet("dirZ"));
				trQuestVarSet("laserNormalY", 0);
				trQuestVarSet("laserNormalZ", trQuestVarGet("dirX"));
				trQuestVarSet("laserStepDist", 0);
				trQuestVarCopy("laserSFXX", "laserStartX");
				trQuestVarCopy("laserSFXZ", "laserStartZ");

				trQuestVarSet("laserheading", 57.295779 * angleBetweenVectors("dir", "laserStep"));


				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserAimer"), true);
				trUnitTeleport(trQuestVarGet("laserStartx"), 10.0, trQuestVarGet("laserStartz"));
				trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
				
				trQuestVarSet("laserAngle", 1.550796);

				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("laserProj"), true);
				trSetSelectedScale(1,1,1);

				trQuestVarSet("bossSpell", 2);
				trQuestVarSet("bossNext", trTimeMS() + 1000);

				zSetProtoUnitStat("Wadjet Spit", p, 1, 8);
				xsEnableRule("spell_world_splitter_activate");
			}
			case SPELL_SOUL_SIPHON:
			{
				trSoundPlayFN("shadeofhadesdeath.wav","1",-1,"","");
				trQuestVarSet("p"+p+"drawCards", 2);
				mSetVarByQV("spellTarget", "health", 0);
				damageUnit(1*trQuestVarGet("spellTarget"), 100);
				deployAtTile(0, "Hero Death", 1*mGetVarByQV("spellTarget", "tile"));
				deployAtTile(0, "Curse SFX", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_BLOOD_PRICE:
			{
				trSoundPlayFN("shadeofhadesselect2.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("allyTarget"), 2 + trQuestVarGet("p"+p+"spellDamage"));
				damageUnit(1*trQuestVarGet("enemyTarget"), 2 + trQuestVarGet("p"+p+"spellDamage"));
				deployAtTile(0, "Tartarian Gate flame", 1*mGetVarByQV("allyTarget", "tile"));
				deployAtTile(0, "Tartarian Gate flame", 1*mGetVarByQV("enemyTarget", "tile"));
			}
			case SPELL_DEATH_APPROACHES:
			{
				trSoundPlayFN("shadeofhadesbirth.wav","1",-1,"","");
				target = summonAtTile(1*trQuestVarGet("spellTarget"),p,kbGetProtoUnitID("Shade of Hades"));
				mSetVar(target, "action", ACTION_SLEEPING);
			}
			case SPELL_DOOM:
			{
				trSoundPlayFN("shadeofhadesacknowledge2.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), 2 + trQuestVarGet("p"+p+"spellDamage"));
				deployAtTile(0, "Curse SFX", 1*mGetVarByQV("spellTarget", "tile"));
				if (HasKeyword(DECAY, 1*mGetVarByQV("spellTarget", "keywords"))) {
					if (yGetDatabaseCount("p"+p+"hand") < 10) {
						addCardToHand(p, 0, SPELL_DOOM);
					}
				}
			}
			case SPELL_SHADOWSTEP:
			{
				trSoundPlayFN("spybirth.wav","1",-1,"","");
				trQuestVarSet("tile1", mGetVarByQV("spellTarget", "tile"));
				trQuestVarSet("tile2", mGetVarByQV("p"+p+"commander", "tile"));
				deployAtTile(0, "Curse SFX", 1*trQuestVarGet("tile1"));
				deployAtTile(0, "Curse SFX", 1*trQuestVarGet("tile2"));
				teleportToTile(1*trQuestVarGet("p"+p+"commander"), 1*trQuestVarGet("tile1"));
				teleportToTile(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("tile2"));
			}
			case SPELL_FINAL_FRENZY:
			{
				trSoundPlayFN("mummyconvert.wav","1",-1,"","");
				deployAtTile(0, "Hero Birth", 1*mGetVarByQV("spellTarget", "tile"));
				mSetVarByQV("spellTarget", "keywords", SetBit(SetBit(1*mGetVarByQV("spellTarget", "keywords"), DECAY), DEADLY));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				spyEffect("Poison SFX");
				spyEffect("Chaos effect");
			}
			case SPELL_CORPSE_PARTY:
			{
				// If two of the tiles are the same, restart
				if ((trQuestVarGet("spellTarget1") - trQuestVarGet("spellTarget2")) * (trQuestVarGet("spellTarget2") - trQuestVarGet("spellTarget3")) * (trQuestVarGet("spellTarget1") - trQuestVarGet("spellTarget3")) == 0) {
					if (trCurrentPlayer() == p) {
						trSoundPlayFN("cantdothat.wav","1",-1,"","");
					}
					done = false;
					battlecry = true;
					chooseSpell(SPELL_CORPSE_PARTY, 1*trQuestVarGet("selectedCard"));
				} else {
					for(x=3; >0) {
						summonAtTile(1*trQuestVarGet("tile"+x), p, kbGetProtoUnitID("Minion"));
					}
				}
			}
			case SPELL_UNDEATH:
			{
				trSoundPlayFN("ui\thunder1.wav","1",-1,"","");
				trSoundPlayFN("mummyflies.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((mGetVarByQV("allUnits", "player") == p) && (mGetVarByQV("allUnits", "spell") == SPELL_NONE)) {
						mSetVarByQV("allUnits", "OnDeath", SetBit(1*mGetVarByQV("allUnits", "OnDeath"), DEATH_SUMMON_ZOMBIE));
					}
				}
			}
		}

		if (trQuestVarGet("selectedCard") >= 0) {
			if (trCurrentPlayer() == 3 - trQuestVarGet("activePlayer")) {
				trMessageSetText("("+1*trQuestVarGet("spell_"+spell+"_cost")+")"+trStringQuestVarGet("spell_"+spell+"_name")+": "+trStringQuestVarGet("spell_"+spell+"_description"), -1);
			}
			ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> cast " + trStringQuestVarGet("spell_"+1*trQuestVarGet("currentSpell")+"_name"));
		}

		if (done) {
			castEnd();
		} else {
			trQuestVarSet("gameplayPhase", GAMEPLAY_ATTACKING);
		}
	}
}

rule spell_party_up_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		int proto = 0;
		int target = 3;
		yDatabasePointerDefault("p"+p+"deck");
		for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
			proto = yDatabaseNext("p"+p+"deck");
			if (yGetVar("p"+p+"deck", "spell") > 0) {
				proto = yGetVar("p"+p+"deck", "spell");
				if (trQuestVarGet("spell_"+proto+"_cost") == 1) {
					ySetPointer("p"+p+"deck", 1 + yGetPointer("p"+p+"deck"));
					drawCard(p);
					target = target - 1;
					if (target == 0) {
						break;
					}
				}
			} else if (trQuestVarGet("card_"+proto+"_cost") == 1) {
				ySetPointer("p"+p+"deck", 1 + yGetPointer("p"+p+"deck"));
				drawCard(p);
				target = target - 1;
				if (target == 0) {
					break;
				}
			}
		}
		updateHandPlayable(p);
		xsDisableRule("spell_party_up_activate");
	}
}

rule spell_copy_homework_activate
highFrequency
inactive
{
	int p = trQuestVarGet("activePlayer");
	int card = 0;
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		for(x=3; >0) {
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				trQuestVarSetFromRand("chooseClass", 1, 2, true);
				trQuestVarSetFromRand("chooseCard", 0, 29, true);
				card = 30*trQuestVarGet("p"+(3-p)+"class"+1*trQuestVarGet("chooseClass")) + trQuestVarGet("chooseCard");
				addCardToHandByIndex(p, card);
			}
		}
		updateHandPlayable(p);
		xsDisableRule("spell_copy_homework_activate");	
	}
}

rule spell_apocalypse_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		for(x=yGetDatabaseCount("p"+p+"hand"); < 10) {
			addCardToHand(p, 0, SPELL_METEOR, true);
			mSetVarByQV("next", "cost", 0);
		}
		xsDisableRule("spell_apocalypse_activate");
	}	
}

rule spell_mirror_image_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		int proto = mGetVarByQV("spellTarget", "proto");
		if (yGetDatabaseCount("p"+p+"hand") < 10) {
			addCardToHand(p, proto);
			updateHandPlayable(p);
		}
		xsDisableRule("spell_mirror_image_activate");
	}
}

rule spell_class_time_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		yDatabasePointerDefault("p"+p+"deck");
		for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
			yDatabaseNext("p"+p+"deck");
			if (yGetVar("p"+p+"deck", "spell") > 0) {
				ySetPointer("p"+p+"deck", 1 + yGetPointer("p"+p+"deck"));
				drawCard(p);
				break;
			}
		}
		yDatabasePointerDefault("p"+p+"deck");
		for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
			yDatabaseNext("p"+p+"deck");
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				ySetPointer("p"+p+"deck", 1 + yGetPointer("p"+p+"deck"));
				drawCard(p);
				break;
			}
		}
		updateHandPlayable(p);
		xsDisableRule("spell_class_time_activate");
	}
}

rule spell_attack_complete
highFrequency
inactive
{
	if ((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + yGetDatabaseCount("pushes") + trQuestVarGet("lightningActivate") - trQuestVarGet("lightningPop") == 0) || 
		(trTime() > cActivationTime + 3)) {
		castEnd();
		xsDisableRule("spell_attack_complete");
	}
}

rule spell_snipe_complete
highFrequency
inactive
{
	if ((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + trQuestVarGet("lightningActivate") - trQuestVarGet("lightningPop") == 0) || 
		(trTime() > cActivationTime + 3)) {
		int tile = mGetVarByQV("spelltarget", "tile");
		deployAtTile(0, "Arkantos God Out", tile);
		mSetVarByQV("spellshooter", "attack", mGetVarByQV("spellshooter", "attack") - mGetVarByQV("spellshooter", "range"));
		castEnd();
		xsDisableRule("spell_snipe_complete");
	}
}

rule spell_whirlwind_sfx
highFrequency
inactive
{
	int p = mGetVarByQV("spellTarget", "player");
	if (trTimeMS() > trQuestVarGet("spellEnd")) {
		for(x=3; >0) {
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("proj"+x), true);
			trUnitChangeProtoUnit("Rocket");
		}
		trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*mGetVarByQV("spellTarget", "tile")));
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (mGetVarByQV("allUnits", "player") == 3 - p) {
				if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
					startAttack(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("allUnits"), false, false);
				}
			}
		}
		xsEnableRule("spell_attack_complete");
		xsDisableRule("spell_whirlwind_sfx");
	} else {
		float diff = trTimeMS() - trQuestVarGet("spellNext");
		trQuestVarSet("spellNext", trTimeMS());
		trQuestVarSet("spellAngle", fModulo(6.283185, trQuestVarGet("spellAngle") + 0.02 * diff));
		for(x=3; >0) {
			trQuestVarSet("spellAngle", fModulo(6.283185, trQuestVarGet("spellAngle") + 2.094395));
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("proj"+x), true);
			trVectorSetFromAngle("dir", trQuestVarGet("spellAngle"));
			trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
		}
	}
}

void laserEnd(int eventId = -1) {
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("laserGround"), true);
	trMutateSelected(kbGetProtoUnitID("Rocket"));
	trQuestVarSet("bossSpell", 0);
	trQuestVarSet("laserEndTime", trTimeMS() + 500);
}

/*
Code taken straight from HBF2 lmao
*/
rule spell_world_splitter_activate
highFrequency
inactive
{
	int p = trQuestVarGet("activePlayer");
	if (trQuestVarGet("bossSpell") == 2) {
		if (trTimeMS() > trQuestVarGet("bossNext")) {
			trQuestVarSet("laserCurDist", 0);
			trQuestVarSet("laserNextDist", 10.0 * xsCos(trQuestVarGet("laserAngle")) / xsSin(trQuestVarGet("laserAngle")));
			trQuestVarSet("laserNextDistSquared", xsPow(trQuestVarGet("laserNextDist"), 2));
			trQuestVarSet("speed", 60.0 * (trQuestVarGet("laserNextDist") - trQuestVarGet("laserCurDist")));

			zSetProtoUnitStat("Wadjet Spit", p, 1, trQuestVarGet("speed"));
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("laserGround"), true);
			trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
			trUnitMoveToPoint(trQuestVarGet("laserEndx"),0,trQuestVarGet("laserEndz"), EVENT_LASER_END);

			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("laserProj"), true);
			trUnitHighlight(3.0, false);
			trSetSelectedScale(12.0,12.0,50.0);
			/*
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("laserMeteorite"), true);
			trMutateSelected(kbGetProtoUnitID("Meteorite"));
			*/
			trSoundPlayFN("sonofosirisbolt.wav","1",-1,"","");
			trSoundPlayFN("nidhoggflame2.wav","1",-1,"","");
			trSoundPlayFN("phoenixattack.wav","1",-1,"","");
			trQuestVarSet("bossSpell", 3);
			trQuestVarSet("laserEndTime", trTimeMS() + 2000);
		}
	} else if (trQuestVarGet("bossSpell") == 3) {
		trVectorQuestVarSet("laserPos", kbGetBlockPosition(""+1*trQuestVarGet("laserGround"), true));

		// adjust speed;
		trQuestVarSet("laserCurDistSquared", zDistanceBetweenVectorsSquared("laserPos", "laserStart"));
		if (trQuestVarGet("laserCurDistSquared") > trQuestVarGet("laserNextDistSquared")) {
			trQuestVarSet("laserCurDist", xsSqrt(trQuestVarGet("laserCurDistSquared")));
			trQuestVarSet("laserAngle", Math_atan(10.0 / trQuestVarGet("laserCurDist")) - 0.02);

			trQuestVarSet("laserNextDist", 10.0 * xsCos(trQuestVarGet("laserAngle")) / xsSin(trQuestVarGet("laserAngle")));
			trQuestVarSet("laserNextDistSquared", xsPow(trQuestVarGet("laserNextDist"), 2));
			trQuestVarSet("speed", 60.0 * (trQuestVarGet("laserNextDist") - trQuestVarGet("laserCurDist")));
			zSetProtoUnitStat("Wadjet Spit", p, 1, trQuestVarGet("speed"));
		}

		if (trQuestVarGet("laserCurDist") > trQuestVarGet("laserStepDist") + 2.0) {
			bool f = true;
			while(trQuestVarGet("laserStepDist") < trQuestVarGet("laserCurDist")) {
				trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
				trArmyDispatch("1,10","Dwarf",1,trQuestVarGet("laserSFXX"),0,trQuestVarGet("laserSFXZ"),trQuestVarGet("laserheading"),f);
				f = false;
				trQuestVarSet("laserStepDist", trQuestVarGet("laserStepDist") + 2.0);
				trQuestVarSet("laserSFXX", trQuestVarGet("laserSFXX") + trQuestVarGet("laserStepX"));
				trQuestVarSet("laserSFXZ", trQuestVarGet("laserSFXZ") + trQuestVarGet("laserStepZ"));
			}
			trArmySelect("1,10");
			trUnitChangeProtoUnit("Tartarian Gate flame");
		}

		// adjust aim;
		trVectorQuestVarSet("laserAim", zGetUnitVector3d("laserStart", "laserPos", -1.0));
		trVectorQuestVarSet("laserAim2", crossProduct("laserAim", "laserNormal"));
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("laserAimer"), true);
		trSetUnitOrientation(trVectorQuestVarGet("laserAim"), trVectorQuestVarGet("laserAim2"), true);

		if (trTimeMS() > trQuestVarGet("laserEndTime")) {
			laserEnd();
		}
	} else if (trQuestVarGet("bossSpell") == 4) {
		trQuestVarSet("scale", 0.024 * (trQuestVarGet("laserEndTime") - trTimeMS()));
		if (trQuestVarGet("scale") < 0) {
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("spellTarget"));
			trUnitChangeProtoUnit(kbGetProtoUnitName(1*mGetVarByQV("spellTarget", "proto")));
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("laserPhoenix"), true);
			trUnitSelect(""+1*trQuestVarGet("laserAimer"), true);
			trUnitSelect(""+1*trQuestVarGet("laserProj"), true);
			trUnitSelect(""+1*trQuestVarGet("laserGround"), true);
			trUnitSelect(""+1*trQuestVarGet("laserMeteorite"), true);
			trUnitDestroy();
			zSetProtoUnitStat("Wadjet Spit", p, 1, 20);
			xsDisableRule("spell_world_splitter_activate");
			for(x=yGetDatabaseCount("worldSplitterHit"); >0) {
				yDatabaseNext("worldSplitterHit");
				startAttack(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("worldSplitterHit"), false, false);
			}
			yClearDatabase("worldSplitterHit");
			castEnd();
		} else {
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("laserProj"), true);
			trSetSelectedScale(trQuestVarGet("scale"), trQuestVarGet("scale"), 50.0);
		}
	}
}