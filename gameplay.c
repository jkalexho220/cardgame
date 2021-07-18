const int GAMEPLAY_SELECT = 0;
const int GAMEPLAY_WORK = 1;
const int GAMEPLAY_MOVING = 2;
const int GAMEPLAY_SUMMONING = 3;
const int GAMEPLAY_ATTACKING = 4;


void processAttack(string db = "attacks") {
	int attackerIndex = yDatabaseNext(db);
	int targetIndex = yGetVar(db, "target");
	int attackerUnit = yGetUnitAtIndex("allUnits", attackerIndex);
	int targetUnit = yGetUnitAtIndex("allUnits", targetIndex);
	int attackerID = kbGetBlockID(""+attackerUnit);
	switch(1*yGetVar(db, "phase"))
	{
		case ATTACK_START:
		{
			if (yGetVarByIndex("allUnits", "health", attackerIndex) > 0) {
				trVectorQuestVarSet("d1pos", kbGetBlockPosition(""+attackerUnit, true));
				trVectorQuestVarSet("d2pos", kbGetBlockPosition(""+targetUnit, true));
				trUnitSelectClear();
				trUnitSelect(""+attackerUnit, true);
				trSetUnitOrientation(zGetUnitVector("d1pos", "d2pos"), xsVectorSet(0,1,0), true);
				if (yGetVarByIndex("allUnits", "range", attackerIndex) == 1) {
					trUnitOverrideAnimation(1,0,0,1,-1);
				} else {
					trUnitOverrideAnimation(12,0,0,1,-1);
				}
				ySetVar(db, "phase", ATTACK_ANIMATE);
				ySetVar(db, "timeout", trTime() + 1);
			} else {
				yRemoveFromDatabase(db);
				yRemoveUpdateVar(db, "target");
				yRemoveUpdateVar(db, "phase");
				yRemoveUpdateVar(db, "timeout");
			}
		}
		case ATTACK_ANIMATE:
		{
			if ((kbUnitGetAnimationActionType(attackerID) == 16) == false || trTime() > yGetVar(db, "timeout")) {
				ySetVar(db, "phase", ATTACK_DONE);
			}
		}
		case ATTACK_DONE:
		{
			if (HasKeyword(LIGHTNING, 1*yGetVarByIndex("allUnits", "keywords", attackerIndex))) {
				lightning(targetIndex, yGetVarByIndex("allUnits", "attack", attackerIndex), 
					HasKeyword(DEADLY, 1*yGetVarByIndex("allUnits", "keywords", attackerIndex)));
			} else if (HasKeyword(DEADLY, 1*yGetVarByIndex("allUnits", "keywords", attackerIndex)) &&
				yGetVarByIndex("allUnits", "spell", targetIndex) == SPELL_NONE) {
				ySetVarByIndex("allUnits", "health", targetIndex, 0);
				damageUnit("allUnits", targetIndex, 1);
				deployAtTile(0, "Lampades Blood", 1*yGetVarByIndex("allUnits", "tile", targetIndex));
			} else {
				damageUnit("allUnits", targetIndex, yGetVarByIndex("allUnits", "attack", attackerIndex));
				deployAtTile(0, "Lightning sparks", 1*yGetVarByIndex("allUnits", "tile", targetIndex));
			}
			/*
			On-attack events.
			*/
			int n = 1*xsPow(2, ATTACK_EVENT_COUNT - 1);
			int events = 1*yGetVarByIndex("allUnits", "OnAttack", attackerIndex);
			for(x=ATTACK_EVENT_COUNT - 1; >=0) {
				if (events >= n) {
					OnAttack(attackerIndex, targetIndex, x);
					events = events - n;
				}
				n = n / 2;
			}

			yRemoveFromDatabase(db);
			yRemoveUpdateVar(db, "target");
			yRemoveUpdateVar(db, "phase");
			yRemoveUpdateVar(db, "timeout");
		}
	}
}

