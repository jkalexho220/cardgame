
const int CAST_UNIT = 0;
const int CAST_TARGET = 1;
const int CAST_SING = 2;
const int CAST_BACKSTAB = 3;
const int CAST_CONVERT = 4;
const int CAST_MAGNETIZE = 5;
const int CAST_ADJACENT_UNIT = 6;
const int CAST_MIRROR_REFLECTION = 7;

const int CAST_TILE = 10;
const int CAST_ADJACENT_TILE = 11;
const int CAST_DIRECTION = 12;
const int CAST_SUMMON_LOCATIONS = 13;
const int CAST_ADJACENT_TILE_UNKNOWN = 14;

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

void castAddMirrorReflectionUnit(string qv = "", int p = 0) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");
	trQuestVarSet("cast"+x+"commander", SPELL_NONE);
	trQuestVarSet("cast"+x+"type", CAST_MIRROR_REFLECTION);
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
qv = name of the quest var to store the selected tile
src = name of quest var holding the unit at the center (not yet known)
*/
void castAddAdjacentTileUnknown(string qv = "", string src = "") {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");
	
	trQuestVarSet("cast"+x+"type", CAST_ADJACENT_TILE_UNKNOWN);
	trStringQuestVarSet("cast"+x+"qv", qv);
	trStringQuestVarSet("cast"+x+"from", src);
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
qv = name of the quest var to store the selected unit
unit = name of quest var holding the index of the magnetizing unit. This will
only highlight targets that are within range of the magnetizer.
*/
void castAddMagnetize(string qv = "", string unit = "") {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");
	
	trQuestVarSet("cast"+x+"type", CAST_MAGNETIZE);
	trStringQuestVarSet("cast"+x+"start", unit);
	trStringQuestVarSet("cast"+x+"qv", qv);
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
		if (1*mGetVar(unit, "echo") <= 0 && (HasKeyword(REPEATABLE, 1*mGetVar(unit, "keywords")) || trCountUnitsInArea("128",p,"Hero Greek Heracles",45) > 0)) {
			generateCard(p, 0, 1*mGetVar(unit, "spell"), true);
			if(HasKeyword(FLEETING, 1*mGetVarByQV("next", "keywords"))){
				mSetVarByQV("next", "echo", 1);
			}
		}
		if (trQuestVarGet("p"+p+"commanderType") == COMMANDER_REACH) {
			trQuestVarSet("p"+p+"extraManaflow", cost + trQuestVarGet("p"+p+"extraManaflow"));
		}
		trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") - xsMax(0, cost));
		updateMana();
		ySetPointer("p"+p+"hand", 1*trQuestVarGet("selectedCard"));
		zSetVarByIndex("p"+p+"handPos", "occupied", 1*yGetVar("p"+p+"hand", "pos"), 0);
		yRemoveFromDatabase("p"+p+"hand");
		
		updateHandPlayable(p);
		
		/*
		Effects that occur whenever a spell is cast
		*/
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits", true);
			if (mGetVarByQV("allUnits", "player") == p) {
				switch(1*mGetVarByQV("allUnits", "proto"))
				{
					case kbGetProtoUnitID("Petsuchos"):
					{
						mSetVarByQV("allUnits", "range", 3);
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
					}
					case kbGetProtoUnitID("Pharaoh of Osiris"):
					{
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
						trQuestVarSet("p"+p+"yeebbonus", 1 + trQuestVarGet("p"+p+"yeebbonus"));
					}
					case kbGetProtoUnitID("Javelin Cavalry Hero"):
					{
						if (mGetVarByQV("allUnits", "action") == ACTION_DONE) {
							mSetVarByQV("allUnits", "action", ACTION_READY);
							deployAtTile(0, "Arkantos Boost SFX", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			if (mGetVarByQV("allUnits", "proto") == kbGetProtoUnitID("Swordsman Hero")) {
				spyEffect(1*trQuestVarGet("allUnits"), "Einheriar Boost SFX");
				mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
				deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
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
					if (HasKeyword(STEALTH, 1*mGetVarByQV("allUnits", "keywords"))) {
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
					if (HasKeyword(STEALTH, 1*mGetVarByQV("allUnits", "keywords"))) {
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
			case CAST_CONVERT:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (HasKeyword(STEALTH, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
						if (mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER && mGetVarByQV("allUnits", "cost") <= trQuestVarGet("p"+1*trQuestVarGet("activePlayer")+"manaflow")) {
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
					if (HasKeyword(STEALTH, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if (mGetVarByQV("allUnits", "player") == p) {
						if (trCountUnitsInArea(""+1*trQuestVarGet("allUnits"), p, "Unit", 8) + trCountUnitsInArea(""+1*trQuestVarGet("allUnits"), p, "Building", 8) > 1) {
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
			case CAST_ADJACENT_TILE_UNKNOWN:
			{
				tile = mGetVarByQV(trStringQuestVarGet("cast"+x+"from"), "tile");
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
			case CAST_MAGNETIZE:
			{
				trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet(trStringQuestVarGet("cast"+x+"start"))));
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((trQuestVarGet("allUnits") == trQuestVarGet(trStringQuestVarGet("cast"+x+"start"))) || (mGetVarByQV("allUnits", "player") == 3 - p)) {
						continue;
					} else if (HasKeyword(MAGNETIC, 1*mGetVarByQV("allUnits", "keywords")) &&
						trDistanceToVectorSquared("allUnits", "pos") < 40) {
						yAddToDatabase("castTargets", "allUnits");
						if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("allUnits"));
							trUnitHighlight(999999, false);
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
					trVectorQuestVarSet("step", trGetUnitVector("pos", "target", 6.0));
					trVectorQuestVarSet("pos", trVectorQuestVarGet("pos") + trVectorQuestVarGet("step"));
					tile = trQuestVarGet("start");
					found = true;
					while(found) {
						found = false;
						// Travel down the line and highlight tiles
						for(z=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
							trVectorQuestVarSet("current", kbGetBlockPosition(""+1*zGetVarByIndex("tiles", "neighbor"+z, tile)));
							if (trDistanceBetweenVectorsSquared("current", "pos") < 1) {
								tile = zGetVarByIndex("tiles", "neighbor"+z, tile);
								trQuestVarSet("currentTile", tile);
								yAddToDatabase("castTiles", "currentTile");
								trVectorQuestVarSet("pos", trVectorQuestVarGet("step") + trVectorQuestVarGet("current"));
								if (trCurrentPlayer() == p) {
									highlightTile(tile, 999999);
								}
								found = true;
								break;
							}
						}
						if (tile >= trQuestVarGet("ztilesend")) {
							found = false;
						}
					}
				}
			}
			case CAST_ADJACENT_UNIT:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (HasKeyword(STEALTH, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
						if (mGetVarByQV("allUnits", "spell") <= trQuestVarGet("cast"+x+"commander")) {
							trVectorSetUnitPos("d1pos", "allUnits");
							trVectorSetUnitPos("d2pos", "cast"+x+"unit");
							if (trDistanceBetweenVectorsSquared("d1pos", "d2pos") < 64){
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
			case CAST_MIRROR_REFLECTION:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (HasKeyword(STEALTH, 1*mGetVarByQV("allUnits", "keywords"))) {
						continue;
					} else if ((mGetVarByQV("allUnits", "player") == p) || (p == 0)) {
						if (mGetVarByQV("allUnits", "spell") <= trQuestVarGet("cast"+x+"commander")) {
							trVectorSetUnitPos("spellProjectileStart", "allUnits");
							trVectorQuestVarSet("temp", kbGetBlockPosition("128"));
							trVectorQuestVarSet("temp", xsVectorSet(trVectorQuestVarGetX("temp") - trVectorQuestVarGetX("spellProjectileStart"), 0, trVectorQuestVarGetZ("temp")  - trVectorQuestVarGetZ("spellProjectileStart")));
							trVectorQuestVarSet("spellProjectileEnd", kbGetBlockPosition("128"));
							trVectorQuestVarSet("spellProjectileEnd", xsVectorSet(trVectorQuestVarGetX("spellProjectileEnd") + trVectorQuestVarGetX("temp"), 0, trVectorQuestVarGetZ("spellProjectileEnd")  + trVectorQuestVarGetZ("temp")));
							zBankNext("tiles");
							trQuestVarSet("temp", trQuestVarGet("tiles"));
							for (x=zGetBankCount("tiles"); >0) {
								zBankNext("tiles");
								if (trDistanceToVectorSquared("tiles", "spellProjectileEnd") < trDistanceToVectorSquared("temp", "spellProjectileEnd")) {
									trQuestVarSet("temp", trQuestVarGet("tiles"));
								}
							}
							if(zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("temp")) + zGetVarByIndex("tiles", "terrain", 1*trQuestVarGet("temp")) == 0){
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
			}
		}
		xsEnableRule("spellcast_01_select");
		if (yGetDatabaseCount("castTargets") + yGetDatabaseCount("castTiles") == 0) {
			if (trCurrentPlayer() == 1*trQuestVarGet("activePlayer")) {
				trMessageSetText("No valid targets.", -1);
			}
		}
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
						
						if (trDistanceToVectorSquared("castTargets", "p"+p+"clickPos") < 8) {
							trQuestVarCopy(trStringQuestVarGet("cast"+x+"qv"), "castTargets");
							selected = true;
							break;
						}
					}
				} else {
					for(z=yGetDatabaseCount("castTiles"); >0) {
						yDatabaseNext("castTiles");
						
						if (trDistanceToVectorSquared("castTiles", "p"+p+"clickPos") < 8) {
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
						if (trDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos") < 4) {
							spellcastClearHighlights(x);
							castReset();
							trQuestVarSet("castDone", CASTING_CANCEL);
							castRestoreWard();
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
		case SPELL_INTIMIDATE:
		{
			castAddAdjacentUnit("spellTarget", 3 - trQuestVarGet("activePlayer"), "p"+1*trQuestVarGet("activePlayer")+"commander", true);
			castInstructions("Choose an enemy adjacent to your commander. Right click to cancel.");
		}
		case SPELL_GROUND_STOMP:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_BOOTS_TREASURE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_WEAPONS_TREASURE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_SHIELDS_TREASURE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_PISTOL_SHOT:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_RELOAD:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_POISON_CLOUD:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_NATURE_ANGRY:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_ELVEN_APOCALYPSE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_CORONA_APOCALYPSE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_METAL_GEAR:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_MIRROR_REFLECTION:
		{
			castAddMirrorReflectionUnit("spellTarget", 0);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_PYROBALL:
		{
			castAddUnit("spellTarget", 0, trQuestVarGet("p"+1*trQuestVarGet("activePlayer")+"spellDamage") > 0);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_KRAKEN_HUG:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_WATER_PRESSURE:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit.");
		}
		case SPELL_OXYGEN_TANK:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_SPARK:
		{
			castAddUnit("spellTarget", 0);
			castInstructions("Choose any unit. Right click to cancel.");
		}
		case SPELL_FOOD:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit to give +1 attack and health to.");
		}
		case SPELL_BAD_FOOD:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy unit to give -2 attack.");
		}
		case SPELL_SING:
		{
			castAddSing("spellTarget", p);
			castInstructions("Choose an ally that has already acted. Right click to cancel.");
		}
		case SPELL_MAP:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit to give +1 speed and Pathfinder to.");
		}
		case SPELL_BACKSTAB:
		{
			castAddBackstabUnit("spellTarget", 3 - p);
			castInstructions("Choose an enemy that is adjacent to another enemy. Right click to cancel.");
		}
		case SPELL_DUEL:
		{
			castAddUnit("allyTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
			castAddUnit("enemyTarget", 3 - p, false);
			castInstructions("Choose an enemy unit. Right click to cancel.");
		}
		case SPELL_PARTY_UP:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_TEAMWORK:
		{
			castAddUnit("cheerTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
		}
		case SPELL_DEFENDER:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
		}
		case SPELL_VICTORY:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right clickto cancel.");
		}
		case SPELL_WHIRLWIND:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
		}
		case SPELL_SUMMON_ONE:
		{
			castAddAdjacentTile("spellTarget", "summonedUnit");
			castInstructions("Choose a tile to summon a random 1-cost unit from your deck.");
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
			castInstructions("Choose an allied unit. Right click to cancel.");
			castAddAdjacentTile("tileTarget", "p"+p+"commander");
			castInstructions("Choose a tile to teleport it to. Right click to cancel.");
		}
		case SPELL_SONG_OF_REST:
		{
			castAddTile("spellTile", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_CLASS_TIME:
		{
			castAddTile("spellTile", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_SNIPE:
		{
			castAddUnit("spellShooter", p, true);
			castInstructions("Choose an allied unit. Right click to cancel.");
			castAddTarget("spellTarget", "spellShooter");
			castInstructions("Choose an enemy within range to attack. Right click to cancel.");
		}
		case SPELL_EXPLOSION:
		{
			castAddTile("spellTarget", true);
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_MAGIC_MISSILES:
		{
			castAddUnit("spellTarget1", 3 - p, true);
			castInstructions("Choose the first target. Right click to cancel.");
			castAddUnit("spellTarget2", 3 - p, true);
			castInstructions("Choose the second target. Right click to cancel.");
			castAddUnit("spellTarget3", 3 - p, true);
			castInstructions("Choose the third target. Right click to cancel.");
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
		case SPELL_ELECTROBALL:
		{
			castAddTile("spellTarget", false);
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
			castInstructions("Choose a unit to transform.");
			castAddUnit("copyTarget", 0, false);
			castInstructions("Choose a unit to copy.");
		}
		case SPELL_APOCALYPSE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_MIRROR_IMAGE:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_MEDUSA_STUN:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy to stun.");
		}
		case SPELL_LAMPADES_CONVERT:
		{
			castAddConvertUnit("spellTarget", 3 - p);
			castInstructions("Choose an enemy unit that costs {Manaflow} or less to convert.");
		}
		case SPELL_WATER_CANNON:
		{
			castAddUnit("spellTarget", 0, false);
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
			castInstructions("Choose an allied unit. Right click to cancel.");
		}
		case SPELL_TELETIDE:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
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
		case SPELL_SERPENT_SKIN:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_DEVOUR:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_DEMON_EAT:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose a unit to devour.");
		}
		case SPELL_SCORPION_STING:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit to teleport.");
			castAddAdjacentTile("spellTile", "spellCaster");
			castInstructions("Choose a tile to teleport it to.");
		}
		case SPELL_DUPLICATE_FRIEND:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit to duplicate.");
			castAddAdjacentTileUnknown("spellTile", "spellTarget");
			castInstructions("Choose a tile to summon the duplicate.");
		}
		case SPELL_WORLD_SPLITTER:
		{
			if (trQuestVarGet("p"+p+"commanderType") == COMMANDER_ZENOPHOBIA) {
				castAddUnit("spellTarget", p, true);
				castInstructions("Choose an ally. Right click to cancel.");
			} else {
				castAddUnit("spellTarget", p, false);
				castInstructions("Choose an allied unit. Right click to cancel.");
			}
			castAddDirection("spellDirection", "spellTarget", true);
			castInstructions("Choose a direction. Right click to cancel.");
		}
		case SPELL_SOUL_SIPHON:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
		}
		case SPELL_BLOOD_PRICE:
		{
			castAddUnit("allyTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
			castAddUnit("enemyTarget", 3-p, true);
			castInstructions("Choose an enemy. Right click to cancel.");
		}
		case SPELL_DEATH_APPROACHES:
		{
			castAddAdjacentTile("spellTarget", "p"+(3-p)+"commander");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_DEATH_DOOR:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy unit. Right click to cancel.");
		}
		case SPELL_POISON_MIST:
		{
			castAddTile("spellTarget", true);
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
			castInstructions("Choose an allied unit. Right click to cancel.");
		}
		case SPELL_FINAL_FRENZY:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_CORPSE_PARTY:
		{
			castAddSummonLocations("spellTarget1");
			castInstructions("Choose a tile (1/3). Right click to cancel.");
			castAddSummonLocations("spellTarget2");
			castInstructions("Choose a tile (2/3). Right click to cancel.");
			castAddSummonLocations("spellTarget3");
			castInstructions("Choose a tile (3/3). Right click to cancel.");
		}
		case SPELL_CALL_OF_THE_DEEP:
		{
			castAddSummonLocations("spellTarget");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_RUNE_OF_DARKNESS:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
			castAddSummonLocations("spellTarget1");
			castInstructions("Choose a tile (1/2). Right click to cancel.");
			castAddSummonLocations("spellTarget2");
			castInstructions("Choose a tile (2/2). Right click to cancel.");
		}
		case SPELL_ZENOS_PARADOX:
		{
			castAddUnit("spellTarget1", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
			castAddUnit("spellTarget2", 3 - p, false);
			castInstructions("Choose an enemy unit. Right click to cancel.");
		}
		case SPELL_SCRAP_METAL:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_MAGNETIZE:
		{
			castAddMagnetize("spellTarget", "spellCaster");
			castInstructions("Choose a unit to Magnetize to. Right click to cancel.");
		}
		case SPELL_ELECTRIC_GRID:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_ZAP_GUN:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_COMPRESS:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_UPGRADE:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_PROFITEERING:
		{
			castAddSummonLocations("spellTarget");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_WARNING_SHOT:
		{
			castAddUnit("spellTarget", 0, true);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_NANOMACHINES:
		{
			castAddUnit("spellTarget", p, false);
			castInstructions("Choose an allied unit. Right click to cancel.");
		}
		case SPELL_REWIND:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy unit. Right click to cancel.");
		}
		case SPELL_TIME_POCKET:
		{
			castAddTile("spellTarget", true);
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_BANHAMMER:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy unit. Right click to cancel.");
		}
		case SPELL_POWER_SUIT:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_GEAR_FACTORY:
		{
			castAddSummonLocations("spellTarget");
			castInstructions("Choose a tile. Right click to cancel.");
		}
		case SPELL_ASSEMBLY_LINE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_BULLET_TIME:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_FORTIFY:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_CHOOSE_DIRECTION:
		{
			castAddDirection("spellDirection", "spellCaster", true);
			castInstructions("Choose a direction to aim the Directional Cannon");
		}
		case SPELL_SPIDER_LAIR:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_TAVERN_BRAWL:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_DOMINANCE:
		{
			castAddUnit("spellTarget", 3 - p, false);
			castInstructions("Choose an enemy unit. Right click to cancel.");
		}
		case SPELL_NICKS_PORTAL:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_PETTY_LASER:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_THICK_LASER:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_GRAND_LASER:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_OMEGA_LASER:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_GODLY_LASER:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_SPACE_VENT:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_REFRESH_MANA:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_ARIES:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_AQUARIUS:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_LIBRA:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_PISCES:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_THE_CALLING:
		{
			castAddSummonLocations("spellTarget");
			castInstructions("Click on a tile to cast. Right click to cancel.");
		}
		case SPELL_DUPLICATE_ME:
		{
			castAddAdjacentTile("spellTarget", "spellCaster");
			castInstructions("Click on a tile to summon a duplicate.");
		}
		case SPELL_BULLET_STORM:
		{
			// if the bot is casting, we make sure it only casts when enemies are in range.
			if ((p == 2) && (Multiplayer == false)) {
				castAddTarget("spellTarget", "p"+p+"commander");
				castInstructions("Get in there and fight, maggot!");
			} else {
				castAddTile("spellTarget", true);
				castInstructions("Click on a tile to cast. Right click to cancel.");
			}
		}
		case SPELL_COPY_ATTACK_EFFECT:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit to copy the Attack effect of.");
		}
		case SPELL_HORROR_MENAGERIE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_RIDE_THE_LIGHTNING:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_RECHARGE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_BLITZ:
		{
			castAddUnit("spellTarget", 3 - p, true);
			castInstructions("Choose a unit. Right click to cancel.");
			castAddAdjacentTileUnknown("spellTile", "spellTarget");
			castInstructions("Choose a tile to teleport. Right click to cancel.");
		}
		case SPELL_MOONBEAM:
		{
			castAddUnit("spellTarget", 0, false);
			castInstructions("Choose a unit. Right click to cancel.");
		}
		case SPELL_CRESCENT_STRIKE:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
		}
		case SPELL_PROTECTION:
		{
			castAddTile("spellTarget", true);
			castInstructions("Click on any tile to cast. Right click to cancel.");
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
		vector start = vector(0,0,0);
		vector step = vector(0,0,0);
		vector end = vector(0,0,0);
		vector dir = vector(0,0,0);
		vector pos = vector(0,0,0);
		trSoundPlayFN("godpower.wav","1",-1,"","");
		trQuestVarSet("p"+p+"spellDamage", trCountUnitsInArea("128",p,"Oracle Scout",45) + trQuestVarGet("p"+p+"spellDamageNonOracle"));
		switch(spell)
		{
			case SPELL_INTIMIDATE:
			{
				trCameraShake(1.0, 0.1);
				trSoundPlayFN("gaiaattack.wav","1",-1,"","");
				stunUnit(1*trQuestVarGet("spellTarget"));
			}
			case SPELL_GROUND_STOMP:
			{
				trQuestVarSetFromRand("soundRandom", 1, 3, true);
				trSoundPlayFN("woodcrush" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (trQuestVarGet("allUnits") != trQuestVarGet("p" + p + "commander")) {
						trVectorSetUnitPos("d1pos", "allUnits");
						trVectorSetUnitPos("d2pos", "p" + p + "commander");
						if (trDistanceBetweenVectorsSquared("d1pos", "d2pos") < 64){
							damageUnit(1*trQuestVarGet("allUnits"), 1 + trQuestVarGet("p" + p + "spellDamage"));
							deployAtTile(0, "Dust Small", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			case SPELL_BOOTS_TREASURE:
			{
				trSoundPlayFN("plentybirth.wav","1",-1,"","");
				trSoundPlayFN("longhouse.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (1*mGetVarByQV("allUnits", "player") == p) {
						if (1*mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER) {
							mSetVarByQV("allUnits", "keywords", SetBit(1*mGetVarByQV("allUnits", "keywords"), ETHEREAL));
							deployAtTile(0, "Fireball Launch Damage Effect", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			case SPELL_WEAPONS_TREASURE:
			{
				trSoundPlayFN("plentybirth.wav","1",-1,"","");
				trSoundPlayFN("barracks.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (1*mGetVarByQV("allUnits", "player") == p) {
						if (1*mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER) {
							mSetVarByQV("allUnits", "attack", mGetVarByQV("allUnits", "attack") + 2);
							deployAtTile(0, "Fireball Launch Damage Effect", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			case SPELL_SHIELDS_TREASURE:
			{
				trSoundPlayFN("plentybirth.wav","1",-1,"","");
				trSoundPlayFN("bronzebirth.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (1*mGetVarByQV("allUnits", "player") == p) {
						if (1*mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER) {
							mSetVarByQV("allUnits", "health", mGetVarByQV("allUnits", "health") + 3);
							mSetVarByQV("allUnits", "maxhealth", mGetVarByQV("allUnits", "maxhealth") + 3);
							deployAtTile(0, "Fireball Launch Damage Effect", 1*mGetVarByQV("allUnits", "tile"));
						}
					}
				}
			}
			
			case SPELL_PISTOL_SHOT:
			{
				addCardToDeck(p, "", SPELL_RELOAD, true);
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
					if (1*mGetVarByQV("allUnits", "player") == 3 - p) {
						if (1*mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER) {
							deployAtTile(0, "Lampades Blood", 1*mGetVarByQV("allUnits", "tile"));
							if (HasKeyword(DECAY, 1*mGetVarByQV("allUnits", "keywords"))) {
								damageUnit(1*trQuestVarGet("allUnits"), 5 + trQuestVarGet("p"+p+"spellDamage"));
							} else {
								mSetVarByQV("allUnits", "keywords", SetBit(1*mGetVarByQV("allUnits", "keywords"), DECAY));
							}
						}
					}
				}
			}
			case SPELL_FROST_BREATH:
			{
				trSoundPlayFN("frostgiantattack.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (1*mGetVarByQV("allUnits", "player") == 3 - p) {
						if (1*mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER) {
							deployAtTile(0, "Icy Footprint", 1*mGetVarByQV("allUnits", "tile"));
							if (mGetVarByQV("allUnits", "stunTime") > 0) {
								damageUnit(1*trQuestVarGet("allUnits"), 3 + trQuestVarGet("p"+p+"spellDamage"));
							} else {
								stunUnit(1*trQuestVarGet("allUnits"));
							}
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
					if (mGetVarByQV("allUnits", "player") == p) {
						healUnit(1*trQuestVarGet("allUnits"), 1*mGetVarByQV("allUnits", "health"));
						deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("allUnits", "tile"));
					} else {
						mSetVarByQV("allUnits", "keywords", SetBit(1*mGetVarByQV("allUnits", "keywords"), DECAY));
						deployAtTile(0, "Lampades Blood", 1*mGetVarByQV("allUnits", "tile"));
					}
				}
			}
			case SPELL_ELVEN_APOCALYPSE:
			{
				trSoundPlayFN("temple.wav","1",-1,"","");
				trSoundPlayFN("battlecry4.wav","1",-1,"","");
				
				trQuestVarSet("apocalypse", 2);
				musicToggleBattleMode();
				xsEnableRule("spell_elven_apocalypse_activate");
			}
			case SPELL_CORONA_APOCALYPSE:
			{
				trSoundPlayFN("Heaven Games\legendary.wav", "3", -1, "","");
				
				trQuestVarSet("apocalypse", 2);
				musicToggleBattleMode();
				xsEnableRule("spell_corona_apocalypse_activate");
			}
			case SPELL_METAL_GEAR:
			{
				trQuestVarSetFromRand("soundRandom", 1, 2, true);
				if(trQuestVarGet("soundRandom") == 1){
					CharacterLog(3-p, trStringQuestVarGet("card_" + mGetVarByQV("p"+(3-p)+"commander", "proto") + "_name"), "I need help!");
					trSoundPlayFN("xpack\xtaunts\en\012 i need help.mp3", "2", -1, "","");
				} else {
					CharacterLog(3-p, trStringQuestVarGet("card_" + mGetVarByQV("p"+(3-p)+"commander", "proto") + "_name"), "*screaming*");
					trSoundPlayFN("xpack\xtaunts\en\029 scream.mp3", "2", -1, "","");
				}
				
				trQuestVarSet("apocalypse", 2);
				musicToggleBattleMode();
				xsEnableRule("spell_metal_gear_activate");
			}
			case SPELL_MIRROR_REFLECTION:
			{
				trSoundPlayFN("lapadesconvert.wav","1",-1,"","");
				trQuestVarSet("spellProjectile", deployAtTile(0, "Dwarf", 1*mGetVarByQV("spellTarget", "tile")));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellProjectile"), true);
				trUnitChangeProtoUnit("Lampades Bolt");
				trVectorSetUnitPos("spellProjectileStart", "spellTarget");
				trVectorQuestVarSet("temp", kbGetBlockPosition("128"));
				trVectorQuestVarSet("temp", xsVectorSet(trVectorQuestVarGetX("temp") - trVectorQuestVarGetX("spellProjectileStart"), 0, trVectorQuestVarGetZ("temp")  - trVectorQuestVarGetZ("spellProjectileStart")));
				trVectorQuestVarSet("spellProjectileEnd", kbGetBlockPosition("128"));
				trVectorQuestVarSet("spellProjectileEnd", xsVectorSet(trVectorQuestVarGetX("spellProjectileEnd") + trVectorQuestVarGetX("temp"), 0, trVectorQuestVarGetZ("spellProjectileEnd")  + trVectorQuestVarGetZ("temp")));
				trUnitMoveToVector("spellProjectileEnd");
				done = false;
				xsEnableRule("spell_projectile_complete");
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
			case SPELL_KRAKEN_HUG:
			{
				trSoundPlayFN("krakendeath.wav","1",-1,"","");
				trSoundPlayFN("shipdeathsplash.wav","1",-1,"","");
				trQuestVarSet("p"+(3-p)+"drawCards", 8*trCountUnitsInArea("128",(3-p),"Unit",45));
			}
			case SPELL_WATER_PRESSURE:
			{
				trSoundPlayFN("shipdeathsplash.wav","1",-1,"","");
				trSoundPlayFN("underminebirth.wav","1",-1,"","");
				trSoundPlayFN("underminebirth.wav","1",-1,"","");
				trSoundPlayFN("underminebirth.wav","1",-1,"","");
				trSoundPlayFN("underminebirth.wav","1",-1,"","");
				deployAtTile(0, "Meteor Impact Water", 1*mGetVarByQV("spellTarget", "tile"));
				mSetVarByQV("spellTarget", "attack", 1);
				mSetVarByQV("spellTarget", "health", 1);
			}
			case SPELL_OXYGEN_TANK:
			{
				trSoundPlayFN("garrison.wav","1",-1,"","");
				trSoundPlayFN("gaiatreesprout2.wav","1",-1,"","");
				trSoundPlayFN("villagercreate.wav","1",-1,"","");
				addCardToDeck(p, "", SPELL_OXYGEN_TANK, true);
				shuffleDeck(p);
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
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "attack", 1 + mGetVar(target, "attack"));
				mSetVar(target, "health", 1 + mGetVar(target, "health"));
				mSetVar(target, "maxhealth", 1 + mGetVar(target, "maxhealth"));
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
				trSoundPlayFN("colossuseat.wav","1",-1,"","");
				trSoundPlayFN("researchcomplete.wav","1",-1,"","");
				trUnitSelectClear();
				trUnitSelect(""+target);
				spyEffect(target, "Einheriar Boost SFX");
			}
			case SPELL_BAD_FOOD:
			{
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "attack", xsMax(0, mGetVar(target, "attack") - 2));
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
				trSoundPlayFN("colossuseat.wav","1",-1,"","");
				trSoundPlayFN("pestilencebirth.wav","1",-1,"","");
			}
			case SPELL_SING:
			{
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "action", ACTION_READY);
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
				deployAtTile(0, "Arkantos Boost SFX", 1*mGetVar(target, "tile"));
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
				trSoundPlayFN("battlecry2.wav","1",-1,"","");
				mSetVarByQV("cheerTarget", "attack", 1 + mGetVarByQV("cheerTarget", "attack"));
				mSetVarByQV("cheerTarget", "health", 1 + mGetVarByQV("cheerTarget", "health"));
				mSetVarByQV("cheerTarget", "maxhealth", 1 + mGetVarByQV("cheerTarget", "maxhealth"));
				xsEnableRule("cheer_activate"); // this trigger is placed in OnPlay lol
			}
			case SPELL_DEFENDER:
			{
				trSoundPlayFN("fortress.wav","1",-1,"","");
				trSoundPlayFN("researchcomplete.wav","1",-1,"","");
				target = 1*trQuestVarGet("spellTarget");
				mSetVar(target, "health", 2 + mGetVar(target, "health"));
				mSetVar(target, "maxhealth", 2 + mGetVar(target, "maxhealth"));
				mSetVar(target, "keywords", SetBit(1*mGetVar(target, "keywords"), GUARD));
				deployAtTile(0, "Hero Birth", 1*mGetVar(target, "tile"));
				refreshGuardAll();
			}
			case SPELL_WOLF:
			{
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
			case SPELL_SUMMON_ONE:
			{
				done = false;
				trSoundPlayFN("mythcreate.wav","1",-1,"","");
				for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
					proto = yDatabaseNext("p"+p+"deck");
					if ((trQuestVarGet("card_"+proto+"_cost") == 1) && (yGetVar("p"+p+"deck", "spell") == SPELL_NONE)) {
						yRemoveFromDatabase("p"+p+"deck");
						done = true;
						break;
					}
				}
				if (done) {
					activeUnit = summonAtTile(1*trQuestVarGet("spellTarget"),p,proto);
					if (HasKeyword(CHARGE, 1*mGetVar(activeUnit, "keywords"))) {
						mSetVar(activeUnit, "action", ACTION_READY);
					} else {
						mSetVar(activeUnit, "action", ACTION_SLEEPING);
					}
				}
				done = true;
			}
			case SPELL_SONG_OF_REST:
			{
				trSoundPlayFN("restorationbirth.wav","1",-1,"","");
				trSoundPlayFN("heal.wav","1",-1,"","");
				healUnit(1*trQuestVarGet("p"+p+"commander"), 6);
				deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
				trQuestVarSet("p"+p+"drawCards", 1 + trQuestVarGet("p"+p+"drawCards"));
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
			}
			case SPELL_FIRST_AID:
			{
				trSoundPlayFN("villagercreate.wav","1",-1,"","");
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("spellTarget", "tile"), 0);
				teleportToTile(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("tileTarget"));
				healUnit(1*trQuestVarGet("spellTarget"), 5);
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
						if (trDistanceToVectorSquared("allUnits", "pos") < 64) {
							damageUnit(1*trQuestVarGet("allUnits"), 1 + trQuestVarGet("p"+p+"spellDamage"));
						}
					}
				}
			}
			case SPELL_MAGIC_MISSILES:
			{
				trSoundPlayFN("suckup1.wav");
				trSoundPlayFN("lapadesconvert.wav");
				trVectorQuestVarSet("magicMissilesCenter", kbGetBlockPosition(""+1*trQuestVarGet("p"+p+"commander")));
				trQuestVarSetFromRand("rand", 0, 3.141592, false);
				dir = xsVectorSet(xsCos(trQuestVarGet("rand")),0,xsSin(trQuestVarGet("rand"))) * 10.0;
				for(i=1; <= 3) {
					trQuestVarSet("next", deployAtTile(0, "Cinematic Block", mGetVarByQV("p"+p+"commander", "tile")));
					yAddToDatabase("magicMissiles", "next");
					trUnitSelectClear();
					trUnitSelectByQV("next", true);
					trMutateSelected(kbGetProtoUnitID("Outpost"));
					trSetSelectedScale(0,0,0);
					yAddUpdateVar("magicMissiles", "target", trQuestVarGet("spellTarget"+i));
					yAddUpdateVector("magicMissiles", "targetPos", kbGetBlockPosition(""+1*trQuestVarGet("spellTarget"+i)));
					yAddUpdateVector("magicMissiles", "pos", trVectorQuestVarGet("magicMissilesCenter"));
					yAddUpdateVector("magicMissiles", "dir", dir);
					dir = rotationMatrix(dir, -0.5, 0.866025);
				}
				done = false;
				xsEnableRule("magic_missiles_active");
				trQuestVarSet("magicMissilesTime", trTimeMS());
				trQuestVarSet("magicMissilesStartTime", trTimeMS());
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
					if ((Multiplayer == false) && (p == 2)) {
						trQuestVarSet("selectedCard", -1);
					} else {
						done = false;
						chooseSpell(SPELL_FIRE_AND_ICE, 1*trQuestVarGet("selectedCard"));
					}
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
				trVectorSetUnitPos("healerPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTarget");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(trGetUnitVector("healerPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(50, 0, false, true, -1);
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
			case SPELL_ELECTROBALL:
			{
				trSoundPlayFN("lapadesconvert.wav");
				trQuestVarSet("next", deployAtTile(0, "Spy Eye", 1*trQuestVarGet("spellTarget")));
				trUnitSelectClear();
				trUnitSelectByQV("next");
				trMutateSelected(kbGetProtoUnitID("Arkantos God"));
				trUnitOverrideAnimation(26, 0, true, false, -1);
				trSetSelectedScale(0,0,0);
				yAddToDatabase("electroballs", "next");
				yAddUpdateVar("electroballs", "tile", trQuestVarGet("spellTarget"));
				yAddUpdateVar("electroballs", "player", p);
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
				mSetVar(activeUnit, "laserDirx", mGetVar(target, "laserDirx"));
				mSetVar(activeUnit, "laserDirz", mGetVar(target, "laserDirz"));
				mSetVar(activeUnit, "keywords", mGetVar(target, "keywords"));
				mSetVar(activeUnit, "onAttack", mGetVar(target, "onAttack"));
				mSetVar(activeUnit, "onDeath", mGetVar(target, "onDeath"));
				mSetVar(activeUnit, "scale", mGetVar(target, "scale"));
				scaleUnit(activeUnit);
				mSetString(activeUnit, "ability", mGetString(target, "ability"));
				deployAtTile(0, "Kronny Birth SFX", 1*mGetVar(activeUnit, "tile"));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trUnitOverrideAnimation(39,0,false,true,-1);
				trUnitSelectClear();
				trUnitSelect(""+activeUnit);
				trUnitChangeProtoUnit(kbGetProtoUnitName(1*mGetVar(activeUnit, "proto")));
				damageUnit(activeUnit, 0);
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
				// if commander is not nottud
				if (trQuestVarGet("p"+p+"commanderType") != COMMANDER_NOTTUD) {
					addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("spellTarget", "proto")), 0, true);
				}
				shuffleDeck(p);
				xsEnableRule("spell_mirror_image_activate");
			}
			case SPELL_MEDUSA_STUN:
			{
				trVectorSetUnitPos("casterPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTarget");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(trGetUnitVector("casterPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(40, 0, false, true, -1);
				stunUnit(1*trQuestVarGet("spellTarget"));
			}
			case SPELL_LAMPADES_CONVERT:
			{
				trVectorSetUnitPos("casterPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTarget");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(trGetUnitVector("casterPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(37, 0, false, true, -1);
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				trUnitConvert(p);
				mSetVarByQV("spellTarget", "player", p);
				if (mGetVarByQV("spellTarget", "stunTime") == 0) {
					if (HasKeyword(CHARGE, 1*mGetVarByQV("spellTarget", "keywords"))) {
						mSetVarByQV("spellTarget", "action", ACTION_READY);
					} else {
						mSetVarByQV("spellTarget", "action", ACTION_SLEEPING);
					}
				}
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
				trVectorQuestVarSet("dir", trGetUnitVector("start", "end"));
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
						trVectorQuestVarSet("dir", trGetUnitVector("center", "pos"));
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
			case SPELL_DEVOUR:
			{
				trSoundPlayFN("wonderdeath.wav");
				trSoundPlayFN("cinematics\32_out\kronosbehinddorrlong.mp3","1",-1,"","");
				trSoundPlayFN("xpack\xcinematics\8_in\guardianawaken.mp3","1",-1,"","");

				trQuestVarSet("keeperGrabStep", 0);
				trQuestVarSet("keeperGrabTime", 0);
				trQuestVarSet("keeperGrabRadius", 0);
				trVectorQuestVarSet("keeperPos", kbGetBlockPosition(""+1*trQuestVarGet("spellTarget")));
				trQuestVarSet("keeperTartarianGate", deployAtTile(0, "Tartarian Gate", mGetVarByQV("spellTarget", "tile")));
				trUnitSelectClear();
				trUnitSelectByQV("keeperTartarianGate");
				trSetSelectedScale(0,0,0);
				trUnitOverrideAnimation(6, 0, true, false, -1);
				xsEnableRule("devour_animation");
				done = false;
			}
			case SPELL_SERPENT_SKIN:
			{
				trSoundPlayFN("icestereo.wav","1",-1,"","");
				trSoundPlayFN("serpentbirth1.wav","1",-1,"","");
				trSoundPlayFN("medusastone.wav","1",-1,"","");
				mSetVarByQV("spellTarget", "keywords", SetBit(mGetVarByQV("spellTarget", "keywords"), REGENERATE));
				stunUnit(1*trQuestVarGet("spellTarget"));
				// give it a lifespan
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Ball of Fire", mGetVarByQV("spellTarget", "tile")), true);
				trMutateSelected(kbGetProtoUnitID("Ice Block"));
				trSetSelectedScale(2,2,2);
			}
			case SPELL_DEMON_EAT:
			{
				trSoundPlayFN("tartarianspawnbirth1.wav","1",-1,"","");
				mSetVarByQV("spellCaster", "health", mGetVarByQV("spellCaster", "health") + mGetVarByQV("spellTarget", "health"));
				mSetVarByQV("spellCaster", "maxhealth", mGetVarByQV("spellCaster", "maxhealth") + mGetVarByQV("spellTarget", "health"));
				mSetVarByQV("spellCaster", "attack", mGetVarByQV("spellCaster", "attack") + mGetVarByQV("spellTarget", "attack"));
				mSetVarByQV("spellCaster", "scale", 1 + 0.25*mGetVarByQV("spellCaster", "health"));
				scaleUnit(1*trQuestVarGet("spellCaster"));
				mSetVarByQV("spellTarget", "health", 0);
				damageUnit(1*trQuestVarGet("spellTarget"),10);
			}
			case SPELL_SCORPION_STING:
			{
				trVectorSetUnitPos("casterPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTile");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(trGetUnitVector("casterPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(39, 0, false, true, -1);
				zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("spellTarget", "tile"), 0);
				teleportToTile(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("spellTile"));
				trSoundPlayFN("relicselect.wav","1",-1,"","");
				trSoundPlayFN("dialog\genr122f.mp3","1",-1,"","");
			}
			case SPELL_DUPLICATE_FRIEND:
			{
				trVectorSetUnitPos("casterPos", "spellCaster");
				trVectorSetUnitPos("targetPos", "spellTile");
				trUnitSelectClear();
				trUnitSelectByQV("spellCaster");
				trSetUnitOrientation(trGetUnitVector("casterPos", "targetPos"), xsVectorSet(0,1,0), true);
				trUnitOverrideAnimation(33, 0, false, true, -1);
				target = trQuestVarGet("spellTarget");
				activeUnit = summonAtTile(1*trQuestVarGet("spellTile"), p, mGetVarByQV("spellTarget", "proto"));
				mSetVar(activeUnit, "proto", mGetVar(target, "proto"));
				mSetVar(activeUnit, "spell", mGetVar(target, "spell"));
				mSetVar(activeUnit, "cost", mGetVar(target, "cost"));
				mSetVar(activeUnit, "attack", mGetVar(target, "attack"));
				mSetVar(activeUnit, "health", mGetVar(target, "health"));
				mSetVar(activeUnit, "maxhealth", mGetVar(target, "maxhealth"));
				mSetVar(activeUnit, "speed", mGetVar(target, "speed"));
				mSetVar(activeUnit, "range", mGetVar(target, "range"));
				mSetVar(activeUnit, "laserDirx", mGetVar(target, "laserDirx"));
				mSetVar(activeUnit, "laserDirz", mGetVar(target, "laserDirz"));
				mSetVar(activeUnit, "keywords", mGetVar(target, "keywords"));
				mSetVar(activeUnit, "onAttack", mGetVar(target, "onAttack"));
				mSetVar(activeUnit, "onDeath", mGetVar(target, "onDeath"));
				mSetVar(activeUnit, "scale", mGetVar(target, "scale"));
				scaleUnit(activeUnit);
				mSetString(activeUnit, "ability", mGetString(target, "ability"));
				if (HasKeyword(DECAY, mGetVar(activeUnit, "keywords")) == false) {
					mSetVar(activeUnit, "keywords", Keyword(DECAY) + mGetVar(activeUnit, "keywords"));
				}
				if (HasKeyword(CHARGE, mGetVar(activeUnit, "keywords"))) {
					mSetVar(activeUnit, "action", ACTION_READY);
				} else {
					mSetVar(activeUnit, "action", ACTION_SLEEPING);
				}
				trSoundPlayFN("sonofosirisbirth.wav","1",-1,"","");
				deployAtTile(p, "Kronny Birth SFX", 1*trQuestVarGet("spellTile"));
			}
			case SPELL_WORLD_SPLITTER:
			{
				trVectorSetUnitPos("laserstart", "spellTarget");
				trVectorSetUnitPos("laserend", "spellDirection");
				dir = trGetUnitVector("laserstart", "laserend");
				start = trVectorQuestVarGet("laserStart") + (dir * 6.0);
				tile = mGetVarByQV("spellTarget", "tile");
				
				while(done) {
					done = false;
					// Travel down the line and find stopping tile
					for(z=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
						neighbor = zGetVarByIndex("tiles", "neighbor"+z, tile);
						if (neighbor < trQuestVarGet("ztilesend")) {
							pos = kbGetBlockPosition(""+neighbor);
							if (distanceBetweenVectors(start, pos) < 1.0) {
								trQuestVarSet("occupant", zGetVarByIndex("tiles", "occupant", neighbor));
								if (trQuestVarGet("occupant") > 0) {
									yAddToDatabase("worldSplitterHit", "occupant");
								}
								tile = neighbor;
								start = pos + dir * 6.0;
								done = true;
								break;
							}
						}
					}
				}
				
				trVectorQuestVarSet("laserEnd", kbGetBlockPosition(""+tile));
				
				if (trQuestVarGet("p"+p+"phoenix") == 0) {
					trQuestVarSet("p"+p+"phoenix", trGetNextUnitScenarioNameNumber());
					trArmyDispatch(""+p+",0","Phoenix",1,1,0,1,0,true);
					trQuestVarSet("p"+p+"floater", trGetNextUnitScenarioNameNumber());
					trArmyDispatch(""+p+",0","Phoenix",1,1,0,1,0,true);

					trQuestVarSet("p"+p+"meteorite", trGetNextUnitScenarioNameNumber());
					trArmyDispatch(""+p+",0", "Dwarf", 1, 1, 0, 1, 0, true);
					trUnitSelectClear();
					trUnitSelectByQV("p"+p+"meteorite");
					spyEffect(1*trQuestVarGet("p"+p+"meteorite"), "Cinematic Block", "p"+p+"meteoriteDeployer");

					trQuestVarSet("p"+p+"worldSplitterLaser", trGetNextUnitScenarioNameNumber());
					trArmyDispatch(""+p+",0", "Dwarf", 1, 1, 0, 1, 0, true);
				}

				zSetProtoUnitStat("Meteorite", p, 1, 1);

				tile = mGetVarByQV("spellTarget", "tile");
				trUnitSelectClear();
				trUnitSelectByID(tile);
				trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
				trSetUnitOrientation(dir, vector(0,1,0), true);
				trUnitConvert(p);

				// garrison floater and meteorite
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"floater", true);
				trMutateSelected(kbGetProtoUnitID("Dwarf"));
				trImmediateUnitGarrison(""+tile);
				trUnitChangeProtoUnit("Phoenix");
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"meteorite", true);
				trMutateSelected(kbGetProtoUnitID("Dwarf"));
				trImmediateUnitGarrison(""+tile);
				trUnitChangeProtoUnit("Dwarf");

				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"meteorite");
				trSetSelectedScale(0,0,0);
				trSetUnitOrientation(dir, vector(0,1,0), true);

				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"floater");
				trMutateSelected(kbGetProtoUnitID("Hero Greek Achilles"));

				trUnitSelectClear();
				trUnitSelectByQV("spellTarget");
				trMutateSelected(kbGetProtoUnitID("Relic"));
				trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"floater"));
				trMutateSelected(mGetVarByQV("spellTarget", "proto"));

				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"phoenix");
				trMutateSelected(kbGetProtoUnitID("Phoenix"));
				trUnitOverrideAnimation(2, 0, true, false, -1);
				trMutateSelected(kbGetProtoUnitID("Relic"));
				trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"floater"));
				trMutateSelected(kbGetProtoUnitID("Phoenix"));

				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"worldSplitterLaser");
				trMutateSelected(kbGetProtoUnitID("Relic"));
				trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"floater"));
				trUnitChangeProtoUnit("Phoenix");
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"worldSplitterLaser");
				trMutateSelected(kbGetProtoUnitID("Petosuchus Projectile"));

				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"floater");
				trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
				trSetUnitOrientation(dir, vector(0,1,0), true);

				trQuestVarSet("p"+p+"worldSplitterActive", 1);

				trVectorQuestVarSet("p"+p+"worldSplitterDir", dir);
				trVectorQuestVarSet("p"+p+"worldSplitterPrev", kbGetBlockPosition(""+tile));

				trQuestVarSet("p"+p+"worldSplitterTimeout", trTimeMS() + 1000);

				trVectorQuestVarSet("laserStart", kbGetBlockPosition(""+1*trQuestVarGet("p"+p+"worldSplitterLaser")));
				
				trUnitSelectClear();
				trUnitSelectByID(tile);
				trUnitConvert(0);
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				xsEnableRule("spell_world_splitter_activate");
			}
			case SPELL_SOUL_SIPHON:
			{
				trSoundPlayFN("shadeofhadesdeath.wav","1",-1,"","");
				trQuestVarSet("p"+p+"drawCards", 2 + trQuestVarGet("p"+p+"drawCards"));
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
			case SPELL_DEATH_DOOR:
			{
				trSoundPlayFN("cinematics\32_out\kronosbehinddorrshort.mp3");
				done = false;
				xsEnableRule("death_door_animation");
				trQuestVarSet("deathDoorUnit1", trGetNextUnitScenarioNameNumber());
				trArmyDispatch("0,0","Dwarf",1,119,0,1,0,true);
				trQuestVarSet("deathDoorUnit2", trGetNextUnitScenarioNameNumber());
				trArmyDispatch("0,0","Dwarf",1,119,0,1,0,true);
				
				trQuestVarSet("deathDoorTime", trTimeMS() + 3000);
				trQuestVarSet("deathDoorNext", trTimeMS());
				trQuestVarSet("deathDoorAngle", 0);
				trQuestVarSet("deathDoorLast", trTimeMS());
				trVectorQuestVarSet("deathDoorPos", kbGetBlockPosition(""+1*trQuestVarGet("spellTarget")));
			}
			case SPELL_POISON_MIST:
			{
				trSoundPlayFN("argusfreezeattack.wav","1",-1,"","");
				trSoundPlayFN("lampadesblood.wav","1",-1,"","");
				deployAtTile(0, "Lampades Blood", 1*trQuestVarGet("spelltarget"));
				trVectorSetUnitPos("pos", "spellTarget");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "spell") == SPELL_NONE) {
						if (trDistanceToVectorSquared("allUnits", "pos") < 64) {
							if (HasKeyword(DECAY, mGetVarByQV("allUnits", "keywords")) == false) {
								mSetVarByQV("allUnits", "keywords", Keyword(DECAY) + mGetVarByQV("allUnits", "keywords"));
							}
						}
					}
				}
			}
			case SPELL_DOOM:
			{
				trSoundPlayFN("shadeofhadesacknowledge2.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), 2 + trQuestVarGet("p"+p+"spellDamage"));
				deployAtTile(0, "Curse SFX", 1*mGetVarByQV("spellTarget", "tile"));
				if (HasKeyword(DECAY, 1*mGetVarByQV("spellTarget", "keywords"))) {
					generateCard(p, 0, SPELL_DOOM);
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
				spyEffect(1*trQuestVarGet("spellTarget"), "Poison SFX");
				spyEffect(1*trQuestVarGet("spellTarget"), "Chaos effect");
			}
			case SPELL_CORPSE_PARTY:
			{
				// If two of the tiles are the same, restart
				if ((trQuestVarGet("spellTarget1") - trQuestVarGet("spellTarget2")) * (trQuestVarGet("spellTarget2") - trQuestVarGet("spellTarget3")) * (trQuestVarGet("spellTarget1") - trQuestVarGet("spellTarget3")) == 0) {
					if (trCurrentPlayer() == p) {
						trSoundPlayFN("cantdothat.wav","1",-1,"","");
					}
					if ((Multiplayer == false) && (p == 2)) {
						trQuestVarSet("selectedCard", -1);
					} else {
						done = false;
						chooseSpell(SPELL_CORPSE_PARTY, 1*trQuestVarGet("selectedCard"));
					}
				} else {
					trSoundPlayFN("ancestorsbirth.wav","1",-1,"","");
					for(x=3; >0) {
						mSetVar(summonAtTile(1*trQuestVarGet("spellTarget"+x), p, kbGetProtoUnitID("Minion")), "action", ACTION_READY);
					}
				}
			}
			case SPELL_CALL_OF_THE_DEEP:
			{
				trQuestVarSet("highestCost", 0);
				trQuestVarSet("currentCost", 0);
				trQuestVarSet("highestPointer", -1);
				for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
					target = yDatabaseNext("p"+p+"deck");
					if (yGetVar("p"+p+"deck", "spell") == 0) {
						trQuestVarCopy("currentCost", "card_"+target+"_cost");
						if ((trQuestVarGet("currentCost") >= trQuestVarGet("highestCost")) && (trQuestVarGet("currentCost") <= trQuestVarGet("p"+p+"manaflow"))) {
							trQuestVarSet("highestPointer", yGetPointer("p"+p+"deck"));
							trQuestVarCopy("highestCost", "currentCost");
						}
					}
				}
				if (trQuestVarGet("highestPointer") >= 0) {
					trSoundPlayFN("leviathanselect3.wav","1",-1,"","");
					trSoundPlayFN("shipdeathsplash.wav","1",-1,"","");
					ySetPointer("p"+p+"deck", 1*trQuestVarGet("highestPointer"));
					target = yGetUnitAtIndex("p"+p+"deck", 1*trQuestVarGet("highestPointer"));
					summonAtTile(1*trQuestVarGet("spellTarget"), p, target);
					yRemoveFromDatabase("p"+p+"deck");
					deployAtTile(0, "Meteor Impact Water", 1*trQuestVarGet("spellTarget"));
				} else {
					trSoundPlayFN("jormundelverselect2.wav", "1", -1, "", "");
					summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Jormund Elver"));
				}
			}
			case SPELL_RUNE_OF_DARKNESS:
			{
				if (trQuestVarGet("spellTarget1") == trQuestVarGet("spellTarget2")) {
					if (trCurrentPlayer() == p) {
						trSoundPlayFN("cantdothat.wav","1",-1,"","");
					}
					if ((Multiplayer == false) && (p == 2)) {
						trQuestVarSet("selectedCard", -1);
					} else {
						done = false;
						chooseSpell(SPELL_RUNE_OF_DARKNESS, 1*trQuestVarGet("selectedCard"));
					}
				} else {
					trSoundPlayFN("mythcreate.wav","1",-1,"","");
					mSetVarByQV("spellTarget", "health", 0);
					damageUnit(1*trQuestVarGet("spellTarget"), 100);
					activeUnit = summonAtTile(1*trQuestVarGet("spellTarget1"), p, kbGetProtoUnitID("Shade of Hades"));
					mSetVar(activeUnit, "action", ACTION_SLEEPING);
					activeUnit = summonAtTile(1*trQuestVarGet("spellTarget2"), p, kbGetProtoUnitID("Shade of Hades"));
					mSetVar(activeUnit, "action", ACTION_SLEEPING);
				}
			}
			case SPELL_ZENOS_PARADOX:
			{
				trSoundPlayFN("spybirth.wav","1",-1,"","");
				trSoundPlayFN("timeshift.wav","1",-1,"","");
				trQuestVarSet("tile1", mGetVarByQV("spellTarget1", "tile"));
				trQuestVarSet("tile2", mGetVarByQV("spellTarget2", "tile"));
				deployAtTile(0, "Curse SFX", 1*trQuestVarGet("tile1"));
				deployAtTile(0, "Curse SFX", 1*trQuestVarGet("tile2"));
				teleportToTile(1*trQuestVarGet("spellTarget2"), 1*trQuestVarGet("tile1"));
				teleportToTile(1*trQuestVarGet("spellTarget1"), 1*trQuestVarGet("tile2"));
			}
			case SPELL_SCRAP_METAL:
			{
				trSoundPlayFN("tributereceived.wav","1",-1,"","");
				trQuestVarSet("p"+p+"mana", 1 + trQuestVarGet("p"+p+"mana"));
			}
			case SPELL_MAGNETIZE:
			{
				trSoundPlayFN("armory.wav","1",-1,"","");
				magnetize(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("spellCaster"));
				for(x=yGetDatabaseCount("allUnits"); >0) {
					if (yDatabaseNext("allUnits") == trQuestVarGet("spellCaster")) {
						yRemoveFromDatabase("allUnits");
						break;
					}
				}
			}
			case SPELL_ELECTRIC_GRID:
			{
				trSoundPlayFN("tower.wav","1",-1,"","");
				xsEnableRule("spell_electric_grid_activate");
			}
			case SPELL_ZAP_GUN:
			{
				trSoundPlayFN("sonofosirisbolt.wav","1",-1,"","");
				deployAtTile(0, "Hero Birth", 1*mGetVarByQV("spellTarget", "tile"));
				mSetVarByQV("spellTarget", "keywords", SetBit(1*mGetVarByQV("spellTarget", "keywords"), LIGHTNING));
			}
			case SPELL_COMPRESS:
			{
				trSoundPlayFN("changeunit.wav","1",-1,"","");
				deployAtTile(0, "Osiris Box Glow", 1*mGetVarByQV("spellTarget", "tile"));
				p = mGetVarByQV("spellTarget", "player");
				trVectorSetUnitPos("pos", "spellTarget");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (trQuestVarGet("allUnits") == trQuestVarGet("spellTarget")) {
						continue;
					} else if ((mGetVarByQV("allUnits", "player") == p) && (mGetVarByQV("allUnits", "spell") == SPELL_NONE)) {
						if (trDistanceToVectorSquared("allUnits", "pos") < 40) {
							magnetize(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("allUnits"));
							yRemoveFromDatabase("allUnits");
						}
					}
				}
			}
			case SPELL_UPGRADE:
			{
				trSoundPlayFN("armory.wav","1",-1,"","");
				deployAtTile(0, "Hero Birth", 1*mGetVarByQV("spellTarget", "tile"));
				mSetVarByQV("spellTarget", "keywords", SetBit(1*mGetVarByQV("spellTarget", "keywords"), MAGNETIC));
				mSetVarByQV("spellTarget", "health", 2 + mGetVarByQV("spellTarget", "health"));
				mSetVarByQV("spellTarget", "maxhealth", 2 + mGetVarByQV("spellTarget", "maxhealth"));
				mSetVarByQV("spellTarget", "attack", 2 + mGetVarByQV("spellTarget", "attack"));
			}
			case SPELL_PROFITEERING:
			{
				trSoundPlayFN("plentybirth.wav","1",-1,"","");
				trSoundPlayFN("miningcamp.wav","1",-1,"");
				summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Mining Camp"));
			}
			case SPELL_WARNING_SHOT:
			{
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Meteorite", 1*mGetVarByQV("spellTarget", "tile")));
				trDamageUnitPercent(100);
				trSoundPlayFN("implode start.wav","1",-1,"","");
				trSoundPlayFN("titanfall.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), 1 + trQuestVarGet("p"+p+"spellDamage"));
				trQuestVarSet("p"+p+"drawCards", 1 + trQuestVarGet("p"+p+"drawCards"));
			}
			case SPELL_NANOMACHINES:
			{
				trSoundPlayFN("petsuchosattack.wav","1",-1,"","");
				deployAtTile(0, "Hero Birth", 1*mGetVarByQV("spellTarget", "tile"));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellTarget"));
				spyEffect(1*trQuestVarGet("spellTarget"), "Valkyrie", "unused", vector(0,0,0), 15, "1,0,0,0,0,0,0");
				spyEffect(1*trQuestVarGet("spellTarget"), "Well of Urd", "unused", vector(0,1,0));
				mSetVarByQV("spellTarget", "keywords", SetBit(SetBit(1*mGetVarByQV("spellTarget", "keywords"), WARD), DODGE));
			}
			case SPELL_REWIND:
			{
				trSoundPlayFN("suckup3.wav","1",-1,"","");
				returnToHand(1*trQuestVarGet("spellTarget"));
			}
			case SPELL_TIME_POCKET:
			{
				trSoundPlayFN("timeshift.wav","1",-1,"","");
				tile = trQuestVarGet("spellTarget");
				deployAtTile(0, "Tremor", tile);
				for(x=0; < zGetVarByIndex("tiles", "neighborCount", 1*trQuestVarGet("spellTarget"))) {
					neighbor = zGetVarByIndex("tiles", "neighbor"+x, tile);
					deployAtTile(0, "Osiris SFX", neighbor);
					target = zGetVarByIndex("tiles", "occupant", neighbor);
					if (target > 0) {
						stunUnit(target);
					}
				}
				target = zGetVarByIndex("tiles", "occupant", tile);
				if ((target > 0) && (mGetVar(target, "spell") == SPELL_NONE)) {
					stunUnit(target);
				}
			}
			case SPELL_BANHAMMER:
			{
				done = false;
				trSoundPlayFN("attackwarning.wav","1",-1,"","");
				deployAtTile(0, "Hero Birth", 1*mGetVarByQV("spellTarget", "tile"));
				trVectorSetUnitPos("pos", "spellTarget");
				for(x=25; >=0) {
					trQuestVarSet("next", deployAtTile(1, "Dwarf", 1*mGetVarByQV("spellTarget", "tile")));
					trQuestVarSet("posY", 50.0 - 0.08*xsPow(x - 25, 2));
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("next"), true);
					trSetUnitOrientation(xsVectorSet(1,0,0), xsVectorSet(0,-1,0), true);
					trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
					trUnitTeleport(trVectorQuestVarGetX("pos"), trQuestVarGet("posy"), trVectorQuestVarGetZ("pos"));
					trQuestVarSet("hammerPos"+x, trQuestVarGet("next"));
				}
				trQuestVarSet("hammerNext", trTimeMS() + 1000);
				trQuestVarSet("hammerStep", 0);
				trQuestVarSet("hammerPosPrev", trQuestVarGet("hammerPos25"));
				trQuestVarSet("banhammer", trGetNextUnitScenarioNameNumber());
				trArmyDispatch("1,10", "Dwarf",1, 119,0,1,0,true);
				trArmySelect("1,10");
				trMutateSelected(kbGetProtoUnitID("Thor hammer"));
				trUnitSetAnimationPath("0,0,0,0,0,0,0");
				xsEnableRule("spell_banhammer_activate");
			}
			case SPELL_POWER_SUIT:
			{
				trSoundPlayFN("ageadvance.wav","1",-1,"","");
				trSoundPlayFN("herobirth2.wav","1",-1,"","");
				deployAtTile(0, "Traitors effect", 1*mGetVarByQV("p"+p+"commander", "tile"));
				mSetVarByQV("p"+p+"commander", "keywords", SetBit(1*mGetVarByQV("p"+p+"commander", "keywords"), MAGNETIC));
			}
			case SPELL_GEAR_FACTORY:
			{
				trSoundPlayFN("armory.wav","1",-1,"","");
				trSoundPlayFN("siegecamp.wav","1",-1,"");
				summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Guild"));
			}
			case SPELL_ASSEMBLY_LINE:
			{
				trSoundPlayFN("siegecamp.wav","1",-1,"","");
				for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("p"+p+"hand", "proto")), 1*mGetVarByQV("p"+p+"hand","spell"), true);
				}
				trQuestVarSet("p"+p+"drawCards", 1 + trQuestVarGet("p"+p+"drawCards"));
			}
			case SPELL_BULLET_TIME:
			{
				trSoundPlayFN("storehouse.wav","1",-1,"","");
				trSoundPlayFN("vortexstart.wav","1",-1,"","");
				trQuestVarSet("p"+p+"borrowedTime", 1 + trQuestVarGet("p"+p+"borrowedTime"));
			}
			case SPELL_FORTIFY:
			{
				trSoundPlayFN("wall.wav","1",-1,"","");
				xsEnableRule("spell_fortify_activate");
			}
			case SPELL_CHOOSE_DIRECTION:
			{
				trVectorSetUnitPos("start", "spellCaster");
				trVectorSetUnitPos("end", "spellDirection");
				trVectorQuestVarSet("dir", trGetUnitVector("start", "end"));
				mSetVarByQV("spellCaster", "laserDirx", trVectorQuestVarGetX("dir") * 100000);
				mSetVarByQV("spellCaster", "laserDirz", trVectorQuestVarGetZ("dir") * 100000);
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("spellCaster"));
				trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
				trUnitHighlight(0.5, false);
				trSoundPlayFN("storehouse.wav","1",-1,"","");
			}
			case SPELL_DOMINANCE:
			{
				trSoundPlayFN("tartariangateselect.wav","1",-1,"","");
				mSetVarByQV("p"+p+"commander", "attack", 1 + mGetVarByQV("p"+p+"commander", "attack"));
				startAttack(1*trQuestVarGet("p"+p+"commander"), 1*trQuestVarGet("spellTarget"));
				done = false;
				xsEnableRule("spell_attack_complete");
			}
			case SPELL_SPIDER_LAIR:
			{
				trSoundPlayFN("spiderscast.wav","1",-1,"","");
				for (x=3; >0) {
					target = yGetDatabaseCount("p"+p+"hand");
					generateCard(p, kbGetProtoUnitID("Spider Egg"), 0, false);
					if (target < 10) {
						mSetVarByQV("next", "cost", 0);
						mSetVarByQV("next", "keywords", Keyword(DECAY) + Keyword(AIRDROP));
					}
				}
			}
			case SPELL_TAVERN_BRAWL:
			{
				trSoundPlayFN("specialist.wav","1",-1,"","");
				trSoundPlayFN("chaos.wav","1",-1,"","");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					activeUnit = yDatabaseNext("allUnits");
					trQuestVarSet("pointer", yGetPointer("allUnits"));
					trQuestVarSetFromRand("temp", 1, yGetDatabaseCount("allUnits") - 1, true);
					for(y=trQuestVarGet("temp"); > 1) {
						yDatabaseNext("allUnits");
					}
					target = yDatabaseNext("allUnits");
					startAttack(activeUnit, target, HasKeyword(AMBUSH, 1*mGetVar(activeUnit, "keywords")), true);
					ySetPointer("allUnits", trQuestVarGet("pointer"));
				}
				done = false;
				xsEnableRule("spell_attack_complete");
			}
			case SPELL_NICKS_PORTAL:
			{
				trSoundPlayFN("vortexstart.wav","1",-1,"","");
				if (trQuestVarGet("p"+p+"commanderType") == COMMANDER_NICK) {
					trQuestVarSet("nickTiles", trQuestVarGet("spellTarget"));
				} else {
					yClearDatabase("nickTiles");
					for (z=zGetBankCount("tiles"); >0) {
						zBankNext("tiles");
						if (zGetVar("tiles", "terrain") == 0 && zGetVar("tiles", "occupant") == 0) {
							if (zGetVar("tiles", "ward") == 0) {
								yAddToDatabase("nickTiles", "tiles");
							}
						}
					}
					trQuestVarSetFromRand("nickRandom", 1, yGetDatabaseCount("nickTiles"), true);
					for(x=trQuestVarGet("nickRandom"); >0) {
						yDatabaseNext("nickTiles");
					}
				}
				
				deployAtTile(0, "Olympus Temple SFX", 1*trQuestVarGet("nickTiles"));
				bool go = true;
				while(go){
					trQuestVarSetFromRand("nickClass", 0, 4, true);
					trQuestVarSetFromRand("nickCard", 7, 29, true);
					ChatLog(0,""+1*trQuestVarGet("nickCard")+" card class "+1*trQuestVarGet("nickClass"));
					trQuestVarSet("nickProto", CardToProto(1*(trQuestVarGet("nickCard") + 30 * trQuestVarGet("nickClass"))));
					if(trQuestVarGet("nickProto") != kbGetProtoUnitID("Statue of Lightning")){
						go = false;
					}
				}
				target = summonAtTile(1*trQuestVarGet("nickTiles"),p,1*trQuestVarGet("nickProto"));
				if(HasKeyword(CHARGE, 1*mGetVar(target, "keywords")) == false){
					mSetVar(target, "action", ACTION_SLEEPING);
				}
			}
			case SPELL_PETTY_LASER:
			{
				for (x = 2 + trQuestVarGet("p"+p+"spellDamage"); >0) {
					trSoundPlayFN("cranegrunt1.wav","1",-1,"","");
				}
				trSoundPlayFN("cranegrunt1.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), 2 + trQuestVarGet("p"+p+"spellDamage"));
				addCardToDeck(p, "", SPELL_THICK_LASER, true);
				shuffleDeck(p);
				deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_THICK_LASER:
			{
				for (x = 4 + trQuestVarGet("p"+p+"spellDamage"); >0) {
					trSoundPlayFN("cranegrunt1.wav","1",-1,"","");
				}
				damageUnit(1*trQuestVarGet("spellTarget"), 4 + trQuestVarGet("p"+p+"spellDamage"));
				addCardToDeck(p, "", SPELL_GRAND_LASER, true);
				shuffleDeck(p);
				deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_GRAND_LASER:
			{
				for (x = 6 + trQuestVarGet("p"+p+"spellDamage"); >0) {
					trSoundPlayFN("cranegrunt1.wav","1",-1,"","");
				}
				damageUnit(1*trQuestVarGet("spellTarget"), 6 + trQuestVarGet("p"+p+"spellDamage"));
				addCardToDeck(p, "", SPELL_OMEGA_LASER, true);
				shuffleDeck(p);
				deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_OMEGA_LASER:
			{
				for (x = 8 + trQuestVarGet("p"+p+"spellDamage"); >0) {
					trSoundPlayFN("cranegrunt1.wav","1",-1,"","");
				}
				damageUnit(1*trQuestVarGet("spellTarget"), 8 + trQuestVarGet("p"+p+"spellDamage"));
				addCardToDeck(p, "", SPELL_GODLY_LASER, true);
				shuffleDeck(p);
				deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_GODLY_LASER:
			{
				for (x = 10 + trQuestVarGet("p"+p+"spellDamage"); >0) {
					trSoundPlayFN("cranegrunt1.wav","1",-1,"","");
				}
				damageUnit(1*trQuestVarGet("spellTarget"), 10 + trQuestVarGet("p"+p+"spellDamage"));
				deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_SPACE_VENT:
			{
				trSoundPlayFN("pigout.wav","1",-1,"","");
				trSoundPlayFN("pigout.wav","1",-1,"","");
				trSoundPlayFN("pigout.wav","1",-1,"","");
				
				//for(ventPlayer=2; >0) {
				int ventPlayer = p;
				string disText = "";
				int disCount = 0;
				for(x=yGetDatabaseCount("p"+ventPlayer+"hand"); >0) {
					disCount = disCount + 1;
					yDatabaseNext("p"+ventPlayer+"hand", true);
					trSoundPlayFN("pigout.wav","1",-1,"","");
					trVectorSetUnitPos("pos", "p"+ventPlayer+"hand");
					trUnitSelectClear();
					trUnitSelectByID(1*yGetVar("p"+ventPlayer+"hand", "pos"));
					trMutateSelected(kbGetProtoUnitID("Victory Marker"));
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("p"+ventPlayer+"hand"), true);
					trMutateSelected(kbGetProtoUnitID("Victory Marker"));
					trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("pos"),0,trVectorQuestVarGetZ("pos"),0, true);
					trUnitSelectClear();
					trArmySelect("1,10");
					trUnitChangeProtoUnit("Hero Death");
					if (mGetVarByQV("p"+ventPlayer+"hand", "spell") == SPELL_NONE) {
						yClearDatabase("ventTiles");
						findAvailableTiles(1*mGetVarByQV("p"+ventPlayer+"commander", "tile"), 1, "ventTiles", false);
						if(yGetDatabaseCount("ventTiles") > 0){
							int ventUnit = summonAtTile(1*yDatabaseNext("ventTiles"),ventPlayer,1*mGetVarByQV("p"+ventPlayer+"hand", "proto"));			
							if(HasKeyword(CHARGE, 1*mGetVar(ventUnit, "keywords")) == true){
								mSetVar(ventUnit, "action", ACTION_READY);
							} else {
								mSetVar(ventUnit, "action", ACTION_SLEEPING);				
							}				
						} else {
							if(disCount < 4){
								disText = disText + trStringQuestVarGet("card_" + 1*mGetVarByQV("p"+ventPlayer+"hand", "proto") + "_name") + " ";
							} else {
								disText = "" + disCount + " cards";
							}
						}
					} else {
						if(disCount < 4){
							disText = disText + trStringQuestVarGet("spell_" + 1*mGetVarByQV("p"+ventPlayer+"hand", "spell") + "_name") + " ";
						} else {
							disText = "" + disCount + " cards";
						}
					}
					zSetVarByIndex("p"+ventPlayer+"handPos", "occupied", 1*yGetVar("p"+ventPlayer+"hand", "pos"), 0);
					yRemoveFromDatabase("p"+ventPlayer+"hand");
				}
				ChatLog(ventPlayer, "Discarded " + disText);
				ChatLog((3-ventPlayer), "Opponent discarded " + disText);
				//}

			}
			case SPELL_REFRESH_MANA:
			{
				/*
				int refreshCount = xsMax(0, trQuestVarGet("maxMana") - trQuestVarGet("p"+p+"mana"));
				if(refreshCount > 5){
					refreshCount = 5;
				}
				for(x=refreshCount; >0) {
					if (yGetDatabaseCount("p"+p+"deck") > 0) {
						int refreshProto = yDatabaseNext("p"+p+"deck");
						if(refreshCount == 1){
							if (yGetVar("p"+p+"deck", "spell") == 0) {
								ChatLog(p, "Discarded " + trStringQuestVarGet("card_" + refreshProto + "_Name") + " from your deck.");
							} else {
								ChatLog(p, "Discarded " + trStringQuestVarGet("spell_" + 1*yGetVar("p"+p+"deck", "spell") + "_Name") + " from your deck.");
							}
						}
						yRemoveFromDatabase("p"+p+"deck");
					}
				}
				if(refreshCount > 1){
					ChatLog(p, "Discarded " + refreshCount + " cards from your deck.");
				}
				*/
				trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") + trQuestVarGet("p"+p+"manaflow"));
				trQuestVarSet("p"+p+"manaflow", 0);
				updateHandPlayable(p);
				updateMana();	
				trSoundPlayFN("skypassagein.wav", "1", -1, "","");
				deployAtTile(0, "Osiris Box Glow", 1*mGetVarByQV("p" + p + "commander", "tile"));
			}
			case SPELL_ARIES:
			{
				trSoundPlayFN("cinematics\14_in\chimes.mp3");
				trSoundPlayFN("tartarianopen2.wav","1",-1,"","");
				trSoundPlayFN("petsuchosattack.wav","1",-1,"","");
				damageUnit(1*trQuestVarGet("spellTarget"), yGetDatabaseCount("p"+p+"hand") + trQuestVarGet("p"+p+"spellDamage"));
				deployAtTile(0, "Arkantos God Out", 1*mGetVarByQV("spellTarget", "tile"));
				deployAtTile(0, "Meteor Impact Ground", 1*mGetVarByQV("spellTarget", "tile"));
			}
			case SPELL_AQUARIUS:
			{
				trSoundPlayFN("cinematics\14_in\chimes.mp3");
				trSoundPlayFN("healingspringbirth.wav","1",-1,"","");
				trSoundPlayFN("heal.wav","1",-1,"","");
				healUnit(1*trQuestVarGet("p"+p+"commander"), yGetDatabaseCount("p"+p+"hand"));
				deployAtTile(0, "Arkantos Boost SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
			}
			case SPELL_LIBRA:
			{
				trSoundPlayFN("cinematics\14_in\chimes.mp3");
				trQuestVarSet("p"+p+"drawCards", xsMax(0, 1 + yGetDatabaseCount("p"+(3-p)+"hand") - yGetDatabaseCount("p"+p+"hand")));
				trSoundPlayFN("temple.wav","1",-1,"","");
				trSoundPlayFN("sentinelbirth.wav","1",-1,"","");
			}
			case SPELL_PISCES:
			{
				trSoundPlayFN("cinematics\14_in\chimes.mp3");
				for(i=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					mSetVarByQV("p"+p+"hand", "attack", 1 + mGetVarByQV("p"+p+"hand", "attack"));
					mSetVarByQV("p"+p+"hand", "health", 1 + mGetVarByQV("p"+p+"hand", "health"));
					mSetVarByQV("p"+p+"hand", "maxhealth", 1 + mGetVarByQV("p"+p+"hand", "maxhealth"));
				}
			}
			case SPELL_THE_CALLING:
			{
				done = false;
				xsEnableRule("the_calling");
				trQuestVarSet("theCallingStep", 1);
				trQuestVarSet("theCallingRadius", 80);
				trQuestVarSet("theCallingNext", trTimeMS());
				trVectorQuestVarSet("theCallingPos", kbGetBlockPosition(""+1*trQuestVarGet("spellTarget")));
				trCameraShake(5.0, 0.3);
				trSoundPlayFN("cinematics\32_out\kronosbehinddorrlong.mp3","1",-1,"","");
				trSoundPlayFN("cinematics\17_in\weirdthing.mp3","1",-1,"","");
				trSoundPlayFN("cinematics\17_in\arrive.mp3","1",-1,"","");
			}
			case SPELL_DUPLICATE_ME:
			{
				trSoundPlayFN("mythcreate.wav","1",-1,"","");
				activeUnit = summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Promethean Small"));
				mSetVar(activeUnit, "action", ACTION_SLEEPING);
				mSetVar(activeUnit, "health", mGetVarByQV("spellCaster", "health"));
				mSetVar(activeUnit, "maxhealth", mGetVarByQV("spellCaster", "maxhealth"));
				mSetVar(activeUnit, "attack", mGetVarByQV("spellCaster", "attack"));
				mSetVar(activeUnit, "keywords", mGetVarByQV("spellCaster", "keywords"));
			}
			case SPELL_COPY_ATTACK_EFFECT:
			{
				trSoundPlayFN("changeunit.wav","1",-1,"","");
				mSetVarByQV("spellCaster", "OnAttack", mGetVarByQV("spellTarget", "OnAttack"));
				if (mGetVarByQV("spellCaster", "OnAttack") > 0) {
					mSetStringByQV("spellCaster", "ability", mGetStringByQV("spellTarget", "ability"));
				}
			}
			case SPELL_HORROR_MENAGERIE:
			{
				trSoundPlayFN("ageadvance.wav");
				trSoundPlayFN("vortexstart.wav");
				trSoundPlayFN("timeshift.wav");
				deployAtTile(0, "Osiris Box Glow", mGetVarByQV("p"+p+"commander", "tile"));
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Ball of Fire", mGetVarByQV("p"+p+"commander", "tile")), true);
				trMutateSelected(kbGetProtoUnitID("Implode Sphere Effect"));
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Dwarf", mGetVarByQV("p"+p+"commander", "tile")), true);
				trDamageUnitPercent(100);
				trMutateSelected(kbGetProtoUnitID("Pyramid Osiris Xpack"));
				trSetSelectedScale(100, 0, 0);
				for(i=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					if (mGetVarByQV("p"+p+"hand", "spell") > 0) {
						mSetVarByQV("p"+p+"hand", "cost", 0);
					}
				}
			}
			case SPELL_BULLET_STORM:
			{
				done = false;
				trSoundPlayFN("manticorespecialattack.wav", "1", -1, "", "");
				xsEnableRule("bullet_storm_active");
				findTargets(1*trQuestVarGet("p"+p+"commander"), "bulletStormTargets");
				trQuestVarSet("bulletStormSphinx", deployAtTile(0, "Dwarf", mGetVarByQV("p"+p+"commander", "tile")));
				trUnitSelectClear();
				trUnitSelectByQV("bulletStormSphinx");
				trMutateSelected(kbGetProtoUnitID("Sphinx"));
				trUnitOverrideAnimation(39, 0, true, false, -1);
				trSetSelectedScale(0,0,0);
				trQuestVarSet("bulletStormSmoke", deployAtTile(0, "Heka Shockwave SFX", mGetVarByQV("p"+p+"commander", "tile")));
				trVectorQuestVarSet("bulletStormDir", vector(1,0,0));
				trQuestVarSet("bulletStormNext", trTimeMS());
				trQuestVarSet("bulletStormHit", 20);
				trQuestVarSet("bulletStormTremor", 0);
			}
			case SPELL_RIDE_THE_LIGHTNING:
			{
				trSoundPlayFN("lightningbirth.wav");
				trQuestVarSet("rideTheLightningBonus", 1 + trQuestVarGet("rideTheLightningBonus"));
				mSetVarByQV("p"+p+"commander", "speed", mGetVarByQV("p"+p+"commander", "speed") + 1);
				mSetVarByQV("p"+p+"commander", "keywords", SetBit(mGetVarByQV("p"+p+"commander", "keywords"), ETHEREAL));
				trQuestVarSet("rideTheLightningPlayer", p);
				xsEnableRule("ride_the_lightning_bonus");
			}
			case SPELL_RECHARGE:
			{
				trSoundPlayFN("suckup2.wav");
				trUnitSelectClear();
				trUnitSelect(""+deployAtTile(0, "Deconstruct Unit", mGetVarByQV("p"+p+"commander", "tile")), true);
				trUnitOverrideAnimation(18, 0, false, true, -1);
				trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") + mGetVarByQV("p"+p+"commander", "attack"));
				trQuestVarSet("p"+p+"drawCards", 2 + trQuestVarGet("p"+p+"drawCards"));
			}
			case SPELL_BLITZ:
			{
				stunUnit(1*trQuestVarGet("spellTarget"));
				start = kbGetBlockPosition(""+1*trQuestVarGet("p"+p+"commander"));
				end = kbGetBlockPosition(""+1*trQuestVarGet("spellTile"));
				dist = distanceBetweenVectors(start, end, false);
				step = getUnitVector(start, end, 2.0);
				for(i = dist / 2; >0) {
					start = start + step;
					trArmyDispatch("0,0", "Dwarf", 1, 61, 0, 61, 0, true);
					trArmySelect("0,0");
					trUnitTeleport(xsVectorGetX(start), 0, xsVectorGetZ(start));
					trUnitChangeProtoUnit("Lightning sparks");
				}
				trQuestVarSetFromRand("rand", 1, 5, true);
				trSoundPlayFN("ui\lightning"+1*trQuestVarGet("rand")+".wav");
				zSetVarByIndex("tiles", "occupant", mGetVarByQV("p"+p+"commander", "tile"), 0);
				teleportToTile(1*trQuestVarGet("p"+p+"commander"), 1*trQuestVarGet("spellTile"));
			}
			case SPELL_MOONBEAM:
			{
				trUnitSelect(""+deployAtTile(0, "Osiris Birth", mGetVarByQV("spellTarget", "tile")));
				trSetSelectedScale(0,0,0);
				trSoundPlayFN("eclipsebirth.wav");
				mSetVarByQV("spellTarget", "keywords", 0);
			}
			case SPELL_CRESCENT_STRIKE:
			{
				trQuestVarSet("p"+p+"crescentStrike", 1);
				trSoundPlayFN("olympustemplesfx.wav");
				if (trQuestVarGet("p"+p+"crescentSpy") == 0) {
					trUnitSelectClear();
					trUnitSelectByQV("p"+p+"commander");
					spyEffect(1*trQuestVarGet("p"+p+"commander"), "Outpost", "p"+p+"crescentSpy");
				} else {
					trUnitSelectClear();
					trUnitSelectByQV("p"+p+"crescentSpy", true);
					trMutateSelected(kbGetProtoUnitID("Outpost"));
				}
				mSetVarByQV("p"+p+"commander", "OnAttack", SetBit(mGetVarByQV("p"+p+"commander", "OnAttack"), ATTACK_STUN_TARGET));
			}
			case SPELL_PROTECTION:
			{
				trQuestVarSet("p"+p+"protection", 1);
				trSoundPlayFN("bronzebirth.wav");
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (mGetVarByQV("allUnits", "player") == p) {
						mSetVarByQV("allUnits", "keywords", SetBit(mGetVarByQV("allUnits", "keywords"), IMMUNE));
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
			trDelayedRuleActivation("spell_cast_end");
		} else {
			trQuestVarSet("gameplayPhase", GAMEPLAY_ATTACKING);
		}
	}
}

// delayed end so that other stuff can detect spell casts
rule spell_cast_end
inactive
highFrequency
{
	xsDisableSelf();
	castEnd();
	uiClearSelection();
}

rule spell_party_up_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		int proto = 0;
		int target = 3;
		for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
			proto = yDatabaseNext("p"+p+"deck");
			if (yGetVar("p"+p+"deck", "spell") > 0) {
				proto = yGetVar("p"+p+"deck", "spell");
				if (trQuestVarGet("spell_"+proto+"_cost") == 1) {
					yDatabaseNext("p"+p+"deck", false, true);
					drawCard(p);
					target = target - 1;
					if (target == 0) {
						break;
					}
				}
			} else if (trQuestVarGet("card_"+proto+"_cost") == 1) {
				yDatabaseNext("p"+p+"deck", false, true);
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
			if (yGetDatabaseCount("p"+p+"hand") < trQuestVarGet("p"+p+"maxHandSize")) {
				trQuestVarSetFromRand("chooseClass", 1, 2, true);
				trQuestVarSetFromRand("chooseCard", 0, 29, true);
				card = 30*trQuestVarGet("p"+(3-p)+"class"+1*trQuestVarGet("chooseClass")) + trQuestVarGet("chooseCard");
				generateCard(p, CardToProto(card), CardToSpell(card));
			}
		}
		xsDisableRule("spell_copy_homework_activate");
	}
}

rule spell_apocalypse_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		for(x=yGetDatabaseCount("p"+p+"hand"); < trQuestVarGet("p"+p+"maxHandSize")) {
			mSetVar(generateCard(p, 0, SPELL_METEOR, true), "cost", 0);
		}
		updateHandPlayable(p);
		xsDisableRule("spell_apocalypse_activate");
	}
}

rule spell_fortify_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		for(x=yGetDatabaseCount("p"+p+"hand"); < trQuestVarGet("p"+p+"maxHandSize")) {
			generateCard(p, kbGetProtoUnitID("Wall Connector"));
		}
		updateHandPlayable(p);
		xsDisableRule("spell_fortify_activate");
	}
}

rule spell_mirror_image_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		int proto = mGetVarByQV("spellTarget", "proto");
		generateCard(p, proto);
		if (trQuestVarGet("p"+p+"commanderType") == COMMANDER_NOTTUD) {
			generateCard(p, proto);
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
		for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
			yDatabaseNext("p"+p+"deck");
			if (yGetVar("p"+p+"deck", "spell") > 0) {
				yDatabaseNext("p"+p+"deck", false, true);
				drawCard(p);
				break;
			}
		}
		for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
			yDatabaseNext("p"+p+"deck");
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				yDatabaseNext("p"+p+"deck", false, true);
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
	if (((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + yGetDatabaseCount("pushes") == 0) && (trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) ||
		(trTime() > cActivationTime + 3)) {
		castEnd();
		xsDisableRule("spell_attack_complete");
	}
}

rule spell_snipe_complete
highFrequency
inactive
{
	if (((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") == 0) && (trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) ||
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
				if (trDistanceToVectorSquared("allUnits", "pos") < 64) {
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
	if (trDistanceBetweenVectorsSquared("spellProjectileStart", "spellProjectileEnd") < 8) {
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
				mSetVarByQV("spellTarget", "health", 0);
				damageUnit(1*trQuestVarGet("spellTarget"), 6900);
			}
			case SPELL_MIRROR_REFLECTION:
			{
				trSoundPlayFN("restorationbirth.wav","1",-1,"","");
				
				zBankNext("tiles");
				trQuestVarSet("temp", trQuestVarGet("tiles"));
				for (x=zGetBankCount("tiles"); >0) {
					zBankNext("tiles");
					if (trDistanceToVectorSquared("tiles", "spellProjectileEnd") < trDistanceToVectorSquared("temp", "spellProjectileEnd")) {
						trQuestVarSet("temp", trQuestVarGet("tiles"));
					}
				}
				
				deployAtTile(0, "Osiris Box Glow", 1*trQuestVarGet("temp"));
				int activeUnit = summonAtTile(1*trQuestVarGet("temp"), 1*mGetVarByQV("spellTarget", "player"), 1*mGetVarByQV("spellTarget", "proto"));
				if(HasKeyword(CHARGE, 1*mGetVar(activeUnit, "keywords")) == false){
					mSetVar(activeUnit, "action", ACTION_SLEEPING);
				}
				mSetVar(activeUnit, "attack", mGetVarByQV("spellTarget", "attack"));
				mSetVar(activeUnit, "health", mGetVarByQV("spellTarget", "health"));
				mSetVar(activeUnit, "maxhealth", mGetVarByQV("spellTarget", "maxhealth"));
				mSetVar(activeUnit, "speed", mGetVarByQV("spellTarget", "speed"));
				mSetVar(activeUnit, "range", mGetVarByQV("spellTarget", "range"));
				mSetVar(activeUnit, "keywords", mGetVarByQV("spellTarget", "keywords"));
				mSetVar(activeUnit, "onAttack", mGetVarByQV("spellTarget", "onAttack"));
				mSetVar(activeUnit, "onDeath", mGetVarByQV("spellTarget", "onDeath"));
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

rule spell_elven_apocalypse_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		int next = 0;
		for(x=yGetDatabaseCount("p"+p+"hand"); < 10) {
			trQuestVarSetFromRand("temp", 1, 4, true);
			if(trQuestVarGet("temp") == 1){
				next = addCardToHand(p, kbGetProtoUnitID("Hetairoi"), 0, true);
			} else if(trQuestVarGet("temp") == 2){
				next = addCardToHand(p, kbGetProtoUnitID("Hero Greek Theseus"), 0, true);
			} else if(trQuestVarGet("temp") == 3){
				next = addCardToHand(p, kbGetProtoUnitID("Peltast"), 0, true);
			} else {
				next = addCardToHand(p, kbGetProtoUnitID("Hero Chinese Immortal"), 0, true);
			}
			mSetVar(next, "cost", 0);
			mSetVar(next, "keywords", SetBit(mGetVar(next, "keywords"), AIRDROP));
		}
		xsDisableRule("spell_elven_apocalypse_activate");
	}
}

rule spell_corona_apocalypse_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		int next = 0;
		for(x=yGetDatabaseCount("p"+p+"hand"); < 10) {
			trQuestVarSetFromRand("temp", 1, 11, true);
			if(trQuestVarGet("temp") == 1){
				next = addCardToHand(p, kbGetProtoUnitID("Hero Greek Hippolyta"), 0, true);
			} else if(trQuestVarGet("temp") == 2){
				next = addCardToHand(p, kbGetProtoUnitID("Nemean Lion"), 0, true);
			} else if(trQuestVarGet("temp") == 3){
				next = addCardToHand(p, kbGetProtoUnitID("Hero Greek Bellerophon"), 0, true);
			} else if(trQuestVarGet("temp") == 4){
				next = addCardToHand(p, kbGetProtoUnitID("Circe"), 0, true);
			} else if(trQuestVarGet("temp") == 5){
				next = addCardToHand(p, kbGetProtoUnitID("Heka Gigantes"), 0, true);
			} else if(trQuestVarGet("temp") == 6){
				next = addCardToHand(p, kbGetProtoUnitID("Hero Greek Polyphemus"), 0, true);
			} else if(trQuestVarGet("temp") == 7){
				next = addCardToHand(p, kbGetProtoUnitID("Tower Mirror"), 0, true);
			} else if(trQuestVarGet("temp") == 8){
				next = addCardToHand(p, kbGetProtoUnitID("Guardian"), 0, true);
			} else if(trQuestVarGet("temp") == 9){
				next = addCardToHand(p, kbGetProtoUnitID("Hero Greek Achilles"), 0, true);
			} else if(trQuestVarGet("temp") == 10){
				next = addCardToHand(p, kbGetProtoUnitID("Hero Greek Heracles"), 0, true);
			} else {
				next = addCardToHand(p, kbGetProtoUnitID("Hero Greek Argo"), 0, true);
			}
			mSetVar(next, "cost", 0);
		}
		xsDisableRule("spell_corona_apocalypse_activate");
	}
}

rule spell_metal_gear_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		int next = 0;
		for(x=yGetDatabaseCount("p"+p+"hand"); < 10) {
			next = addCardToHand(p, kbGetProtoUnitID("Apep"), 0, true);
			mSetVar(next, "cost", 0);
			mSetVar(next, "keywords", SetBit(mGetVar(next, "keywords"), MAGNETIC));
		}
		xsDisableRule("spell_metal_gear_activate");
	}
}

rule spell_electric_grid_activate
highFrequency
inactive
{
	if (trQuestVarGet("castDone") == CASTING_NOTHING) {
		int p = trQuestVarGet("activePlayer");
		for(x=2; >0) {
			generateCard(p, kbGetProtoUnitID("Outpost"));
		}
		xsDisableRule("spell_electric_grid_activate");
	}
}

void laserEnd(int eventId = -1) {
	int p = trQuestVarGet("activePlayer");
	trQuestVarSet("p"+p+"worldSplitterActive", 3);
	trQuestVarSet("p"+p+"worldSplitterTimeout", trTimeMS() + 1000);
	trUnitSelectClear();
	trUnitSelectByQV("p"+p+"meteorite");
	trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
}

/*
Code taken straight from HBF2 lmao
*/
rule spell_world_splitter_activate
highFrequency
inactive
{
	int p = trQuestVarGet("activePlayer");
	
	// world splitter
	vector dir = vector(0,0,0);
	vector pos = vector(0,0,0);
	vector next = vector(0,0,0);
	int target = 0;
	float dist = 0;
	float scale = 0;
	switch(1*trQuestVarGet("p"+p+"worldSplitterActive"))
	{
	case 1:
		{
			if (trTimeMS() > trQuestVarGet("p"+p+"worldSplitterTimeout")) {
				zSetProtoUnitStat("Meteorite", p, 1, 1.0);
				trQuestVarSet("p"+p+"worldSplitterActive", 2);
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"meteorite");
				trMutateSelected(kbGetProtoUnitID("Meteorite"));
				trUnitOverrideAnimation(6, 0, true, false, -1); // EXPLOSION
				dir = trVectorQuestVarGet("p"+p+"worldSplitterDir");
				pos = trVectorQuestVarGet("laserEnd");
				trUnitMoveToPoint(xsVectorGetX(pos), 0, xsVectorGetZ(pos), EVENT_LASER_END, false);

				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"worldSplitterLaser");
				trSetSelectedScale(12.0,12.0,50.0);
				trUnitHighlight(50.0, false);
				trSetUnitOrientation(vector(0,1,0), rotationMatrix(dir, 1.0, 0), true);

				trSoundPlayFN("sonofosirisbolt.wav");
				trSoundPlayFN("phoenixattack.wav");
			}
		}
	case 2:
		{
			// calculate my speed
			pos = kbGetBlockPosition(""+1*trQuestVarGet("p"+p+"meteorite"));
			if (distanceBetweenVectors(pos, trVectorQuestVarGet("laserStart")) > 0.0) {
				//point the laser at the meteorite
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"worldSplitterLaser");
				trSetUnitOrientation(xsVectorNormalize(trVectorQuestVarGet("laserstart") - pos), rotationMatrix(trVectorQuestVarGet("p"+p+"worldSplitterDir"), 0.0, 1.0), true);

				dist = distanceBetweenVectors(pos, trVectorQuestVarGet("laserStart"), false);
				dir = xsVectorSet(dist, 0, xsVectorGetY(trVectorQuestVarGet("laserstart") - pos)); // construct a vector representation of the 3d angle
				dir = rotationMatrix(dir, 0.9998, -0.019999); // the angle one second from now is 0.02 radians further
				dir = dir * (xsVectorGetY(trVectorQuestVarGet("laserstart") - pos) / xsVectorGetZ(dir)); // scale it back up

				scale = 60.0 * (xsVectorGetX(dir) - dist); // this is our speed if we need to reach that next spot in 1/60th of a second
				zSetProtoUnitStat("Meteorite", p, 1, scale);
			}
			/*
			if (distanceBetweenVectors(pos, trVectorQuestVarGet("laserEnd")) <= 9.0) {
				trQuestVarSet("p"+p+"worldSplitterActive", 3);
				trQuestVarSet("p"+p+"worldSplitterTimeout", trTimeMS() + 1000);
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"meteorite");
				trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
			}
			*/
			next = pos;
			pos = trVectorQuestVarGet("p"+p+"worldSplitterPrev");
			dist = distanceBetweenVectors(next, pos);
			if (dist > 9.0) {
				dir = trVectorQuestVarGet("p"+p+"worldSplitterDir");
				dist = xsSqrt(dist);
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"meteoriteDeployer");
				trUnitChangeProtoUnit("Transport Ship Greek");
				target = trGetNextUnitScenarioNameNumber();
				trArmyDispatch(""+p+",0","Dwarf",1,xsVectorGetX(pos),0,xsVectorGetZ(pos),0,true);
				trUnitSelectClear();
				trUnitSelect(""+target, true);
				trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"meteoriteDeployer"));
				trUnitChangeProtoUnit("Tartarian Gate flame");
				
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"meteoriteDeployer");
				trUnitChangeProtoUnit("Cinematic Block");

				trUnitSelectClear();
				trUnitSelect(""+target, true);
				trSetSelectedScale(1.0, 1.0, dist * 0.3);
				trVectorQuestVarSet("p"+p+"worldSplitterPrev", next);
			}
		}
	case 3:
		{
			scale = 0.012 * (trQuestVarGet("p"+p+"worldSplitterTimeout") - trTimeMS());
			if (scale > 0) {
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"worldSplitterLaser");
				trSetSelectedScale(scale, scale, 50.0);
			} else {
				trUnitSelectClear();
				trUnitSelectByQV("spellTarget");
				trUnitChangeProtoUnit(kbGetProtoUnitName(mGetVarByQV("spellTarget", "proto")));
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"phoenix");
				trUnitChangeProtoUnit("Cinematic Block");
				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"worldSplitterLaser");
				trUnitChangeProtoUnit("Cinematic Block");

				trUnitSelectClear();
				trUnitSelectByQV("p"+p+"floater");
				trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
				trQuestVarSet("p"+p+"worldSplitterActive", 0);

				xsDisableSelf();
				xsEnableRule("spell_attack_complete");

				for(x=yGetDatabaseCount("worldSplitterHit"); >0) {
					yDatabaseNext("worldSplitterHit");
					startAttack(1*trQuestVarGet("spellTarget"), 1*trQuestVarGet("worldSplitterHit"), false, false);
				}
			}
		}
	}
}

rule spell_banhammer_activate
highFrequency
inactive
{
	int x = 0;
	switch(1*trQuestVarGet("hammerStep"))
	{
		case 0:
		{
			if (trTimeMS() > trQuestVarGet("hammerNext")) {
				trQuestVarSet("hammerStep", 1);
				trQuestVarSet("hammerNext", trTimeMS() + 1000);
				trSoundPlayFN("implode reverse.wav","1",-1,"","");
			}
		}
		case 1:
		{
			if (trTimeMS() >= trQuestVarGet("hammerNext")) {
				trQuestVarSet("hammerStep", 2);
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("banhammer"), true);
				trUnitChangeProtoUnit("Meteor Impact Ground");
				trUnitSelectClear();
				for(x=25; >0) {
					trUnitSelect(""+1*trQuestVarGet("hammerPos"+x), true);
				}
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("hammerPos0"), true);
				trDamageUnitPercent(100);
				trUnitChangeProtoUnit("Implode Sphere Effect");
				trSoundPlayFN("cinematics\35_out\strike.mp3","1",-1,"","");
				trCameraShake(2.5, 0.25);
			} else {
				x = xsMax(0, (trQuestVarGet("hammerNext") - trTimeMS()) / 40);
				if (x < trQuestVarGet("hammerPosPrev")) {
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("banhammer"), true);
					trUnitChangeProtoUnit("Dwarf");
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("hammerPos"+x), true);
					trMutateSelected(kbGetProtoUnitID("Hero Greek Achilles"));
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("banhammer"), true);
					trMutateSelected(kbGetProtoUnitID("Thor hammer"));
					trUnitSetAnimationPath("0,0,0,0,0,0,0");
					trMutateSelected(kbGetProtoUnitID("Relic"));
					trImmediateUnitGarrison(""+1*trQuestVarGet("hammerPos"+x));
					trMutateSelected(kbGetProtoUnitID("Thor hammer"));
					
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("hammerPos"+x), true);
					trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
					trQuestVarSet("hammerPosPrev", trQuestVarGet("hammerPos"+x));
				}
			}
		}
		case 2:
		{
			mSetVarByQV("spellTarget", "health", 0);
			damageUnit(1*trQuestVarGet("spellTarget"), 100);
			if (trQuestVarGet("p"+1*trQuestVarGet("activePlayer")+"commanderType") == COMMANDER_YEEBAAGOOON) {
				int p = mGetVarByQV("spellTarget", "player");
				for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					if (mGetVarByQV("p"+p+"hand", "proto") == mGetVarByQV("spellTarget", "proto")) {
						trUnitSelectClear();
						trUnitSelect(""+1*trQuestVarGet("p"+p+"hand"), true);
						trMutateSelected(kbGetProtoUnitID("Victory Marker"));
						zSetVarByIndex("p"+p+"handPos", "occupied", 1*yGetVar("p"+p+"hand", "pos"), 0);
						yRemoveFromDatabase("p"+p+"hand");
					}
				}
				for(x=yGetDatabaseCount("p"+p+"deck"); >0) {
					if (yDatabaseNext("p"+p+"deck") == mGetVarByQV("spellTarget", "proto")) {
						yRemoveFromDatabase("p"+p+"deck");
					}
				}
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					if (mGetVarByQV("allUnits", "player") == p) {
						if (mGetVarByQV("allUnits", "proto") == mGetVarByQV("spellTarget", "proto")) {
							damageUnit(1*trQuestVarGet("allUnits"), 100);
						}
					}
				}
			}
			castEnd();
			xsDisableRule("spell_banhammer_activate");
		}
	}
}

