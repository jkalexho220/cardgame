/*
These are functions are called to play the storyline
CinematicReset();
CinematicAdd("icons\infantry g hoplite icon 64", "pen island");
CinematicStart();
*/
void CinematicPlay(string cin = "", int start = 0, int end = 0, string m = "") {
	trMusicPlay(m, "1", 0);
	trQuestVarSet("cinematicStep", start);
	trQuestVarSet("cinematicEnd", end);
	trStringQuestVarSet("cinematicImage", cin);
	xsEnableRule("Cinematic_Play");
}

rule Cinematic_Play
highFrequency
inactive
{
	trShowImageDialog(trStringQuestVarGet("cinematicImage") + 1*trQuestVarGet("cinematicStep"), "");
	xsDisableSelf();
	trDelayedRuleActivation("Cinematic_Next");
}

rule Cinematic_Next
highFrequency
inactive
{
	if (trQuestVarGet("cinematicStep") < trQuestVarGet("cinematicEnd")) {
		trQuestVarSet("cinematicStep", 1 + trQuestVarGet("cinematicStep"));
		trDelayedRuleActivation("Cinematic_Play");
	}
	xsDisableSelf();
}

// DIALOG
int dDialogs = 0;
int xDialogMessage = 0;

void DialogAdd(string msg = "") {
	xAddDatabaseBlock(dDialogs, true);
	xSetString(dDialogs, xDialogMessage, msg);
}

void DialogStart() {
	xsEnableRule("Dialog_Play");
}

rule initialize_dialog_db
active
highFrequency
{
	dDialogs = xInitDatabase("dialogs");
	xDialogMessage = xInitAddString(dDialogs, "message");
	xsDisableSelf();
}

rule Dialog_Play
highFrequency
inactive
{
	//trQuestVarSet("cinematicStep", 1 + trQuestVarGet("cinematicStep"));
	//trShowImageDialog(trStringQuestVarGet("cinematicImage") + 1*trQuestVarGet("cinematicStep"));
	if (xGetDatabaseCount(dDialogs) > 0) {
		xDatabaseNext(dDialogs);
		uiMessageBox(xGetString(dDialogs, xDialogMessage));
		xFreeDatabaseBlock(dDialogs);
		trDelayedRuleActivation("Dialog_Next");
	}
	xsDisableSelf();
}

rule Dialog_Next
highFrequency
inactive
{
	if (trIsGadgetVisible("ingame-messagedialog") == false) {
		trDelayedRuleActivation("Dialog_Play");
		xsDisableSelf();
	}
}