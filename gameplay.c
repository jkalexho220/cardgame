
const int ACTION_READY = 0;
const int ACTION_MOVED = 1;
const int ACTION_DONE = 2;

const int CASTING_NORMAL = 0;
const int CASTING_SUMMON = 1;
const int CASTING_SPELL = 2;
const int CASTING_WAIT = 3;

/*
Removes the currently selected unit in a search from
the database. This is where we put all the special variables
that need to be updated whenever a unit is removed.
*/
void removeUnit() {
	yRemoveFromDatabase("allUnits");
	yRemoveUpdateVar("allUnits", "health");
	yRemoveUpdateVar("allUnits", "attack");
	yRemoveUpdateVar("allUnits", "speed");
	yRemoveUpdateVar("allUnits", "cardType");
	yRemoveUpdateVar("allUnits", "player");
	yRemoveUpdateVar("allUnits", "ready");
	yRemoveUpdateVar("allUnits", "keywords");
	yRemoveUpdateVar("allUnits", "tile");
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
				return(1*trQuestVarGet("zdataliteAllUnitspointer"));
			}
		}
	}
	return(-1);
}


/*
Given a card type, print information of the
of the selected unit.
*/
void displayCardKeywordsAndDescription(int cardType = 0) {
	trMessageSetText(trStringQuestVarGet("card"+cardType+"description"),-1);
	trSoundPlayFN("default","1",-1,trStringQuestVarGet("card"+cardType+"keywords"),"");
}

/*
Given the index of a unit in the allUnits database, highlight
the tiles that are reachable by that unit.
*/
void highlightReachable(int index = 0) {
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetUnitAtIndex("allUnits", index), true));
	int tile = findNearestTile("pos");
	findAvailableTiles(tile, yGetVarByIndex("allUnits", "speed", index), 
		"reachable", (yGetVarByIndex("allUnits", "ghost", index) == 1));
	for(x=yGetDatabaseCount("reachable"); >0) {
		tile = yDatabaseNext("reachable");
		highlightTile(tile, 3600);
	}
}

/*
Given the index of a unit in the allUnits database, find
enemy units that can be attacked by the unit and add them to
the database db.
*/
void findTargets(int index = 0, string db = "") {
	float dist = xsPow(yGetVarByIndex("allUnits", "range", index) * 6 + 3, 2);
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

/*
If target of the right-click was an enemy within range, start an attack
*/
bool attackUnitAtCursor(int p = 0) {
	int target = findNearestUnit("p"+p+"clickPos", 1);
	int a = trQuestVarGet("activeUnitIndex");

	if (target == -1) {
		return(false);
	}
	if (yGetVarByIndex("allUnits", "player", target) == 3 - p) {
		trQuestVarSet("targetUnit", yGetUnitAtIndex("allUnits", target));
		trVectorSetUnitPos("d1pos", "activeUnit");
		trVectorSetUnitPos("d2pos", "targetUnit");
		float range = xsPow(yGetVarByIndex("allUnits", "range", a) * 6 + 3, 2);
		if (zDistanceBetweenVectorsSquared("d1pos", "d2pos") < range) {
			// TODO: Guard activates here
			trQuestVarSet("counterAttack", 0);
			trQuestVarSet("attackDamage", yGetVarByIndex("allUnits", "attack", a));
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("activeUnit"), true);
			trSetUnitOrientation(zGetUnitVector("d1pos", "d2pos"), xsVectorSet(0,1,0), true);
			// TODO: choose correct animation based on card type
			trUnitOverrideAnimation(1,0,0,1,-1);

			// Counterattack
			range = xsPow(yGetVarByIndex("allUnits", "range", target) * 6 + 3, 2);
			if (zDistanceBetweenVectorsSquared("d1pos", "d2pos") < range) {
				trQuestVarSet("counterAttack", 1);
				trQuestVarSet("targetUnitIndex", target);
				trQuestVarSet("counterDamage", yGetVarByIndex("allUnits", "attack", target));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("targetUnit"), true);
				trSetUnitOrientation(zGetUnitVector("d2pos", "d1pos"), xsVectorSet(0,1,0), true);
				// TODO: choose correct animation based on card type
				trUnitOverrideAnimation(1,0,0,1,-1);
			}

			trQuestVarSet("p"+p+"casting", CASTING_WAIT);
			ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_DONE);

			xsEnableRule("attackComplete");
			return(true);
		}
	}

	return(false);
}

