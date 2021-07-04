
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
This is called only after a yDatabaseNext("allUnits").
*/
void removeUnit(string db = "allUnits") {
	yRemoveFromDatabase(db);
	yRemoveUpdateString(db, "name");
	yRemoveUpdateString(db, "ability");
	yRemoveUpdateVar(db, "health");
	yRemoveUpdateVar(db, "attack");
	yRemoveUpdateVar(db, "speed");
	yRemoveUpdateVar(db, "proto");
	// Since cardType = protounit, we don't need this variable
	// yRemoveUpdateVar(db, "cardType");
	yRemoveUpdateVar(db, "player");
	yRemoveUpdateVar(db, "ready");
	yRemoveUpdateVar(db, "keywords");
	yRemoveUpdateVar(db, "tile");
}

/*
Transfers the unit at the current pointer in the 'from' database
to the 'to' database.
*/
void transferUnit(string to = "", string from = "") {
	yAddToDatabase(to, from);
	yTransferUpdateString(to, from, "name");
	yTransferUpdateString(to, from, "ability");
	yTransferUpdateVar(to, from, "health");
	yTransferUpdateVar(to, from, "attack");
	yTransferUpdateVar(to, from, "speed");
	yTransferUpdateVar(to, from, "proto");
	yTransferUpdateVar(to, from, "player");
	yTransferUpdateVar(to, from, "ready");
	yTransferUpdateVar(to, from, "keywords");
	yTransferUpdateVar(to, from, "tile");
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
	int target = findNearestUnit("p"+p+"clickPos", 4);
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
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("targetUnit"), true);
				trSetUnitOrientation(zGetUnitVector("d2pos", "d1pos"), xsVectorSet(0,1,0), true);
				// TODO: choose correct animation based on card type
				trUnitOverrideAnimation(1,0,0,1,-1);
			}

			
			ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_DONE);

			xsEnableRule("gameplay_05_attackComplete");
			return(true);
		}
	}

	return(false);
}


/*
Game is waiting for the active player to select a unit. This trigger
does not check what the inactive player is doing
*/
rule gameplay_01_select
highFrequency
inactive
{
	if (trQuestVarGet("turnEnd") == 1) {
		xsDisableRule("gameplay_01_select");
	} else {
		int p = trQuestVarGet("activePlayer");
		if (trQuestVarGet("p"+p+"click") == LEFT_CLICK) {
			int unit = findNearestUnit("p"+p+"clickPos", 4);
			trQuestVarSet("activeUnitIndex", unit);
			if (unit > -1) {
				/* this might be put somewhere else idk */
				if (trCurrentPlayer() == p) {
					displayCardKeywordsAndDescription("allUnits", unit);
				}
				/*
				If the player owns the selected unit and and the unit hasn't moved yet,
				then highlight locations that it can move to and proceed to gameplay_02_work.
				*/
				if (yGetVarByIndex("allUnits", "player", unit) == p &&
					yGetVarByIndex("allUnits", "action", unit) == ACTION_READY) {
					highlightReachable(unit);

					// highlight attackable enemies within range
					findTargets(unit, "targets");
					yDatabaseSelectAll("targets");
					trUnitHighlight(3600.0, false);

					xsDisableRule("gameplay_01_select");
					xsEnableRule("gameplay_02_work");

				}
			} else {
				// Check if player selected a card in hand.
				unit = -1;
				for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					if (zDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos") < 4) {
						unit = yGetPointer("p"+p+"hand");
						break;
					}
				}
				if (unit > -1) {
					trVectorSetUnitPos("pos", "p"+p+"commander");
					int tile = findNearestTile("pos");
					findAvailableTiles(tile, 1, "summonLocations");
					if (trQuestVarGet("p"+p+"mana") > yGetVarByIndex("p"+p+"hand", "cost", unit)) {
						for (x=yGetDatabaseCount("summonLocations"); >0) {
							tile = yDatabaseNext("summonLocations");
							if (trCurrentPlayer() == p) {
								highlightTile(tile, 3600);
							}
						}

						trQuestVarSet("summonUnitIndex", unit);
						xsEnableRule("gameplay_10_summon");
						xsDisableRule("gameplay_01_select");
					}
					
					if (trCurrentPlayer() == p) {
						displayCardKeywordsAndDescription("p"+p+"hand", unit);
					}
				}
			}

			trQuestVarSet("p"+p+"click", 0);
		}
	}
}

