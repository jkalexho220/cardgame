
const int ACTION_READY = 0;
const int ACTION_MOVED = 1;
const int ACTION_DONE = 2;

const int CASTING_NORMAL = 0;
const int CASTING_SUMMON = 1;
const int CASTING_SPELL = 2;

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
	yDatabaseSelectAll("reachable");
	trUnitHighlight(90, false);
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
			yDatabaseSelectAll("reachable");
			trUnitHighlight(0.1, false);
			yClearDatabase("reachable");
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
			highlightReachable(unit);
		}
	} else {
		// Check if player selected a unit in hand.
	}
}

/*
Action that takes place with a generic right click
*/
void unitWorkAtCursor(int p = 0) {
	int unit = trQuestVarGet("p"+p+"selected");
	if (trQuestVarGet("activePlayer") == p) {
		if (trQuestVarGet("p"+p+"selected") > -1) {
			switch(yGetVarByIndex("allUnits", "action", 1*trQuestVarGet("p"+p+"selected")))
			{
				case ACTION_READY:
				{

				}
				case ACTION_MOVED:
				{

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

allUnits is a database that contains all units of both players

activePlayer is the player who's turn it currently is
*/
rule selectAndMove
highFrequency
active
{
	int unit = 0;
	for (p=2; >0) {
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
	}
}
