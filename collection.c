/*
These are functions are called to play the storyline
CinematicReset();
CinematicAdd("icons\infantry g hoplite icon 64", "pen island");
CinematicStart();
*/

void CinematicReset() {
	trQuestVarSet("cinematicStep", 0);
	trQuestVarSet("cinematicLength", 0);
}

/*
i = icon
s = string text
*/
void CinematicAdd(string i = "", string s = "") {
	trQuestVarSet("cinematicLength", 1 + trQuestVarGet("cinematicLength"));
	trStringQuestVarSet("cinematicImage"+1*trQuestVarGet("cinematicLength"), i);
	trStringQuestVarSet("cinematicText"+1*trQuestVarGet("cinematicLength"), s);
}

/*
m = music filename
*/
void CinematicStart(string m = "") {
	trMusicPlay(m, "1", 0);
	xsEnableRule("Story_Cinematic_Play");
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
		trUnitChangeName(trStringQuestVarGet("card_" + proto + "_Name"));
		trUnitChangeProtoUnit(kbGetProtoUnitName(proto));
	} else {
		trUnitChangeName(trStringQuestVarGet("spell_" + spell + "_Name"));
		proto = kbGetProtoUnitID("Statue of Lightning");
		trUnitChangeProtoUnit("Statue of Lightning");
		trSetSelectedScale(0.75, 0.2 + xsSqrt(trQuestVarGet("spell_" + spell + "_cost")) * 0.4, 0.75);
		trUnitSetAnimationPath(""+1*trQuestVarGet("spell_"+spell+"_animation") + ",0,0,0,0");
	}

	yAddToDatabase("class"+class+"units", "next");
	yAddUpdateVar("class"+class+"units", "proto", proto);
	yAddUpdateVar("class"+class+"units", "spell", spell);
	
	//trModifyProtounit(kbGetProtoUnitName(proto), 1, 1, 9999999999999999999.0);
	//trModifyProtounit(kbGetProtoUnitName(proto), 1, 1, -9999999999999999999.0);
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
					return ("Shrubbery Lane");
				}
				case 2:
				{
					return ("Standard Procedure");
				}
				case 3:
				{
					return ("Carbon-Free Antivirus");
				}
				case 4:
				{
					return ("Swampy Hideout");
				}
				case 5:
				{
					return ("Forest Heart");
				}
				case 6:
				{
					return ("The Real Fight");
				}
			}
		}
		case CLASS_ARCANE:
		{
			switch(mission)
			{
				case 1:
				{
					return ("Tower Courtyard");
				}
				case 2:
				{
					return ("Flammable Fire");
				}
				case 3:
				{
					return ("Freezing Frost");
				}
				case 4:
				{
					return ("Elevator");
				}
				case 5:
				{
					return ("Archmage");
				}
				case 6:
				{
					return ("On Top Of The Arcane Tower");
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
					return ("A Dastardly Trap");
				}
				case 5:
				{
					return ("Minigames Z");
				}
				case 6:
				{
					return ("The Final Boss?");
				}
			}
		}
		case CLASS_EVIL:
		{
			switch(mission)
			{
				case 1:
				{
					return ("The Old Lands");
				}
				case 2:
				{
					return ("Den of Spiders");
				}
				case 3:
				{
					return ("Nightfall");
				}
				case 4:
				{
					return ("Crossing Over");
				}
				case 5:
				{
					return ("The Otherworld");
				}
				case 6:
				{
					return ("Zeno's Paradox");
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
	ThrowError("GetMissionTitle");
}

void SetupClass(int class = 0, int terrainType = 0, int terrainSubType = 0){
	int progress = getClassProgress(class);
	int x = 0;
	int z = 0;
	bool doClass = false;
	
	if(progress > 0){
		doClass = true;
	}
	
	for(i = (30 * class) + 7;<30 * (class + 1)){
		if(getCardCountCollection(i) > 0 || getCardCountDeck(i) > 0){
			doClass = true;
			break;
		}
	}
	
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
	xsEnableRule("CollectionSelect");
	trQuestVarSet("lastSelected", -1);
	trSetFogAndBlackmap(false, false);
	unitTransform("Statue of Automaton Base","Victory Marker");
	trPaintTerrain(0, 0, 60, 60, 5, 4, false); //Black
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
	trQuestVarSet("canPressEnter", -1);
	ValidateCollection();
	if(true){
		trUIFadeToColor(0,0,0,1000,0,false);
		xsEnableRule("CollectionSpace");
		trCounterAddTime("tooltipSpace", -1, -9999999, "(Press SPACE to save deck and QUIT)");
		trQuestVarSet("canPressSpace", 1);
		if(getClassProgress(CLASS_ADVENTURER) == 1 && getClassProgress(CLASS_ARCANE) == 1){
			CinematicReset();
			CinematicAdd("icons\improvement architects icon 64", "This is your Collection and Deck. Right Click a Card to move it between the two.");
			CinematicAdd("icons\improvement architects icon 64", "Your Deck must have a Commander and 40 Cards from one or two Classes.");
			CinematicAdd("icons\improvement architects icon 64", "The Deck you make will be used for Story Missions as well as PvP when playing Multiplayer.");
			CinematicAdd("icons\building outpost icon 64", "The Story Missions are Outposts. They reward packs containing Class Cards.");
			CinematicAdd("icons\building outpost icon 64", "After beating a Mission you can replay it on Hardmode for packs containing Random Cards.");
			CinematicAdd("icons\building outpost icon 64", "After completing a Class Story you will unlock the second Commander for that Class.");
			CinematicAdd("icons\improvement rheias gift icons 64", "Complete your first Class Story to unlock the other Classes.");
			CinematicStart();
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
					trQuestVarSet("canPressEnter", 0);
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
		trQuestVarSet("p1click", 0);
	}
}

rule CollectionSelect
highFrequency
inactive
{
	int class = trQuestVarGet("p1ClickClass");
	for(x=xsMin(3, yGetDatabaseCount("class"+class+"units")); >0) {
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
			if (trQuestVarGet("missionSelection") != i || trQuestVarGet("missionClass") != class) {
				int cards = 2 + i;
				if(getClassProgress(class) == i){
					trQuestVarSet("missionHardmode", 0);
					collectionMission = GetMissionTitle(class,i);
					collectionReward = "Reward: " + cards + " Class Cards";
				} else {
					trQuestVarSet("missionHardmode", 1);
					collectionMission = GetMissionTitle(class,i) + " (HARDMODE)";
					collectionReward = "Reward: " + cards + " Random Cards";
				}
				trQuestVarSet("missionSelection", i);
				trQuestVarSet("missionClass", class);
				xsEnableRule("CollectionEnter");
				trQuestVarSet("canPressEnter", 1);
				CollectionGodPowers();
			}
		} else if ((trQuestVarGet("missionSelection") == i) && (trQuestVarGet("missionClass") == class)) { 
			// if deselect
			trQuestVarSet("canPressEnter", 0);
			trQuestVarSet("missionSelection", 0);
			trQuestVarSet("missionClass", 0);
			collectionMission = "";
			collectionReward = "";
			CollectionGodPowers();
		}
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
				trCounterAbort("deckCount");
				trCounterAbort("mission");
				trCounterAbort("reward");
				xsDisableRule("CollectionClick");
				xsDisableRule("CollectionSelect");
				xsDisableRule("CollectionSpace");
				ChatLog(1, "Starting Mission: " + GetMissionTitle(trQuestVarGet("missionClass"),trQuestVarGet("missionSelection")));
				trCounterAbort("tooltipSpace");
				dataSave();
				/*
				// do we really need this?
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
				*/
				int next = trGetNextUnitScenarioNameNumber();
				for(i=trQuestVarGet("idsStart");<next){
					trUnitSelectClear();trUnitSelect(""+i);
					trUnitDestroy();
				}
				xsEnableRule("MissionBegin");
				for(i=0; < 6) {
					if (trQuestVarGet("class"+i+"units") > 0) {
						yDeleteDatabase("class"+i+"units");
					}
				}
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
			// trChatHistoryClear();
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
