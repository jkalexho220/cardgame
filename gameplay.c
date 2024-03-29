


void processAttack(string db = "attacks") {
	int attacker = yDatabaseNext(db);
	int target = yGetVar(db, "target");
	int attackerID = kbGetBlockID(""+attacker);
	switch(1*yGetVar(db, "phase"))
	{
		case ATTACK_START:
		{
			if (mGetVar(attacker, "health") > 0) {
				trVectorQuestVarSet("d1pos", kbGetBlockPosition(""+attacker, true));
				trVectorQuestVarSet("d2pos", kbGetBlockPosition(""+target, true));
				trUnitSelectClear();
				trUnitSelect(""+attacker, true);
				trSetUnitOrientation(trGetUnitVector("d1pos", "d2pos"), xsVectorSet(0,1,0), true);
				switch(1*yGetVar(db, "animation"))
				{
					case ANIM_DEFAULT:
					{
						if (mGetVar(attacker, "range") <= 1) {
							trUnitOverrideAnimation(1,0,false,true,-1);
						} else {
							trUnitOverrideAnimation(12,0,false,true,-1);
						}
					}
					case ANIM_CHARGING:
					{
						trUnitOverrideAnimation(19,0,false,true,-1);
					}
					case ANIM_GORE:
					{
						trUnitOverrideAnimation(26,0,false,true,-1);
					}
				}
				
				ySetVar(db, "phase", ATTACK_ANIMATE);
				ySetVar(db, "timeout", trTimeMS() + 1500);
				
				/*
				Undercity Sniper
				*/
				if (mGetVar(attacker, "spell") == SPELL_COMMANDER) {
					for(x=yGetDatabaseCount("allUnits"); >0) {
						yDatabaseNext("allUnits");
						if ((mGetVarByQV("allUnits", "proto") == kbGetProtoUnitID("Archer Atlantean")) &&
							(mGetVarByQV("allUnits", "player") == mGetVar(attacker, "player"))) {
							startAttack(1*trQuestVarGet("allUnits"), target, false, true);
						}
					}
				}
			} else {
				yRemoveFromDatabase(db);
			}
		}
		case ATTACK_ANIMATE:
		{
			if ((kbUnitGetAnimationActionType(attackerID) == 16) == false || trTimeMS() > yGetVar(db, "timeout")) {
				ySetVar(db, "phase", ATTACK_DONE);
			}
		}
		case ATTACK_DONE:
		{
			if (HasKeyword(LIGHTNING, 1*mGetVar(attacker, "keywords"))) {
				lightning(target, mGetVar(attacker, "attack"), HasKeyword(DEADLY, 1*mGetVar(attacker, "keywords")));
			} else if (HasKeyword(DEADLY, 1*mGetVar(attacker, "keywords")) &&
				mGetVar(target, "spell") == SPELL_NONE) {
				mSetVar(target, "health", 0);
				damageUnit(target, 1);
				deployAtTile(0, "Lampades Blood", 1*mGetVar(target, "tile"));
			} else {
				damageUnit(target, mGetVar(attacker, "attack"));
				deployAtTile(0, "Lightning sparks", 1*mGetVar(target, "tile"));
			}
			/*
			On-attack events.
			*/
			int n = 1*xsPow(2, ATTACK_EVENT_COUNT - 1);
			int events = 1*mGetVar(attacker, "OnAttack");
			for(x=ATTACK_EVENT_COUNT - 1; >=0) {
				if (events >= n) {
					OnAttack(attacker, target, x);
					events = events - n;
				}
				n = n / 2;
			}
			
			yRemoveFromDatabase(db);
		}
	}
}