/*
If target of the right-click was an enemy within range, start an attack
*/
bool attackUnitAtCursor(int p = 0) {
	int target = findNearestUnit("p"+p+"clickPos", 9);
	int a = trQuestVarGet("activeUnitIndex");

	if (target == -1) {
		return(false);
	}
	if (yGetVarByIndex("allUnits", "player", target) == 3 - p) {
		trQuestVarSet("targetUnit", yGetUnitAtIndex("allUnits", target));
		trVectorSetUnitPos("d1pos", "activeUnit");
		trVectorSetUnitPos("d2pos", "targetUnit");
		float range = xsPow(yGetVarByIndex("allUnits", "range", a) * 6 + 3, 2);
		float dist = 0;
		if (zDistanceBetweenVectorsSquared("d1pos", "d2pos") < range) {
			// Guard activates
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				dist = zDistanceToVectorSquared("allUnits", "d2pos");
				if (dist < 64 && dist > 9 &&
					yGetVar("allUnits", "stunTime") == 0 &&
					yGetVar("allUnits", "player") == 3 - p &&
					HasKeyword(GUARD, 1*yGetVar("allUnits", "keywords"))) {
					trSoundPlayFN("bronzebirth.wav","1",-1,"","");
					trSoundPlayFN("militarycreate.wav","1",-1,"","");
					trUnitHighlight(2.0, true);
					int guardTile = yGetVar("allUnits", "tile");
					int saveTile = yGetVarByIndex("allUnits", "tile", target);
					teleportToTile("allUnits", saveTile);
					teleportToTile("allUnits", guardTile, target);
					target = yGetPointer("allUnits");
					trQuestVarSet("targetUnit", trQuestVarGet("allUnits"));
					break;
				}
			}
			refreshGuardAll();

			startAttack(a, target, HasKeyword(AMBUSH, 1*yGetVarByIndex("allUnits", "keywords", a)), true);

			// Counterattack
			trQuestVarSet("targetUnitIndex", target);
			range = xsPow(yGetVarByIndex("allUnits", "range", target) * 6 + 3, 2);
			if ((zDistanceBetweenVectorsSquared("d1pos", "d2pos") < range) && (yGetVarByIndex("allUnits", "stunTime", target) == 0)) {
				startAttack(target, a, false, true);
			}

			ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), 
				xsMax(ACTION_DONE, yGetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"))));
			xsEnableRule("gameplay_05_attackComplete");
			return(true);
		}
	}

	return(false);
}

