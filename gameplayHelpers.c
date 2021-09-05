const int GAMEPLAY_SELECT = 0;
const int GAMEPLAY_WORK = 1;
const int GAMEPLAY_MOVING = 2;
const int GAMEPLAY_SUMMONING = 3;
const int GAMEPLAY_ATTACKING = 4;
const int GAMEPLAY_SPELL_UNIT = 5;
const int GAMEPLAY_SPELL_TILE = 6;


const int ACTION_READY = 0;
const int ACTION_MOVED = 1;
const int ACTION_DONE = 2;
const int ACTION_FURY = 3;
const int ACTION_SLEEPING = 4;
const int ACTION_STUNNED = 5;

const int ATTACK_START = 0;
const int ATTACK_ANIMATE = 1;
const int ATTACK_DONE = 2;

const int STATE_ALIVE = 0;
const int STATE_DEAD = 1;

const int ANIM_DEFAULT = 0;
const int ANIM_CHARGING = 1;
const int ANIM_GORE = 2;

void updateMana() {
	int p = trQuestVarGet("activePlayer");
	trCounterAbort("mana");
	trCounterAddTime("mana", -1, -91, 
			"<color={Playercolor("+p+")}>Mana: "+1*trQuestVarGet("p"+p+"mana") + "/" + 1*trQuestVarGet("maxMana"),-1);
}



void scaleUnit(int unit = 0) {
	float scale = xsSqrt(mGetVar(unit, "scale"));
	trUnitSelectClear();
	trUnitSelect(""+unit);
	trSetSelectedScale(scale, scale, scale);
}


void refreshGuardAll() {
	yClearDatabase("guardUnits");
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		if (HasKeyword(GUARD, 1*mGetVarByQV("allUnits", "keywords")) == false) {
			tileGuard(1*mGetVarByQV("allUnits", "tile"), false);
		} else {
			yAddToDatabase("guardUnits", "allUnits");
		}
	}
	for(x=yGetDatabaseCount("guardUnits"); >0) {
		yDatabaseNext("guardUnits");
		tileGuard(1*mGetVarByQV("guardUnits", "tile"), true);
	}
}


/*
Removes the currently selected unit in a search from
the database. This is where we put all the special variables
that need to be updated whenever a unit is removed.
This is called only after a yDatabaseNext("allUnits").
*/
void removeUnit(string db = "allUnits") {
	yRemoveFromDatabase(db);
	yRemoveUpdateVar(db, "pos");
}

/*
Transfers the unit at the current pointer in the 'from' database
to the 'to' database.
*/
void transferUnit(string to = "", string from = "") {
	yAddToDatabase(to, from);
	yTransferUpdateVar(to, from, "pos");
}


void teleportToTile(int name = 0, int tile = 0) {
	int p = mGetVar(name, "player");

	if (HasKeyword(GUARD, 1*mGetVar(name, "keywords"))) {
		if (mGetVar(name, "tile") > 0) {
			tileGuard(1*mGetVar(name, "tile"), false);
		}
		tileGuard(tile, true);
	}
	

	trUnitSelectClear();
	trUnitSelectByID(tile);
	trUnitConvert(p);
	trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
	
	trUnitSelectClear();
	trUnitSelect(""+name);
	trMutateSelected(kbGetProtoUnitID("Dwarf"));
	trImmediateUnitGarrison(""+tile);
	trUnitChangeProtoUnit("Victory Marker");
	trUnitSelectClear();
	trUnitSelect(""+name);
	trMutateSelected(1*mGetVar(name, "proto"));
	scaleUnit(name);

	trUnitSelectClear();
	trUnitSelectByID(tile);
	trUnitConvert(0);
	trMutateSelected(kbGetProtoUnitID("Victory Marker"));

	mSetVar(name, "tile", tile);
	zSetVarByIndex("tiles", "occupant", tile, name);
}



int summonAtTile(int tile = 0, int p = 0, int proto = 0) {
	trQuestVarSet("next", CardInstantiate(p, proto, SPELL_NONE));
	teleportToTile(1*trQuestVarGet("next"), tile);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("next"));
	trUnitOverrideAnimation(18,0,0,1,-1);
	yAddToDatabase("allUnits", "next");
	return(1*trQuestVarGet("next"));
}


