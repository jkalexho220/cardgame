bool ValidateClass(int class = 0){
	bool valid = true;
	bool hasCardsInDeck = false;
	for(i = 30 * class;<30 * (class + 1)){
		if(getCardCountDeck(i) > 0){
			hasCardsInDeck = true;
		}
		trQuestVarSet("cardsInDeck", trQuestVarGet("cardsInDeck") + getCardCountDeck(i));
		if((i == 14 + 30 * class) || (i == 29 + 30 * class)){
			if(getCardCountDeck(i) + getCardCountCollection(i) > 1){
				ChatLog(1, "ERROR! More than 1 copy of Legendary card: " + i);
				valid = false;
			}
		} else {
			if(getCardCountDeck(i) + getCardCountCollection(i) > 3){
				ChatLog(1, "ERROR! More than 3 copies of Common card: " + i);
				valid = false;
			}
		}
	}	
	
	if(getDeckCommander() == (2 * class) || getDeckCommander() == (2 * class + 1)){
		trQuestVarSet("commanderClass", class);
		trQuestVarSet("class1", class);
		if(getClassProgress(class) < 1){
			ChatLog(1, "ERROR! Deck Commander is from locked class: " + class);
			valid = false;
		}
	} else {
		if(hasCardsInDeck){
			trQuestVarSet("class2", class);
		}
	}
	
	if(hasCardsInDeck){
		trQuestVarSet("classesInDeck", trQuestVarGet("classesInDeck") + 1);
		if(getClassProgress(class) < 1){
			ChatLog(1, "ERROR! Cards in locked class: " + class);
			valid = false;
		}
	}
	
	return (valid);
}

bool ValidateCollection(){
	bool valid = true;
	trQuestVarSet("class1", -1);
	trQuestVarSet("class2", -1);
	trQuestVarSet("commanderClass", -1);
	trQuestVarSet("cardsInDeck", 0);
	trQuestVarSet("classesInDeck", 0);
	for(class=0;<6){
		if(ValidateClass(class) == false){
			valid = false;
		}
	}
		
	if(trQuestVarGet("class2") < 0){
		trQuestVarSet("class2", trQuestVarGet("class1"));
	}
	
	if(trQuestVarGet("cardsInDeck") != 40){
		ChatLog(1, "ERROR! Not 40 cards in deck!");
		valid = false;
	}
	
	if(trQuestVarGet("classesInDeck") > 2){
		ChatLog(1, "ERROR! More than 2 classes in deck!");
		valid = false;
	}
	
	if(trQuestVarGet("commanderClass") < 0){
		ChatLog(1, "ERROR! No Commander in deck!");
		valid = false;
	}
	
	if(trQuestVarGet("commanderClass") != trQuestVarGet("class1") && trQuestVarGet("commanderClass") != trQuestVarGet("class2")){
		ChatLog(1, "ERROR! Deck Commander not from one of the two classes!");
		valid = false;
	}
	
	return (valid);
}

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
		trUnitChangeProtoUnit(kbGetProtoUnitName(proto));
	} else {
		trUnitChangeName("("+1*trQuestVarGet("spell_" + spell + "_Cost")+") "+trStringQuestVarGet("spell_" + spell + "_Name"));
		proto = kbGetProtoUnitID("Statue of Lightning");
		trUnitChangeProtoUnit("Statue of Lightning");
		trSetSelectedScale(0.75, xsSqrt(trQuestVarGet("spell_" + spell + "_cost")) * 0.5, 0.75);
		trUnitSetAnimationPath(1*trQuestVarGet("spell_"+spell+"_animation") + ",0,0,0,0");
	}

	yAddUpdateVar("allUnits", "player", 1);
	yAddUpdateVar("allUnits", "proto", proto);
	yAddUpdateVar("allUnits", "spell", spell);
	
	trModifyProtounit(kbGetProtoUnitName(proto), 1, 1, 9999999999999999999.0);
	trModifyProtounit(kbGetProtoUnitName(proto), 1, 1, -9999999999999999999.0);
}

