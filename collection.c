

string ClassName(int class = 0) {
	string cn = "Not a class";
	switch(class)
	{
		case CLASS_ADVENTURER:
		{
			cn = "Adventurer";
		}
		case CLASS_ARCANE:
		{
			cn = "Arcane";
		}
		case CLASS_NAGA:
		{
			cn = "Naga";
		}
		case CLASS_CLOCKWORK:
		{
			cn = "Clockwork";
		}
		case CLASS_EVIL:
		{
			cn = "Otherworld";
		}
		case CLASS_SPACE:
		{
			cn = "Space";
		}
	}
	return(cn);
}

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
	
	if(hasCardsInDeck || (trQuestVarGet("commanderClass") == class)){
		trQuestVarSet("classesInDeck", trQuestVarGet("classesInDeck") + 1);
		if(getClassProgress(class) < 1){
			ChatLog(1, "ERROR! Cards in locked class: " + class);
			valid = false;
		}
	}
	
	return (valid);
}

bool ValidateCollection(){
	if(getClassProgress(0) <= 0){
		setDeckCommander(-1);
	}
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
	
	string cardsInDeckColor = "";
	if(trQuestVarGet("cardsInDeck") != 40){
		ChatLog(1, "ERROR! Not 40 cards in deck! " + 1*trQuestVarGet("cardsInDeck") + "/40");
		valid = false;
		cardsInDeckColor = "<color={Playercolor(2)}>";
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
	
	trCounterAbort("deckCount");
	trCounterAddTime("deckCount", -1, -9999999, cardsInDeckColor+"Deck: " + 1*trQuestVarGet("cardsInDeck") + "/40");
	
	return (valid);
}

void CollectionDeploy(int card = 0, int x = 0, int z = 0, bool cardIsCommander = false, int class = 0){
	trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("1,10","Dwarf",1,x,0,z,180,true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("next"), true);
	
	int proto = CardToProto(card);
	int spell = CardToSpell(card);
	
	if(cardIsCommander){
		proto = card;
		spell = SPELL_COMMANDER;
	}
	
	if (spell == 0 || spell == SPELL_COMMANDER) {
		trUnitChangeName("(" + 1*trQuestVarGet("card_" + proto + "_Cost") + ") " + trStringQuestVarGet("card_" + proto + "_Name"));
		trUnitChangeProtoUnit(kbGetProtoUnitName(proto));
	} else {
		trUnitChangeName("(" + 1*trQuestVarGet("spell_" + spell + "_Cost") + ") " + trStringQuestVarGet("spell_" + spell + "_Name"));
		proto = kbGetProtoUnitID("Statue of Lightning");
		trUnitChangeProtoUnit("Statue of Lightning");
		trSetSelectedScale(0.75, 0.1 + xsSqrt(trQuestVarGet("spell_" + spell + "_cost")) * 0.2, 0.75);
		trUnitSetAnimationPath(""+1*trQuestVarGet("spell_"+spell+"_animation") + ",0,0,0,0");
	}

	yAddToDatabase("class"+class+"units", "next");
	yAddUpdateVar("class"+class+"units", "proto", proto);
	yAddUpdateVar("class"+class+"units", "spell", spell);
	
	trModifyProtounit(kbGetProtoUnitName(proto), 1, 1, 9999999999999999999.0);
	trModifyProtounit(kbGetProtoUnitName(proto), 1, 1, -9999999999999999999.0);
}

int CommanderToProtounit(int commander = 0){
	switch(commander)
	{
		case COMMANDER_ROGERS:
		{
			return (kbGetProtoUnitID("Hero Greek Jason"));
		}
		case COMMANDER_VENLESH:
		{
			return (kbGetProtoUnitID("Maceman Hero"));
		}
		case COMMANDER_NANO:
		{
			return (kbGetProtoUnitID("Oracle Hero"));
		}
		case COMMANDER_NOTTUD:
		{
			return (kbGetProtoUnitID("Minotaur"));
		}
		case COMMANDER_REACH:
		{
			return (kbGetProtoUnitID("Royal Guard Hero"));
		}
		case COMMANDER_SCRAGINS:
		{
			return (kbGetProtoUnitID("Archer Atlantean Hero"));
		}
		case COMMANDER_ROXAS:
		{
			return (kbGetProtoUnitID("Arkantos God"));
		}
		case COMMANDER_YEEBAAGOOON:
		{
			return (kbGetProtoUnitID("Pharaoh of Osiris"));
		}
		case COMMANDER_ZENOPHOBIA:
		{
			return (kbGetProtoUnitID("Hoplite"));
		}
		case COMMANDER_ANRAHEIR:
		{
			return (kbGetProtoUnitID("Hero Greek Perseus"));
		}
		case COMMANDER_NICK:
		{
			return (kbGetProtoUnitID("Hero Greek Odysseus"));
		}
		case COMMANDER_GOD:
		{
			return (kbGetProtoUnitID("Caravan Atlantean"));
		}
	}
	return (commander);
	//ThrowError("CommanderToProtounit");
}

string CommanderName(int commander = 0){
	string name = "WHO DA FUCK";
	switch(commander)
	{
		case COMMANDER_ROGERS:
		{
			name = "phdorogers4";
		}
		case COMMANDER_VENLESH:
		{
			name = "Venlesh";
		}
		case COMMANDER_NANO:
		{
			name = "nanodude";
		}
		case COMMANDER_NOTTUD:
		{
			name = "nottud";
		}
		case COMMANDER_REACH:
		{
			name = "out reach";
		}
		case COMMANDER_SCRAGINS:
		{
			name = "scragins";
		}
		case COMMANDER_ROXAS:
		{
			name = "Roxas";
		}
		case COMMANDER_YEEBAAGOOON:
		{
			name = "Yeebaagooon";
		}
		case COMMANDER_ZENOPHOBIA:
		{
			name = "Zenophobia";
		}
		case COMMANDER_ANRAHEIR:
		{
			name = "Anraheir";
		}
		case COMMANDER_NICK:
		{
			name = "Nickonhawk, Portal Master";
		}
		case COMMANDER_GOD:
		{
			name = "Nickonhawk, God";
		}
	}
	return (name);
	//ThrowError("CommanderToProtounit");
}

void CollectionCommander(int commander = 0, int x = 0, int z = 0, int class = 0){
	CollectionDeploy(CommanderToProtounit(commander), x, z, true, class);
}

void CollectionCard(int index = 0, int x = 0, int z = 0, int class = 0) {
	int countDeck = getCardCountDeck(index);
	int countCollection = getCardCountCollection(index);
	for(i=0;<3){
		if(countDeck > 0){
			CollectionDeploy(index, x, z + 44, false, class);
			countDeck = countDeck - 1;
		} else if(countCollection > 0){
			CollectionDeploy(index, x, z, false, class);
			countCollection = countCollection - 1;
		}
		for(j=0;<6){
			if(index > 0 && index == trQuestVarGet("packReward" + j)){
				trUnitHighlight(4.7, true);
				trQuestVarSet("packReward" + j, -1);
			}
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
					return ("First Contact");
				}
				case 3:
				{
					return ("Fools' Errand");
				}
				case 4:
				{
					return ("Prove Yourself");
				}
				case 5:
				{
					return ("Swampy Business");
				}
				case 6:
				{
					return ("The Imposter");
				}
			}
		}
		case CLASS_ARCANE:
		{
			switch(mission)
			{
				case 1:
				{
					return ("At the School Gates");
				}
				case 2:
				{
					return ("The Tour");
				}
				case 3:
				{
					return ("The Library");
				}
				case 4:
				{
					return ("Playtime");
				}
				case 5:
				{
					return ("The Elevator");
				}
				case 6:
				{
					return ("Lab of the Mad Scientist");
				}
			}
		}
		case CLASS_NAGA:
		{
			switch(mission)
			{
				case 1:
				{
					return ("Waves");
				}
				case 2:
				{
					return ("Underwater");
				}
				case 3:
				{
					return ("Reef");
				}
				case 4:
				{
					return ("Bubbles");
				}
				case 5:
				{
					return ("Deep Gate");
				}
				case 6:
				{
					return ("Deep Palace");
				}
			}
		}
		case CLASS_CLOCKWORK:
		{
			switch(mission)
			{
				case 1:
				{
					return ("The Scrapyard");
				}
				case 2:
				{
					return ("Profit Raid");
				}
				case 3:
				{
					return ("Sneak Mission");
				}
				case 4:
				{
					return ("Ride The Lightning");
				}
				case 5:
				{
					return ("Minigames Z");
				}
				case 6:
				{
					return ("The Supervillain");
				}
			}
		}
		case CLASS_EVIL:
		{
			switch(mission)
			{
				case 1:
				{
					return ("Separated");
				}
				case 2:
				{
					return ("Den of Spiders");
				}
				case 3:
				{
					return ("A Being From Beyond");
				}
				case 4:
				{
					return ("Lights, Camera, and Zombies");
				}
				case 5:
				{
					return ("The Ritual");
				}
				case 6:
				{
					return ("Nightfall");
				}
			}
		}
		case CLASS_SPACE:
		{
			switch(mission)
			{
				case 1:
				{
					return ("Hoof, Sword and Arrow");
				}
				case 2:
				{
					return ("Magical Staff");
				}
				case 3:
				{
					return ("Water Horse");
				}
				case 4:
				{
					return ("Cogs");
				}
				case 5:
				{
					return ("Nasty Hand");
				}
				case 6:
				{
					return ("Black Star");
				}
			}
		}
	}
	return("N/A");
}