/*
Action that takes place with a generic left click  
*/
void selectUnitAtCursor(int p = 0) {
	int unit = 0;
	/*
	Deselect previously selected unit
	*/
	if (trQuestVarGet("activePlayer") == p &&
		trQuestVarGet("p"+p+"selected") > -1) {
		// Clear previously highlighted tiles.
		if (yGetDatabaseCount("reachable") > 0) {
			for(x=yGetDatabaseCount("reachable"); >0) {
				highlightTile(1*yDatabaseNext("reachable"), 0.1);
			}
			yClearDatabase("reachable");
		}
		/*
		Clear previously highlighted target enemies
		*/
		if (yGetDatabaseCount("targets") > 0) {
			yDatabaseSelectAll("targets");
			trUnitHighlight(0.1, false);
			yClearDatabase("targets");
		}
		if (yGetVarByIndex("allUnits", "action", 1*trQuestVarGet("p"+p+"selected")) == ACTION_MOVED) {
			ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("p"+p+"selected"), ACTION_DONE);
		}
	}
	unit = findNearestUnit("p"+p+"clickPos", 1);
	trQuestVarSet("p"+p+"selected", unit);
	if (unit > -1) {
		if (trCurrentPlayer() == p) {
			displayCardKeywordsAndDescription(yGetVarByIndex("allUnits", "cardType", unit));
		}
		/*
		If the player owns the selected unit and it is currently
		their turn, and also the unit hasn't moved yet,
		then highlight locations that it can move to.
		*/
		if (yGetVarByIndex("allUnits", "player", unit) == p &&
			yGetVarByIndex("allUnits", "action", unit) == ACTION_READY &&
			trQuestVarGet("activePlayer") == p) {
			trQuestVarSet("activeUnitIndex", trQuestVarGet("p"+p+"selected"));
			highlightReachable(unit);
			findTargets(unit, "targets");
			yDatabaseSelectAll("targets");
			trUnitHighlight(3600.0, false);
		}
	} else {
		// TODO: Check if player selected a unit in hand.
	}
}

/*
Action that takes place with a generic right click
*/
void unitWorkAtCursor(int p = 0) {
	int unit = trQuestVarGet("p"+p+"selected");
	trQuestVarSet("moveTile", -1);
	if (trQuestVarGet("activePlayer") == p) {
		if (trQuestVarGet("activeUnitIndex") > -1) {
			trQuestVarSet("activeUnit", yGetUnitAtIndex("allUnits", 1*trQuestVarGet("activeUnitIndex")));
			switch(yGetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex")))
			{
				case ACTION_READY:
				{
					/*
					First check if player wants unit to attack something in range 
					without moving it.
					 */
					if (attackUnitAtCursor(p) == false) {
						for (x=yGetDatabaseCount("reachable"); >0) {
							yDatabaseNext("reachable");
							if (zDistanceToVectorSquared("reachable", "p"+p+"clickPos") < 9) {
								trQuestVarCopy("moveTile", "reachable");
							}
						}
						if (trQuestVarGet("moveTile") == -1) {
							if (trCurrentPlayer() == p) {
								trSoundPlayFN("cantdothat.wav","1",-1,"","");
							}
						} else {
							// un-highlight all tiles
							for (x=yGetDatabaseCount("reachable"); >0) {
								highlightTile(1*yDatabaseNext("reachable", false), 0.1);
							}
							yClearDatabase("reachable");

							/* setting old tile to unoccupied */
							trVectorSetUnitPos("pos", "activeUnit");
							int tile = yGetVarByIndex("allUnits", "tile", 1*trQuestVarGet("activeUnitIndex"));
							zSetVarByIndex("tiles", "occupied", tile, xsMax(TILE_EMPTY, zGetVarByIndex("tiles", "terrain", tile)));

							trVectorSetUnitPos("moveDestination", "moveTile");
							trQuestVarSet("activeUnitID", kbGetBlockID(""+1*trQuestVarGet("activeUnit"), true));
							trUnitSelectClear();
							trUnitSelectByID(1*trQuestVarGet("activeUnitID"));
							trUnitMoveToVector("moveDestination");
							trQuestVarSet("p"+p+"casting", CASTING_WAIT);
							ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_MOVED);
							trQuestVarSet("moving", 0);
							xsEnableRule("moveComplete");
						}
					}
				}
				case ACTION_MOVED:
				{
					attackUnitAtCursor(p);
				}
			}
		}
	}
}

