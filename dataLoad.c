/*
Slots 0-5 = progress on storyline only

ignore this part
1 bit = class in deck?
1 bit = class is first or second (0 = first class)
1 bit = selected commander


3 bits for progress on storyline


ignore this part
2 x 7 bits = collectible commons 7-13 in collection
1 bit = collectible legendary in collection



Slots 6-7 = cards from class 1 in current deck
Slots 8-9 = cards from class 2 in current deck

Slot 10 = commander of deck and which classes in deck

Slot 11 = Command
Slot 12-15 = Command data

ignore this now
Slots 10-15 = collectible class cards in collection
*/

/*
If you want a full collection for a particular class:
The progress + metadata slot for that class should have the number: 2097088
+ 1 if class is in the deck
+ 2 if the class is second
+ 4 if the selected commander is second
+ 8 * storyline progress

The collectible class cards number should be: 536870911
*/

int deckc1d0 = 0;
int deckc1d1 = 0;
int deckc2d0 = 0;
int deckc2d1 = 0;

/*
This function assumes the following:
- the quest vars named "class1" and "class2" are properly set.
- the "commander" quest var is properly set.
- there are only two classes in the "deck" database
*/
void saveDeckAndProgress() {
	trQuestVarCopy("p1commanderType", "commander");
	int card = 0;
	int c = trQuestVarGet("class1");
	int data = 0;
	int power = 1;
	for(x=0; <15) {
		card = x + 30 * c;
		data = data + power * getCardCountDeck(card);
		power = power * 4;
	}
	trSetCurrentScenarioUserData(6, data);
	data = 0;
	power = 1;
	for(x=15; <30) {
		card = x + 30 * c;
		data = data + power * getCardCountDeck(card);
		power = power * 4;
	}
	trSetCurrentScenarioUserData(7, data);
	
	if (trQuestVarGet("class1") == trQuestVarGet("class2")) {
		trSetCurrentScenarioUserData(8, 0);
		trSetCurrentScenarioUserData(9, 0);
	} else {
		c = trQuestVarGet("class2");
		data = 0;
		power = 1;
		for(x=0; <15) {
			card = x + 30 * c;
			data = data + power * getCardCountDeck(card);
			power = power * 4;
		}
		trSetCurrentScenarioUserData(8, data);
		data = 0;
		power = 1;
		for(x=15; <30) {
			card = x + 30 * c;
			data = data + power * getCardCountDeck(card);
			power = power * 4;
		}
		trSetCurrentScenarioUserData(9, data);
	}

	int currentdata = trQuestVarGet("class2");
	data = 0;
	data = data * 6 + currentdata;
	currentdata = trQuestVarGet("class1");
	data = data * 6 + currentdata;
	currentdata = trQuestVarGet("commander");
	data = data * 12 + currentdata;
	trSetCurrentScenarioUserData(10, data);
	
	/*
	Saving class progress data
	*/
	for(c=0; <6) {
		/*
		if (trQuestVarGet("class1") == c) {
			data = data + 1; // set the first 2 bits
			data = data + 4 * (1 * trQuestVarGet("commander") - 2 * c); // set the commander bit
		} else if (trQuestVarGet("class2") == c) {
			data = data + 3; // set the first bit
		}
		*/
		data = trQuestVarGet("class"+c+"progress"); // progress is bits 3-5
		trSetCurrentScenarioUserData(c, data);
		
		/*
		power = 64; // skip first 6 bits to add collectible cards
		for(x=7; <15) {
			card = x + 30 * c;
			data = data + power * trQuestVarGet("card_"+card+"_count");
			power = power * 4;
		}
		trSetCurrentScenarioUserData(c, data);
		
		data = 0;
		power = 1;
		for(x=15; < 30) {
			card = x + 30 * c;
			data = data + power * trQuestVarGet("card_"+card+"_count");
			power = power * 4;
		}
		trSetCurrentScenarioUserData(c+10, data);
		*/
	}
}

void saveCollection() {
	trSetCurrentScenarioUserData(COMMANDS, COMMAND_UPDATE_COLLECTION);
	trGameLoadScenario(collectionFilename);
}

void showLoadProgress(int p = 0) {
	trSoundPlayFN("default","1",-1,"Loading Data:"+100 * p / 22,"icons\god power reverse time icons 64");
}

void loadDeckCommanderAndClass(int slot = 0) {
	vector meta = readDeckCommanderAndClass(slot);
	trQuestVarSet("commander", xsVectorGetX(meta));
	trQuestVarSet("class1", xsVectorGetY(meta));
	trQuestVarSet("class2", xsVectorGetZ(meta));
}

