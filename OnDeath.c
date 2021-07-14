bool OnDeath(int index = -1, int event = -1){
	int p = yGetVarByIndex("allUnits", "player", index);
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
		case DEATH_BOOM_SMALL:
		{
			deployAtTile(0, "Meteor Impact Ground", 1*yGetVarByIndex("allUnits", "tile", index));
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", index)));
			for(y=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (yGetPointer("allUnits") != index) { // yGetVar("allUnits", "player") == 3 - p
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 2);
						checkAgain = true;
						deployAtTile(0, "Ball of Fire impact", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("meteorsmallhit.wav","1",-1,"","");
		}
		case DEATH_BOOM_MEDIUM:
		{
			deployAtTile(0, "Meteor", 1*yGetVarByIndex("allUnits", "tile", index));
			deployAtTile(0, "Meteor Impact Ground", 1*yGetVarByIndex("allUnits", "tile", index));
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", index)));
			for(y=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (yGetPointer("allUnits") != index) { // yGetVar("allUnits", "player") == 3 - p
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 4);
						checkAgain = true;
						deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
					} else if (zDistanceToVectorSquared("allUnits", "pos") < 196) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 2);
						checkAgain = true;
						deployAtTile(0, "Ball of Fire impact", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("meteorbighit.wav","1",-1,"","");
			trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
		}
		case DEATH_BOOM_BIG:
		{
			deployAtTile(0, "Meteor", 1*yGetVarByIndex("allUnits", "tile", index));
			deployAtTile(0, "Meteor Impact Ground", 1*yGetVarByIndex("allUnits", "tile", index));
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", index)));
			for(y=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (yGetPointer("allUnits") != index) { // yGetVar("allUnits", "player") == 3 - p
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 6);
						checkAgain = true;
						deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
					} else if (zDistanceToVectorSquared("allUnits", "pos") < 196) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 4);
						checkAgain = true;
						deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
					} else if (zDistanceToVectorSquared("allUnits", "pos") < 400) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 2);
						checkAgain = true;
						deployAtTile(0, "Ball of Fire impact", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			zSetVarByIndex("tiles", "occupied", 1*yGetVarByIndex("allUnits", "tile", index), TILE_IMPASSABLE);
			trSoundPlayFN("implodeexplode.wav","1",-1,"","");
			trSoundPlayFN("meteorbighit.wav","1",-1,"","");
			trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
		}
	}
	if(checkAgain){
		xsEnableRule("DelayedDeathCheck");
	} else {
		xsEnableRule("gameplay_01_select");
		highlightReady(100);
	}
	return (checkAgain);
}

bool removeIfDead(string db = "", int index = -1) {
	
	bool checkAgain = false;
	if (index >= 0) {
		ySetPointer(db, index);
	} else {
		index = yGetPointer(db);
	}
	if (yGetVar(db, "health") <= 0) {
		int tile = yGetVar(db, "tile");
		zSetVarByIndex("tiles", "occupied", tile, xsMax(TILE_EMPTY, zGetVarByIndex("tiles", "terrain", tile)));
		trDamageUnitPercent(100);
		if (HasKeyword(GUARD, 1*yGetVar(db, "keywords"))) {
			tileGuard(tile, false);
		}
		
		/*
		On-attack events.
		*/
		int n = 1*xsPow(2, DEATH_EVENT_COUNT - 1);	
		int events = 1*yGetVar(db, "OnDeath");
		for(x=DEATH_EVENT_COUNT - 1; >=0) {
			if (events >= n) {		
				if(OnDeath(index, x)){
					checkAgain = true;
				}
				events = events - n;
			}
		n = n / 2;
		}	

		removeUnit(db);
	}
	return (checkAgain);
}


rule DelayedDeathCheck
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		bool finalCheck = true;
		yDatabasePointerDefault("allUnits");
		for(y=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if(removeIfDead("allUnits")){
				finalCheck = false;
			}
		}
		if(finalCheck){
			xsEnableRule("gameplay_01_select");
			highlightReady(100);
		}
		xsDisableRule("DelayedDeathCheck");
	}
}