rule resolve_attacks
highFrequency
active
{
	if (yGetDatabaseCount("ambushAttacks") > 0) {
		processAttack("ambushAttacks");
	} else if (yGetDatabaseCount("attacks") > 0) {
		processAttack("attacks");
	}
	/*
	Resolve lightning every 100 MS.
	*/
	if (trTimeMS() > trQuestVarGet("lightningNext") && 
		(trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop")) == false) {
		trQuestVarSet("lightningNext", trTimeMS() + 100);
		int index = modularCounterNext("lightningActivate");
		int targetIndex = trQuestVarGet("lightning"+index);
		// If Deadly and target isn't a commander
		if (trQuestVarGet("lightning"+index+"damage") == -1 &&
			yGetVarByIndex("allUnits", "spell", targetIndex) == SPELL_NONE) {
			ySetVarByIndex("allUnits", "health", targetIndex, 0);
			damageUnit("allUnits", targetIndex, 1);
			deployAtTile(0, "Lampades Blood", 1*yGetVarByIndex("allUnits", "tile", targetIndex));
		} else {
			damageUnit("allUnits", targetIndex, trQuestVarGet("lightning"+index+"damage"));
			deployAtTile(0, "Lightning sparks", 1*yGetVarByIndex("allUnits", "tile", targetIndex));
		}
	}
}

rule gameplay_toggle_camera
highFrequency
inactive
{
	for(p=2; >0) {
		if (trCheckGPActive("rain", p)) {
			if (trQuestVarGet("p"+p+"rain") == 0) {
				trQuestVarSet("p"+p+"rain", 1);
				if (trCurrentPlayer() == p) {
					trQuestVarSet("cameraCut", 1 - trQuestVarGet("cameraCut"));
					if (trQuestVarGet("cameraCut") == 1) {
						uiLookAtUnit(1*trQuestVarGet("p"+p+"block"));
					} else {
						uiLookAtUnit(kbGetBlockID(""+1*trQuestVarGet("p"+p+"commander"), true));
					}
				}
				ChatLogShow();
			}
		} else if (trQuestVarGet("p"+p+"rain") == 1) {
			trTechGodPower(p, "rain", 1);
			trQuestVarSet("p"+p+"rain", 0);
		}
	}
}


rule gameplay_select_show_keywords
highFrequency
active
{
	yDatabaseNext("allUnits", true);
	if (trUnitIsSelected()) {
		displayCardKeywordsAndDescription("allUnits", 1*yGetPointer("allUnits"));
	}
	for(p=2; >0) {
		yDatabaseNext("p"+p+"hand", true);
		if (trUnitIsSelected()) {
			displayCardKeywordsAndDescription("p"+p+"hand", 1*yGetPointer("p"+p+"hand"));
		}
	}
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
		highlightReady(0.1);
	} else {
		trQuestVarSet("gameplayPhase", GAMEPLAY_SELECT);
		int p = trQuestVarGet("activePlayer");
		if (trQuestVarGet("p"+p+"click") == LEFT_CLICK) {
			int unit = findNearestUnit("p"+p+"clickPos", 8);
			trQuestVarSet("activeUnitIndex", unit);
			if (unit > -1) {
				
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
					highlightReady(0.1);
					xsEnableRule("gameplay_02_work");
				}
			} else {
				// Check if player selected a card in hand.
				unit = -1;
				float closestDistance = 9.0;
				float currentDistance = 0;
				for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					currentDistance = zDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos");
					if (currentDistance < closestDistance) {
						closestDistance = currentDistance;
						unit = yGetPointer("p"+p+"hand");
					}
				}
				if (unit > -1) {
					if (trQuestVarGet("p"+p+"mana") >= yGetVarByIndex("p"+p+"hand", "cost", unit)) {
						trQuestVarSet("gameplayPhase", GAMEPLAY_SUMMONING);
						// If it is a unit
						if (yGetVarByIndex("p"+p+"hand", "spell", unit) == 0) {
							int tile = 0;
							yClearDatabase("summonLocations");
							if (HasKeyword(AIRDROP, 1*yGetVarByIndex("p"+p+"hand", "keywords", unit))) {
								for(x=zGetBankCount("tiles"); >0) {
									zBankNext("tiles");
									if (zGetVar("tiles", "occupied") == TILE_EMPTY) {
										yAddToDatabase("summonLocations", "tiles");
									}
								}
							} else {
								for(x=yGetDatabaseCount("allUnits"); >0) {
									yDatabaseNext("allUnits");
									if (yGetVar("allUnits", "player") == p && HasKeyword(BEACON, 1*yGetVar("allUnits", "keywords"))) {
										tile = yGetVar("allUnits", "tile");
										findAvailableTiles(tile, 1, "summonLocations");
									}
								}
							}
							for (x=yGetDatabaseCount("summonLocations"); >0) {
								tile = yDatabaseNext("summonLocations");
								if (trCurrentPlayer() == p) {
									highlightTile(tile, 3600);
								}
							}

							trQuestVarSet("summonUnitIndex", unit);
							xsEnableRule("gameplay_10_summon");
						} else {
							// If it is a spell
							chooseSpell(1*yGetVarByIndex("p"+p+"hand", "spell", unit), unit);
						}
						
						xsDisableRule("gameplay_01_select");
						highlightReady(0.1);
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
		}
		if (yGetDatabaseCount("targets") > 0) {
			yDatabaseSelectAll("targets");
			trUnitHighlight(0.1, false);
			yClearDatabase("targets");
		}
	} else {
		trQuestVarSet("gameplayPhase", GAMEPLAY_WORK);
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
					highlightReady(100);

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
						if (HasKeyword(GUARD, 1*yGetVarByIndex("allUnits", "keywords", 1*trQuestVarGet("activeUnitIndex")))) {
							tileGuard(tile, false);
						}

						trVectorSetUnitPos("moveDestination", "moveTile");
						trQuestVarSet("activeUnitID", kbGetBlockID(""+1*trQuestVarGet("activeUnit"), true));
						trUnitSelectClear();
						trUnitSelectByID(1*trQuestVarGet("activeUnitID"));
						trUnitMoveToVector("moveDestination");
						
						ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_MOVED);
						trQuestVarSet("moving", 0);
						trQuestVarSet("gameplayPhase", GAMEPLAY_MOVING);
						xsEnableRule("gameplay_03_moveComplete");
						xsDisableRule("gameplay_02_work");
					}
				} else {
					trQuestVarSet("gameplayPhase", GAMEPLAY_ATTACKING);
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
	} else if (trQuestVarGet("moving") == 1) {
		if (kbUnitGetAnimationActionType(1*trQuestVarGet("activeUnitID")) == 9 || trQuestVarGet("turnEnd") == 1) {
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
					highlightReady(100);
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

			if (HasKeyword(GUARD, 1*yGetVarByIndex("allUnits", "keywords", 1*trQuestVarGet("activeUnitIndex")))) {
				refreshGuardAll();
			}


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
		trQuestVarSet("gameplayPhase", GAMEPLAY_WORK);
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
				highlightReady(100);
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
					trQuestVarSet("p"+p+"click", 0);
					xsDisableRule("gameplay_04_attack");
				}
			}
		}
	}
}