/*
Given a QV vector name, find the name of the closest unit to it.
Returns -1 if none found.
radius is the squared value to be compared to
*/
int findNearestUnit(string qv = "", float radius = 1) {
	int id = 0;
	for (x=yGetDatabaseCount("allUnits"); >0) {
		id = yDatabaseNext("allUnits", true);
		if (id == -1) {
			removeUnit();
		} else {
			if (zDistanceToVectorSquared("allUnits", qv) < radius) {
				return(1*trQuestVarGet("allUnits"));
			}
		}
	}
	return(-1);
}




/*
Given the name of a unit in the allUnits database, highlight
the tiles that are reachable by that unit.
*/
void highlightReachable(int name = 0) {
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+name, true));
	int tile = findNearestTile("pos");
	findAvailableTiles(tile, mGetVar(name, "speed"), "reachable", 
		(HasKeyword(ETHEREAL, 1*mGetVar(name, "keywords")) || HasKeyword(FLYING, 1*mGetVar(name, "keywords"))));
	for(x=yGetDatabaseCount("reachable"); >0) {
		tile = yDatabaseNext("reachable");
		highlightTile(tile, 3600);
	}
}

/*
highlights units that are ready to perform an action
*/
void highlightReady(float duration = 0.1) {
	int p = trQuestVarGet("activePlayer");
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		if ((mGetVarByQV("allUnits", "action") == ACTION_READY) && (mGetVarByQV("allUnits", "player") == p)) {
			if (trCurrentPlayer() == p) {
				trUnitHighlight(duration, false);
			}
		}
	}
}

/*
Given the name of a unit in the allUnits database, find
enemy units that can be attacked by the unit and add them to
the database db.
*/
void findTargets(int name = 0, string db = "", bool healer = false) {
	float dist = xsPow(mGetVar(name, "range") * 6 + 1, 2);
	int p = 3 - mGetVar(name, "player");
	if (healer) {
		p = 3 - p;
	}
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+name));
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		if (trQuestVarGet("allUnits") == name) {
			continue;
		} else if ((mGetVarByQV("allUnits", "player") == p) ||
			mGetVar(name, "proto") == kbGetProtoUnitID("Hoplite")) {
			if (zDistanceToVectorSquared("allUnits", "pos") < dist) {
				if (HasKeyword(FLYING, 1*mGetVarByQV("allUnits", "keywords")) == false) {
					yAddToDatabase(db, "allUnits");
				} else if (mGetVar(name, "range") > 1) {
					yAddToDatabase(db, "allUnits");
				}
			}
		}
	}
}

void healUnit(int index = 0, float heal = 0) {
	xsSetContextPlayer(1*mGetVar(index, "player"));
	float health = kbUnitGetCurrentHitpoints(kbGetBlockID(""+index));
	trUnitSelectClear();
	trUnitSelect(""+index);
	trDamageUnit(0 - heal);
	float diff = kbUnitGetCurrentHitpoints(kbGetBlockID(""+index)) - health;
	mSetVar(index, "health", 1*mGetVar(index, "health") + diff);
}

void damageUnit(int index = 0, float dmg = 0) {
	int p = mGetVar(index, "player");
	if (HasKeyword(ARMORED, 1*mGetVar(index, "keywords"))) {
		dmg = xsMax(0, dmg - 1);
	}
	/*
	Throne Shield activates here
	*/
	if ((trCountUnitsInArea("128",p,"Trident Soldier Hero",45) > 0) && (index == trQuestVarGet("p"+p+"commander"))) {
		int pointer = yGetPointer("allUnits");
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (1*mGetVarByQV("allUnits", "proto") == kbGetProtoUnitID("Trident Soldier Hero")) {
				damageUnit(1*trQuestVarGet("allUnits"), dmg);
				break;
			}
		}
		ySetPointer("allUnits", pointer);
	} else {
		xsSetContextPlayer(p);
		float health = kbUnitGetCurrentHitpoints(kbGetBlockID(""+index));
		mSetVar(index, "health", 1*mGetVar(index, "health") - dmg);
		trUnitSelectClear();
		trUnitSelect(""+index);
		trDamageUnit(health - mGetVar(index, "health"));
	}
}

