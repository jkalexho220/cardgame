void SetupMission(int class = 0, int mission = 0){
	// Tutorial
	trPaintTerrain(0, 0, 60, 60, 0, 1, false);
	trQuestVarSet("dimension", 6);
	// Opponent Starter Deck
	yClearDatabase("p2deck");
	for(i=0;<6){
		for(x=0;<3){
			addCardToDeckByIndex(2, i);
			addCardToDeckByIndex(2, i + 30);
		}
	}
	for(x=0;<2){
		addCardToDeckByIndex(2, 6);
		addCardToDeckByIndex(2, 36);
	}
	InitBot(BOT_PERSONALITY_DEFAULT);
	switch(class)
	{
		case CLASS_ADVENTURER:
		{
			switch(mission)
			{
				case 1:
				{				
					trQuestVarSet("dimension", 8);	
				}
				case 2:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 3:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 4:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 5:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 6:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 7:
				{
					trQuestVarSet("dimension", 8);	
				}
			}
		}
		case CLASS_ARCANE:
		{
			switch(mission)
			{
				case 1:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 2:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 3:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 4:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 5:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 6:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 7:
				{
					trQuestVarSet("dimension", 8);	
				}
			}
		}
		case CLASS_NAGA:
		{
			switch(mission)
			{
				case 1:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 2:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 3:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 4:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 5:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 6:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 7:
				{
					trQuestVarSet("dimension", 8);	
				}
			}
		}
		case CLASS_CLOCKWORK:
		{
			switch(mission)
			{
				case 1:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 2:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 3:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 4:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 5:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 6:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 7:
				{
					trQuestVarSet("dimension", 8);	
				}
			}
		}
		case CLASS_EVIL:
		{
			switch(mission)
			{
				case 1:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 2:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 3:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 4:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 5:
				{
					trQuestVarSet("dimension", 8);		
				}
				case 6:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 7:
				{
					trQuestVarSet("dimension", 8);	
				}
			}
		}
		case CLASS_SPACE:
		{
			switch(mission)
			{
				case 1:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 2:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 3:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 4:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 5:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 6:
				{
					trQuestVarSet("dimension", 8);	
				}
				case 7:
				{
					trQuestVarSet("dimension", 8);	
				}
			}
		}
	}
	shuffleDeck(2);
}

void CleanBoard(){
	xsDisableRule("gameplay_select_show_keywords");
	trCounterAbort("counter");
	trCounterAbort("mana");
	trClearCounterDisplay();
	trSoundPlayDialog("default", "1", -1, false, " : ", "");
	uiClearSelection();
	trQuestVarSet("maxMana", 0);
	trQuestVarSet("p1mana", 0);	
	trQuestVarSet("p2mana", 0);
	for(x=zGetBankCount("tiles"); >0) {
		zBankNext("tiles");
		zSetVar("tiles","occupant", TILE_EMPTY);
	}
	for(i=trQuestVarGet("idsEyecandyStart");<trQuestVarGet("idsEyecandyEnd")){
		trUnitSelectClear();trUnitSelect(""+i);
		trUnitDestroy();
	}
	yDatabasePointerDefault("allUnits");
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
	}
	yClearDatabase("allUnits");
	yDatabasePointerDefault("p1hand");
	for(x=yGetDatabaseCount("p1hand"); >0) {
		yDatabaseNext("p1hand", true);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
	}
	yClearDatabase("p1hand");
	updateHandPlayable(1);
	yDatabasePointerDefault("p2hand");
	for(x=yGetDatabaseCount("p2hand"); >0) {
		yDatabaseNext("p2hand", true);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
	}
	yClearDatabase("p2hand");
	updateHandPlayable(2);
}

