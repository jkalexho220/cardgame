const int COMMAND_UPDATE_COLLECTION = 1;
const int COMMAND_SAVE_DECK = 2;
const int COMMAND_DELETE_DECK = 3;

const int COMMANDS = 11;

const string collectionFilename = "HG-Data\Collection-Data.scx";
const string newDeckFilename = "HG-Data\HG-New-Deck.scx";
const string mainFilename = "!HeavenGames.scx";

string slotFilename(int slot = 0) {
	string fn = "!HeavenGames.scx";
	if (slot > 0) {
		fn = "HG-Data\HG-Slot-" + slot + ".scx";
	}
	return(fn);
}

/*
slot 11 = command
slots 12-15 = command data


COMMAND_SAVE_DECK
12 = filenum

COMMAND_DELETE_DECK
12 = deck num


COMMAND_UPDATE_COLLECTION
each slot holds 3 cards to add to collection (180^3 = 5,832,000)
*/

rule blackScreen
active
highFrequency
runImmediately
{
	trUIFadeToColor(0,0,0,0,0,true);
	xsDisableSelf();
}