/*
p1casting determines the behavior of the left/right click based on the following:
	CASTING_NORMAL: normal behavior (i.e. unit click and move)
	CASTING_SUMMON: summoning a unit
	CASTING_SPELL: special rules when casting a spell
	CASTING_WAIT: nothing should happen. Waiting for animations to finish playing.

allUnits is a database that contains all units of both players

activePlayer is the player who's turn it currently is
*/
rule selectAndMove
highFrequency
active
{
	for (p=2; >0) {
		if (trQuestVarGet("p"+p+"click") > 0) {
			switch(1*trQuestVarGet("p"+p+"casting")) 
			{
				case CASTING_NORMAL:
				{
					switch(1*trQuestVarGet("p"+p+"click"))
					{
						case LEFT_CLICK:
						{
							selectUnitAtCursor(p);
						}
						case RIGHT_CLICK:
						{
							unitWorkAtCursor(p);
						}
					}
				}
				case CASTING_SUMMON:
				{

				}
				case CASTING_SPELL:
				{

				}
			}
			trQuestVarSet("p"+p+"click", 0);
		}
	}
}

/*
Called when a unit is moving to its destination tile. Only one unit can be
moving at a time.
*/
rule moveComplete
highFrequency
inactive
{
	// unit starts moving
	if (trQuestVarGet("moving") == 0) {
		if (kbUnitGetAnimationActionType(1*trQuestVarGet("activeUnitID")) == 11 ||
			kbUnitGetAnimationActionType(1*trQuestVarGet("activeUnitID")) == 10) {
			trQuestVarSet("moving", 1);
		}
	} else if (trQuestVarGet("moving") == 1) {
		if (kbUnitGetAnimationActionType(1*trQuestVarGet("activeUnitID")) == 9) {
			int p = trQuestVarGet("activePlayer");

			trVectorSetUnitPos("start", "activeUnit");
			trVectorSetUnitPos("end", "moveTile");

			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("moveTile"));
			trUnitConvert(p);
			trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
			trSetUnitOrientation(zGetUnitVector("start", "end"),xsVectorSet(0,1,0), true);

			int type = kbGetUnitBaseTypeID(1*trQuestVarGet("activeUnitID"));

			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("activeUnitID"));
			trMutateSelected(kbGetProtoUnitID("Dwarf"));
			trImmediateUnitGarrison(""+1*trQuestVarGet("moveTile"));
			trUnitChangeProtoUnit(kbGetProtoUnitName(type));

			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("moveTile"));
			trUnitConvert(0);
			trMutateSelected(kbGetProtoUnitID("Victory Marker"));

			findTargets(1*trQuestVarGet("activeUnitIndex"), "targets");

			if (yGetDatabaseCount("targets") == 0) {
				ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_DONE);
			} else {
				ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_MOVED);
				yDatabaseSelectAll("targets");
				trUnitHighlight(3600, false);
			}

			ySetVarByIndex("allUnits", "tile", 1*trQuestVarGet("activeUnitIndex"), trQuestVarGet("moveTile"));
			zSetVarByIndex("tiles", "occupied", 1*trQuestVarGet("moveTile"), TILE_OCCUPIED);

			trQuestVarSet("p"+p+"casting", CASTING_NORMAL);

			xsDisableRule("moveComplete");
		}
	}
}


/*
Called to complete a duel of fates
*/
rule attackComplete
highFrequency
inactive
{
	int attackerID = kbGetBlockID(""+1*trQuestVarGet("activeUnit"));
	int targetID = kbGetBlockID(""+1*trQuestVarGet("targetUnit"));
	if (kbUnitGetAnimationActionType(attackerID) == 9 &&
		kbUnitGetAnimationActionType(targetID) == 9) {
		int p = trQuestVarGet("activePlayer");
		trUnitSelectClear();
		trUnitSelectByID(targetID);
		trDamageUnit(yGetVarByIndex("allUnits", "attack", 1*trQuestVarGet("activeUnitIndex")));

		if (trQuestVarGet("counterAttack") == 1) {
			trUnitSelectClear();
			trUnitSelectByID(attackerID);
			trDamageUnit(yGetVarByIndex("allUnits", "attack", 1*trQuestVarGet("targetUnitIndex")));
		}

		
		trQuestVarSet("p"+p+"casting", CASTING_NORMAL);
		xsDisableRule("attackComplete");
		trDelayedRuleActivation("resolveDead");
	}
}

rule resolveDead
highFrequency
inactive
{
	/*
	Resolve dead units.
	*/
	int id = 0;
	int tile = 0;
	for (x=yGetDatabaseCount("allUnits"); >0) {
		id = yDatabaseNext("allUnits", true);
		if (id == -1 || trUnitAlive() == false) {
			tile = yGetVar("allUnits", "tile");
			zSetVarByIndex("tiles", "occupied", tile, xsMax(TILE_EMPTY, zGetVarByIndex("tiles", "terrain", tile)));
			removeUnit();
		}
	}
	xsDisableRule("resolveDead");
}
