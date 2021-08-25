
const int CAST_UNIT = 0;
const int CAST_TARGET = 1;
const int CAST_SING = 2;
const int CAST_BACKSTAB = 3;
const int CAST_ADJACENT_UNIT = 4;

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


void castAddAdjacentUnit(string qv = "", int p = 0, string src = "", bool commander = true) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	if (commander) {
		trQuestVarSet("cast"+x+"commander", SPELL_COMMANDER);
	} else {
		trQuestVarSet("cast"+x+"commander", SPELL_NONE);
	}
	trQuestVarSet("cast"+x+"type", CAST_ADJACENT_UNIT);
	trQuestVarSet("cast"+x+"player", p);
	trQuestVarSet("cast"+x+"unit", 1*trQuestVarGet(src));
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

void castStart() {
	trQuestVarSet("castDone", CASTING_IN_PROGRESS);
	xsEnableRule("spellcast_00_process");
}

void castEnd() {
	removeDeadUnits();
	refreshGuardAll();
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
		switch(1*trQuestVarGet("cast"+x+"type"))
		{
			case CAST_UNIT:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (HasKeyword(WARD, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
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
					if (HasKeyword(WARD, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
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
			case CAST_BACKSTAB:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (HasKeyword(WARD, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if (mGetVarByQV("allUnits", "player") == p) {
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
						yAddToDatabase("castTiles", "tiles");
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("tiles"), 999999);
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
				for(x=yGetDatabaseCount("castTiles"); >0) {
					yDatabaseNext("castTiles");
					if (trCurrentPlayer() == p) {
						highlightTile(1*trQuestVarGet("casttiles"), 999999);
					}
				}
			}
			case CAST_ADJACENT_TILE:
			{
				tile = mGetVarByQV("cast"+x+"unit", "tile");
				findAvailableTiles(tile, 1, "castTiles", false);
				for(z=yGetDatabaseCount("castTiles"); >0) {
					yDatabaseNext("castTiles");
					if (trCurrentPlayer() == p) {
						highlightTile(1*trQuestVarGet("castTiles"), 999999);
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
					trQuestVarSet("start", mGetVar(1*trQuestVarGet(trStringQuestVarGet("cast"+x+"start")), "tile"));
				} else {
					trQuestVarSet("start", trQuestVarGet(trStringQuestVarGet("cast"+x+"start")));
				}
				float angle = 0.785398;
				trVectorSetUnitPos("pos", "start");
				bool found = true;
				tile = 0;
				// For each direction...
				for(d=6; >0) {
					trVectorSetFromAngle("step", angle);
					trVectorScale("step", 6.0);
					trQuestVarSet("posx", trQuestVarGet("posx") + trQuestVarGet("stepx"));
					trQuestVarSet("posz", trQuestVarGet("posx") + trQuestVarGet("stepz"));
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
								trQuestVarSet("posx", trQuestVarGet("posx") + trQuestVarGet("stepx"));
								trQuestVarSet("posz", trQuestVarGet("posz") + trQuestVarGet("stepz"));
								if (trCurrentPlayer() == p) {
									highlightTile(tile, 999999);
								}
								found = true;
								break;
							}
						}
					}
					angle = fModulo(6.283185, angle + 1.047197);
				}
			}
			case CAST_ADJACENT_UNIT:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (HasKeyword(WARD, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
						if (mGetVarByQV("allUnits", "spell") <= trQuestVarGet("cast"+x+"commander")) {
							trVectorSetUnitPos("d1pos", "allUnits");
							trVectorSetUnitPos("d2pos", "cast"+x+"unit");
							if (zDistanceBetweenVectorsSquared("d1pos", "d2pos") <= 64){
								trUnitSelectClear();
								trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
								yAddToDatabase("castTargets", "allUnits");
								if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
									trUnitHighlight(999999, false);
								}
							}
						}
					}
				}
			}
		}
		xsEnableRule("spellcast_01_select");
		if (yGetDatabaseCount("castTargets") + yGetDatabaseCount("castTiles") == 0) {
			if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
				trSoundPlayFN("cantdothat.wav","1",-1,"","");
				trChatSend(0, "That spell has no valid targets.");
			}
		}
	} else {
		trQuestVarSet("castDone", CASTING_DONE);
	}


	xsDisableRule("spellcast_00_process");
}

