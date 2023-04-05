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
	trVectorQuestVarSet("dir", trGetUnitVector("start", "end"));
	mSetVar(siphon, "laserDirx", trVectorQuestVarGetX("dir") * 100000);
	mSetVar(siphon, "laserDirz", trVectorQuestVarGetZ("dir") * 100000);
	trUnitSelectClear();
	trUnitSelect(""+siphon);
	trSetUnitOrientation(trVectorQuestVarGet("dir"), xsVectorSet(0,1,0), true);
	return(siphon);
}

void SummonLightningRod(int tile = 0) {
	// make them immune
	mSetVar(summonAtTile(tile, 2, kbGetProtoUnitID("Outpost")), "keywords", Keyword(CONDUCTOR) + Keyword(IMMUNE) + Keyword(STEALTH));
}

void SetupWalls3(string wall = "", string connector = "", float wallScale = 1, float connectorScale = 1) {
	AddToCustomBoard(135, TILE_OCCUPIED, connector, 1, 45, connectorScale);
	AddToCustomBoard(136, TILE_OCCUPIED, wall, 1, 75, wallScale);
	AddToCustomBoard(138, TILE_OCCUPIED, connector, 1, 105, connectorScale);
	AddToCustomBoard(139, TILE_OCCUPIED, wall, 1, 135, wallScale);
	AddToCustomBoard(140, TILE_OCCUPIED, connector, 1, 165, connectorScale);
	AddToCustomBoard(141, TILE_OCCUPIED, wall, 1, 195, wallScale);
	AddToCustomBoard(142, TILE_OCCUPIED, connector, 1, 225, connectorScale);
	AddToCustomBoard(143, TILE_OCCUPIED, wall, 1, 255, wallScale);
	AddToCustomBoard(144, TILE_OCCUPIED, connector, 1, 285, connectorScale);
	AddToCustomBoard(145, TILE_OCCUPIED, wall, 1, 315, wallScale);
	AddToCustomBoard(146, TILE_OCCUPIED, connector, 1, 345, connectorScale);
	AddToCustomBoard(137, TILE_OCCUPIED, wall, 1, 15, wallScale);
}

void SetupWalls5(string wall = "", string connector = "", float wallScale = 1, float connectorScale = 1) {
	AddToCustomBoard(165, TILE_OCCUPIED, connector, 1, 45, connectorScale);

	AddToCustomBoard(166, TILE_OCCUPIED, wall, 1, 75, wallScale);
	AddToCustomBoard(168, TILE_OCCUPIED, connector, 1, 75, connectorScale);
	AddToCustomBoard(170, TILE_OCCUPIED, wall, 1, 75, wallScale);

	AddToCustomBoard(172, TILE_OCCUPIED, connector, 1, 105, connectorScale);

	AddToCustomBoard(173, TILE_OCCUPIED, wall, 1, 135, wallScale);
	AddToCustomBoard(174, TILE_OCCUPIED, connector, 1, 135, connectorScale);
	AddToCustomBoard(175, TILE_OCCUPIED, wall, 1, 135, wallScale);

	AddToCustomBoard(176, TILE_OCCUPIED, connector, 1, 165, connectorScale);

	AddToCustomBoard(177, TILE_OCCUPIED, wall, 1, 195, wallScale);
	AddToCustomBoard(178, TILE_OCCUPIED, connector, 1, 195, connectorScale);
	AddToCustomBoard(179, TILE_OCCUPIED, wall, 1, 195, wallScale);

	AddToCustomBoard(180, TILE_OCCUPIED, connector, 1, 225, connectorScale);

	AddToCustomBoard(181, TILE_OCCUPIED, wall, 1, 255, wallScale);
	AddToCustomBoard(182, TILE_OCCUPIED, connector, 1, 255, connectorScale);
	AddToCustomBoard(183, TILE_OCCUPIED, wall, 1, 255, wallScale);

	AddToCustomBoard(184, TILE_OCCUPIED, connector, 1, 285, connectorScale);

	AddToCustomBoard(185, TILE_OCCUPIED, wall, 1, 315, wallScale);
	AddToCustomBoard(186, TILE_OCCUPIED, connector, 1, 315, connectorScale);
	AddToCustomBoard(187, TILE_OCCUPIED, wall, 1, 315, wallScale);

	AddToCustomBoard(188, TILE_OCCUPIED, connector, 1, 345, connectorScale);

	AddToCustomBoard(171, TILE_OCCUPIED, wall, 1, 15, wallScale);
	AddToCustomBoard(169, TILE_OCCUPIED, connector, 1, 15, connectorScale);
	AddToCustomBoard(167, TILE_OCCUPIED, wall, 1, 15, wallScale);
}

void SetupWalls7(string wall = "", string connector = "", float wallScale = 1, float connectorScale = 1) {
	AddToCustomBoard(219, TILE_OCCUPIED, connector, 1, 45, connectorScale);

	AddToCustomBoard(220, TILE_OCCUPIED, wall, 1, 75, wallScale);
	AddToCustomBoard(222, TILE_OCCUPIED, connector, 1, 75, connectorScale);
	AddToCustomBoard(224, TILE_OCCUPIED, wall, 1, 75, wallScale);
	AddToCustomBoard(226, TILE_OCCUPIED, connector, 1, 75, connectorScale);
	AddToCustomBoard(228, TILE_OCCUPIED, wall, 1, 75, wallScale);

	AddToCustomBoard(230, TILE_OCCUPIED, connector, 1, 105, connectorScale);

	AddToCustomBoard(231, TILE_OCCUPIED, wall, 1, 135, wallScale);
	AddToCustomBoard(232, TILE_OCCUPIED, connector, 1, 135, connectorScale);
	AddToCustomBoard(233, TILE_OCCUPIED, wall, 1, 135, wallScale);
	AddToCustomBoard(234, TILE_OCCUPIED, connector, 1, 135, connectorScale);
	AddToCustomBoard(235, TILE_OCCUPIED, wall, 1, 135, wallScale);

	AddToCustomBoard(236, TILE_OCCUPIED, connector, 1, 165, connectorScale);

	AddToCustomBoard(237, TILE_OCCUPIED, wall, 1, 195, wallScale);
	AddToCustomBoard(238, TILE_OCCUPIED, connector, 1, 195, connectorScale);
	AddToCustomBoard(239, TILE_OCCUPIED, wall, 1, 195, wallScale);
	AddToCustomBoard(240, TILE_OCCUPIED, connector, 1, 195, connectorScale);
	AddToCustomBoard(241, TILE_OCCUPIED, wall, 1, 195, wallScale);

	AddToCustomBoard(242, TILE_OCCUPIED, connector, 1, 225, connectorScale);

	AddToCustomBoard(243, TILE_OCCUPIED, wall, 1, 255, wallScale);
	AddToCustomBoard(244, TILE_OCCUPIED, connector, 1, 255, connectorScale);
	AddToCustomBoard(245, TILE_OCCUPIED, wall, 1, 255, wallScale);
	AddToCustomBoard(246, TILE_OCCUPIED, connector, 1, 255, connectorScale);
	AddToCustomBoard(247, TILE_OCCUPIED, wall, 1, 255, wallScale);

	AddToCustomBoard(248, TILE_OCCUPIED, connector, 1, 285, connectorScale);

	AddToCustomBoard(249, TILE_OCCUPIED, wall, 1, 315, wallScale);
	AddToCustomBoard(250, TILE_OCCUPIED, connector, 1, 315, connectorScale);
	AddToCustomBoard(251, TILE_OCCUPIED, wall, 1, 315, wallScale);
	AddToCustomBoard(252, TILE_OCCUPIED, connector, 1, 315, connectorScale);
	AddToCustomBoard(253, TILE_OCCUPIED, wall, 1, 315, wallScale);

	AddToCustomBoard(254, TILE_OCCUPIED, connector, 1, 345, connectorScale);

	AddToCustomBoard(221, TILE_OCCUPIED, wall, 1, 15, wallScale);
	AddToCustomBoard(223, TILE_OCCUPIED, connector, 1, 15, connectorScale);
	AddToCustomBoard(225, TILE_OCCUPIED, wall, 1, 15, wallScale);
	AddToCustomBoard(227, TILE_OCCUPIED, connector, 1, 15, connectorScale);
	AddToCustomBoard(229, TILE_OCCUPIED, wall, 1, 15, wallScale);
}

