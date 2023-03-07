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
			}
		}
	case 1:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				trQuestVarSet("cinTime", trTime());
				uiMessageBox("Welcome to HeavenGames! This tutorial will walk you through the basics.");
				tutorialStep = 2;
			}
		}
	case 2:
		{
			if (trIsGadgetVisible("ingame-messagedialog") == false) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 3;
			}
		}
	case 3:
		{
			if (trTime() > trQuestVarGet("cinTime")) {
				uiMessageBox("This unit with the spotlight is your Commander. If your Commander dies, you lose!");
				uiLookAtUnit(1*trQuestVarGet("p1commander"));
				tutorialStep = 4;
			}
		}
	case 4:
		{
			if (trIsGadgetVisible("ingame-messagedialog") == false) {
				trQuestVarSet("cinTime", trTime());
				tutorialStep = 5;
			}
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
				DialogAdd("Your maximum mana increases by 1 and refills each turn.");
				DialogAdd("Select one of the cards in your hand.");
				DialogStart();
				tutorialStep = 16;
			}
		}
	case 16:
		{
			if (trQuestVarGet("gameplayPhase") == GAMEPLAY_SUMMONING) {
				DialogAdd("The Sharpshooter costs 2 mana to play. You can see its cost next to its name in parenthesis (2).");
				DialogAdd("Press SPACE again to move the camera back to your Commander.");
				DialogStart();
				tutorialStep = 17;
			}
		}
	case 17:
		{
			trQuestVarSet("p1click", 0);
			if (trQuestVarGet("pressSpace") == 1) {
				DialogAdd("The highlighted tiles show the available locations where you can summon units.");
				DialogAdd("Left click on a highlighted tile to summon the unit.");
				DialogStart();
				tutorialStep = 18;
			}
		}
	case 18:
		{
			if (trQuestVarGet("p1mana") == 0) {
				DialogAdd("Good! Notice that the unit you just summoned cannot move or attack this turn.");
				DialogAdd("Units cannot act the turn they are summoned.");
				DialogAdd("Now, utilize what you have learned to defeat the Training Dummy!");
				DialogStart();
				InitBot(BOT_PERSONALITY_DEFAULT);
				tutorialStep = 19;
			}
		}
	default:
		{
			xsDisableSelf();
		}
	}
}