void OnPlay(int unit = 0, int event = 0) {
	int p = yGetVarByIndex("allUnits", "player", unit);
	trChatSend(0, "Index: " + unit + " Player: " + p);
	bool done = true;
	switch(event)
	{
		case PLAY_GET_SPARK:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				addCardToHand(p, kbGetProtoUnitID("Statue of Lightning"), SPELL_SPARK);
				updateHandPlayable(p);
			}
		}
		case PLAY_GET_TRAP:
		{
			if (yGetDatabaseCount("p"+p+"hand") < 10) {
				addCardToHand(p, kbGetProtoUnitID("Petrobolos"));
				updateHandPlayable(p);
			}
		}
		case PLAY_FOOD:
		{
			done = false;
			chooseSpell(SPELL_FOOD);
		}
		case PLAY_DOUBLEBLADE:
		{
			trUnitSelectClear();
			trUnitSelect(""+1*yGetUnitAtIndex("allUnits", unit), true);
			trMutateSelected(kbGetProtoUnitID("Avenger"));
			trUnitOverrideAnimation(39, 0, 0, 1, -1);
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*yGetVarByIndex("allUnits", "tile", unit)));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
					if (yGetVar("allUnits", "player") == 3 - p) {
						damageUnit("allUnits", 1*yGetPointer("allUnits"), 1);
						deployAtTile(0, "Lightning sparks", 1*yGetVar("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("sphinxspecialattack.wav","1",-1,"","");
		}
	}
	if (done) {
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits", true);
			removeIfDead("allUnits");
		}
		xsEnableRule("gameplay_01_select");
		highlightReady(100);
	}
}