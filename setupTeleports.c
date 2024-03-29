
// P1 murmillos = 0 - 63
// P2 murmillos = 64 - 127
// Tile victory markers = 128 - 296 (169 tiles)
// Lines between tiles = 297 - 848 (552 lines)

// Number of tiles in a hexagonal grid of X*X*X dimensions:
// 3*(X^2-X) + 1
// Number of border lines in a hexagonal grid of X*X*X dimensions:
// (3*(X^2-X) + 1 + (2X-1))*3

rule setup
highFrequency
inactive
{
	// Teleport p1 murmillos to the corner
	trUnitSelectClear();
	for (x=63; >=0) {
		trUnitSelectByID(x);
	}
	trUnitTeleport(1,1,1);

	// Teleport p2 murmillos to the corner
	trUnitSelectClear();
	for(x=127; >=64) {
		trUnitSelectByID(x);
	}
	trUnitTeleport(1,1,1);

	// Map is 120x120
	trQuestVarSet("posx", 60);
	trQuestVarSet("posz", 60);
	float radius = trQuestVarGet("radius");

	// setup a step vector for each of the six directional angles
	float angle = 0.785398;
	for(x=6; >0) {
		trVectorSetFromAngle("step"+x, angle);
		trVectorScale("step"+x, radius);
		trQuestVarSet("angle"+x, angle);
		angle = fModulo(6.283185, angle + 1.047197);
	}

	zBankInit("tiles", 128, 169);
	zBankInit("borders", 297, 552);

	zSetVar("tiles", "posx", 60);
	zSetVar("tiles", "posz", 60);
	trQuestVarSet("x60z60", 1);

	trUnitSelectClear();
	trUnitSelectByID(1*trQuestVarGet("tiles"));
	trUnitTeleport(60,0,60);

	for (c=128; < 297) {
		// loop through the 6 directions
		for(x=6; >0) {
			// 0 means the tile hasn't been explored
			// 1 means the tile is in the fringe and doesn't needed to be added again
			// 2 means the tile is done and removed from the fringe
			trQuestVarSet("posx", zGetVarIndex("tiles", "posx", c) + 2.0*trQuestVarGet("step"+x+"x"));
			trQuestVarSet("posz", zGetVarIndex("tiles", "posz", c) + 2.0*trQuestVarGet("step"+x+"z"));
			if (trQuestVarGet("x"+1*xsRound(trQuestVarGet("posx"))+"z"+1*xsRound(trQuestVarGet("posz"))) == 0) {
				zBankNext("tiles", true);
				if (trQuestVarGet("tiles") > c) {
					trUnitTeleport(trQuestVarGet("posx"),0,trQuestVarGet("posz"));
					zSetVar("tiles", "posx", trQuestVarGet("posx"));
					zSetVar("tiles", "posz", trQuestVarGet("posz"));
				}
				trQuestVarSet("x"+1*xsRound(trQuestVarGet("posx"))+"z"+1*xsRound(trQuestVarGet("posz")),1);
			}

			// Draw border line if it isn't there
			if (trQuestVarGet("x"+1*xsRound(trQuestVarGet("posx"))+"z"+1*xsRound(trQuestVarGet("posz"))) < 2) {
				// teleport border line
				trQuestVarSet("borderx", zGetVarIndex("tiles", "posx", c) + trQuestVarGet("step"+x+"x"));
				trQuestVarSet("borderz", zGetVarIndex("tiles", "posz", c) + trQuestVarGet("step"+x+"z"));
				zBankNext("borders", true);
				trUnitTeleport(trQuestVarGet("borderx"),0,trQuestVarGet("borderz"));
				zUnitHeading(trQuestVarGet("angle"+x));
				// trMutateSelected(kbGetProtoUnitID("undermine ground decal long"));
				trMutateSelected(kbGetProtoUnitID("Statue of Automaton Base"));
				trSetSelectedScale(radius + 0.1, 0.1, 0.2);
			}
		}
		// set the position as explored
		trQuestVarSet("posx", zGetVarIndex("tiles", "posx", c));
		trQuestVarSet("posz", zGetVarIndex("tiles", "posz", c));
		trQuestVarSet("x"+1*xsRound(trQuestVarGet("posx"))+"z"+1*xsRound(trQuestVarGet("posz")),2);
	}

	xsDisableRule("setup");
}