void loadDeck(int slot = 0) {
	string fn = slotFilename(slot);

	int c = 0;
	int data = 0;
	int card = 0;

	loadDeckCommanderAndClass(slot);

	c = 30 * trQuestVarGet("class1");
	data = trGetScenarioUserData(6, fn);
	for(x=0;<15) {
		card = c + x;
		trQuestVarSet("card_"+card+"_countInDeck", iModulo(4, data));
		data = data / 4;
		if (data == 0) {
			break;
		}
	}
	data = trGetScenarioUserData(7, fn);
	for(x=15;<30) {
		card = c + x;
		trQuestVarSet("card_"+card+"_countInDeck", iModulo(4, data));
		data = data / 4;
		if (data == 0) {
			break;
		}
	}
	if ((trQuestVarGet("class1") == trQuestVarGet("class2")) == false) {
		c = 30 * trQuestVarGet("class2");
		data = trGetScenarioUserData(8, fn);
		for(x=0;<15) {
			card = c + x;
			trQuestVarSet("card_"+card+"_countInDeck", iModulo(4, data));
			data = data / 4;
			if (data == 0) {
				break;
			}
		}
		data = trGetScenarioUserData(9, fn);
		for(x=15;<30) {
			card = c + x;
			trQuestVarSet("card_"+card+"_countInDeck", iModulo(4, data));
			data = data / 4;
			if (data == 0) {
				break;
			}
		}
	}
}

void getNewCard(int card = 0) {
	int data = 0;
	for(i=COMMANDS + 1; < 16) {
		data = trGetScenarioUserData(i);
		if (data < 32400) { // less than 180
			data = data * 180 + card;
			trSetCurrentScenarioUserData(i, data);
			break;
		}
	}
}

rule data_load_00
highFrequency
inactive
{
	if (trQuestVarGet("cardsReady") == 1) {
		int data = 0;
		int bit = 0;
		int card = 0;
		
		
		for(x=0; < 6) {
			data = trGetScenarioUserData(x, mainFilename);
			/*
			bit = iModulo(2, data);
			// Check if class is in deck
			if (bit == 1) {
				data = data / 2;
				bit = iModulo(2, data);
				// Check if class is first or second
				if (bit == 1) {
					trQuestVarSet("class2", x);
				} else {
					trQuestVarSet("class1", x);
					data = data / 2;
					bit = iModulo(2, data);
					// Calculate commander
					trQuestVarSet("commander", 2*trQuestVarGet("class1") + bit);
				}
			}
			
			data = trGetScenarioUserData(x, mainFilename);
			data = data / 8;
			*/
			trQuestVarSet("class"+x+"progress", iModulo(8, data));
		}

		loadDeckCommanderAndClass(0);
		
		if (Multiplayer) {
			trSoundPlayFN("default","1",-1,"Loading:","icons\god power reverse time icons 64");
			trUIFadeToColor(0,0,0,0,0,true);
			
			for(p=2; >0) {
				trModifyProtounit("Swordsman Hero", p, 6, -100);	// population count
				trModifyProtounit("Swordsman Hero", p, 16, -1000);	// cost gold
				trModifyProtounit("Swordsman Hero", p, 17, -1000);	// cost food
				trModifyProtounit("Swordsman Hero", p, 18, -1000);	// cost wood
				trModifyProtounit("Swordsman Hero", p, 19, -1000);	// cost favor
			}
			int m = kbGetProtoUnitID("Swordsman");
			for(x=0; < 128) {
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(m);
			}
			
			trBlockAllSounds(true);
			xsEnableRule("data_load_01_ready");
		} else {
			trForbidProtounit(1, "Swordsman Hero");
			trForbidProtounit(2, "Swordsman Hero");
			// ChatLog(1, "Mode:Singleplayer");
			// Cards will probably be unlocked in order, so I'm assuming the player has not played before if the first value is zero
			int sum = 0;
			for(i=0; < 16) {
				sum = sum + trGetScenarioUserData(i);
			}
			if(sum <= 0){
				xsEnableRule("CinPrologue00");
			} else {
				xsEnableRule("Collection");
			}
			/*
			Load player's collection
			*/
			loadCollection();
			/*
			Load player's deck
			*/
			loadDeck(0);
			
			trSetCurrentScenarioUserData(COMMANDS, 0);
		}
		xsDisableSelf();
	}
}

