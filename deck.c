/*
Fischer-Yates shuffle
*/
void shuffleDeck(int p = 0) {
	/*
	Copy the deck into an array
	*/
	int proto = 0;
	int spell = 0;
	int count = yGetDatabaseCount("p"+p+"deck");
	int db = aiPlanCreate("shuffle", 8);
	aiPlanAddUserVariableInt(db, 0, "proto", count);
	aiPlanAddUserVariableInt(db, 1, "spell", count);
	for(i=0; < count) {
		proto = yDatabaseNext("p"+p+"deck");
		spell = yGetVar("p"+p+"deck", "spell");
		aiPlanSetUserVariableInt(db, 0, i, proto);
		aiPlanSetUserVariableInt(db, 1, i, spell);
	}
	yClearDatabase("p"+p+"deck");
	/*
	Shuffle the array into the deck
	*/
	for(i=count - 1; >= 0) {
		// choose a random card
		trQuestVarSetFromRand("temp", 0, i, true);
		trQuestVarSet("tempProto", aiPlanGetUserVariableInt(db, 0, 1*trQuestVarGet("temp")));
		trQuestVarSet("tempSpell", aiPlanGetUserVariableInt(db, 1, 1*trQuestVarGet("temp")));
		yAddToDatabase("p"+p+"deck", "tempProto");
		yAddUpdateVar("p"+p+"deck", "spell", trQuestVarGet("tempSpell"));
		// swap with the last card
		proto = aiPlanGetUserVariableInt(db, 0, i);
		spell = aiPlanGetUserVariableInt(db, 1, i);
		aiPlanSetUserVariableInt(db, 0, 1*trQuestVarGet("temp"), proto);
		aiPlanSetUserVariableInt(db, 1, 1*trQuestVarGet("temp"), spell);
	}
	aiPlanDestroy(db);
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
	int cost = 0;
	trQuestVarSet("p"+p+"unitDiscount", trCountUnitsInArea("128",p,"Throwing Axeman",45));
	trQuestVarSet("p"+p+"spellDiscount", trCountUnitsInArea("128",p,"Priest",45));
	for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
		yDatabaseNext("p"+p+"hand");
		cost = mGetVarByQV("p"+p+"hand", "cost");
		if (mGetVarByQV("p"+p+"hand", "spell") > 0) {
			cost = cost - trQuestVarGet("p"+p+"spellDiscount");
		} else {
			cost = cost - trQuestVarGet("p"+p+"unitDiscount");
		}
		if (HasKeyword(OVERFLOW, 1*mGetVarByQV("p"+p+"hand", "keywords"))) {
			cost = cost - trQuestVarGet("p"+p+"manaflow");
		}
		if (cost <= trQuestVarGet("p"+p+"mana")) {
			trUnitSelectClear();
			trUnitSelectByID(1*yGetVar("p"+p+"hand", "pos"));
			trMutateSelected(kbGetProtoUnitID("Garrison Flag Sky Passage"));
		}
	}
}

void addCardToDeck(int p = 0, string proto = "", int spell = 0) {
	if (spell == 0) {
		trQuestVarSet("proto", kbGetProtoUnitID(proto));
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", 0);
	} else {
		trQuestVarSet("proto", kbGetProtoUnitID("Statue of Lightning"));
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", spell);
	}
}

void addCardToDeckByIndex(int p = 0, int card = 0) {
	int spell = CardToSpell(card);
	if (spell == 0) {
		trQuestVarSet("proto", CardToProto(card));
		if (trQuestVarGet("proto") == 0) {
			trSoundPlayFN("cantdothat.wav","1",-1,"","");
			ChatLog(1, "Card invalid! " + card);
		}
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", 0);
	} else {
		trQuestVarSet("proto", kbGetProtoUnitID("Statue of Lightning"));
		yAddToDatabase("p"+p+"deck", "proto");
		yAddUpdateVar("p"+p+"deck", "spell", spell);
	}
}

/*
This function should only be called if there is room in the hand!
*/
int addCardToHand(int p = 0, int proto = 0, int spell = 0, bool fleeting = false) {
	trQuestVarSet("next", CardInstantiate(p, proto, spell));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("next"), true);
	
	if (spell > SPELL_NONE) {
		proto = kbGetProtoUnitID("Statue of Lightning");
	}
	
	yAddToDatabase("p"+p+"hand", "next");
	
	trUnitHighlight(3, true);
	
	if (fleeting) {
		mSetVarByQV("next", "keywords", SetBit(1*trQuestVarGet("card_" + proto + "_Keywords"), FLEETING));
	}
	
	if ((trCountUnitsInArea("128",p,"Heka Gigantes",45) > 0) && (spell == SPELL_NONE)) {
		mSetVarByQV("next", "keywords", SetBit(1*trQuestVarGet("card_" + proto + "_Keywords"), OVERFLOW));
	}
	
	// Find an empty position in the hand to place the unit.
	for(x=zGetBankCount("p"+p+"handPos"); >0) {
		zBankNext("p"+p+"handPos");
		if (zGetVar("p"+p+"handPos", "occupied") == 0) {
			zSetVar("p"+p+"handPos", "occupied", 1);
			yAddUpdateVar("p"+p+"hand", "pos", trQuestVarGet("p"+p+"handPos"));
			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("p"+p+"handPos"));
			trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
			
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("next"), true);
			trMutateSelected(kbGetProtoUnitID("Dwarf"));
			trImmediateUnitGarrison(""+1*trQuestVarGet("p"+p+"handPos"));
			
			trUnitChangeProtoUnit(kbGetProtoUnitName(proto));
			
			
			trUnitSelectClear();
			trUnitSelectByID(1*trQuestVarGet("p"+p+"handPos"));
			trMutateSelected(kbGetProtoUnitID("Victory Marker"));
			
			break;
		}
	}
	if (spell > SPELL_NONE) {
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("next"), true);
		float scale = 0.2 + xsSqrt(trQuestVarGet("spell_"+spell+"_cost")) * 0.4;
		trSetSelectedScale(0.75, scale, 0.75);
		trUnitSetAnimationPath(""+1*trQuestVarGet("spell_"+spell+"_animation") + ",0,0,0,0");
	}

	return(1*trQuestVarGet("next"));
}

