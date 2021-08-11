/*
Slots 0-5 = progress and metadata for each class and cards 7-14
1 bit = class in deck?
1 bit = class is first or second (0 = first class)
1 bit = selected commander
3 bits for progress on storyline
3 x 7 bits = collectible commons 7-13 in collection
1 bit = collectible legendary in collection



Slots 6-7 = cards from class 1 in current deck
Slots 8-9 = cards from class 2 in current deck

Slots 10-15 = collectible class cards in collection
*/


/*
This function assumes the following:
- the quest vars named "class1" and "class2" are properly set.
- the "commander" quest var is properly set.
- there are only two classes in the "deck" database
*/
void dataSave() {
	int card = 0;
	int c = trQuestVarGet("class1");
	int data = 0;
	int power = 1;
	for(x=0; <15) {
		card = x + 30 * c;
		data = data + power * getCardCountDeck(card);
		power = power * 4;
	}
	trQuestVarSet("data6", data);
	data = 0;
	power = 1;
	for(x=15; <30) {
		card = x + 30 * c;
		data = data + power * getCardCountDeck(card);
		power = power * 4;
	}
	trQuestVarSet("data7", data);

	c = trQuestVarGet("class2");
	data = 0;
	power = 1;
	for(x=0; <15) {
		card = x + 30 * c;
		data = data + power * getCardCountDeck(card);
		power = power * 4;
	}
	trQuestVarSet("data8", data);
	data = 0;
	power = 1;
	for(x=15; <30) {
		card = x + 30 * c;
		data = data + power * getCardCountDeck(card);
		power = power * 4;
	}
	trQuestVarSet("data9", data);

	/*
	Saving collection and class progress data
	*/
	for(c=0; <6) {
		data = 0;
		if (trQuestVarGet("class2") == c) {
			data = data + 1; // set the first bit
		} else if (trQuestVarGet("class1") == c) {
			data = data + 3; // set the first 2 bits
			data = data + 4 * (1 * trQuestVarGet("commander") - 2 * c); // set the commander bit
		}
		data = data + 8 * trQuestVarGet("class"+c+"progress"); // progress is bits 3-5

		power = 64; // skip first 6 bits to add collectible cards
		for(x=7; <15) {
			card = x + 30 * c;
			data = data + power * trQuestVarGet("card_"+card+"_count");
			power = power * 4;
		}
		trQuestVarSet("data"+c, data);

		data = 0;
		power = 1;
		for(x=15; < 30) {
			card = x + 30 * c;
			data = data + power * trQuestVarGet("card_"+card+"_count");
			power = power * 4;
		}
		trQuestVarSet("data"+(c+10), data);
	}

	for(x=0; <16) {
		trSetCurrentScenarioUserData(x, 1*trQuestVarGet("data"+x));
	}
}

void showLoadProgress(int p = 0) {
	trSoundPlayFN("default","1",-1,""+100 * p / 22,"");
}

rule data_load_00
highFrequency
inactive
{
	trQuestVarSet("virgin", 0);
	for(x=0; < 16) {
		trQuestVarSet("data"+x, trGetScenarioUserData(x, "!HeavenGames.scx"));
		trQuestVarSet("virgin", trQuestVarGet("virgin") + trQuestVarGet("data"+x));
	}

	int bit = 0;
	int data = 0;
	int card = 0;
	for(x=0; < 6) {
		data = 1*trQuestVarGet("data"+x);
		bit = zModulo(2, data);
		/*
		Check if class is in deck
		*/
		if (bit == 1) {
			data = data / 2;
			bit = zModulo(2, data);
			/*
			Check if class is first or second
			*/
			if (bit == 1) {
				trQuestVarSet("class2", x);
			} else {
				trQuestVarSet("class1", x);
				data = data / 2;
				bit = zModulo(2, data);
				/*
				Calculate commander
				*/
				trQuestVarSet("commander", 2*trQuestVarGet("class1") + bit);
			}
		}

		data = 1*trQuestVarGet("data"+x);
		data = data / 8;
		trQuestVarSet("class"+x+"progress", zModulo(8, data));
	}

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
		for(x=127; >=0) {
			trUnitSelectClear();
			trUnitSelectByID(x);
			trMutateSelected(m);
		}
		xsEnableRule("initializeBoard");
		trBlockAllSounds(true);
		xsEnableRule("data_load_01_ready");
	} else {
		ChatLog(1, "Mode:Singleplayer");
		// Cards will probably be unlocked in order, so I'm assuming the player has not played before if the first value is zero
		if(trGetScenarioUserData(0) == 0){
			xsEnableRule("CinPrologue00");
		} else {
			xsEnableRule("Collection");
		}
		/* 
		Load player's collection 
		*/
		for(c=0; <6) {
			// Starter cards 0-6
			for (x=0; < 7) {
				card = x + 30 * c;
				trQuestVarSet("card_"+card+"_count", 3);
			}
			// Cards 7-14
			data = 1*trQuestVarGet("data"+c);
			data = data / 64; // skip first 6 bits
			for(x=7; <15) {
				card = x + 30 * c;
				trQuestVarSet("card_"+card+"_count", zModulo(4, data));
				data = data / 4;
			}
			// Cards 15-29
			data = 1*trQuestVarGet("data"+(c+10));
			for(x=15; <30) {
				card = x + 30 * c;
				trQuestVarSet("card_"+card+"_count", zModulo(4, data));
				data = data / 4;
			}
		}
		/*
		Load player's deck
		*/
		c = 30 * trQuestVarGet("class1");
		data = 1*trQuestVarGet("data6");
		for(x=0;<15) {
			card = c + x;
			trQuestVarSet("card_"+card+"_countInDeck", zModulo(4, data));
			data = data / 4;
			if (data == 0) {
				break;
			}
		}
		data = 1*trQuestVarGet("data7");
		for(x=15;<30) {
			card = c + x;
			trQuestVarSet("card_"+card+"_countInDeck", zModulo(4, data));
			data = data / 4;
			if (data == 0) {
				break;
			}
		}

		c = 30 * trQuestVarGet("class2");
		data = 1*trQuestVarGet("data8");
		for(x=0;<15) {
			card = c + x;
			trQuestVarSet("card_"+card+"_countInDeck", zModulo(4, data));
			data = data / 4;
			if (data == 0) {
				break;
			}
		}
		data = 1*trQuestVarGet("data9");
		for(x=15;<30) {
			card = c + x;
			trQuestVarSet("card_"+card+"_countInDeck", zModulo(4, data));
			data = data / 4;
			if (data == 0) {
				break;
			}
		}
	}
	xsDisableSelf();
}

