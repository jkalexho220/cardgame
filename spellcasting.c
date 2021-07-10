
const int CAST_UNIT = 0;
const int CAST_TARGET = 1;
const int CAST_TILE = 2;
const int CAST_DIRECTION = 3;

const int CASTING_IN_PROGRESS = 0;
const int CASTING_DONE = 1;
const int CASTING_CANCEL = 2;


void castReset() {
	trQuestVarSet("castPush", 0);
	trQuestVarSet("castPop", -1);
}

/*
int p = the player of the unit being selected. 0 = any player
string qv = the name of the quest var to store the unit selected by the player

This function doesn't do anything on its own. It adds a selection request to the queue.
The spellcast_ set of triggers will process these requests one by one and store the results
in the quest vars.
*/
void castAddUnit(string qv = "", int p = 0) {
	int x = trQuestVarGet("castPush");
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);

	trQuestVarSet("cast"+x+"type", CAST_UNIT);
	trQuestVarSet("cast"+x+"player", p);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

/*
qv = name of the quest var to store the selected tile
ghost = true if ignore impassable terrain
*/
void castAddTile(string qv = "", bool ghost = false) {
	int x = trQuestVarGet("castPush");
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);

	trQuestVarSet("cast"+x+"type", CAST_TILE);
	trStringQuestVarSet("cast"+x+"qv", qv);
	if (ghost) {
		trQuestVarSet("cast"+x+"terrain", 0);
	} else {
		trQuestVarSet("cast"+x+"terrain", 1);
	}
}

/*
qv = name of the quest var to store the selected unit
attacker = name of quest var holding the index of the attacking unit. This will
only highlight targets that are within range of the attacker.
*/
void castAddTarget(string qv = "", string attacker = "") {
	int x = trQuestVarGet("castPush");
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);

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
	int x = trQuestVarGet("castPush");
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);

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
	xsEnableRule("spellcast_00_process");
}


rule spellcast_00_process
highFrequency
inactive
{
	if (trQuestVarGet("castPop") < trQuestVarGet("castPush")) {
		trQuestVarSet("castPop", trQuestVarGet("castPop") + 1);
		int x = trQuestVarGet("castPop");
		int p = 0;
		yClearDatabase("castTargets");
		switch(1*trQuestVarGet("cast"+x+"type"))
		{
			case CAST_UNIT:
			{
				p = trQuestVarGet("cast"+x+"player");
				trUnitSelectClear();
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if (yGetVar("allUnits", "player") == p) {
						trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
						trQuestVarSet("allUnitsIndex", yGetPointer("allUnits"));
						yAddToDatabase("castTargets", "allUnitsIndex");
					}
				}
				trUnitHighlight(999999, false);
			}
			case CAST_TILE:
			{
				for (z=zGetBankCount("tiles"); >0) {
					zBankNext("tiles");
					if (zGetVar("tiles", "terrain") * trQuestVarGet("cast"+x+"terrain") == 0) {
						yAddToDatabase("castTargets", "tiles");
						highlightTile(trQuestVarGet("tiles"), 999999);
					}
				}
			}
			case CAST_TARGET:
			{
				findTargets(1*trQuestVarGet(trStringQuestVarGet("cast"+x+"attacker")), "castTargets");
				trUnitSelectClear();
				yDatabaseSelectAll("castTargets");
				trUnitHighlight(999999, false);
			}
			case CAST_DIRECTION:
			{
				if (trQuestVarGet("cast"+x+"unit") == 1) {
					trQuestVarSet("cast"+x+"start", yGetVarByIndex("allUnits", "tile", 1*trQuestVarGet("start")));
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
	castTargets can be either a tile or the index of a unit in the allUnits database.
	The behavior of this function differs based on type.
	*/
	if (trQuestVarGet("cast"+x+"type") >= CAST_TILE) {
		for(z=yGetDatabaseCount("castTargets"); >0) {
			yDatabaseNext("castTargets");
			highlightTile(1*trQuestVarGet("castTargets"), 0.1);
		}
	} else {
		trUnitSelectClear();
		yDatabaseSelectAll("castTargets");
		trUnitHighlight(0.1, false);
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
				for(z=yGetDatabaseCount("castTargets"); >0) {
					yDatabaseNext("castTargets");
					/*
					castTargets can be either a tile or the index of a unit in the allUnits database. If it is 
					a unit index, we need the unit at that index.
					*/
					if (trQuestVarGet("cast"+x+"type") < CAST_TILE) {
						trQuestVarSet("castTargets", yGetUnitAtIndex("allUnits", 1*trQuestVarGet("castTargets")));
					}
					if (zDistanceToVectorSquared("castTargets", "p"+p+"clickPos") < 64) {
						trQuestVarCopy(trStringQuestVarGet("cast"+x+"qv"), "castTargets");
						selected = true;
						break;
					}
				}
				if (selected) {
					spellcastClearHighlights(x);
					trQuestVarSet("castDone", CASTING_DONE);
					xsDisableRule("spellcast_01_select");
				} else {
					if (trCurrentPlayer() == p) {
						trSoundPlayFN("cantdothat.wav","1",-1,"","");
					}
				}
			}
			case RIGHT_CLICK:
			{
				spellcastClearHighlights(x);
				castReset();
				trQuestVarSet("castDone", CASTING_CANCEL);
				xsDisableRule("spellcast_01_select");
			}
		}
		trQuestVarSet("p"+p+"click", 0);
	}
}