void SetupClass(int class = 0, int terrainType = 0, int terrainSubType = 0){
	int progress = getClassProgress(class);
	int x = 0;
	int z = 0;
	bool doClass = false;
	
	if(progress > 0){
		doClass = true;
	}
	/*
	for(i = (30 * class) + 7;<30 * (class + 1)){
		if(getCardCountCollection(i) > 0 || getCardCountDeck(i) > 0){
			doClass = true;
			break;
		}
	}
	*/
	
	if(doClass){
		//ChatLog(1, "Setup Class: " + class + " Progress: " + progress);
		trPaintTerrain(10 * class, 0, 10 + 10 * class, 43, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(1 + 10 * class, 0, 9 + 10 * class, 20, terrainType, terrainSubType, false);
		trPaintTerrain(1 + 10 * class, 22, 9 + 10 * class, 42, terrainType, terrainSubType, false);
		/* Cards */
		x = 3 + 20 * class; z = 37;
		for(i = 30 * class;<30 * (class + 1)){
			if(progress < 1 && i < (30 * class) + 7){
				continue;
			}
			if(i == 14 + 30 * class){
				/* First Legendary */
				CollectionCard(i,9 + 20 * class,35, class);
			} else if(i == 29 + 30 * class){
				/* Second Legendary */
				CollectionCard(i,13 + 20 * class,35, class);
			} else {
				CollectionCard(i,x,z, class);
				z = z - 4;
				if(i == 9 + 30 * class){
					x = 9 + 20 * class; z = 31;
				}
				if(i == 18 + 30 * class){
					x = 15 + 20 * class; z = 37;
				}
			}
		}
		
		if(progress > 0){
			z = 41;
			/* Commanders */
			if(getDeckCommander() ==  (2 * class)){
				trQuestVarSet("currentCommander", trGetNextUnitScenarioNameNumber());
				z = z + 44;
			}
			CollectionCommander(2 * class, 5 + 20 * class, z, class);
			if(progress > 6){
				z = 41;
				if(getDeckCommander() == (2 * class + 1)){
					trQuestVarSet("currentCommander", trGetNextUnitScenarioNameNumber());
					z = z + 44;
				}
				CollectionCommander(2 * class + 1, 17 + 20 * class, z, class);
			}
			
			/* Missions */
			x = 11 + 20 * class; z = 91;
			for(i=1;<=xsMin(progress,6)){
				trQuestVarSet("class" + class + "Mission" + i, trGetNextUnitScenarioNameNumber());
				trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
				trArmySelect("1,10");
				trUnitChangeName(GetMissionTitle(class,i));
				trUnitChangeProtoUnit("Outpost");
				trSetSelectedScale(1.0, 0.3, 1.0);
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
}

string collectionReward = "";

void CollectionGodPowers(){
	trCounterAbort("tooltipSpace");
	trCounterAbort("tooltipEnter");
	trCounterAbort("mission");
	trCounterAbort("reward");
	/*
	if(collectionMission != ""){
		trCounterAddTime("mission", -1, -9999999, collectionMission);
	}
	if(collectionReward != ""){
		trCounterAddTime("reward", -1, -9999999, collectionReward);
	}
	*/
	trPlayerKillAllGodPowers(1);
	trTechGodPower(1, "animal magnetism", 1);
	trTechGodPower(1, "create gold", 1);

	if(trQuestVarGet("canPressEnter") == 1){
		//trTechGodPower(1, "rain", 1);
		trTechGodPower(1, "rain", 1);
		trCounterAddTime("tooltipEnter", -1, -9999999, "(Press ENTER to save and quit)");
	} else {
		xsDisableRule("CollectionEnter");
	}
	trCounterAddTime("tooltipSpace", -1, -9999999, "(Press SPACE to save/load/delete decks)");
}

rule Collection
highFrequency
inactive
{
	trCameraCut(vector(-58.161659,112.294716,-58.161659),vector(0.500000,-0.707107,0.500000),vector(0.500000,0.707107,0.500000),vector(0.707107,0.000000,-0.707107));
	xsEnableRule("CollectionClick");
	xsEnableRule("CollectionSelect");
	trQuestVarSet("lastSelected", -1);
	trSetFogAndBlackmap(false, false);
	unitTransform("Statue of Automaton Base","Victory Marker");
	trPaintTerrain(0, 0, 60, 60, 5, 4, false); //Black
	for(i=1; <= 28) {
		trObjectiveSetID(i, i);
	}
	// trChatHistoryClear();
	/*
	// we used to need this for the collection reload but not anymore
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
	}
	yClearDatabase("allUnits");
	*/
	trQuestVarSet("activePlayer", 1);
	trQuestVarSet("idsStart", trGetNextUnitScenarioNameNumber());
	collectionMission = "";
	collectionReward = "";
	trQuestVarSet("missionSelection", -1);
	trQuestVarSet("missionClass", -1);
	ValidateCollection();
	if(true){
		trUIFadeToColor(0,0,0,1000,0,false);
		xsEnableRule("CollectionEnter");
		xsEnableRule("CollectionSpace");
		trQuestVarSet("canPressEnter", 1);
		if(getClassProgress(CLASS_ADVENTURER) == 1 && getClassProgress(CLASS_ARCANE) == 1){
			DialogAdd("This is your Collection and Deck. Right Click a Card to move it between the two.");
			DialogAdd("Cards above the blue horizontal line are in your Deck, while cards below it are in your Collection.");
			DialogAdd("Each column corresponds to a class. The first column has Adventurer cards and the second one has Arcane.");
			DialogAdd("Your Deck must have a Commander and 40 Cards from one or two Classes.");
			DialogAdd("The Deck you make will be used for Story Missions as well as PvP when playing Multiplayer.");
			DialogAdd("The Story Missions are Obelisks. They reward packs containing Class Cards.");
			DialogAdd("After beating a Mission you can replay it on Hardmode for packs containing Random Cards.");
			DialogAdd("After completing a Class Story you will unlock the second Commander for that Class.");
			DialogAdd("Complete your first Class Story to unlock the other Classes.");
			DialogStart();
		}
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

	/*
	If the player has completed the story for all current classes,
	they can choose a new one.
	*/
	bool newClass = true;
	int totalProgress = 0;
	for(i=CLASS_ADVENTURER; < CLASS_SPACE) {
		totalProgress = totalProgress + getClassProgress(i);
		if (getClassProgress(i) < 7 && getClassProgress(i) > 0) {
			newClass = false;
			break;
		}
	}

	if (newClass) {
		if (totalProgress == 35) {
			if (getClassProgress(CLASS_SPACE) == 0) {
				// DISABLED FOR BETA
				//trDelayedRuleActivation(""); // unlock space
			}
		} else if (totalProgress == 14) {
			// BETA ONLY. Players will unlock one extra class of their choosing for the beta
			trDelayedRuleActivation("ChooseNewClass_00"); // choose next class to unlock
		} else {
			// DISABLED FOR BETA
			//trDelayedRuleActivation("ChooseNewClass_00"); // choose next class to unlock
		}
	}
	
	xsDisableRule("Collection");
}

// Given the click coordinates, which class are we looking at?
int classFromPos(string v = "") {
	int class = trVectorQuestVarGetX(v) / 20;
	return(class);
}

rule CollectionClick
highFrequency
inactive
{
	if (trQuestVarGet("p1click") > 0) {
		int class = classFromPos("p1ClickPos");
		switch(1*trQuestVarGet("p1click"))
		{
			case LEFT_CLICK:
			{
				uiClearSelection();
				trClearCounterDisplay();
				trSoundPlayDialog("default", "1", -1, false, " : ", "");
				if (class != trQuestVarGet("p1ClickClass")) {
					trQuestVarSet("missionSelection", 0);
					trQuestVarSet("missionClass", 0);
					collectionMission = "";
					collectionReward = "";
					trQuestVarSet("p1ClickClass", class);
				}
				CollectionGodPowers();
			}
			case RIGHT_CLICK:
			{
				for(x=yGetDatabaseCount("class"+class+"units"); >0) {
					int id = yDatabaseNext("class"+class+"units", true);
					float dist = trDistanceToVectorSquared("class"+class+"units","p1clickPos");
					if(dist < 4){
						trVectorSetUnitPos("temp","class"+class+"units");
						if(1*yGetVar("class"+class+"units", "spell") == SPELL_COMMANDER){
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
								trQuestVarSet("currentCommander", trQuestVarGet("class"+class+"units"));
								ChatLog(1, "Commander chosen");
							} else {
								ChatLog(1, "Deck must have a Commander");
							}
						} else {
							int card = 0;
							string name = "";
							if(1*yGetVar("class"+class+"units", "spell") == 0){
								card = ProtoToCard(kbGetUnitBaseTypeID(id));
								name = trStringQuestVarGet("card_"+kbGetUnitBaseTypeID(id)+"_Name");
							} else {
								card = SpellToCard(1*yGetVar("class"+class+"units", "spell"));
								name = trStringQuestVarGet("spell_"+1*yGetVar("class"+class+"units", "spell")+"_Name");
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
							xsEnableRule("CollectionEnter");
							trQuestVarSet("canPressEnter", 1);
						} else {
							xsDisableRule("CollectionEnter");
							trQuestVarSet("canPressEnter", 0);
						}
						CollectionGodPowers();
						break;
					}
				}
			}
		}
		trQuestVarSet("p1click", 0);
	}
}

rule CollectionSelect
highFrequency
inactive
{
	int class = trQuestVarGet("p1ClickClass");
	for(x=xsMin(10, yGetDatabaseCount("class"+class+"units")); >0) {
		int id = yDatabaseNext("class"+class+"units", true);
		if (trUnitIsSelected() && (trQuestVarGet("lastSelected") != trQuestVarGet("class"+class+"units"))) {
			displayCardDetails(kbGetUnitBaseTypeID(id), 1*yGetVar("class"+class+"units", "spell"));
			trQuestVarCopy("lastSelected", "class"+class+"units");
			break;
		}
	}

	for(i=1;<=xsMin(getClassProgress(class),6)){
		// if we newly selected this one
		trUnitSelectClear();
		trUnitSelectByQV("class"+class+"mission"+i);
		if(trUnitIsSelected()){
			if (ValidateCollection()) {
				if (trQuestVarGet("missionSelection") != i || trQuestVarGet("missionClass") != class) {
					int cards = 2 + i;
					if(getClassProgress(class) == i){
						trQuestVarSet("missionHardmode", 0);
						collectionMission = GetMissionTitle(class,i);
						collectionReward = "(Reward: " + cards + " Class Cards)";
					} else {
						trQuestVarSet("missionHardmode", 1);
						collectionMission = GetMissionTitle(class,i) + " (HARDMODE)";
						collectionReward = "(Reward: " + cards + " Random Cards)";
					}
					trQuestVarSet("missionSelection", i);
					trQuestVarSet("missionClass", class);
					//xsEnableRule("CollectionEnter");
					trShowChoiceDialog(collectionMission, "Start " + collectionReward, EVENT_START_MISSION, "Cancel", EVENT_DESELECT);
					CollectionGodPowers();
				}
			} else {
				uiClearSelection();
				trSoundPlayFN("cantdothat.wav");
				uiMessageBox("Your deck is invalid. You cannot start a mission until your deck is valid.");
			}
		} else if ((trQuestVarGet("missionSelection") == i) && (trQuestVarGet("missionClass") == class)) { 
			// if deselect
			trQuestVarSet("missionSelection", 0);
			trQuestVarSet("missionClass", 0);
			collectionMission = "";
			collectionReward = "";
			CollectionGodPowers();
		}
	}
}

void CollectionStartMission(int eventId = -1) {
	xsSetContextPlayer(0);
	trPlayerKillAllGodPowers(1);
	trCounterAbort("tooltipEnter");
	//xsDisableRule("CollectionEnter");
	trClearCounterDisplay();
	trSoundPlayDialog("default", "1", -1, false, " : ", "");
	trCounterAbort("deckCount");
	trCounterAbort("mission");
	trCounterAbort("reward");
	xsDisableRule("CollectionClick");
	xsDisableRule("CollectionSelect");
	xsDisableRule("CollectionEnter");
	xsDisableRule("CollectionSpace");
	ChatLog(1, "Starting Mission: " + GetMissionTitle(trQuestVarGet("missionClass"),trQuestVarGet("missionSelection")));
	trCounterAbort("tooltipSpace");
	saveDeckAndProgress();
	int next = trGetNextUnitScenarioNameNumber();
	for(i=trQuestVarGet("idsStart");<next){
		trUnitSelectClear();
		trUnitSelect(""+i);
		trUnitDestroy();
	}
	xsEnableRule("MissionBegin");
	for(i=0; < 6) {
		if (yDatabaseExists("class"+i+"units")) {
			for(x=yGetDatabaseCount("class"+i+"units"); >0) {
				yDatabaseNext("class"+i+"units");
				string protoname = kbGetProtoUnitName(1*yGetVar("class"+i+"units", "proto"));
				if(protoname != "Cinematic Block"){
					trModifyProtounit(protoname, 1, 1, 9999999999999999999.0);
					trModifyProtounit(protoname, 1, 1, -9999999999999999999.0);
					trModifyProtounit(protoname, 1, 1, 10);
				}
			}
			yClearDatabase("class"+i+"units");
			yDeleteDatabase("class"+i+"units");
		}
	}
}


rule CollectionEnter
highFrequency
inactive
{
	if (trCheckGPActive("rain", 1)) {
		// trChatHistoryClear();
		saveDeckAndProgress();
		map("mouse1down", "game", "uiSelectionButtonDown");
		map("mouse2up", "game", "uiWorkAtPointer");
		map("mouse2doubleup", "game", "uiWorkAtPointer");
		map("delete", "game", "uiDeleteSelectedUnit");
		map("space", "game", "uiLookAtSelection");
		map("enter", "game", "gadgetReal(\"chatInput\") uiIgnoreNextKey");
		trModeEnter("Pregame");
	}
}

string displayDeckDetails(int slot = 0) {
	string result = "Empty slot";
	if (slot <= getDeckCount()) {
		vector metadata = readDeckCommanderAndClass(slot);
		vector counts = readDeckCardCount(slot);
		string commander = CommanderName(1*xsVectorGetX(metadata));
		string first = ClassName(1*xsVectorGetY(metadata)) + " x" + 1*xsVectorGetX(counts);
		string second = ClassName(1*xsVectorGetZ(metadata)) + " x" + 1*xsVectorGetY(counts);
		result = commander + " - " + first + ", " + second;
	}
	return(result);
}

void loadOrDeleteFile(int eventId = -1) {
	if (getDeckCount() > 0) {
		trQuestVarSet("selectionLimit", getDeckCount());
		trShowChoiceDialog("Load or delete a deck?", "Load", EVENT_NEXT_LOAD, "Delete", EVENT_NEXT_DELETE);
	} else {
		uiMessageBox("No decks to load or delete.");
	}
}

void nextFile(int eventId = -1) {
	trQuestVarSet("collectionEvent", eventId);
	trDelayedRuleActivation("CollectionScrollThroughFiles");
}

void saveToFile(int eventId = -1) {
	trSetCurrentScenarioUserData(COMMANDS, COMMAND_SAVE_DECK);
	trSetCurrentScenarioUserData(COMMANDS + 1, 1*trQuestVarGet("filenum"));
	saveDeckAndProgress();
	trGameLoadScenario(collectionFilename);
}

void loadFromFile(int eventId = -1) {
	copyDeckData(1*trQuestVarGet("filenum"));
	subModeEnter("Simulation", "Editor");
	uiMessageBox("moo","restartCurrentGame()");
	uiCycleCurrentActivate();
	subModeLeave("Simulation", "Editor");
	modeEnter("pregame");
	modeEnter("Simulation");
}

void deleteFile(int eventId = -1) {
	trSetCurrentScenarioUserData(COMMANDS, COMMAND_DELETE_DECK);
	trSetCurrentScenarioUserData(COMMANDS + 1, 1*trQuestVarGet("filenum"));
	trGameLoadScenario(collectionFilename);
}

rule CollectionScrollThroughFiles
inactive
highFrequency
{
	int eventId = trQuestVarGet("collectionEvent");
	trQuestVarSet("filenum", 1 + trQuestVarGet("filenum"));
	int fn = trQuestVarGet("filenum");
	string confirm = "What";
	switch(eventId)
	{
		case EVENT_NEXT_SAVE:
		{
			confirm = "Save (Overwrite this file)";
		}
		case EVENT_NEXT_LOAD:
		{
			confirm = "Load";
		}
		case EVENT_NEXT_DELETE:
		{
			confirm = "Delete";
		}
	}
	if (trQuestVarGet("filenum") == trQuestVarGet("selectionLimit")) {
		if (eventId == EVENT_NEXT_SAVE) {
			confirm = "Save";
		}
		trShowChoiceDialog(displayDeckDetails(fn), confirm, eventId - 1, "Cancel", -1);
	} else {
		trShowChoiceDialog(displayDeckDetails(fn), confirm, eventId - 1, "Next...", eventId);
	}
	xsDisableSelf();
}

rule CollectionSpace
inactive
highFrequency
{
	if (trQuestVarGet("pressSpace") == 1) {
		trQuestVarSet("pressSpace", 0);
		if (trQuestVarGet("canPressEnter") == 1) { // we can save
			trQuestVarSet("filenum", 0);
			trQuestVarSet("selectionLimit", getDeckCount() + 1);
			trShowChoiceDialog("Save, Load, or Delete a deck?", "Save deck file", EVENT_NEXT_SAVE, "Load/Delete Deck", EVENT_CHOOSE_LOAD_DELETE);
		} else {
			trEventFire(EVENT_CHOOSE_LOAD_DELETE);
		}
	}
}

rule CollectionTutorial
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		trShowImageDialog("icons\improvement architects icon 64", "This is your Collection and Deck. Right Click a card to move it between the two.");
		trSoundPlayFN("ui\scroll.wav","1",-1,"","");
		xsDisableSelf();
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

void ChooseThisClass(int eventID = -1) {
	xsSetContextPlayer(0);
	setClassProgress(1*trQuestVarGet("nextClass"), 1);
	saveDeckAndProgress();
	trDelayedRuleActivation("ChooseNewClass_02");
}

void ChooseNextClass(int eventID = -1) {
	xsSetContextPlayer(0);
	bool found = false;
	while(found == false) {
		trQuestVarSet("nextClass", iModulo(5, 1*trQuestVarGet("nextClass") + 1));
		if (getClassProgress(1*trQuestVarGet("nextClass")) == 0) {
			found = true;
			break;
		}
	}
	trDelayedRuleActivation("ChooseNewClass_01");
}

rule ChooseNewClass_00
highFrequency
inactive
{
	if (trTime() > cActivationTime) {
		uiMessageBox("You are ready to unlock your next class!");
		trQuestVarSet("nextClass", 0);
		trEventSetHandler(EVENT_CHOOSE_CLASS, "ChooseThisClass");
		trEventSetHandler(EVENT_NEXT_CLASS, "ChooseNextClass");
		trEventFire(EVENT_NEXT_CLASS);
		xsDisableSelf();
	}
}

rule ChooseNewClass_01
highFrequency
inactive
{
	if (trIsGadgetVisible("ingame-messagedialog") == false) {
		int class = trQuestVarGet("nextClass");
		trShowChoiceDialog(ClassName(class), "Unlock", EVENT_CHOOSE_CLASS, "Or...", EVENT_NEXT_CLASS);
		xsDisableSelf();
	}
}

rule ChooseNewClass_02
highFrequency
inactive
{
	trDelayedRuleActivation("ChooseNewClass_03");
	xsDisableSelf();
	// TODO: Make this flashy
	trShowImageDialog("HeavenGames\class"+1*trQuestVarGet("nextClass")+"unlock0", "New class unlocked!");
	trSoundPlayFN("ageadvance.wav");
}

rule ChooseNewClass_03
highFrequency
inactive
{
	if (trTime() > cActivationTime) {
		trShowImageDialog("HeavenGames\class"+1*trQuestVarGet("nextClass")+"unlock1", "New Commander unlocked!");
		trSoundPlayFN("ui\thunder"+1*trQuestVarGet("nextClass")+".wav");
		trSoundPlayFN("herocreation.wav");
		xsDisableSelf();
		xsEnableRule("ChooseNewClass_04");
	}
}

rule ChooseNewClass_04
highFrequency
inactive
{
	if (trIsGadgetVisible("ShowImageBox") == false) {
		saveCollection();
	}
}