void lightning(int index = 0, int damage = 0, bool deadly = false) {
	trQuestVarSetFromRand("rand", 1, 5, true);
	trSoundPlayFN("lightningstrike"+1*trQuestVarGet("rand")+".wav","1",-1,"","");
	int p = mGetVar(index, "player");
	if (deadly) {
		damage = -1;
	}
	// find lightning chain
	for (x=zGetBankCount("tiles"); >0) {
		zBankNext("tiles");
		zSetVar("tiles", "searched", 0);
	}
	int unit = index;
	zSetVarByIndex("tiles", "searched", 1*mGetVar(index, "tile"), 1);
	int tile = 0;
	int pop = -1;
	int neighbor = 0;
	int push = modularCounterNext("lightningPush");
	trQuestVarSet("lightning" + push, index);
	trQuestVarSet("lightning" + push + "damage", damage);
	while ((pop == push) == false) {
		pop = modularCounterNext("lightningPop");
		unit = trQuestVarGet("lightning" + pop);
		tile = mGetVar(unit, "tile");

		for(x=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
			neighbor = 1*zGetVarByIndex("tiles", "neighbor"+x, tile);
			if (zGetVarByIndex("tiles", "searched", neighbor) == 0) {
				zSetVarByIndex("tiles", "searched", neighbor, 1);
				unit = zGetVarByIndex("tiles", "occupant", neighbor);
				if (unit > 0) {
					if (mGetVar(unit, "player") == p) {
						push = modularCounterNext("lightningPush");
						trQuestVarSet("lightning"+push, unit);
						trQuestVarSet("lightning"+push+"damage", damage);
					} else if (HasKeyword(CONDUCTOR, mGetVar(unit, "keywords"))) {
						push = modularCounterNext("lightningPush");
						trQuestVarSet("lightning"+push, unit);
						trQuestVarSet("lightning"+push+"damage", 0);
					}
				}
			}
		}
	}
}

/*
Checks and activates guard for the targeted unit.
*/
int checkGuard(int target = 0) {
	trVectorQuestVarSet("targetPos", kbGetBlockPosition(""+target, true));
	float dist = 0;
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		dist = zDistanceToVectorSquared("allUnits", "targetPos");
		if (dist < 64 && dist > 9 &&
			mGetVarByQV("allUnits", "stunTime") == 0 &&
			mGetVarByQV("allUnits", "player") == 3 - trQuestVarGet("activePlayer") &&
			HasKeyword(GUARD, 1*mGetVarByQV("allUnits", "keywords"))) {
			trSoundPlayFN("bronzebirth.wav","1",-1,"","");
			trSoundPlayFN("militarycreate.wav","1",-1,"","");
			trUnitHighlight(2.0, true);
			int guardTile = mGetVarByQV("allUnits", "tile");
			int saveTile = mGetVar(target, "tile");
			teleportToTile(1*trQuestVarGet("allUnits"), saveTile);
			teleportToTile(target, guardTile);
			target = 1*trQuestVarGet("allUnits");
			break;
		}
	}
	refreshGuardAll();
	return(target);
}

/*
int attacker = index of attacking unit in the "allUnits" database
int target = index of the target unit in the "allUnits" database
bool first = true if the unit has Ambush keyword and activates it.
bool animate = does this attack need an animation?
*/
void startAttack(int attacker = 0, int target = 0, bool first = false, bool animate = true) {
	string db = "attacks";
	if (first) {
		db = "ambushAttacks";
	}
	trQuestVarSet("temp", attacker);
	yAddToDatabase(db, "temp");
	yAddUpdateVar(db, "target", target);
	if (animate) {
		yAddUpdateVar(db, "phase", ATTACK_START);
		yAddUpdateVar(db, "animation", ANIM_DEFAULT);
		switch(1*mGetVar(attacker, "proto"))
		{
			case kbGetProtoUnitID("Minotaur"):
			{
				/*
				Nottud's counter-attack
				*/
				if (mGetVar(attacker, "player") == 3 - trQuestVarGet("activePlayer")){
					yAddUpdateVar(db, "animation", ANIM_GORE);
				}
			}
			case kbGetProtoUnitID("Pharaoh of Osiris"):
			{
				yAddUpdateVar(db, "animation", ANIM_CHARGING);
			}
		}
	} else {
		yAddUpdateVar(db, "phase", ATTACK_DONE);
	}
}



bool spyReady() {
	return(trQuestVarGet("spyFind") == trQuestVarGet("spyFound"));
}


