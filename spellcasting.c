
const int CAST_UNIT = 0;
const int CAST_TARGET = 1;
const int CAST_SING = 2;

const int CAST_TILE = 10;
const int CAST_DIRECTION = 11;

const int CASTING_NOTHING = 0;
const int CASTING_IN_PROGRESS = 1;
const int CASTING_DONE = 2;
const int CASTING_CANCEL = 3;


void castReset() {
	trQuestVarSet("castPush", 0);
	trQuestVarSet("castPop", 0);
	trQuestVarSet("castDone", CASTING_NOTHING);
}

/*
int p = the player of the unit being selected. 0 = any player
string qv = the name of the quest var to store the unit selected by the player

This function doesn't do anything on its own. It adds a selection request to the queue.
The spellcast_ set of triggers will process these requests one by one and store the results
in the quest vars.
*/
void castAddUnit(string qv = "", int p = 0, bool commander = true) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	if (commander) {
		trQuestVarSet("cast"+x+"commander", SPELL_COMMANDER);
	} else {
		trQuestVarSet("cast"+x+"commander", SPELL_NONE);
	}
	trQuestVarSet("cast"+x+"type", CAST_UNIT);
	trQuestVarSet("cast"+x+"player", p);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

void castAddSing(string qv = "", int p = 0) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

	trQuestVarSet("cast"+x+"type", CAST_SING);
	trQuestVarSet("cast"+x+"player", p);
	trStringQuestVarSet("cast"+x+"qv", qv);
}

/*
qv = name of the quest var to store the selected tile
ghost = true if ignore impassable terrain
*/
void castAddTile(string qv = "", bool ghost = false) {
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

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
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

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
	trQuestVarSet("castPush", trQuestVarGet("castPush") + 1);
	int x = trQuestVarGet("castPush");

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
	trQuestVarSet("castDone", CASTING_IN_PROGRESS);
	xsEnableRule("spellcast_00_process");
}

void castEnd() {
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		removeIfDead("allUnits");
	}
	refreshGuardAll();
	xsEnableRule("gameplay_01_select");
	highlightReady(999999);

	if (trQuestVarGet("selectedCard") >= 0) {
		int p = trQuestVarGet("activePlayer");
		trUnitSelectClear();
		trUnitSelect(""+1*yGetUnitAtIndex("p"+p+"hand", 1*trQuestVarGet("selectedCard")), true);
		trUnitChangeProtoUnit("Hero Death");
		trQuestVarSet("p"+p+"mana", trQuestVarGet("p"+p+"mana") - yGetVarByIndex("p"+p+"hand", "cost", 1*trQuestVarGet("selectedCard")));
		updateMana();
		ySetPointer("p"+p+"hand", 1*trQuestVarGet("selectedCard"));
		removeUnit("p"+p+"hand");

		updateHandPlayable(p);
	}
	trQuestVarSet("castDone", CASTING_NOTHING);
}


