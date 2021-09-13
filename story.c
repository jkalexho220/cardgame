void AddToCustomBoard(int tile = 0, int terrain = 0, string proto = "", int count = 1, int heading = 45, int scale = 1){
	yAddToDatabase("customBoard", "thisDoesNotMatterRight");
	yAddUpdateVar("customBoard", "tile", tile);
	yAddUpdateVar("customBoard", "terrain", terrain);
	yAddUpdateVar("customBoard", "proto", kbGetProtoUnitID(proto));						
	yAddUpdateVar("customBoard", "count", count);
	yAddUpdateVar("customBoard", "heading", heading);
	yAddUpdateVar("customBoard", "scale", scale);
}

void SetupMission(int class = 0, int mission = 0){
	yClearDatabase("p2deck");
	trQuestVarSet("dontPlaceRandomStuff", 0);
	/*
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
	*/
	InitBot(BOT_PERSONALITY_DEFAULT);
	switch(class)
	{
		case -1:
		{
			// Tutorial
			/* Arena */
			trPaintTerrain(0, 0, 60, 60, 0, 1, false);
			trQuestVarSet("dimension", 6);
			/* Opponent */
			trQuestVarSet("p2commanderType", 900);
			for(x=0;<40){
				addCardToDeck(2, "Swordsman");
			}	
		}
		case CLASS_ADVENTURER:
		{
			switch(mission)
			{
				case 1:
				{	
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 6);	
					trQuestVarSet("dontPlaceRandomStuff", 1);
					trQuestVarSet("customTerrainEmpty", T_GRASS_50);
					trQuestVarSet("customTerrainEmptyNot", T_FOREST_PINE);
					yClearDatabase("customBoard");
					//First Berry Bush
					AddToCustomBoard(171, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(164, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(169, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(151, TILE_OCCUPIED, "Berry Bush", 1, 47, 2);
					AddToCustomBoard(146, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(149, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(137, TILE_IMPASSABLE, "Berry Bush", 3);
					//Second Berry Bush
					AddToCustomBoard(152, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(170, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(168, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(150, TILE_OCCUPIED, "Berry Bush", 1, 69, 2);
					AddToCustomBoard(138, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(136, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(148, TILE_IMPASSABLE, "Berry Bush", 3);
					//Third Berry Bush
					AddToCustomBoard(161, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(183, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(144, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(160, TILE_OCCUPIED, "Berry Bush", 1, 69, 2);
					AddToCustomBoard(182, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(143, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(159, TILE_IMPASSABLE, "Berry Bush", 3);
					//Fourth Berry Bush
					AddToCustomBoard(141, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(157, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(140, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(156, TILE_OCCUPIED, "Berry Bush", 1, 47, 2);
					AddToCustomBoard(178, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(155, TILE_IMPASSABLE, "Berry Bush", 3);
					AddToCustomBoard(177, TILE_IMPASSABLE, "Berry Bush", 3);			
					/* Opponent */
					trQuestVarSet("p2commanderType", 901);
					for(x=0;<40){
						addCardToDeck(2, "", SPELL_INTIMIDATE);
					}				
				}
				case 2:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 8);	
					/* Opponent */
					trQuestVarSet("p2commanderType", 902);
					for(x=0;<6){
						addCardToDeck(2, "Swordsman");
						addCardToDeck(2, "Bondi");
						addCardToDeck(2, "Toxotes");
					}	
					for(x=0;<5){
						addCardToDeck(2, "Hero Greek Ajax");
						addCardToDeck(2, "Trident Soldier");
					}	
					for(x=0;<3){
						addCardToDeck(2, "Huskarl");
						addCardToDeck(2, "", SPELL_DEFENDER);
						addCardToDeck(2, "", SPELL_DUEL);
						addCardToDeck(2, "", SPELL_VICTORY);
					}						
				}
				case 3:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 8);	
					/* Opponent */
					trQuestVarSet("p2commanderType", 904);
					for(x=0;<10){
						addCardToDeck(2, "Wolf");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Bear");
						addCardToDeck(2, "Hetairoi");
						addCardToDeck(2, "Hero Greek Theseus");
						addCardToDeck(2, "", SPELL_SING);
						addCardToDeck(2, "", SPELL_GUARDIAN_OF_SEA);
					}	
					addCardToDeck(2, "Hero Greek Hippolyta");	
				}
				case 4:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 8);	
					/* Opponent */
					trQuestVarSet("p2commanderType", 903);
					for(x=0;<7){
						addCardToDeck(2, "Bondi");
						addCardToDeck(2, "Khopesh");
						addCardToDeck(2, "Avenger");
						addCardToDeck(2, "Raiding Cavalry");
						addCardToDeck(2, "", SPELL_BACKSTAB);
						addCardToDeck(2, "", SPELL_PISTOL_SHOT);
					}	
				}
				case 5:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 8);	
					/* Opponent */
					trQuestVarSet("p2commanderType", 904);
					for(x=0;<10){
						addCardToDeck(2, "Wolf");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Bear");
						addCardToDeck(2, "Hetairoi");
						addCardToDeck(2, "Hero Greek Theseus");
						addCardToDeck(2, "", SPELL_SING);
						addCardToDeck(2, "", SPELL_GUARDIAN_OF_SEA);
					}	
					addCardToDeck(2, "Hero Greek Hippolyta");
				}
				case 6:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 8);	
					/* Opponent */
					trQuestVarSet("p2commanderType", 905);
					for(x=0;<10){
						addCardToDeck(2, "Audrey Water");
					}
					for(x=0;<3){
						addCardToDeck(2, "Wolf");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Bear");
						addCardToDeck(2, "", SPELL_POISON_CLOUD);
						addCardToDeck(2, "", SPELL_NATURE_ANGRY);
					}	
				}
			}
		}
		case CLASS_ARCANE:
		{
			switch(mission)
			{
				case 1:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 5, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("dontPlaceRandomStuff", 1);
					trQuestVarSet("customTerrainEmpty", T_GRASS_75);
					trQuestVarSet("customTerrainEmptyNot", T_GREEK_ROAD);
					yClearDatabase("customBoard");
					AddToCustomBoard(136, TILE_IMPASSABLE, "Rock Limestone Big", 3);
					AddToCustomBoard(137, TILE_IMPASSABLE, "Rock Limestone Big", 3);
					AddToCustomBoard(140, TILE_IMPASSABLE, "Rock Limestone Big", 3);
					AddToCustomBoard(144, TILE_IMPASSABLE, "Rock Limestone Big", 3);
					AddToCustomBoard(142, TILE_IMPASSABLE, "Rock Limestone Big", 3);
					AddToCustomBoard(210, TILE_IMPASSABLE, "Rock Limestone Big", 3);
					AddToCustomBoard(206, TILE_IMPASSABLE, "Rock Limestone Big", 3);
					//Left Column Row
					AddToCustomBoard(188, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(186, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(184, TILE_OCCUPIED, "Columns", 1, 45, 2);	
					//Right Column Row
					AddToCustomBoard(176, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(174, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(172, TILE_OCCUPIED, "Columns", 1, 45, 2);											
					/* Opponent */
					trQuestVarSet("p2commanderType", 906);
					for(x=0;<40){
						addCardToDeck(2, "", SPELL_GROUND_STOMP);
					}		
				}
				case 2:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 7);				
					/* Opponent */
					trQuestVarSet("p2commanderType", 907);
					for(x=0;<5){
						addCardToDeck(2, "Slinger");
						addCardToDeck(2, "Monument");	
						addCardToDeck(2, "Magic Teacher");							
						addCardToDeck(2, "", SPELL_SPARK);
						addCardToDeck(2, "", SPELL_EXPLOSION);
						addCardToDeck(2, "", SPELL_PYROBALL);						
					}
					for(x=0;<2){
						addCardToDeck(2, "", SPELL_METEOR);
						addCardToDeck(2, "", SPELL_ELECTROSURGE);
						addCardToDeck(2, "", SPELL_APOCALYPSE);
					}					
				}
				case 3:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 8);				
					/* Opponent */
					trQuestVarSet("p2commanderType", COMMANDER_NOTTUD);
					for(x=0;<5){
						addCardToDeck(2, "Centaur");	
						addCardToDeck(2, "", SPELL_FINAL_EXAM);
						addCardToDeck(2, "", SPELL_MIRROR_REFLECTION);
					}
					for(x=0;<3){
						addCardToDeck(2, "Hippocampus");	
						addCardToDeck(2, "", SPELL_FINAL_EXAM);
						addCardToDeck(2, "", SPELL_FINAL_EXAM);
					}
					
					addCardToDeck(2, "Guardian");
					addCardToDeck(2, "Hero Greek Chiron");	
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
			}
		}
	}
	shuffleDeck(2);
}

void CleanBoard(){
	xsDisableRule("gameplay_select_show_keywords");
	unitTransform("Healing SFX", "Cinematic Block");
	unitTransform("Sky Passage", "Cinematic Block");
	trCounterAbort("counter");
	trCounterAbort("mana");
	trClearCounterDisplay();
	trSoundPlayDialog("default", "1", -1, false, " : ", "");
	uiClearSelection();
	trQuestVarSet("maxMana", 0);
	trQuestVarSet("p1mana", 0);	
	trQuestVarSet("p2mana", 0);
	for(i=trQuestVarGet("idsEyecandyStart");<trQuestVarGet("idsEyecandyEnd")){
		trUnitSelectClear();trUnitSelect(""+i);
		trUnitDestroy();
	}
	yDatabasePointerDefault("allUnits");
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		tileGuard(1*mGetVarByQV("allUnits", "tile"), false);
		zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("allUnits", "tile"), 0);
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
			xsEnableRule("StoryTutorial0");
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
			setClassProgress(CLASS_NAGA, 0);
			setClassProgress(CLASS_CLOCKWORK, 0);
			setClassProgress(CLASS_EVIL, 0);
			setClassProgress(CLASS_SPACE, 0);
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
		
		for(i=0;<5){
			//addCardToDeck(1, "", SPELL_INTIMIDATE);
			//addCardToDeck(1, "", SPELL_PISTOL_SHOT);
			//addCardToDeck(1, "", SPELL_PYROBALL);
			//addCardToDeck(1, "", SPELL_POISON_CLOUD);
			//addCardToDeck(1, "", SPELL_NATURE_ANGRY);
			//addCardToDeck(1, "Bear");
			//addCardToDeck(1, "Bondi");
			//addCardToDeck(1, "Audrey");
			//addCardToDeck(1, "Audrey Water");
			//addCardToDeck(1, "", SPELL_MIRROR_REFLECTION);
			//addCardToDeck(1, "Monument");
			//addCardToDeck(1, "", SPELL_INTIMIDATE);
		}

		SetupMission(trQuestVarGet("missionClass"), trQuestVarGet("missionSelection"));
		xsEnableRule("initializeBoard");
		xsEnableRule("MissionEnd");
		xsDisableRule("MissionBegin");		
   }
}

bool PlayerDefeated(int p = 1){
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("p" + p + "commander"), true);
	return (trUnitDead());
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
		xsDisableRule("Bot1");
		xsDisableRule("Bot2");
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
				for(i=0;<6){
					trQuestVarSetFromRand("temp", 0, 29, true);
					int reward = trQuestVarGet("temp") * trQuestVarGet("missionClass");	
					if((reward == 14 + 30 * trQuestVarGet("missionClass")) || (reward == 29 + 30 * trQuestVarGet("missionClass"))){
						ChatLog(0, "INCREASING LEGENDARY RARITY");
						trQuestVarSetFromRand("temp", 0, 29, true);
						reward = trQuestVarGet("temp") * trQuestVarGet("missionClass");	
					}
					if((getCardCountDeck(reward) + getCardCountCollection(reward)) < 3){
						setCardCountCollection(reward, getCardCountCollection(reward) + 1);
						trQuestVarSet("packReward" + i, reward);
					} else {
						trQuestVarSet("packReward" + i, -1);
					}
				}
				setClassProgress(trQuestVarGet("missionClass"), trQuestVarGet("missionSelection") + 2);
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

rule StoryTutorial0
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 1){
		trShowImageDialog("Zenophobia\SFA\Nick", "Wtf are you doing here?");
		xsDisableRule("StoryTutorial0");
		xsEnableRule("StoryTutorial1");
   }
}

rule StoryTutorial1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		trShowImageDialog("Zenophobia\SFA\Nick", "Zeno was supposed to make some pretty images for this tutorial but he's busy making random cards...");
		xsDisableRule("StoryTutorial1");
		xsEnableRule("StoryTutorial2");
   }
}

rule StoryTutorial2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 0){
		trShowImageDialog("Zenophobia\SFA\Nick", "Have a few swings at the Training Dummy and we'll call it a day.");
		xsDisableRule("StoryTutorial2");
   }
}