/*
If target of the right-click was an enemy within range, start an attack
*/
bool attackUnitAtCursor(int p = 0) {
	int target = findNearestUnit("p"+p+"clickPos", 9);
	int a = trQuestVarGet("activeUnit");
	int id = trQuestVarGet("activeUnitID");
	
	if (target == -1) {
		return(false);
	}
	if (HasKeyword(STEALTH, 1*mGetVar(target, "keywords"))) {
		return(false);
	}
	if (mGetVar(target, "player") == 3 - p) {
		trQuestVarSet("targetUnit", target);
		trVectorSetUnitPos("d1pos", "activeUnit");
		trVectorSetUnitPos("d2pos", "targetUnit");
		float range = xsPow(mGetVar(a, "range") * 6 + 1, 2);
		float dist = 0;
		if (trDistanceBetweenVectorsSquared("d1pos", "d2pos") < range) {
			// Guard activates
			target = checkGuard(target);
			
			startAttack(a, target, HasKeyword(AMBUSH, 1*mGetVar(a, "keywords")), true);
			
			// Counterattack
			range = xsPow(mGetVar(target, "range") * 6 + 3, 2);
			if ((trDistanceBetweenVectorsSquared("d1pos", "d2pos") < range) &&
				(mGetVar(target, "stunTime") == 0) &&
				(HasKeyword(HEALER, 1*mGetVar(target, "keywords")) == false)) {
				if ((HasKeyword(FLYING, 1*mGetVar(a, "keywords")) == false) ||
					(mGetVar(target, "range") > 1)) {
					startAttack(target, a, false, true);
				}
			}
			
			mSetVar(a, "action", xsMax(ACTION_DONE, mGetVar(a, "action")));
			xsEnableRule("gameplay_05_attackComplete");
			return(true);
		}
	} else if (HasKeyword(HEALER, 1*mGetVar(a, "keywords"))) {
		trQuestVarSet("targetUnit", target);
		trUnitSelectClear();
		trUnitSelect(""+a, true);
		trVectorSetUnitPos("d1pos", "activeUnit");
		trVectorSetUnitPos("d2pos", "targetUnit");
		trSetUnitOrientation(trGetUnitVector("d1pos", "d2pos"), xsVectorSet(0,1,0), true);
		switch(kbGetUnitBaseTypeID(id))
		{
			case kbGetProtoUnitID("Maceman Hero"):
			{
				trUnitOverrideAnimation(1, 0, false, true, -1);
			}
			case kbGetProtoUnitID("Flying Purple Hippo"):
			{
				trUnitOverrideAnimation(1, 0, false, true, -1);
			}
			default:
			{
				trUnitOverrideAnimation(50, 0, false, true, -1);
			}
		}
		healUnit(target, mGetVar(a, "attack"));
		if (kbGetUnitBaseTypeID(kbGetBlockID(""+a)) == kbGetProtoUnitID("Physician")) {
			if (mGetVar(target, "action") < ACTION_SLEEPING) {
				mSetVar(target, "action", ACTION_READY);
				deployAtTile(0, "Arkantos Boost SFX", 1*mGetVar(target, "tile"));
			}
		}
		deployAtTile(0, "Regeneration SFX", 1*mGetVar(target, "tile"));
		mSetVar(a, "action", xsMax(ACTION_DONE, mGetVar(a, "action")));
		xsEnableRule("gameplay_05_attackComplete");
		return(true);
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
			mGetVar(targetIndex, "spell") == SPELL_NONE) {
			mSetVar(targetIndex, "health", 0);
			damageUnit(targetIndex, 1);
			deployAtTile(0, "Lampades Blood", 1*mGetVar(targetIndex, "tile"));
		} else {
			damageUnit(targetIndex, trQuestVarGet("lightning"+index+"damage"));
			deployAtTile(0, "Lightning sparks", 1*mGetVar(targetIndex, "tile"));
		}
	}
}

rule gameplay_toggle_camera
highFrequency
inactive
{
	if (trQuestVarGet("pressSpace") == 1) {
		int p = trCurrentPlayer();
		trQuestVarSet("cameraCut", 1 - trQuestVarGet("cameraCut"));
		if (trQuestVarGet("cameraCut") == 1) {
			uiLookAtUnit(1*trQuestVarGet("p"+p+"block"));
		} else {
			uiLookAtUnit(kbGetBlockID(""+1*trQuestVarGet("p"+p+"commander"), true));
		}
		trQuestVarSet("pressSpace", 0);
	}
}


