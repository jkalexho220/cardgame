void CollectionDeploy(int card = 0, int x = 0, int z = 0, bool cardIsCommander = false){
	trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("1,10","Dwarf",1,x,0,z,180,true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("next"), true);

	yAddToDatabase("allUnits", "next");
	int proto = CardToProto(card);
	int spell = CardToSpell(card);
	
	if(cardIsCommander){
		proto = card;
		spell = SPELL_COMMANDER;
	}
	
	if (spell == 0 || spell == SPELL_COMMANDER) {
		trUnitChangeName("("+1*trQuestVarGet("card_" + proto + "_Cost")+") "+trStringQuestVarGet("card_" + proto + "_Name")+" <"+1*trQuestVarGet("card_" + proto + "_Speed")+">");
	} else {
		trUnitChangeName("("+1*trQuestVarGet("spell_" + spell + "_Cost")+") "+trStringQuestVarGet("spell_" + spell + "_Name"));
		yAddUpdateVar("allUnits", "spell", spell);
		proto = kbGetProtoUnitID("Statue of Lightning");
	}
	trUnitChangeProtoUnit(kbGetProtoUnitName(proto));
	
	yAddUpdateVar("allUnits", "proto", proto);

	yAddUpdateVar("allUnits", "player", 1);
	yAddUpdateVar("allUnits", "spell", spell);
}

