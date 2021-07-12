
const int TILE_EMPTY = 0;
const int TILE_IMPASSABLE = 1;
const int TILE_OCCUPIED = 2;

int deployAtTile(int p = 0, string proto = "", int tile = 0) {
	int next = trGetNextUnitScenarioNameNumber();
	trArmyDispatch("1,10","Dwarf",1,119,0,1,0,true);

	trUnitSelectClear();
	trUnitSelectByID(tile);
	trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));

	trUnitSelectClear();
	trUnitSelect(""+next, true);
	trUnitConvert(0);
	trImmediateUnitGarrison(""+tile);
	trUnitConvert(p);
	trUnitChangeProtoUnit(proto);

	trUnitSelectClear();
	trUnitSelectByID(tile);
	trMutateSelected(kbGetProtoUnitID("Victory Marker"));

	return(next);
}

void tileGuard(int tile = 0, bool on = true) {
	trUnitSelectClear();
	for(x=zGetVarByIndex("tiles", "borderCount", tile) - 1; >=0) {
		trUnitSelectByID(1*zGetVarByIndex("tiles", "border"+x, tile));
	}
	if (on) {
		trSetSelectedScale(3.1, 0.1, 0.6);
	} else {
		trSetSelectedScale(3.1, 0.1, 0.2);
	}
}


void setupBoard() {
	unitTransform("Statue of Automaton Base", "Victory Marker");
	
	trQuestVarSet("borders", trQuestVarGet("zbordersend") - 2);
	bool allborders = false;
	int count = 0;
	int statue = kbGetProtoUnitID("Statue of Automaton Base");
	for (x=zGetBankCount("tiles"); >0) {
		trVectorSetUnitPos("currentPos", "tiles", false);
		/*
		Take advantage of the fact that the borders were added in ascending
		order when the board was originally created.
		*/
		if (allborders == false) {
			for(y=6; >0) {
				zBankNext("borders");
				yAddToDatabase("borderSearch", "borders");
				if (trQuestVarGet("borders") == trQuestVarGet("zbordersend") - 2) {
					allborders = true;
					break;
				}
			}
		}
		

		// Assigning neighbors to the tile
		for (y=yGetDatabaseCount("neighbors"); >0) {
			yDatabaseNext("neighbors");
			if (zGetVarByIndex("tiles", "neighborCount", 1*trQuestVarGet("neighbors")) == 6) {
				yRemoveFromDatabase("neighbors");
			} else {
				// Tiles have radius 3 and are 6 units apart.
				// Add this tile to the neighborlist of adjacent tiles and add adjacent neighbors to this tile's neighborlist
				if (zDistanceToVectorSquared("neighbors", "currentPos") < 40) {
					count = zGetVarByIndex("tiles", "neighborCount", 1*trQuestVarGet("neighbors"));
					zSetVarByIndex("tiles", "neighbor"+count, 1*trQuestVarGet("neighbors"), trQuestVarGet("tiles"));
					zSetVarByIndex("tiles", "neighborCount", 1*trQuestVarGet("neighbors"), count + 1);

					count = zGetVar("tiles", "neighborCount");
					zSetVar("tiles", "neighbor"+count, trQuestVarGet("neighbors"));
					zSetVar("tiles", "neighborCount", count + 1);
					if (count == 6) {
						break;
					}
				}
			}
		}
		yAddToDatabase("neighbors", "tiles");

		// Assigning borders to the tile
		for (y=yGetDatabaseCount("borderSearch"); >0) {
			yDatabaseNext("borderSearch");
			if (yGetVar("borderSearch", "count") == 2) {
				yRemoveFromDatabase("borderSearch");
				yRemoveUpdateVar("borderSearch", "count");
			} else {
				if (zDistanceToVectorSquared("borderSearch", "currentPos") < 10) {
					count = zGetVar("tiles", "borderCount");
					zSetVar("tiles", "border"+count, trQuestVarGet("borderSearch"));
					zSetVar("tiles", "borderCount", count + 1);
					ySetVar("borderSearch", "count", yGetVar("borderSearch", "count") + 1);
					trUnitSelectClear();
					trUnitSelectByID(1*trQuestVarGet("borderSearch"));
					trMutateSelected(statue);
					if (count == 6) {
						break;
					}
				}
			}
		}
		zBankNext("tiles");
	}
}