void spellcastClearHighlights(int x = 0) {
	/*
	castTargets can be either a tile or the index of a unit in the allUnits database.
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
	castReset();
	switch(spell)
	{
		case SPELL_INTIMIDATE:
		{
			castAddAdjacentUnit("spellTarget", 3 - trQuestVarGet("activePlayer"), "p"+1*trQuestVarGet("activePlayer")+"commander", true);
		}
		case SPELL_GROUND_STOMP:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_PISTOL_SHOT:
		{
			castAddUnit("spellTarget", 0, false);
		}
		case SPELL_RELOAD:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_POISON_CLOUD:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_NATURE_ANGRY:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_PYROBALL:
		{
			castAddUnit("spellTarget", 0, trQuestVarGet("p"+1*trQuestVarGet("activePlayer")+"spellDamage") > 0);
		}
		case SPELL_SPARK:
		{
			castAddUnit("spellTarget", 0);
		}
		case SPELL_FOOD:
		{
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"), false);
		}
		case SPELL_SING:
		{
			castAddSing("spellTarget", 1*trQuestVarGet("activePlayer"));
		}
		case SPELL_MAP:
		{
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"), false);
		}
		case SPELL_BACKSTAB:
		{
			castAddBackstabUnit("spellTarget", 3 - trQuestVarGet("activePlayer"));
		}
		case SPELL_DUEL:
		{
			castAddUnit("allyTarget", 1*trQuestVarGet("activePlayer"), false);
			castAddUnit("enemyTarget", 3 - trQuestVarGet("activePlayer"), false);
		}
		case SPELL_PARTY_UP:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_TEAMWORK:
		{
			castAddUnit("spellTarget", 3 - trQuestVarGet("activePlayer"), false);
		}
		case SPELL_DEFENDER:
		{
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"), false);
		}
		case SPELL_VICTORY:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_WHIRLWIND:
		{
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"), false);
		}
		case SPELL_HEROIC:
		{
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"), false);
		}
		case SPELL_WOLF:
		{
			castAddAdjacentTile("spellTarget", "summonedUnit");
		}
		case SPELL_PING:
		{
			castAddUnit("spellTarget", 0);
		}
		case SPELL_FIRST_AID:
		{
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"), false);
			castAddAdjacentTile("tileTarget", "p"+1*trQuestVarGet("activePlayer")+"commander");
		}
		case SPELL_CLASS_TIME:
		{
			castAddTile("spellTile", true);
		}
		case SPELL_SNIPE:
		{
			castAddUnit("spellShooter", 1*trQuestVarGet("activePlayer"), true);
			castAddTarget("spellTarget", "spellShooter");
		}
		case SPELL_EXPLOSION:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_DOUBLEBLAST:
		{
			castAddUnit("spellTarget1", 3 - trQuestVarGet("activePlayer"), true);
			castAddUnit("spellTarget2", 3 - trQuestVarGet("activePlayer"), true);
		}
		case SPELL_ELECTROSURGE:
		{
			castAddUnit("spellTarget", 3 - trQuestVarGet("activePlayer"), true);
		}
		case SPELL_RUNE_OF_FLAME:
		{
			castAddSummonLocations("spellTarget");
		}
		case SPELL_RUNE_OF_ICE:
		{
			castAddSummonLocations("spellTarget");
		}
		case SPELL_FIRE_AND_ICE:
		{
			castAddSummonLocations("spellTargetFire");
			castAddSummonLocations("spellTargetIce");
		}
		case SPELL_VALKYRIE_HEAL:
		{
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"));
		}
		case SPELL_COPY_HOMEWORK:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_METEOR:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_FINAL_EXAM:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_SHAPESHIFT:
		{
			castAddUnit("copyTarget", 0, false);
			castAddUnit("transformTarget", 0, false);
		}
		case SPELL_APOCALYPSE:
		{
			castAddTile("spellTarget", true);
		}
		case SPELL_MIRROR_IMAGE:
		{
			castAddUnit("spellTarget", 0, false);
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
		bool done = true;
		int activeUnit = 0;
		int target = 0;
		int p = trQuestVarGet("activePlayer");
		int proto = 0;
		float dist = 0;
		trSoundPlayFN("godpower.wav","1",-1,"","");
		bool battlecry = false;
		trQuestVarSet("p"+p+"spellDamage", trCountUnitsInArea("128",p,"Oracle Scout",45));
		switch(1*trQuestVarGet("currentSpell"))
		{
			case SPELL_INTIMIDATE:
			{
				trCameraShake(1.0, 0.1);
				trSoundPlayFN("gaiaattack.wav","1",-1,"","");
				stunUnit(1*trQuestVarGet("spellTarget"));
			}
			case SPELL_GROUND_STOMP:
			{
				trCameraShake(1.0, 0.1);
				trQuestVarSetFromRand("soundRandom", 1, 3, true);
				trSoundPlayFN("woodcrush" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
				trVectorSetUnitPos("d2pos", "p" + p + "commander");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (trQuestVarGet("allUnits") != trQuestVarGet("p" + p + "commander")) {
						trVectorSetUnitPos("d1pos", "allUnits");
						if (zDistanceBetweenVectorsSquared("d1pos", "d2pos") <= 64){
							damageUnit(1*trQuestVarGet("allUnits"), 1 + trQuestVarGet("p" + p + "spellDamage"));
							deployAtTile(0, "Dust Small", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			case SPELL_PISTOL_SHOT:
			{
				addCardToDeck(p, "", SPELL_RELOAD);
				ySetPointer("p"+p+"deck", yGetDatabaseCount("p"+p+"deck"));
				trSoundPlayFN("shockwave.wav","1",-1,"","");				
				trQuestVarSet("spellProjectile", deployAtTile(0, "Dwarf", 1*mGetVarByQV("p" + p + "commander", "tile")));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellProjectile"), true);
				trUnitChangeProtoUnit("Petrobolos Shot");
				trVectorSetUnitPos("spellProjectileStart", "p" + p + "commander");
				trVectorSetUnitPos("spellProjectileEnd", "spellTarget");
				trUnitMoveToVector("spellProjectileEnd");
				done = false;
				xsEnableRule("spell_projectile_complete");
			}
			case SPELL_RELOAD:
			{
				trSoundPlayFN("siegecamp.wav","1",-1,"","");
				trQuestVarSet("p"+p+"drawCards", 1);
			}
			case SPELL_POISON_CLOUD:
			{
				trSoundPlayFN("carnivorabirth.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "player") == 3 - p) {
						if (mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER) {
							mSetVarByQV("allUnits", "keywords", SetBit(1*mGetVarByQV("allUnits", "keywords"), DECAY));
							deployAtTile(0, "Lampades Blood", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			case SPELL_NATURE_ANGRY:
			{
				trCameraShake(3.0, 0.3);
				trSoundPlayFN("gaiaforestambient2.wav","1",-1,"","");
				trQuestVarSetFromRand("soundRandom", 1, 2, true);
				trSoundPlayFN("gaiaattack" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "spell") == SPELL_COMMANDER) {
						if (mGetVarByQV("allUnits", "player") == p) {
							mSetVarByQV("allUnits", "keywords", SetBit(1*mGetVarByQV("allUnits", "keywords"), REGENERATE));
							deployAtTile(0, "Vision SFX", 1*mGetVarByQV("allUnits", "tile"));
						} else {
							mSetVarByQV("allUnits", "keywords", SetBit(1*mGetVarByQV("allUnits", "keywords"), DECAY));
							deployAtTile(0, "Lampades Blood", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			case SPELL_PYROBALL:
			{
				trSoundPlayFN("fireball launch.wav","1",-1,"","");
				trQuestVarSet("spellProjectile", deployAtTile(0, "Dwarf", 1*mGetVarByQV("p" + p + "commander", "tile")));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellProjectile"), true);
				trUnitChangeProtoUnit("Ball of Fire");
				trVectorSetUnitPos("spellProjectileStart", "p" + p + "commander");
				trVectorSetUnitPos("spellProjectileEnd", "spellTarget");
				trUnitMoveToVector("spellProjectileEnd");
				done = false;
				xsEnableRule("spell_projectile_complete");
			}
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
				addCardToDeckByIndex(p, target);
				shuffleDeck(p);
				xsEnableRule("spell_mirror_image_activate");
			}
		}

		if (battlecry == false) {
			if (trCurrentPlayer() == 3 - trQuestVarGet("activePlayer")) {
				trMessageSetText(trStringQuestVarGet("spell_"+1*trQuestVarGet("currentSpell")+"_description"), -1);
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
		int target = ProtoToCard(proto);
		if (yGetDatabaseCount("p"+p+"hand") < 10) {
			addCardToHandByIndex(p, target);
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
	if ((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + trQuestVarGet("lightningActivate") - trQuestVarGet("lightningPop") == 0) || 
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

rule spell_projectile_complete
highFrequency
inactive
{
	trVectorSetUnitPos("spellProjectileStart", "spellProjectile");
	if ((trTime()-cActivationTime) >= 4){
		trVectorQuestVarSet("spellProjectileStart", trVectorQuestVarGet("spellProjectileEnd"));
	}
	if (zDistanceBetweenVectorsSquared("spellProjectileStart", "spellProjectileEnd") < 8) {
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("spellProjectile"), true);
		trUnitDestroy();
		switch(1*trQuestVarGet("currentSpell"))
		{
			case SPELL_PISTOL_SHOT:
			{				
				trSoundPlayFN("arrowonwood1.wav","1",-1,"","");
				trSoundPlayFN("arrowonwood2.wav","1",-1,"","");
				trSoundPlayFN("arrowonflesh3.wav","1",-1,"","");
				trSoundPlayFN("arrowonflesh4.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), 6900);
			}
			case SPELL_PYROBALL:
			{
				trSoundPlayFN("meteorbighit.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), 6 + trQuestVarGet("p"+1*trQuestVarGet("activePlayer")+"spellDamage"));
				deployAtTile(0, "Meteor Impact Ground", 1*mGetVarByQV("spellTarget", "tile"));
			}
		}
		castEnd();
		xsDisableRule("spell_projectile_complete");
	}
}