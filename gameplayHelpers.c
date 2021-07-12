
const int ACTION_READY = 0;
const int ACTION_MOVED = 1;
const int ACTION_DONE = 2;
const int ACTION_FURY = 3;
const int ACTION_STUNNED = 4;

const int ATTACK_START = 0;
const int ATTACK_ANIMATE = 1;
const int ATTACK_DONE = 2;




void updateMana() {
	int p = trQuestVarGet("activePlayer");
	trCounterAbort("mana");
	trCounterAddTime("mana", -1, -91, 
			"<color={Playercolor("+p+")}>Mana: "+1*trQuestVarGet("p"+p+"mana") + "/" + 1*trQuestVarGet("maxMana"),-1);
}




/*
Removes the currently selected unit in a search from
the database. This is where we put all the special variables
that need to be updated whenever a unit is removed.
This is called only after a yDatabaseNext("allUnits").
*/
void removeUnit(string db = "allUnits") {
	yRemoveFromDatabase(db);
	yRemoveUpdateString(db, "ability");
	yRemoveUpdateVar(db, "cost");
	yRemoveUpdateVar(db, "pos");
	yRemoveUpdateVar(db, "health");
	yRemoveUpdateVar(db, "attack");
	yRemoveUpdateVar(db, "range");
	yRemoveUpdateVar(db, "speed");
	yRemoveUpdateVar(db, "proto");
	yRemoveUpdateVar(db, "player");
	yRemoveUpdateVar(db, "ready");
	yRemoveUpdateVar(db, "keywords");
	yRemoveUpdateVar(db, "tile");
	yRemoveUpdateVar(db, "spell");
	yRemoveUpdateVar(db, "action");
	yRemoveUpdateVar(db, "onPlay");
	yRemoveUpdateVar(db, "onAttack");
	yRemoveUpdateVar(db, "onDeath");
	yRemoveUpdateVar(db, "stunTime");
	yRemoveUpdateVar(db, "stunSFX");
	yRemoveUpdateVar(db, "stunIndex");
}

/*
Transfers the unit at the current pointer in the 'from' database
to the 'to' database.
*/
void transferUnit(string to = "", string from = "") {
	yAddToDatabase(to, from);
	yTransferUpdateString(to, from, "ability");
	yTransferUpdateVar(to, from, "cost");
	yTransferUpdateVar(to, from, "pos");
	yTransferUpdateVar(to, from, "health");
	yTransferUpdateVar(to, from, "attack");
	yTransferUpdateVar(to, from, "range");
	yTransferUpdateVar(to, from, "speed");
	yTransferUpdateVar(to, from, "proto");
	yTransferUpdateVar(to, from, "player");
	yTransferUpdateVar(to, from, "ready");
	yTransferUpdateVar(to, from, "keywords");
	yTransferUpdateVar(to, from, "tile");
	yTransferUpdateVar(to, from, "spell");
	yTransferUpdateVar(to, from, "action");
	yTransferUpdateVar(to, from, "onPlay");
	yTransferUpdateVar(to, from, "onAttack");
	yTransferUpdateVar(to, from, "onDeath");
	yTransferUpdateVar(to, from, "stunTime");
	yTransferUpdateVar(to, from, "stunSFX");
	yTransferUpdateVar(to, from, "stunIndex");
}



void teleportToTile(string db = "", int tile = 0, int index = -1) {
	int p = yGetVar(db, "player");
	if (index == -1) {
		index = yGetPointer(db);
	}

	if (HasKeyword(GUARD, 1*yGetVarByIndex(db, "keywords", index))) {
		if (yGetVarByIndex(db, "tile", index) > 0) {
			tileGuard(1*yGetVarByIndex(db, "tile", index), false);
		}
		tileGuard(tile, true);
	}
	

	trUnitSelectClear();
	trUnitSelectByID(tile);
	trUnitConvert(p);
	trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
	
	trUnitSelectClear();
	trUnitSelect(""+1*yGetUnitAtIndex(db, index), true);
	trMutateSelected(kbGetProtoUnitID("Dwarf"));
	trImmediateUnitGarrison(""+tile);
	trUnitChangeProtoUnit(kbGetProtoUnitName(1*yGetVarByIndex(db, "proto", index)));

	trUnitSelectClear();
	trUnitSelectByID(tile);
	trUnitConvert(0);
	trMutateSelected(kbGetProtoUnitID("Victory Marker"));

	ySetVarByIndex(db, "tile", index, tile);
}




