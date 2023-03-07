int tutorialStep = 0;

rule StoryTutorial
inactive
highFrequency
{
	if (trTime() > trQuestVarGet("cinTime")) {
		int current = tutorialStep;
		trQuestVarSet("cinTime", trTime());
		switch(tutorialStep)
		{
		case 0:
			{
				if (trQuestVarGet("p2done") == 1) {
					trQuestVarSet("p1done", 1);
					trQuestVarSet("cinTime", trTime() + 2);
					tutorialStep = 1;
				}
			}
		case 1:
			{
				uiMessageBox("Welcome to HeavenGames! This tutorial will walk you through the basics.");
				tutorialStep = 2;
			}
		case 2:
			{
				if (trIsGadgetVisible("ingame-messagedialog") == false) {
					uiMessageBox("This unit with the spotlight is your Commander. If your Commander dies, you lose!");
					uiLookAtUnit(1*trQuestVarGet("p1commander"));
					tutorialStep = 3;
				}
			}
		case 3:
			{
				if (trIsGadgetVisible("ingame-messagedialog") == false) {
					trQuestVarSet("cinTime", trTime() + 2);
					tutorialStep = 4;
				}
			}
		case 4:
			{
				uiMessageBox("Let's take a look at what we're up against. Select the flashing unit.");
				trUnitSelectClear();
				trUnitSelectByQV("tutorialBotUnit");
				trUnitHighlight(10.0, true);
				tutorialStep = 5;
			}
		}
	}
}