int CommanderToProtounit(int commander = 0){
	switch(commander)
	{
		case 0:
		{
			return (kbGetProtoUnitID("Hero Greek Jason"));
		}
		case 1:
		{
			return (kbGetProtoUnitID("Hero Greek Heracles"));
		}
		case 2:
		{
			return (kbGetProtoUnitID("Oracle Hero"));
		}
		case 3:
		{
			return (kbGetProtoUnitID("Minotaur"));
		}
		case 4:
		{
			return (kbGetProtoUnitID("Royal Guard Hero"));
		}
		case 5:
		{
			return (kbGetProtoUnitID("Archer Atlantean Hero"));
		}
		case 6:
		{
			return (kbGetProtoUnitID("Hero Greek Polyphemus"));
		}
		case 7:
		{
			return (kbGetProtoUnitID("Pharaoh of Osiris"));
		}
		case 8:
		{
			return (kbGetProtoUnitID("Hoplite"));
		}
		case 9:
		{
			return (kbGetProtoUnitID("Hero Greek Perseus"));
		}
		case 10:
		{
			return (kbGetProtoUnitID("Hero Greek Odysseus"));
		}
		case 11:
		{
			return (kbGetProtoUnitID("Caravan Atlantean"));
		}
		case 900:
		{
			return (kbGetProtoUnitID("Bear"));
		}
		case 906:
		{
			return (kbGetProtoUnitID("Golem"));
		}
	}
	ThrowError("CommanderToProtounit");
}

void CollectionCommander(int commander = 0, int x = 0, int z = 0){
	CollectionDeploy(CommanderToProtounit(commander), x, z, true);
}

void CollectionCard(int index = 0, int x = 0, int z = 0) {
	int countDeck = getCardCountDeck(index);
	int countCollection = getCardCountCollection(index);
	for(i=0;<3){
		if(countDeck > 0){
			CollectionDeploy(index, x, z + 44);
			countDeck = countDeck - 1;
		} else if(countCollection > 0){
			CollectionDeploy(index, x, z);
			countCollection = countCollection - 1;
		} 
		x = x + 2;
	}
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
			}
		}
	}
	ThrowError("GetMissionTitle");
}