rule MissionBegin
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 1){
		trSoundPlayFN("default","1",-1,"Loading:","icons\god power reverse time icons 64");
		trPlayerKillAllGodPowers(1);
		trTechGodPower(1, "animal magnetism", 1);
		trTechGodPower(1, "create gold", 1);
		trUIFadeToColor(0,0,0,1000,1000,false);
		trSetFogAndBlackmap(true, true);
		trOverlayTextColour(255, 255, 0);
		if(collectionMission == ""){
			trOverlayText("Tutorial", 4.7, 500, 200, 1000);
			// Starter Deck
			for(i = 0;<180){
				setCardCountDeck(i, 0);
				setCardCountCollection(i, 0);
			}
			for(i = 0;<6){
				setCardCountDeck(i, 3);
				setCardCountDeck(i + 30, 3);
			}
			setCardCountDeck(6, 2);
			setCardCountCollection(6, 1);
			setCardCountDeck(36, 2);
			setCardCountCollection(36, 1);
			setClassProgress(CLASS_ADVENTURER, 1);
			setClassProgress(CLASS_ARCANE, 1);
			setClassProgress(2, 0);
			setClassProgress(3, 0);
			setClassProgress(4, 0);
			setClassProgress(5, 0);
			setDeckCommander(0);
		} else {
			trOverlayText(collectionMission, 4.7, 500, 200, 1000);
		}
		// Add Cards to Deck
		yClearDatabase("p1deck");
		for(i=0;<180){
			for(x=0;<getCardCountDeck(i)){
				addCardToDeckByIndex(1, i);
			}
		}
		shuffleDeck(1);
		SetupMission(trQuestVarGet("missionClass"), trQuestVarGet("missionSelection"));
		xsEnableRule("initializeBoard");
		xsEnableRule("MissionEnd");
		xsDisableRule("MissionBegin");		
   }
}

bool PlayerDefeated(int p = 1){
	bool defeat = false;
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("p" + p + "commander"), true);
	if(trUnitDead()){
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("p" + p + "commanderSecondary"), true);
		if(trUnitDead()){
			defeat = true; 
		} else {
			trQuestVarSet("p" + p + "commander", trQuestVarGet("p" + p + "commanderSecondary"));
			trQuestVarSet("p" + p + "commanderSecondary", -1);
		}
	}
	return (defeat);
}

rule MissionEnd
highFrequency
inactive
{
	
	bool defeat = PlayerDefeated(1);
	bool victory = PlayerDefeated(2);
	if (defeat || victory){
		trPlayerKillAllGodPowers(1);
		trPlayerKillAllGodPowers(2);
		trUIFadeToColor(0,0,0,1000,1000,true);
		xsDisableRule("MissionEnd");		
		if(defeat && victory){
			trOverlayTextColour(255, 255, 0);
			trOverlayText("~ TIE ~", 4.7, 500, 200, 1000);
			trSoundPlayFN("xlose.wav","1",-1,"","");
		} else if(defeat){
			trOverlayTextColour(255, 0, 0);
			trOverlayText("~ DEFEAT ~", 4.7, 500, 200, 1000);
			trSoundPlayFN("xlose.wav","1",-1,"","");
		} else {
			trOverlayTextColour(0, 0, 255);
			trOverlayText("~ VICTORY ~", 4.7, 500, 200, 1000);
			trSoundPlayFN("xwin.wav","1",-1,"","");
			if(trQuestVarGet("missionSelection") < 0){
				// Starter Deck already set, just save
				dataSave();
			} else {
				// Reward Card Pack
				dataSave();
			}
		}
		// If you lost the Tutorial restart, otherwise go to collection
		if(defeat && collectionMission == ""){
			trQuestVarSet("restartMission", 1);
		} else {
			trQuestVarSet("restartMission", 0);
		}
		xsEnableRule("MissionEnd1");
   }
}

rule MissionEnd1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 3){
		unitTransform("Healing SFX", "Cinematic Block");
		CleanBoard();
		trFadeOutAllSounds(0.0);
		trUIFadeToColor(0,0,0,1000,1000,false);
		xsDisableRule("MissionEnd1");
		if(trQuestVarGet("restartMission") == 1){
			xsEnableRule("MissionBegin");
		} else {
			xsEnableRule("Collection");
		}
   }
}