

rule StoryClass1Mission1
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m1_", 1, 3);
		MusicLow();
		mSetVarByQV("p2commander", "attack", 2);
		
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
			summonAtTile(168, 2, kbGetProtoUnitID("Prisoner"));
			summonAtTile(169, 2, kbGetProtoUnitID("Monument"));
		}
		xsEnableRule("StoryClass1Mission1_end");
	}
}

rule StoryClass1Mission1_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c2m1_", 4, 8);
		MusicMedium();
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}

rule StoryClass1Mission2
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();		
		CinematicPlay("HeavenGames\c2m2_", 1, 4);
		MusicLow();
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
			summonAtTile(192, 2, kbGetProtoUnitID("Frost Giant"));
			summonAtTile(193, 2, kbGetProtoUnitID("Frost Giant"));
		}
	}
}

void addMagicBook(int tile = 0) {
	trQuestVarSet("next", deployAtTile(0, "Dwarf",tile));
	trUnitSelectClear();
	trUnitSelectByQV("next");
	trMutateSelected(kbGetProtoUnitID("Curse SFX"));
	yAddToDatabase("magicBooks", "next");
	yAddUpdateVar("magicBooks", "tile", tile);
}

void StoryClass1Mission3Music(int eventID = -1) {
	trDelayedRuleActivation("StoryClass1Mission3_Music");
}

rule StoryClass1Mission3
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		trQuestVarSet("libraryStep", trQuestVarGet("activePlayer"));
		CinematicPlay("HeavenGames\c2m3_", 1, 3);
		MusicMedium();
		xsEnableRule("StoryClass1Mission3_LOS");
		xsEnableRule("StoryClass1Mission3_explain");

		teleportToTile(1*trQuestVarGet("p2commander"), 254, true);
		deployAtTile(0, "Garrison Flag Sky Passage", 218);

		// sparkly books of magic
		if (trQuestVarGet("missionHardmode") == 1) {
			mSetVarByQV("libraryMoonblade", "speed", 3);
			// mSetVarByQV("libraryNanodude", "speed", 3); // this is a bit much
			teleportToTile(1*trQuestVarGet("libraryMoonblade"), 200, true);
		}
		addMagicBook(158);
		addMagicBook(143);
		addMagicBook(173);
		addMagicBook(170);
		addMagicBook(147);
		addMagicBook(128);

		trQuestVarSet("line"+1*trQuestVarGet("libraryMoonblade")+"to"+1*trQuestVarGet("p1commander"), deployAtTile(2, "Victory Marker", 128));
		trQuestVarSet("line"+1*trQuestVarGet("libraryMoonblade")+"to"+1*trQuestVarGet("deadeye"), deployAtTile(2, "Victory Marker", 128));
		trQuestVarSet("line"+1*trQuestVarGet("libraryNanodude")+"to"+1*trQuestVarGet("p1commander"), deployAtTile(2, "Victory Marker", 128));
		trQuestVarSet("line"+1*trQuestVarGet("libraryNanodude")+"to"+1*trQuestVarGet("deadeye"), deployAtTile(2, "Victory Marker", 128));

		trUnitSelectClear();
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryMoonblade")+"to"+1*trQuestVarGet("p1commander"));
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryMoonblade")+"to"+1*trQuestVarGet("deadeye"));
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryNanodude")+"to"+1*trQuestVarGet("p1commander"));
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryNanodude")+"to"+1*trQuestVarGet("deadeye"));
		trSetSelectedScale(0,0,0);
		trMutateSelected(kbGetProtoUnitID("Petosuchus Projectile"));

		trEventSetHandler(EVENT_MUSIC, "StoryClass1Mission3Music");
		trEventFire(EVENT_MUSIC);
	}
}

rule StoryClass1Mission3_explain
highFrequency
inactive
{
	if (trQuestVarGet("p1mana") == 1) {
		xsDisableSelf();
		DialogAdd("Get Rogers to the spotlight without being spotted by Nanodude or the Moonblade!");
		DialogAdd("Line of sight updates during your opponent's turn.");
		DialogAdd("The bookshelves contain useful spells! Pick them up to help your escape!");
		DialogStart();
	}
}

