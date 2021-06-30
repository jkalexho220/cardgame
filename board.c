void setupBoard() {
	unitTransform("Statue of Automaton Base", "Rocket");
	
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


	xsDisableRule("initializeBoard");
}