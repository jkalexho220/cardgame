/*
slots 6-7: class 1 cards
slots 8-9: class 2 cards

slot 10: which commander + which two classes
*/

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
				copyDeckData();
				trGameLoadScenario(mainFilename);
			}
		}
		case COMMAND_DELETE_DECK:
		{
			copyDeckData(trGetScenarioUserData(12, collectionFilename) + 1); // copy deck data from the last deck
			trGameLoadScenario(mainFilename);
		}
	}
}