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
		/*
		case kbGetProtoUnitID("Theocrat"):
		{
			drawCard(p, true);
			return (true);
		}
		*/
		case kbGetProtoUnitID("Bireme"):
		{
			trQuestVarSet("p"+p+"manaTax", trQuestVarGet("p"+p+"manaTax") - 1);
		}
		case kbGetProtoUnitID("Eitri"):
		{
			generateCard(p, 0, SPELL_SCRAP_METAL);
			trQuestVarSet("p"+p+"drawCards", 1 + trQuestVarGet("p"+p+"drawCards"));
		}
		case kbGetProtoUnitID("Fire Siphon"):
		{
			trVectorQuestVarSet("dir", xsVectorSet(1.0*mGetVar(unit, "laserDirx")/100000.0, 0, 1.0*mGetVar(unit, "laserDirz")/100000.0));
			trUnitSelectClear();
			trUnitSelect(""+unit);
			trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true); // This makes the siphon dissapear
			trSoundPlayFN("sky passage.wav","1",-1,"","");
			trQuestVarSet("next", deployAtTile(0, "Dwarf", 1*mGetVar(unit, "tile")));
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("next"), true);
			trUnitHighlight(1.0, false);
			trSetSelectedScale(10, 0, 60);
			trSetUnitOrientation(vector(0,0,0) - trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
			trMutateSelected(kbGetProtoUnitID("Petosuchus Projectile"));
			yAddToDatabase("directionalLasers", "next");
			yAddUpdateVar("directionalLasers", "timeout", trTimeMS() + 500);
			xsEnableRule("directional_lasers");
			
			bool found = true;
			tile = mGetVar(unit, "tile");
			while (found) {
				found = false;
				trVectorQuestVarSet("pos", kbGetBlockPosition(""+tile) + (trVectorQuestVarGet("dir") * 6.0));
				for(x=0; < zGetVarByIndex("tiles", "neighborCount", tile)) {
					trVectorQuestVarSet("current", kbGetBlockPosition(""+1*zGetVarByIndex("tiles", "neighbor"+x, tile)));
					if (trDistanceBetweenVectorsSquared("current", "pos") < 9) {
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
			mSetVar(unit, "action", ACTION_SLEEPING);
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
					CharacterLog(p, "Vora", "*plant noises*");
				}
				return (true);
			}
		}
		case kbGetProtoUnitID("Shaba Ka"):
		{
			trQuestVarSet("p1count", 0);
			trQuestVarSet("p2count", 0);
			if(trQuestVarGet("chats_Kemsyt_0") == 0){
				trQuestVarSet("chats_Kemsyt_0", 1);
				CharacterLog(p, "Mister Pirate", "I like treasure!");
				trSoundPlayFN("kemsytattack2.wav","1",-1,"","");
			}
			for (x=yGetDatabaseCount("allUnits"); >0)  {
				yDatabaseNext("allUnits");
				p = mGetVarByQV("allUnits", "player");
				trQuestVarSet("p"+p+"count", 1 + trQuestVarGet("p"+p+"count"));
			}
			if (trQuestVarGet("p1count") > trQuestVarGet("p2count")) {
				p = 1;
			} else {
				p = 2;
			}
			trQuestVarSetFromRand("temp", 1, 3, true);
			if(trQuestVarGet("temp") == 1){
				generateCard(p, 0, SPELL_BOOTS_TREASURE);
			} else if(trQuestVarGet("temp") == 2){
				generateCard(p, 0, SPELL_WEAPONS_TREASURE);
			} else {
				generateCard(p, 0, SPELL_SHIELDS_TREASURE);
			}
			return(true);
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
						CharacterLog(p, "Pirate Crew", "Damn, we missed!");
					}
				} else if(1*mGetVar(occupant, "tile") == p){
					if(trQuestVarGet("chats_PirateShip_2") == 0){
						trQuestVarSet("chats_PirateShip_2", 1);
						CharacterLog(p, "Pirate Crew", "Oops! Sorry about that!");
					}
				} else {
					if(trQuestVarGet("chats_PirateShip_3") == 0){
						trQuestVarSet("chats_PirateShip_3", 1);
						CharacterLog(p, "Pirate Crew", "We got them good!");
					}
				}
			} else {
				if(trQuestVarGet("chats_PirateShip_4") == 0){
					trQuestVarSet("chats_PirateShip_4", 1);
					CharacterLog(p, "Pirate Crew", "Cannons be ready to fire!");
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
		case kbGetProtoUnitID("Invisible Target"):
		{
			trVectorQuestVarSet("pos", kbGetBlockPosition(""+unit));
			mSetVar(unit, "action", ACTION_SLEEPING);
			if (trDistanceToVectorSquared("p1commander", "pos") < 64) {
				mSetVar(unit, "health", 0);
				damageUnit(unit, 9999);
				trSoundPlayFN("favordump.wav","1",-1,"","");
			}
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
					CharacterLog(p, "Floating Housekeeper", "Dirt detected. Cleaning.");
				}
			} else {
				if(trQuestVarGet("chats_Monument_2") == 0){
					trQuestVarSet("chats_Monument_2", 1);
					CharacterLog(p, "Floating Housekeeper", "Nothing to clean.");
				}
			}
			return (true);
		}
		case kbGetProtoUnitID("Monument 2"):
		{
			trQuestVarSetFromRand("rand", 30, 59, true);
			generateCard(p, CardToProto(1*trQuestVarGet("rand")), CardToSpell(1*trQuestVarGet("rand")));
			if(trQuestVarGet("chats_Monument2_2") == 0){
				trQuestVarSet("chats_Monument2_2", 1);
				CharacterLog(p, "Floating Butler", "Please try this, sir.");
			}
			return (true);
		}
		case kbGetProtoUnitID("Monument 3"):
		{
			if(yGetDatabaseCount("p"+(3-p)+"hand") > 0){
				trQuestVarSetFromRand("temp", 1, yGetDatabaseCount("p"+(3-p)+"hand"), true);
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
				trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("pos"),0,trVectorQuestVarGetZ("pos"),0, true);
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
				if(trQuestVarGet("chats_Monument3_1") == 0){
					trQuestVarSet("chats_Monument3_1", 1);
					CharacterLog(p, "Floating Steward", "Assisting guest with luggage.");
				}
			} else {
				if(trQuestVarGet("chats_Monument3_2") == 0){
					trQuestVarSet("chats_Monument3_2", 1);
					CharacterLog(p, "Floating Steward", "Guest is free of luggage.");
				}
			}
			return (true);
		}
		case kbGetProtoUnitID("Monument 4"):
		{
			if(yGetDatabaseCount("p"+p+"hand") < trQuestVarGet("p"+p+"maxHandSize")){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);
			}
			if(yGetDatabaseCount("p"+p+"hand") < trQuestVarGet("p"+p+"maxHandSize")){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);
			}
			if(trQuestVarGet("chats_Monument4_1") == 0){
				trQuestVarSet("chats_Monument4_1", 1);
				CharacterLog(p, "Floating Twins", "Providing Arcane delicacies.");
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
			
			trQuestVarSetFromRand("rand", 30, 59, true);
			generateCard(p, CardToProto(1*trQuestVarGet("rand")), CardToSpell(1*trQuestVarGet("rand")));
			
			if(yGetDatabaseCount("p"+(3-p)+"hand") > 0){
				trQuestVarSetFromRand("temp", 1, yGetDatabaseCount("p"+(3-p)+"hand"), true);
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
				trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("pos"),0,trVectorQuestVarGetZ("pos"),0, true);
				trUnitSelectClear();
				trArmySelect("1,10");
				trUnitChangeProtoUnit("Hero Death");
				if (mGetVarByQV("p"+(3-p)+"hand", "spell") == SPELL_NONE) {
					ChatLog((3-p), "Discarded " + trStringQuestVarGet("card_" + 1*mGetVarByQV("p"+(3-p)+"hand", "proto") + "_name"));
				} else {
					ChatLog((3-p), "Discarded " + trStringQuestVarGet("spell_" + 1*mGetVarByQV("p"+(3-p)+"hand", "spell") + "_name"));
				}
				yRemoveFromDatabase("p"+(3-p)+"hand");
			}
			
			if(yGetDatabaseCount("p"+p+"hand") < trQuestVarGet("p"+p+"maxHandSize")){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);
			}
			if(yGetDatabaseCount("p"+p+"hand") < trQuestVarGet("p"+p+"maxHandSize")){
				trQuestVarSetFromRand("temp", 30, 59, true);
				generateCard(p, CardToProto(1*trQuestVarGet("temp")), CardToSpell(1*trQuestVarGet("temp")));
				mSetVarByQV("next", "cost", 0);
			}
			trQuestVarSetFromRand("soundRandom", 1, 3, true);
			trSoundPlayFN("gaiasparkle" + 1*trQuestVarGet("soundRandom") + ".wav","1",-1,"","");
			if(trQuestVarGet("chats_Monument5_1") == 0){
				trQuestVarSet("chats_Monument5_1", 1);
				CharacterLog(p, "Floating Majordomo", "RANDOM BULLSHIT GO!");
			}
			return (true);
		}
	}
	return (false);
}