/*
Casts spy on the currently selected unit. The spy will transform into the specified protounit.
Returns the index of the spy eye in case the user wants to reference it later. The name of the
spy eye will be set in the quest var "spyEye"+x, where x is the integer returned by this function.
*/
int spyEffect(string proto = "") {
	int x = modularCounterNext("spyFind");
	trQuestVarSet("spyEye"+x+"proto", kbGetProtoUnitID(proto));
	trTechInvokeGodPower(0, "spy", xsVectorSet(1,1,1), xsVectorSet(1,1,1));
	return(x);
}

rule spy_find
highFrequency
active
{
	if (spyReady() == false) {
		while (yFindLatest("spyEye", "Spy Eye", 0) >= 0) {
			int x = modularCounterNext("spyFound");
			trQuestVarCopy("spyEye"+x, "spyEye");
			trMutateSelected(1*trQuestVarGet("spyEye"+x+"proto"));
			trQuestVarSet("spyTimeout", 0);
		}
		trQuestVarSet("spyTimeout", trQuestVarGet("spyTimeout") + 1);
		if (trQuestVarGet("spyTimeout") >= 5) {
			trQuestVarCopy("spyFound", "spyFind");
		}
	}
}

/*
index = index of unit in the allUnits database.
*/
void stunUnit(int index = 0) {
	if (mGetVar(index, "health") > 0) {
		mSetVar(index, "stunTime", 2);
		mSetVar(index, "action", ACTION_STUNNED);
		if (mGetVar(index, "stunSFX") == 0) {
			trUnitSelectClear();
			trUnitSelect(""+index);
			mSetVar(index, "stunIndex", spyEffect("Shockwave stun effect"));
			xsEnableRule("spy_assign_new");
		} else {
			trUnitSelectClear();
			trUnitSelect(""+1*mGetVar(index, "stunSFX"));
			trMutateSelected(kbGetProtoUnitID("Shockwave stun effect"));
		}
	}
}

/*
name = the unit name number
dir = string containing the name of a vector for the direction to be pushed
*/
void pushUnit(int name = 0, string dir = "") {
	int p = mGetVar(name, "player");
	int tile = mGetVar(name, "tile");
	int container = deployAtTile(p, "Dwarf", tile);
	zSetVarByIndex("tiles", "occupant", tile, 0);
	tileGuard(tile, false);
	refreshGuardAll();

	trUnitSelectClear();
	trUnitSelect(""+container, true);
	trSetUnitOrientation(trVectorQuestVarGet(dir), xsVectorSet(0,1,0), true);
	trMutateSelected(kbGetProtoUnitID("Hero Greek Achilles"));

	trUnitSelectClear();
	trUnitSelect(""+name);
	trUnitOverrideAnimation(24,0,1,1,-1);
	trMutateSelected(kbGetProtoUnitID("Relic"));
	trImmediateUnitGarrison(""+container);
	trMutateSelected(1*mGetVar(name, "proto"));


	/*
	Find destination
	*/
	trVectorQuestVarSet("start", kbGetBlockPosition(""+name));
	trVectorQuestVarSet("pos", kbGetBlockPosition(""+name));
	trQuestVarSet("posx", trQuestVarGet("posx") + 6.0*trQuestVarGet(dir+"x"));
	trQuestVarSet("posz", trQuestVarGet("posz") + 6.0*trQuestVarGet(dir+"z"));
	bool found = true;
	int neighbor = 0;
	int target = 0;
	while(found) {
		found = false;
		// Travel down the line and find stopping tile
		for(z=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
			neighbor = zGetVarByIndex("tiles", "neighbor"+z, tile);
			if (zGetVarByIndex("tiles", "terrain", neighbor) == 0 && neighbor < trQuestVarGet("ztilesend")) {
				trVectorQuestVarSet("current", kbGetBlockPosition(""+neighbor));
				if (zDistanceBetweenVectorsSquared("current", "pos") < 1) {
					if (zGetVarByIndex("tiles", "occupant", neighbor) > 0) {
						target = zGetVarByIndex("tiles", "occupant", neighbor);
					} else {
						tile = neighbor;
						trQuestVarSet("posx", trQuestVarGet("currentx") + 6.0*trQuestVarGet(dir+"x"));
						trQuestVarSet("posz", trQuestVarGet("currentz") + 6.0*trQuestVarGet(dir+"z"));
						found = true;
						break;
					}
				}
			}
		}
	}
	trQuestVarSet("next", container);
	yAddToDatabase("pushes", "next");
	yAddUpdateVar("pushes", "name", name);
	yAddUpdateVar("pushes", "dest", tile);
	yAddUpdateVar("pushes", "target", target);
	yAddUpdateVar("pushes", "timeout", trTimeMS() + 70 * zDistanceBetweenVectors("start", "pos"));
	trUnitSelectClear();
	trUnitSelect(""+tile);
	trSetUnitOrientation(trVectorQuestVarGet(dir), xsVectorSet(0,1,0), true);
	trUnitSelectClear();
	trUnitSelect(""+container);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trUnitMoveToVector("pos", false);
}