/*
Given a QV vector name, find the name of the closest unit to it. 
Returns the index of the unit in the 'allUnits' array. This index can 
be used in yGetVarByIndex and ySetVarByIndex and yGetUnitAtIndex.
Returns -1 if none found.
BEWARE: if this unit is removed from the database, the pointer will no longer
point to it!
*/
int findNearestUnit(string qv = "", float radius = 1) {
	int id = 0;
	for (x=yGetDatabaseCount("allUnits"); >0) {
		id = yDatabaseNext("allUnits", true);
		if (id == -1) {
			removeUnit();
		} else {
			if (zDistanceToVectorSquared("allUnits", qv) < radius) {
				return(yGetPointer("allUnits"));
			}
		}
	}
	return(-1);
}




/*
Given the index of a unit in the allUnits database, highlight
the tiles that are reachable by that unit.
*/
void highlightReachable(int index = 0) {
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetUnitAtIndex("allUnits", index), true));
	int tile = findNearestTile("pos");
	findAvailableTiles(tile, yGetVarByIndex("allUnits", "speed", index), 
		"reachable", HasKeyword(ETHEREAL, 1*yGetVarByIndex("allUnits", "keywords", index)));
	for(x=yGetDatabaseCount("reachable"); >0) {
		tile = yDatabaseNext("reachable");
		highlightTile(tile, 3600);
	}
}

/*
highlights units that are ready to perform an action
*/
void highlightReady(float duration = 0.1) {
	int p = trQuestVarGet("activePlayer");
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		if (yGetVar("allUnits", "action") == ACTION_READY && yGetVar("allUnits", "player") == p) {
			if (trCurrentPlayer() == p) {
				trUnitHighlight(duration, false);
			}
		}
	}
}

/*
Given the index of a unit in the allUnits database, find
enemy units that can be attacked by the unit and add them to
the database db.
*/
void findTargets(int index = 0, string db = "") {
	float dist = xsPow(yGetVarByIndex("allUnits", "range", index) * 6 + 1, 2);
	int p = 3 - yGetVarByIndex("allUnits", "player", index);
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetUnitAtIndex("allUnits", index), true));
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		if (yGetVar("allUnits", "player") == p) {
			if (zDistanceToVectorSquared("allUnits", "pos") < dist) {
				yAddToDatabase(db, "allUnits");
			}
		}
	}
}

void damageUnit(string db = "", int index = 0, float dmg = 0) {
	xsSetContextPlayer(1*yGetVarByIndex(db, "player", index));
	float health = kbUnitGetCurrentHitpoints(kbGetBlockID(""+1*yGetUnitAtIndex(db, index), true));
	ySetVarByIndex(db, "health", index, 1*yGetVarByIndex(db, "health", index) - dmg);
	trUnitSelectClear();
	trUnitSelect(""+1*yGetUnitAtIndex(db, index), true);
	trDamageUnit(health - yGetVarByIndex(db, "health", index));
}

void removeIfDead(string db = "", int index = -1) {
	if (index >= 0) {
		ySetPointer(db, index);
	}
	if (yGetVar(db, "health") <= 0) {
		int tile = yGetVar(db, "tile");
		zSetVarByIndex("tiles", "occupied", tile, xsMax(TILE_EMPTY, zGetVarByIndex("tiles", "terrain", tile)));
		trDamageUnitPercent(100);
		if (HasKeyword(GUARD, 1*yGetVar(db, "keywords"))) {
			tileGuard(tile, false);
		}
		removeUnit(db);
	}
}

