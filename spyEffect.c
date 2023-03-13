int dSpyRequests = 0;
int xSpyRequestProto = 0;
int xSpyRequestAnim = 0;
int xSpyRequestAnimPath = 0;
int xSpyRequestDest = 0;
int xSpyRequestScale = 0;
int spyreset = 0;
int spysearch = 0;

rule init_spy_db
active
highFrequency
{
	dSpyRequests = xInitDatabase("spyRequests");
	xSpyRequestProto = xInitAddInt(dSpyRequests, "proto");
	xSpyRequestAnim = xInitAddInt(dSpyRequests, "anime");
	xSpyRequestAnimPath = xInitAddString(dSpyRequests, "path");
	xSpyRequestDest = xInitAddString(dSpyRequests, "destinationQV");
	xSpyRequestScale = xInitAddVector(dSpyRequests, "scale");
	spysearch = trGetNextUnitScenarioNameNumber();
	xsDisableSelf();
}

/*
Assumes that the target unit is already selected
*/

bool spyReady() {
	return(trQuestVarGet("spyFind") == trQuestVarGet("spyFound"));
}

/*
Casts spy on the currently selected unit. The spy will transform into the specified protounit.
Returns the index of the spy eye in case the user wants to reference it later. The name of the
spy eye will be set in the quest var "spyEye"+x, where x is the integer returned by this function.
*/
void spyEffect(string proto = "", string dest = "unused", vector scale = vector(0,0,0), int anim = -1, string animPath = "0,0,0,0,0,0,0") {
	int newest = xAddDatabaseBlock(dSpyRequests);
	xSetInt(dSpyRequests, xSpyRequestProto, kbGetProtoUnitID(proto), newest);
	xSetInt(dSpyRequests, xSpyRequestAnim, anim, newest);
	xSetString(dSpyRequests, xSpyRequestDest, dest, newest);
	xSetVector(dSpyRequests, xSpyRequestScale, scale, newest);
	xSetString(dSpyRequests, xSpyRequestAnimPath, animPath);
	trTechInvokeGodPower(0, "spy", xsVectorSet(1,1,1), xsVectorSet(1,1,1));
}

rule spy_find
highFrequency
active
{
	if (xGetDatabaseCount(dSpyRequests) > 0) {
		vector scale = vector(0,0,0);
		int id = 0;
		for(i=spysearch; < trGetNextUnitScenarioNameNumber()) {
			id = kbGetBlockID(""+i, true);
			if (kbGetUnitBaseTypeID(id) == kbGetProtoUnitID("Spy Eye")) {
				scale = xGetVector(dSpyRequests, xSpyRequestScale);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trMutateSelected(xGetInt(dSpyRequests, xSpyRequestProto));
				trSetSelectedScale(xsVectorGetX(scale),xsVectorGetY(scale),xsVectorGetZ(scale));
				trUnitSetAnimationPath(xGetString(dSpyRequests, xSpyRequestAnimPath));
				trUnitOverrideAnimation(xGetInt(dSpyRequests, xSpyRequestAnim),0,true,true,-1);
				trQuestVarSet(xGetString(dSpyRequests, xSpyRequestDest), i);
				xFreeDatabaseBlock(dSpyRequests);
				spyreset = 0;
			}
		}
		if (xGetDatabaseCount(dSpyRequests) > 0) {
			spyreset = spyreset + 1;
			if (spyreset >= 10) {
				ChatLog(0, "Spy reset. Failed requests: " + xGetDatabaseCount(dSpyRequests));
				xClearDatabase(dSpyRequests);
				spyreset = 0;
			}
		}
	} else {
		spysearch = trGetNextUnitScenarioNameNumber();
	}
}