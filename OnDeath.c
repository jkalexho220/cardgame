bool deathSummonQueue(int tile = 0, int p = 0, string proto = "") {
	int push = modularCounterNext("deathSummonPush");
	trQuestVarSet("deathSummon"+push+"proto", kbGetProtoUnitID(proto));
	trQuestVarSet("deathSummon"+push+"player", p);
	trQuestVarSet("deathSummon"+push+"tile", tile);
}

bool OnDeath(int event = -1, int unit = 0){
	int p = mGetVar(unit, "player");
	int count = 0;
	int target = 0;
	int tile = 0;
	bool checkAgain = false;
	switch(event)
	{
		case DEATH_DRAW_CARD:
		{
			drawCard(p);
		}
		case DEATH_OPPONENT_DRAW_CARD:
		{
			drawCard(3-p);
		}
		case DEATH_EGG:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Phoenix Egg");
		}
		case DEATH_GET_ARCANE:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				trQuestVarSetFromRand("spellChosen", SPELL_SPARK, SPELL_APOCALYPSE, true);
				addCardToHand(p, 0, 1*trQuestVarGet("spellChosen"), false);
				updateHandPlayable(p);
			}
		}
		case DEATH_SUMMON_ZOMBIE:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Minion");
		}
		case DEATH_SUMMON_SHADOW:
		{
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Shade of Hades");
		}
		case DEATH_POISON_MIST:
		{
			for(x=0; < zGetVarByIndex("tiles", "neighborCount", 1*mGetVar(unit, "tile"))) {
				tile = zGetVarByIndex("tiles", "neighbor"+x, 1*mGetVar(unit, "tile"));
				target = zGetVarByIndex("tiles", "occupant", tile);
				if (target > 0) {
					if (mGetVar(target, "spell") == SPELL_NONE) {
						mSetVar(target, "keywords", SetBit(1*mGetVar(target, "keywords"), DECAY));
					}
				}
			}
			deployAtTile(0, "Lampades Blood", 1*mGetVar(unit, "tile"));
			trSoundPlayFN("lampadesblood.wav","1",-1,"","");
			trSoundPlayFN("carnivorabirth.wav","1",-1,"","");
		}
		case DEATH_DARKNESS_RETURNS:
		{
			addCardToDeck(p, "Guardian");
			trSoundPlayFN("cinematics\32_out\kronosbehinddorrshort.mp3","1",-1,"","");
			deployAtTile(0, "Kronny Birth SFX", 1*mGetVar(unit, "tile"));
		}
		case DEATH_GET_ATTACK:
		{
			trQuestVarSet("p"+p+"yeebBonus", 1 + trQuestVarGet("p"+p+"yeebBonus"));
			mSetVarByQV("p"+p+"commander", "attack", 1 + mGetVarByQV("p"+p+"commander", "attack"));
			deployAtTile(0, "Hero Birth", 1*mGetVarByQV("p"+p+"commander", "tile"));
		}
		/*
		case DEATH_BOOM_SMALL:
		{
			deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVar("allUnits", "tile")));
			yDatabasePointerDefault("allUnits");
			for(y=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (zDistanceToVectorSquared("allUnits", "pos") > 2) { // yGetVar("allUnits", "player") == 3 - p
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 2);
						checkAgain = true;
						deployAtTile(0, "Ball of Fire impact", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("meteorsmallhit.wav","1",-1,"","");
		}
		*/
	}
	return (checkAgain);
}

