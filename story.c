/*
These are functions are called to play the storyline
CinematicReset();
CinematicAdd("icons/infantry g hoplite icon 64", "pen island");
CinematicStart();
*/

void CinematicReset() {
	trQuestVarSet("cinematicStep", 0);
	trQuestVarSet("cinematicLength", 0);
}

/*
i = icon
s = string text
*/
void CinematicAdd(string i = "", string s = "") {
	trQuestVarSet("cinematicLength", 1 + trQuestVarGet("cinematicLength"));
	trStringQuestVarSet("cinematicImage"+1*trQuestVarGet("cinematicLength"), i);
	trStringQuestVarSet("cinematicText"+1*trQuestVarGet("cinematicLength"), s);
}

/*
m = music filename
*/
void CinematicStart(string m = "") {
	trMusicPlay(m, "1", 0);
	xsEnableRule("Story_Cinematic_Play");
}


void AddToCustomBoard(int tile = 0, int terrain = 0, string proto = "", int count = 1, int heading = 45, int scale = 1){
	yAddToDatabase("customBoard", "thisDoesNotMatterRight");
	yAddUpdateVar("customBoard", "tile", tile);
	yAddUpdateVar("customBoard", "terrain", terrain);
	yAddUpdateVar("customBoard", "proto", kbGetProtoUnitID(proto));
	yAddUpdateVar("customBoard", "count", count);
	yAddUpdateVar("customBoard", "heading", heading);
	yAddUpdateVar("customBoard", "scale", scale);
}

int SummonLaser(int tile = 0, int target = 0) {
	int siphon = summonAtTile(tile, 2, kbGetProtoUnitID("Fire Siphon"));
	trVectorQuestVarSet("start", kbGetBlockPosition(""+tile));
	trVectorQuestVarSet("end", kbGetBlockPosition(""+target));
	trVectorQuestVarSet("dir", zGetUnitVector("start", "end"));
	mSetVar(siphon, "laserDirx", trQuestVarGet("dirx"));
	mSetVar(siphon, "laserDirz", trQuestVarGet("dirz"));
	trUnitSelectClear();
	trUnitSelect(""+siphon);
	trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
	return(siphon);
}