/*
Called to complete a duel of fates
Wait until all attacks are resolved to proceed.
*/
rule gameplay_05_attackComplete
highFrequency
inactive
{
	if ((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + trQuestVarGet("lightningActivate") - trQuestVarGet("lightningPop") == 0) || 
		(trTime() > cActivationTime + 3)) {
		int p = trQuestVarGet("activePlayer");

		if (yGetDatabaseCount("reachable") > 0) {
			for(x=yGetDatabaseCount("reachable"); >0) {
				highlightTile(1*yDatabaseNext("reachable"), 0.1);
			}
			yClearDatabase("reachable");
		}
		if (yGetDatabaseCount("targets") > 0) {
			yDatabaseSelectAll("targets");
			trUnitHighlight(0.1, false);
			yClearDatabase("targets");
		}

		if (trQuestVarGet("turnEnd") == 0) {
			if (HasKeyword(FURIOUS, 1*yGetVarByIndex("allUnits", "keywords", 1*trQuestVarGet("activeUnitIndex"))) &&
				yGetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex")) < ACTION_FURY &&
				yGetVarByIndex("allUnits", "health", 1*trQuestVarGet("activeUnitIndex")) > 0) {
				ySetVarByIndex("allUnits", "action", 1*trQuestVarGet("activeUnitIndex"), ACTION_FURY);
				xsEnableRule("gameplay_04_attack");
				yClearDatabase("targets");
				findTargets(1*trQuestVarGet("activeUnitIndex"), "targets");
				yDatabaseSelectAll("targets");
				trUnitHighlight(3600, false);
			} else {
				xsEnableRule("gameplay_01_select");
				highlightReady(100);
			}
		}

		removeDeadUnits();
		refreshGuardAll();

		/* 
		Database has been modified after removing units.
		If active unit has furious, we need to update the activeUnitIndex
		*/
		for(x=yGetDatabaseCount("allUnits"); >0) {
			if (trQuestVarGet("activeUnit") == yDatabaseNext("allUnits")) {
				trQuestVarSet("activeUnitIndex", yGetPointer("allUnits"));
				break;
			}
		}
		
		xsDisableRule("gameplay_05_attackComplete");
	}
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
					highlightReady(100);
					xsDisableRule("gameplay_10_summon");
					// We don't set the player click to 0 in case this click was used to select another unit in hand.
				} else {
					ySetPointer("p"+p+"hand", 1*trQuestVarGet("summonUnitIndex"));
					int unit = yGetUnitAtIndex("p"+p+"hand", 1*trQuestVarGet("summonUnitIndex"));
					
					teleportToTile("p"+p+"hand", tile, 1*trQuestVarGet("summonUnitIndex"));

					trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") - yGetVar("p"+p+"hand", "cost"));
					trSoundPlayFN("mythcreate.wav","1",-1,"","");

					transferUnit("allUnits", "p"+p+"hand");
					if (HasKeyword(CHARGE, 1*yGetVar("p"+p+"hand", "keywords")) == true) {
						yAddUpdateVar("allUnits", "action", ACTION_READY);
					} else {
						yAddUpdateVar("allUnits", "action", ACTION_SLEEPING);
					}
					updateMana();

					// If the unit has an OnPlay effect
					if (yGetVar("p"+p+"hand", "OnPlay") > 0) {
						int n = 1*xsPow(2, PLAY_EVENT_COUNT - 1);
						int events = 1*yGetVar("p"+p+"hand", "OnPlay");
						int latest = yGetDatabaseCount("allUnits") - 1;
						for(x=PLAY_EVENT_COUNT - 1; >=0) {
							if (events >= n) {
								OnPlay(latest, x);
								events = events - n;
							}
							n = n / 2;
						}
					} else {
						xsEnableRule("gameplay_01_select");
						highlightReady(100);
					}

					removeUnit("p"+p+"hand");

					zSetVarByIndex("tiles", "occupied", tile, TILE_OCCUPIED);
					updateHandPlayable(p);

					for (x=yGetDatabaseCount("summonLocations"); >0) {
						yDatabaseNext("summonLocations");
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("summonLocations"), 0.1);
						}
					}
					yClearDatabase("summonLocations");

					
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
				highlightReady(100);
				xsDisableRule("gameplay_10_summon");
			}
		}
	}
}