void lightning(int index = 0, int damage = 0, bool deadly = false) {
	trQuestVarSetFromRand("rand", 1, 5, true);
	trSoundPlayFN("lightningstrike"+1*trQuestVarGet("rand")+".wav","1",-1,"","");
	int p = yGetVarByIndex("allUnits", "player", index);
	yClearDatabase("lightningTargets");
	for (x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		if (yGetVar("allUnits", "player") == p) {
			trQuestVarSet("allUnitsIndex", yGetPointer("allUnits"));
			if ((trQuestVarGet("allUnitsIndex") == index) == false) {
				yAddToDatabase("lightningTargets", "allUnitsIndex");
			}
		}
	}
	if (deadly) {
		damage = -1;
	}
	// find lightning chain
	int pop = -1;
	int push = modularCounterNext("lightningPush");
	trQuestVarSet("lightning" + push, index);
	trQuestVarSet("lightning" + push + "damage", damage);
	while ((pop == push) == false) {
		pop = modularCounterNext("lightningPop");
		trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", 1*trQuestVarGet("lightning" + pop))));
		for (x=yGetDatabaseCount("lightningTargets"); >0) {
			yDatabaseNext("lightningTargets");
			trQuestVarSet("lightningTargetUnit", yGetUnitAtIndex("allUnits", 1*trQuestVarGet("lightningTargets")));
			if (zDistanceToVectorSquared("lightningTargetUnit", "pos") <= 64) {
				push = modularCounterNext("lightningPush");
				trQuestVarCopy("lightning" + push, "lightningTargets");
				trQuestVarSet("lightning"+push+"damage", damage);
				yRemoveFromDatabase("lightningTargets");
			}
		}
	}
}


/*
int attacker = index of attacking unit in the "allUnits" database
int target = index of the target unit in the "allUnits" database
bool first = true if the unit has Ambush keyword and activates it.
bool animate = does this attack need an animation?
*/
void startAttack(int attacker = 0, int target = 0, bool first = false, bool animate = true) {
	string db = "attacks";
	if (first) {
		db = "ambushAttacks";
	}
	trQuestVarSet("temp", attacker);
	yAddToDatabase(db, "temp");
	yAddUpdateVar(db, "target", target);
	if (animate) {
		yAddUpdateVar(db, "phase", ATTACK_START);
	} else {
		yAddUpdateVar(db, "phase", ATTACK_DONE);
	}
}



bool spyReady() {
	return(trQuestVarGet("spyFind") == trQuestVarGet("spyFound"));
}


/*
Casts spy on the currently selected unit. The spy will transform into the specified protounit.
Returns the index of the spy eye in case the user wants to reference it later. The name of the
spy eye will be set in the quest var "spyEye"+x, where x is the integer returned by this function.
*/
int spyEffect(string proto = "") {
	int x = modularCounterNext("spyFind");
	trQuestVarSet("spyEye"+x+"proto", kbGetProtoUnitID(proto));
	trTechInvokeGodPower(0, "spy", xsVectorSet(1,1,1), xsVectorSet(1,1,1));
	return(x);
}

rule spy_find
highFrequency
active
{
	if (spyReady() == false) {
		while (yFindLatest("spyEye", "Spy Eye", 0) >= 0) {
			int x = modularCounterNext("spyFound");
			trQuestVarCopy("spyEye"+x, "spyEye");
			trMutateSelected(1*trQuestVarGet("spyEye"+x+"proto"));
			trQuestVarSet("spyTimeout", 0);
		}
		trQuestVarSet("spyTimeout", trQuestVarGet("spyTimeout") + 1);
		if (trQuestVarGet("spyTimeout") >= 5) {
			trQuestVarCopy("spyFound", "spyFind");
		}
	}
}

/*
index = index of unit in the allUnits database.
*/
void stunUnit(int index = 0) {
	if (yGetVarByIndex("allUnits", "health", index) > 0) {
		ySetVarByIndex("allUnits", "stunTime", index, 2);
		ySetVarByIndex("allUnits", "action", index, ACTION_STUNNED);
		if (yGetVarByIndex("allUnits", "stunSFX", index) == 0) {
			trUnitSelectClear();
			trUnitSelect(""+1*yGetUnitAtIndex("allUnits", index), true);
			ySetVarByIndex("allUnits", "stunIndex", index, spyEffect("Shockwave stun effect"));
			xsEnableRule("spy_assign_new");
		} else {
			trUnitSelectClear();
			trUnitSelect(""+1*yGetVarByIndex("allUnits", "stunSFX", index), true);
			trMutateSelected(kbGetProtoUnitID("Shockwave stun effect"));
		}
	}
}

rule spy_assign_new
highFrequency
inactive
{
	if (spyReady())	{
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if ((yGetVar("allUnits", "stunSFX") == 0) && (yGetVar("allUnits", "stunIndex") > 0)) {
				ySetVar("allUnits", "stunSFX", trQuestVarGet("spyEye"+1*yGetVar("allUnits", "stunIndex")));
			}
		}
		xsDisableRule("spy_assign_new");
	}
}