void removeDeadUnits() {
	bool checkAgain = true;
	int pointer = 0;
	int p = 0;
	while(checkAgain){
		checkAgain = false;
		yDatabasePointerDefault("allUnits");
		for(y=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (mGetVarByQV("allUnits", "health") <= 0 && mGetVarByQV("allUnits", "OnDeath") > 0) {
				pointer = yGetPointer("allUnits");
				/*
				OnDeath events.
				*/
				int events = 1*mGetVarByQV("allUnits", "OnDeath");
				mSetVarByQV("allUnits", "OnDeath", 0);	
				int n = 1*xsPow(2, DEATH_EVENT_COUNT - 1);	
				for(x=DEATH_EVENT_COUNT - 1; >=0) {
					if (events >= n) {							
						checkAgain = OnDeath(x, 1*trQuestVarGet("allUnits")) || checkAgain;
						events = events - n;
					}
					n = n / 2;
				}
				ySetPointer("allUnits", pointer);
			}
		}
	}
	trQuestVarSet("p1deathCount", 0);
	trQuestVarSet("p2deathCount", 0);
	yDatabasePointerDefault("allUnits");
	for(y=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		if (mGetVarByQV("allUnits", "health") <= 0 && mGetVarByQV("allUnits", "health") > -9000) {
			int tile = mGetVarByQV("allUnits", "tile");
			zSetVarByIndex("tiles", "occupant", tile, 0);
			trDamageUnitPercent(100);
			if (HasKeyword(GUARD, 1*mGetVarByQV("allUnits", "keywords"))) {
				tileGuard(tile, false);
			}
			p = mGetVarByQV("allUnits", "player");
			trQuestVarSet("p"+p+"deathCount", 1 + trQuestVarGet("p"+p+"deathCount"));
			mSetVarByQV("allUnits", "health", -9999);	
			yRemoveFromDatabase("allUnits");
		}
	}

	for (x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		switch(1*mGetVarByQV("allUnits", "proto"))
		{
			case kbGetProtoUnitID("Einheriar"):
			{
				p = mGetVarByQV("allUnits","player");
				mSetVarByQV("allUnits", "attack", trQuestVarGet("p"+p+"deathCount") + mGetVarByQV("allUnits", "attack"));
				mSetVarByQV("allUnits", "health", trQuestVarGet("p"+p+"deathCount") + mGetVarByQV("allUnits", "health"));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("allUnits"));
				spyEffect("Einheriar Boost SFX");
			}
		}
	}

	/* 
	summon units from deathrattles on a first-come-first-served basis
	If multiple summons conflict on the same tile, the first one gets it.
	*/
	int pop = 0;
	int unit = 0;
	while ((trQuestVarGet("deathSummonPush") == trQuestVarGet("deathSummonPop")) == false) {
		pop = modularCounterNext("deathSummonPop");
		if (zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("deathSummon"+pop+"tile")) == 0) {
			unit = summonAtTile(1*trQuestVarGet("deathSummon"+pop+"tile"), 
				1*trQuestVarGet("deathSummon"+pop+"player"), 
				1*trQuestVarGet("deathSummon"+pop+"proto"));
			if (HasKeyword(CHARGE, 1*mGetVar(unit, "keywords"))) {
				mSetVar(unit, "action", ACTION_READY);
			} else {
				mSetVar(unit, "action", ACTION_SLEEPING);
			}
		}
	}
	updateAuras();
}



void returnToHand(int unit = 0) {
	int p = mGetVar(unit, "player");
	int proto = mGetVar(unit, "proto");
	zSetVarByIndex("tiles", "occupant", 1*mGetVar(unit, "tile"), 0);
	if (HasKeyword(GUARD, 1*mGetVar(unit, "keywords"))) {
		tileGuard(1*mGetVar(unit, "tile"), false);
	}
	deployAtTile(0, "Hero Death", 1*mGetVar(unit, "tile"));
	if (yGetDatabaseCount("p"+p+"hand") < 10) {
		ChatLog(p, trStringQuestVarGet("card_" + proto + "_Name") + " returned to hand.");
		for(x=yGetDatabaseCount("allUnits"); >0) {
			if (yDatabaseNext("allUnits") == unit) {
				yRemoveFromDatabase("allUnits");
				break;
			}
		}
		trSoundPlayFN("hitpointsmax.wav","1",-1,"","");
		trUnitSelectClear();
		trUnitSelect(""+unit);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		mSetVar(unit, "played", 0);
		addCardToHand(p, proto, 0, false);
		updateAuras();
		updateHandPlayable();
	} else {
		trSoundPlayFN("cantdothat.wav","1",-1,"","");
		ChatLog(p, "Hand full! Burned " + trStringQuestVarGet("card_" + proto + "_Name"));
		mSetVar(unit, "health", 0);
		damageUnit(unit, 999);
		removeDeadUnits();
	}
}