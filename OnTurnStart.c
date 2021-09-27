bool OnTurnStart(int unit = 0) {
	int p = mGetVar(unit, "player");
	int proto = mGetVar(unit, "proto");
	int tile = 0;
	int target = 0;
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
			return (true);
		}
		case kbGetProtoUnitID("Theocrat"):
		{
			drawCard(p, true);
			return (true);
		}
		case kbGetProtoUnitID("Fire Siphon"):
		{
			trQuestVarSet("dirx", mGetVar(unit, "laserDirx"));
			trQuestVarSet("dirz", mGetVar(unit, "laserDirz"));
			trUnitSelectClear();
			trUnitSelect(""+unit);
			trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
			trSoundPlayFN("sky passage.wav","1",-1,"","");
			trQuestVarSet("next", deployAtTile(0, "Dwarf", 1*mGetVar(unit, "tile")));
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("next"), true);
			trUnitHighlight(1.0, false);
			trSetSelectedScale(10, 0, 60);
			trSetUnitOrientation(xsVectorSet(0.0 - trQuestVarGet("dirx"), 0, 0.0 - trQuestVarGet("dirz")), xsVectorSet(0,1,0), true);
			trMutateSelected(kbGetProtoUnitID("Petosuchus Projectile"));
			yAddToDatabase("directionalLasers", "next");
			yAddUpdateVar("directionalLasers", "timeout", trTimeMS() + 500);
			xsEnableRule("directional_lasers");

			bool found = true;
			tile = mGetVar(unit, "tile");
			while (found) {
				found = false;
				trVectorQuestVarSet("pos", kbGetBlockPosition(""+tile));
				trQuestVarSet("posx", trQuestVarGet("posx") + trQuestVarGet("dirx") * 6);
				trQuestVarSet("posz", trQuestVarGet("posz") + trQuestVarGet("dirz") * 6);
				for(x=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
					trVectorQuestVarSet("current", kbGetBlockPosition(""+1*zGetVarByIndex("tiles", "neighbor"+x, tile)));
					if (zDistanceBetweenVectorsSquared("current", "pos") < 9) {
						found = true;
						tile = zGetVarByIndex("tiles", "neighbor"+x, tile);
						break;
					}
				}
				if (found) {
					target = zGetVarByIndex("tiles", "occupant", tile);
					startAttack(unit, target, false, false);
				}
			}
			return (true);
		}
		case kbGetProtoUnitID("Tartarian Gate"):
		{
			target = yGetDatabaseCount("p"+p+"hand");
			drawCard(p);
			if (target < 10) {
				mSetVarByQV("next", "cost", 0);
			}
		}
		case kbGetProtoUnitID("Audrey"):
		{
			if(trQuestVarGet("maxMana") == 5){
				mSetVar(unit, "keywords", SetBit(1*mGetVar(unit, "keywords"), REGENERATE));
				trSoundPlayFN("carnivorabirth.wav","1",-1,"","");
				if(trQuestVarGet("chats_Audrey_0") == 0){
					trQuestVarSet("chats_Audrey_0", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Vora</color>: *plant noises*");
				}					
				return (true);				
			}	
		}
		case kbGetProtoUnitID("Pirate Ship"):
		{
			if(trQuestVarGet("pirateShipTarget" + unit) > -1){
				trSoundPlayFN("meteorbighit.wav","1",-1,"","");		
				deployAtTile(0, "Meteor Impact Ground", 1*trQuestVarGet("pirateShipTarget" + unit));
				int occupant = zGetVarByIndex("tiles", "occupant", 1*trQuestVarGet("pirateShipTarget" + unit));
				damageUnit(occupant, 8);
				if(occupant < 1){
					if(trQuestVarGet("chats_PirateShip_1") == 0){
						trQuestVarSet("chats_PirateShip_1", 1);
						ChatLog(0, "<color={Playercolor("+p+")}>Pirate Crew</color>: Damn, we missed!");
					}		
				} else if(1*mGetVar(occupant, "tile") == p){
					if(trQuestVarGet("chats_PirateShip_2") == 0){
						trQuestVarSet("chats_PirateShip_2", 1);
						ChatLog(0, "<color={Playercolor("+p+")}>Pirate Crew</color>: Oops! Sorry about that!");
					}					
				} else {
					if(trQuestVarGet("chats_PirateShip_3") == 0){
						trQuestVarSet("chats_PirateShip_3", 1);
						ChatLog(0, "<color={Playercolor("+p+")}>Pirate Crew</color>: We got them good!");
					}					
				}
			} else {
				if(trQuestVarGet("chats_PirateShip_4") == 0){
					trQuestVarSet("chats_PirateShip_4", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Pirate Crew</color>: Cannons be ready to fire!");
				}
			}
			yClearDatabase("pirateShipTargets");	
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits", true);
				if(mGetVarByQV("allUnits", "player") == 3 - p){
					trQuestVarSet("temp", mGetVarByQV("allUnits", "tile"));
					yAddToDatabase("pirateShipTargets", "temp");	
				}
			}
			trQuestVarSetFromRand("pirateShipRandom", 1, yGetDatabaseCount("pirateShipTargets"), true);
			for(x=trQuestVarGet("pirateShipRandom"); >0) {
				yDatabaseNext("pirateShipTargets");
			}
			trQuestVarSet("pirateShipTarget" + unit, trQuestVarGet("pirateShipTargets"));
			return (true);
		}
		case kbGetProtoUnitID("Monument"):
		{
			bool clean = false;
			for(x=yGetDatabaseCount("allUnits"); >0) {
				yDatabaseNext("allUnits", true);
				if(trUnitPercentDamaged() > 0 && mGetVarByQV("allUnits", "spell") != SPELL_COMMANDER){
					damageUnit(1*trQuestVarGet("allUnits"), 1);
					deployAtTile(0, "Dust Small", 1*mGetVarByQV("allUnits", "tile"));
					clean = true;
				}
			}
			if(clean){
				trQuestVarSetFromRand("soundRandom", 1, 3, true);
				trSoundPlayFN("farming" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
				if(trQuestVarGet("chats_Monument_1") == 0){
					trQuestVarSet("chats_Monument_1", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Floating Housekeeper</color>: Dirt detected. Cleaning.");
				}
			} else {
				if(trQuestVarGet("chats_Monument_2") == 0){
					trQuestVarSet("chats_Monument_2", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Floating Housekeeper</color>: Nothing to clean.");
				}
			}
			return (true);
		}
		case kbGetProtoUnitID("Monument 2"):
		{
			int h = mGetVarByQV("p"+p+"commander", "health");
			healUnit(1*trQuestVarGet("p"+p+"commander"), 5);
			deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
			trSoundPlayFN("heal.wav","1",-1,"","");
			if(1*mGetVarByQV("p"+p+"commander", "health") == h){
				if(trQuestVarGet("chats_Monument2_1") == 0){
					trQuestVarSet("chats_Monument2_1", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Floating Butler</color>: Exemplary outfit. Congratulations.");
				}	
			} else {
				if(trQuestVarGet("chats_Monument2_2") == 0){
					trQuestVarSet("chats_Monument2_2", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Floating Butler</color>: Outfit issues detected. Addressing.");
				}	
			}
			return (true);
		}
		case kbGetProtoUnitID("Monument 3"):
		{
			if(yGetDatabaseCount("p"+(3-p)+"hand") > 0){
				trQuestVarSetFromRand("temp", 1, yGetDatabaseCount("p"+(3-p)+"hand"), true);
				yDatabasePointerDefault("p"+(3-p)+"hand");
				for(x=trQuestVarGet("temp"); >0) {
					yDatabaseNext("p"+(3-p)+"hand", true);
				}
				//addCardToDeck(3-p, kbGetProtoUnitName(1*mGetVarByQV("p"+(3-p)+"hand", "proto")), mGetVarByQV("p"+(3-p)+"hand", "spell"));
				trQuestVarSetFromRand("soundRandom", 1, 3, true);
				trSoundPlayFN("swing" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");	
				trVectorSetUnitPos("pos", "p"+(3-p)+"hand");
				trUnitSelectClear();
				trUnitSelectByID(1*yGetVar("p"+(3-p)+"hand", "pos"));
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("p"+(3-p)+"hand"), true);
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trArmyDispatch("1,10","Dwarf",1,trQuestVarGet("posx"),0,trQuestVarGet("posz"),0, true);
				trUnitSelectClear();
				trArmySelect("1,10");
				trUnitChangeProtoUnit("Hero Death");
				if (mGetVarByQV("p"+(3-p)+"hand", "spell") == SPELL_NONE) {
					ChatLog((3-p), "Discarded " + trStringQuestVarGet("card_" + 1*mGetVarByQV("p"+(3-p)+"hand", "proto") + "_name"));
				} else {
					ChatLog((3-p), "Discarded " + trStringQuestVarGet("spell_" + 1*mGetVarByQV("p"+(3-p)+"hand", "spell") + "_name"));
				}
				zSetVarByIndex("p"+(3-p)+"handPos", "occupied", 1*yGetVar("p"+(3-p)+"hand", "pos"), 0);
				yRemoveFromDatabase("p"+(3-p)+"hand");
				yRemoveUpdateVar("p"+(3-p)+"hand", "pos");
				if(trQuestVarGet("chats_Monument3_1") == 0){
					trQuestVarSet("chats_Monument3_1", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Floating Steward</color>: Assisting guest with luggage.");
				}	
			} else {
				if(trQuestVarGet("chats_Monument3_2") == 0){
					trQuestVarSet("chats_Monument3_2", 1);
					ChatLog(0, "<color={Playercolor("+p+")}>Floating Steward</color>: Guest is free of luggage.");
				}	
			}		
			return (true);
		}
		case kbGetProtoUnitID("Monument 4"):
		{
			if(yGetDatabaseCount("p"+p+"hand") < 10){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);				
			}
			if(yGetDatabaseCount("p"+p+"hand") < 10){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);				
			}
			if(trQuestVarGet("chats_Monument4_1") == 0){
				trQuestVarSet("chats_Monument4_1", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>Floating Twins</color>: Providing Arcane delicacies.");
			}
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("gaiasparkle" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
			return (true);
		}
		case kbGetProtoUnitID("Monument 5"):
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
			
			healUnit(1*trQuestVarGet("p"+p+"commander"), 5);
			deployAtTile(0, "Regeneration SFX", 1*mGetVarByQV("p"+p+"commander", "tile"));
			trSoundPlayFN("heal.wav","1",-1,"","");
			
			if(yGetDatabaseCount("p"+(3-p)+"hand") > 0){
				trQuestVarSetFromRand("temp", 1, yGetDatabaseCount("p"+(3-p)+"hand"), true);
				yDatabasePointerDefault("p"+(3-p)+"hand");
				for(x=trQuestVarGet("temp"); >0) {
					yDatabaseNext("p"+(3-p)+"hand", true);
				}
				trQuestVarSetFromRand("soundRandom", 1, 3, true);
				trSoundPlayFN("swing" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
				trVectorSetUnitPos("pos", "p"+(3-p)+"hand");
				trUnitSelectClear();
				trUnitSelectByID(1*yGetVar("p"+(3-p)+"hand", "pos"));
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("p"+(3-p)+"hand"), true);
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
				trArmyDispatch("1,10","Dwarf",1,trQuestVarGet("posx"),0,trQuestVarGet("posz"),0, true);
				trUnitSelectClear();
				trArmySelect("1,10");
				trUnitChangeProtoUnit("Hero Death");
				if (mGetVarByQV("p"+(3-p)+"hand", "spell") == SPELL_NONE) {
					ChatLog((3-p), "Discarded " + trStringQuestVarGet("card_" + 1*mGetVarByQV("p"+(3-p)+"hand", "proto") + "_name"));
				} else {
					ChatLog((3-p), "Discarded " + trStringQuestVarGet("spell_" + 1*mGetVarByQV("p"+(3-p)+"hand", "spell") + "_name"));
				}
				yRemoveFromDatabase("p"+(3-p)+"hand");
				yRemoveUpdateVar("p"+(3-p)+"hand", "pos");				
			}

			if(yGetDatabaseCount("p"+p+"hand") < 10){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);				
			}
			if(yGetDatabaseCount("p"+p+"hand") < 10){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);				
			}
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("gaiasparkle" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
			if(trQuestVarGet("chats_Monument5_1") == 0){
				trQuestVarSet("chats_Monument5_1", 1);
				ChatLog(0, "<color={Playercolor("+p+")}>Floating Majordomo</color>: YES.");
			}
			return (true);
		}
	}
	return (false);
}