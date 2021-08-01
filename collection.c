void CollectionCard(int index = 0, int x = 0, int z = 0) {
	int count = getCardCountCollection(index);
	count = 3; // Testing
	if(count > 0){
		trArmyDispatch("1,10", "Trident Soldier", 1, x - 2, 0, z, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Card");	
	}
	if(count > 1){
		trArmyDispatch("1,10", "Trident Soldier", 1, x, 0, z, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Card");	
	}
	if(count > 2){
		trArmyDispatch("1,10", "Trident Soldier", 1, x + 2, 0, z, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Card");	
	}
}

rule Collection
highFrequency
inactive
{
	unitTransform("Statue of Automaton Base","Victory Marker");
	trChangeTerrainHeight(0, 0, 60, 60, 0, false);
	trPaintTerrain(0, 0, 60, 60, 5, 4, false); //Black
	int progressAdventurer = getClassProgress(CLASS_ADVENTURER);
	progressAdventurer = 8; // Testing
	int x = 0;
	int z = 0;
	if(progressAdventurer > 0){
		trPaintTerrain(0, 0, 9, 41, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(0, 0, 8, 19, 0, 65, false); // GreekRoadA
		trPaintTerrain(0, 21, 8, 40, 0, 65, false); // GreekRoadA
		// First Commander
		trArmyDispatch("1,10", "Hero Greek Jason", 1, 3, 0, 39, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("phdorogers4 (Commander)");
		if(progressAdventurer > 7){
			// Second Commander
			trArmyDispatch("1,10", "Hero Greek Heracles", 1, 15, 0, 39, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Venlesh (Commander)");
		}
		// Cards
		x = 3; z = 35;
		for(i=0;<27){
			CollectionCard(i,x,z);
			z = z - 4;
			if(i==8){
				x = 9; z = 33;
			}
			if(i==17){
				x = 15; z = 35;
			}
		}
		if(getCardCountCollection(27) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 7, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		if(getCardCountCollection(28) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 11, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		// Missions
		x = 9; z = 87;
		for(i=1;<=progressAdventurer){
			trQuestVarSet("missionAdventurer"+i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Adventurer Mission "+i);
			z = z + 4;
		}
	}
	
	int progressArcane = getClassProgress(CLASS_ARCANE);
	progressArcane = 8; // Testing
	if(progressArcane > 0){
		trPaintTerrain(9, 0, 19, 41, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(10, 0, 18, 19, 5, 2, false); // IceC
		trPaintTerrain(10, 21, 18, 40, 5, 2, false); // IceC
		// First Commander
		trArmyDispatch("1,10", "Oracle Hero", 1, 23, 0, 39, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Nanodude (Commander)");
		if(progressArcane > 7){
			// Second Commander
			trArmyDispatch("1,10", "Minotaur", 1, 35, 0, 39, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("nottud (Commander)");
		}
		// Cards
		x = 23; z = 35;
		for(i=0;<27){
			CollectionCard(i+29,x,z);
			z = z - 4;
			if(i==8){
				x = 29; z = 33;
			}
			if(i==17){
				x = 35; z = 35;
			}
		}
		if(getCardCountCollection(27+29) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 27, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		if(getCardCountCollection(28+29) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 31, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		// Missions
		x = 29; z = 87;
		for(i=1;<8){
			trQuestVarSet("missionArcane"+i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Arcane Mission "+i);
			z = z + 4;
		}
	}
		
	int progressNaga = getClassProgress(CLASS_NAGA);
	progressNaga = 8; // Testing
	if(progressNaga > 0){
		trPaintTerrain(19, 0, 29, 41, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(20, 0, 28, 19, 3, 10, false); // coralB
		trPaintTerrain(20, 21, 28, 40, 3, 10, false); // coralB
		// First Commander
		trArmyDispatch("1,10", "Royal Guard", 1, 43, 0, 39, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Out Reach (Commander)");
		if(progressNaga > 7){
			// Second Commander
			trArmyDispatch("1,10", "Archer Atlantean Hero", 1, 55, 0, 39, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("scragins (Commander)");
		}
		// Cards
		x = 43; z = 35;
		for(i=0;<27){
			CollectionCard(i+29*2,x,z);
			z = z - 4;
			if(i==8){
				x = 49; z = 33;
			}
			if(i==17){
				x = 55; z = 35;
			}
		}
		if(getCardCountCollection(27+29*2) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 47, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		if(getCardCountCollection(28+29*2) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 51, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		// Missions
		x = 49; z = 87;
		for(i=1;<8){
			trQuestVarSet("missionNaga"+i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Naga Mission "+i);
			z = z + 4;
		}
	}
	
	int progressClockwork = getClassProgress(CLASS_CLOCKWORK);
	progressClockwork = 8; // Testing
	if(progressClockwork > 0){
		trPaintTerrain(29, 0, 39, 41, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(30, 0, 38, 19, 0, 71, false); // CityTileAtlantis
		trPaintTerrain(30, 21, 38, 40, 0, 71, false); // CityTileAtlantis
		// First Commander
		trArmyDispatch("1,10", "Hero Greek Polyphemus", 1, 63, 0, 39, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Roxas (Commander)");
		if(progressClockwork > 7){
			// Second Commander
			trArmyDispatch("1,10", "Pharaoh of Osiris", 1, 75, 0, 39, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Yeebaagooon (Commander)");
		}
		// Cards
		x = 63; z = 35;
		for(i=0;<27){
			CollectionCard(i+29*3,x,z);
			z = z - 4;
			if(i==8){
				x = 69; z = 33;
			}
			if(i==17){
				x = 75; z = 35;
			}
		}
		if(getCardCountCollection(27+29*3) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 67, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		if(getCardCountCollection(28+29*3) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 71, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		// Missions
		x = 69; z = 87;
		for(i=1;<8){
			trQuestVarSet("missionClockwork"+i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Clockwork Mission "+i);
			z = z + 4;
		}
	}
	
	int progressEvil = getClassProgress(CLASS_EVIL);
	progressEvil = 8; // Testing
	if(progressEvil > 0){
		trPaintTerrain(39, 0, 49, 41, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(40, 0, 48, 19, 0, 84, false); // Hadesbuildable1
		trPaintTerrain(40, 21, 48, 40, 0, 84, false); // Hadesbuildable1
		// First Commander
		trArmyDispatch("1,10", "Hoplite", 1, 83, 0, 39, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Zenophobia (Commander)");
		if(progressEvil > 7){
			// Second Commander
			trArmyDispatch("1,10", "Hero Greek Perseus", 1, 95, 0, 39, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Aros (Commander)");
		}
		// Cards
		x = 83; z = 35;
		for(i=0;<27){
			CollectionCard(i+29*4,x,z);
			z = z - 4;
			if(i==8){
				x = 89; z = 33;
			}
			if(i==17){
				x = 95; z = 35;
			}
		}
		if(getCardCountCollection(27+29*4) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 87, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		if(getCardCountCollection(28+29*4) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 91, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		// Missions
		x = 89; z = 87;
		for(i=1;<8){
			trQuestVarSet("missionEvil"+i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Evil Mission "+i);
			z = z + 4;
		}
	}
	
	int progressSpace = getClassProgress(CLASS_SPACE);
	progressSpace = 8; // Testing
	if(progressSpace > 0){
		trPaintTerrain(49, 0, 59, 41, 0, 73, false); // CityTileWaterPool
		trPaintTerrain(50, 0, 58, 19, 0, 52, false); // OlympusC
		trPaintTerrain(50, 21, 58, 40, 0, 52, false); // OlympusC
		// First Commander
		trArmyDispatch("1,10", "Hero Greek Odysseus", 1, 103, 0, 39, 180, true);
		trArmySelect("1,10");
		trUnitChangeName("Nickonhawk (Commander)");
		if(progressSpace > 7){
			// Second Commander
			trArmyDispatch("1,10", "Caravan Atlantean", 1, 115, 0, 39, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("God (Commander)");
		}
		// Cards
		x = 103; z = 35;
		for(i=0;<27){
			CollectionCard(i+29*5,x,z);
			z = z - 4;
			if(i==8){
				x = 109; z = 33;
			}
			if(i==17){
				x = 115; z = 35;
			}
		}
		if(getCardCountCollection(27+29*5) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 107, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		if(getCardCountCollection(28+29*5) > -1){
			trArmyDispatch("1,10", "Trident Soldier Hero", 1, 111, 0, 37, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Legendary Card");	
		}
		// Missions
		x = 109; z = 87;
		for(i=1;<8){
			trQuestVarSet("missionSpace"+i, trGetNextUnitScenarioNameNumber());
			trArmyDispatch("1,10", "Dwarf", 1, x, 0, z, 180, true);
			trArmySelect("1,10");
			trUnitChangeName("Space Mission "+i);
			z = z + 4;
		}
	}
    xsDisableRule("Collection");
}