/*
Given a QV vector name, find the ID of the closest space to it.
Returns -1 if none found.
*/
int findNearestTile(string v = "") {
	for (x=zGetBankCount("tiles"); >0) {
		zBankNext("tiles");
		if (zDistanceToVectorSquared("tiles", v) < 9) {
			return(1*trQuestVarGet("tiles"));
		}
	}
	return(-1);
}

/*
Finds all tiles that can be reached by the tile indicated by 'id'.
Adds all of the found tiles to the yDatabase 'db'.
If 'ghost' is set to true, uses ghost pathfinding rules (ignore occupied and impassable terrain)
*/
void findAvailableTiles(int id = 0, int distance = 1, string db = "", bool ghost = false) {
	for (x=zGetBankCount("tiles"); >0) {
		zBankNext("tiles");
		zSetVar("tiles", "searched", 0);
	}
	int push = 0;
	int pop = -1;
	int tile = 0;
	int neighbor = 0;
	trQuestVarSet("search"+push+"tile", id);
	trQuestVarSet("search"+push+"distance", distance);
	while (pop < push) {
		pop = pop + 1;
		tile = trQuestVarGet("search"+pop+"tile");
		// Add it to the db if it is not occupied
		if (zGetVarByIndex("tiles", "occupied", tile) < TILE_OCCUPIED) {
			yAddToDatabase(db, "search"+pop+"tile");
		}
		// Search neighbors
		if (trQuestVarGet("search"+pop+"distance") > 0) {
			for (x=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
				neighbor = zGetVarByIndex("tiles", "neighbor"+x, tile);
				if (zGetVarByIndex("tiles", "searched", neighbor) == 0) {
					zSetVarByIndex("tiles", "searched", neighbor, 1);
					// Add to fringe if it can be moved through.
					if (zGetVarByIndex("tiles", "occupied", neighbor) == TILE_EMPTY || ghost) {
						push = push + 1;
						trQuestVarSet("search"+push+"tile", neighbor);
						trQuestVarSet("search"+push+"distance", trQuestVarGet("search"+pop+"distance") - 1);
					}
				}
			}
		}
	}
}

void highlightTile(int tile = 0, float duration = 0.1) {
	trUnitSelectClear();
	for (x=0; < zGetVarByIndex("tiles", "borderCount", tile)) {
		trUnitSelectByID(zGetVarByIndex("tiles", "border"+x, tile));
	}
	trUnitHighlight(duration, false);
}

rule initializeBoard
highFrequency
active
runImmediately
{
	/*
	Tile index increases outwards from the center.
	To vary the size of the map, just vary the 
	size of the array.
	*/
	if (trQuestVarGet("dimension") <= 1) {
		trQuestVarSetFromRand("dimension", 6, 8, true);
	}
	int tiles = 1 + 3 * (xsPow(trQuestVarGet("dimension"), 2) - trQuestVarGet("dimension"));
	// Number of tiles in a hexagonal grid of X*X*X dimensions:
	// 3*(X^2-X) + 1
	zBankInit("tiles", 128, tiles);
	zBankInit("borders", 297, 552);

	setupBoard();
	trQuestVarSet("p1startPosx", 60.0 - 4.24 * (trQuestVarGet("dimension") - 1));
	trQuestVarCopy("p1startPosz", "p1startposx");
	// Since p2 goes second, they start one tile closer to the center
	trQuestVarSet("p2startPosx", 60.0 + 4.24 * (trQuestVarGet("dimension") - 2));
	trQuestVarCopy("p2startposz", "p2startposx");

	trQuestVarSet("p1startTile", findNearestTile("p1StartPos"));
	trQuestVarSet("p2startTile", findNearestTile("p2StartPos"));

	trModifyProtounit("Revealer", 0, 2, 6 * trQuestVarGet("dimension") - 6);
	trModifyProtounit("Revealer to Player", 1, 2, 6);
	trModifyProtounit("Revealer to Player", 2, 2, 6);

	xsDisableRule("initializeBoard");
}