rule the_calling
inactive
highFrequency
{
	float dist = 0;
	int primary = 0;
	int secondary = 0;
	int p = trQuestVarGet("activePlayer");
	vector data = vector(0,0,0);
	vector pos = trVectorQuestVarGet("theCallingPos");
	switch(1*trQuestVarGet("theCallingStep"))
	{
		case 1:
		{
			if (trTimeMS() > trQuestVarGet("theCallingNext")) {
				trQuestVarSet("theCallingNext", trTimeMS() + 200);
				trQuestVarSet("theCallingRadius", trQuestVarGet("theCallingRadius") - 4);
				dist = xsPow(trQuestVarGet("theCallingRadius"), 2);
				for(x=0; < 60) {
					for(y=0; < 60) {
						if (dist < distanceBetweenVectors(pos, xsVectorSet(x, 0, y) * 2.0)) {
							trPaintTerrain(x, y, x, y, 5, 4, false); // paint black
						}
					}
				}
				if (trQuestVarGet("theCallingRadius") == 0) {
					trQuestVarSet("theCallingStep", 2);
					trSoundPlayFN("wonderdeath.wav","1",-1,"","");
					trCameraShake(3.0, 0.5);
					trQuestVarSet("theCallingRadius", 80);
					int next = summonAtTile(1*trQuestVarGet("spellTarget"), p, kbGetProtoUnitID("Titan Kronos"));
					for(x=yGetDatabaseCount("allUnits"); >0) {
						yDatabaseNext("allUnits");
						if ((trQuestVarGet("allUnits") != next) && (mGetVarByQV("allUnits", "spell") == SPELL_NONE)) {
							deployAtTile(0, "Kronny Birth SFX", mGetVarByQV("allUnits", "tile"));
							magnetize(next, 1*trQuestVarGet("allUnits"));
							yRemoveFromDatabase("allUnits");
						}
					}
					mSetVar(next, "scale", 0);
					trUnitSelectClear();
					trUnitSelect(""+next);
					trSetSelectedScale(0.1, 0.1, 0.1);
				}
			}
		}
		case 2:
		{
			if (trTimeMS() > trQuestVarGet("theCallingNext")) {
				trQuestVarSet("theCallingNext", trTimeMS() + 200);
				trQuestVarSet("theCallingRadius", trQuestVarGet("theCallingRadius") - 5);
				dist = xsPow(trQuestVarGet("theCallingRadius"), 2);
				for(x=0; < 60) {
					for(y=0; < 60) {
						if (dist < distanceBetweenVectors(pos, xsVectorSet(x, 0, y) * 2.0)) {
							data = aiPlanGetUserVariableVector(terrainTiles, x, y);
							primary = xsVectorGetX(data);
							secondary = xsVectorGetY(data);
							trPaintTerrain(x, y, x, y, primary, secondary, false); // paint black
						}
					}
				}
				if (trQuestVarGet("theCallingRadius") == 0) {
					xsDisableSelf();
					castEnd();
				}
			}
		}
	}
}


