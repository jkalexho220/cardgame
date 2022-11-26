rule collectionDataRun
active
highFrequency
{
	trUIFadeToColor(0,0,0,0,0,true);
	xsDisableSelf();

	bool done = false;
	int data = 0;
	int currentdata = 0;
	int card = 0;
	int command = trGetScenarioUserData(COMMANDS, mainFilename);
	switch(command)
	{
		case COMMAND_UPDATE_COLLECTION:
		{
			loadCollection();
			for(c=0; <6) {
				data = trGetScenarioUserData(c, mainFilename);
				if (data > 0) {
					for (x=0; < 7) {
						card = x + 30 * c;
						trQuestVarSet("card_"+card+"_count", 3);
					}
				}
			}
			// new cards
			for(slot = 12; < 16) {
				data = trGetScenarioUserData(slot, mainFilename);
				for(i=0; <3) {
					card = iModulo(180, data);
					trQuestVarSet("card_"+card+"_count", xsMin(3, trQuestVarGet("card_"+card+"_count") + 1));
					if ((iModulo(30, card) == 14) || (iModulo(30, card) == 29)) { // if legendary
						trQuestVarSet("card_"+card+"_count", 1);
					}
					data = data / 180;
				}
			}

			// save collection data
			for(c=0; <6) {
				data = 0;
				for(x=14; >= 0) {
					card = x + 30 * c;
					currentdata = trQuestVarGet("card_"+card+"_count");
					data = data * 4 + currentdata;
				}
				trSetCurrentScenarioUserData(c, data);
				data = 0;
				for(x=29; >= 15) {
					card = x + 30 * c;
					currentdata = trQuestVarGet("card_"+card+"_count");
					data = data * 4 + currentdata;
				}
				trSetCurrentScenarioUserData(c + 6, data);
			}
			

			trGameLoadScenario(mainFilename);
		}
		case COMMAND_SAVE_DECK:
		{
			int deckCount = trGetScenarioUserData(12);
			int deckSlotCount = trGetScenarioUserData(13);
			data = trGetScenarioUserData(COMMANDS + 1, mainFilename);
			if (data > deckCount) { // new deck
				deckCount = data;
				trSetCurrentScenarioUserData(12, deckCount);
				if (data > deckSlotCount) { // we need to write a new file
					done = true;
					deckSlotCount = data;
					trSetCurrentScenarioUserData(13, deckSlotCount);
					trSetCurrentScenarioUserData(14, 1);
					trGameLoadScenario(newDeckFilename);
				}
			}

			if (done == false) { // we don't need to write a new file
				trSetCurrentScenarioUserData(14, 0);
				trGameLoadScenario(slotFilename(data));
			}
		}
		case COMMAND_DELETE_DECK:
		{
			trSetCurrentScenarioUserData(12, trGetScenarioUserData(12) - 1); // reduce deck count by 1
			data = trGetScenarioUserData(COMMANDS + 1, mainFilename);
			trGameLoadScenario(slotFilename(data));
		}
	}
}