void SetupMission(int class = 0, int mission = 0){
	vector pos = vector(0,0,0);
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
			
			AddToCustomBoard(153, TILE_IMPASSABLE, "Crate", 3);
			AddToCustomBoard(163, TILE_IMPASSABLE, "Crate", 3);
			AddToCustomBoard(155, TILE_IMPASSABLE, "Crate", 3);
			AddToCustomBoard(161, TILE_IMPASSABLE, "Crate", 3);
			

			trQuestVarSet("tutorialBotUnit", summonAtTile(132, 2, kbGetProtoUnitID("Automaton SPC")));
			
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
				addCardToDeck(2, "Automaton SPC");
			}

			for(i=10; >0) {
				addCardToDeck(1, "Toxotes");
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
					trQuestVarSet("p2class2", CLASS_ADVENTURER);
				}
				case 2:
				{
					/* Arena */
					InitBot(BOT_PERSONALITY_SUMMON_FIRST);
					trSetCivAndCulture(0, 6, 2); //norse
					trTechSetStatus(0, 127, 4); // stone wall
					trSetLighting("dusk",0.0);
					trPaintTerrain(0, 0, 60, 60, 5, 4, false);
					trQuestVarSet("dimension", 4);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_CITY_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_CITY_TILE);
					AddToCustomBoard(141, TILE_OCCUPIED, "Wall Connector", 1, 105);
					AddToCustomBoard(140, TILE_OCCUPIED, "Wall Connector", 1, 105);

					AddToCustomBoard(138, TILE_OCCUPIED, "Wall Connector", 1, 105);
					AddToCustomBoard(152, TILE_OCCUPIED, "Wall Connector", 1, 105);

					AddToCustomBoard(146, TILE_OCCUPIED, "Wall Connector", 1, 105);
					AddToCustomBoard(137, TILE_OCCUPIED, "Wall Connector", 1, 105);

					SetupWalls5("Wall Long", "Wall Connector");
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Maceman Hero"));
					for(x=0; <6) {
						addCardToDeck(2, "Swordsman");
						addCardToDeck(2, "Lancer Hero");
						addCardToDeck(2, "Trident Soldier Hero");
						addCardToDeck(2, "Raiding Cavalry");
						addCardToDeck(2, "Villager Atlantean");
						addCardToDeck(2, "", SPELL_BACKSTAB);
					}
					for(x=0; < 2) {
						addCardToDeck(2, "Avenger");
						addCardToDeck(2, "", SPELL_PARTY_UP);
					}
					trQuestVarSet("p2class2", CLASS_ADVENTURER);
				}
				case 3:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 1, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_GRASS_50);
					trQuestVarSet("customTerrainEmptyNot", T_FOREST_PINE);
					trQuestVarSet("customTerrainEmptySpecial", T_GREEK_ROAD);
					
					for(i=194; <= 205) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Pine", 3);
					}
					
					for(i=170; <= 177) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Pine", 3);
					}

					for(i=152; <= 155) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Pine", 3);
					}

					for(i=211; <= 218) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Pine", 3);
					}

					for(i=183; <= 188) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Pine", 3);
					}

					for(i=161; <= 164) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Pine", 3);
					}

					for(i=128; <= 137) {
						AddToCustomBoard(i, TILE_EMPTY, "Cinematic Block");
					}
					for(i=0; < 3) {
						AddToCustomBoard(i + 141, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 157, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 179, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 157, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 207, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 147, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 165, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 189, TILE_EMPTY, "Cinematic Block");
					}
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
				case 4:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 11, false);
					trQuestVarSet("dimension", 7);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", 8);
					trQuestVarSet("customTerrainEmptyNot", 90);
					trQuestVarSet("customTerrainEmptySpecial", T_GRASS_50);
					
					AddToCustomBoard(187, TILE_OCCUPIED, "Tamarisk Tree", 1, 0, 1);
					AddToCustomBoard(172, TILE_OCCUPIED, "Tamarisk Tree", 1, 0, 1);
					
					/* Border */
					for(x=256;< 297){
						AddToCustomBoard(x, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					}
					AddToCustomBoard(238, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(205, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(178, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(157, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(142, TILE_IMPASSABLE, "Gaia Forest Tree", 3);

					AddToCustomBoard(182, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(161, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(214, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(133, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(154, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(150, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(190, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(226, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(199, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(154, TILE_IMPASSABLE, "Gaia Forest Tree", 3);

					AddToCustomBoard(227, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(195, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(169, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(149, TILE_IMPASSABLE, "Gaia Forest Tree", 3);
					AddToCustomBoard(135, TILE_IMPASSABLE, "Gaia Forest Tree", 3);

					// blowing leaves
					AddToCustomBoard(158, TILE_EMPTY, "Blowing Leaves", 1, 270);
					AddToCustomBoard(164, TILE_EMPTY, "Blowing Leaves", 1, 270);
					AddToCustomBoard(194, TILE_EMPTY, "Blowing Leaves", 1, 270);
					AddToCustomBoard(174, TILE_EMPTY, "Blowing Leaves", 1, 270);

					for(i=220; <= 254) {
						if (i > 243 || i < 241) {
							AddToCustomBoard(i, TILE_IMPASSABLE, "Gaia Forest Tree", 2);
						}
					}

					/* Opponent */
					trQuestVarSet("p2class2", CLASS_EVIL);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Invisible Target"));
					deployAtTile(0, "Garrison Flag Sky Passage", 219);
					for(x=0;<5){
						addCardToDeck(2, "Wolf");
						addCardToDeck(2, "Ornlu");
						addCardToDeck(2, "Hetairoi");
						addCardToDeck(2, "Peltast");
						addCardToDeck(2, "Hero Greek Theseus");
						addCardToDeck(2, "Dryad");
					}
					for(x=0;<4){
						addCardToDeck(2, "Hero Chinese Immortal");
					}
					addCardToDeck(2, "", SPELL_ELVEN_APOCALYPSE);
					addCardToDeck(2, "", SPELL_ELVEN_APOCALYPSE);

					summonAtTile(143, 2, kbGetProtoUnitID("Audrey Water"));
					summonAtTile(131, 2, kbGetProtoUnitID("Audrey Water"));
					summonAtTile(136, 2, kbGetProtoUnitID("Audrey Water"));
					summonAtTile(186, 2, kbGetProtoUnitID("Flying Medic"));
					summonAtTile(199, 2, kbGetProtoUnitID("Flying Medic"));

					summonAtTile(171, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(215, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(250, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(232, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(226, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(169, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(140, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(175, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(152, 2, kbGetProtoUnitID("Peltast"));
					summonAtTile(165, 2, kbGetProtoUnitID("Hero Chinese Immortal"));
				}
				case 5:
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
					trQuestVarSet("p2class2", CLASS_ADVENTURER);
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
				case 6:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 0, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", TERRAIN_GRASSLAND);
					trSetLighting("dusk", 0.0);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Jason"));
					for(x=0;<3){
						addCardToDeck(2, "Griffon");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Bear");
						addCardToDeck(2, "Golden Lion");
						addCardToDeck(2, "", SPELL_BACKSTAB);
						addCardToDeck(2, "", SPELL_LIBRA);
					}
					for(x=0; < 6) {
						addCardToDeck(2, "Villager Atlantean");
						addCardToDeck(2, "Ornlu");
						addCardToDeck(2, "Lancer");
						addCardToDeck(2, "Promethean Small");
						addCardToDeck(2, "", SPELL_PISCES);
					}

					summonAtTile(192, 2, kbGetProtoUnitID("Regent"));
					summonAtTile(193, 2, kbGetProtoUnitID("Regent"));
					trQuestVarSet("p2class2", CLASS_SPACE);
				}
				
			}
		}
		case CLASS_ARCANE:
		{
			trSetCivAndCulture(0, 10, 3);
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
					for(x=0;<20){
						addCardToDeck(2, "", SPELL_GROUND_STOMP);
						addCardToDeck(2, "", SPELL_MAGIC_MISSILES);
					}
				}
				case 2:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, T_ATLANTIS_TILE, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_CITY_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_ATLANTIS_TILE); // atlantis tile
					trQuestVarSet("customTerrainEmptySpecial", T_OLYMPUS_TILE); // olympus tile

					AddToCustomBoard(148, TILE_OCCUPIED, "Atlantis Wall Connector", 1, 75);
					AddToCustomBoard(150, TILE_OCCUPIED, "Atlantis Wall Long", 1, 75);
					AddToCustomBoard(152, TILE_OCCUPIED, "Atlantis Wall Connector", 1, 105);
					AddToCustomBoard(153, TILE_OCCUPIED, "Atlantis Wall Long", 1, 135);
					AddToCustomBoard(154, TILE_OCCUPIED, "Atlantis Wall Connector", 1, 135);

					AddToCustomBoard(163, TILE_OCCUPIED, "Atlantis Wall Connector", 1, 135);
					AddToCustomBoard(162, TILE_OCCUPIED, "Atlantis Wall Long", 1, 135);
					AddToCustomBoard(161, TILE_OCCUPIED, "Atlantis Wall Connector", 1, 105);
					AddToCustomBoard(160, TILE_OCCUPIED, "Atlantis Wall Long", 1, 75);
					AddToCustomBoard(159, TILE_OCCUPIED, "Atlantis Wall Connector", 1, 75);

					AddToCustomBoard(128, TILE_OCCUPIED, "Columns", 1, 195, 2);
					AddToCustomBoard(141, TILE_OCCUPIED, "Columns", 1, 195, 2);
					AddToCustomBoard(137, TILE_OCCUPIED, "Columns", 1, 195, 2);
					AddToCustomBoard(178, TILE_OCCUPIED, "Columns", 1, 195, 2);
					AddToCustomBoard(169, TILE_OCCUPIED, "Columns", 1, 195, 2);

					AddToCustomBoard(213, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(218, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(203, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(198, TILE_OCCUPIED, "Columns", 1, 45, 2);

					AddToCustomBoard(138, TILE_EMPTY, "Snow Drift Barracks", 1);
					AddToCustomBoard(185, TILE_EMPTY, "Snow Drift Archery", 1);
					AddToCustomBoard(201, TILE_EMPTY, "Snow Drift Stable", 1);
					AddToCustomBoard(151, TILE_EMPTY, "Snow Drift Siege", 1);
					AddToCustomBoard(158, TILE_EMPTY, "Snow Drift Tower", 1, 69);

					SetupWalls7("Atlantis Wall Long", "Atlantis Wall Connector");
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("King Folstag"));
					for(x=0;<6){
						addCardToDeck(2, "Maceman");
						addCardToDeck(2, "Monument");
						addCardToDeck(2, "Javelin Cavalry Hero");
						addCardToDeck(2, "", SPELL_FROST_BREATH);
					}
					for(x=0; < 3) {
						addCardToDeck(2, "", SPELL_RUNE_OF_ICE);
						addCardToDeck(2, "Trident Soldier Hero");
						addCardToDeck(2, "Monument 2");
						addCardToDeck(2, "Monument 3");
					}
					addCardToDeck(2, "Griffon");
					addCardToDeck(2, "Trident Soldier Hero");
					addCardToDeck(2, "", SPELL_CLASS_TIME);
					addCardToDeck(2, "", SPELL_ELECTROSURGE);
				}
				case 3:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, T_ATLANTIS_TILE, false);
					InitBot(BOT_PERSONALITY_LIBRARY);
					
					trTechSetStatus(0, 413, 4); //oreichalkos wall
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_CITY_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_ATLANTIS_TILE);
					trQuestVarSet("customTerrainEmptySpecial", T_ATLANTIS_TILE);

					// bookshelves
					AddToCustomBoard(180, TILE_OCCUPIED, "Wall Connector", 1, 195);
					AddToCustomBoard(179, TILE_OCCUPIED, "Wall Long", 1, 195);
					AddToCustomBoard(178, TILE_OCCUPIED, "Wall Connector", 1, 195);

					AddToCustomBoard(182, TILE_OCCUPIED, "Wall Connector", 1, 195);
					AddToCustomBoard(159, TILE_OCCUPIED, "Wall Long", 1, 195);
					AddToCustomBoard(142, TILE_OCCUPIED, "Wall Connector", 1, 195);

					AddToCustomBoard(184, TILE_OCCUPIED, "Wall Connector", 1, 195);
					AddToCustomBoard(161, TILE_OCCUPIED, "Wall Long", 1, 195);
					AddToCustomBoard(144, TILE_OCCUPIED, "Wall Connector", 1, 195);

					AddToCustomBoard(138, TILE_OCCUPIED, "Wall Connector", 1, 195);
					AddToCustomBoard(152, TILE_OCCUPIED, "Wall Long", 1, 195);
					AddToCustomBoard(172, TILE_OCCUPIED, "Wall Connector", 1, 195);

					AddToCustomBoard(135, TILE_OCCUPIED, "Wall Connector", 1, 195);
					AddToCustomBoard(148, TILE_OCCUPIED, "Wall Long", 1, 195);
					AddToCustomBoard(168, TILE_OCCUPIED, "Wall Connector", 1, 195);

					AddToCustomBoard(169, TILE_OCCUPIED, "Wall Connector", 1, 195);
					AddToCustomBoard(167, TILE_OCCUPIED, "Wall Long", 1, 195);
					AddToCustomBoard(165, TILE_OCCUPIED, "Wall Connector", 1, 195);

					AddToCustomBoard(169, TILE_OCCUPIED, "Wall Connector", 1, 195);
					AddToCustomBoard(167, TILE_OCCUPIED, "Wall Long", 1, 195);
					AddToCustomBoard(165, TILE_OCCUPIED, "Wall Connector", 1, 195);

					AddToCustomBoard(164, TILE_OCCUPIED, "Wall Connector", 1, 75);
					AddToCustomBoard(146, TILE_OCCUPIED, "Wall Long", 1, 75);
					AddToCustomBoard(134, TILE_OCCUPIED, "Wall Connector", 1, 75);

					AddToCustomBoard(131, TILE_OCCUPIED, "Wall Connector", 1, 75);
					AddToCustomBoard(140, TILE_OCCUPIED, "Wall Long", 1, 75);
					AddToCustomBoard(155, TILE_OCCUPIED, "Wall Connector", 1, 75);

					/*
					Serpent Skin
					Bullet Time
					Water Cannon
					Zeno's Paradox
					Time Pocket

					*/

					// pathway
					for(i=0; <3) {
						AddToCustomBoard(i + 130, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 139, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 154, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 175, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 202, TILE_EMPTY, "Cinematic Block", 1);
					}

					for(i=0; <2) {
						AddToCustomBoard(i + 133, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 145, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 163, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 187, TILE_EMPTY, "Cinematic Block", 1);
						AddToCustomBoard(i + 217, TILE_EMPTY, "Cinematic Block", 1);
					}

					AddToCustomBoard(129, TILE_EMPTY, "Cinematic Block", 1);
					AddToCustomBoard(137, TILE_EMPTY, "Cinematic Block", 1);
					AddToCustomBoard(151, TILE_EMPTY, "Cinematic Block", 1);
					AddToCustomBoard(171, TILE_EMPTY, "Cinematic Block", 1);
					AddToCustomBoard(197, TILE_EMPTY, "Cinematic Block", 1);
					AddToCustomBoard(128, TILE_EMPTY, "Cinematic Block", 1);

					SetupWalls7("Atlantis Wall Long", "Atlantis Wall Connector");
					trQuestVarSet("deadeye", summonAtTile(209, 1, kbGetProtoUnitID("Hero Greek Hippolyta")));
					/* Opponent */
					trQuestVarSet("libraryMoonblade", summonAtTile(186, 2, kbGetProtoUnitID("Hero Greek Theseus")));
					trQuestVarSet("libraryNanodude", summonAtTile(163, 2, kbGetProtoUnitID("Oracle Hero")));
					mSetVarByQV("libraryMoonblade", "keywords", Keyword(IMMUNE));
					mSetVarByQV("libraryNanodude", "keywords", Keyword(IMMUNE));

					trQuestVarSet("p1commanderType", COMMANDER_ROGERS);
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Invisible Target"));
					for(x=40; >0) {
						addCardToDeck(2, "", SPELL_SCRAP_METAL);
					}
					yClearDatabase("p1deck");
					for(x=20; >0) {
						addCardToDeck(1, "", SPELL_SING);
						addCardToDeck(1, "", SPELL_SCRAP_METAL);
					}
					/*
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
					*/
				}
				case 4:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, T_ATLANTIS_TILE, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_CITY_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_ATLANTIS_TILE); // atlantis tile
					trQuestVarSet("customTerrainEmptySpecial", T_ATLANTIS_TILE); // olympus tile

					//Left Column Row
					AddToCustomBoard(188, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(186, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(184, TILE_OCCUPIED, "Columns", 1, 45, 2);
					//Right Column Row
					AddToCustomBoard(176, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(174, TILE_OCCUPIED, "Columns", 1, 45, 2);
					AddToCustomBoard(172, TILE_OCCUPIED, "Columns", 1, 45, 2);

					// path
					for(i=128; <= 137) {
						AddToCustomBoard(i, TILE_EMPTY, "Cinematic Block");
					}
					for(i=0; < 3) {
						AddToCustomBoard(i + 141, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 157, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 179, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 157, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 207, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 147, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 165, TILE_EMPTY, "Cinematic Block");
						AddToCustomBoard(i + 189, TILE_EMPTY, "Cinematic Block");
					}

					SetupWalls7("Atlantis Wall Long", "Atlantis Wall Connector");
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Circe"));
					trQuestVarSet("p2class2", CLASS_NAGA);
					for(x=0; < 5){
						addCardToDeck(2, "", SPELL_FLUSH);
						addCardToDeck(2, "", SPELL_MIRROR_REFLECTION);
						addCardToDeck(2, "Wadjet");
						addCardToDeck(2, "Maceman");
						addCardToDeck(2, "Hydra");
						addCardToDeck(2, "", SPELL_ELECTROBALL);
					}

					for(x=0; <2) {
						addCardToDeck(2, "Monument");
						addCardToDeck(2, "Monument 2");
						addCardToDeck(2, "Monument 3");
						addCardToDeck(2, "Apep");
						addCardToDeck(2, "Man O War");
					}
				}
				case 5:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 5, 4, false);
					trQuestVarSet("dimension", 2);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_CITY_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_ATLANTIS_TILE);

					trTechSetStatus(0, 412, 4); // iron wall

					SetupWalls3("Gate", "Outpost");

					for(i=147; <= 164) {
						trUnitSelect(""+deployAtTile(0, "Spy Eye", i));
						trMutateSelected(kbGetProtoUnitID("Timeshift In"));
						trUnitSetAnimationPath("0,1,1,0,0,0,0");
					}
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Chimera"));
					trQuestVarSet("p2class2", CLASS_ADVENTURER);
					for(x=0;<4){
						addCardToDeck(2, "", SPELL_GROUND_STOMP);
						addCardToDeck(2, "Griffon");
						addCardToDeck(2, "Oracle Scout");
						addCardToDeck(2, "", SPELL_HORROR_MENAGERIE);
					}
					for(x=0; < 6) {
						addCardToDeck(2, "", SPELL_INTIMIDATE);
						addCardToDeck(2, "Prisoner");
						addCardToDeck(2, "", SPELL_CLASS_TIME);
						addCardToDeck(2, "", SPELL_PYROBALL);
					}
				}
				case 6:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, 50, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_OLYMPUS_TILE);
					trQuestVarSet("customTerrainEmptyNot", T_ATLANTIS_TILE);
					trQuestVarSet("customTerrainEmptySpecial", 51);

					trTechSetStatus(0, 412, 4); // iron wall
					SetupWalls7("Gate", "Outpost");
					/* Border */
					for(x=255;<297){
						AddToCustomBoard(x, TILE_OCCUPIED, "Mist", 1, 0, 1);
					}
					/* nottud's shit */
					AddToCustomBoard(137, TILE_OCCUPIED, "Great Box", 1, 99, 1);
					AddToCustomBoard(153, TILE_OCCUPIED, "Animal Attractor", 1, 51);
					AddToCustomBoard(164, TILE_OCCUPIED, "Outpost", 1, 90);
					AddToCustomBoard(161, TILE_OCCUPIED, "Outpost", 1, 90);
					AddToCustomBoard(155, TILE_OCCUPIED, "Outpost", 1, 90);
					AddToCustomBoard(152, TILE_OCCUPIED, "Outpost", 1, 90);

					AddToCustomBoard(177, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(144, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(187, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(215, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(160, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(173, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(204, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(131, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(130, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					AddToCustomBoard(132, TILE_IMPASSABLE, "Broken Siege Weapons", 3);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Minotaur"));
					for(x=0;<3){
						addCardToDeck(2, "Oracle Scout");
						addCardToDeck(2, "Centaur");
						addCardToDeck(2, "Trident Soldier Hero");
						addCardToDeck(2, "Griffon");
						addCardToDeck(2, "Slinger");
						addCardToDeck(2, "Monument");
						addCardToDeck(2, "Monument 2");
						addCardToDeck(2, "Monument 3");
						addCardToDeck(2, "Monument 4");
						addCardToDeck(2, "", SPELL_MIRROR_IMAGE);
						addCardToDeck(2, "", SPELL_MIRROR_REFLECTION);
						addCardToDeck(2, "", SPELL_PYROBALL);
						addCardToDeck(2, "", SPELL_DEATH_DOOR);
						addCardToDeck(2, "", SPELL_FINAL_EXAM);
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
						addCardToDeck(2, "", SPELL_DEVOUR);
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
						addCardToDeck(2, "", SPELL_DEVOUR);
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
						addCardToDeck(2, "", SPELL_NANOMACHINES);
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
					mSetVarByQV("objectiveObelisk", "maxhealth", 10);
					mSetVarByQV("objectiveObelisk", "spell", SPELL_COMMANDER);
					for(x=0; <6) {
						addCardToDeck(2, "Crossbowman");
						addCardToDeck(2, "", SPELL_WARNING_SHOT);
						addCardToDeck(2, "", SPELL_MAGIC_MISSILES);
						addCardToDeck(2, "", SPELL_NANOMACHINES);
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
					trPaintTerrain(0, 0, 60, 60, 5, 4, false); 
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_OLYMPUS_TILE);
					trQuestVarSet("customTerrainEmptyNot", 50);

					trTechSetStatus(0, 132, 4); // citadel wall
					SetupWalls7("Wall Long", "Wall Connector");

					AddToCustomBoard(173, TILE_OCCUPIED, "Wall Connector", 1, 135);
					AddToCustomBoard(174, TILE_OCCUPIED, "Wall Long", 1, 135);
					AddToCustomBoard(175, TILE_OCCUPIED, "Wall Connector", 1, 135);

					AddToCustomBoard(185, TILE_OCCUPIED, "Wall Connector", 1, 135);
					AddToCustomBoard(186, TILE_OCCUPIED, "Wall Long", 1, 135);
					AddToCustomBoard(187, TILE_OCCUPIED, "Wall Connector", 1, 135);

					AddToCustomBoard(144, TILE_OCCUPIED, "Wall Connector", 1, 135);
					AddToCustomBoard(160, TILE_OCCUPIED, "Wall Long", 1, 135);
					AddToCustomBoard(182, TILE_OCCUPIED, "Wall Connector", 1, 135);

					AddToCustomBoard(146, TILE_OCCUPIED, "Wall Connector", 1, 135);
					AddToCustomBoard(151, TILE_OCCUPIED, "Wall Long", 1, 135);
					AddToCustomBoard(169, TILE_OCCUPIED, "Wall Connector", 1, 135);

					AddToCustomBoard(140, TILE_OCCUPIED, "Wall Connector", 1, 135);
					AddToCustomBoard(156, TILE_OCCUPIED, "Wall Long", 1, 135);
					AddToCustomBoard(178, TILE_OCCUPIED, "Wall Connector", 1, 135);

					AddToCustomBoard(138, TILE_OCCUPIED, "Wall Connector", 1, 135);
					AddToCustomBoard(150, TILE_OCCUPIED, "Wall Long", 1, 135);
					AddToCustomBoard(168, TILE_OCCUPIED, "Wall Connector", 1, 135);

					AddToCustomBoard(129, TILE_OCCUPIED, "Wall Connector", 1, 135);
					AddToCustomBoard(128, TILE_OCCUPIED, "Wall Long", 1, 135);
					AddToCustomBoard(132, TILE_OCCUPIED, "Wall Connector", 1, 135);


					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Atalanta"));
					trQuestVarSet("p2class2", CLASS_ADVENTURER);
					for(x=0; < 5){
						addCardToDeck(2, "", SPELL_RIDE_THE_LIGHTNING);
						addCardToDeck(2, "", SPELL_RECHARGE);
						addCardToDeck(2, "", SPELL_BLITZ);
						addCardToDeck(2, "", SPELL_SING);
						addCardToDeck(2, "Javelin Cavalry");
						addCardToDeck(2, "Crossbowman");
					}
					for(x=0; < 3) {
						addCardToDeck(2, "", SPELL_SONG_OF_REST);
						addCardToDeck(2, "", SPELL_GUARDIAN_OF_SEA);
						addCardToDeck(2, "Chieroballista");
					}
					addCardToDeck(2, "", SPELL_BANHAMMER);
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
						addCardToDeck(2, "Monkey");
					}
				}
				case 6:
				{
					InitBot(BOT_PERSONALITY_SUMMON_FIRST);

					trPaintTerrain(0, 0, 60, 60, 5, 4, false); 
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_OLYMPUS_TILE);
					trQuestVarSet("customTerrainEmptyNot", 50);

					trTechSetStatus(0, 132, 4); // citadel wall
					SetupWalls7("Wall Long", "Wall Connector");

					// electric grid of horrors
					SummonLightningRod(128);

					SummonLightningRod(135);
					SummonLightningRod(138);
					SummonLightningRod(140);
					SummonLightningRod(142);
					SummonLightningRod(144);
					SummonLightningRod(146);

					SummonLightningRod(168);
					SummonLightningRod(169);
					for(i=172; <= 188) {
						if (iModulo(2, i) == 0) {
							SummonLightningRod(i);
						}
					}

					trQuestVarSet("p2commanderType", COMMANDER_YEEBAAGOOON);
					for(x=0; < 7) {
						addCardToDeck(2, "Eitri");
					}
					for(x=0;<3) {
						addCardToDeck(2, "", SPELL_SONG_OF_REST);
						addCardToDeck(2, "", SPELL_WARNING_SHOT);
						addCardToDeck(2, "", SPELL_DOMINANCE);
						addCardToDeck(2, "", SPELL_BULLET_STORM);
						addCardToDeck(2, "Javelin Cavalry");
						addCardToDeck(2, "", SPELL_BANHAMMER);
						addCardToDeck(2, "", SPELL_CLASS_TIME);
						addCardToDeck(2, "Crossbowman");
						addCardToDeck(2, "Chieroballista");
						addCardToDeck(2, "Prisoner");
						addCardToDeck(2, "", SPELL_PROFITEERING);
					}
					
					summonAtTile(190, 2, kbGetProtoUnitID("Hero Greek Atalanta"));
					summonAtTile(191, 2, kbGetProtoUnitID("Eitri"));
					trQuestVarSet("p2class2", CLASS_ARCANE);
				}
			}
		}
		case CLASS_EVIL:
		{
			trSetLighting("eclipse", 0);
			trSetCivAndCulture(0, 8, 2);
			switch(mission)
			{
				case 1:
				{
					/* Arena */
					trPaintTerrain(0, 0, 59, 59, 0, T_MARSH_A, false);
					trQuestVarSet("dimension", 5);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_MARSH_A);
					trQuestVarSet("customTerrainEmptyNot", T_FOREST_MARSH);

					// border
					for(i=189; < 219) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Marsh Tree", 3);
					}

					AddToCustomBoard(151, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(136, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(150, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(168, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(133, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(151, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(161, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(185, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(141, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(155, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(157, TILE_IMPASSABLE, "Marsh Tree", 3);
					/* Opponent */
					trQuestVarSet("p1commanderType", kbGetProtoUnitID("Hero Greek Theseus"));
					yClearDatabase("p1deck");
					for(x=0; < 6) {
						addCardToDeck(1, "Wolf");
						addCardToDeck(1, "", SPELL_MOONBEAM);
						addCardToDeck(1, "", SPELL_CRESCENT_STRIKE);
						addCardToDeck(1, "", SPELL_PROTECTION);
					}
					for(x=0; < 3) {
						addCardToDeck(1, "Ornlu");
						addCardToDeck(1, "Peltast");
						addCardToDeck(1, "Hetairoi");
						addCardToDeck(1, "", SPELL_SING);
						addCardToDeck(1, "", SPELL_GUARDIAN_OF_SEA);
					}

					addCardToDeck(1, "Jarl");

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
					trPaintTerrain(0, 0, 59, 59, 0, T_MARSH_A, false);
					trQuestVarSet("dimension", 6);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_MARSH_A);
					trQuestVarSet("customTerrainEmptyNot", T_FOREST_MARSH);
					trQuestVarSet("customTerrainEmptySpecial", 29); // PlainDirt75

					for(i=219; < 255) {
						AddToCustomBoard(i, TILE_IMPASSABLE, "Marsh Tree", 3);
					}

					AddToCustomBoard(157, TILE_OCCUPIED, "Bolder Wall", 1, 15, 0.7);
					AddToCustomBoard(156, TILE_OCCUPIED, "Bolder Wall", 1, 45, 0.7);
					AddToCustomBoard(177, TILE_OCCUPIED, "Bolder Wall", 1, 75, 0.7);
					AddToCustomBoard(178, TILE_EMPTY, "Cinematic Block");
					summonAtTile(178, 1, kbGetProtoUnitID("Onager"));

					AddToCustomBoard(183, TILE_OCCUPIED, "Bolder Wall", 1, 15, 0.7);
					AddToCustomBoard(160, TILE_OCCUPIED, "Bolder Wall", 1, 45, 0.7);
					AddToCustomBoard(159, TILE_OCCUPIED, "Bolder Wall", 1, 75, 0.7);
					AddToCustomBoard(182, TILE_EMPTY, "Cinematic Block");
					summonAtTile(182, 1, kbGetProtoUnitID("Onager"));

					AddToCustomBoard(168, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(128, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(171, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(137, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(189, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(218, TILE_IMPASSABLE, "Marsh Tree", 3);

					AddToCustomBoard(153, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(200, TILE_IMPASSABLE, "Marsh Tree", 3);
					/* Opponent */
					trQuestVarSet("p1commanderType", kbGetProtoUnitID("Hero Greek Hippolyta"));
					yClearDatabase("p1deck");
					for(x=0; < 6) {
						addCardToDeck(1, "Archer Atlantean");
						addCardToDeck(1, "Hypaspist");
					}
					for(x=0; < 3) {
						addCardToDeck(1, "", SPELL_BULLET_STORM);
						addCardToDeck(1, "", SPELL_BULLET_TIME);
						addCardToDeck(1, "Wadjet");
						addCardToDeck(1, "Hippikon");
						addCardToDeck(1, "Petrobolos");
						addCardToDeck(1, "Onager");
						addCardToDeck(1, "Ballista");
						addCardToDeck(1, "", SPELL_SONG_OF_REST);
						addCardToDeck(1, "", SPELL_WARNING_SHOT);
					}
					addCardToDeck(1, "", SPELL_WATER_CANNON);

					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hoplite"));
					summonAtTile(190, 2, kbGetProtoUnitID("Theocrat"));
					summonAtTile(191, 2, kbGetProtoUnitID("Theocrat"));
					for(x=0; < 12) {
						addCardToDeck(2, "Anubite");
					}
					for(x=0;<6){
						addCardToDeck(2, "Tartarian Gate Spawn");
						addCardToDeck(2, "", SPELL_DEATH_DOOR);
					}
					for(x=0;<3){
						addCardToDeck(2, "", SPELL_DEVOUR);
						addCardToDeck(2, "Theocrat");
						addCardToDeck(2, "", SPELL_MIRROR_IMAGE);
						addCardToDeck(2, "Theris");
						addCardToDeck(2, "Tartarian Gate");
					}
					addCardToDeck(2, "Guardian");
					trQuestVarSet("p2class2", CLASS_ARCANE);
				}
				case 4:
				{
					trQuestVarSet("dimension", 6);
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 0, T_MARSH_A, false);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_MARSH_A);
					trQuestVarSet("customTerrainEmptyNot", T_FOREST_MARSH);
					/* Walls */
					for(i=219; < 255) {
						AddToCustomBoard(i, TILE_OCCUPIED, "Marsh Tree", 3);
					}

					AddToCustomBoard(206, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(157, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(182, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(161, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(214, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(187, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(146, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(193, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(196, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(173, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(153, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(201, TILE_IMPASSABLE, "Marsh Tree", 3);
					AddToCustomBoard(142, TILE_IMPASSABLE, "Marsh Tree", 3);
					
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Cinematic Block"));

					summonAtTile(168, 2, kbGetProtoUnitID("Tartarian Gate"));
					summonAtTile(151, 2, kbGetProtoUnitID("Tartarian Gate"));
					summonAtTile(128, 2, kbGetProtoUnitID("Tartarian Gate"));
					
					for(x=0; < 6){
						addCardToDeck(2, "Walking Woods Marsh");
						addCardToDeck(2, "Dryad");
						addCardToDeck(2, "Mummy");
						addCardToDeck(2, "Satyr");
						addCardToDeck(2, "Theris");
						addCardToDeck(2, "Shade of Hades");
					}
					for(x=0; < 20) {
						addCardToDeck(2, "Minion");
					}
					trQuestVarSet("p2class2", CLASS_NAGA);
				}
				case 5:
				{
					trQuestVarSet("dimension", 6);
					trPaintTerrain(0, 0, 60, 60, 0, T_MARSH_A, false);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_MARSH_A);
					trQuestVarSet("customTerrainEmptyNot", T_FOREST_MARSH);

					/* Walls */
					for(i=219; < 255) {
						AddToCustomBoard(i, TILE_OCCUPIED, "Marsh Tree", 3);
					}

					for(i=189; < 219) {
						if (iModulo(3, i) == 0) {
							AddToCustomBoard(i, TILE_IMPASSABLE, "Marsh Tree", 3);
						}
					}

					for(i=165; < 189) {
						if (iModulo(5, i) == 1) {
							AddToCustomBoard(i, TILE_IMPASSABLE, "Marsh Tree", 3);
						}
					}

					AddToCustomBoard(128, TILE_OCCUPIED, "Well of Urd", 1);

					AddToCustomBoard(136, TILE_OCCUPIED, "House", 1, 55);
					AddToCustomBoard(152, TILE_OCCUPIED, "House", 1, 77);
					AddToCustomBoard(154, TILE_OCCUPIED, "House", 1, 99);

					AddToCustomBoard(163, TILE_OCCUPIED, "House", 1, 123);
					AddToCustomBoard(144, TILE_OCCUPIED, "House", 1, 234);
					
					summonAtTile(149, 2, kbGetProtoUnitID("Royal Guard"));
					summonAtTile(148, 2, kbGetProtoUnitID("Royal Guard"));
					
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Setna"));
					for(x=0;<6){
						addCardToDeck(2, "Spearman");
						addCardToDeck(2, "Royal Guard");
						addCardToDeck(2, "Hero Greek Ajax");
					}
					
					for(x=0;<3) {
						addCardToDeck(2, "Einheriar");
						addCardToDeck(2, "Bondi");
						addCardToDeck(2, "Bogsveigir");
						addCardToDeck(2, "Pharaoh");
						addCardToDeck(2, "Mountain Giant");
					}

					for(x=0; < 2) {
						addCardToDeck(2, "", SPELL_PARTY_UP);
						addCardToDeck(2, "Bear");
						addCardToDeck(2, "", SPELL_BLOOD_PRICE);
						addCardToDeck(2, "", SPELL_SPIDER_LAIR);
						addCardToDeck(2, "", SPELL_DEATH_APPROACHES);
					}
					
					trQuestVarSet("p2class2", CLASS_ADVENTURER);
				}
				case 6:
				{
					trQuestVarSet("dimension", 7);
					trPaintTerrain(0, 0, 60, 60, 0, T_MARSH_A, false);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					trQuestVarSet("customTerrainEmpty", T_MARSH_A);
					trQuestVarSet("customTerrainEmptyNot", T_FOREST_MARSH);

					for(i=219; < 255) {
						AddToCustomBoard(i, TILE_OCCUPIED, "Marsh Tree", 3);
					}
					for(i=128; < 219) {
						if (iModulo(5, i) == 1) {
							AddToCustomBoard(i, TILE_OCCUPIED, "Marsh Tree", 3);
						}
					}

					summonAtTile(167, 2, kbGetProtoUnitID("Shade of Hades"));
					summonAtTile(166, 2, kbGetProtoUnitID("Shade of Hades"));
					summonAtTile(128, 2, kbGetProtoUnitID("Tartarian Gate"));
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Achilles"));
					
					for(i=6; >0) {
						addCardToDeck(2, "Bogsveigir");
						addCardToDeck(2, "Argus");
						addCardToDeck(2, "Dryad");
					}
					for(i=3; >0) {
						addCardToDeck(2, "Theris");
						addCardToDeck(2, "Tartarian Gate");
						addCardToDeck(2, "Satyr");
						addCardToDeck(2, "", SPELL_CORPSE_PARTY);
						addCardToDeck(2, "", SPELL_POISON_MIST);
						addCardToDeck(2, "", SPELL_DOOM);
					}
					for(i=2; >0) {
						addCardToDeck(2, "", SPELL_DEVOUR);
						addCardToDeck(2, "", SPELL_POISON_CLOUD);
					}

					trQuestVarSet("p2class2", CLASS_EVIL);
				}
			}
		}
		case CLASS_SPACE:
		{
			switch(mission)
			{
				case 1:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 5, 4, false); // Black
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Odysseus"));
					for(x=0;<10){
						addCardToDeck(2, "Swordsman");
						addCardToDeck(2, "Jarl");
						addCardToDeck(2, "Mountain Giant");
						addCardToDeck(2, "Hero Greek Hippolyta");
					}
				}
				case 2:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 5, 4, false); // Black
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Odysseus"));
					for(x=0;<10){
						addCardToDeck(2, "Prisoner");
						addCardToDeck(2, "Fire Giant");
						addCardToDeck(2, "", SPELL_COPY_HOMEWORK);
						addCardToDeck(2, "Chimera");
						addCardToDeck(2, "Hero Greek Bellerophon");
					}
				}
				case 3:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 5, 4, false); // Black
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Odysseus"));
					for(x=0;<10){
						addCardToDeck(2, "", SPELL_WATER_CANNON);
						addCardToDeck(2, "Kraken");
						addCardToDeck(2, "Hydra");
						addCardToDeck(2, "Scylla");
						addCardToDeck(2, "Sea Turtle");
						addCardToDeck(2, "Leviathan");	
					}
				}
				case 4:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 5, 4, false); // Black
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Odysseus"));
					for(x=0;<10){
						addCardToDeck(2, "", SPELL_REWIND);
						addCardToDeck(2, "", SPELL_SONG_OF_REST);
						addCardToDeck(2, "Automaton SPC");
						addCardToDeck(2, "Ballista");
						addCardToDeck(2, "Battle Boar");
						addCardToDeck(2, "Colossus");
						addCardToDeck(2, "Tower Mirror");
					}
				}
				case 5:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 5, 4, false); // Black
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Odysseus"));
					for(x=0;<80){
						addCardToDeck(2, "Guardian");	
					}
				}
				case 6:
				{
					/* Arena */
					trPaintTerrain(0, 0, 60, 60, 5, 4, false); // Black
					trQuestVarSet("dimension", 8);
					trQuestVarSet("zenoMakeRandomStuffPlease", -1);
					/* Opponent */
					trQuestVarSet("p2commanderType", kbGetProtoUnitID("Hero Greek Odysseus"));
					for(x=0;<10){
						addCardToDeck(2, "", SPELL_REFRESH_MANA);
						addCardToDeck(2, "", SPELL_PETTY_LASER);
						addCardToDeck(2, "", SPELL_NICKS_PORTAL);
						addCardToDeck(1, "", SPELL_SPACE_VENT);
						addCardToDeck(2, "Trireme");
						addCardToDeck(2, "Siege Ship Greek");
						addCardToDeck(2, "Siege Ship Atlantean");
						addCardToDeck(2, "Catapult");
						addCardToDeck(2, "Hero Greek Argo");
					}
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
	for(x=yGetDatabaseCount("allUnits"); >0) {
		yDatabaseNext("allUnits", true);
		mSetVarByQV("allUnits", "played", 0);
		trMutateSelected(kbGetProtoUnitID("Victory Marker"));
		tileGuard(1*mGetVarByQV("allUnits", "tile"), false);
		zSetVarByIndex("tiles", "occupant", 1*mGetVarByQV("allUnits", "tile"), 0);
	}
	yClearDatabase("allUnits");
}

rule Overlay_Mission_name
inactive
highFrequency
{
	if (trTime() > cActivationTime + 1) {
		trOverlayText(collectionMission, 4.7, 500, 200, 1000);
		xsDisableSelf();
	}
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
			xsEnableRule("StoryTutorial");
			/* Starter Deck */
			/*
			for(i = 0;<180){
				setCardCountDeck(i, 0);
				//setCardCountCollection(i, 0);
			}
			for(i = 0;<6){
				setCardCountDeck(i, 3);
				setCardCountDeck(i + 30, 3);
			}
			
			setCardCountDeck(6, 2);
			setCardCountDeck(36, 2);
			*/

			//setCardCountCollection(6, 3);
			
			//setCardCountCollection(36, 3);
			setClassProgress(CLASS_ADVENTURER, 1);
			setClassProgress(CLASS_ARCANE, 1);
			setClassProgress(CLASS_NAGA, 0);
			setClassProgress(CLASS_CLOCKWORK, 0);
			setClassProgress(CLASS_EVIL, 0);
			setClassProgress(CLASS_SPACE, 0);
			setDeckCommander(0);
		} else {
			trDelayedRuleActivation("Overlay_Mission_name");
			xsEnableRule("StoryClass" + 1*trQuestVarGet("missionClass") + "Mission" + 1*trQuestVarGet("missionSelection"));
			xsEnableRule("SelectCommander"); // disable campaign hero healing
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
		xsDisableSelf();
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


void CommanderUnlockLine(int class = -1, bool first = false){
	if(first){
		switch(class)
		{
			case CLASS_ADVENTURER:
			{
				trShowImageDialog("icons\hero g jason icon 64", "phdorogers4: Well, here we go again!");
				trSoundPlayFN("gha1.wav","1",-1,"","");
			}
			case CLASS_ARCANE:
			{
				trShowImageDialog("icons\infantry x Oracle hero icons 64", "Nanodude: You must be pretty good to finish the tutorial. Mind if I tag along?");
				trSoundPlayFN("ahs4.wav","1",-1,"","");
			}
			case CLASS_NAGA:
			{
				trShowImageDialog("icons\infantry x fanatic hero icons 64", "Out Reach: You look sexy, wanna catch an eel later?");
				trSoundPlayFN("aha2.wav","1",-1,"","");	
			}
			case CLASS_CLOCKWORK:
			{
				trShowImageDialog("icons\scenario arkantos icon 64", "Roxas: I don't even know who you are!");
				trSoundPlayFN("arkantos2attack1.wav","1",-1,"","");	
			}
			case CLASS_EVIL:
			{
				trShowImageDialog("icons\hero g perseus icon 64", "Anraheir: And... ACTION! And some juice please, film making is like super hard and stuff.");
				trSoundPlayFN("gha3.wav","1",-1,"","");		
			}
			case CLASS_SPACE:
			{
				trShowImageDialog("icons\hero g odysseus icon 64", "Nickonhawk: You have recruited all the forumers! Well done!");
				trSoundPlayFN("gha2.wav","1",-1,"","");	
			}
		}
	} else {
		switch(class)
		{
			case CLASS_ADVENTURER:
			{
				trShowImageDialog("icons\cavalry x Lancer hero icons 64", "Venlesh: Sorry you had to come all this way, I was working on LOME. Now what's all this about?");
				trSoundPlayFN("aha1.wav","1",-1,"","");
			}
			case CLASS_ARCANE:
			{
				trShowImageDialog("icons\Special G Minotaur Icon 64", "nottud: Ah! You found me! I'll join you but I won't be using my super powers, that would make things too easy.");
				trSoundPlayFN("minotaurgore.wav","1",-1,"","");
			}
			case CLASS_NAGA:
			{
				trShowImageDialog("icons\archer x arcus hero icons 64", "scragins: It's scragins time!");
				trSoundPlayFN("aha2.wav","1",-1,"","");
			}
			case CLASS_CLOCKWORK:
			{
				trShowImageDialog("icons\Special E Son of Osiris Icon 64", "Yeebaagooon: BOW BEFORE YEEBAAGOOON!");
				trSoundPlayFN("soopattack.wav","1",-1,"","");
			}
			case CLASS_EVIL:
			{
				trShowImageDialog("icons\Infantry G Hoplite Icon 64", "Zenophobia: Why is Nick taking so long with this map?");
				trSoundPlayFN("mummydie.wav","1",-1,"","");
			}
			case CLASS_SPACE:
			{
				trShowImageDialog("Zenophobia\SFA\Nick", "God: Pew-pew!");
				trSoundPlayFN("llamamove2.wav","1",-1,"","");
			}
		}
	}
}

rule MissionEnd1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 5){ // wait for sound to complete before starting the cinematic
		trSetLighting("default", 0.1);
		CleanBoard();
		if(trQuestVarGet("newCards") == 1){
			trQuestVarSet("missionComplete", 1);
			if(trQuestVarGet("missionSelection") < 0){
				trQuestVarSet("newCards", 0);
				/*
				trQuestVarSet("newCommanderType", kbGetProtoUnitID("Oracle Hero"));
				xsEnableRule("NewCommander0");
				CommanderUnlockLine(CLASS_ARCANE, true);

				trDelayedRuleActivation("ClassUnlockMessage_1");
				*/
				trQuestVarSet("class1", CLASS_ADVENTURER);
				trQuestVarSet("class2", CLASS_ARCANE);
				for(i = 0;<6){
					setCardCountDeck(i, 3);
					setCardCountDeck(i + 30, 3);
				}
				setCardCountDeck(6, 2);
				setCardCountDeck(36, 2);
				setClassProgress(CLASS_ADVENTURER, 1);
				setClassProgress(CLASS_ARCANE, 1);

				trQuestVarSet("cinStep", 0);
				trQuestVarSet("newCommanderType", 1);
				xsEnableRule("CinPrologue_end");
			} else {
				/* Progress Current Story */
						
				if(trQuestVarGet("missionHardmode") == 0){
					setClassProgress(1*trQuestVarGet("missionClass"), getClassProgress(1*trQuestVarGet("missionClass")) + 1);
					/*
					if(getClassProgress(1*trQuestVarGet("missionClass")) > 6){
						
						trQuestVarSet("newCommanderType", CommanderToProtounit(1+(2*trQuestVarGet("missionClass"))));
						xsEnableRule("NewCommander0");
						CommanderUnlockLine(trQuestVarGet("missionClass"));

						
						storiesFinished = storiesFinished + 1;
						if(getClassProgress(CLASS_NAGA) == 0){
							trQuestVarSet("unlockMore", CLASS_NAGA);
						} else if(storiesFinished > 4 && getClassProgress(CLASS_SPACE) == 0) {
							trQuestVarSet("unlockMore", CLASS_SPACE);
						}
					}
					*/
					if (getClassProgress(1*trQuestVarGet("missionClass")) == 7) {
						trDelayedRuleActivation("UnlockCommander");
						trQuestVarSet("newCommanderType", 1);
					}
				}
				/* Reward Pack Cards */
				trVectorQuestVarSet("packPos", xsVectorSet(105, 0, 1));
				trQuestVarSet("newCardsCount", 2 + trQuestVarGet("missionSelection"));
				trVectorQuestVarSet("packPos", xsVectorSet(trVectorQuestVarGetX("packPos")+(8-trQuestVarGet("newCardsCount")),0,trVectorQuestVarGetZ("packPos")+(8-trQuestVarGet("newCardsCount"))));
				
				xsEnableRule("NewCards0");
				// populate the array with unlocked classes
				int unlocked = zNewArray(mInt, 6);
				int unlockedCount = 0;
				for(i=0; <6) {
					if (getClassProgress(i) > 0) {
						aiPlanSetUserVariableInt(ARRAYS, unlocked, unlockedCount, i);
						unlockedCount = unlockedCount + 1;
					}
				}

				unlockedCount = unlockedCount - 1;

				for(i=0;<trQuestVarGet("newCardsCount")){
					int reward = 0;
					int legendary = 0;
					trQuestVarSet("packReward" + i, -1);
					/* Extras Rarity */
					for(k=0;<9){
						legendary = 0;
						trQuestVarSetFromRand("reward", 7, 29, true);
						/* Legendary Rarity */
						if((1*trQuestVarGet("reward") == 14) || (1*trQuestVarGet("reward") == 29)){
							trQuestVarSetFromRand("rand", 1, 2);
							if (trQuestVarGet("rand") == 1) {
								trQuestVarSetFromRand("reward", 7, 29, true);
							}
						}
						
						int maxCopies = 3;
						if((1*trQuestVarGet("reward") == 14) || (1*trQuestVarGet("reward") == 29)){
							maxCopies = 1;
							legendary = 1;
						}
						
						int class = trQuestVarGet("missionClass");
						
						if(trQuestVarGet("missionHardmode") > 0){
							trQuestVarSetFromRand("temp", 0, unlockedCount, true);
							class = aiPlanGetUserVariableInt(ARRAYS, unlocked, 1*trQuestVarGet("temp"));
						}
						
						reward = 1*trQuestVarGet("reward") + 30 * class;
						
						if((getCardCountDeck(reward) + getCardCountCollection(reward)) < maxCopies){
							//setCardCountCollection(reward, getCardCountDeck(reward) + getCardCountCollection(reward) + 1);
							getNewCard(reward);
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
				}
			}
			saveDeckAndProgress();
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
			/* restart */
			saveDeckAndProgress();
			saveCollection();
			/*
			subModeEnter("Simulation", "Editor");
			uiMessageBox("moo","restartCurrentGame()");
			uiCycleCurrentActivate();
			subModeLeave("Simulation", "Editor");
			modeEnter("pregame");
			modeEnter("Simulation");
			*/
		}
	}
}

rule UnlockCommander
highFrequency
inactive
{
	// wait until cinematic is done
	if ((trQuestVarGet("cinematicStep") == trQuestVarGet("cinematicEnd")) && (trTime() > cActivationTime)) {
		trQuestVarSet("newCommanderType", 0);
		// TODO: make this flashy
		trShowImageDialog("HeavenGames\class"+1*trQuestVarGet("missionClass")+"unlock2", "New Commander unlocked!");
		trSoundPlayFN("ui\thunder"+1*trQuestVarGet("missionClass")+".wav");
		trSoundPlayFN("herocreation.wav");
		xsDisableSelf();
	}
}

rule NewCards0
highFrequency
inactive
{
	if (trQuestVarGet("newCommanderType") == 0 && (trTime()-cActivationTime) > 1){
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
		trUIFadeToColor(0,0,0,100,100,false);
		trCameraCut(vector(85.849754,59.475327,36.041752), vector(0.374977,-0.843302,-0.385012), vector(0.588380,0.537438,-0.604126), vector(-0.716381,0.0,-0.697709));
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		trSoundPlayFN("plentybirth.wav", "1", -1, "","");
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
		trQuestVarSet("timermstimer", trTimeMS() + 200);
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
	if (trTimeMS() > trQuestVarGet("timermstimer")){
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
						trUnitChangeName(trStringQuestVarGet("card_" + proto + "_Name"));
						trUnitChangeProtoUnit(kbGetProtoUnitName(proto));
					} else {
						trUnitChangeName(trStringQuestVarGet("spell_" + spell + "_Name"));
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
						trTechGodPower(1, "rain", 1);
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
	if (trCheckGPActive("rain", 1)) {
		trUnitDestroy();
		uiClearSelection();
		trCounterAbort("tooltipEnter");
		trPlayerKillAllGodPowers(1);
		trSoundPlayDialog("default", "1", -1, false, " : ", "");
		trQuestVarSet("newCards", 0);
		unitTransform("Gaia Forest effect", "Cinematic Block");
		xsDisableRule("NewCardsClick");
		xsDisableRule("NewCardsEnter");
	}
}

/*
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
		trSoundPlayDialog("default", "1", -1, false, "Commander Unlocked:" + trStringQuestVarGet("card_" + 1*trQuestVarGet("newCommanderType") + "_Name"), "");
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
*/
void UnlockClass(int class = 0){
	CommanderUnlockLine(class, true);
	trDelayedRuleActivation("ClassUnlockMessage_" + class);
	setClassProgress(class, 1);
	saveDeckAndProgress();
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
		xsDisableRule("NewCommander3");		
		if(1*trQuestVarGet("unlockMore") == 0){
			trQuestVarSet("newCommander", 0);
			trQuestVarSet("newCommanderType", 0);			
		} else if(1*trQuestVarGet("unlockMore") == CLASS_NAGA) {
			xsEnableRule("NewCommander0");
			trQuestVarSet("newCommanderType", kbGetProtoUnitID("Royal Guard Hero"));	
			UnlockClass(CLASS_NAGA);
			trQuestVarSet("unlockMore", CLASS_CLOCKWORK);			
		} else if(1*trQuestVarGet("unlockMore") == CLASS_CLOCKWORK) {
			xsEnableRule("NewCommander0");
			trQuestVarSet("newCommanderType", kbGetProtoUnitID("Arkantos God"));	
			UnlockClass(CLASS_CLOCKWORK);
			trQuestVarSet("unlockMore", CLASS_EVIL);
		} else if(1*trQuestVarGet("unlockMore") == CLASS_EVIL) {
			xsEnableRule("NewCommander0");
			trQuestVarSet("newCommanderType", kbGetProtoUnitID("Hero Greek Perseus"));
			UnlockClass(CLASS_EVIL);
			trQuestVarSet("unlockMore", 0);
		} else if(1*trQuestVarGet("unlockMore") == CLASS_SPACE) {
			xsEnableRule("NewCommander0");
			trQuestVarSet("newCommanderType", kbGetProtoUnitID("Hero Greek Odysseus"));	
			UnlockClass(CLASS_SPACE);
			trQuestVarSet("unlockMore", 0);
		}
	}
}

rule NewCommanderRotate
highFrequency
inactive
{
	if (trQuestVarGet("newCommander") > 0){
		float diff = trTimeMS() - trQuestVarGet("timermstimer");
		trQuestVarSet("newCommanderHeading", fModulo(360.0, trQuestVarGet("newCommanderHeading") + diff * 0.15));
		trQuestVarSet("timermstimer", trTimeMS());
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("newCommander"), true);
		trUnitSetHeading(trQuestVarGet("newCommanderHeading"));
	} else {
		xsDisableSelf();
	}
}


rule SelectCommander
highFrequency
inactive
{
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("p2commander"), true);
	xsSetContextPlayer(2);
	float health = kbUnitGetCurrentHitpoints(1*trQuestVarGet("p2commander"));
	xsSetContextPlayer(0);
	trDamageUnit(health - mGetVarByQV("p2commander", "health"));
}

rule StoryClass5Mission1
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\building specialist icons 64", "");
		trSoundPlayFN("visionswoosh.wav", "1", -1, "","");
		mSetVarByQV("p2commander", "health", 20);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Wolf"));
			summonAtTile(223, 2, kbGetProtoUnitID("Wolf"));
		}
	}
}

rule StoryClass5Mission2
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\improvement focus icons 64", "");
		trSoundPlayFN("visionswoosh.wav", "1", -1, "","");
		mSetVarByQV("p2commander", "health", 25);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Phoenix Egg"));
			summonAtTile(223, 2, kbGetProtoUnitID("Phoenix Egg"));
		}
	}
}

rule StoryClass5Mission3
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\improvement poseidons secret icons 64", "");
		trSoundPlayFN("visionswoosh.wav", "1", -1, "","");
		mSetVarByQV("p2commander", "health", 30);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Servant"));
			summonAtTile(223, 2, kbGetProtoUnitID("Servant"));
		}
	}
}

rule StoryClass5Mission4
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\improvement engineers icon 64", "");
		trSoundPlayFN("visionswoosh.wav", "1", -1, "","");
		mSetVarByQV("p2commander", "health", 35);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Eitri"));
			summonAtTile(223, 2, kbGetProtoUnitID("Eitri"));
		}
	}
}

rule StoryClass5Mission5
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\god power ancestors icon 64", "");
		trSoundPlayFN("visionswoosh.wav", "1", -1, "","");
		mSetVarByQV("p2commander", "health", 40);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Guardian"));
			summonAtTile(223, 2, kbGetProtoUnitID("Guardian"));
		}
	}
}

rule StoryClass5Mission6
highFrequency
inactive
{
	if ((trTime()-cActivationTime) > 0){
		xsDisableSelf();
		trShowImageDialog("icons\god power eclipse icon 64", "");
		trSoundPlayFN("visionswoosh.wav", "1", -1, "","");
		mSetVarByQV("p2commander", "health", 45);
		if (trQuestVarGet("missionHardmode") == 1) {
			summonAtTile(222, 2, kbGetProtoUnitID("Minotaur"));
			summonAtTile(223, 2, kbGetProtoUnitID("Hoplite"));
		}
	}
}
