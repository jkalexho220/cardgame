void OnPlay(int unit = 0, int event = 0) {
	int p = mGetVar(unit, "player");
	bool done = true;
	switch(event)
	{
		case PLAY_GET_SPARK:
		{
			addCardToHand(p, kbGetProtoUnitID("Statue of Lightning"), SPELL_SPARK);
			updateHandPlayable(p);
		}
		case PLAY_GET_TRAP:
		{
			addCardToHand(p, kbGetProtoUnitID("Petrobolos"));
			updateHandPlayable(p);
		}
		case PLAY_FOOD:
		{
			done = false;
			chooseSpell(SPELL_FOOD);
		}
		case PLAY_DOUBLEBLADE:
		{
			trUnitSelectClear();
			trUnitSelect(""+unit, true);
			trMutateSelected(kbGetProtoUnitID("Avenger"));
			trUnitOverrideAnimation(39, 0, 0, 1, -1);
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*mGetVar(unit, "tile")));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (mGetVarByQV("allUnits", "player") == 3 - p) {
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						damageUnit(1*trQuestVarGet("allUnits"), 1);
						deployAtTile(0, "Lightning sparks", 1*mGetVarByQV("allUnits", "tile"));
					}
				}
			}
			trSoundPlayFN("sphinxspecialattack.wav","1",-1,"","");
		}
		case PLAY_LEGENDARY:
		{
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("lightningbirth.wav","1",-1,"","");
		}
	}
	if (done) {
		removeDeadUnits();
		xsEnableRule("gameplay_01_select");
		highlightReady(999999);
	}
}