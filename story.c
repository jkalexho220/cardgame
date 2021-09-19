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
	yClearDatabase("customBoard");
	trQuestVarSet("dontPlaceRandomStuff", 0);
	trQuestVarSet("customTerrainEmpty", 0);
	trQuestVarSet("customTerrainEmptyNot", 0);
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
			trPaintTerrain(0, 0, 60, 60, 0, T_EGYPTIAN_ROAD, false);
			trQuestVarSet("dimension", 5);
			trQuestVarSet("dontPlaceRandomStuff", 1);
			trQuestVarSet("customTerrainEmpty", T_GRASS_25);
			trQuestVarSet("customTerrainEmptyNot", T_FOREST_PALM);
			AddToCustomBoard(150, TILE_IMPASSABLE, "Crate", 4);
			AddToCustomBoard(151, TILE_IMPASSABLE, "Crate", 4);
			AddToCustomBoard(136, TILE_IMPASSABLE, "Crate", 4);
			AddToCustomBoard(137, TILE_IMPASSABLE, "Crate", 4);
			AddToCustomBoard(129, TILE_IMPASSABLE, "Crate", 4);
			
			AddToCustomBoard(223, TILE_EMPTY, "House", 1, 105, 2);
			AddToCustomBoard(225, TILE_EMPTY, "House", 1, 165, 2);
			AddToCustomBoard(229, TILE_EMPTY, "House", 1, 225, 2);
			AddToCustomBoard(230, TILE_EMPTY, "House", 1, 285, 2);
			AddToCustomBoard(234, TILE_EMPTY, "House", 1, 345, 2);
			AddToCustomBoard(238, TILE_EMPTY, "House", 1, 345, 2);
			AddToCustomBoard(242, TILE_EMPTY, "House", 1, 285, 2);
			AddToCustomBoard(246, TILE_EMPTY, "House", 1, 225, 2);
			AddToCustomBoard(250, TILE_EMPTY, "House", 1, 165, 2);
			AddToCustomBoard(254, TILE_EMPTY, "House", 1, 105, 2);
			/* Opponent */
			InitBot(BOT_PERSONALITY_TRAINING);
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
					trQuestVarSet("dimension", 6);	
					/* Opponent */
					trQuestVarSet("p2commanderType", 902);
					for(x=0;<6){
						addCardToDeck(2, "Swordsman");
						addCardToDeck(2, "Bondi");
						addCardToDeck(2, "Toxotes");
					}	
					for(x=0;<5){
						addCardToDeck(2, "", SPELL_DEFENDER);
						addCardToDeck(2, "Trident Soldier");
					}	
					for(x=0;<3){
						addCardToDeck(2, "Huskarl");
						addCardToDeck(2, "", SPELL_PARTY_UP);
						addCardToDeck(2, "", SPELL_DUEL);
						addCardToDeck(2, "", SPELL_VICTORY);
					}						
				}
				case 3:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 6);	
					/* Opponent */
					trQuestVarSet("p2commanderType", 904);
					for(x=0;<6){
						addCardToDeck(2, "Wolf");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Bear");
						addCardToDeck(2, "Hetairoi");
						addCardToDeck(2, "Hero Greek Theseus");
					}
					for(x=0;<4){
						addCardToDeck(2, "", SPELL_SING);
						addCardToDeck(2, "", SPELL_GUARDIAN_OF_SEA);
					}					
					addCardToDeck(2, "Hero Chinese Immortal");
					addCardToDeck(2, "Hero Greek Hippolyta");	
				}
				case 4:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 59, false);
					trQuestVarSet("dimension", 7);
					trQuestVarSet("dontPlaceRandomStuff", 1);
					trQuestVarSet("customTerrainEmpty", 63);
					trQuestVarSet("customTerrainEmptyNot", 94);
					/* River Middle */
					AddToCustomBoard(268, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(230, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(198, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(172, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(152, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(138, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(130, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(128, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(133, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(144, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(161, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(184, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(213, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(248, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(289, TILE_IMPASSABLE, "Bush Short", 4);
					/* River Up */
					AddToCustomBoard(266, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(228, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(196, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(170, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(150, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(136, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(129, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(134, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(145, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(162, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(185, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(214, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(249, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(290, TILE_IMPASSABLE, "Bush Short", 4);
					/* River Down */
					AddToCustomBoard(269, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(231, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(199, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(173, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(153, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(139, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(131, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(132, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(143, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(160, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(183, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(212, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(247, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(288, TILE_IMPASSABLE, "Bush Short", 4);
					
					AddToCustomBoard(150, TILE_OCCUPIED, "Dock", 1, 45, 1);
					summonAtTile(152, 2, kbGetProtoUnitID("Pirate Ship"));
									
					AddToCustomBoard(195, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(151, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(141, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(237, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(221, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(174, TILE_EMPTY, "Rock Limestone Sprite", 5);
					AddToCustomBoard(137, TILE_EMPTY, "Rock Limestone Sprite", 5);
					
					AddToCustomBoard(142, TILE_OCCUPIED, "Marsh Tree", 1, 47, 2);	
					AddToCustomBoard(158, TILE_OCCUPIED, "Marsh Tree", 1, 69, 2);
					AddToCustomBoard(181, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(180, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(210, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(209, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(205, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(239, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(238, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(204, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(229, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(227, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(195, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(197, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(220, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(190, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(224, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(192, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(175, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(155, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(176, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(177, TILE_IMPASSABLE, "Bush Short", 4);
					AddToCustomBoard(220, TILE_OCCUPIED, "Marsh Tree", 1, 42, 2);
					AddToCustomBoard(200, TILE_OCCUPIED, "Marsh Tree", 1, 47, 2);
					AddToCustomBoard(244, TILE_OCCUPIED, "Marsh Tree", 1, 69, 2);					
					
					AddToCustomBoard(253, TILE_OCCUPIED, "Tent", 1, 225, 1);
					AddToCustomBoard(252, TILE_OCCUPIED, "Tent", 1, 225, 1);	
					AddToCustomBoard(217, TILE_OCCUPIED, "Campfire", 1, 45, 2);		
					summonAtTile(218, 2, kbGetProtoUnitID("Khopesh"));	
					summonAtTile(216, 2, kbGetProtoUnitID("Khopesh"));						
					AddToCustomBoard(187, TILE_IMPASSABLE, "Crate", 4);	

					/* Border */
					for(x=255;<297){
						trQuestVarSetFromRand("temp", 0, 360, true);			
						AddToCustomBoard(x, TILE_OCCUPIED, "Marsh Tree", 1, trQuestVarGet("temp"), 2);	
					}
					
					/* Opponent */
					trQuestVarSet("p2commanderType", 903);
					for(x=0;<6){
						addCardToDeck(2, "Bondi");
						addCardToDeck(2, "Khopesh");
						addCardToDeck(2, "Avenger");
						addCardToDeck(2, "Raiding Cavalry");					
						addCardToDeck(2, "Jarl");
						addCardToDeck(2, "", SPELL_BACKSTAB);
					}
					for(x=0;<2){
						addCardToDeck(2, "Pirate Ship");
						addCardToDeck(2, "", SPELL_PISTOL_SHOT);
					}					
				}
				case 5:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 8, false);
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
				case 6:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 11, false);
					trQuestVarSet("dimension", 7);	
					trQuestVarSet("dontPlaceRandomStuff", 1);
					trQuestVarSet("customTerrainEmpty", 8);
					trQuestVarSet("customTerrainEmptyNot", 90);
					/* Middle */
					AddToCustomBoard(128, TILE_OCCUPIED, "Gaia Pool", 1, 0, 1);
					for(x=129;<134){
						AddToCustomBoard(x, TILE_OCCUPIED, "Parrot", 1, 0, 2);	
					}
					/* Border */
					for(x=255;<297){
						trQuestVarSetFromRand("temp", 0, 360, true);	
						AddToCustomBoard(x, TILE_OCCUPIED, "Gaia Forest Tree", 1, trQuestVarGet("temp"), 2);	
					}
					/* Opponent */
					trQuestVarSet("p2commanderType", 904);
					for(x=0;<5){
						addCardToDeck(2, "Wolf");
						addCardToDeck(2, "Ornlu");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Bear");
						addCardToDeck(2, "Hetairoi");
						addCardToDeck(2, "Hero Greek Theseus");
					}
					for(x=0;<4){		
						addCardToDeck(2, "Hero Greek Hippolyta");
						addCardToDeck(2, "Hero Chinese Immortal");
					}		
					addCardToDeck(2, "", SPELL_ELVEN_APOCALYPSE);
					addCardToDeck(2, "", SPELL_ELVEN_APOCALYPSE);					
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
					trPaintTerrain(0, 0, 60, 60, 0, T_GREEK_CLIFF_B, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("dontPlaceRandomStuff", 1);
					trQuestVarSet("customTerrainEmpty", T_GRASS_75);
					trQuestVarSet("customTerrainEmptyNot", T_GREEK_ROAD);
					yClearDatabase("customBoard");
					AddToCustomBoard(136, TILE_IMPASSABLE, "Columns Broken", 3);
					AddToCustomBoard(137, TILE_IMPASSABLE, "Columns Broken", 3);
					AddToCustomBoard(140, TILE_IMPASSABLE, "Columns Broken", 3);
					AddToCustomBoard(144, TILE_IMPASSABLE, "Columns Broken", 3);
					AddToCustomBoard(142, TILE_IMPASSABLE, "Columns Broken", 3);
					AddToCustomBoard(210, TILE_IMPASSABLE, "Columns Broken", 3);
					AddToCustomBoard(206, TILE_IMPASSABLE, "Columns Broken", 3);
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
	unitTransform("Shockwave stun effect", "Cinematic Block");
	unitTransform("UI Range Indicator Norse SFX", "Cinematic Block");
	unitTransform("Poison SFX", "Cinematic Block");
	unitTransform("Chaos effect", "Cinematic Block");
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
	yClearDatabase("customBoard");
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
			setCardCountCollection(6, 3);
			setCardCountDeck(36, 2);
			setCardCountCollection(36, 3);
			setClassProgress(CLASS_ADVENTURER, 1);
			setClassProgress(CLASS_ARCANE, 1);
			setClassProgress(CLASS_NAGA, 0);
			setClassProgress(CLASS_CLOCKWORK, 0);
			setClassProgress(CLASS_EVIL, 0);
			setClassProgress(CLASS_SPACE, 0);
			setDeckCommander(0);
		} else {
			trOverlayText(collectionMission, 4.7, 500, 200, 1000);
			if(trQuestVarGet("missionHardmode") == 0){
				xsEnableRule("StoryClass" + 1*trQuestVarGet("missionClass") + "Mission" + 1*trQuestVarGet("missionSelection"));
			}
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
		for(x=zGetBankCount("tiles"); >0) {
			highlightTile(zBankNext("tiles"), 0.1);
		}			
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
				xsDisableRule("StoryTutorial1");
				xsDisableRule("StoryTutorial2");
				xsDisableRule("StoryTutorial3");
				xsDisableRule("StoryTutorial4");
				xsDisableRule("StoryTutorial5");
			} else {
				/* Progress Current Story */
				if(trQuestVarGet("missionHardmode") == 0){
					setClassProgress(1*trQuestVarGet("missionClass"), getClassProgress(1*trQuestVarGet("missionClass")) + 1);
				}
				/* Reward Pack Cards */
				for(i=0;<6){
					trQuestVarSet("packReward" + i, -1);
					/* Extras Rarity */
					for(k=0;<3000){
						/* Legendary Rarity */
						for(j=0;<3){
							trQuestVarSetFromRand("reward", 0, 29, true);
							if(trQuestVarGet("reward") != 14 && trQuestVarGet("reward") != 29){
								break;
							}
						}			
					
						int maxCopies = 3;			
						if(trQuestVarGet("reward") == 14 || trQuestVarGet("reward") == 29){
							maxCopies = 1;
						}				
					
						int class = trQuestVarGet("missionClass");
						
						if(trQuestVarGet("missionHardmode") > 0){
							if(getClassProgress(CLASS_SPACE) > 0){
								trQuestVarSetFromRand("temp", 0, 5, true);
							} else {
								trQuestVarSetFromRand("temp", 0, 4, true);
							}					
							class = trQuestVarGet("temp");
						}
					
						int reward = trQuestVarGet("reward") + 30 * class;
								
						if((getCardCountDeck(reward) + getCardCountCollection(reward)) < maxCopies){
							setCardCountCollection(reward, getCardCountDeck(reward) + getCardCountCollection(reward) + 1);
							trQuestVarSet("packReward" + i, reward);
							break;
						}
					}
				}			
			}
			dataSave();
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
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryTutorial0");		
		trShowImageDialog("Zenophobia\SFA\Nick", "Zeno was supposed to make some pretty images for this tutorial but did he? Of course not!");
		trSoundPlayFN("llamaselect1.wav","1",-1,"","");			
		xsEnableRule("StoryTutorial1");
   }
}

rule StoryTutorial1
highFrequency
inactive
{
	if (trQuestVarGet("p1drawCards") + trQuestVarGet("p2drawCards") == 0) {
		trShowImageDialog("Zenophobia\SFA\Nick", "Anyway, this is the mulligan. Highlighted cards will be kept and the rest shuffled back in deck.");
		trSoundPlayFN("llamagrunt2.wav","1",-1,"","");	
		xsDisableRule("StoryTutorial1");
		xsEnableRule("StoryTutorial2");		
	}
}

rule StoryTutorial2
highFrequency
inactive
{
	if (trQuestVarGet("p1done") + trQuestVarGet("p2done") == 2){	
		trShowImageDialog("Zenophobia\SFA\Nick", "Left Click to select.");
		trSoundPlayFN("llamamove2.wav","1",-1,"","");
		xsDisableRule("StoryTutorial2");
		xsEnableRule("StoryTutorial3");
		xsEnableRule("StoryTutorial4");
		xsEnableRule("StoryTutorial5");
	}
}


rule StoryTutorial3
highFrequency
inactive
{
	if (trQuestVarGet("gameplayPhase") == GAMEPLAY_WORK){	
		trShowImageDialog("Zenophobia\SFA\Nick", "You selected a unit on the battlefield. Right Click to move or attack.");
		trSoundPlayFN("llamamove2.wav","1",-1,"","");	
		xsDisableRule("StoryTutorial3");
	}
}


rule StoryTutorial4
highFrequency
inactive
{
	if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SUMMONING || trQuestVarGet("gameplayPhase") == GAMEPLAY_SPELL_UNIT || trQuestVarGet("gameplayPhase") == GAMEPLAY_SPELL_TILE){	
		trShowImageDialog("Zenophobia\SFA\Nick", "You selected a card from hand. Left Click again to play or Right Click to cancel.");
		trSoundPlayFN("llamamove2.wav","1",-1,"","");	
		xsDisableRule("StoryTutorial4");
	}
}

rule StoryTutorial5
highFrequency
inactive
{
	if (trCountUnitsInArea(""+1*trQuestVarGet("p2commander"),1,"Unit",27) > 0){	
		trShowImageDialog("Zenophobia\SFA\Nick", "Commanders have that light effect. Kill the enemy Commander while keeping yours alive to win.");
		trSoundPlayFN("llamagrunt1.wav","1",-1,"","");	
		xsDisableRule("StoryTutorial5");
	}
}

rule StoryClass0Mission1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission1");		
		trShowImageDialog("World Berry Bush icon 64", "Not long after starting your journey, a large figure comes running to greet you.");	
		trSoundPlayFN("gaiatreesprout1.wav","1",-1,"","");	
   }
}

rule StoryClass0Mission2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission2");		
		trShowImageDialog("icons/scenario x general icons 64", "Hello civilian! We will take your money to fund the army. Standard procedure.");	
		trSoundPlayFN("llamaselect1.wav","1",-1,"","");	
   }
}

rule StoryClass0Mission3
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission3");		
		trShowImageDialog("icons/Special C Qilin Icon", "I am the Protector of this forest.");	
		trSoundPlayFN("qilin_select1.wav","1",-1,"","");	
   }
}

rule StoryClass0Mission4
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission4");		
		trShowImageDialog("icons/Scenario Kemsyt Icon 64", "Ready the cannons! We have treasure to plunder!");	
		trSoundPlayFN("kemsytattack1.wav","1",-1,"","");	
   }
}

rule StoryClass0Mission5
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission5");		
		trShowImageDialog("icons/god power audrey icons 64", "*plant noises*");	
		trSoundPlayFN("carnivorabirth.wav","1",-1,"","");	
   }
}

rule StoryClass0Mission6
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission6");		
		trShowImageDialog("icons/Special C Qilin Icon", "This time we fight for real!");
		trSoundPlayFN("qilin_select2.wav","1",-1,"","");	
   }
}

rule StoryClass1Mission1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass1Mission1");			
		trShowImageDialog("icons/improvement granite blood icon 64", "As you approach the Arcane Tower, you notice something blocking the way. It moves.");	
		trSoundPlayFN("medusastone.wav","1",-1,"","");	
   }
}