rule bullet_storm_active
inactive
highFrequency
{
	int p = trQuestVarGet("activePlayer");
	if (trTimeMS() > trQuestVarGet("bulletStormNext")) {
		trQuestVarSet("bulletStormNext", trQuestVarGet("bulletStormNext") + 100);
		trVectorQuestVarSet("bulletStormDir", rotationMatrix(trVectorQuestVarGet("bulletStormDir"), -0.740544, -0.672008));
		trUnitSelectClear();
		trUnitSelectByQV("bulletStormSmoke", true);
		trSetUnitOrientation(trVectorQuestVarGet("bulletStormDir"), vector(0,1,0), true);

		// attacks
		if (yGetDatabaseCount("bulletStormTargets") > 0 && (trQuestVarGet("lightningPop") == trQuestVarGet("lightningActivate"))) {
			// animation
			trQuestVarSet("next", deployAtTile(0, "Dwarf", mGetVarByQV("p"+p+"commander", "tile")));
			trUnitSelectClear();
			trUnitSelectByQV("next", true);
			trSetUnitOrientation(trVectorQuestVarGet("bulletStormDir"), vector(0,1,0), true);
			trMutateSelected(kbGetProtoUnitID("Petosuchus Projectile"));
			trUnitHighlight(5.0, false);
			trQuestVarSetFromRand("rand", 0.8, 1.2, false);
			yAddToDatabase("bulletStormLasers", "next");
			yAddUpdateVar("bulletStormLasers", "scale", (3.6 + 7.2 * mGetVarByQV("p"+p+"commander", "range")) * trQuestVarGet("rand"));
			yAddUpdateVar("bulletStormLasers", "timeout", trTimeMS() + 1000);
			trSoundPlayFN("titanfall.wav");

			trUnitSelectClear();
			trUnitSelectByQV("p"+p+"commander");
			trSetUnitOrientation(trVectorQuestVarGet("bulletStormDir"), vector(0,1,0), true);

			trQuestVarSet("bulletStormTremor", trQuestVarGet("bulletStormTremor") - 1);
			if (trQuestVarGet("bulletStormTremor") <= 0) {
				trQuestVarSet("bulletStormTremor", 5);
				trUnitSelect(""+deployAtTile(0, "Dwarf", mGetVarByQV("p"+p+"commander", "tile")), true);
				trUnitChangeProtoUnit("Tremor");
			}

			trQuestVarSet("bulletStormHit", trQuestVarGet("bulletStormHit") - 1);
			if (trQuestVarGet("bulletStormHit") <= 0) {
				trQuestVarSet("bulletStormHit", 3);
				deployAtTile(0, "Tremor", mGetVarByQV("p"+p+"commander", "tile"));
				startAttack(1*trQuestVarGet("p"+p+"commander"), yDatabaseNext("bulletStormTargets"), false, false);
				yRemoveFromDatabase("bulletStormTargets");
			}
		}
	}
	if (yGetDatabaseCount("bulletStormLasers") > 0) {
		yDatabaseNext("bulletStormLasers", true);
		if (trTimeMS() > yGetVar("bulletStormLasers", "timeout")) {
			trUnitDestroy();
			yRemoveFromDatabase("bulletStormLasers");
		} else {
			float scale = 0.004 * (yGetVar("bulletStormLasers", "timeout") - trTimeMS());
			trSetSelectedScale(scale, scale, yGetVar("bulletStormLasers", "scale"));
		}
	}
	if ((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + yGetDatabaseCount("bulletStormTargets") + yGetDatabaseCount("bulletStormLasers") == 0) && (trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) {
		trUnitSelectClear();
		trUnitSelectByQV("bulletStormSphinx", true);
		trUnitChangeProtoUnit("Dust Large");
		trUnitSelectClear();
		trUnitSelectByQV("bulletStormSmoke", true);
		trUnitChangeProtoUnit("Dust Large");
		castEnd();
		xsDisableSelf();
	}
}

rule ride_the_lightning_bonus
inactive
highFrequency
{
	if (trQuestVarGet("activePlayer") != trQuestVarGet("rideTheLightningPlayer")) {
		int p = trQuestVarGet("rideTheLightningPlayer");
		mSetVarByQV("p"+p+"commander", "speed", mGetVarByQV("p"+p+"commander", "speed") - trQuestVarGet("rideTheLightningBonus"));
		mSetVarByQV("p"+p+"commander", "keywords", ClearBit(mGetVarByQV("p"+p+"commander", "keywords"), ETHEREAL));
		xsDisableSelf();
	}
}

void spawnFinger(vector center = vector(0,0,0), vector offset = vector(0,0,0), vector dest = vector(0,0,0), float scale = 0) {
	vector pos = center + offset;
	vector dir = xsVectorNormalize(rotationMatrix(dest - offset, 0, -1.0));
	trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
	yAddToDatabase("fingers", "next");
	trArmyDispatch("0,0","Dwarf",1,xsVectorGetX(pos),0,xsVectorGetZ(pos),0,true);
	trArmySelect("0,0");
	trMutateSelected(kbGetProtoUnitID("Taproot Small"));
	trSetSelectedScale(0.0 - scale, scale, 0.0 - scale);
	trUnitSetAnimationPath("0,0,0,0,0,0,0");
	trSetUnitOrientation(dir, vector(0,-1,0), true);
	yAddUpdateVector("fingers", "dir", dir);
}

rule devour_animation
inactive
highFrequency
{
	int x = 0;
	int z = 0;
	int primary = 0;
	int secondary = 0;
	int dist = 0;
	int p = trQuestVarGet("activePlayer");
	vector data = vector(0,0,0);
	vector pos = vector(0,0,0);
	vector center = vector(0,0,0);
	vector test = vector(0,0,0);
	switch(1*trQuestVarGet("keeperGrabStep"))
	{
		case 0:
		{
			if (trTimeMS() > trQuestVarGet("keeperGrabTime")) {
				trQuestVarSet("keeperGrabTime", trQuestVarGet("keeperGrabTime") + 200);
				trQuestVarSet("keeperGrabRadius", 1 + trQuestVarGet("keeperGrabRadius"));
				pos = vectorToGrid(trVectorQuestVarGet("keeperPos"));
				dist = xsPow(trQuestVarGet("keeperGrabRadius"), 2);
				for(a=0-trQuestVarGet("keeperGrabRadius"); <= trQuestVarGet("keeperGrabRadius")) {
					for(b=0-trQuestVarGet("keeperGrabRadius"); <= trQuestVarGet("keeperGrabRadius")) {
						test = pos + xsVectorSet(a, 0, b);
						if (distanceBetweenVectors(pos, test) <= dist) {
							x = xsVectorGetX(test);
							z = xsVectorGetZ(test);
							primary = trGetTerrainType(x, z);
							secondary = trGetTerrainSubType(x, z);
							if ((primary != 5) || (secondary != 4)) {
								trPaintTerrain(x, z, x, z, 5, 4, false);
							}
						}
					}
				}
				if (trQuestVarGet("keeperGrabRadius") >= 8) {
					trQuestVarSet("keeperGrabStep", 1);
				}
			}
		}
		case 1:
		{
			center = trVectorQuestVarGet("keeperPos");
			test = vector(-10, 0, -10);
			trQuestVarSet("keeperGrabStep", 2);
			// thumb
			spawnFinger(center, vector(-6, 0, 2), vector(-1,0,-1), 3.5);
			// other fingers
			spawnFinger(center, vector(0, 0, 4), test, 4.5);
			spawnFinger(center, vector(2, 0, 2), test, 5.5);
			spawnFinger(center, vector(4, 0, 0), test, 4.5);
			spawnFinger(center, vector(4, 0, -2), test, 3.5);

			trSoundPlayFN("cinematics\31_in\swipenew.mp3","1",-1,"","");
			trQuestVarSet("keeperGrabStep", 2);
			trQuestVarSet("keeperAngle", 3.141592);
			trQuestVarSet("keeperGrabTime", trTimeMS());

			trCameraShake(3.0, 0.3);
		}
		case 2:
		{
			float diff = trTimeMS() - trQuestVarGet("keeperGrabTime");
			trQuestVarSet("keeperAngle", 3.141592 - 0.001 * diff);
			float mCos = xsCos(trQuestVarGet("keeperAngle"));
			float mSin = xsSin(trQuestVarGet("keeperAngle"));
			for(i=5; >0) {
				yDatabaseNext("fingers", true);
				pos = xsVectorSetY(rotationMatrix(yGetVector("fingers", "dir"), 0.0, -1.0) * mSin, mCos);
				trSetUnitOrientation(yGetVector("fingers", "dir"), pos, true);
			}
			if (trQuestVarGet("keeperAngle") < 0) {
				trQuestVarSet("keeperGrabStep", 3);
				trSoundPlayFN("xpack\xcinematics\7_in\krioschange.mp3","1",-1,"","");
				trUnitSelectClear();
				trUnitSelectByQV("keeperTartarianGate");
				trUnitChangeProtoUnit("Tartarian Gate birth");
				trUnitSelectClear();
				trUnitSelectByQV("keeperTartarianGate");
				trSetSelectedScale(0,0,0);
				trCameraShake(3.0, 0.5);
				trQuestVarSet("keeperGrabTime", trTimeMS() + 1000);
				
			}
		}
		case 3:
		{
			if (trTimeMS() > trQuestVarGet("keeperGrabTime")) {
				trQuestVarSet("keeperGrabTime", trTimeMS() + 200);
				trQuestVarSet("keeperGrabRadius", trQuestVarGet("keeperGrabRadius") - 1);
				dist = xsPow(trQuestVarGet("keeperGrabRadius"), 2);
				center = vectorToGrid(trVectorQuestVarGet("keeperPos"));
				for(x=0; < 60) {
					for(y=0; < 60) {
						if (dist <= distanceBetweenVectors(center, xsVectorSet(x, 0, y))) {
							data = aiPlanGetUserVariableVector(terrainTiles, x, y);
							primary = xsVectorGetX(data);
							secondary = xsVectorGetY(data);
							trPaintTerrain(x, y, x, y, primary, secondary, false); // paint back
						}
					}
				}
				if (trQuestVarGet("keeperGrabRadius") == 0) {
					xsDisableSelf();
					trSoundPlayFN("spybirth.wav","1",-1,"","");
					trCameraShake(3.0, 1.0);
					for(i=yGetDatabaseCount("fingers"); >0) {
						yDatabaseNext("fingers", true);
						trUnitChangeProtoUnit("Hero Death");
					}
					trUnitSelectClear();
					trUnitSelectByQV("keeperTartarianGate");
					trUnitDestroy();
					

					// devour
					addCardToDeck(p, kbGetProtoUnitName(1*mGetVarByQV("spellTarget", "proto")), 0, true);
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
					tileGuard(1*mGetVarByQV("spellTarget", "tile"), false);

					castEnd();
				}
			}
		}
	}
}

rule death_door_animation
inactive
highFrequency
{

	if (trTimeMS() > trQuestVarGet("deathDoorTime")) {
		trSoundPlayFN("tartariangateselect.wav");
		int target = returnToHand(1*trQuestVarGet("spellTarget"));
		mSetVar(target, "keywords", SetBit(mGetVar(target, "keywords"), FLEETING));
		xsDisableSelf();
		castEnd();
	} else {
		float height = 0.008 * (trQuestVarGet("deathDoorTime") - trTimeMS());
		float dist = 0.003 * (trQuestVarGet("deathDoorTime") - trTimeMS());
		float diff = 0.001 * (trTimeMS() - trQuestVarGet("deathDoorLast"));
		trQuestVarSet("deathDoorLast", trTimeMS());
		trQuestVarSet("deathDoorAngle", fModulo(6.283185, trQuestVarGet("deathDoorAngle") + diff * 3.141592));
		trUnitSelectClear();
		trUnitSelectByQV("deathDoorUnit1");
		trUnitTeleport(dist * xsCos(trQuestVarGet("deathDoorAngle")) + trVectorQuestVarGetX("deathDoorPos"), 
			height + trVectorQuestVarGetY("deathDoorPos"),
			dist * xsSin(trQuestVarGet("deathDoorAngle")) + trVectorQuestVarGetZ("deathDoorPos"));
		trUnitSelectClear();
		trUnitSelectByQV("deathDoorUnit2");
		trUnitTeleport(0.0 - dist * xsCos(trQuestVarGet("deathDoorAngle")) + trVectorQuestVarGetX("deathDoorPos"), 
			height + trVectorQuestVarGetY("deathDoorPos"),
			0.0 - dist * xsSin(trQuestVarGet("deathDoorAngle")) + trVectorQuestVarGetZ("deathDoorPos"));
		if (trTimeMS() > trQuestVarGet("deathDoorNext")) {
			trUnitSelectClear();
			trUnitSelectByQV("deathDoorUnit1");
			trUnitChangeProtoUnit("Kronny Birth SFX");
			trUnitSelectClear();
			trUnitSelectByQV("deathDoorUnit2");
			trUnitChangeProtoUnit("Kronny Birth SFX");
			trQuestVarSet("deathDoorNext", trTimeMS() + 500);
		}
	}
}

rule magic_missiles_active
inactive
highFrequency
{
	float acceleration = 0.003 * (trTimeMS() - trQuestVarGet("magicMissilesStartTime"));
	float timediff = 0.001 * (trTimeMS() - trQuestVarGet("magicMissilesTime"));
	vector dir = vector(0,0,0);
	vector pos = vector(0,0,0);
	float dist = 0;
	int p = trQuestVarGet("activePlayer");
	trQuestVarSet("magicMissilesTime", trTimeMS());
	if (yGetDatabaseCount("magicMissiles") > 0) {
		for (i = yGetDatabaseCount("magicMissiles"); >0) {
			yDatabaseNext("magicMissiles", true);
			pos = yGetVector("magicMissiles", "pos");
			dist = distanceBetweenVectors(pos, yGetVector("magicMissiles", "targetPos")); // distance squared
			if (dist < xsSqrt(acceleration)) {
				trUnitDestroy();
				damageUnit(1*yGetVar("magicMissiles", "target"), 1 + trQuestVarGet("p" + p + "spellDamage"));
				trQuestVarSetFromRand("sound", 1, 5, true);
				trSoundPlayFN("ui\lightning"+1*trQuestVarGet("sound")+".wav");
				trUnitSelect(""+deployAtTile(0, "Dwarf", mGetVar(1*yGetVar("magicMissiles", "target"), "tile")));
				trDamageUnitPercent(100);
				trUnitChangeProtoUnit("Meteorite");
				yRemoveFromDatabase("magicMissiles");
			} else {
				dir = yGetVector("magicMissiles", "dir") / (1.0 + timediff) + getUnitVector(pos, yGetVector("magicMissiles", "targetPos"), 10.0 * timediff * acceleration);
				ySetVector("magicMissiles", "dir", dir);
				pos = pos + dir * timediff;
				ySetVector("magicMissiles", "pos", pos);
				dir = (pos - trVectorQuestVarGet("magicMissilesCenter")) * 3.33;
				trSetSelectedUpVector(xsVectorGetX(dir), 0.2, xsVectorGetZ(dir));
			}
		}
	} else {
		castEnd();
		xsDisableSelf();
	}
}