/*
slots 6-7: class 1 cards
slots 8-9: class 2 cards

slot 10: which commander + which two classes
*/

void saveDeckSlot(int slot = 0) {
	// copy current deck data
	for(i=6; <= 10) {
		trSetCurrentScenarioUserData(i, trGetScenarioUserData(i, mainFilename));
	}
	// copy first three bits of class metadata
	/*
	for(i=0; < 6) {
		trSetCurrentScenarioUserData(i, iModulo(8, trGetScenarioUserData(i, mainFilename)));
	}
	*/
}

rule deckSlotRun
highFrequency
{
	trUIFadeToColor(0,0,0,0,0,true);
	xsDisableSelf();

	int command = trGetScenarioUserData(COMMANDS, mainFilename);
	switch(command)
	{
		case COMMAND_SAVE_DECK:
		{
			if (trGetScenarioUserData(14, collectionFilename) == 1) { // if it's time to write a new file
				subModeEnter("Simulation", "Editor");
				saveScenario(slotFilename(trGetScenarioUserData(12, mainFilename)));
				subModeLeave("Simulation", "Editor");
				modeEnter("pregame");
				modeEnter("Simulation");
				subModeEnter("Simulation", "Singleplayer");
				trGameLoadScenario(collectionFilename);
			} else {
				saveDeckSlot();
				trGameLoadScenario(mainFilename);
			}
		}
	}
}