void SetupClass(int class = 0, int terrainType = 0, int terrainSubType = 0){
	int progress = getClassProgress(class);
	int x = 0;
	int z = 0;
	if(progress > 0){
		ChatLog(1, "Setup Class: " + class + " Progress: " + progress);
		trPaintTerrain(10 * class, 0, 10 + 10 * class, 43, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(1 + 10 * class, 0, 9 + 10 * class, 20, terrainType, terrainSubType, false);
		trPaintTerrain(1 + 10 * class, 22, 9 + 10 * class, 42, terrainType, terrainSubType, false);	
		// Cards		
		x = 3 + 20 * class; z = 37;
		for(i = 30 * class;<30 * (class + 1)){
			if(i == 14 + 30 * class){
				// First Legendary
				CollectionCard(i,9 + 20 * class,35);
			} else if(i == 29 + 30 * class){
				// Second Legendary
				CollectionCard(i,13 + 20 * class,35);
			} else {
				CollectionCard(i,x,z);
				z = z - 4;
				if(i == 9 + 30 * class){
					x = 9 + 20 * class; z = 31;
				}
				if(i == 18 + 30 * class){
					x = 15 + 20 * class; z = 37;
				}
			}
		}	
		
		z = 41;
		// Commanders
		if(getDeckCommander() ==  (2 * class)){
			trQuestVarSet("currentCommander", trGetNextUnitScenarioNameNumber());
			z = z + 44;
		}
		CollectionCommander(2 * class, 5 + 20 * class, z);
		if(progress > 6){
			if(getDeckCommander() == (2 * class + 1)){
				trQuestVarSet("currentCommander", trGetNextUnitScenarioNameNumber());
				z = z + 44;
			}
			CollectionCommander(2 * class + 1, 17 + 20 * class, z);
		}
		// Missions
		x = 11 + 20 * class; z = 91;
		for(i=1;<=xsMin(progress,6)){
			trQuestVarSet("class" + class + "Mission" + i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName(GetMissionTitle(class,i));
			trUnitChangeProtoUnit("Outpost");
			trSetSelectedScale(1.0, 0.3, 1.0);
			yAddToDatabase("allUnits", "class" + class + "Mission" + i);
			yAddUpdateVar("allUnits", "proto", kbGetProtoUnitID("Cinematic Block"));
			z = z + 4;
		}
		if(progress < 7){
			trArmyDispatch("1,10", "Dwarf", 1, 0, 0, 0, 180, true);
			trArmySelect("1,10");
			trUnitChangeProtoUnit("Garrison Flag Sky Passage");
			trUnitTeleport(x,0,z - 4);
		}
	}	
}

string collectionMission = "";
string collectionReward = "";

void CollectionGodPowers(){
	trCounterAbort("tooltipSpace");	
	trCounterAbort("tooltipEnter");
	trCounterAbort("mission");
	trCounterAbort("reward");
	if(collectionMission != ""){
		trCounterAddTime("mission", -1, -9999999, collectionMission);
	}
	if(collectionReward != ""){
		trCounterAddTime("reward", -1, -9999999, collectionReward);
	}
	trPlayerKillAllGodPowers(1);
	trTechGodPower(1, "animal magnetism", 1);
	trTechGodPower(1, "create gold", 1);
	if(trQuestVarGet("canPressSpace") == 1){
		trTechGodPower(1, "rain", 1);
		if(trQuestVarGet("canPressEnter") == 1){
			trCounterAddTime("tooltipEnter", -1, -9999999, "(Press ENTER to start mission)");
			trTechGodPower(1, "nidhogg", 1);
		} else {
			xsDisableRule("CollectionEnter");
		}
		trCounterAddTime("tooltipSpace", -1, -9999999, "(Press SPACE to save deck and QUIT)");
	} else {
		xsDisableRule("CollectionSpace");
		xsDisableRule("CollectionEnter");
	}
}

rule Collection
highFrequency
inactive
{
	trCameraCut(vector(-58.161659,112.294716,-58.161659),vector(0.500000,-0.707107,0.500000),vector(0.500000,0.707107,0.500000),vector(0.707107,0.000000,-0.707107));
	xsEnableRule("CollectionClick");
	trSetFogAndBlackmap(false, false);
	unitTransform("Statue of Automaton Base","Victory Marker");
	trPaintTerrain(0, 0, 60, 60, 5, 4, false); //Black

	yClearDatabase("allUnits");	
	trQuestVarSet("activePlayer", 1);
	trQuestVarSet("idsStart", trGetNextUnitScenarioNameNumber());
	collectionMission = "";
	collectionReward = "";
	trQuestVarSet("missionSelection", -1);
	trQuestVarSet("missionClass", -1);
	trQuestVarSet("canPressEnter", -1);
	ValidateCollection();
	if(true){
		trUIFadeToColor(0,0,0,1000,0,false);
		xsEnableRule("CollectionSpace");
		trCounterAddTime("tooltipSpace", -1, -9999999, "(Press SPACE to save deck and QUIT)");
		trQuestVarSet("canPressSpace", 1);
	} else {
		trLetterBox(true);
		trUIFadeToColor(0,0,0,0,0,true);
		trOverlayTextColour(255, 0, 255);
		trOverlayText("Collection Invalid! Fuck off cheater!", 4.7, 500, 200, 1000);
		trSoundPlayFN("default","1",-1," :Alternatively, this is a bug in which case we apologise and kindly ask you to report it.","");
		trSoundPlayFN("xpack\xtaunts\en\999 theme.mp3", "1", -1, "","");
		trMusicPlay("xpack\xtaunts\en\999 theme.mp3", "1", 0.0);
		for(x=0; <16) {
			trSetCurrentScenarioUserData(x, 0);
		}		
		xsEnableRule("EjectButton");	
	}
	CollectionGodPowers();
	
	SetupClass(CLASS_ADVENTURER, 0, 65); // GreekRoadA
	SetupClass(CLASS_ARCANE, 5, 2); // IceC
	SetupClass(CLASS_NAGA, 3, 10); // coralB
	SetupClass(CLASS_CLOCKWORK, 0, 71); // CityTileAtlantis
	SetupClass(CLASS_EVIL, 0, 84); // Hadesbuildable1
	SetupClass(CLASS_SPACE, 0, 52); // OlympusC
	
    xsDisableRule("Collection");
}

rule CollectionClick
highFrequency
inactive
{
	switch(trQuestVarGet("p1click"))
	{
		case LEFT_CLICK:
		{
			uiClearSelection();
			trQuestVarSet("p1click", 0);
			trClearCounterDisplay();
			trSoundPlayDialog("default", "1", -1, false, " : ", "");	
			CollectionGodPowers();	
			xsEnableRule("CollectionSelect");							
		}
		case RIGHT_CLICK:
		{		
			trQuestVarSet("p1click", 0);
			for(x=yGetDatabaseCount("allUnits"); >0) {
				int id = yDatabaseNext("allUnits", true);			
				if(zDistanceToVector("allUnits","p1clickPos") < 2){	
					trVectorSetUnitPos("temp","allUnits");
					if(1*yGetVar("allUnits", "spell") == SPELL_COMMANDER){
						if(trVectorQuestVarGetZ("temp") < 44){
							trUnitTeleport(trVectorQuestVarGetX("temp"),trVectorQuestVarGetY("temp"),trVectorQuestVarGetZ("temp") + 44);
							for(y=0; <12) {
								if(kbGetUnitBaseTypeID(id) == CommanderToProtounit(y)){
									setDeckCommander(y);
									trQuestVarSet("class1", -1);
									trQuestVarSet("class2", -1);
									break;
								}
							}
							trVectorSetUnitPos("temp","currentCommander");
							trUnitSelectClear();
							trUnitSelect(""+1*trQuestVarGet("currentCommander"), true);
							trUnitTeleport(trVectorQuestVarGetX("temp"),trVectorQuestVarGetY("temp"),trVectorQuestVarGetZ("temp") - 44);
							trQuestVarSet("currentCommander", trQuestVarGet("allUnits"));
							ChatLog(1, "Commander chosen");
						} else {
							ChatLog(1, "Deck must have a Commander");
						}
					} else {
						int card = 0;
						string name = "";
						if(1*yGetVar("allUnits", "spell") == 0){
							card = ProtoToCard(kbGetUnitBaseTypeID(id));
							name = trStringQuestVarGet("card_"+kbGetUnitBaseTypeID(id)+"_Name");
						} else {
							card = SpellToCard(1*yGetVar("allUnits", "spell"));
							name = trStringQuestVarGet("spell_"+1*yGetVar("allUnits", "spell")+"_Name");
						}

						if(trVectorQuestVarGetZ("temp") < 44){
							trUnitTeleport(trVectorQuestVarGetX("temp"),trVectorQuestVarGetY("temp"),trVectorQuestVarGetZ("temp") + 44);
							setCardCountDeck(card, getCardCountDeck(card) + 1);
							ChatLog(1, name + " added to deck");
						} else {
							trUnitTeleport(trVectorQuestVarGetX("temp"),trVectorQuestVarGetY("temp"),trVectorQuestVarGetZ("temp") - 44);
							setCardCountDeck(card, getCardCountDeck(card) - 1);
							ChatLog(1, name + " removed from deck");
						}
					}
					if(ValidateCollection()){
						xsEnableRule("CollectionSpace");
						trQuestVarSet("canPressSpace", 1);
					} else {
						xsDisableRule("CollectionSpace");
						trQuestVarSet("canPressSpace", 0);	
					}
					CollectionGodPowers();
					break;
				}
			}
		}
	}
}

rule CollectionSelect
highFrequency
inactive
{
	for(x=yGetDatabaseCount("allUnits"); >0) {
		int id = yDatabaseNext("allUnits", true);
		if (trUnitIsSelected()) {
			trVectorSetUnitPos("temp","allUnits");
			if(trVectorQuestVarGetZ("temp") < 90){
				displayCardDetails(kbGetUnitBaseTypeID(id), 1*yGetVar("allUnits", "spell"));
			} else {
				trQuestVarSet("canPressEnter", 0);	
				collectionMission = "";
				collectionReward = "";
				for(class=0;<6){
					for(i=1;<=xsMin(getClassProgress(class),6)){
						if(zDistanceToVector("class" + class + "Mission" + i,"temp") < 2){
							if(getClassProgress(class) == i){
								trQuestVarSet("missionHardmode", 0);
								collectionMission = GetMissionTitle(class,i);
								collectionReward = "Reward: Class Pack";					
							} else {
								trQuestVarSet("missionHardmode", 1);
								collectionMission = GetMissionTitle(class,i) + " (HARDMODE)";
								collectionReward = "Reward: Random Pack";
							}
							trQuestVarSet("missionSelection", i);
							trQuestVarSet("missionClass", class);
							xsEnableRule("CollectionEnter");
							trQuestVarSet("canPressEnter", 1);	
							CollectionGodPowers();
						}
					}
				}
			}
			xsDisableRule("CollectionSelect");
			break;
		}
	}
	if ((trTime()-cActivationTime) > 1){
		xsDisableRule("CollectionSelect");
	}
}

rule CollectionEnter
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Nidhogg") > 0) {
		if (yFindLatestReverse("nidhoggNext", "Nidhogg", 1) > 0) {
			if(true){
				trUnitDestroy();
				uiClearSelection();
				trPlayerKillAllGodPowers(1);
				trCounterAbort("tooltipEnter");
				xsDisableRule("CollectionEnter");
				trClearCounterDisplay();
				trSoundPlayDialog("default", "1", -1, false, " : ", "");
				trCounterAbort("mission");
				trCounterAbort("reward");
				xsDisableRule("CollectionClick");
				xsDisableRule("CollectionSpace");
				ChatLog(1, "Starting Mission: " + GetMissionTitle(trQuestVarGet("missionClass"),trQuestVarGet("missionSelection")));
				trCounterAbort("tooltipSpace");
				dataSave();
				for(x=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits");
					string protoname = kbGetProtoUnitName(yGetVar("allUnits", "proto"));
					if(protoname != "Cinematic Block"){
						trModifyProtounit(protoname, 1, 1, 9999999999999999999.0);
						trModifyProtounit(protoname, 1, 1, -9999999999999999999.0);
						trModifyProtounit(protoname, 1, 1, 10);			
					}
				}
				yClearDatabase("allUnits");
				int next = trGetNextUnitScenarioNameNumber();
				for(i=trQuestVarGet("idsStart");<next){
					trUnitSelectClear();trUnitSelect(""+i);
					trUnitDestroy();
				}
				xsEnableRule("MissionBegin");
			}
		} else {
			ThrowError();
		}
	}
}

rule CollectionSpace
highFrequency
inactive
{
	if (trCheckGPActive("rain", 1)) {
		if (trQuestVarGet("p1rain") == 0) {
			trQuestVarSet("p1rain", 1);
			dataSave();
			map("mouse1down", "game", "");
			map("mouse2up", "game", "");
			map("space", "game", "");
			map("enter", "game", "gadgetReal(\"chatInput\") uiIgnoreNextKey");
			trModeEnter("Pregame");
		}
	} else if (trQuestVarGet("p1rain") == 1) {
		trTechGodPower(1, "rain", 1);
		trQuestVarSet("p1rain", 0);
	}
}

rule EjectButton
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 5){
		exit(false);
	}
}