void SetupMission(int class = 0, int mission = 0){
	yClearDatabase("p2deck");
	yClearDatabase("customBoard");
	trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_GRASSLAND);
	trQuestVarSet("customTerrainEmpty", 0);
	trQuestVarSet("customTerrainEmptyNot", 0);
	InitBot(BOT_PERSONALITY_DEFAULT);
	trQuestVarSet("dungeonMode", 0);
	trQuestVarSet("p2class1", class);
	switch(class)
	{
		case -1:
		{
			// Tutorial
			/* Arena */
			trPaintTerrain(0, 0, 60, 60, 0, T_EGYPTIAN_ROAD, false);
			trQuestVarSet("dimension", 5);
			trQuestVarSet("zenoMakeRandomStuffPlease", -1);
			trQuestVarSet("customTerrainEmpty", T_GRASS_25);
			trQuestVarSet("customTerrainEmptyNot", T_FOREST_PALM);
			AddToCustomBoard(150, TILE_IMPASSABLE, "Crate", 3);
			AddToCustomBoard(151, TILE_IMPASSABLE, "Crate", 3);
			AddToCustomBoard(136, TILE_IMPASSABLE, "Crate", 3);
			AddToCustomBoard(137, TILE_IMPASSABLE, "Crate", 3);
			AddToCustomBoard(129, TILE_IMPASSABLE, "Crate", 3);
			
			AddToCustomBoard(223, TILE_EMPTY, "Wood Pile 1", 1, 105, 2);
			AddToCustomBoard(225, TILE_EMPTY, "Wood Pile 2", 1, 165, 2);
			AddToCustomBoard(229, TILE_EMPTY, "Wood Pile 3", 1, 225, 2);
			AddToCustomBoard(230, TILE_EMPTY, "Wood Pile 3", 1, 285, 2);
			AddToCustomBoard(234, TILE_EMPTY, "Wood Pile 2", 1, 345, 2);
			AddToCustomBoard(238, TILE_EMPTY, "Wood Pile 1", 1, 345, 2);
			AddToCustomBoard(240, TILE_EMPTY, "Wood Pile 1", 1, 285, 2);
			AddToCustomBoard(246, TILE_EMPTY, "Wood Pile 2", 1, 225, 2);
			AddToCustomBoard(250, TILE_EMPTY, "Wood Pile 3", 1, 165, 2);
			AddToCustomBoard(254, TILE_EMPTY, "Wood Pile 3", 1, 105, 2);
			/* Opponent */
			InitBot(BOT_PERSONALITY_TRAINING);
			trQuestVarSet("p2commanderType", kbGetProtoUnitID("Automaton"));
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
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
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
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Bear"));
					for(x=0;<40){
						addCardToDeck(2, "", SPELL_INTIMIDATE);
					}
				}
				case 2:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_GRASSLAND);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("General Melagius"));
					for(x=0;<6){
						addCardToDeck(2, "Swordsman");
						addCardToDeck(2, "Bondi");
						addCardToDeck(2, "Toxotes");
					}
					for(x=0;<4){
						addCardToDeck(2, "", SPELL_DEFENDER);
						addCardToDeck(2, "Trident Soldier");
					}
					for(x=0;<3){
						addCardToDeck(2, "Huskarl");
						addCardToDeck(2, "Hero Greek Ajax");
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
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_GRASSLAND);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Qilin"));
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
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
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
					
					AddToCustomBoard(253, TILE_OCCUPIED, "Wood Pile 1", 1, 225, 1);
					AddToCustomBoard(187, TILE_OCCUPIED, "Wood Pile 1", 1, 225, 1);
					AddToCustomBoard(217, TILE_OCCUPIED, "Tent", 1, 225, 1);
					AddToCustomBoard(252, TILE_OCCUPIED, "Campfire", 1, 45, 2);
					summonAtTile(218, 2, kbGetProtoUnitID("Khopesh"));
					summonAtTile(216, 2, kbGetProtoUnitID("Khopesh"));
					
					/* Border */
					for(x=255;<297){
						if(x != 282){
							trQuestVarSetFromRand("temp", 0, 360, true);
							AddToCustomBoard(x, TILE_OCCUPIED, "Marsh Tree", 1, trQuestVarGet("temp"), 2);
						}
					}
					
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Shaba Ka"));
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
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_GRASSLAND);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Audrey"));
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
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", 8);
					trQuestVarSet("customTerrainEmptyNot", 90);
					/* Middle */
					AddToCustomBoard(128, TILE_OCCUPIED, "Gaia Pool", 1, 0, 1);
					for(x=129;<135){
						AddToCustomBoard(x, TILE_OCCUPIED, "Parrot", 1, 0, 2);
					}
					/* Border */
					for(x=255;<297){
						if(x != 282){
							trQuestVarSetFromRand("temp", 0, 360, true);
							AddToCustomBoard(x, TILE_OCCUPIED, "Gaia Forest Tree", 1, trQuestVarGet("temp"), 2);
						}
					}
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Qilin"));
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
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_GRASS_75);
					trQuestVarSet("customTerrainEmptyNot", T_GREEK_ROAD);
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
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Golem"));
					for(x=0;<40){
						addCardToDeck(2, "", SPELL_GROUND_STOMP);
					}
				}
				case 2:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 7);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_TOWER);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Pharaoh Secondary"));
					for(x=0;<5){
						addCardToDeck(2, "Slinger");
						addCardToDeck(2, "Monument");
						addCardToDeck(2, "Oracle Scout");
						addCardToDeck(2, "", SPELL_SPARK);
						addCardToDeck(2, "", SPELL_EXPLOSION);
						addCardToDeck(2, "", SPELL_PYROBALL);
					}
					for(x=0;<2){
						addCardToDeck(2, "Slinger");
						addCardToDeck(2, "", SPELL_SPARK);
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
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_TOWER);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("King Folstag"));
					for(x=0;<6){
						addCardToDeck(2, "Maceman");
						addCardToDeck(2, "Monument");
						addCardToDeck(2, "Monument 2");
						addCardToDeck(2, "Monument 3");
						addCardToDeck(2, "", SPELL_RUNE_OF_ICE);
						addCardToDeck(2, "", SPELL_FROST_BREATH);
					}
					addCardToDeck(2, "Griffon");
					addCardToDeck(2, "Trident Soldier Hero");
					addCardToDeck(2, "", SPELL_CLASS_TIME);
					addCardToDeck(2, "", SPELL_ELECTROSURGE);
				}
				case 4:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 2);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Boar"));
					for(x=0;<4){
						addCardToDeck(2, "Maceman");
						addCardToDeck(2, "Centaur");
						addCardToDeck(2, "Griffon");
						addCardToDeck(2, "Golem");
						addCardToDeck(2, "", SPELL_SPARK);
						addCardToDeck(2, "", SPELL_BACKSTAB);
						addCardToDeck(2, "", SPELL_FINAL_EXAM);
						addCardToDeck(2, "", SPELL_PYROBALL);
						addCardToDeck(2, "", SPELL_METEOR);
					}
					addCardToDeck(2, "Trident Soldier Hero");
					addCardToDeck(2, "", SPELL_CLASS_TIME);
					addCardToDeck(2, "", SPELL_ELECTROSURGE);
					addCardToDeck(2, "", SPELL_APOCALYPSE);
				}
				case 5:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_TOWER);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Setna"));
					for(x=0;<3){
						addCardToDeck(2, "Maceman");
						addCardToDeck(2, "Slinger");
						addCardToDeck(2, "Oracle Scout");
						addCardToDeck(2, "Griffon");
						addCardToDeck(2, "Golem");
						addCardToDeck(2, "Monument");
						addCardToDeck(2, "Monument 2");
						addCardToDeck(2, "Monument 3");
						addCardToDeck(2, "Monument 4");
						addCardToDeck(2, "", SPELL_SPARK);
						addCardToDeck(2, "", SPELL_CLASS_TIME);
						addCardToDeck(2, "", SPELL_MIRROR_REFLECTION);
						addCardToDeck(2, "", SPELL_PYROBALL);
					}
					addCardToDeck(2, "Monument 5");
				}
				case 6:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 7);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Border */
					for(x=255;<297){
						AddToCustomBoard(x, TILE_OCCUPIED, "Mist", 1, 0, 1);
					}
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Circe"));
					for(x=0;<3){
						addCardToDeck(2, "Maceman");
						addCardToDeck(2, "Slinger");
						addCardToDeck(2, "Oracle Scout");
						addCardToDeck(2, "Griffon");
						addCardToDeck(2, "Golem");
						addCardToDeck(2, "Monument");
						addCardToDeck(2, "Monument 2");
						addCardToDeck(2, "Monument 3");
						addCardToDeck(2, "Monument 4");
						addCardToDeck(2, "", SPELL_SPARK);
						addCardToDeck(2, "", SPELL_CLASS_TIME);
						addCardToDeck(2, "", SPELL_MIRROR_REFLECTION);
						addCardToDeck(2, "", SPELL_PYROBALL);
					}
					addCardToDeck(2, "Monument 5");
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
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Scylla"));
					trPaintTerrain(0, 0, 59, 59, 5, 2, false); // ice c
					for(x=0;<4) {
						addCardToDeck(2, "Wadjet");
						addCardToDeck(2, "Jormund Elver");
						addCardToDeck(2, "Medusa");
						addCardToDeck(2, "Cyclops");
						addCardToDeck(2, "", SPELL_SEA_EMBRACE);
						addCardToDeck(2, "Nereid");
						addCardToDeck(2, "Hydra");
						addCardToDeck(2, "", SPELL_TELETIDE);
						addCardToDeck(2, "", SPELL_WRATH_OF_SEA);
						addCardToDeck(2, "", SPELL_DROWN);
					}
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
				case 2:
				{
					trQuestVarSet("dimension", 3);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Man O War"));
					trPaintTerrain(0, 0, 59, 59, 5, 2, false); // ice c
					for(x=0;<20) {
						addCardToDeck(2, "Man O War");
						addCardToDeck(2, "", SPELL_ELECTROSURGE);
					}
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
				case 3:
				{
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_ATLANTIS);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Polyphemus"));
					for(x=0;<4) {
						addCardToDeck(2, "Wadjet");
						addCardToDeck(2, "Hippikon");
						addCardToDeck(2, "", SPELL_TELETIDE);
						addCardToDeck(2, "Medusa");
					}
					for(x=0;<4) {
						addCardToDeck(2, "Man O War");
						addCardToDeck(2, "", SPELL_SEA_EMBRACE);
						addCardToDeck(2, "Leviathan");
						addCardToDeck(2, "Hydra");
						addCardToDeck(2, "Sea Turtle");
						addCardToDeck(2, "", SPELL_DROWN);
					}
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
				case 4:
				{
					trQuestVarSet("dimension", 5);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_ATLANTIS);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Kraken"));
					for(x=0;<10) {
						addCardToDeck(2, "Wadjet");
						addCardToDeck(2, "Medusa");
						addCardToDeck(2, "Jormund Elver");
						addCardToDeck(2, "", SPELL_KRAKEN_HUG);
					}
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
				case 5:
				{
					trQuestVarSet("dimension", 7);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_ATLANTIS);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Servant"));
					for(x=0;<10) {
						addCardToDeck(2, "Servant");
						addCardToDeck(2, "", SPELL_WATER_CANNON);
						addCardToDeck(2, "", SPELL_DOMINANCE);
					}
					for(x=0;<2) {
						addCardToDeck(2, "Nereid");
						addCardToDeck(2, "", SPELL_TIDAL_WAVE);
						addCardToDeck(2, "", SPELL_FLUSH);
						addCardToDeck(2, "", SPELL_DEEP_DIVE);
						addCardToDeck(2, "", SPELL_CLASS_TIME);
					}
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
				case 6:
				{
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trPaintTerrain(0, 0, 59, 59, 0, 72, false); // atlantis coral
					trQuestVarSet("p1commanderType", COMMANDER_REACH);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Cinematic Block"));
					AddToCustomBoard(284, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(243, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(208, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(207, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(206, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(205, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(204, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(203, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(202, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(201, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(200, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(199, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(198, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(196, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(194, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(168, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(148, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(135, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(258, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(220, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(189, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(191, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(193, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(195, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(197, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(218, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(217, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(216, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(215, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(214, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(213, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(212, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(211, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(182, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(159, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					AddToCustomBoard(142, TILE_OCCUPIED, "Wall Connector", 1, 0, 2);
					for(x=0;<40) {
						addCardToDeck(2, "", SPELL_NICKS_PORTAL);
					}
					for(x=0;<20) {
						addCardToDeck(2, "", SPELL_SPARK);
						addCardToDeck(2, "", SPELL_METEOR);
						addCardToDeck(2, "", SPELL_EXPLOSION);
					}
					for(x=0;<10) {
						addCardToDeck(2, "", SPELL_ZENOS_PARADOX);
						addCardToDeck(2, "", SPELL_DEATH_APPROACHES);
						addCardToDeck(2, "", SPELL_TIME_POCKET);
						addCardToDeck(2, "", SPELL_WORLD_SPLITTER);
					}
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
			}
		}
		case CLASS_CLOCKWORK:
		{
			switch(mission)
			{
				case 1:
				{
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_SCRAPYARD);
					trQuestVarSet("p2commanderType", COMMANDER_ROXAS);
					for(x=0;<6) {
						addCardToDeck(2, "Automaton SPC");
						addCardToDeck(2, "Dwarf");
						addCardToDeck(2, "Throwing Axeman");
					}
					for(x=0;<3) {
						addCardToDeck(2, "Battle Boar");
						addCardToDeck(2, "", SPELL_REWIND);
						addCardToDeck(2, "Ballista");
						addCardToDeck(2, "Colossus");
						addCardToDeck(2, "Petrobolos");
						addCardToDeck(2, "", SPELL_GEAR_FACTORY);
						addCardToDeck(2, "", SPELL_PORTABLE_SPELL_SHIELD);
					}
					addCardToDeck(2, "", SPELL_POWER_SUIT);
					trQuestVarSet("p2class2", CLASS_CLOCKWORK);
				}
				case 2:
				{
					trQuestVarSet("dimension", 8);
					trQuestVarSet("storyMissionBotMana", 0);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trPaintTerrain(0, 0, 59, 59, 5, 3, false); // mining ground
					trQuestVarSet("customTerrainEmpty", T_SAND_D);
					trQuestVarSet("customTerrainEmptyNot", T_EGYPTIAN_ROAD);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Cinematic Block"));
					AddToCustomBoard(157, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					AddToCustomBoard(158, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					AddToCustomBoard(159, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					
					AddToCustomBoard(153, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					AddToCustomBoard(152, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					AddToCustomBoard(150, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					
					AddToCustomBoard(164, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					AddToCustomBoard(163, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					AddToCustomBoard(151, TILE_OCCUPIED, "Destroyed Buildings Small", 1);
					
					summonAtTile(142, 1, kbGetProtoUnitID("Onager"));
					summonAtTile(138, 1, kbGetProtoUnitID("Onager"));
					summonAtTile(146, 1, kbGetProtoUnitID("Onager"));
					summonAtTile(130, 1, kbGetProtoUnitID("Throwing Axeman"));
					summonAtTile(134, 1, kbGetProtoUnitID("Priest"));
					
					zSetVarByIndex("tiles", "occupant", 282, 0);
					zSetVarByIndex("tiles", "occupant", 219, 0);
					trQuestVarSet("objectiveObelisk", summonAtTile(128, 1, kbGetProtoUnitID("Outpost")));
					mSetVarByQV("objectiveObelisk", "health", 10);
					mSetVarByQV("objectiveObelisk", "spell", SPELL_COMMANDER);
					for(x=0; <6) {
						addCardToDeck(2, "Crossbowman");
						addCardToDeck(2, "", SPELL_WARNING_SHOT);
						addCardToDeck(2, "", SPELL_DOUBLEBLAST);
						addCardToDeck(2, "", SPELL_PORTABLE_SPELL_SHIELD);
					}
				}
				case 3:
				{
					trQuestVarSet("dimension", 6);
					trQuestVarSet("dungeonMode", 1);
					trPaintTerrain(0, 0, 59, 59, 2, 13, false); // black rock
					InitBot(BOT_PERSONALITY_TRAINING);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", 0);
					trQuestVarSet("customTerrainEmptySpecial", T_BLUE_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_BLUE_TILE);
					
					mSetVar(SummonLaser(181, 180), "attack", 5);
					AddToCustomBoard(208, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(207, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(206, TILE_EMPTY, "Cinematic Block", 0);
					mSetVar(SummonLaser(216, 186), "attack", 5);
					AddToCustomBoard(178, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(156, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(157, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(158, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(142, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(132, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(143, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(160, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(212, TILE_EMPTY, "Cinematic Block", 0);
					for(x=188; >=183) {
						AddToCustomBoard(x, TILE_EMPTY, "Cinematic Block", 0);
					}
					mSetVar(SummonLaser(212, 184), "attack", 5);
					mSetVar(SummonLaser(145, 163), "attack", 5);
					AddToCustomBoard(171, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(169, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(167, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(147, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(150, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(148, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(152, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(173, TILE_EMPTY, "Cinematic Block", 0);
					AddToCustomBoard(200, TILE_EMPTY, "Cinematic Block", 0);
					mSetVar(SummonLaser(137, 151), "attack", 5);
					mSetVar(SummonLaser(135, 149), "attack", 5);
					
					mSetVar(SummonLaser(130, 136), "attack", 5);
					mSetVar(SummonLaser(139, 138), "attack", 5);
					mSetVar(SummonLaser(154, 153), "attack", 5);
					mSetVar(SummonLaser(175, 174), "attack", 5);
					
					summonAtTile(193, 2, kbGetProtoUnitID("Servant"));
					deployAtTile(0, "Garrison Flag Sky Passage", 200);
					trQuestVarSet("p1commanderType", COMMANDER_ROGERS);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Invisible Target"));
					yClearDatabase("p1deck");
					for(x=40; >0) {
						addCardToDeck(1, "", SPELL_SCRAP_METAL);
						addCardToDeck(2, "", SPELL_SCRAP_METAL);
					}
				}
				case 4:
				{
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_TOWER);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Eitri"));
					for(x=0;<6){
						addCardToDeck(2, "Helepolis");
						addCardToDeck(2, "", SPELL_MIRROR_IMAGE);
						addCardToDeck(2, "", SPELL_CLASS_TIME);
					}
					for(x=0; <3) {
						addCardToDeck(2, "", SPELL_ASSEMBLY_LINE);
						addCardToDeck(2, "", SPELL_DOMINANCE);
						addCardToDeck(2, "Javelin Cavalry");
						addCardToDeck(2, "Chieroballista");
						addCardToDeck(2, "Tower Mirror");
						addCardToDeck(2, "", SPELL_WARNING_SHOT);
						addCardToDeck(2, "", SPELL_DOUBLEBLAST);
					}
					
					SummonLaser(218, 217);
					SummonLaser(195, 171);
					SummonLaser(191, 167);
					SummonLaser(190, 166);
					SummonLaser(194, 170);
					SummonLaser(198, 199);
					trQuestVarSet("p2class2", CLASS_ARCANE);
				}
				case 5:
				{
					trQuestVarSet("dimension", 3);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Cinematic Block"));
					trPaintTerrain(0, 0, 59, 59, 2, 13, false); // black rock
					InitBot(BOT_PERSONALITY_TRAINING);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_BLUE_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_BLUE_TILE);
					trQuestVarSet("p1commanderType", COMMANDER_ROGERS);
					yClearDatabase("p1deck");
					for(x=40; >0) {
						addCardToDeck(1, "", SPELL_BORROWED_TIME);
						addCardToDeck(2, "Monkey");
					}
				}
				case 6:
				{
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_HEAVEN);
					trQuestVarSet("p2commanderType", COMMANDER_YEEBAAGOOON);
					for(x=0;<6) {
						addCardToDeck(2, "", SPELL_DOMINANCE);
						addCardToDeck(2, "Eitri");
						addCardToDeck(2, "", SPELL_CLASS_TIME);
					}
					for(x=0;<3) {
						addCardToDeck(2, "", SPELL_WARNING_SHOT);
						addCardToDeck(2, "Javelin Cavalry");
						addCardToDeck(2, "", SPELL_BANHAMMER);
						addCardToDeck(2, "Crossbowman");
						addCardToDeck(2, "Maceman Hero");
						addCardToDeck(2, "Chieroballista");
						addCardToDeck(2, "Portable Ram");
						addCardToDeck(2, "Prisoner");
						addCardToDeck(2, "Priest");
					}
					
					summonAtTile(190, 2, kbGetProtoUnitID("Eitri"));
					summonAtTile(191, 2, kbGetProtoUnitID("Eitri"));
					trQuestVarSet("p2class2", CLASS_ARCANE);
				}
			}
		}
		case CLASS_EVIL:
		{
			switch(mission)
			{
				case 1:
				{
					/* Arena */
					trQuestVarSet("dimension", 5);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_MARSH);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Tartarian Gate"));
					for(x=0;<8){
						addCardToDeck(2, "Walking Woods Marsh");
						addCardToDeck(2, "Dryad");
					}
					for(x=0;<5){
						addCardToDeck(2, "", SPELL_FINAL_FRENZY);
						addCardToDeck(2, "", SPELL_DEATH_APPROACHES);
						addCardToDeck(2, "Mummy");
					}
					for(x=0;<3){
						addCardToDeck(2, "Shade");
						addCardToDeck(2, "", SPELL_DUEL);
						addCardToDeck(2, "", SPELL_DEFENDER);
					}
					trQuestVarSet("p2class2", CLASS_ADVENTURER);
				}
				case 2:
				{
					/* Arena */
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_CAVE);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Einheriar"));
					for(x=0;<6){
						addCardToDeck(2, "", SPELL_SOUL_SIPHON);
						addCardToDeck(2, "", SPELL_RUNE_OF_DARKNESS);
						addCardToDeck(2, "Prodromos");
						addCardToDeck(2, "Spearman");
					}
					for(x=0;<9){
						addCardToDeck(2, "", SPELL_SPIDER_LAIR);
					}
					for(x=0;<3){
						addCardToDeck(2, "", SPELL_POISON_CLOUD);
						addCardToDeck(2, "", SPELL_BLOOD_PRICE);
						addCardToDeck(2, "Argus");
					}
					trQuestVarSet("p2class2", CLASS_EVIL);
				}
				case 3:
				{
					/* Arena */
					trQuestVarSet("dimension", 7);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_MARSH);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Achilles"));
					for(x=0;<6){
						addCardToDeck(2, "Bogsveigir");
						addCardToDeck(2, "Dryad");
						addCardToDeck(2, "Manticore");
					}
					for(x=0;<3){
						addCardToDeck(2, "", SPELL_DOOM);
						addCardToDeck(2, "", SPELL_METEOR);
						addCardToDeck(2, "Argus");
						addCardToDeck(2, "", SPELL_EXPLOSION);
						addCardToDeck(2, "", SPELL_DEATH_APPROACHES);
						addCardToDeck(2, "Mummy");
						addCardToDeck(2, "Walking Woods Marsh");
						addCardToDeck(2, "Theris");
						addCardToDeck(2, "Tartarian Gate");
					}
					trQuestVarSet("p2class2", CLASS_ARCANE);
				}
				case 4:
				{
					trQuestVarSet("dimension", 8);
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 2, 2, false);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_SAND_D);
					trQuestVarSet("customTerrainEmptyNot", T_HADES_FOREST);
					/* Walls */
					AddToCustomBoard(285, TILE_OCCUPIED, "Bolder Rolling Small", 1);
					AddToCustomBoard(244, TILE_OCCUPIED, "Bolder Rolling Small", 1);
					AddToCustomBoard(209, TILE_OCCUPIED, "Bolder Rolling Small", 1);
					for (x=180; >= 165) {
						AddToCustomBoard(x, TILE_OCCUPIED, "Bolder Rolling Small", 1);
					}
					for (x=188; >= 183) {
						AddToCustomBoard(x, TILE_OCCUPIED, "Bolder Rolling Small", 1);
					}
					
					summonAtTile(236, 2, kbGetProtoUnitID("Tartarian Gate"));
					summonAtTile(219, 2, kbGetProtoUnitID("Tartarian Gate"));
					summonAtTile(248, 2, kbGetProtoUnitID("Tartarian Gate"));
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Invisible Target"));
					
					for(x=0;<6){
						addCardToDeck(2, "Fire Giant");
						addCardToDeck(2, "Walking Woods Marsh");
						addCardToDeck(2, "Dryad");
						addCardToDeck(2, "Argus");
						addCardToDeck(2, "Wadjet");
						addCardToDeck(2, "Pharaoh");
					}
					for(x=0; <20) {
						addCardToDeck(2, "Anubite");
						addCardToDeck(2, "Minion");
					}
					trQuestVarSet("p2class1", CLASS_NAGA);
				}
				case 5:
				{
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_HEAVEN);
					trQuestVarSet("p2commanderType", COMMANDER_ZENOPHOBIA);
					
					summonAtTile(190, 2, kbGetProtoUnitID("Theris"));
					summonAtTile(191, 2, kbGetProtoUnitID("Theris"));
					
					
					for(x=0;<6){
						addCardToDeck(2, "Female");
						addCardToDeck(2, "Archer Atlantean");
					}
					
					for(x=0;<3) {
						addCardToDeck(2, "Theris");
						addCardToDeck(2, "Bireme");
						addCardToDeck(2, "Hippocampus");
						addCardToDeck(2, "Scylla");
						addCardToDeck(2, "Mummy");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Sea Turtle");
						addCardToDeck(2, "", SPELL_DOMINANCE);
						addCardToDeck(2, "", SPELL_WORLD_SPLITTER);
					}
					addCardToDeck(2, "", SPELL_TAVERN_BRAWL);
					addCardToDeck(2, "Hero Greek Achilles");
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
				case 6:
				{
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_HEAVEN);
					trQuestVarCopy("p2commanderType", "p1commanderType");
					
					summonAtTile(190, 2, kbGetProtoUnitID("Bireme"));
					summonAtTile(191, 2, kbGetProtoUnitID("Bireme"));
					
					for(x=yGetDatabaseCount("p1deck"); >0) {
						yDatabaseNext("p1deck");
						yAddToDatabase("p2deck", "p1deck");
						yTransferUpdateVar("p2deck", "p1deck", "spell");
						yTransferUpdateVar("p2deck", "p1deck", "proto");
					}
					for(x=0;<6) {
						addCardToDeck(2, "Theris");
						addCardToDeck(2, "", SPELL_DOMINANCE);
					}
					trQuestVarCopy("p2class1", "p1class1");
					trQuestVarCopy("p2class2", "p1class2");
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
	trQuestVarSet("apocalypse", 0);
	trQuestVarSet("maxMana", 0);
	for(p=2; >0) {
		trCounterAbort("mana"+p);
		trCounterAbort("handAndDeck"+p);
		trQuestVarSet("p"+p+"mana", 0);
		trQuestVarSet("p"+p+"manaTax", 0);
		trQuestVarSet("p"+p+"manaflow", 0);
		trQuestVarSet("p"+p+"extraManaflow", 0);
		trQuestVarSet("p"+p+"spellDamageNonOracle", 0);
		trQuestVarSet("p"+p+"yeebbonus", 0);
		trQuestVarSet("p"+p+"roxasHealth", 0);
		trQuestVarSet("p"+p+"guardianOfTheSea", 0);
		for(x=zGetBankCount("p"+p+"handPos"); >0) {
			zBankNext("p"+p+"handPos");
			zSetVar("p"+p+"handPos", "occupied", 0);
		}
		yDatabasePointerDefault("p"+p+"hand");
		for(x=yGetDatabaseCount("p"+p+"hand"); >0) {
			yDatabaseNext("p"+p+"hand", true);
			mSetVarByQV("p"+p+"hand", "played", 0);
			trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		}
		yClearDatabase("p"+p+"hand");
		updateHandPlayable(p);
	}
	yClearDatabase("customBoard");
	for(i=trQuestVarGet("idsEyecandyStart");<trQuestVarGet("idsEyecandyEnd")){
		trUnitSelectClear();trUnitSelect(""+i);
		trUnitDestroy();
	}
	yDatabasePointerDefault("allUnits");
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		mSetVarByQV("allUnits", "played", 0);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		tileGuard(1*mGetVarByQV("allUnits", "tile"), false);
		zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("allUnits", "tile"), 0);
	}
	yClearDatabase("allUnits");
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
			/* Starter Deck */
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
			xsEnableRule("StoryClass" + 1*trQuestVarGet("missionClass") + "Mission" + 1*trQuestVarGet("missionSelection"));
			if(trQuestVarGet("missionClass") == 0 && trQuestVarGet("missionSelection") == 3){
				xsEnableRule("StoryClass0Mission3_");
			}
			xsEnableRule("SelectCommander");
		}
		/* Add Cards to Deck */
		yClearDatabase("p1deck");
		for(i=0;<180){
			for(x=0;<getCardCountDeck(i)){
				addCardToDeckByIndex(1, i);
			}
		}
		shuffleDeck(1);
		
		SetupMission(trQuestVarGet("missionClass"), trQuestVarGet("missionSelection"));
		trQuestVarSet("missionComplete", 0);
		xsEnableRule("initializeBoard");
		xsDisableRule("MissionBegin");
	}
}

bool PlayerDefeated(int p = 1){
	return (trQuestVarGet("p"+p+"defeated") == 1);
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
		xsDisableRule("gameplay_01_select");
		xsDisableRule("gameplay_02_work");
		xsDisableRule("gameplay_03_moveComplete");
		xsDisableRule("gameplay_04_attack");
		xsDisableRule("gameplay_05_attackComplete");
		xsDisableRule("gameplay_10_summon");
		xsDisableRule("MissionEnd");
		xsDisableRule("turn_00_start");
		xsDisableRule("turn_01_resolve_turn_start");
		xsDisableRule("turn_02_end");
		xsDisableRule("SelectCommander");
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
			trQuestVarSet("newCards", 1);
		}
		/* If you lost the Tutorial restart, otherwise go to collection */
		if(defeat && collectionMission == ""){
			trQuestVarSet("restartMission", 1);
		} else {
			trQuestVarSet("restartMission", 0);
		}
		xsEnableRule("MissionEnd1");
	}
}


void CommanderUnlockLine(int class = -1){
	switch(class)
	{
		case -1:
		{
			trShowImageDialog("icons/infantry x Oracle hero icons 64", "You must be pretty good to finish the tutorial. Mind if I tag along?");
			trSoundPlayFN("ahs4.wav","1",-1,"","");
		}
		case CLASS_ADVENTURER:
		{
			trShowImageDialog("icons/cavalry x Lancer hero icons 64", "Sorry you had to come all this way, I was working on LOME. Now what's all this about?");
			trSoundPlayFN("aha1.wav","1",-1,"","");
		}
		case CLASS_ARCANE:
		{
			trShowImageDialog("icons/Special G Minotaur Icon 64", "Ah! You found me! I'll join you but I won't be using my Arcane God powers, that would make things too easy.");
			trSoundPlayFN("minotaurgore.wav","1",-1,"","");
		}
		case CLASS_NAGA:
		{
			trShowImageDialog("icons/archer x arcus hero icons 64", "It's scragins time!");
			trSoundPlayFN("aha2.wav","1",-1,"","");
		}
		case CLASS_CLOCKWORK:
		{
			trShowImageDialog("icons/Special E Son of Osiris Icon 64", "BOW BEFORE YEEBAAGOOON!");
			trSoundPlayFN("soopattack.wav","1",-1,"","");
		}
		case CLASS_EVIL:
		{
			trShowImageDialog("icons/Infantry G Hoplite Icon 64", "Why is Nick taking so long with this map?");
			trSoundPlayFN("mummydie.wav","1",-1,"","");
		}
		case CLASS_SPACE:
		{
			trShowImageDialog("Zenophobia\SFA\Nick", "You made it to the end! Well played!");
			trSoundPlayFN("llamamove2.wav","1",-1,"","");
		}
	}
}

rule MissionEnd1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) >= 3){
		trSetLighting("default", 0.1);
		CleanBoard();
		if(trQuestVarGet("newCards") == 1){
			trQuestVarSet("missionComplete", 1);
			if(trQuestVarGet("missionSelection") < 0){
				xsDisableRule("StoryTutorial1");
				xsDisableRule("StoryTutorial2");
				xsDisableRule("StoryTutorial3");
				xsDisableRule("StoryTutorial4");
				xsDisableRule("StoryTutorial5");
				trQuestVarSet("newCards", 0);
				trQuestVarSet("newCommanderType", kbGetProtoUnitID("Oracle Hero"));
				xsEnableRule("NewCommander0");
				CommanderUnlockLine();
			} else {
				/* Progress Current Story */
				if(trQuestVarGet("missionHardmode") == 0){
					setClassProgress(1*trQuestVarGet("missionClass"), getClassProgress(1*trQuestVarGet("missionClass")) + 1);
					if(getClassProgress(1*trQuestVarGet("missionClass")) > 6){
						trQuestVarSet("newCommanderType", CommanderToProtounit(1+(2*trQuestVarGet("missionClass"))));
						xsEnableRule("NewCommander0");
						CommanderUnlockLine(trQuestVarGet("missionClass"));
					}
				}
				/* Reward Pack Cards */
				trVectorQuestVarSet("packPos", xsVectorSet(105, 0, 1));
				trQuestVarSet("newCardsCount", 2 + trQuestVarGet("missionSelection"));
				trVectorQuestVarSet("packPos", xsVectorSet(trVectorQuestVarGetX("packPos")+(8-trQuestVarGet("newCardsCount")),0,trVectorQuestVarGetZ("packPos")+(8-trQuestVarGet("newCardsCount"))));
				
				xsEnableRule("NewCards0");
				xsEnableRule("CollectionClick");
				for(i=0;<trQuestVarGet("newCardsCount")){
					int reward = 0;
					int legendary = 0;
					trQuestVarSet("packReward" + i, -1);
					/* Extras Rarity */
					for(k=0;<7){
						/* Legendary Rarity */
						for(j=0;<4){
							trQuestVarSetFromRand("reward", 7, 29, true);
							if(trQuestVarGet("reward") != 14 && trQuestVarGet("reward") != 29){
								break;
							}
						}
						
						int maxCopies = 3;
						if(trQuestVarGet("reward") == 14 || trQuestVarGet("reward") == 29){
							maxCopies = 1;
							legendary = 1;
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
						
						reward = trQuestVarGet("reward") + 30 * class;
						
						if((getCardCountDeck(reward) + getCardCountCollection(reward)) < maxCopies){
							setCardCountCollection(reward, getCardCountDeck(reward) + getCardCountCollection(reward) + 1);
							trQuestVarSet("packReward" + i, reward);
							break;
						}
					}
					trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
					trArmyDispatch("1,10","Dwarf",1,trVectorQuestVarGetX("packPos"),0,trVectorQuestVarGetZ("packPos"),315,true);
					trVectorQuestVarSet("packPos", xsVectorSet(trVectorQuestVarGetX("packPos") + 2, 0, trVectorQuestVarGetZ("packPos") + 2));
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("next"), true);
					trUnitChangeProtoUnit("Cinematic Block");
					trSetSelectedScale(0.7, 0.2, 1.0);
					trUnitChangeName("?");
					yAddToDatabase("allUnits", "next");
					yAddUpdateVar("allUnits", "player", 1);
					yAddUpdateVar("allUnits", "pos", i);
					yAddUpdateVar("allUnits", "legendary", legendary);
					yAddUpdateVar("allUnits", "proto", CardToProto(reward));
					yAddUpdateVar("allUnits", "spell", CardToSpell(reward));
					trModifyProtounit(kbGetProtoUnitName(CardToProto(reward)), 1, 1, 9999999999999999999.0);
					trModifyProtounit(kbGetProtoUnitName(CardToProto(reward)), 1, 1, -9999999999999999999.0);
				}
			}
			dataSave();
		}
		xsDisableRule("MissionEnd1");
		xsEnableRule("MissionEnd2");
	}
}

rule MissionEnd2
highFrequency
inactive
{
	if (trQuestVarGet("newCards") == 0 && trQuestVarGet("newCommanderType") == 0){
		trFadeOutAllSounds(0.0);
		trFadeOutMusic(0.0);
		trUIFadeToColor(0,0,0,1000,1000,false);
		xsDisableRule("MissionEnd2");
		if(trQuestVarGet("restartMission") == 1){
			xsEnableRule("MissionBegin");
		} else {
			xsEnableRule("Collection");
		}
	}
}

rule NewCards0
highFrequency
inactive
{
	if (trQuestVarGet("newCommanderType") == 0 && (trTime()-cActivationTime) > 2){
		trCounterAbort("counter");
		trCounterAbort("mana");
		trChatHistoryClear();
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		uiClearSelection();
		xsDisableRule("NewCards0");
		xsEnableRule("NewCards1");
		trFadeOutAllSounds(0.0);
		trFadeOutMusic(0.0);
		MusicLow();
	}
}

rule NewCards1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 2){
		trPaintTerrain(0, 0, 60, 60, 5, 4, false);
		trSetFogAndBlackmap(false, false);
		trUIFadeToColor(0,0,0,500,500,false);
		trCameraCut(vector(85.849754,59.475327,36.041752), vector(0.374977,-0.843302,-0.385012), vector(0.588380,0.537438,-0.604126), vector(-0.716381,0.0,-0.697709));
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		trSoundPlayFN("plentybirth.wav", "1", -1, "","");
		yDatabasePointerDefault("allUnits");
		xsEnableRule("NewCardsEffect_");
		trQuestVarSet("newCardsSelection", -1);
		xsDisableRule("NewCards1");
	}
}

rule NewCardsEffect
highFrequency
inactive
{
	int id = yDatabaseNext("allUnits", true);
	if(kbGetUnitBaseTypeID(id) != kbGetProtoUnitID("Atlantis Wall Connector")){
		trUnitChangeProtoUnit("Atlantis Wall Connector");
		trSetSelectedScale(0.7, 0.2, 1.0);
		if(yGetVar("allUnits","legendary") == 1){
			trSoundPlayFN("xpack\xtaunts\en\009 oooh.mp3", "2", -1, "","");
			trVectorSetUnitPos("temp", "allUnits");
			DeploySober("Gaia Forest effect", "temp");
		}
		trSoundPlayFN("ui\scroll.wav","1",-1,"","");
		xsEnableRule("NewCardsEffect_");
	} else {
		xsEnableRule("NewCardsClick");
	}
	xsDisableRule("NewCardsEffect");
}

rule NewCardsEffect_
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("NewCardsEffect_");
		xsEnableRule("NewCardsEffect");
	}
}

rule NewCardsClick
highFrequency
inactive
{
	if(true){
		for(x=yGetDatabaseCount("allUnits"); >0) {
			yDatabaseNext("allUnits", true);
			if(trUnitIsSelected() && trQuestVarGet("newCardsSelection") != trQuestVarGet("allUnits")){
				trQuestVarSet("newCardsSelection", trQuestVarGet("allUnits"));
				int proto = yGetVar("allUnits","proto");
				int spell = yGetVar("allUnits","spell");
				if(trUnitTypeIsSelected("Atlantis Wall Connector")){
					if (spell == 0) {
						trUnitChangeName("("+1*trQuestVarGet("card_" + proto + "_Cost")+") "+trStringQuestVarGet("card_" + proto + "_Name")+" <"+1*trQuestVarGet("card_" + proto + "_Speed")+">");
						trUnitChangeProtoUnit(kbGetProtoUnitName(proto));
					} else {
						trUnitChangeName("("+1*trQuestVarGet("spell_" + spell + "_Cost")+") "+trStringQuestVarGet("spell_" + spell + "_Name"));
						trUnitChangeProtoUnit("Statue of Lightning");
						trSetSelectedScale(0.75, 0.2 + xsSqrt(trQuestVarGet("spell_" + spell + "_cost")) * 0.4, 0.75);
						trUnitSetAnimationPath(""+1*trQuestVarGet("spell_"+spell+"_animation") + ",0,0,0,0");
					}
					if(trQuestVarGet("packReward" + 1*yGetVar("allUnits","pos")) == -1){
						trDamageUnitPercent(100);
						trMessageSetText("You already have all the copies of this card!", -1);
					}
					if(yGetVar("allUnits","legendary") == 1){
						trCameraShake(1.0, 0.1);
						trSoundPlayFN("meteorbighit.wav","1",-1,"","");
						trVectorSetUnitPos("temp", "allUnits");
						DeploySober("Meteor Impact Ground", "temp");
						trSoundPlayFN("Heaven Games\legendary.wav", "3", -1, "","");
					}
					trQuestVarSet("newCardsCount", trQuestVarGet("newCardsCount") - 1);
					if(trQuestVarGet("newCardsCount") < 1){
						trCounterAddTime("tooltipEnter", -1, -9999999, "(Press ENTER to continue)");
						trPlayerKillAllGodPowers(1);
						trTechGodPower(1, "nidhogg", 1);
						xsEnableRule("NewCardsEnter");
					}
				}
				displayCardDetails(proto, spell);
				break;
			}
		}
	}
}

rule NewCardsEnter
highFrequency
inactive
{
	if (trPlayerUnitCountSpecific(1, "Nidhogg") > 0) {
		if (yFindLatestReverse("nidhoggNext", "Nidhogg", 1) > 0) {
			trUnitDestroy();
			uiClearSelection();
			trCounterAbort("tooltipEnter");
			trPlayerKillAllGodPowers(1);
			trSoundPlayDialog("default", "1", -1, false, " : ", "");
			trQuestVarSet("newCards", 0);
			unitTransform("Gaia Forest effect", "Cinematic Block");
			xsDisableRule("NewCardsClick");
			xsDisableRule("NewCardsEnter");
		} else {
			ThrowError();
		}
	}
}


rule NewCommander0
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 2){
		uiClearSelection();
		trLetterBox(true);
		xsDisableRule("NewCommander0");
		xsEnableRule("NewCommander1");
		trFadeOutAllSounds(0.0);
		trFadeOutMusic(0.0);
		MusicMedium();
	}
}

rule NewCommander1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 2){
		trPaintTerrain(0, 0, 60, 60, 5, 4, false);
		trRenderSky(true, "DefaultSkyBox");
		trSetFogAndBlackmap(false, false);
		trUIFadeToColor(0,0,0,500,500,false);
		trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
		trArmyDispatch("1,10", "Implode Sphere Effect", 1, 107.5, 0.00, 10, 0, true);
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("temp"), true);
		trDamageUnitPercent(100);
		trQuestVarSet("newCommander", trGetNextUnitScenarioNameNumber());
		trQuestVarSet("newCommanderHeading", 0);
		trArmyDispatch("1,10", kbGetProtoUnitName(trQuestVarGet("newCommanderType")), 1, 107.5, 0.00, 10, 0, true);
		trCameraCut(vector(89.639015,9.863803,26.737341), vector(0.713514,-0.328201,-0.619017), vector(0.247909,0.944608,-0.215076), vector(-0.655317,0.0,-0.755354));
		trSoundPlayDialog("default", "1", -1, false, "New Commander Unlocked:" + trStringQuestVarGet("card_" + 1*trQuestVarGet("newCommanderType") + "_Name"), "");
		trSoundPlayFN("arkantosarrive.wav", "1", -1, "","");
		trSoundPlayFN("lightthunder.wav", "1", -1, "","");
		xsDisableRule("NewCommander1");
		xsEnableRule("NewCommanderRotate");
		xsEnableRule("NewCommander2");
	}
}

rule NewCommander2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 6){
		trUIFadeToColor(0,0,0,1000,0,true);
		xsDisableRule("NewCommander2");
		xsEnableRule("NewCommander3");
	}
}

rule NewCommander3
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 1){
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		trLetterBox(false);
		trSetFogAndBlackmap(true, true);
		trUIFadeToColor(0,0,0,1000,0,false);
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("newCommander"), true);
		trUnitDestroy();
		trQuestVarSet("newCommander", 0);
		trQuestVarSet("newCommanderType", 0);
		xsDisableRule("NewCommander3");
	}
}

rule NewCommanderRotate
highFrequency
inactive
{
	if (trQuestVarGet("newCommander") > 0){
		trQuestVarSet("newCommanderTimer", trTimeMS() + 2);
		trQuestVarSet("newCommanderHeading", trQuestVarGet("newCommanderHeading") + 2);
		if(trQuestVarGet("newCommanderHeading") > 360){
			trQuestVarSet("newCommanderHeading", 1);
		}
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("newCommander"), true);
		trUnitSetHeading(trQuestVarGet("newCommanderHeading"));
		xsEnableRule("NewCommanderRotate_");
	}
	xsDisableRule("NewCommanderRotate");
}

rule NewCommanderRotate_
highFrequency
inactive
{
	if(trTimeMS() > trQuestVarGet("newCommanderTimer")){
		xsDisableRule("NewCommanderRotate_");
		xsEnableRule("NewCommanderRotate");
	}
}

rule SelectCommander
highFrequency
inactive
{
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("p2commander"), true);
	if(trUnitIsSelected()){
		trUnitSetHP(mGetVarByQV("p2commander", "health"));
	}
}


rule Story_Cinematic_Play
highFrequency
inactive
{
	trQuestVarSet("cinematicStep", 1 + trQuestVarGet("cinematicStep"));
	int x = trQuestVarGet("cinematicStep");
	trShowImageDialog(trStringQuestVarGet("cinematicImage"+x), trStringQuestVarGet("cinematicText"+x));
	xsDisableSelf();
	trDelayedRuleActivation("Story_Cinematic_Next");
}

rule Story_Cinematic_Next
highFrequency
inactive
{
	if (trQuestVarGet("cinematicStep") < trQuestVarGet("cinematicLength")) {
		trDelayedRuleActivation("Story_Cinematic_Play");
	}
	xsDisableSelf();
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
		trSoundPlayFN("llamamove1.wav","1",-1,"","");
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
		trShowImageDialog("icons/World Berry Bush icon 64", "Not long after starting your journey, a large figure comes running to greet you.");
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
		trSoundPlayFN("xpack\xdialog\en\xgen005.mp3", "2", -1, "","");
		if (trQuestVarGet("missionHardmode") == 1) {
			for (x=6; >0) {
				addCardToDeck(2, "Hero Greek Ajax");
			}
		}
	}
}

rule StoryClass0Mission3
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission3");
		trShowImageDialog("icons/Special C Qilin Icon", "I am the Protector of this forest. How dare you walk into my domain?");
		trSoundPlayFN("qilin_select1.wav","1",-1,"","");
	}
}

rule StoryClass0Mission3_
highFrequency
inactive
{
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("p2commander"), true);
	if (trUnitPercentDamaged() > 50){
		if(PlayerDefeated(1) == false){
			xsDisableRule("StoryClass0Mission3_");
			if(kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet("p2commander"))) == kbGetProtoUnitID("Qilin")){
				trShowImageDialog("icons/Special C Qilin Icon", "Oh right, I uhhh... left the stove on! Please excuse me!");
				trSoundPlayFN("qilin_select2.wav","1",-1,"","");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("p2commander"), true);
				trUnitChangeProtoUnit("Victory Marker");
				trDamageUnitPercent(100);
			}
		}
	}
}

rule StoryClass0Mission4
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass0Mission4");
		trShowImageDialog("icons/Scenario Kemsyt Icon 64", "Ah perfect, something to plunder! We got stuck in this swamp and we were getting bored!");
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
		trShowImageDialog("icons/Special C Qilin Icon", "The stove incident has been resolved. This time let's fight for real!");
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

rule StoryClass1Mission2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass1Mission2");
		trShowImageDialog("icons/Special E Pharaoh Icon 64", "Welcome to the Arcane Tower! I shall be your first challenger, the great Fire Mage!");
		trSoundPlayFN("pha1.wav","1",-1,"","");
	}
}

rule StoryClass1Mission3
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass1Mission3");
		trShowImageDialog("icons/scenario x folstag icons 64", "Yo! Frost Mage here!");
		trSoundPlayFN("mountaingiantattack1.wav","1",-1,"","");
	}
}

rule StoryClass1Mission4
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass1Mission4");
		trShowImageDialog("icons/Animal Boar icon 64", "Hey I have to be somewhere, can we do this challenge thing in the elevator? Thanks.");
		trSoundPlayFN("pigambient.wav","1",-1,"","");
	}
}

rule StoryClass1Mission5
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass1Mission5");
		trShowImageDialog("icons/Special E Setna Icon 64", "Impressive. But you are no match for the Archmage!");
		trSoundPlayFN("setnaattack1.wav","1",-1,"","");
	}
}

rule StoryClass1Mission6
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableRule("StoryClass1Mission6");
		trShowImageDialog("icons/Special G Circe Icon 64", "*You feel a large amount of fear!*");
		trSoundPlayFN("xattackwarning.wav","1",-1,"","");
	}
}