rule data_load_01_ready
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Swordsman") + trPlayerUnitCountSpecific(2, "Swordsman") == 128) {
		xsEnableRule("data_load_01_load_classes");
		xsEnableRule("data_load_02_detect_classes");
		xsDisableSelf();
	}
}

rule data_load_01_load_classes
highFrequency
inactive
{
	trLetterBox(false);
	trBlockAllSounds(true);
	int c = 6 * trQuestVarGet("class1") + trQuestVarGet("class2");
	if (trCurrentPlayer() == 2) {
		c = c + 64;
	}
	trChatSend(0, "Class data: " + c);
	trUnitSelectClear();
	trUnitSelectByID(c);
	for(i=64; >0) {
		if (trUnitIsSelected() == false) {
			uiFindType("Swordsman");
		} else {
			trChatSend(0, "Found!");
			break;
		}
	}
	uiTransformSelectedUnit("Swordsman Hero");
	xsDisableSelf();
	trForceNonCinematicModels(true);
	trLetterBox(true);
	showLoadProgress(1*trQuestVarGet("progress"));
}

rule data_load_02_detect_classes
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Swordsman Hero") + trPlayerUnitCountSpecific(2, "Swordsman Hero") == 2) {
		for(x=0; < 64) {
			if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Swordsman Hero")) {
				trQuestVarSet("p1classes", x);
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(kbGetProtoUnitID("Swordsman"));
				break;
			}
		}
		for(x=64; < 128) {
			if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Swordsman Hero")) {
				trQuestVarSet("p2classes", x - 64);
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(kbGetProtoUnitID("Swordsman"));
				break;
			}
		}
		int c = 0;
		for(p=2; >0) {
			c = trQuestVarGet("p"+p+"classes");
			trQuestVarSet("p"+p+"class2", iModulo(6, c));
			c = c / 6;
			trQuestVarSet("p"+p+"class1", c);
			trPlayerGrantResources(p, "food", -1000);
			trPlayerGrantResources(p, "wood", -1000);
			trPlayerGrantResources(p, "gold", -1000);
			trPlayerGrantResources(p, "favor", -1000);
		}
		showLoadProgress(1);
		xsEnableRule("data_load_03_load_commanders");
		xsEnableRule("data_load_04_detect_commanders");
		xsDisableSelf();
	}
}

rule data_load_03_load_commanders
highFrequency
inactive
{
	int p = trCurrentPlayer();
	if (trPlayerUnitCountSpecific(p, "Swordsman Hero") == 0) {
		trLetterBox(false);
		trBlockAllSounds(true);
		int c = trQuestVarGet("commander");
		if (p == 2) {
			c = c + 64;
		}
		trChatSend(0, "Commander data: " + c);
		trUnitSelectClear();
		trUnitSelectByID(c);
		for(i=64; >0) {
			if (trUnitIsSelected() == false) {
				uiFindType("Swordsman");
			} else {
				trChatSend(0, "Found!");
				break;
			}
		}
		if (trUnitIsOwnedBy(trCurrentPlayer())) {
			uiTransformSelectedUnit("Swordsman Hero");
		}
		xsDisableSelf();
		trForceNonCinematicModels(true);
		trLetterBox(true);
		showLoadProgress(1*trQuestVarGet("progress"));
	}
}

rule data_load_04_detect_commanders
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Swordsman Hero") + trPlayerUnitCountSpecific(2, "Swordsman Hero") == 2) {
		for(x=0; < 12) {
			if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Swordsman Hero")) {
				trQuestVarSet("p1commanderType", x);
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(kbGetProtoUnitID("Swordsman"));
				break;
			}
		}
		for(x=64; < 76) {
			if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Swordsman Hero")) {
				trQuestVarSet("p2commanderType", x - 64);
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(kbGetProtoUnitID("Swordsman"));
				break;
			}
		}
		showLoadProgress(2);
		xsDisableRule("data_load_04_detect_commanders");
		for(p=2; >0) {
			trPlayerGrantResources(p, "food", -1000);
			trPlayerGrantResources(p, "wood", -1000);
			trPlayerGrantResources(p, "gold", -1000);
			trPlayerGrantResources(p, "favor", -1000);
		}
		
		/*
		Deck data
		*/
		deckc1d0 = trGetScenarioUserData(6, mainFilename);
		deckc1d1 = trGetScenarioUserData(7, mainFilename);
		deckc2d0 = trGetScenarioUserData(8, mainFilename);
		deckc2d1 = trGetScenarioUserData(9, mainFilename);
		
		trQuestVarSet("loadProgress", 0);
		trQuestVarSet("classProgress", 1);
		trQuestVarSet("loadNext", 1);
		trQuestVarSet("progress", 2);
		
		xsEnableRule("data_load_05_load_cards");
		xsEnableRule("data_load_06_detect_cards");
	}
}