/*
target = the unit that is being upgraded
unit = the unit being magnetized and consumed
*/
void magnetize(int target = 0, int unit = 0) {
	deployAtTile(0, "Fireball Launch Damage Effect", 1*mGetVar(unit, "tile"));
	trUnitSelectClear();
	trUnitSelect(""+unit);
	trMutateSelected(kbGetProtoUnitID("Victory Marker"));
	zSetVarByIndex("tiles", "occupant", 1*mGetVar(unit, "tile"), 0);
	tileGuard(1*mGetVar(unit, "tile"), false);
	mSetVar(target, "health", mGetVar(target, "health") + mGetVar(unit, "health"));
	mSetVar(target, "attack", mGetVar(target, "attack") + mGetVar(unit, "attack"));
	trQuestVarSet("keywords1", mGetVar(target, "keywords"));
	trQuestVarSet("keywords2", mGetVar(unit, "keywords"));
	int keywords = 0;
	int current = xsPow(2, NUM_KEYWORDS - 1);
	for(x=NUM_KEYWORDS - 1; >=0) {
		if (trQuestVarGet("keywords1") >= current || trQuestVarGet("keywords2") >= current) {
			keywords = keywords + current;
			if (trQuestVarGet("keywords1") >= current) {
				trQuestVarSet("keywords1", trQuestVarGet("keywords1") - current);
			}
			if (trQuestVarGet("keywords2") >= current) {
				trQuestVarSet("keywords2", trQuestVarGet("keywords2") - current);
			}
		}
		current = current / 2;
	}
	mSetVar(target, "keywords", keywords);
	mSetVar(target, "scale", mGetVar(target, "scale") + 0.25 * mGetVar(unit, "health"));
	scaleUnit(target);
	if (HasKeyword(CHARGE, 1*mGetVar(target, "keywords")) && mGetVar(target, "action") == ACTION_SLEEPING) {
		mSetVar(target, "action", ACTION_READY);
	}
}

void updateRoxasHealth(int p = 0) {
	if (trQuestVarGet("p"+p+"commanderType") == COMMANDER_ROXAS) {
		int diff = trQuestVarGet("p"+p+"roxasHealth") - yGetDatabaseCount("p"+p+"deck");
		trQuestVarSet("p"+p+"roxasHealth", yGetDatabaseCount("p"+p+"deck"));
		damageUnit(1*trQuestVarGet("p"+p+"commander"), diff);
	}
}

void updateAuras() {
	int card = 0;
	for(p=2; >0) {
		trQuestVarSet("p"+p+"spellDamage", trCountUnitsInArea("128",p,"Oracle Scout",45));
		trQuestVarSet("p"+p+"spellDiscount", trCountUnitsInArea("128",p,"Priest",45) - trCountUnitsInArea("128",3-p,"Argus",45));
		trQuestVarSet("p"+p+"minionDiscount", trCountUnitsInArea("128",p,"Throwing Axeman",45));
		if (trQuestVarGet("p"+p+"guardianOfTheSea") == 0) {
			if (trCountUnitsInArea("128",p,"Trident Soldier Hero", 45) > 0) {
				mSetVarByQV("p"+p+"commander", "keywords", SetBit(1*mGetVarByQV("p"+p+"commander", "keywords"), GUARD));
			} else {
				mSetVarByQV("p"+p+"commander", "keywords", ClearBit(1*mGetVarByQV("p"+p+"commander", "keywords"), GUARD));
			}
		}
		if (trCountUnitsInArea("128",p,"Hero Greek Polyphemus", 45) > 0) {
			mSetVarByQV("p"+p+"commander", "keywords", SetBit(1*mGetVarByQV("p"+p+"commander", "keywords"), FURIOUS));
		} else {
			mSetVarByQV("p"+p+"commander", "keywords", ClearBit(1*mGetVarByQV("p"+p+"commander", "keywords"), FURIOUS));
		}

		/*
		Scylla discounts
		*/
		if (trCountUnitsInArea("128", p, "Heka Gigantes", 45) > 0) {
			for (x=yGetDatabaseCount("p"+p+"hand"); >0) {
				yDatabaseNext("p"+p+"hand");
				if (mGetVarByQV("p"+p+"hand", "spell") == SPELL_NONE) {
					mSetVarByQV("p"+p+"hand", "keywords", SetBit(1*mGetVarByQV("p"+p+"hand", "keywords"), OVERFLOW));
				}
			}
		} else {
			for (x=yGetDatabaseCount("p"+p+"hand"); >0) {
				yDatabaseNext("p"+p+"hand");
				if (mGetVarByQV("p"+p+"hand", "spell") == SPELL_NONE) {
					card = mGetVarByQV("p"+p+"hand", "proto");
					if (HasKeyword(OVERFLOW, 1*trQuestVarGet("card_"+card+"_keywords")) == false) {
						mSetVarByQV("p"+p+"hand", "keywords", ClearBit(1*mGetVarByQV("p"+p+"hand", "keywords"), OVERFLOW));
					}
				}
			}
		}
		updateRoxasHealth(p);
	}
	refreshGuardAll();
}

