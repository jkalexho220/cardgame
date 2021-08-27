bool OnTurnStart(int unit = 0) {
	int p = mGetVar(unit, "player");
	int proto = mGetVar(unit, "proto");
	switch(proto)
	{
		case kbGetProtoUnitID("Phoenix Egg"):
		{
			damageUnit(unit, 1*mGetVar(unit, "health"));
			deathSummonQueue(1*mGetVar(unit, "tile"), p, "Phoenix From Egg");
			return (true);
		}
		case kbGetProtoUnitID("Hero Greek Chiron"):
		{
			trQuestVarSet("p1drawCards", 1 + trQuestVarGet("p1drawCards"));
			trQuestVarSet("p2drawCards", 1 + trQuestVarGet("p2drawCards"));
		}
		case kbGetProtoUnitID("Pirate Ship"):
		{
			if(trQuestVarGet("pirateShipTarget") > -1){
				
			}
			yClearDatabase("pirateShipTargets");	
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits", true);
				if(mGetVarByQV("allUnits", "player") == 3 - p){
					yAddToDatabase("pirateShipTargets", "allUnits");	
				}
			}
			trQuestVarSetFromRand("pirateShipRandom", 1, yGetDatabaseCount("pirateShipTargets"), true);
			for(x=trQuestVarGet("pirateShipRandom"); >0) {
				yDatabaseNext("pirateShipTargets");
			}
			trQuestVarSet("pirateShipTarget", trQuestVarGet("pirateShipTargets"));
			return (true);
		}
		case kbGetProtoUnitID("Monument"):
		{
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits", true);
				if(trUnitPercentDamaged() > 0 && mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER){
					damageUnit(1*trQuestVarGet("allUnits"), 1);
					deployAtTile(0, "Dust Small", 1*mGetVarByQV("allUnits", "tile"));
					trQuestVarSetFromRand("soundRandom", 1, 2, true);
					trSoundPlayFN("farming" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
				}
			}
			return (true);
		}
		case kbGetProtoUnitID("Monument 2"):
		{
			healUnit(1*trQuestVarGet("p"+p+"commander"), 5);
			deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
			trSoundPlayFN("heal.wav","1",-1,"","");
			return (true);
		}
		case kbGetProtoUnitID("Monument 3"):
		{
			healUnit(1*trQuestVarGet("p"+p+"commander"), 5);
			deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
			trSoundPlayFN("heal.wav","1",-1,"","");
			return (true);
		}
		case kbGetProtoUnitID("Monument 4"):
		{
			healUnit(1*trQuestVarGet("p"+p+"commander"), 5);
			deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
			trSoundPlayFN("heal.wav","1",-1,"","");
			return (true);
		}
		case kbGetProtoUnitID("Monument 5"):
		{
			healUnit(1*trQuestVarGet("p"+p+"commander"), 5);
			deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
			trSoundPlayFN("heal.wav","1",-1,"","");
			return (true);
		}
	}
	return (false);
}