rule data_load_05_load_cards
highFrequency
inactive
{
	int p = trCurrentPlayer();
	if ((trQuestVarGet("loadNext") == 1) &&
		(trPlayerUnitCountSpecific(p, "Swordsman Hero") == 0)) {
		trLetterBox(false);
		trBlockAllSounds(true);
		trQuestVarSet("loadNext", 0);
		int c = trQuestVarGet("classProgress");
		int d = 0;
		if (trQuestVarGet("loadProgress") >= 5) {
			d = 1;
		}
		int data = 0;
		switch(10*c + d)
		{
			case 10:
			{
				data = deckc1d0;
				deckc1d0 = deckc1d0 / 64;
			}
			case 11:
			{
				data = deckc1d1;
				deckc1d1 = deckc1d1 / 64;
			}
			case 20:
			{
				data = deckc2d0;
				deckc2d0 = deckc2d0 / 64;
			}
			case 21:
			{
				data = deckc2d1;
				deckc2d1 = deckc2d1 / 64;
			}
		}
		
		int x = iModulo(64, data);
		if (p == 2) {
			x = x + 64;
		}
		trUnitSelectClear();
		trUnitSelectByID(x);
		for(i=64; >0) {
			if (trUnitIsSelected() == false) {
				uiFindType("Swordsman");
			} else {
				trChatSend(0, "Found!");
				break;
			}
		}
		uiTransformSelectedUnit("Swordsman Hero");
		trForceNonCinematicModels(true);
		trLetterBox(true);
		showLoadProgress(1*trQuestVarGet("progress"));
	}
}

void loadCardsToDeck(int p = 1, int v = 0) {
	int class = trQuestVarGet("p"+p+"class"+1*trQuestVarGet("classProgress"));
	int offset = 30 * class + 3 * trQuestVarGet("loadProgress");
	for(y = 0; <3) {
		int count = iModulo(4, v);
		for(x=count; >0) {
			addCardToDeckByIndex(p,offset+y);
		}
		v = v / 4;
	}
}

rule data_load_06_detect_cards
highFrequency
inactive
{
	int r = trPlayerUnitCountSpecific(1, "Swordsman Hero") + trPlayerUnitCountSpecific(2, "Swordsman Hero");
	if (r == 2) {
		trQuestVarSet("derp", trTime());
		for(p=2; >0) {
			trPlayerGrantResources(p, "food", -1000);
			trPlayerGrantResources(p, "wood", -1000);
			trPlayerGrantResources(p, "gold", -1000);
			trPlayerGrantResources(p, "favor", -1000);
		}
		trQuestVarSet("progress", 1 + trQuestVarGet("progress"));
		showLoadProgress(1*trQuestVarGet("progress"));
		for(x=0; < 64) {
			if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Swordsman Hero")) {
				trChatSend(0, "value1: " + x);
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(kbGetProtoUnitID("Swordsman"));
				loadCardsToDeck(1, x);
				break;
			}
		}
		for(x=64; < 128) {
			if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Swordsman Hero")) {
				trChatSend(0, "value2: " + x);
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(kbGetProtoUnitID("Swordsman"));
				loadCardsToDeck(2, x - 64);
				break;
			}
		}
		trQuestVarSet("loadProgress", 1 + trQuestVarGet("loadProgress"));
		if (trQuestVarGet("loadProgress") == 10) {
			trQuestVarSet("loadProgress", 0);
			trQuestVarSet("classProgress", 1 + trQuestVarGet("classProgress"));
			if (trQuestVarGet("classProgress") == 3) {
				xsDisableRule("data_load_05_load_cards");
				xsDisableRule("data_load_06_detect_cards");
				xsEnableRule("data_load_07_done");
			}
		}
		trQuestVarSet("loadNext", 1);
	}
}

rule data_load_07_done
highFrequency
inactive
{
	unitTransform("Swordsman", "Cinematic Block");
	trForbidProtounit(1, "Swordsman Hero");
	trForbidProtounit(2, "Swordsman Hero");
	trLetterBox(false);
	trUIFadeToColor(0,0,0,1000,0,false);
	trUnblockAllSounds();
	trSoundPlayFN("favordump.wav","1",-1,"","");
	xsDisableRule("data_load_07_done");
	trQuestVarSet("dimension", 6);
	xsEnableRule("initializeBoard");
}