rule gameplay_select_show_keywords
highFrequency
inactive
{
	yDatabaseNext("allUnits", true);
	if (trUnitIsSelected()) {
		displayCardKeywordsAndDescription(1*trQuestVarGet("allUnits"));
	}
	
	for(p=2; >0) {
		yDatabaseNext("p"+p+"hand", true);
		if (trUnitIsSelected()) {
			displayCardKeywordsAndDescription(1*trQuestVarGet("p"+p+"hand"));
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
		int tile = 0;
		if (trQuestVarGet("p"+p+"click") == LEFT_CLICK) {
			int unit = findNearestUnit("p"+p+"clickPos", 8);
			trQuestVarSet("activeUnit", unit);
			trQuestVarSet("activeUnitID", kbGetBlockID(""+unit));
			if (unit > -1) {
				
				/*
				If the player owns the selected unit and and the unit hasn't moved yet,
				then highlight locations that it can move to and proceed to gameplay_02_work.
				*/
				if (mGetVar(unit, "player") == p &&
					mGetVar(unit, "action") == ACTION_READY) {
					highlightReachable(unit);
					
					// highlight attackable enemies within range
					findTargets(unit, "targets", HasKeyword(HEALER, 1*mGetVar(unit, "keywords")));
					yDatabaseSelectAll("targets");
					trUnitHighlight(3600.0, false);
					
					xsDisableRule("gameplay_01_select");
					highlightReady(0.1);
					xsEnableRule("gameplay_02_work");
				}
			} else {
				// Check if player selected a card in hand.
				unit = -1;
				int cost = 0;
				int pointer = 0;
				float closestDistance = 9.0;
				float currentDistance = 0;
				for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
					yDatabaseNext("p"+p+"hand");
					currentDistance = trDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos");
					if (currentDistance < closestDistance) {
						closestDistance = currentDistance;
						unit = trQuestVarGet("p"+p+"hand");
						pointer = yGetPointer("p"+p+"hand");
					}
				}
				if (unit > -1) {
					cost = mGetVar(unit, "cost");
					if (mGetVar(unit, "spell") > 0) {
						cost = cost - trQuestVarGet("p"+p+"spellDiscount");
					} else {
						cost = cost - trQuestVarGet("p"+p+"unitDiscount");
					}
					if (HasKeyword(OVERFLOW, 1*mGetVar(unit, "keywords"))) {
						cost = cost - trQuestVarGet("p"+p+"manaflow");
					}
					if (trQuestVarGet("p"+p+"mana") >= cost) {
						trQuestVarSet("gameplayPhase", GAMEPLAY_SUMMONING);
						// If it is a unit
						if (mGetVar(unit, "spell") == 0) {
							tile = 0;
							yClearDatabase("summonLocations");
							if (HasKeyword(AIRDROP, 1*mGetVar(unit, "keywords"))) {
								for(x=zGetBankCount("tiles"); >0) {
									zBankNext("tiles");
									if (zGetVar("tiles", "occupant") + zGetVar("tiles", "terrain") == TILE_EMPTY) {
										yAddToDatabase("summonLocations", "tiles");
									}
								}
							} else {
								for(x=yGetDatabaseCount("allUnits"); >0) {
									yDatabaseNext("allUnits");
									if (mGetVarByQV("allUnits", "player") == p && HasKeyword(BEACON, 1*mGetVarByQV("allUnits", "keywords"))) {
										tile = mGetVarByQV("allUnits", "tile");
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
							
							trQuestVarSet("summonUnit", unit);
							xsEnableRule("gameplay_10_summon");
						} else {
							// If it is a spell
							chooseSpell(1*mGetVar(unit, "spell"), pointer);
						}
						
						trQuestVarSet("handPointer", pointer);
						
						xsDisableRule("gameplay_01_select");
						highlightReady(0.1);
					}
					
				} else {
					for(x=yGetDatabaseCount("meteors"); >0) {
						yDatabaseNext("meteors");
						if (trDistanceToVectorSquared("meteors", "p"+p+"clickPos") < 9) {
							trMessageSetText("A meteor will fall on this tile, dealing 6 damage to it and 2 damage to adjacent tiles.", -1);
							break;
						}
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
				if (trQuestVarGet("activeUnit") > -1) {
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
					if (mGetVarByQV("activeUnit", "action") == ACTION_MOVED) {
						mSetVarByQV("activeUnit", "action", ACTION_DONE);
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
				int unit = trQuestVarGet("activeUnit");
				/*
				First check if player wants unit to attack something in range
				without moving it.
				*/
				if (attackUnitAtCursor(p) == false) {
					trQuestVarSet("moveTile", -1);
					for (x=yGetDatabaseCount("reachable"); >0) {
						yDatabaseNext("reachable");
						if (trDistanceToVectorSquared("reachable", "p"+p+"clickPos") < 9) {
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
						int tile = mGetVarByQV("activeUnit", "tile");
						zSetVarByIndex("tiles", "occupant", tile, 0);
						if (HasKeyword(GUARD, 1*mGetVarByQV("activeUnit", "keywords"))) {
							tileGuard(tile, false);
						}
						
						trVectorSetUnitPos("moveDestination", "moveTile");
						trUnitSelectClear();
						trUnitSelectByID(1*trQuestVarGet("activeUnitID"));
						trUnitMoveToVector("moveDestination");
						trQuestVarSet("moving", 0);
						
						mSetVarByQV("activeUnit", "action", ACTION_MOVED);
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
		} else if((trTime()-cActivationTime) > 1) {
			trQuestVarSet("moving", 1);
		}
	} else if (trQuestVarGet("moving") == 1) {
		if (kbUnitGetAnimationActionType(1*trQuestVarGet("activeUnitID")) == 9 || trQuestVarGet("turnEnd") == 1) {
			int p = trQuestVarGet("activePlayer");
			
			trVectorSetUnitPos("start", "activeUnit");
			trVectorSetUnitPos("end", "moveTile");
			
			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("moveTile"));
			trSetUnitOrientation(trGetUnitVector("start", "end"),xsVectorSet(0,1,0), true);
			teleportToTile(1*trQuestVarGet("activeUnit"), 1*trQuestVarGet("moveTile"));

			if (kbGetUnitBaseTypeID(1*trQuestVarGet("activeUnitID")) == kbGetProtoUnitID("Hero Greek Atalanta")) {
				mSetVarByQV("activeUnit", "attack", 1 + mGetVarByQV("activeUnit", "attack"));
			}
			
			if (trQuestVarGet("turnEnd") == 0) {
				findTargets(1*trQuestVarGet("activeUnit"), "targets", HasKeyword(HEALER, 1*mGetVarByQV("activeUnit", "keywords")));
				/*
				If no targets found, we go back to gameplay_01_select
				Otherwise, we go to gameplay_04_attack
				*/
				if (yGetDatabaseCount("targets") == 0) {
					xsEnableRule("gameplay_01_select");
					highlightReady(100);
					mSetVarByQV("activeUnit", "action", ACTION_DONE);
				} else {
					xsEnableRule("gameplay_04_attack");
					mSetVarByQV("activeUnit", "action", ACTION_MOVED);
					yDatabaseSelectAll("targets");
					trUnitHighlight(3600, false);
				}
			}
			
			mSetVarByQV("activeUnit", "tile", trQuestVarGet("moveTile"));
			zSetVarByIndex("tiles", "occupant", 1*trQuestVarGet("moveTile"), 1*trQuestVarGet("activeUnit"));
			
			if (HasKeyword(GUARD, 1*mGetVarByQV("activeUnit", "keywords"))) {
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
				mSetVarByQV("activeUnit", "action", ACTION_DONE);
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
					trQuestVarSet("gameplayPhase", GAMEPLAY_ATTACKING);
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
	if (((yGetDatabaseCount("ambushAttacks") + yGetDatabaseCount("attacks") + yGetDatabaseCount("pushes") == 0) && (trQuestVarGet("lightningActivate") == trQuestVarGet("lightningPop"))) ||
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
		
		removeDeadUnits();
		updateAuras();
		refreshGuardAll();
		
		if (trQuestVarGet("turnEnd") == 0) {
			if (HasKeyword(FURIOUS, 1*mGetVarByQV("activeUnit", "keywords")) &&
				mGetVarByQV("activeUnit", "action") < ACTION_FURY &&
				mGetVarByQV("activeUnit", "health") > 0) {
				mSetVarByQV("activeUnit", "action", ACTION_FURY);
				xsEnableRule("gameplay_04_attack");
				yClearDatabase("targets");
				findTargets(1*trQuestVarGet("activeUnit"), "targets", HasKeyword(HEALER, 1*mGetVarByQV("activeUnit", "keywords")));
				yDatabaseSelectAll("targets");
				trUnitHighlight(3600, false);
			} else {
				xsEnableRule("gameplay_01_select");
				highlightReady(100);
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
					if (trDistanceToVectorSquared("summonLocations", "p"+p+"clickPos") < 9) {
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
					int unit = trQuestVarGet("summonUnit");
					yAddToDatabase("allUnits", "summonUnit");
					
					teleportToTile(unit, tile);

					trQuestVarSet("p"+p+"lastProto", kbGetUnitBaseTypeID(unit));
					
					int cost = mGetVar(unit, "cost");
					cost = xsMax(0, cost - trQuestVarGet("p"+p+"unitDiscount"));
					if (HasKeyword(OVERFLOW, 1*mGetVar(unit, "keywords"))) {
						cost = xsMax(0, mGetVar(unit, "cost") - trQuestVarGet("p"+p+"manaflow"));
					}
					trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") - cost);
					trSoundPlayFN("mythcreate.wav","1",-1,"","");
					
					if (HasKeyword(CHARGE, 1*mGetVar(unit, "keywords")) == true) {
						mSetVar(unit, "action", ACTION_READY);
					} else {
						mSetVar(unit, "action", ACTION_SLEEPING);
					}
					updateMana();
					
					
					
					updateAuras();
					
					ySetPointer("p"+p+"hand", 1*trQuestVarGet("handPointer"));
					zSetVarByIndex("p"+p+"handPos", "occupied", 1*yGetVar("p"+p+"hand", "pos"), 0);
					yRemoveFromDatabase("p"+p+"hand");
					
					zSetVarByIndex("tiles", "occupant", tile, unit);
					// If the unit has an OnPlay effect
					OnCreate(unit);
					OnPlay(unit);
					updateHandPlayable(p);
					
					for (x=yGetDatabaseCount("summonLocations"); >0) {
						yDatabaseNext("summonLocations");
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("summonLocations"), 0.1);
						}
					}
					yClearDatabase("summonLocations");
					
					string name = trStringQuestVarGet("card_"+1*kbGetUnitBaseTypeID(kbGetBlockID(""+unit))+"_name");
					ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> summoned " + name);
					
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

rule PlayerResign
highFrequency
active
{
	if (kbIsPlayerResigned(trCurrentPlayer())) {
		xsDisableSelf();
		// trChatHistoryClear();
		map("mouse1down", "game", "uiSelectionButtonDown");
		map("mouse2up", "game", "uiWorkAtPointer");
		map("mouse2doubleup", "game", "uiWorkAtPointer");
		map("delete", "game", "uiDeleteSelectedUnit");
		map("space", "game", "uiLookAtSelection");
		map("enter", "game", "gadgetReal(\"chatInput\") uiIgnoreNextKey");
		//trModeEnter("Pregame");
	}
}