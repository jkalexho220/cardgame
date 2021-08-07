bool OnDeath(int event = -1, int unit = 0){
	int p = mGetVar(unit, "player");
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
		case DEATH_SPELL_DISCOUNT:
		{
			trQuestVarSet("p"+p+"spellDiscount", trQuestVarGet("p"+p+"spellDiscount") - 1);
		}
		case DEATH_SPELL_DAMAGE:
		{
			trQuestVarSet("p"+p+"spellDamage", trQuestVarGet("p"+p+"spellDamage") - 1);
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
			mSetVarByQV("allUnits", "health", -9999);	
			removeUnit("allUnits");
		}
	}
}