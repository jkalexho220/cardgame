void OnPlay(int unit = 0) {
	int p = mGetVar(unit, "player");
	int proto = mGetVar(unit, "proto");
	bool done = true;
	switch(proto)
	{
		case kbGetProtoUnitID("Slinger"):
		{
			addCardToHand(p, kbGetProtoUnitID("Statue of Lightning"), SPELL_SPARK);
			updateHandPlayable(p);
		}
		case kbGetProtoUnitID("Skraeling"):
		{
			if (trCurrentPlayer() == p) {
				trMessageSetText("Choose a tile to summon a Loyal Wolf.", -1);
			}
			trQuestVarSet("summonedUnit", unit);
			chooseSpell(SPELL_WOLF);
			done = false;
		}
		case kbGetProtoUnitID("Villager Atlantean"):
		{
			done = false;
			chooseSpell(SPELL_FOOD);
			if (trCurrentPlayer() == p) {
				trMessageSetText("Choose an allied minion to grant +1 attack and health to.", -1);
			}
		}
		case kbGetProtoUnitID("Avenger"):
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
		case kbGetProtoUnitID("Hero Greek Hippolyta"):
		{
			trSoundPlayFN("herocreation.wav","1",-1,"","");
			trSoundPlayFN("lightningbirth.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Hetairoi"):
		{
			addCardToHand(p, kbGetProtoUnitID("Statue of Lightning"), SPELL_MAP);
			updateHandPlayable(p);
		}
		case kbGetProtoUnitID("Peltast"):
		{
			done = false;
			chooseSpell(SPELL_PING);
			if (trCurrentPlayer() == p) {
				trMessageSetText("Choose an enemy to deal 1 damage to.", -1);
			}
		}
		case kbGetProtoUnitID("Huskarl"):
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*mGetVar(unit, "tile")));
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (trQuestVarGet("allUnits") == unit) {
					continue;
				} else if ((mGetVarByQV("allUnits", "player") == p) && (mGetVarByQV("allUnits", "spell") == 0)) {
					if (zDistanceToVectorSquared("allUnits", "pos") < 64) {
						deployAtTile(0, "Hero Birth", 1*mGetVarByQV("allUnits", "tile"));
						mSetVarByQV("allUnits", "attack", 1 + mGetVarByQV("allUnits", "attack"));
						mSetVarByQV("allUnits", "health", 1 + mGetVarByQV("allUnits", "health"));
						trUnitSelectClear();
						trUnitSelect(""+1*trQuestVarGet("allUnits"), true);
						spyEffect("Einheriar Boost SFX");
					}
				}
			}
			trSoundPlayFN("researchcomplete.wav","1",-1,"","");
			trSoundPlayFN("battlecry3.wav","1",-1,"","");
		}
		case kbGetProtoUnitID("Nemean Lion"):
		{
			trUnitSelectClear();
			trUnitSelect(""+unit, true);
			trMutateSelected(kbGetProtoUnitID("Nemean Lion"));
			trUnitOverrideAnimation(39, 0, 0, 1, -1);
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits");
				if (mGetVarByQV("allUnits", "player") == 3 - p) {
					if ((trQuestVarGet("p"+p+"manaflow") >= mGetVarByQV("allUnits", "cost")) &&
						(mGetVarByQV("allUnits", "spell") == 0)) {
						stunUnit(1*trQuestVarGet("allUnits"));
					}
				}
			}
		}
		case kbGetProtoUnitID("Priest"):
		{
			trQuestVarSet("p"+p+"spellDiscount", 1 + trQuestVarGet("p"+p+"spellDiscount"));
		}
		case kbGetProtoUnitID("Oracle Scout"):
		{
			trQuestVarSet("p"+p+"spellDamage", 1 + trQuestVarGet("p"+p+"spellDamage"));
		}
	}
	if (done) {
		removeDeadUnits();
		xsEnableRule("gameplay_01_select");
		highlightReady(999999);
	}
}