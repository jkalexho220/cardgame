

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
	yRemoveUpdateVar(db, "attackEvent");
	yRemoveUpdateVar(db, "deathEvent");
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
	yTransferUpdateVar(to, from, "attackEvent");
	yTransferUpdateVar(to, from, "deathEvent");
}



void teleportToTile(string db = "", int tile = 0, int index = -1) {
	int p = yGetVar(db, "player");
	if (index == -1) {
		index = yGetPointer(db);
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
		int tile = yGetVar("allUnits", "tile");
		zSetVarByIndex("tiles", "occupied", tile, xsMax(TILE_EMPTY, zGetVarByIndex("tiles", "terrain", tile)));
		trDamageUnitPercent(100);
		removeUnit(db);
	}
}