void CollectionCommanderFirst(int class = 0, int x = 0, int z = 0){
	switch(class)
	{
		case CLASS_ADVENTURER:
		{
			trArmyDispatch("1,10", "Hero Greek Jason", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("phdorogers4 (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Hero Greek Jason"), x, z, true);
		}
		case CLASS_ARCANE:
		{
			trArmyDispatch("1,10", "Oracle Hero", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Nanodude (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Oracle Hero"), x, z, true);
		}
		case CLASS_NAGA:
		{
			trArmyDispatch("1,10", "Royal Guard", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Out Reach (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Royal Guard"), x, z, true);
		}
		case CLASS_CLOCKWORK:
		{
			trArmyDispatch("1,10", "Hero Greek Polyphemus", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Roxas (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Hero Greek Polyphemus"), x, z, true);
		}
		case CLASS_EVIL:
		{
			trArmyDispatch("1,10", "Hoplite", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Zenophobia (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Hoplite"), x, z, true);
		}
		case CLASS_SPACE:
		{
			trArmyDispatch("1,10", "Hero Greek Odysseus", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Nickonhawk (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Hero Greek Odysseus"), x, z, true);
		}
	}
}

void CollectionCommanderSecond(int class = 0, int x = 0, int z = 0){
	switch(class)
	{
		case CLASS_ADVENTURER:
		{
			trArmyDispatch("1,10", "Hero Greek Heracles", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Venlesh (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Hero Greek Heracles"), x, z, true);
		}
		case CLASS_ARCANE:
		{
			trArmyDispatch("1,10", "Minotaur", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("nottud (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Minotaur"), x, z, true);
		}
		case CLASS_NAGA:
		{
			trArmyDispatch("1,10", "Archer Atlantean Hero", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("scragins (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Archer Atlantean Hero"), x, z, true);
		}
		case CLASS_CLOCKWORK:
		{
			trArmyDispatch("1,10", "Pharaoh of Osiris", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Yeebaagooon (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Pharaoh of Osiris"), x, z, true);
		}
		case CLASS_EVIL:
		{
			trArmyDispatch("1,10", "Hero Greek Perseus", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("Aros (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Hero Greek Perseus"), x, z, true);
		}
		case CLASS_SPACE:
		{
			trArmyDispatch("1,10", "Caravan Atlantean", 1, x, 0, z, 180, true);	
			trArmySelect("1,10");
			trUnitChangeName("God (Commander)");
			//CollectionDeploy(kbGetProtoUnitID("Caravan Atlantean"), x, z, true);
		}
	}
}

bool CollectionCardLegendary(int index = 0, int x = 0, int z = 0) {
	/*
	if(getCardCountCollection(index) > 0){
		CollectionDeploy(index, x, z);
		return (false);
	}
	if(getCardCountDeck(index) > 0){
		CollectionDeploy(index, x, z + 44);
		return (true);
	}
	*/
	return(true);
}

bool CollectionCard(int index = 0, int x = 0, int z = 0) {
	
	int countCollection = getCardCountCollection(index);
	for(i=0;<countCollection){
		CollectionDeploy(index, x, z);
		x = x + 2;
	}
	x = x - 2 * countCollection;
	int countDeck = getCardCountDeck(index);
	for(i=0;<countDeck){
		CollectionDeploy(index, x, z + 44);
		x = x + 2;
	}
	return (countDeck>0);
}

string GetMissionTitle(int class = 0, int mission = 0){
	switch(class)
	{
		case CLASS_ADVENTURER:
		{
			switch(mission)
			{
				case 1:
				{
					return ("The Adventure Begins");	
				}
				case 2:
				{
					return ("The Plot Thickens");	
				}
				case 3:
				{
					return ("The Adventure Continues");	
				}
				case 4:
				{
					return ("The Plot Twists");	
				}
				case 5:
				{
					return ("The Adventure Continues Again");	
				}
				case 6:
				{
					return ("The Plot Twists Again");	
				}
				case 7:
				{
					return ("The Adventure Concludes");	
				}
			}
		}
		case CLASS_ARCANE:
		{
			switch(mission)
			{
				case 1:
				{
					return ("Letter From An Owl");	
				}
				case 2:
				{
					return ("Sparkling Gates");	
				}
				case 3:
				{
					return ("Palace Of Magic");	
				}
				case 4:
				{
					return ("Unusual Companions");	
				}
				case 5:
				{
					return ("Wizard Tournament");	
				}
				case 6:
				{
					return ("It's Not Over Yet");	
				}
				case 7:
				{
					return ("Power Of Magic");	
				}
			}
		}
		case CLASS_NAGA:
		{
			switch(mission)
			{
				case 1:
				{
					return ("Odd Catch");	
				}
				case 2:
				{
					return ("Storm Approaching");	
				}
				case 3:
				{
					return ("Roaring Waves");	
				}
				case 4:
				{
					return ("Dreaming Whirlpool");	
				}
				case 5:
				{
					return ("Go With The Flow");	
				}
				case 6:
				{
					return ("Empire Of Water");	
				}
				case 7:
				{
					return ("Return What Was Taken");	
				}
			}
		}
		case CLASS_CLOCKWORK:
		{
			switch(mission)
			{
				case 1:
				{
					return ("An Invention Like Any Other");	
				}
				case 2:
				{
					return ("Life");	
				}
				case 3:
				{
					return ("Junkyard Is To Be Explored");	
				}
				case 4:
				{
					return ("Creator");	
				}
				case 5:
				{
					return ("A Friend Like No Other");	
				}
				case 6:
				{
					return ("Accident");	
				}
				case 7:
				{
					return ("Memories Are To Be Remembered");	
				}
			}
		}
		case CLASS_EVIL:
		{
			switch(mission)
			{
				case 1:
				{
					return ("Nothing Left But Revenge");	
				}
				case 2:
				{
					return ("Eyes Behind The Veil");	
				}
				case 3:
				{
					return ("The Master Answered");	
				}
				case 4:
				{
					return ("Sky Melts Downwards");	
				}
				case 5:
				{
					return ("Air Turns To Formless Flesh");	
				}
				case 6:
				{
					return ("Moment Of Hesitation");	
				}
				case 7:
				{
					return ("Break Of Dawn");	
				}
			}
		}
		case CLASS_SPACE:
		{
			switch(mission)
			{
				case 1:
				{
					return ("It's Over And Yet");	
				}
				case 2:
				{
					return ("The Portal Guy");	
				}
				case 3:
				{
					return ("Secrets And Stars");	
				}
				case 4:
				{
					return ("Puzzle Box");	
				}
				case 5:
				{
					return ("It's Empty And Yet");	
				}
				case 6:
				{
					return ("Thank You");	
				}
				case 7:
				{
					return ("Goodbye");	
				}
			}
		}
	}
	ThrowError("GetMissionTitle");
}

int SetupClass(int class = 0, int terrainType = 0, int terrainSubType = 0){
	int progress = getClassProgress(class);
	trQuestVarSet("progressClass" + class, progress);
	int cardsInDeck = 0;
	int x = 0;
	int z = 0;
	if(progress > 0){
		trPaintTerrain(10 * class, 0, 9 + 10 * class, 43, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(10 * class, 0, 8 + 10 * class, 20, terrainType, terrainSubType, false);
		trPaintTerrain(10 * class, 22, 8 + 10 * class, 42, terrainType, terrainSubType, false);	
		// Cards
		
		x = 1 + 20 * class; z = 37;
		for(i = 30 * class;<30 * (class + 1)){
			if(i == 14 + 30 * class){
				if(CollectionCardLegendary(i,7 + 20 * class,35)){
					cardsInDeck = cardsInDeck + 1;
				}
			} else if(i == 29 + 30 * class){
				if(CollectionCardLegendary(i,11 + 20 * class,35)){
					cardsInDeck = cardsInDeck + 1;
				}
			} else {
				if(CollectionCard(i,x,z)){
					cardsInDeck = cardsInDeck + 1;
				}
				z = z - 4;
				if(i == 9 + 30 * class){
					x = 7 + 20 * class; z = 31;
				}
				if(i == 18 + 30 * class){
					x = 13 + 20 * class; z = 37;
				}
			}
		}	
		
		z = 41;
		// Commanders
		if(getDeckCommander() ==  (2 * class)){
			z = z + 44;
		}
		CollectionCommanderFirst(class, 3 + 20 * class, z);
		if(progress > 7){
			if(getDeckCommander() == (2 * class + 1)){
				z = z + 44;
			}
			CollectionCommanderSecond(class, 15 + 20 * class, z);
		}
		// Missions
		x = 9 + 20 * class; z = 91;
		for(i=1;<progress){
			trQuestVarSet("class" + class + "Mission" + i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName(GetMissionTitle(class,i));
			trUnitChangeProtoUnit("Outpost");
			trSetSelectedScale(1.0, 0.3, 1.0);
			yAddToDatabase("allUnits", "class" + class + "Mission" + i);
			z = z + 4;
		}
		if(progress < 7){
			trArmyDispatch("1,10", "Garrison Flag Sky Passage", 1, x, 0, z - 4, 180, true);
		}
		if(cardsInDeck > 0){
			trQuestVarSet("classesInDeck", trQuestVarGet("classesInDeck") + 1);
		}
	}	
	return (cardsInDeck);
}

rule Collection
highFrequency
inactive
{
	trCameraCut(vector(-58.161659,112.294716,-58.161659),vector(0.500000,-0.707107,0.500000),vector(0.500000,0.707107,0.500000),vector(0.707107,0.000000,-0.707107));
	xsEnableRule("CollectionClick");
	trSetFogAndBlackmap(false, false);
	unitTransform("Statue of Automaton Base","Victory Marker");
	trChangeTerrainHeight(0, 0, 60, 60, 0, false);
	trPaintTerrain(0, 0, 60, 60, 5, 4, false); //Black

	yClearDatabase("allUnits");	
	trQuestVarSet("classesInDeck", 0);
	int cardsInDeck = 0;
	
	cardsInDeck = cardsInDeck + SetupClass(CLASS_ADVENTURER, 0, 65); // GreekRoadA
	cardsInDeck = cardsInDeck + SetupClass(CLASS_ARCANE, 5, 2); // IceC
	cardsInDeck = cardsInDeck + SetupClass(CLASS_NAGA, 3, 10); // coralB
	cardsInDeck = cardsInDeck + SetupClass(CLASS_CLOCKWORK, 0, 71); // CityTileAtlantis
	cardsInDeck = cardsInDeck + SetupClass(CLASS_EVIL, 0, 84); // Hadesbuildable1
	cardsInDeck = cardsInDeck + SetupClass(CLASS_SPACE, 0, 52); // OlympusC
	
	
	if(cardsInDeck > 40){
		ThrowError("More than 40 cards in deck!");
	}
	
	if(trQuestVarGet("classesInDeck") > 2){
		ThrowError("More than 2 classes in deck!");
	}
	
    xsDisableRule("Collection");
}

rule CollectionClick
highFrequency
inactive
{
	if (trQuestVarGet("p1click") == LEFT_CLICK) {
		trQuestVarSet("p1click", 0);
		trCounterAbort("mission");
		trCounterAbort("reward");
		trCounterAbort("tooltip");
		xsDisableRule("CollectionEnter");
		trPlayerKillAllGodPowers(1);
		trTechGodPower(1, "animal magnetism", 1);
		xsEnableRule("CollectionSelect");
		trClearCounterDisplay();
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
	}
}

rule CollectionSelect
highFrequency
inactive
{
	int id = yDatabaseNext("allUnits", true);
	if (trUnitIsSelected()) {
		xsDisableRule("CollectionSelect");
		trVectorSetUnitPos("temp","allUnits");
		if(trVectorQuestVarGetZ("temp") < 90){
			// this is a data leak. will need a very similar function that is based on protounit instead of name.
			// displayCardKeywordsAndDescription(1*trQuestVarGet("allUnits"));
			xsEnableRule("CollectionEnter");
			trTechGodPower(1, "nidhogg", 1);
			trQuestVarSet("collectionSelection", trQuestVarGet("allUnits"));
			if(1*yGetVar("allUnits", "spell") == 0){
				trQuestVarSet("collectionCard", ProtoToCard(kbGetUnitBaseTypeID(id)));
			} else {
				trQuestVarSet("collectionCard", SpellToCard(yGetVar("allUnits", "spell")));
			}
			displayCardDetails(kbGetUnitBaseTypeID(id), 1*yGetVar("allUnits", "spell"));

			if(trVectorQuestVarGetZ("temp") < 44){
				trCounterAddTime("tooltip", -1, -9999999, "(Press ENTER to add to deck)");
				trChatSend(0, "(Press ENTER to add to deck)");
			} else {
				trCounterAddTime("tooltip", -1, -9999999, "(Press ENTER to remove from deck)");
				trChatSend(0, "(Press ENTER to remove from deck)");
			}
		} else {
			for(class=0;<6){
				for(i=1;<=xsMin(trQuestVarGet("progressClass" + class),7)){
					if(zDistanceToVector("class" + class + "Mission" + i,"temp") < 2){
						if(trQuestVarGet("progressClass" + class) == i){
							trQuestVarSet("missionHardmode", 0);
							trCounterAddTime("mission", -1, -9999999, GetMissionTitle(class,i));
							trCounterAddTime("reward", -1, -9999999, "Reward: Class Pack");					
						} else {
							trQuestVarSet("missionHardmode", 1);
							trCounterAddTime("mission", -1, -9999999, GetMissionTitle(class,i) + " (HARDMODE)");
							trCounterAddTime("reward", -1, -9999999, "Reward: Random Pack");
						}
						trCounterAddTime("tooltip", -1, -9999999, "(Press ENTER to start mission)");
						trChatSend(0, "(Press ENTER to start mission)");
						trTechGodPower(1, "nidhogg", 1);
						trQuestVarSet("collectionSelection", -1);
						trQuestVarSet("missionSelection", i);
						trQuestVarSet("missionClass", class);
						xsEnableRule("CollectionEnter");
						break;
					}
				}
			}
		}
	}
}

rule CollectionEnter
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Nidhogg") > 0) {
		if (yFindLatestReverse("nidhoggNext", "Nidhogg", 1) > 0) {
			trUnitDestroy();
			trPlayerKillAllGodPowers(1);
			trCounterAbort("tooltip");
			xsDisableRule("CollectionEnter");
			trClearCounterDisplay();
			trSoundPlayDialog("default", "1", -1, false, " : ", "");
			uiClearSelection();
			if(trQuestVarGet("collectionSelection") < 0){
				trCounterAbort("mission");
				trCounterAbort("reward");
				xsDisableRule("CollectionClick");
				ChatLog(1, "Starting Mission: " + GetMissionTitle(trQuestVarGet("missionClass"),trQuestVarGet("missionSelection")));
				unitTransform("Victory Marker", "Statue of Automaton Base");
				dataSave();
			} else {
				trTechGodPower(1, "animal magnetism", 1);
				trVectorSetUnitPos("temp","collectionSelection");
				int card = trQuestVarGet("collectionCard");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("collectionSelection"), true);
				if(trVectorQuestVarGetZ("temp") < 44){
					trUnitTeleport(trVectorQuestVarGetX("temp"),trVectorQuestVarGetY("temp"),trVectorQuestVarGetZ("temp") + 44);
					setCardCountDeck(card, getCardCountDeck(card) + 1);
					//setCardCountCollection(card, getCardCountCollection(card) - 1);
					ChatLog(1, "Card added to deck");
				} else {
					trUnitTeleport(trVectorQuestVarGetX("temp"),trVectorQuestVarGetY("temp"),trVectorQuestVarGetZ("temp") - 44);
					setCardCountDeck(card, getCardCountDeck(card) - 1);
					//setCardCountCollection(card, getCardCountCollection(card) + 1);
					ChatLog(1, "Card removed from deck");
				}
			}
		} else {
			ThrowError();
		}
	}
}