bool LibraryCheckLOS(int from = 0, int to = 0) {
	vector start = kbGetBlockPosition(""+from);
	vector end = kbGetBlockPosition(""+to);
	vector dir = getUnitVector(start, end);
	trUnitSelectClear();
	trUnitSelectByQV("line"+from+"to"+to);
	trUnitTeleport(xsVectorGetX(start), xsVectorGetY(start) - 1.0, xsVectorGetZ(start));
	trSetUnitOrientation(vector(0,0,0) - dir, vector(0,1,0), true);

	int occupant = 0;
	int next = mGetVar(from, "tile");
	float dist = 0;

	dir = dir * 6.0;
	end = start;

	bool hit = false;
	
	for(i=15; >0) {
		end = end + dir;
		dist = dist + 6.0;
		next = getNearestNeighbor(next, end);
		if (zGetVarByIndex("tiles", "terrain", next) == TILE_OCCUPIED) {
			hit = false;
			break;
		} else if (zGetVarByIndex("tiles", "occupant", next) > 0) {
			occupant = zGetVarByIndex("tiles", "occupant", next);
			if ((occupant == trQuestVarGet("deadeye")) || (occupant == trQuestVarGet("p1commander"))) {
				hit = true;
				break;
			} else {
				hit = false;
				break;
			}
		}
	}
	dist = dist * 1.222222;
	trSetSelectedScale(3.0, 0.0, dist);
	if (hit) {
		trUnitHighlight(0.1, false);
	}
	return(hit);
}



rule StoryClass1Mission3_Music
inactive
highFrequency
{
	trMusicPlay("music\interface\gank sneakin'.mp3", "1", 3.0);
	trSoundTimer(8300, EVENT_MUSIC);
	xsDisableSelf();
}