/*
Game is waiting for the active player to issue a right click, 
which can be a move or an attack command. A left click will cancel
and send us back to gameplay_01_select.
Again, we ignore whatever the inactive player is doing.
*/
rule gameplay_02_work
highFrequency
inactive
{
	if (trQuestVarGet("turnEnd") == 1) {
		xsDisableRule("gameplay_02_work");
		if (yGetDatabaseCount("reachable") > 0) {
			for(x=yGetDatabaseCount("reachable"); >0) {
				highlightTile(1*yDatabaseNext("reachable"), 0.1);
			}
			yClearDatabase("reachable");

			if (yGetDatabaseCount("targets") > 0) {
				yDatabaseSelectAll("targets");
				trUnitHighlight(0.1, false);
				yClearDatabase("targets");
			}
		}
	} else {
		int p = trQuestVarGet("activePlayer");
		switch(1*trQuestVarGet("p"+p+"click"))
		{
			case LEFT_CLICK:
			{
				/*
				Deselect previously selected unit
				*/
				if (trQuestVarGet("activeUnitIndex") > -1) {
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
					if (yGetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex")) == ACTION_MOVED) {
						ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_DONE);
					}

					xsDisableRule("gameplay_02_work");
					xsEnableRule("gameplay_01_select");

					/* 
					We DON'T set click back to zero in case the user selected another unit 
					with this click.
					*/
					// trQuestVarSet("p"+p+"click", 0);
				}
			}
			case RIGHT_CLICK:
			{
				int unit = trQuestVarGet("activeUnitIndex");
				trQuestVarSet("activeUnit", yGetUnitAtIndex("allUnits", 1*trQuestVarGet("activeUnitIndex")));
				/*
				First check if player wants unit to attack something in range 
				without moving it.
				 */
				if (attackUnitAtCursor(p) == false) {
					trQuestVarSet("moveTile", -1);
					for (x=yGetDatabaseCount("reachable"); >0) {
						yDatabaseNext("reachable");
						if (zDistanceToVectorSquared("reachable", "p"+p+"clickPos") < 9) {
							trQuestVarCopy("moveTile", "reachable");
							break;
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

						/*
						Clear previously highlighted target enemies
						*/
						if (yGetDatabaseCount("targets") > 0) {
							yDatabaseSelectAll("targets");
							trUnitHighlight(0.1, false);
							yClearDatabase("targets");
						}

						/* setting old tile to unoccupied */
						int tile = yGetVarByIndex("allUnits", "tile", 1*trQuestVarGet("activeUnitIndex"));
						zSetVarByIndex("tiles", "occupied", tile, xsMax(TILE_EMPTY, zGetVarByIndex("tiles", "terrain", tile)));

						trVectorSetUnitPos("moveDestination", "moveTile");
						trQuestVarSet("activeUnitID", kbGetBlockID(""+1*trQuestVarGet("activeUnit"), true));
						trUnitSelectClear();
						trUnitSelectByID(1*trQuestVarGet("activeUnitID"));
						trUnitMoveToVector("moveDestination");
						
						ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_MOVED);
						trQuestVarSet("moving", 0);
						xsEnableRule("gameplay_03_moveComplete");
						xsDisableRule("gameplay_02_work");
					}
				} else {
					xsDisableRule("gameplay_02_work");
				}
				trQuestVarSet("p"+p+"click", 0);
			}
		}
	}
}

/*
Called when a unit is moving to its destination tile. Only one unit can be
moving at a time.
*/
rule gameplay_03_moveComplete
highFrequency
inactive
{
	// unit starts moving
	if (trQuestVarGet("moving") == 0) {
		if (kbUnitGetAnimationActionType(1*trQuestVarGet("activeUnitID")) == 11 ||
			kbUnitGetAnimationActionType(1*trQuestVarGet("activeUnitID")) == 10) {
			trQuestVarSet("moving", 1);
		}
	} else if (trQuestVarGet("moving") == 1 || trQuestVarGet("turnEnd") == 1) {
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
			trUnitChangeProtoUnit("Dwarf");
			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("activeUnitID"));
			trMutateSelected(type);

			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("moveTile"));
			trUnitConvert(0);
			trMutateSelected(kbGetProtoUnitID("Victory Marker"));

			if (trQuestVarGet("turnEnd") == 0) {
				findTargets(1*trQuestVarGet("activeUnitIndex"), "targets");
				/*
				If no targets found, we go back to gameplay_01_select
				Otherwise, we go to gameplay_04_attack
				*/
				if (yGetDatabaseCount("targets") == 0) {
					xsEnableRule("gameplay_01_select");
					ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_DONE);
				} else {
					xsEnableRule("gameplay_04_attack");
					ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_MOVED);
					yDatabaseSelectAll("targets");
					trUnitHighlight(3600, false);
				}
			}
			

			ySetVarByIndex("allUnits", "tile", 1*trQuestVarGet("activeUnitIndex"), trQuestVarGet("moveTile"));
			zSetVarByIndex("tiles", "occupied", 1*trQuestVarGet("moveTile"), TILE_OCCUPIED);


			xsDisableRule("gameplay_03_moveComplete");
		}
	}
}

