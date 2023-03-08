
/*
slots 0-5: cards 0-14 
slots 6-11: cards 15-29

slot 12: deck count
slot 13: deck slot count
slot 14: new file
*/
void loadCollection() {
	int card = 0;
	int data = 0;
	for(c=0; <6) {
		// Starter cards 0-6
		/*
		for (x=0; < 7) {
			card = x + 30 * c;
			trQuestVarSet("card_"+card+"_count", 3);
		}
		*/
		data = trGetScenarioUserData(c, collectionFilename);
		if (data == -1) {
			data = 0;
			trSetCurrentScenarioUserData(c, 0);
		}
		for(x=0; <15) {
			card = x + 30 * c;
			trQuestVarSet("card_"+card+"_count", iModulo(4, data));
			data = data / 4;
		}
		// Cards 15-29
		data = trGetScenarioUserData(c + 6, collectionFilename);
		if (data == -1) {
			data = 0;
			trSetCurrentScenarioUserData(c + 6, 0);
		}
		for(x=15; <30) {
			card = x + 30 * c;
			trQuestVarSet("card_"+card+"_count", iModulo(4, data));
			data = data / 4;
		}
	}
}

int getDeckCount() {
	return(trGetScenarioUserData(12, collectionFilename));
}

int getDeckSlotCount() {
	return(trGetScenarioUserData(13, collectionFilename));
}