rule StoryClass1Mission3_LOS
inactive
highFrequency
{
	vector pos = vector(0,0,0);
	if (mGetVarByQV("libraryMoonblade", "stunTime") <= 0) {
		LibraryCheckLOS(1*trQuestVarGet("libraryMoonblade"), 1*trQuestVarGet("deadeye"));
		LibraryCheckLOS(1*trQuestVarGet("libraryMoonblade"), 1*trQuestVarGet("p1commander"));
	} else {
		trUnitSelectClear();
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryMoonblade")+"to"+1*trQuestVarGet("p1commander"));
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryMoonblade")+"to"+1*trQuestVarGet("deadeye"));
		trSetSelectedScale(0,0,0);
	}
	if (mGetVarByQV("libraryNanodude", "stunTime") <= 0) {
		LibraryCheckLOS(1*trQuestVarGet("libraryNanodude"), 1*trQuestVarGet("deadeye"));
		LibraryCheckLOS(1*trQuestVarGet("libraryNanodude"), 1*trQuestVarGet("p1commander"));
	} else {
		trUnitSelectClear();
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryNanodude")+"to"+1*trQuestVarGet("p1commander"));
		trUnitSelectByQV("line"+1*trQuestVarGet("libraryNanodude")+"to"+1*trQuestVarGet("deadeye"));
		trSetSelectedScale(0,0,0);
	}
	if (trQuestVarGet("libraryStep") != trQuestVarGet("activePlayer")) {
		trQuestVarSet("libraryStep", trQuestVarGet("activePlayer"));
		bool caught = false;
		// perform LOS checking each time a turn ends.
		if (mGetVarByQV("libraryMoonblade", "stunTime") <= 0) {
			if (LibraryCheckLOS(1*trQuestVarGet("libraryMoonblade"), 1*trQuestVarGet("deadeye"))) {
				CharacterLog(2, "Moonblade", "Oh there you are! Check out this book!");
				caught = true;
			} else if (LibraryCheckLOS(1*trQuestVarGet("libraryMoonblade"), 1*trQuestVarGet("p1commander"))) {
				CharacterLog(2, "Moonblade", "Oh Rogers! Check this out! It's called manga?");
				caught = true;
			}
		}
		if ((mGetVarByQV("libraryNanodude", "stunTime") <= 0) && (caught == false)) {
			if (LibraryCheckLOS(1*trQuestVarGet("libraryNanodude"), 1*trQuestVarGet("deadeye"))) {
				CharacterLog(2, "Nanodude", "Ah, there you are! Come check out this tome!");
				caught = true;
			} else if (LibraryCheckLOS(1*trQuestVarGet("libraryNanodude"), 1*trQuestVarGet("p1commander"))) {
				CharacterLog(2, "Nanodude", "Rogers! You're seriously missing out on a great novel!");
				caught = true;
			}
		}
		if (caught) {
			trSoundPlayFN("attackwarning.wav");
			for(i=yGetDatabaseCount("losPath"); >0) {
				yDatabaseNext("losPath");
				highlightTile(1*trQuestVarGet("losPath"), 9999);
			}
			trQuestVarSet("bossSpell", 1);
			xsEnableRule("StoryClass1Mission3_death");
			xsDisableRule("Bot1");
			xsDisableRule("Bot_00_turn_start");
			xsDisableRule("turn_01_resolve_turn_start");
			xsDisableSelf();
		}
	}
	// funny stuff
	if (trQuestVarGet("librarySpellcast") != trQuestVarGet("castDone")) {
		trQuestVarSet("librarySpellcast", trQuestVarGet("castDone"));
		if (trQuestVarGet("librarySpellcast") == CASTING_DONE) {
			switch(1*trQuestVarGet("currentspell"))
			{
			case SPELL_SERPENT_SKIN:
				{
					if (trQuestVarGet("spellTarget") == trQuestVarGet("libraryMoonblade")) {
						CharacterLog(2, "Moonblade", "Oh god! What's happening to me?");
					} else if (trQuestVarGet("spellTarget") == trQuestVarGet("libraryNanodude")) {
						CharacterLog(2, "Nanodude", "Hissssss~");
					} else if (trQuestVarGet("spellTarget") == trQuestVarGet("deadeye")) {
						CharacterLog(1, "Deadeye", "Why are you using that on me?!");
					}
				}
			case SPELL_WATER_CANNON:
				{
					if (trQuestVarGet("spellTarget") == trQuestVarGet("libraryMoonblade")) {
						CharacterLog(2, "Moonblade", "Wheee!");
					} else if (trQuestVarGet("spellTarget") == trQuestVarGet("libraryNanodude")) {
						CharacterLog(2, "Nanodude", "My bones! Argh!");
					}
				}
			case SPELL_TIME_POCKET:
				{
					pos = kbGetBlockPosition(""+1*trQuestVarGet("spellTarget"));
					if (distanceBetweenVectors(kbGetBlockPosition(""+1*trQuestVarGet("libraryNanodude")), pos) < 81.0) {
						CharacterLog(2, "Nanodude", "To think I'd be caught in such an elementary trap! Curses!");
					}
					if (distanceBetweenVectors(kbGetBlockPosition(""+1*trQuestVarGet("libraryMoonblade")), pos) < 81.0) {
						CharacterLog(2, "Moonblade", "Is it just me or is everyone else moving super fast?");
					}
				}
			case SPELL_ZENOS_PARADOX:
				{
					if (trQuestVarGet("spellTarget2") == trQuestVarGet("libraryMoonblade")) {
						CharacterLog(2, "Moonblade", "Eeep! What was that?!");
					} else if (trQuestVarGet("spellTarget2") == trQuestVarGet("libraryNanodude")) {
						CharacterLog(2, "Nanodude", "Not again!");
					}
				}
			}
		}
	}

	// check books
	if (yGetDatabaseCount("magicBooks") > 0) {
		yDatabaseNext("magicBooks");
		int tile = yGetVar("magicBooks", "tile");
		int occupant = zGetVarByIndex("tiles", "occupant", tile);
		int spell = SPELL_SERPENT_SKIN;
		if (occupant > 0) {
			trUnitSelectClear();
			trUnitSelect(""+occupant);
			if (trUnitIsOwnedBy(1)) {
				trQuestVarSetFromRand("temp", 1, 6, true);
				trQuestVarSetFromRand("rand", 1, 6, true);
				if (trQuestVarGet("rand") < trQuestVarGet("temp")) {
					trQuestVarSet("temp", trQuestVarGet("rand"));
				}
				switch(1*trQuestVarGet("temp"))
				{
				case 1:
					{
						spell = SPELL_SERPENT_SKIN;
						CharacterLog(1, "Deadeye", "We could use this to freeze one of them. They won't see us.");
					}
				case 2:
					{
						spell = SPELL_BULLET_TIME;
						CharacterLog(1, "Deadeye", "If we move fast enough, they can't see us.");
					}
				case 3:
					{
						spell = SPELL_WATER_CANNON;
						CharacterLog(1, "Deadeye", "We could send them flying with this.");
					}
				case 4:
					{
						spell = SPELL_TIME_POCKET;
						CharacterLog(1, "Deadeye", "Looks like we found something useful.");
					}
				case 5:
					{
						spell = SPELL_FORTIFY;
						CharacterLog(1, "Deadeye", "Maybe this can be used to block them off?");
					}
				case 6:
					{
						spell = SPELL_ZENOS_PARADOX;
						CharacterLog(1, "Deadeye", "What is this spell doing here?");
					}
				}
				generateCard(1, kbGetProtoUnitID("Statue of Lightning"), spell);
				trUnitSelectClear();
				trUnitSelectByQV("magicBooks");
				trUnitChangeProtoUnit("Deconstruct Unit");
				trUnitSelectClear();
				trUnitSelectByQV("magicBooks");
				trUnitOverrideAnimation(18, 0, false, true, -1);
				yRemoveFromDatabase("magicBooks");
			}
		}
	}
	
	if (trQuestVarGet("missionComplete") == 1) {
		xsDisableSelf();
	}
}

