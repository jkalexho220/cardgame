
const int ACTION_READY = 0;
const int ACTION_MOVED = 1;
const int ACTION_DONE = 2;

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
	yRemoveUpdateVar("allUnits", "ghost");
	yRemoveUpdateVar("allUnits", "cardType");
	yRemoveUpdateVar("allUnits", "player");
	yRemoveUpdateVar("allUnits", "ready");
}


/*
Given a QV vector name, find the name of the closest unit to it. 
Returns the index of the unit in the 'allUnits' array. This index can 
be used in yGetVarByIndex and ySetVarByIndex.
Returns -1 if none found.
BEWARE: if this unit is removed from the database, the pointer will no longer
point to it!
*/
int findNearestUnit(string qv = "") {
	int id = 0;
	for (x=yGetDatabaseCount("allUnits"); >0) {
		id = yDatabaseNext("allUnits", true);
		if (id == -1) {
			removeUnit();
		} else {
			if (zDistanceToVectorSquared("allUnits", qv) < 1) {
				return(1*trQuestVarGet("zdataliteAllUnitspointer"));
			}
		}
	}
	return(-1);
}


/*
Given an index for the allUnits database, print the information
of the selected unit.
*/
void displayUnitKeywordsAndDescription(int index = 0) {
	int cardType = yGetVarByIndex("allUnits", "cardType", index);
	trMessageSetText(trStringQuestVarGet("card"+cardType+"description"),-1);
	trSoundPlayFN("default","1",-1,trStringQuestVarGet("card"+cardType+"keywords"),"");
}

void highlightReachable(int index = 0) {
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetUnitAtIndex("allUnits", index), true));
	int tile = findNearestTile("pos");
	findAvailableTiles(tile, yGetVarByIndex("allUnits", "speed", index), 
		"reachable", (yGetVarByIndex("allUnits", "ghost", index) == 1));
	yDatabaseSelectAll("reachable");
	trUnitHighlight(90, false);
}

/*
activePlayer = the player who's turn it is.
*/
rule selectAndMove
highFrequency
active
{
	int unit = 0;
	for (p=2; >0) {
		if (trQuestVarGet("p"+p+"click") == 1) {
			/*
			If previously selected unit moved but didn't attack, set
			it as done because we deselect it.
			*/
			if (trQuestVarGet("activePlayer") == p &&
				trQuestVarGet("p"+p+"selected") > -1) {
				// Clear previously highlighted tiles.
				if (yGetDatabaseCount("reachable") > 0) {
					yDatabaseSelectAll("reachable");
					trUnitHighlight(0.1, false);
					yClearDatabase("reachable");
				}
				if (yGetVarByIndex("allUnits", "action", 1*trQuestVarGet("p"+p+"selected")) == ACTION_MOVED) {
					ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("p"+p+"selected"), ACTION_DONE);
				}
			}
			unit = findNearestUnit("p"+p+"clickPos");
			trQuestVarSet("p"+p+"selected", unit);
			if (unit > -1) {
				if (trCurrentPlayer() == p) {
					displayUnitKeywordsAndDescription(unit);
				}
				/*
				If the player owns the selected unit and it is currently
				their turn, and also the unit hasn't moved yet,
				then highlight locations that it can move to.
				*/
				if (yGetVarByIndex("allUnits", "player", unit) == p &&
					yGetVarByIndex("allUnits", "action", unit) == ACTION_READY &&
					trQuestVarGet("activePlayer") == p) {
					highlightReachable(unit);
				}
			}
		} else if (trQuestVarGet("p"+p+"click") == 2) {

		}
	}
}