void addCardToHandByIndex(int p = 0, int card = 0, bool fleeting = false) {
	int spell = CardToSpell(card);
	int proto = CardToProto(card)	;
	addCardToHand(p, proto, spell, fleeting);
}


void drawCard(int p = 0, bool fleeting = false) {
	if (yGetDatabaseCount("p"+p+"deck") <= 0) {
		trQuestVarSet("p"+p+"fatigue", 1 + trQuestVarGet("p"+p+"fatigue"));
		damageUnit(1*trQuestVarGet("p"+p+"commander"), trQuestVarGet("p"+p+"fatigue"));
		ChatLog(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has no more cards! " + 1*trQuestVarGet("p"+p+"fatigue") + " damage");
		trQuestVarSetFromRand("sound", 1, 5, true);
		trSoundPlayFN("lightningstrike"+1*trQuestVarGet("sound")+".wav","1",-1,"","");
		if (mGetVarByQV("p"+p+"commander", "health") <= 0) {
			trQuestVarSet("p"+p+"drawCards", 0);
			trQuestVarSet("p"+p+"defeated", 1);
			xsEnableRule("match_end");
		}
	} else {
		int proto = yDatabaseNext("p"+p+"deck");
		if (yGetDatabaseCount("p"+p+"hand") < trQuestVarGet("p"+p+"maxHandSize")) {
			if (trCurrentPlayer() == p) {
				trSoundPlayFN("ui\scroll.wav","1",-1,"","");
			}
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				ChatLog(p, "Drew " + trStringQuestVarGet("card_" + proto + "_Name"));
			} else {
				ChatLog(p, "Drew " + trStringQuestVarGet("spell_" + 1*yGetVar("p"+p+"deck", "spell") + "_Name"));
			}
			addCardToHand(p, proto, 1*yGetVar("p"+p+"deck", "spell"), fleeting);
			// mad acolyte heals
			int acolytes = trCountUnitsInArea("128",(3-p),"Theocrat",45);
			if (acolytes > 0) {
				healUnit(1*trQuestVarGet("p"+(3-p)+"commander"), acolytes);
				trSoundPlayFN("recreation.wav","1",-1,"","");
				deployAtTile(0, "Regeneration SFX", mGetVarByQV("p"+(3-p)+"commander", "tile"));
			}
		} else {
			if (trCurrentPlayer() == p) {
				trSoundPlayFN("cantdothat.wav","1",-1,"","");
			}
			if (yGetVar("p"+p+"deck", "spell") == 0) {
				ChatLog(p, "Hand full! Burned " + trStringQuestVarGet("card_" + proto + "_Name"));
			} else {
				ChatLog(p, "Hand full! Burned " + trStringQuestVarGet("spell_" + 1*yGetVar("p"+p+"deck", "spell") + "_Name"));
			}
			
		}
		yRemoveFromDatabase("p"+p+"deck");
		
		updateRoxasHealth(p);
		updateHandPlayable(p);
		updateMana();
	}
}

int generateCard(int p = 0, int proto = 0, int spell = 0, bool fleeting = false) {
	int card = -1;
	if (yGetDatabaseCount("p"+p+"hand") < trQuestVarGet("p"+p+"maxHandSize")) {
		if (trCurrentPlayer() == p) {
			trSoundPlayFN("ui\scroll.wav","1",-1,"","");
		}
		if (spell == 0) {
			ChatLog(p, "Created " + trStringQuestVarGet("card_" + proto + "_Name"));
		} else {
			ChatLog(p, "Created " + trStringQuestVarGet("spell_" + spell + "_Name"));
		}
		card = addCardToHand(p, proto, spell, fleeting);
		updateHandPlayable(p);
		updateMana();
	} else {
		if (trCurrentPlayer() == p) {
			trSoundPlayFN("cantdothat.wav","1",-1,"","");
		}
		if (spell == 0) {
			ChatLog(p, "Hand full! Burned created " + trStringQuestVarGet("card_" + proto + "_Name"));
		} else {
			ChatLog(p, "Hand full! Burned created " + trStringQuestVarGet("spell_" + spell + "_Name"));
		}
	}
	return(card);
}

rule initializeHand
highFrequency
active
{
	zBankInit("p1handPos", 849, 10);
	zBankInit("p2handPos", 859, 10);
	
	xsDisableRule("initializeHand");
}


rule card_draw
highFrequency
active
{
	// We want to give the trCountUnitsInArea some time to update
	if (trTimeMS() > trQuestVarGet("card_draw_next")) {
		trQuestVarSet("card_draw_next", trTimeMS() + 500);
		for(p=2; >0) {
			if (trQuestVarGet("p"+p+"drawCards") > 0) {
				trQuestVarSet("p"+p+"drawCards", trQuestVarGet("p"+p+"drawCards") - 1);
				drawCard(p);
				if (trQuestVarGet("p"+p+"drawCards") == 0) {
					updateHandPlayable(1*trQuestVarGet("activePlayer"));
				}
			}
		}
	}
}