rule data_load_01_ready
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Swordsman") + trPlayerUnitCountSpecific(2, "Swordsman") > 64) {
		xsEnableRule("data_load_01_load_classes");
		xsEnableRule("data_load_02_detect_classes");
		xsDisableSelf();
	}
}

rule data_load_01_load_classes
highFrequency
inactive
{
	int c = 6 * trQuestVarGet("class1") + trQuestVarGet("class2");
	if (trCurrentPlayer() == 2) {
		c = c + 64;
	}
	trUnitSelectClear();
	trUnitSelectByID(c);
	while(trUnitIsSelected() == false) {
		uiFindType("Swordsman");
	}
	uiTransformSelectedUnit("Swordsman Hero");
	xsDisableSelf();
}

rule data_load_02_detect_classes
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Swordsman Hero") + trPlayerUnitCountSpecific(2, "Swordsman Hero") == 1) {
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
			trQuestVarSet("p"+p+"class2", zModulo(6, c));
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
		int c = trQuestVarGet("commander");
		if (p == 2) {
			c = c + 64;
		}
		trUnitSelectClear();
		trUnitSelectByID(c);
		while(trUnitIsSelected() == false) {
			uiFindType("Swordsman");
		}
		uiTransformSelectedUnit("Swordsman Hero");
		xsDisableSelf();
	}
}

rule data_load_04_detect_commanders
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Swordsman Hero") + trPlayerUnitCountSpecific(2, "Swordsman Hero") == 1) {
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
		trQuestVarSet("deckDataC1D0", trQuestVarGet("data6"));
		trQuestVarSet("deckDataC1D1", trQuestVarGet("data7"));
		trQuestVarSet("deckDataC2D0", trQuestVarGet("data8"));
		trQuestVarSet("deckDataC2D1", trQuestVarGet("data9"));
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
		trQuestVarSet("loadNext", 0);
		int c = trQuestVarGet("classProgress");
		int d = 0;
		if (trQuestVarGet("loadProgress") >= 5) {
			d = 1;
		}
		int data = trQuestVarGet("deckDataC"+c+"D"+d);
		int x = zModulo(64, data);
		if (p == 2) {
			x = x + 64;
		}
		trUnitSelectClear();
		trUnitSelectByID(x);
		while(trUnitIsSelected() == false) {
			uiFindType("Swordsman");
		}
		uiTransformSelectedUnit("Swordsman Hero");
		trQuestVarSet("deckDataC"+c+"D"+d, data / 64);
	}
}

void loadCardsToDeck(int p = 1, int v = 0) {
	int class = trQuestVarGet("p"+p+"class"+1*trQuestVarGet("classProgress"));
	int offset = 30 * class + 3 * trQuestVarGet("loadProgress");
	for(y = 0; <3) {
		int count = zModulo(4, v);
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
	if (r == 1) {
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
				trChatSend(0, "value: " + x);
				trUnitSelectClear();
				trUnitSelectByID(x);
				trMutateSelected(kbGetProtoUnitID("Swordsman"));
				loadCardsToDeck(1, x);
				break;
			}
		}
		for(x=64; < 128) {
			if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Swordsman Hero")) {
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
	trLetterBox(false);
	trUIFadeToColor(0,0,0,1000,0,false);
	trUnblockAllSounds();
	trSoundPlayFN("favordump.wav","1",-1,"","");
	xsDisableRule("data_load_07_done");
}