rule spellcast_00_process
highFrequency
inactive
{
	if (trQuestVarGet("castPop") < trQuestVarGet("castPush")) {
		trQuestVarSet("castPop", trQuestVarGet("castPop") + 1);
		int x = trQuestVarGet("castPop");
		int p = trQuestVarGet("activePlayer");
		yClearDatabase("castTargets");
		yClearDatabase("castTiles");
		switch(1*trQuestVarGet("cast"+x+"type"))
		{
			case CAST_UNIT:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((yGetVar("allUnits", "player") == p) || (p == 0)) {
						if (yGetVar("allUnits", "spell") <= trQuestVarGet("cast"+x+"commander")) {
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
							trQuestVarSet("allUnitsIndex", yGetPointer("allUnits"));
							yAddToDatabase("castTargets", "allUnitsIndex");
							if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
								trUnitHighlight(999999, false);
							}
						}
					}
				}
			}
			case CAST_SING:
			{
				p = trQuestVarGet("cast"+x+"player");
				for(z=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					if ((yGetVar("allUnits", "player") == p) || (p == 0)) {
						if ((yGetVar("allUnits", "action") >= ACTION_DONE) && (yGetVar("allUnits", "action") < ACTION_SLEEPING)) {
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
							trQuestVarSet("allUnitsIndex", yGetPointer("allUnits"));
							yAddToDatabase("castTargets", "allUnitsIndex");
							if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
								trUnitHighlight(999999, false);
							}
						}
					}
				}
			}
			case CAST_TILE:
			{
				for (z=zGetBankCount("tiles"); >0) {
					zBankNext("tiles");
					if (zGetVar("tiles", "terrain") * trQuestVarGet("cast"+x+"terrain") == 0) {
						yAddToDatabase("castTiles", "tiles");
						if (trCurrentPlayer() == p) {
							highlightTile(1*trQuestVarGet("tiles"), 999999);
						}
					}
				}
			}
			case CAST_TARGET:
			{
				findTargets(1*trQuestVarGet(trStringQuestVarGet("cast"+x+"start")), "castTargets");
				trUnitSelectClear();
				yDatabaseSelectAll("castTargets");
				if (trCurrentPlayer() == p) {
					trUnitHighlight(999999, false);
				}
			}
			case CAST_DIRECTION:
			{
				if (trQuestVarGet("cast"+x+"unit") == 1) {
					trQuestVarSet("start", yGetVarByIndex("allUnits", "tile", 1*trQuestVarGet(trStringQuestVarGet("cast"+x+"start"))));
				} else {
					trQuestVarSet("start", trQuestVarGet(trStringQuestVarGet("cast"+x+"start")));
				}
				float angle = 0.785398;
				trVectorSetUnitPos("pos", "start");
				bool found = true;
				int tile = 0;
				// For each direction...
				for(d=6; >0) {
					trVectorSetFromAngle("step", angle);
					trVectorScale("step", 6.0);
					trQuestVarSet("posx", trQuestVarGet("posx") + trQuestVarGet("stepx"));
					trQuestVarSet("posz", trQuestVarGet("posx") + trQuestVarGet("stepz"));
					tile = trQuestVarGet("start");
					found = true;
					while(found) {
						found = false;
						// Travel down the line and highlight tiles
						for(z=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
							trVectorQuestVarSet("current", kbGetBlockPosition(""+1*zGetVarByIndex("tiles", "neighbor"+z, tile)));
							if (zDistanceBetweenVectorsSquared("current", "pos") < 1) {
								tile = zGetVarByIndex("tiles", "neighbor"+z, tile);
								trQuestVarSet("currentTile", tile);
								yAddToDatabase("castTiles", "currentTile");
								trQuestVarSet("posx", trQuestVarGet("posx") + trQuestVarGet("stepx"));
								trQuestVarSet("posz", trQuestVarGet("posz") + trQuestVarGet("stepz"));
								if (trCurrentPlayer() == p) {
									highlightTile(tile, 999999);
								}
								found = true;
								break;
							}
						}
					}
					angle = fModulo(6.283185, angle + 1.047197);
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
	if (trCurrentPlayer() == 1*trQuestVarGet("activePlayer")) {
		if (trQuestVarGet("cast"+x+"type") >= CAST_TILE) {
			for(z=yGetDatabaseCount("castTargets"); >0) {
				yDatabaseNext("castTargets");
				highlightTile(1*trQuestVarGet("castTargets"), 0.1);
			}
		} else {
			for (z=yGetDatabaseCount("castTargets"); >0) {
				yDatabaseNext("castTargets");
				trUnitSelectClear();
				trUnitSelect(""+1*yGetUnitAtIndex("allUnits", 1*trQuestVarGet("castTargets")), true);
				trUnitHighlight(0.1, false);
			}
		}
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
				if (trQuestVarGet("cast"+x+"type") < CAST_TILE) {
					for(z=yGetDatabaseCount("castTargets"); >0) {
						yDatabaseNext("castTargets");
						trQuestVarCopy("castTargetUnit", "castTargets");

						trQuestVarSet("castTargetUnit", yGetUnitAtIndex("allUnits", 1*trQuestVarGet("castTargets")));
						
						if (zDistanceToVectorSquared("castTargetUnit", "p"+p+"clickPos") < 8) {
							trQuestVarCopy(trStringQuestVarGet("cast"+x+"qv"), "castTargets");
							selected = true;
							break;
						}
					}
				} else {
					for(z=yGetDatabaseCount("castTiles"); >0) {
						yDatabaseNext("castTiles");
						
						if (zDistanceToVectorSquared("castTiles", "p"+p+"clickPos") < 8) {
							trQuestVarCopy(trStringQuestVarGet("cast"+x+"qv"), "castTiles");
							selected = true;
							break;
						}
					}
				}
				if (selected) {
					spellcastClearHighlights(x);
					trQuestVarSet("p"+p+"click", 0);
					xsEnableRule("spellcast_00_process");
					xsDisableRule("spellcast_01_select");
				} else {
					/*
					If the player selected another card in hand, we abort. Otherwise, we shame
					the player for making such a rookie mistake.
					We don't set click back to 0 if they selected another card in hand.
					*/
					for(z=yGetDatabaseCount("p"+p+"hand"); >0) {
						yDatabaseNext("p"+p+"hand");
						if (zDistanceToVectorSquared("p"+p+"hand", "p"+p+"clickPos") < 2) {
							spellcastClearHighlights(x);
							castReset();
							trQuestVarSet("castDone", CASTING_CANCEL);
							xsEnableRule("gameplay_01_select");
							highlightReady(999999);
							xsDisableRule("spellcast_01_select");
							break;
						}
					}
					if (z == 0) {
						trQuestVarSet("p"+p+"click", 0);
						if (trCurrentPlayer() == p) {
							trSoundPlayFN("cantdothat.wav","1",-1,"","");
						}
					}
				}
			}
			case RIGHT_CLICK:
			{
				trQuestVarSet("p"+p+"click", 0);
				spellcastClearHighlights(x);
				castReset();
				trQuestVarSet("castDone", CASTING_CANCEL);
				xsEnableRule("gameplay_01_select");
				highlightReady(999999);
				xsDisableRule("spellcast_01_select");
			}
		}
	}
}

