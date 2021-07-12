void OnDeath(int unit = 0, int event = 0) {
	int p = yGetVarByIndex("allUnits", "player", unit);
	switch(event)
	{
		case DEATH_DRAW_CARD:
		{
			drawCard(p);
		}
		case DEATH_BOOM_SMALL:
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", unit)));
			DeploySober("Meteor Impact Ground", "pos");
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (true || yGetVar("allUnits", "player") == 3 - p) {
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 2);
						deployAtTile(0, "Ball of Fire impact", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("meteorsmallhit.wav","1",-1,"","");
		}
		case DEATH_BOOM_MEDIUM:
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", unit)));
			DeploySober("Meteor", "pos");
			DeploySober("Meteor Impact Ground", "pos");
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (true || yGetVar("allUnits", "player") == 3 - p) {
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 4);
						deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
					} else if (zDistanceToVectorSquared("allUnits", "pos") < 128) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 2);
						deployAtTile(0, "Ball of Fire impact", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("meteorbighit.wav","1",-1,"","");
			trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
		}
		case DEATH_BOOM_BIG:
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", unit)));
			DeploySober("Meteor", "pos");
			DeploySober("Meteor Impact Ground", "pos");
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (true || yGetVar("allUnits", "player") == 3 - p) {
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 6);
						deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
					} else if (zDistanceToVectorSquared("allUnits", "pos") < 128) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 4);
						deployAtTile(0, "Meteor Impact Ground", 1*yGetVar("allUnits", "tile"));
					} else if (zDistanceToVectorSquared("allUnits", "pos") < 256) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 2);
						deployAtTile(0, "Ball of Fire impact", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			zSetVarByIndex("tiles", "occupied", 1*yGetVarByIndex("allUnits", "tile", unit), TILE_IMPASSABLE);
			trSoundPlayFN("implodeexplode.wav","1",-1,"","");
			trSoundPlayFN("meteorbighit.wav","1",-1,"","");
			trSoundPlayFN("meteordustcloud.wav","1",-1,"","");
		}
	}
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		removeIfDead("allUnits");
	}
	xsEnableRule("gameplay_01_select");
	highlightReady(100);
}