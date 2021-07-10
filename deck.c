
/*
Fischer-Yates shuffle
*/
void shuffleDeck(int p = 0) {
	int i = 0;
	for(x=yGetDatabaseCount("p"+p+"deck")-1; >=0) {
		trQuestVarSetFromRand("pos", 0, x, true);
		i = trQuestVarGet("pos");
		trQuestVarSet("tempProto", yGetUnitAtIndex("p"+p+"deck", i));
		trQuestVarSet("tempSpell", yGetVarByIndex("p"+p+"deck", "spell", i));

		ySetUnitAtIndex("p"+p+"deck", i, yGetUnitAtIndex("p"+p+"deck", x));
		ySetVarByIndex("p"+p+"deck", "spell", i, yGetVarByIndex("p"+p+"deck", "spell", x));

		ySetUnitAtIndex("p"+p+"deck", x, 1*trQuestVarGet("tempProto"));
		ySetVarByIndex("p"+p+"deck", "spell", x, trQuestVarGet("tempSpell"));
	}
}
/* 
Updates the hand UI by highlighting cards that the user can
afford to play
*/
void updateHandPlayable(int p = 0) {
	for(x=zGetBankCount("p"+p+"handPos"); >0) {
		zBankNext("p"+p+"handPos", true);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
	}
	for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
		yDatabaseNext("p"+p+"hand");
		if (yGetVar("p"+p+"hand", "cost") <= trQuestVarGet("p"+p+"mana")) {
			trUnitSelectClear();
			trUnitSelectByID(1*yGetVar("p"+p+"hand", "pos"));
			trMutateSelected(kbGetProtoUnitID("Garrison Flag Sky Passage"));
		}
	}
}

void addCardToDeck(int p = 0, string proto = "", int spell = 0) {
	trQuestVarSet("proto", kbGetProtoUnitID(proto));
	yAddToDatabase("p"+p+"deck", "proto");
	yAddUpdateVar("p"+p+"deck", "spell", spell);
}


/* 
This function should only be called if there is room in the hand!
*/
void addCardToHand(int p = 0, int proto = 0, int spell = 0) {
	trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("1,10","Dwarf",1,trQuestVarGet("p"+p+"deckx"),0,trQuestVarGet("p"+p+"deckz"),0,true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("next"), true);
	trUnitConvert(p);
	trUnitChangeName("("+1*trQuestVarGet("card_" + proto + "_Cost")+") "+trStringQuestVarGet("card_" + proto + "_Name")+" <"+1*trQuestVarGet("card_" + proto + "_Speed")+">");
	trUnitHighlight(3, true);


	yAddToDatabase("p"+p+"hand", "next");
	yAddUpdateVar("p"+p+"hand", "proto", proto);
	yAddUpdateVar("p"+p+"hand", "cost", trQuestVarGet("card_" + proto + "_Cost"));
	yAddUpdateVar("p"+p+"hand", "attack", trQuestVarGet("card_" + proto + "_Attack"));
	yAddUpdateVar("p"+p+"hand", "health", trQuestVarGet("card_" + proto + "_Health"));
	yAddUpdateVar("p"+p+"hand", "speed", trQuestVarGet("card_" + proto + "_Speed"));
	yAddUpdateVar("p"+p+"hand", "range", trQuestVarGet("card_" + proto + "_Range"));
	yAddUpdateVar("p"+p+"hand", "keywords", trQuestVarGet("card_" + proto + "_Keywords"));
	yAddUpdateString("p"+p+"hand", "ability", trStringQuestVarGet("card_" + proto + "_Ability"));

	yAddUpdateVar("p"+p+"hand", "player", p);
	yAddUpdateVar("p"+p+"hand", "spell", spell);

	// Find an empty position in the hand to place the unit.
	for(x=zGetBankCount("p"+p+"handPos"); >0) {
		if (trCountUnitsInArea(""+zBankNext("p"+p+"handPos"),p,"Unit",2) == 0) {
			yAddUpdateVar("p"+p+"hand", "pos", trQuestVarGet("p"+p+"handPos"));
			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("p"+p+"handPos"));
			trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));

			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("next"), true);
			trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"handPos"));

			trUnitChangeProtoUnit(kbGetProtoUnitName(proto));


			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("p"+p+"handPos"));
			trMutateSelected(kbGetProtoUnitID("Victory Marker"));

			break;
		}
	}
}


void drawCard(int p = 0) {
	int proto = yDatabaseNext("p"+p+"deck");
	if (yGetDatabaseCount("p"+p+"hand") < 10) {
		if (trCurrentPlayer() == p) {
			trSoundPlayFN("ui\scroll.wav","1",-1,"","");
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				trChatSend(0, "Drew a " + trStringQuestVarGet("card_" + proto + "_Name"));
			}
		}
		addCardToHand(p, proto, yGetVar("p"+p+"deck", "spell"));
	} else {
		if (trCurrentPlayer() == p) {
			trSoundPlayFN("cantdothat.wav","1",-1,"","");
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				trChatSend(0, "Hand full! Burned a " + trStringQuestVarGet("card_" + proto + "_Name"));
			}
		}
	}
	yRemoveFromDatabase("p"+p+"deck");
	yRemoveUpdateVar("p"+p+"deck", "spell");

	updateHandPlayable(p);
}


rule initializeHand
highFrequency
active
{
	zBankInit("p1handPos", 849, 10);
	zBankInit("p2handPos", 859, 10);

	trVectorQuestVarSet("p1deck", xsVectorSet(1,0,1));
	trVectorQuestVarSet("p2deck", xsVectorSet(119,0,119));

	xsDisableRule("initializeHand");
}


rule card_draw
highFrequency
active
{
	// We want to give the trCountUnitsInArea some time to update
	for(p=2; >0) {
		if (trQuestVarGet("p"+p+"drawCards") > 0) {
			trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") - 1);
			drawCard(p);
		}
	}
}