/*
Wait for the user to issue an attack command.
*/
rule gameplay_04_attack
highFrequency
inactive
{
	if (trQuestVarGet("turnEnd") == 1) {
		xsDisableRule("gameplay_04_attack");
		if (yGetDatabaseCount("targets") > 0) {
			yDatabaseSelectAll("targets");
			trUnitHighlight(0.1, false);
			yClearDatabase("targets");
		}
	} else {
		int p = trQuestVarGet("activePlayer");
		switch(1*trQuestVarGet("p"+p+"click"))
		{
			case LEFT_CLICK:
			{
				ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_DONE);
				/*
				Clear previously highlighted target enemies
				*/
				if (yGetDatabaseCount("targets") > 0) {
					yDatabaseSelectAll("targets");
					trUnitHighlight(0.1, false);
					yClearDatabase("targets");
				}
				xsDisableRule("gameplay_04_attack");
				xsEnableRule("gameplay_01_select");
			}
			case RIGHT_CLICK:
			{
				if (attackUnitAtCursor(p)) {
					/*
					Clear previously highlighted target enemies
					*/
					if (yGetDatabaseCount("targets") > 0) {
						yDatabaseSelectAll("targets");
						trUnitHighlight(0.1, false);
						yClearDatabase("targets");
					}
					xsDisableRule("gameplay_04_attack");
				}
			}
		}
	}
	
	trQuestVarSet("p"+p+"click", 0);
}


/*
Called to complete a duel of fates
*/
rule gameplay_05_attackComplete
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

		if (trQuestVarGet("turnEnd") == 0) {
			xsEnableRule("gameplay_01_select");
		}
		xsDisableRule("gameplay_05_attackComplete");
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


rule gameplay_10_summon
highFrequency
inactive
{
	int p = trQuestVarGet("activePlayer");
	if (trQuestVarGet("turnEnd") == 1) {
		for (x=yGetDatabaseCount("summonLocations"); >0) {
			yDatabaseNext("summonLocations");
			if (trCurrentPlayer() == p) {
				highlightTile(1*trQuestVarGet("summonLocations"), 0.1);
			}
		}
		yClearDatabase("summonLocations");
		xsDisableRule("gameplay_10_summon");
	} else {
		switch(1*trQuestVarGet("p"+p+"click"))
		{
			case LEFT_CLICK:
			{
				int tile = -1;
				for(x=yGetDatabaseCount("summonLocations"); >0) {
					yDatabaseNext("summonLocations");
					if (zDistanceToVectorSquared("summonLocations", "p"+p+"clickPos") < 9) {
						tile = trQuestVarGet("summonLocations");
						break;
					}
				}
				// Invalid location
				if (tile < 0) {
					for (x=yGetDatabaseCount("summonLocations"); >0) {
						yDatabaseNext("summonLocations");
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("summonLocations"), 0.1);
						}
					}
					yClearDatabase("summonLocations");
					xsEnableRule("gameplay_01_select");
					xsDisableRule("gameplay_10_summon");
					// We don't set the player click to 0 in case this click was used to select another unit in hand.
				} else {
					int unit = yGetUnitAtIndex("p"+p+"hand", 1*trQuestVarGet("summonUnitIndex"));
					trUnitSelectClear();
					trUnitSelectByID(tile);
					trUnitConvert(p);
					trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));

					trUnitSelectClear();
					trUnitSelect(""+unit, true);
					trMutateSelected(kbGetProtoUnitID("Dwarf"));
					trImmediateUnitGarrison(""+tile);
					trUnitChangeProtoUnit(kbGetProtoUnitName(1*yGetVarByIndex("p"+p+"hand", "proto", 1*trQuestVarGet("summonUnitIndex"))));

					trUnitSelectClear();
					trUnitSelectByID(tile);
					trUnitConvert(0);
					trMutateSelected(kbGetProtoUnitID("Victory Marker"));

					ySetPointer("p"+p+"hand", 1*trQuestVarGet("summonUnitIndex"));

					trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") - yGetVar("p"+p+"hand", "cost"));
					trSoundPlayFN("mythcreate.wav","1",-1,"","");

					transferUnit("allUnits", "p"+p+"hand");
					yAddUpdateVar("allUnits", "tile", tile);
					if (HasCharge(1*yGetVar("p"+p+"hand", "keywords")) == true) {
						yAddUpdateVar("allUnits", "action", ACTION_READY);
					} else {
						yAddUpdateVar("allUnits", "action", ACTION_DONE);
					}
					removeUnit("p"+p+"hand");
					yRemoveUpdateVar("p"+p+"hand", "spell");
					yRemoveUpdateVar("p"+p+"hand", "pos");

					zSetVarByIndex("tiles", "occupied", tile, TILE_OCCUPIED);
					updateHandPlayable(p);

					for (x=yGetDatabaseCount("summonLocations"); >0) {
						yDatabaseNext("summonLocations");
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("summonLocations"), 0.1);
						}
					}
					yClearDatabase("summonLocations");

					xsEnableRule("gameplay_01_select");
					xsDisableRule("gameplay_10_summon");
					trQuestVarSet("p"+p+"click", 0);
				}
			}
			case RIGHT_CLICK:
			{
				for (x=yGetDatabaseCount("summonLocations"); >0) {
					yDatabaseNext("summonLocations");
					if (trCurrentPlayer() == p) {
						highlightTile(1*trQuestVarGet("summonLocations"), 0.1);
					}
				}
				yClearDatabase("summonLocations");
				trQuestVarSet("p"+p+"click", 0);
				xsEnableRule("gameplay_01_select");
				xsDisableRule("gameplay_10_summon");
			}
		}
	}
}
