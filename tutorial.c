int tutorialStep = 0;

rule StoryTutorial
inactive
highFrequency
{
	int current = tutorialStep;
	switch(tutorialStep)
	{
	case 0:
		{
			if (trQuestVarGet("p2done") == 1) {
				gadgetUnreal("messageWindow"); // remove the mulligan message
				trQuestVarSet("p1done", 1);
				trQuestVarSet("cinTime", trTime() + 2);
				tutorialStep = 1;
				// move the enemy commander away
				teleportToTile(1*trQuestVarGet("p2commander"), 255, true);
			}
			trQuestVarSet("p1click", 0);
		}
	case 1:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				trQuestVarSet("cinTime", trTime());
				uiMessageBox("Welcome to HeavenGames! This tutorial will walk you through the basics.");
				tutorialStep = 2;
			}
			trQuestVarSet("p1click", 0);
		}
	case 2:
		{
			if (trIsGadgetVisible("ingame-messagedialog") == false) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 3;
			}
			trQuestVarSet("p1click", 0);
		}
	case 3:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				uiMessageBox("This unit with the spotlight is your Commander. If your Commander dies, you lose!");
				uiLookAtUnit(1*trQuestVarGet("p1commander"));
				tutorialStep = 4;
			}
			trQuestVarSet("p1click", 0);
		}
	case 4:
		{
			if (trIsGadgetVisible("ingame-messagedialog") == false) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 5;
			}
			trQuestVarSet("p1click", 0);
		}
	case 5:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				uiMessageBox("Let's take a look at what we're up against. Select the flashing unit.");
				trUnitSelectClear();
				trUnitSelectByQV("tutorialBotUnit");
				trUnitHighlight(10.0, true);
				tutorialStep = 6;
			}
			trQuestVarSet("p1click", 0);
		}
	case 6:
		{
			trUnitSelectClear();
			trUnitSelectByQV("tutorialBotUnit");
			if (trUnitIsSelected()) {
				DialogAdd("This unit's stats are displayed on the left side of your screen.");
				DialogAdd("It has Attack, Health, Speed, and Range.");
				DialogAdd("Below that are the unit's Keywords and special effects.");
				DialogAdd("Now select your Commander.");
				DialogStart();
				tutorialStep = 7;
				trUnitSelectClear();
				trUnitSelectByQV("p1commander");
				trUnitHighlight(100.0, true);
			}
			trQuestVarSet("p1click", 0);
		}
	case 7:
		{
			trUnitSelectClear();
			trUnitSelectByQV("p1commander");
			if (trUnitIsSelected()) {
				trUnitHighlight(0.1, true);
				DialogAdd("The highlighted tiles show where your unit can move.");
				DialogAdd("Right click on the tile next to the enemy unit.");
				DialogStart();
				tutorialStep = 8;
				trQuestVarSet("tutorialHighlight", deployAtTile(0, "Garrison Flag Sky Passage", 142));
			}
		}
	case 8:
		{
			if (trQuestVarGet("gameplayPhase") == GAMEPLAY_WORK) {
				switch(1*trQuestVarGet("p1click"))
				{
				case RIGHT_CLICK:
					{
						trVectorQuestVarSet("p1ClickPos", kbGetBlockPosition("142"));
						trUnitSelectClear();
						trUnitSelectByQV("tutorialHighlight");
						trUnitChangeProtoUnit("Cinematic Block");
						tutorialStep = 9;
					}
				case LEFT_CLICK:
					{
						trQuestVarSet("p1click", 0);
						// lol you have no choice
					}
				}
			}
		}
	case 9:
		{
			if (trQuestVarGet("gameplayPhase") == GAMEPLAY_MOVING) {
				tutorialStep = 10;
			}
		}
	case 10:
		{
			if (trQuestVarGet("gameplayPhase") == GAMEPLAY_WORK) {
				DialogAdd("Good! Now the enemy is within your attack range.");
				DialogAdd("Right click on the enemy unit to attack it.");
				DialogStart();
				tutorialStep = 11;
				trUnitSelectClear();
				trUnitSelectByID(132);
				trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));

				trUnitSelectClear();
				trUnitSelectByQV("tutorialHighlight");
				trUnitChangeProtoUnit("Militia");

				trUnitSelectClear();
				trUnitSelectByQV("tutorialHighlight");
				trImmediateUnitGarrison("132");
				trUnitChangeProtoUnit("Garrison Flag Sky Passage");

				trUnitSelectClear();
				trUnitSelectByID(132);
				trMutateSelected(kbGetProtoUnitID("Victory Marker"));
			}
		}
	case 11:
		{
			switch(1*trQuestVarGet("p1click"))
			{
			case RIGHT_CLICK:
				{
					trVectorQuestVarSet("p1ClickPos", kbGetBlockPosition("132"));
					trUnitSelectClear();
					trUnitSelectByQV("tutorialHighlight");
					trUnitChangeProtoUnit("Cinematic Block");
					tutorialStep = 12;
				}
			case LEFT_CLICK:
				{
					trQuestVarSet("p1click", 0);
					// no deselect for you, you bastard
				}
			}
		}
	case 12:
		{
			if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SELECT) {
				DialogAdd("Notice that the enemy also counterattacked Rogers.");
				DialogAdd("When you initiate an attack, the target will counterattack if you are within its range.");
				DialogAdd("Now that Rogers has moved and attacked, he has no more actions.");
				DialogAdd("Press ENTER to end your turn.");
				DialogStart();
				tutorialStep = 13;
			}
		}
	case 13:
		{
			if (trQuestVarGet("p1mana") == 2) {
				DialogAdd("Now let's learn about summoning units.");
				DialogAdd("Press SPACE to move the camera to your hand.");
				DialogStart();
				tutorialStep = 14;
			}
		}
	case 14:
		{
			if (trQuestVarGet("pressSpace") == 1) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 15;
			}
			trQuestVarSet("p1click", 0);
		}
	case 15:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				DialogAdd("This is your hand. The units with spotlights are the ones that you can afford to play.");
				DialogAdd("All units cost Mana. Your Mana is displayed on the right side of the screen.");
				DialogAdd("Select one of the cards in your hand.");
				DialogStart();
				tutorialStep = 16;
			}
		}
	case 16:
		{
			if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SUMMONING) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 17;
			}
		}
	case 17:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				DialogAdd("The Sharpshooter costs 2 mana to play. You can see its cost next to its name in parenthesis (2).");
				DialogAdd("Press SPACE again to move the camera back to your Commander.");
				DialogStart();
				tutorialStep = 18;
			}
		}
	case 18:
		{
			trQuestVarSet("p1click", 0);
			if (trQuestVarGet("pressSpace") == 1) {
				DialogAdd("The highlighted tiles show the available locations where you can summon units.");
				DialogAdd("Left click on a highlighted tile to summon the unit.");
				DialogStart();
				tutorialStep = 19;
			}
		}
	case 19:
		{
			if (trQuestVarGet("p1mana") == 0) {
				DialogAdd("Good! Notice that the unit you just summoned cannot move or attack this turn.");
				DialogAdd("Units cannot act the turn they are summoned. Next turn, your Sharpshooter will be able to act!");
				DialogAdd("You just spent all your mana this turn, but next turn you will get it back, with more!");
				DialogAdd("Each turn, your maximum mana increases by 1 and it refills to full, so use it or lose it!");
				DialogStart();
				trQuestVarSet("tutorialSharpshooter", trQuestVarGet("summonUnit"));
				tutorialStep = 20;
			}
		}
	case 20:
		{
			if ((xGetDatabaseCount(dDialogs) == 0) && (trIsGadgetVisible("ingame-messagedialog") == false)) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 21;
			}
		}
	case 21:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				DialogAdd("Now let's learn about range! Your Sharpshooter has 2 range, while Gearwalkers only have 1.");
				DialogAdd("If your Sharpshooter attacks outside of the Gearwalkers' range, it won't be counterattacked!");
				DialogAdd("Use your Sharpshooter to defeat the three Gearwalkers over the next three turns!");
				DialogStart();
				trQuestVarSet("maxMana", 0);
				teleportToTile(1*trQuestVarGet("p1commander"), 282, true);

				teleportToTile(1*trQuestVarGet("tutorialSharpshooter"), 142, true);
				mSetVarByQV("tutorialSharpshooter", "action", ACTION_READY);
				trUnitSelectClear();
				trUnitSelectByQV("tutorialSharpshooter");
				trUnitHighlight(999, false);

				summonAtTile(132, 2, kbGetProtoUnitID("Automaton SPC"));
				summonAtTile(130, 2, kbGetProtoUnitID("Automaton SPC"));
				summonAtTile(137, 2, kbGetProtoUnitID("Automaton SPC"));
				InitBot(BOT_PERSONALITY_ATTACK_SHARPSHOOTER);
				tutorialStep = 22;
			}
		}
	case 22:
		{
			trQuestVarSet("p1mana", 0);
			trQuestVarSet("p1drawCards", 0);
			trQuestVarSet("p2drawCards", 0);
			trQuestVarSet("maxMana", 0);
			mSetVarByQV("p1commander", "action", ACTION_DONE);
			if ((mGetVarByQV("tutorialSharpshooter", "action") == ACTION_DONE) && (trIsGadgetVisible("messageWindow") == false) && (trQuestVarGet("activePlayer") == 1)) {
				trMessageSetText("You have no more actions. Press ENTER to end your turn.");
			} else if (trQuestVarGet("activePlayer") == 2) {
				gadgetUnreal("messageWindow");
			}
			if (trQuestVarGet("p1deathCount") == 1) { // you dumbass you killed him
				trQuestVarSet("p1deathCount", 0);
				trSoundPlayFN("cantdothat.wav");
				for(i=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					if (mGetVarByQV("allUnits", "proto") == kbGetProtoUnitID("Automaton SPC")) {
						trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
						mSetVarByQV("allUnits", "played", 0);
						zSetVarByIndex("tiles", "occupant", mGetVarByQV("allUnits", "tile"), 0);
						yRemoveFromDatabase("allUnits");
					}
				}

				trQuestVarSet("tutorialSharpshooter", summonAtTile(142, 1, kbGetProtoUnitID("Toxotes")));
				summonAtTile(132, 2, kbGetProtoUnitID("Automaton SPC"));
				summonAtTile(130, 2, kbGetProtoUnitID("Automaton SPC"));
				summonAtTile(137, 2, kbGetProtoUnitID("Automaton SPC"));

				mSetVarByQV("tutorialSharpshooter", "action", ACTION_READY);
				trUnitSelectClear();
				trUnitSelectByQV("tutorialSharpshooter");
				trUnitHighlight(999, false);

				DialogAdd("Make sure to attack while outside the Gearwalkers' range!");
				DialogAdd("You will also need to reposition to avoid getting attacked on your opponent's turn!");
				DialogAdd("Also keep in mind that your units cannot move after attacking! So move FIRST and then attack!");
				DialogStart();
			} else if (trCountUnitsInArea("128", 2, "Automaton SPC", 36) == 0) {
				gadgetUnreal("messageWindow");
				DialogAdd("Excellent! You've defeated the Gearwalkers with your superior range!");
				DialogStart();
				tutorialStep = 23;
			}
		}
	case 23:
		{
			if ((xGetDatabaseCount(dDialogs) == 0) && (trIsGadgetVisible("ingame-messagedialog") == false)) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 24;
			}
		}
	case 24:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				DialogAdd("Now it's time to learn about the Guard keyword.");
				DialogAdd("Some units have the Guard keyword. This allows them to defend adjacent allies from attacks.");
				DialogAdd("If you attack a unit adjacent to a unit with Guard, the Guard unit will swap with it before the attack hits!");
				DialogAdd("Try to kill the flashing Gearwalker this turn!");
				DialogStart();
				InitBot(BOT_PERSONALITY_TRAINING);

				teleportToTile(1*trQuestVarGet("tutorialSharpshooter"), 141, true);
				teleportToTile(1*trQuestVarGet("p1commander"), 143, true);
				mSetVarByQV("tutorialSharpshooter", "action", ACTION_READY);
				mSetVarByQV("p1commander", "action", ACTION_READY);

				trUnitSelectClear();
				trUnitSelectByQV("tutorialSharpshooter");
				trUnitHighlight(999, false);

				summonAtTile(129, 2, kbGetProtoUnitID("Trident Soldier"));
				trQuestVarSet("gearwalker", summonAtTile(130, 2, kbGetProtoUnitID("Automaton SPC")));
				summonAtTile(134, 2, kbGetProtoUnitID("Dwarf"));

				trUnitSelectClear();
				trUnitSelectByQV("gearwalker");
				trUnitHighlight(999, true);
				tutorialStep = 25;
			}
		}
	case 25:
		{
			trQuestVarSet("maxMana", 0);
			trQuestVarSet("p1drawCards", 0);
			trQuestVarSet("p2drawCards", 0);
			if ((mGetVarByQV("gearwalker", "health") == 0) && (trQuestVarGet("p2deathCount") == 1)) {
				//STUPENDOUS
				DialogAdd("Marvelous! As you can see, Guard is a powerful tool, but there are ways around it!");
				DialogAdd("Guard isn't the only keyword in the game. There are dozens, with special effects!");
				DialogAdd("If you come across an unfamiliar keyword, you can read about it in the objectives!");
				DialogStart();
				for(i=6; <= 26) {
					trObjectiveSetID(i, i);
				}
				tutorialStep = 27;
			} else if (trQuestVarGet("activePlayer") == 2) {
				trSoundPlayFN("cantdothat.wav");
				for(i=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					if (mGetVarByQV("allUnits", "spell") == SPELL_NONE) {
						zSetVarByIndex("tiles", "occupant", mGetVarByQV("allUnits", "tile"), 0);
						trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
						mSetVarByQV("allUnits", "played", 0);
						yRemoveFromDatabase("allUnits");
					}
				}

				trQuestVarSet("tutorialSharpshooter", summonAtTile(141, 1, kbGetProtoUnitID("toxotes")));
				teleportToTile(1*trQuestVarGet("p1commander"), 143, true);
				mSetVarByQV("tutorialSharpshooter", "action", ACTION_READY);
				mSetVarByQV("p1commander", "action", ACTION_READY);
				healUnit(1*trQuestVarGet("p1commander"), 2);

				trUnitSelectClear();
				trUnitSelectByQV("tutorialSharpshooter");
				trUnitHighlight(999, false);

				summonAtTile(129, 2, kbGetProtoUnitID("Trident Soldier"));
				trQuestVarSet("gearwalker", summonAtTile(130, 2, kbGetProtoUnitID("Automaton SPC")));
				summonAtTile(134, 2, kbGetProtoUnitID("Dwarf"));

				trUnitSelectClear();
				trUnitSelectByQV("gearwalker");
				trUnitHighlight(999, true);

				tutorialStep = 26;
			}
		}
	case 26:
		{
			trQuestVarSet("maxMana", 0);
			trQuestVarSet("p1drawCards", 0);
			trQuestVarSet("p2drawCards", 0);
			if (trQuestVarGet("activePlayer") == 1) {
				DialogAdd("When you attack one of its adjacent allies, the Shieldbearer will swap places with it!");
				DialogAdd("Hint: Attack the Iron Scavenger first!");
				DialogStart();
				tutorialStep = 25;
			}
		}
	case 27:
		{
			if ((xGetDatabaseCount(dDialogs) == 0) && (trIsGadgetVisible("ingame-messagedialog") == false)) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 28;
				for(i=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					if (mGetVarByQV("allUnits", "spell") == SPELL_NONE) {
						zSetVarByIndex("tiles", "occupant", mGetVarByQV("allUnits", "tile"), 0);
						trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
						mSetVarByQV("allUnits", "played", 0);
						tileGuard(1*mGetVarByQV("allUnits", "tile"), false);
						yRemoveFromDatabase("allUnits");
					}
				}
			}
		}
	case 28:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				trQuestVarSet("maxMana", 3);
				trSoundPlayFN("siegeselect.wav");
				teleportToTile(1*trQuestVarGet("p1commander"), 128, true);
				DialogAdd("Uh oh! The opponent has a Mechanized Bow with massive range!");
				DialogAdd("We're in trouble if we don't get rid of it fast!");
				DialogStart();

				trQuestVarSet("gearwalker", summonAtTile(147, 2, kbGetProtoUnitID("Ballista")));
				summonAtTile(135, 2, kbGetProtoUnitID("Trident Soldier"));
				trUnitSelectClear();
				trUnitSelectByQV("gearwalker");
				trUnitHighlight(999.0, true);
				tutorialStep = 29;
			}
		}
	case 29:
		{
			if ((xGetDatabaseCount(dDialogs) == 0) && (trIsGadgetVisible("ingame-messagedialog") == false)) {
				trQuestVarSet("p1mana", 3);
				for (i=yGetDatabaseCount("p1hand"); >0) {
					yDatabaseNext("p1hand");
					trVectorSetUnitPos("pos", "p1hand");
					trUnitSelectClear();
					trUnitSelectByID(1*yGetVar("p1hand", "pos"));
					trMutateSelected(kbGetProtoUnitID("Victory Marker"));
					trUnitSelectClear();
					trUnitSelect(""+1*trQuestVarGet("p1hand"), true);
					trMutateSelected(kbGetProtoUnitID("Victory Marker"));
					zSetVarByIndex("p1handPos", "occupied", 1*yGetVar("p1hand", "pos"), 0);
				}
				yClearDatabase("p1hand");
				trQuestVarSet("tutorialSharpshooter", generateCard(1, kbGetProtoUnitID("Peltast")));
				DialogAdd("Fortunately, we have spells and Play effects! Press SPACE to look at your hand.");
				DialogStart();
				tutorialStep = 30;
			}
		}
	case 30:
		{
			if (trQuestVarGet("pressSpace") == 1) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 31;
			}
			trQuestVarSet("p1click", 0);
		}
	case 31:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				DialogAdd("The Elven Ranger is a unit that has a Play effect.");
				DialogAdd("A unit's Play effect occurs when you summon it.");
				DialogAdd("The Elven Ranger's play effect allows you to select a unit and deal 1 damage to it.");
				DialogAdd("Summon the Elven Ranger and destroy the Mechanized Bow!");
				DialogStart();
				tutorialStep = 32;
			}
		}
	case 32:
		{
			if (trQuestVarGet("castDone") == CASTING_IN_PROGRESS) {
				tutorialStep = 33;
			}
		}
	case 33:
		{
			if (trQuestVarGet("castDone") == CASTING_NOTHING) {
				if (mGetVarByQV("gearwalker", "health") > 0) {
					trSoundPlayFN("cantdothat.wav");
					for(i=yGetDatabaseCount("allUnits"); >0) {
						yDatabaseNext("allUnits", true);
						if (trQuestVarGet("allUnits") == trQuestVarGet("tutorialSharpshooter")) {
							zSetVarByIndex("tiles", "occupant", mGetVarByQV("allUnits", "tile"), 0);
							trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
							mSetVarByQV("allUnits", "played", 0);
							tileGuard(1*mGetVarByQV("allUnits", "tile"), false);
							yRemoveFromDatabase("allUnits");
							break;
						}
					}
					tutorialStep = 32;
					trQuestVarSet("p1mana", 3);
					trQuestVarSet("tutorialSharpshooter", generateCard(1, kbGetProtoUnitID("Peltast")));

					DialogAdd("After you summon the Elven Ranger, follow the message instructions to damage the Mechanized Bow!");
					DialogAdd("Your mana has been reset to 3. Try again!");
					DialogStart();
				} else {
					trQuestVarSet("cinTime", trTime());
					tutorialStep = 34;
				}
			}
		}
	case 34:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				DialogAdd("Stupendous! Notice that the Shieldbearer did not defend the Mechanized Bow!");
				DialogAdd("Guard only blocks attacks. Play effects and spells do not count as attacks!");
				DialogStart();
				tutorialStep = 35;
			}
		}
	case 35:
		{
			if ((xGetDatabaseCount(dDialogs) == 0) && (trIsGadgetVisible("ingame-messagedialog") == false)) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 36;
				xsDisableRule("turn_02_end");
			}
		}
	case 36:
		{
			if (trTime() > trQuestVarGet("cinTime") && (trQuestVarGet("gameplayPhase") == GAMEPLAY_SELECT)) {
				DialogAdd("Now it's time for a real duel! There is one last thing to learn about.");
				DialogAdd("The last thing to learn about is the Mulligan.");
				DialogAdd("At the start of a match, you will draw 4 cards from your deck.");
				DialogAdd("However, the cards you draw may not be the most ideal. This is your chance to redraw!");
				DialogAdd("Select cards to mark them for the mulligan.");
				DialogStart();

				for(i=yGetDatabaseCount("allUnits"); >0) {
					yDatabaseNext("allUnits", true);
					zSetVarByIndex("tiles", "occupant", mGetVarByQV("allUnits", "tile"), 0);
					trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
					mSetVarByQV("allUnits", "played", 0);
					tileGuard(1*mGetVarByQV("allUnits", "tile"), false);
				}
				yClearDatabase("allUnits");

				trUnitSelectClear();
				trUnitSelectByQV("p1commander");
				trUnitTeleport(0,0,0);

				yClearDatabase("p1deck");

				trQuestVarSet("class1", CLASS_ADVENTURER);
				trQuestVarSet("class2", CLASS_ARCANE);
				for(j = 0;<6){
					for(i=3; >0) {
						addCardToDeckByIndex(1, i);
						addCardToDeckByIndex(1, i + 30);
					}
				}

				for(i=2; >0) {
					addCardToDeckByIndex(1, 6);
					addCardToDeckByIndex(1, 36);
				}

				trQuestVarSet("p2commanderType", kbGetProtoUnitID("Automaton"));

				xsEnableRule("match_00_start");
				xsDisableRule("gameplay_select_show_keywords");
				xsDisableRule("gameplay_01_select");
				trQuestVarSet("cinTime", trTime());

				tutorialStep = 37;
			}
		}
	case 37:
		{
			if ((trQuestVarGet("p1drawCards") == 0) && (trTime() > trQuestVarGet("cinTime"))) {
				uiLookAtUnit(1*trQuestVarGet("p1block"));
				tutorialStep = 38;
			}
		}
	case 38:
		{
			if (trQuestVarGet("p1click") > 0) {
				trQuestVarSet("cinTime", trTime());
				InitBot(BOT_PERSONALITY_DEFAULT);
				tutorialStep = 39;
			}
		}
	case 39:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				DialogAdd("Notice that the card you selected is no longer highlighted.");
				DialogAdd("When you're finished with your mulligan, any unhighlighted cards will be returned to your deck.");
				DialogAdd("Then you will draw new cards from your deck to replace them.");
				DialogAdd("Press ENTER to end your mulligan and start the battle!");
				DialogStart();
				tutorialStep = 40;
			}
		}
	default:
		{
			xsDisableSelf();
		}
	}
}