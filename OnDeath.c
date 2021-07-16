bool OnDeath(int event = -1){
	int savePointer = yGetPointer("allUnits");	
	int p = yGetVar("allUnits", "player");
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
		case DEATH_BOOM_MEDIUM:
		{
			deployAtTile(0, "Meteor", 1*yGetVar("allUnits", "tile"));
			deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVar("allUnits", "tile")));
			yDatabasePointerDefault("allUnits");
			for(y=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (zDistanceToVectorSquared("allUnits", "pos") > 2) { // yGetVar("allUnits", "player") == 3 - p
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
			deployAtTile(0, "Meteor", 1*yGetVar("allUnits", "tile"));
			deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
			zSetVarByIndex("tiles", "occupied", 1*yGetVar("allUnits", "tile"), TILE_IMPASSABLE);
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVar("allUnits", "tile")));
			yDatabasePointerDefault("allUnits");
			for(y=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (zDistanceToVectorSquared("allUnits", "pos") > 2) { // yGetVar("allUnits", "player") == 3 - p
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
			trSoundPlayFN("implodeexplode.wav","1",-1,"","");
			trSoundPlayFN("meteorbighit.wav","1",-1,"","");
			trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
		}
	}
	ySetPointer("allUnits", savePointer);
	return (checkAgain);
}

void removeDeadUnits() {
	int savePointer = yGetPointer("allUnits");
	bool checkAgain = true;
	while(checkAgain){
		checkAgain = false;
		yDatabasePointerDefault("allUnits");
		for(y=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits");
			if (yGetVar("allUnits", "health") <= 0 && yGetVar("allUnits", "OnDeath") > 0) {
				/*
				OnDeath events.
				*/
				int events = 1*yGetVar("allUnits", "OnDeath");
				ySetVar("allUnits", "OnDeath", 0);	
				int n = 1*xsPow(2, DEATH_EVENT_COUNT - 1);	
				for(x=DEATH_EVENT_COUNT - 1; >=0) {
					if (events >= n) {							
						if(OnDeath(x)){
							checkAgain = true;
						}
						events = events - n;
					}
					n = n / 2;
				}			
			}
		}
	}
	yDatabasePointerDefault("allUnits");
	for(y=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits");
		if (yGetVar("allUnits", "health") <= 0 && yGetVar("allUnits", "health") > -9000) {
			int tile = yGetVar("allUnits", "tile");
			zSetVarByIndex("tiles", "occupied", tile, xsMax(TILE_EMPTY, zGetVarByIndex("tiles", "terrain", tile)));
			trDamageUnitPercent(100);
			if (HasKeyword(GUARD, 1*yGetVar("allUnits", "keywords"))) {
				tileGuard(tile, false);
			}
			ySetVar("allUnits", "health", -9999);	
			removeUnit("allUnits");
		}
	}
	ySetPointer("allUnits", savePointer);
}