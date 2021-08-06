const int TERRAIN_GRASSLAND = 0;
const int TERRAIN_DESERT = 1;
const int TERRAIN_SNOW = 2;

const int T_GRASS_25 = 2;
const int T_GRASS_50 = 3;
const int T_GRASS_75 = 4;
const int T_GREEK_ROAD = 65;
const int T_GREEK_CLIFF_B = 5;
const int T_FOREST_PINE = 87;

const int T_SAND_D = 37;
const int T_FOREST_PALM = 86;

const int T_SNOW_A = 41;
const int T_FOREST_SNOW = 88;

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
		if (zGetVarByIndex("tiles", "occupant", tile) == 0) {
			yAddToDatabase(db, "search"+pop+"tile");
		}
		// Search neighbors
		if (trQuestVarGet("search"+pop+"distance") > 0) {
			for (x=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
				neighbor = zGetVarByIndex("tiles", "neighbor"+x, tile);
				if (zGetVarByIndex("tiles", "searched", neighbor) == 0) {
					zSetVarByIndex("tiles", "searched", neighbor, 1);
					// Add to fringe if it can be moved through.
					if ((zGetVarByIndex("tiles", "occupant", neighbor) + zGetVarByIndex("tiles", "terrain", neighbor) == 0) || ghost) {
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

void paintTile(int tile = 0, int type = 0, int subType = 0) {
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+tile));
	vectorToGrid("pos", "square");
	int x = trQuestVarGet("squarex");
	int z = trQuestVarGet("squarez");
	trPaintTerrain(x-1, z-1, x+1, z+1, type, subType, false);
}

void chooseTerrainTheme(int terrain = 0) {
	int pop = 0;
	int push = 0;
	int tile = 0;
	int val = 0;
	int neighbor = 0;
	switch(terrain)
	{
		case TERRAIN_GRASSLAND:
		{
			trStringQuestVarSet("treeType", "Tundra Tree");
			trQuestVarSet("treeTile", T_FOREST_PINE);
			for(i=zGetBankCount("tiles"); >0) {
				zBankNext("tiles");
				zSetVar("tiles", "searched", 0);
			}
			for(i=trQuestVarGet("dimension"); >0) {
				trQuestVarSetFromRand("tile", trQuestVarGet("ztilesstart"), trQuestVarGet("ztilesend"), true);
				zSetVarByIndex("tiles", "searched", 1*trQuestVarGet("tile"), 1);
				pop = 0;
				push = 1;
				trQuestVarCopy("search1", "tile");
				trQuestVarSet("search1val", 2);
				while(push > pop) {
					pop = pop + 1;
					tile = trQuestVarGet("search"+pop);
					paintTile(tile, 0, T_GRASS_25 + trQuestVarGet("search"+pop+"val"));
					trQuestVarSetFromRand("rand", 0, 1, true);
					trQuestVarSet("search"+pop+"val", trQuestVarGet("search"+pop+"val") - trQuestVarGet("rand"));
					
					if (trQuestVarGet("search"+pop+"val") >= 0) {
						for(j=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
							neighbor = zGetVarByIndex("tiles", "neighbor"+j, tile);
							if (zGetVarByIndex("tiles", "searched", neighbor) == 0) {
								zSetVarByIndex("tiles", "searched", neighbor, 1);
								push = push + 1;
								trQuestVarSet("search"+push, neighbor);
								trQuestVarCopy("search"+push+"val", "search"+pop+"val");
							}
						}
					}
				}
			}
		}
		case TERRAIN_DESERT:
		{
			trStringQuestVarSet("treeType", "Palm");
			trQuestVarSet("treeTile", T_FOREST_PALM);
			trPaintTerrain(0, 0, 59, 59, 0, T_SAND_D, false);
			/*
			TODO: Terrain mixing for sand
			*/
		}
		case TERRAIN_SNOW:
		{
			trStringQuestVarSet("treeType", "Pine Snow");
			trQuestVarSet("treeTile", T_FOREST_SNOW);
			trPaintTerrain(0, 0, 59, 59, 0, T_SNOW_A, false);
			/*
			TODO: Terrain mixing for snow
			*/
		}
	}
}

void paintTreesOnTile(int tile = 0) {
	int x = 0;
	int z = 0;
	zSetVarByIndex("tiles", "terrain", tile, TILE_IMPASSABLE);
	paintTile(tile, 0, 1*trQuestVarGet("treeTile"));
	for(i=4; >0) {
		trVectorQuestVarSet("pos", kbGetBlockPosition(""+tile));
		trQuestVarSetFromRand("modx", -2, 2, true);
		trQuestVarSetFromRand("modz", -2, 2, true);
		trQuestVarSetFromRand("heading",0, 360, true);
		x = trQuestVarGet("posx") + trQuestVarGet("modx");
		z = trQuestVarGet("posz") + trQuestVarGet("modz");
		trArmyDispatch("1,10",trStringQuestVarGet("treeType"),1,x,0,z,trQuestVarGet("heading"), true);
	}
}

void setupImpassableTerrain() {
	int tileStart = 1*trQuestVarGet("ztilesstart");
	int tile = 0;
	int layerSize = 1;
	for(dist=2; <= trQuestVarGet("dimension")) {
		tileStart = tileStart + layerSize;
		layerSize = layerSize + 6;
		/*
		Skip second-to-last layer to prevent impossible movement
		*/
		if (dist == trQuestVarGet("dimension") - 1) {
			continue;
		} else {
			trQuestVarSetFromRand("count", 0, dist, true);
			trQuestVarSet("remaining", layerSize / 2);
			tile = tileStart;
			while (trQuestVarGet("count") > 0) {
				trQuestVarSetFromRand("step", 1, trQuestVarGet("remaining") - trQuestVarGet("count"), true);
				trQuestVarSet("remaining", trQuestVarGet("remaining") - trQuestVarGet("step"));
				tile = tile + trQuestVarGet("step");
				paintTreesOnTile(tile);
				trVectorQuestVarSet("pos", kbGetBlockPosition(""+tile));
				trQuestVarSet("posx", 120 - trQuestVarGet("posx"));
				trQuestVarSet("posz", 120 - trQuestVarGet("posz"));
				paintTreesOnTile(1*findNearestTile("pos"));
				trQuestVarSet("count", trQuestVarGet("count") - 1);
			}
		}
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

	chooseTerrainTheme(TERRAIN_GRASSLAND);
	setupImpassableTerrain();

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