/*
Given an integer for a spell, prompt the player to select a target
and get ready to cast the spell.
card = the index of the card in hand that will be removed when the spell is cast. If -1, then no
card is removed.
*/
void chooseSpell(int spell = 0, int card = -1) {
	trQuestVarSet("currentSpell", spell);
	trQuestVarSet("selectedCard", card);
	switch(spell)
	{
		case SPELL_SPARK:
		{
			if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
				trMessageSetText("(1)Spark: Deal 1 damage to a unit.", -1);
			}
			castReset();
			castAddUnit("spellTarget", 0);
			castStart();
			xsEnableRule("spell_cast");
		}
		case SPELL_FOOD:
		{
			if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
				trMessageSetText("Choose a unit to give +1 attack and health to.", -1);
			}
			castReset();
			castAddUnit("spellTarget", 1*trQuestVarGet("activePlayer"), false);
			castStart();
			xsEnableRule("spell_cast");
		}
		case SPELL_SING:
		{
			if (trCurrentPlayer() == trQuestVarGet("activePlayer")) {
				trMessageSetText("(2)Windsong: Select an ally that has already acted. Grant it another action.", -1);
			}
			castReset();
			castAddSing("spellTarget", 1*trQuestVarGet("activePlayer"));
			castStart();
			xsEnableRule("spell_cast");
		}
	}
}


rule spell_cast
highFrequency
inactive
{
	if (trQuestVarGet("turnEnd") == 1) {
		xsDisableRule("spell_cast");
	} else if (trQuestVarGet("castDone") == CASTING_DONE) {
		bool done = true;
		int target = 0;
		trSoundPlayFN("godpower.wav","1",-1,"","");
		switch(1*trQuestVarGet("currentSpell"))
		{
			case SPELL_SPARK:
			{
				damageUnit("allUnits", 1*trQuestVarGet("spellTarget"), 1);
				deployAtTile(0, "Tartarian Gate flame", 1*yGetVarByIndex("allUnits", "tile", 1*trQuestVarGet("spellTarget")));
				trMessageSetText("(1)Spark: Deal 1 damage to a unit.", -1);
			}
			case SPELL_FOOD:
			{
				target = 1*trQuestVarGet("spellTarget");
				ySetVarByIndex("allUnits", "attack", target, 1 + yGetVarByIndex("allUnits", "attack", target));
				ySetVarByIndex("allUnits", "health", target, 1 + yGetVarByIndex("allUnits", "health", target));
				deployAtTile(0, "Hero Birth", 1*yGetVarByIndex("allUnits", "tile", target));
				trSoundPlayFN("colossuseat.wav","1",-1,"","");
				trSoundPlayFN("researchcomplete.wav","1",-1,"","");
				trUnitSelectClear();
				trUnitSelect(""+1*yGetUnitAtIndex("allUnits", target), true);
				spyEffect("Einheriar Boost SFX");
			}
			case SPELL_SING:
			{
				target = 1*trQuestVarGet("spellTarget");
				ySetVarByIndex("allUnits", "action", target, ACTION_READY);
				deployAtTile(0, "Hero Birth", 1*yGetVarByIndex("allUnits", "tile", target));
				trSoundPlayFN("restorationbirth.wav","1",-1,"","");
				trMessageSetText("(2)Windsong: Select an ally that has already acted. Grant it another action.",-1);
			}
		}

		if (done) {
			castEnd();
		}
		xsDisableRule("spell_cast");
	}
}