rule resolve_pushes
highFrequency
active
{
	if (yGetDatabaseCount("pushes") > 0) {
		int unit = yDatabaseNext("pushes");
		trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVar("pushes", "dest")));
		if (zDistanceToVectorSquared("pushes", "pos") < 4 || trTimeMS() > yGetVar("pushes", "timeout")) {
			trUnitSelectClear();
			trUnitSelect(""+1*yGetVar("pushes", "name"));
			trUnitChangeProtoUnit("Dwarf");
			trUnitSelectClear();
			trUnitSelect(""+unit);
			trUnitChangeProtoUnit("Dust Large");
			teleportToTile(1*yGetVar("pushes", "name"), 1*yGetVar("pushes", "dest"));
			if (yGetVar("pushes", "target") > 0) {
				startAttack(1*yGetVar("pushes", "name"), 1*yGetVar("pushes", "target"), false, false);
				startAttack(1*yGetVar("pushes", "target"), 1*yGetVar("pushes", "name"), false, false);
			}
			yRemoveFromDatabase("pushes");
			yRemoveUpdateVar("pushes", "name");
			yRemoveUpdateVar("pushes", "dest");
			yRemoveUpdateVar("pushes", "target");
			yRemoveUpdateVar("pushes", "timeout");
		}
	}
}

rule spy_assign_new
highFrequency
inactive
{
	if (spyReady())	{
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if ((mGetVarByQV("allUnits", "stunSFX") == 0) && (mGetVarByQV("allUnits", "stunIndex") > 0)) {
				mSetVarByQV("allUnits", "stunSFX", trQuestVarGet("spyEye"+1*mGetVarByQV("allUnits", "stunIndex")));
			}
		}
		xsDisableRule("spy_assign_new");
	}
}

rule recycle_dead_cards
highFrequency
active
{
	int unit = zBankNext("allUnitsBank");
	trUnitSelectClear();
	trUnitSelect(""+unit);
	switch(1*zGetVar("allUnitsBank", "state"))
	{
		case STATE_ALIVE:
		{
			if (trUnitAlive() == false) {
				zSetVar("allUnitsBank", "state", STATE_DEAD);
				if (kbProtoUnitIsUnitType(1*mGetVar(unit, "proto"), 937)) {
					zSetVar("allUnitsBank", "next", trTimeMS() + 300);
				} else {
					zSetVar("allUnitsBank", "next", trTimeMS() + 2000);
				}
			}
		}
		case STATE_DEAD:
		{
			if (trTimeMS() > zGetVar("allUnitsBank", "next")) {
				trDamageUnitPercent(-100);
				trUnitChangeProtoUnit("Automaton");
				trUnitSelectClear();
				trUnitSelect(""+unit);
				trDamageUnitPercent(-100);
				trUnitChangeProtoUnit("Victory Marker");
				trUnitSelectClear();
				trUnitSelect(""+unit);
				if (trUnitAlive() == true) {
					zSetVar("allUnitsBank", "state", STATE_ALIVE);
					mSetVarByQV("allUnitsBank", "played", 0);
				}
			}
		}
	}
}