rule StoryClass1Mission3_death
highFrequency
inactive
{
	if (trTime() > (cActivationTime + 2)) {
		if (trQuestVarGet("p2defeated") == 0) {
			trQuestVarSet("p1defeated", 1);
			xsEnableRule("match_end");
			trQuestVarSet("bossSpell", 0);
		}
		xsDisableSelf();
	}
}

rule StoryClass1Mission4
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m4_", 1, 4);
		MusicHigh();
		xsEnableRule("StoryClass1Mission4_polymorph");
		mSetVarByQV("p2commander", "health", 20);
		mSetVarByQV("p2commander", "maxhealth", 20);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON));
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
			for(i=3; >0) {
				generateCard(2, kbGetProtoUnitID("Statue of Lightning"), SPELL_ELECTROBALL);
			}
			addCardToDeck(2, "", SPELL_DOMINANCE);
			addCardToDeck(2, "", SPELL_DOMINANCE);
			summonAtTile(192, 2, kbGetProtoUnitID("Monument"));
			summonAtTile(193, 2, kbGetProtoUnitID("Monument"));
			shuffleDeck(2);
		}
	}
}

rule StoryClass1Mission4_polymorph
highFrequency
inactive
{
	if (trQuestVarGet("activePlayer") == 2) {
		xsDisableSelf();
		trSoundPlayFN("pigpower.wav");
		trMessageSetText("(0) Polymorph: Transform the opposing Commander into a 1|1 Boar with no abilities.");
		ChatLog(0, "<color={Playercolor(2)}>Opponent</color> cast Polymorph!");
		CharacterLog(2, "Spark Witch", "Oops! I've accidentally made you cute!");
		trUnitSelectClear();
		trUnitSelectByQV("p1commander");
		trMutateSelected(kbGetProtoUnitID("Hero Boar 2"));
		deployAtTile(0, "Curse SFX", mGetVarByQV("p1commander", "tile"));
		mSetVarByQV("p1commander", "keywords", Keyword(BEACON));
		mSetVarByQV("p1commander", "OnAttack", 0);
		mSetVarByQV("p1commander", "attack", 1);
		mSetVarByQV("p1commander", "range", 1);
		mSetVarByQV("p1commander", "health", 1);
		mSetVarByQV("p1commander", "maxhealth", 1);
		mSetVarByQV("p1commander", "proto", kbGetProtoUnitID("Hero Boar 2"));
		mSetStringByQV("p1commander", "ability", "");
	}
}

rule StoryClass1Mission5
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m5_", 1, 4);
		MusicMedium();
		mSetVarByQV("p2commander", "health", 30);
		mSetVarByQV("p2commander", "maxhealth", 30);
		mSetVarByQV("p2commander", "keywords", Keyword(BEACON) + Keyword(WARD));
		generateCard(2, kbGetProtoUnitID("Statue of Lightning"), SPELL_HORROR_MENAGERIE);
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
			for(i=3; >0) {
				addCardToDeck(2, "", SPELL_TAVERN_BRAWL);
				addCardToDeck(2, "", SPELL_AQUARIUS);
				addCardToDeck(2, "", SPELL_HORROR_MENAGERIE);
				addCardToDeck(2, "", SPELL_COPY_HOMEWORK);
			}
			shuffleDeck(2);
		}
	}
}

rule StoryClass1Mission6
highFrequency
inactive
{
	if (trQuestVarGet("p2drawCards") > 0){
		xsDisableSelf();
		CinematicPlay("HeavenGames\c2m6_", 1, 6);
		MusicLow();
		mSetVarByQV("p2commander", "health", 30);
		mSetVarByQV("p2commander", "maxhealth", 30);
		summonAtTile(193, 2, kbGetProtoUnitID("Chimera"));
		summonAtTile(192, 2, kbGetProtoUnitID("Chimera"));
		if (trQuestVarGet("missionHardmode") == 1) {
			trQuestVarSet("p2drawCards", 2 + trQuestVarGet("p2drawCards"));
			for(i=5; >0) {
				addCardToDeck(2, "", SPELL_DOMINANCE);
			}
			addCardToDeck(2, "", SPELL_HORROR_MENAGERIE);
			addCardToDeck(2, "", SPELL_TAVERN_BRAWL);
			shuffleDeck(2);
		}

		xsEnableRule("StoryClass1Mission6_end");
	}
}

rule StoryClass1Mission6_end
highFrequency
inactive
{
	if (trQuestVarGet("missionComplete") == 1) {
		CinematicPlay("HeavenGames\c2m6_", 7, 13);
		MusicMedium();
		xsDisableSelf();
	} else if (PlayerDefeated(1)) {
		xsDisableSelf();
	}
}
