bool Multiplayer = false;

const float PI = 3.141592;

bool playerIsPlaying(int p = 0) {
	return(kbIsPlayerHuman(p) == true && kbIsPlayerResigned(p) == false);
}


void trVectorQuestVarSet(string name = "", vector QVv = vector(-1,-1,-1)) {
	if (name == "") return;
	if (trQuestVarGet("vector"+name) == 0) {
		trQuestVarSet("vector"+name, zNewVector(QVv));
	} else {
		zSetVector(1*trQuestVarGet("vector"+name),QVv);
	}
}

vector trVectorQuestVarGet(string name = "") {
	return(zGetVector(1*trQuestVarGet("vector"+name)));
}

float trVectorQuestVarGetX(string name = "") {
	return(xsVectorGetX(trVectorQuestVarGet(name)));
}

float trVectorQuestVarGetY(string name = "") {
	return(xsVectorGetY(trVectorQuestVarGet(name)));
}

float trVectorQuestVarGetZ(string name = "") {
	return(xsVectorGetZ(trVectorQuestVarGet(name)));
}

void trVectorQuestVarEcho(string name = "") {
	if (name == "") return;
	trChatSend(0, ""+name+": "+trVectorQuestVarGet(name));
}


void trStringQuestVarSet(string name = "", string value = "") {
	if (trQuestVarGet("string"+name) > 0) {
		zSetString(1*trQuestVarGet("string"+name), value);
	} else {
		trQuestVarSet("string"+name, zNewString(value));
	}
}

string trStringQuestVarGet(string name="") {
	string val = zGetString(1*trQuestVarGet("string"+name));
	return(val);
}


void trUnitSelectByQV(string s = "", bool reverse = true) {
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet(""+s), reverse);
}


/*
Given a quest var that stores a unit name, store
the unit's position in the vector.
*/
void trVectorSetUnitPos(string v = "", string db = "", bool reverse = true) {
	trVectorQuestVarSet(v, kbGetBlockPosition(""+1*trQuestVarGet(db), reverse));
}

void trVectorSetUnitPosInt(string v = "", int val = 0, bool reverse = true) {
	trVectorQuestVarSet(v, kbGetBlockPosition(""+val, reverse));
}


void trUnitMoveToVector(string v = "", bool attack = false) {
	trUnitMoveToPoint(trVectorQuestVarGetX(v),0,trVectorQuestVarGetZ(v),-1,attack);
}

void trVectorScale(string db = "", float s = 1.0) {
	trVectorQuestVarSet(db, trVectorQuestVarGet(db) * s);
}

vector vectorSnapToGrid(vector v = vector(0,0,0)) {
	int x = xsVectorGetX(v) / 2;
	int z = xsVectorGetZ(v) / 2;
	return(xsVectorSet(x * 2 + 1,xsVectorGetY(v),z * 2 + 1));
}

void trVectorSnapToGrid(string qv = "") {
	trVectorQuestVarSet(qv, vectorSnapToGrid(trVectorQuestVarGet(qv)));
}

int iModulo(int mod = 10, int val = 0) {
	return(val - val / mod * mod);
}

float fModulo(float mod = 0, float val = 0) {
	int c = 0;
	if (val > 0) {
		c = val / mod;
	} else {
		c = val / mod - 1;
	}
	return(0.0 + val - mod * c);
}


void zUnitHeading(float a = 0) {
	trSetUnitOrientation(xsVectorSet(xsSin(a),0,xsCos(a)), xsVectorSet(0,1,0), true);
}

void zInitProtoUnitStat(string r = "", int p = 0, int f = 0, float v = 0.0) {
	trQuestVarSet("p"+p+"pf"+kbGetProtoUnitID(r)+"f"+f, v);
}

void zSetProtoUnitStat(string r = "", int p = 0, int f = 0, float v = 0.0) {
for(zsps=0; >1){}
	zsps = kbGetProtoUnitID(r);
	trModifyProtounit(r, p, f, 0.0 + v - trQuestVarGet("p"+p+"pf"+zsps+"f"+f));
	trQuestVarSet("p"+p+"pf"+zsps+"f"+f, 0.0 + v);
}

vector vectorToGrid(vector v = vector(0,0,0)) {
	return(xsVectorSet(0 + xsVectorGetX(v) / 2,xsVectorGetY(v),0 + xsVectorGetZ(v) / 2));
}

void trVectorToGrid(string from = "", string to = ""){
	trVectorQuestVarSet(to, vectorToGrid(trVectorQuestVarGet(from)));
}

vector gridToVector(vector g = vector(0,0,0)) {
	return(xsVectorSet(xsVectorGetX(g) * 2 + 1,xsVectorGetY(g),xsVectorGetZ(g) * 2 + 1));
}

void trGridToVector(string from = "", string to = "") {
	trVectorQuestVarSet(to, gridToVector(trVectorQuestVarGet(from)));
}

void trSquareVar(string qv = "") {
	trQuestVarSet(qv, xsPow(trQuestVarGet(qv), 2));
}

float distanceBetweenVectors(vector start = vector(0,0,0), vector end = vector(0,0,0), bool squared = true) {
	float xDiff = xsVectorGetX(end) - xsVectorGetX(start);
	float zDiff = xsVectorGetZ(end) - xsVectorGetZ(start);
	float dist = xDiff * xDiff + zDiff * zDiff;
	if (squared == false) {
		dist = xsSqrt(dist);
	}
	return(dist);
}

float trDistanceBetweenVectorsSquared(string start = "", string end = "") {
	return(distanceBetweenVectors(trVectorQuestVarGet(start),trVectorQuestVarGet(end)));
}

bool vectorInRectangle(vector pos = vector(0,0,0), vector bot = vector(0,0,0), vector top = vector(0,0,0)) {
	if (xsVectorGetX(pos) < xsVectorGetX(bot)) {
		return(false);
	}
	if (xsVectorGetX(pos) > xsVectorGetX(top)) {
		return(false);
	}
	if (xsVectorGetZ(pos) < xsVectorGetZ(bot)) {
		return(false);
	}
	if (xsVectorGetZ(pos) > xsVectorGetZ(top)) {
		return(false);
	}
	return(true);
}

bool trVectorInRectangle(string pos = "", string bot = "", string top = "") {
	vector tempPos = zGetVector(1*trQuestVarGet(pos));
	vector tempBot = zGetVector(1*trQuestVarGet(bot));
	vector tempTop = zGetVector(1*trQuestVarGet(top));
	return(vectorInRectangle(tempPos,tempBot,tempTop));
}

vector rotationMatrix(vector v = vector(0,0,0), float cosT = 0, float sinT = 0) {
	float x = xsVectorGetX(v);
	float z = xsVectorGetZ(v);
	vector ret = xsVectorSet(x * cosT - z * sinT, 0, x * sinT + z * cosT);
	return(ret);
}

float trDistanceBetweenVectors(string start = "", string end = "") {
	return(distanceBetweenVectors(trVectorQuestVarGet(start),trVectorQuestVarGet(end),false));
}

float distanceBetweenVectors3d(vector start = vector(0,0,0), vector end = vector(0,0,0), bool squared = true) {
	float xdiff = xsVectorGetX(start) - xsVectorGetX(end);
	float ydiff = xsVectorGetY(start) - xsVectorGetY(end);
	float zdiff = xsVectorGetZ(start) - xsVectorGetZ(end);
	float dist = xdiff * xdiff + ydiff * ydiff + zdiff * zdiff;
	if (squared == false) {
		dist = xsSqrt(dist);
	}
	return(dist);
}

float trDistanceBetweenVectors3d(string start = "", string end = "") {
	return(distanceBetweenVectors3d(trVectorQuestVarGet(start),trVectorQuestVarGet(end),false));
}

float unitDistanceToVector(int name = 0, vector v = vector(0,0,0), bool squared = true) {
	vector temp = kbGetBlockPosition(""+name,true);
	return(distanceBetweenVectors(temp,v,squared));
}

float trDistanceToVectorSquared(string qv = "", string v = "") {
	return(unitDistanceToVector(1*trQuestVarGet(qv),trVectorQuestVarGet(v)));
}

/* For use in a ySearch */
float trDistanceToVector(string qv = "", string v = "") {
	return(unitDistanceToVector(1*trQuestVarGet(qv),trVectorQuestVarGet(v),false));
}

vector vectorSetFromAngle(float angle = 0) {
	return(xsVectorSet(xsSin(angle), 0, xsCos(angle)));
}

void trVectorSetFromAngle(string qv = "", float angle = 0) {
	trVectorQuestVarSet(qv,xsVectorSet(xsSin(angle), 0, xsCos(angle)));
}

float angleBetweenVectors(vector from = vector(0,0,0), vector to = vector(0,0,0)) {
	float a = xsVectorGetX(to) - xsVectorGetX(from);
	a = a / (xsVectorGetZ(to) - xsVectorGetZ(from));
	a = xsAtan(a);
	if (xsVectorGetZ(from) > xsVectorGetZ(to)) {
		if (xsVectorGetX(from) > xsVectorGetX(to)) {
			a = a - PI;
		} else {
			a = a + PI;
		}
	}
	return(a);
}

float trAngleBetweenVectors(string from = "", string to = "") {
	return(angleBetweenVectors(trVectorQuestVarGet(from),trVectorQuestVarGet(to)));
}

float angleOfVector(vector dir = vector(0,0,0)) {
	float a = xsVectorGetX(dir) / xsVectorGetZ(dir);
	a = xsAtan(a);
	if (0.0 > xsVectorGetZ(dir)) {
		if (0.0 > xsVectorGetX(dir)) {
			a = a - PI;
		} else {
			a = a + PI;
		}
	}
	return(a);
}

float trAngleOfVector(string v = "") {
	return(angleOfVector(trVectorQuestVarGet(v)));
}

vector getUnitVector(vector start = vector(0,0,0), vector end = vector(0,0,0), float mod = 1.0) {
	float xdiff = xsVectorGetX(end) - xsVectorGetX(start);
	float zdiff = xsVectorGetZ(end) - xsVectorGetZ(start);
	float dist = xsSqrt(xdiff * xdiff + zdiff * zdiff);
	vector ret = vector(1,0,0);
	if (dist > 0) {
		ret = xsVectorSet(xdiff / dist * mod, 0, zdiff / dist * mod);
	}
	return(ret);
}

vector trGetUnitVector(string start = "", string end = "", float mod = 1.0) {
	return(getUnitVector(trVectorQuestVarGet(start),trVectorQuestVarGet(end),mod));
}

vector getUnitVector3d(vector start = vector(0,0,0), vector end = vector(0,0,0), float mod = 1.0) {
	float xdiff = xsVectorGetX(end) - xsVectorGetX(start);
	float ydiff = xsVectorGetY(end) - xsVectorGetY(start);
	float zdiff = xsVectorGetZ(end) - xsVectorGetZ(start);
	float dist = xsSqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
	vector ret = vector(0,1,0);
	if (dist > 0) {
		ret = xsVectorSet(xdiff / dist * mod, ydiff / dist * mod, zdiff / dist * mod);
	}
	return(ret);
}

vector trGetUnitVector3d(string start = "", string end = "", float mod = 1.0) {
	return(getUnitVector3d(trVectorQuestVarGet(start),trVectorQuestVarGet(end),mod));
}

vector crossProduct(vector a = vector(0,0,0), vector b = vector(0,0,0)) {
	float x = xsVectorGetY(a) * xsVectorGetZ(b) - xsVectorGetZ(a) * xsVectorGetY(b);
	float y = xsVectorGetZ(a) * xsVectorGetX(b) - xsVectorGetX(a) * xsVectorGetZ(b);
	float z = xsVectorGetX(a) * xsVectorGetY(b) - xsVectorGetY(a) * xsVectorGetX(b);
	vector ret = xsVectorSet(x, y, z);
	return(ret);
}

vector trCrossProduct(string first = "", string second = "") {
	return(crossProduct(trVectorQuestVarGet(first), trVectorQuestVarGet(second)));
}

float dotProduct(vector a = vector(0,0,0), vector b = vector(0,0,0)) {
	return(xsVectorGetX(a) * xsVectorGetX(b) + xsVectorGetZ(a) * xsVectorGetZ(b));
}

bool terrainIsType(vector v = vector(0,0,0), int type = 0, int subtype = 0) {
	bool isType = trGetTerrainType(xsVectorGetX(v),xsVectorGetZ(v)) == type;
	isType = isType && (trGetTerrainSubType(xsVectorGetX(v),xsVectorGetZ(v)) == subtype);
	return(isType);
}

bool trTerrainIsType(string qv = "", int type = 0, int subtype = 0) {
	return(terrainIsType(trVectorQuestVarGet(qv),type,subtype));
}

/* initializes a modular counter. */
void modularCounterInit(string name = "", int size = 0) {
	trQuestVarSet("counter" + name + "size", size);
	trQuestVarSet("counter" + name + "pointer", 1);
	trQuestVarSet(name, 1);
}

/* Progresses the modular counter by 1 and returns the value */
int modularCounterNext(string name = "") {
	trQuestVarSet("counter" + name + "pointer", 1 + trQuestVarGet("counter" + name + "pointer"));
	if (trQuestVarGet("counter" + name + "pointer") > trQuestVarGet("counter" + name + "size")) {
		trQuestVarSet("counter" + name + "pointer", 1);
	}
	trQuestVarSet(name, trQuestVarGet("counter"+name+"pointer"));
	return(0 + trQuestVarGet("counter" + name + "pointer"));
}

/* Peeks at the next value of the modular counter */
int peekModularCounterNext(string name = "") {
	trQuestVarSet("counter" + name + "fake", 1 + trQuestVarGet("counter" + name + "pointer"));
	if (trQuestVarGet("counter" + name + "fake") >= trQuestVarGet("counter" + name + "size")) {
		trQuestVarSet("counter" + name + "fake", 1);
	}
	return(0 + trQuestVarGet("counter" + name + "fake"));
}

/*
Shows the Chat Log
*/
void ChatLogShow(){
	trChatHistoryClear();
	for(p=2; >0) {
		if (trCurrentPlayer() == p) {
			for (i = 5; >0) {
				trChatSend(0, trStringQuestVarGet("chat" + p + "Log" + modularCounterNext("chat"+p+"log")));
			}
		}
	}
}

/*
Adds a new message in the Chat Log and shows it
*/
void ChatLog(int p = 1, string message = ""){
	if (p == 0) {
		trStringQuestVarSet("chat1Log" + modularCounterNext("chat1Log"), message);
		trStringQuestVarSet("chat2Log" + modularCounterNext("chat2Log"), message);
	} else {
		trStringQuestVarSet("chat" + p + "Log" + modularCounterNext("chat" + p + "Log"), message);
	}
	ChatLogShow();
}
/*
Initializes a database of units given a starting value and length.
Units are selected using trUnitSelectByID, which is O(1), as opposed
to trUnitSelect, which is O(n).
Variables are associated with the unit value rather than the index in
the database.
This database is meant to be static. No adding or removing is supported.
This allows faster access of units and variables and less memory consumed.
*/
void zBankInit(string name = "", int start = 0, int length = 0) {
	trQuestVarSet("z"+name+"start", start);
	trQuestVarSet("z"+name+"end", start + length);
	trQuestVarSet("z"+name+"pointer", start);
	trQuestVarSet(name, start);
}

/* Gets the next unit in the bank. */
int zBankNext(string name = "", bool select = false) {
	trQuestVarSet("z"+name+"pointer", trQuestVarGet("z"+name+"pointer") + 1);
	if (trQuestVarGet("z"+name+"pointer") >= trQuestVarGet("z"+name+"end")) {
		trQuestVarSet("z"+name+"pointer", trQuestVarGet("z"+name+"start"));
	}
	trQuestVarCopy(name, "z"+name+"pointer");
	if (select) {
		trUnitSelectClear();
		trUnitSelectByID(1*trQuestVarGet(name));
	}
	return(1*trQuestVarGet(name));
}

/* Sets the variable of the currently selected bank item */
void zSetVar(string name = "", string var = "", float val = 0) {
	int index = trQuestVarGet(name);
	trQuestVarSet("z"+name+"i"+index+"v"+var, val);
}

/* Sets the variable of the bank item specified by index */
void zSetVarByIndex(string name = "", string var = "", int index = 0, float val = 0) {
	trQuestVarSet("z"+name+"i"+index+"v"+var, val);
}

/* Gets the variable of the currently selected bank item */
float zGetVar(string name = "", string var = "") {
	int index = trQuestVarGet(name);
	return(trQuestVarGet("z"+name+"i"+index+"v"+var));
}

/* Gets the variable of the bank item given by index */
float zGetVarByIndex(string name = "", string var = "", int index = 0) {
	return(trQuestVarGet("z"+name+"i"+index+"v"+var));
}

int zGetBankCount(string name = "") {
	return(1*trQuestVarGet("z"+name+"end") - trQuestVarGet("z"+name+"start"));
}


void mSetVar(int name = 0, string var = "", int val = 0) {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mInt,129,var));
	}
	aiPlanSetUserVariableInt(ARRAYS,1*trQuestVarGet("m"+var),name,val);
	
}

void mSetVarByQV(string qv = "", string var = "", int val = 0) {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mInt,129,var));
	}
	aiPlanSetUserVariableInt(ARRAYS,1*trQuestVarGet("m"+var),1*trQuestVarGet(qv),val);
}

void mSetString(int name = 0, string var = "", string val = "") {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mString,129,var));
	}
	aiPlanSetUserVariableString(ARRAYS,1*trQuestVarGet("m"+var),name,val);
}

void mSetStringByQV(string qv = "", string var = "", string val = "") {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mString,129,var));
	}
	aiPlanSetUserVariableString(ARRAYS,1*trQuestVarGet("m"+var),1*trQuestVarGet(qv),val);
}

int mGetVar(int name = 0, string var = "") {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mInt,129,var));
	}
	return(aiPlanGetUserVariableInt(ARRAYS,1*trQuestVarGet("m"+var),name));
}

int mGetVarByQV(string qv = "", string var = "") {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mInt,129,var));
	}
	return(aiPlanGetUserVariableInt(ARRAYS,1*trQuestVarGet("m"+var),1*trQuestVarGet(qv)));
}

string mGetString(int name = 0, string var = "") {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mString,129,var));
	}
	return(aiPlanGetUserVariableString(ARRAYS,1*trQuestVarGet("m"+var),name));
}

string mGetStringByQV(string qv = "", string var = "") {
	xsSetContextPlayer(0);
	if (trQuestVarGet("m"+var) <= 0) {
		trQuestVarSet("m"+var, zNewArray(mString,129,var));
	}
	return(aiPlanGetUserVariableString(ARRAYS,1*trQuestVarGet("m"+var),1*trQuestVarGet(qv)));
}

bool yDatabaseExists(string dbname = "") {
	return(trQuestVarGet("database"+dbname) > 0);
}

bool yDatabaseCreateIfNull(string dbname = "", int count = 0) {
	bool created = false;
	if (trQuestVarGet("database"+dbname) == 0) {
		if (count < 0) {
			count = 0;
		}
		trQuestVarSet("database"+dbname, xInitDatabase(dbname, count));
		created = true;
	}
	return(created);
}

bool yVariableExists(string dbname = "", string varname = "") {
	int db = trQuestVarGet("database"+dbname);
	int var = trQuestVarGet("database"+dbname+varname);
	return(db * var > 0);
}

float yGetVarAtIndex(string db = "", string var = "", int index = 0) {
	if (yVariableExists(db, var)) {
		return(xGetFloat(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),index));
	} else {
		return(0);
	}
}

float yGetVar(string db = "", string var = "") {
	return(yGetVarAtIndex(db, var, -1));
}

string yGetStringAtIndex(string db = "", string var = "", int index = 0) {
	if (yVariableExists(db, var)) {
		return(xGetString(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),index));
	} else {
		return("");
	}
}

string yGetString(string db = "", string var = "") {
	return(yGetStringAtIndex(db, var, -1));
}

vector yGetVectorAtIndex(string db = "", string var = "", int index = 0) {
	if (yVariableExists(db, var)) {
		return(xGetVector(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),index));
	} else {
		return(vector(0,0,0));
	}
}

vector yGetVector(string db = "", string var = "") {
	return(yGetVectorAtIndex(db, var, -1));
}

void ySetVarAtIndex(string db = "", string var = "", float val = 0, int index = 0) {
	if (yVariableExists(db, var)) {
		xSetFloat(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
	} else {
		yDatabaseCreateIfNull(db, index + 1);
		trQuestVarSet("database"+db+var, xInitAddFloat(1*trQuestVarGet("database"+db),var));
		xSetFloat(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
	}
}

void ySetVar(string db = "", string var = "", float val = 0) {
	ySetVarAtIndex(db, var, val, -1);
}

void ySetStringAtIndex(string db = "", string var = "", string val = "", int index = 0) {
	if (yVariableExists(db, var)) {
		xSetString(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
	} else {
		yDatabaseCreateIfNull(db, index);
		trQuestVarSet("database"+db+var, xInitAddFloat(1*trQuestVarGet("database"+db),var));
		xSetString(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
	}
}

void ySetString(string db = "", string var = "", string val = "") {
	ySetStringAtIndex(db, var, val, -1);
}

void ySetVectorAtIndex(string db = "", string var = "", vector val = vector(0,0,0), int index = 0) {
	if (yVariableExists(db, var)) {
		xSetVector(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
	} else {
		yDatabaseCreateIfNull(db, index);
		trQuestVarSet("database"+db+var, xInitAddFloat(1*trQuestVarGet("database"+db),var));
		xSetVector(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
	}
}

void ySetVector(string db = "", string var = "", vector val = vector(0,0,0)) {
	ySetVectorAtIndex(db, var, val, -1);
}

int yGetDatabaseCount(string db = "") {
	yDatabaseCreateIfNull(db);
	return(xGetDatabaseCount(1*trQuestVarGet("database"+db)));
}

int yDatabaseNext(string db = "", bool select = false, bool reverse = false) {
	if (yGetDatabaseCount(db) > 0) {
		xDatabaseNext(1*trQuestVarGet("database"+db), reverse);
	}
	int u = yGetVar(db, "unitName");
	trQuestVarSet(db, u);
	if (select) {
		trUnitSelectClear();
		trUnitSelect(""+u, true);
		return(kbGetBlockID(""+u, true));
	} else {
		return(u);
	}
}

void yRemoveFromDatabase(string db = "") {
	xFreeDatabaseBlock(1*trQuestVarGet("database"+db));
}

int yGetNewestPointer(string db = "") {
	return(xGetNewestPointer(1*trQuestVarGet("database"+db)));
}

void yAddUpdateVar(string db = "", string var = "", float val = 0) {
	ySetVarAtIndex(db, var, val, yGetNewestPointer(db));
}

void yAddUpdateString(string db = "", string var = "", string val = "") {
	ySetStringAtIndex(db, var, val, yGetNewestPointer(db));
}

void yAddUpdateVector(string db = "", string var = "", vector val = vector(0,0,0)) {
	ySetVectorAtIndex(db, var, val, yGetNewestPointer(db));
}

int yAddToDatabase(string db = "", string val = "") {
	yDatabaseCreateIfNull(db);
	int id = trQuestVarGet("database"+db);
	int next = xAddDatabaseBlock(id);
	yAddUpdateVar(db, "unitName", trQuestVarGet(val));
	return(next);
}

int yGetPointer(string db = "") {
	return(xGetPointer(1*trQuestVarGet("database"+db)));
}

bool ySetPointer(string db = "", int index = 0) {
	bool safe = xSetPointer(1*trQuestVarGet("database"+db), index);
	if (safe) {
		trQuestVarSet(db, yGetVar(db, "unitName"));
	}
	return(safe);
}

int yGetUnitAtIndex(string db = "", int index = 0) {
	return(1*yGetVarAtIndex(db, "unitName", index));
}

void ySetUnitAtIndex(string db = "", int index = 0, int value = 0) {
	ySetVarAtIndex(db, "unitName", value, index);
}

void ySetUnit(string db = "", int value = 0) {
	ySetVar(db, "unitName", value);
}

void yClearDatabase(string db = "") {
	xClearDatabase(1*trQuestVarGet("database"+db));
}

void yDeleteDatabase(string db = "") {
	aiPlanDestroy(1*trQuestVarGet("database"+db));
}

void yDatabaseSelectAll(string db = "") {
	trUnitSelectClear();
	for(x=yGetDatabaseCount(db); >0) {
		yDatabaseNext(db);
		trUnitSelectByQV(db);
	}
}

/*
Starting from NextUnitScenarioNameNumber and going backwards until the quest var 'qv',
looks for the specified protounit. If none found, returns -1. Otherwise, returns the
unit name.
*/
int yFindLatestReverse(string qv = "", string proto = "", int p = 0) {
	int id = kbGetProtoUnitID(proto);
	trUnitSelectClear();
	for(x=trGetNextUnitScenarioNameNumber(); >trQuestVarGet(qv)) {
		int i = kbGetBlockID(""+x, true);
		if (kbGetUnitBaseTypeID(i) == id) {
			trUnitSelectClear();
			trUnitSelectByID(i);
			if (trUnitIsOwnedBy(p)) {
				trQuestVarSet(qv, x);
				return(i);
			}
		}
	}
	return(-1);
}

/*
Starting from quest var 'qv' and going up until NextUnitScenarioNameNumber,
looks for the specified protounit. If none found, returns -1. Otherwise, returns the
unit name.
*/
int yFindLatest(string qv = "", string proto = "", int p = 0) {
	int id = kbGetProtoUnitID(proto);
	trUnitSelectClear();
	int next = trGetNextUnitScenarioNameNumber() - 1;
	int current = trQuestVarGet(qv);
	while(next > current) {
		current = current + 1;
		int i = kbGetBlockID(""+current, true);
		if (kbGetUnitBaseTypeID(i) == id) {
			trUnitSelectClear();
			trUnitSelectByID(i);
			if (trUnitIsOwnedBy(p)) {
				trQuestVarSet(qv, current);
				return(i);
			}
		}
	}
	return(-1);
}


/*
Deploy a unit exactly where I want.
p - protounit name, v - vector name
Used in prologue.c
*/
void DeploySober(string p="", string v=""){
	int next = trGetNextUnitScenarioNameNumber();
	trArmyDispatch("1,10",p,1,trVectorQuestVarGetX(v), trVectorQuestVarGetY(v), trVectorQuestVarGetZ(v),0,true);
	trUnitSelectClear();trUnitSelect(""+next, true);
	trUnitTeleport(trVectorQuestVarGetX(v),trVectorQuestVarGetY(v),trVectorQuestVarGetZ(v));
}

/*
Bit functions
n - number, p - position
*/
bool GetBit(int n=0, int p=0){
	for(i=0;<30){
		if(i==p){
			return (iModulo(2,n)==1);
		}
		n=n/2;
	}
	return (false);
}

int SetBit(int n=0, int p=0){
	int r = 0;
	for(i=0;<30){
		if(iModulo(2,n)==1||i==p){
			r=r+xsPow(2,i);
		}
		n=n/2;
	}
	return (r);
}

int ClearBit(int n=0, int p=0){
	int r = 0;
	for(i=0;<30){
		if(iModulo(2,n)==1&&i!=p){
			r=r+xsPow(2,i);
		}
		n=n/2;
	}
	return (r);
}

rule initializeEverything
highFrequency
active
runImmediately
{
	// Set idle processing to false so the game doesn't lag from trying to process 128 murmillos
	trSetUnitIdleProcessing(false);
	trUIFadeToColor(0,0,0,0,0,true);
	trSetObscuredUnits(false);
	trSetCivAndCulture(1, 9, 3); // Set P1 to Kronos
	trSetCivAndCulture(2, 9, 3); // Set P2 to Kronos
	
	gadgetUnreal("GodPowers");
	
	for(p=2; >0) {
		modularCounterInit("chat" + p + "Log", 5);
	}
	
	Multiplayer = aiIsMultiplayer(); 	// nottud is smart
	if(Multiplayer && kbIsPlayerHuman(2) == false){
		Multiplayer = false; // or kick?
	}
	xsEnableRule("data_load_00");
	
	modularCounterInit("lightningPop", 40);
	modularCounterInit("lightningPush", 40);
	modularCounterInit("lightningActivate", 40);
	
	modularCounterInit("spyFind", 40);
	modularCounterInit("spyFound", 40);
	
	modularCounterInit("deathSummonPush", 20);
	modularCounterInit("deathSummonPop", 20);
	
	
	trModifyProtounit("Gold Mine Dwarven", 1, 55, 4);
	trModifyProtounit("Gold Mine Dwarven", 2, 55, 4);
	// Modify animal attractor flying
	trModifyProtounit("Animal Attractor", 1, 55, 4);
	trModifyProtounit("Animal Attractor", 2, 55, 4);
	
	zInitProtoUnitStat("Wadjet Spit", 1, 1, 30);
	zInitProtoUnitStat("Wadjet Spit", 2, 1, 30);
	zSetProtoUnitStat("Wadjet Spit", 1, 1, 20);
	zSetProtoUnitStat("Wadjet Spit", 2, 1, 20);
	
	trModifyProtounit("Revealer", 0, 2, 9999999999999999999.0);
	trModifyProtounit("Revealer", 0, 2, -9999999999999999999.0);
	trModifyProtounit("Revealer", 0, 2, 54);
	trModifyProtounit("Revealer to Player", 1, 2, 9999999999999999999.0);
	trModifyProtounit("Revealer to Player", 1, 2, -9999999999999999999.0);
	trModifyProtounit("Revealer to Player", 1, 2, 18);
	trModifyProtounit("Revealer to Player", 2, 2, 9999999999999999999.0);
	trModifyProtounit("Revealer to Player", 2, 2, -9999999999999999999.0);
	trModifyProtounit("Revealer to Player", 2, 2, 18);
	
	trModifyProtounit("Bolt Strike", 0, 27, -10000);
	trModifyProtounit("Bolt Strike", 0, 28, -10000);
	trModifyProtounit("Bolt Strike", 0, 29, -10000);
	
	// LOS
	for(p=2; >0) {
		trModifyProtounit("Dwarf", p, 2, -20);
		trModifyProtounit("Animal Attractor", p, 2, -20);
		trModifyProtounit("Nidhogg", p, 2, -20);
		trTechSetStatus(p, 7, 4); // heavy infantry
		trTechSetStatus(p, 476, 4); // iron all
		trTechSetStatus(p, 412, 4); // Iron wall
	}
	
	// Disable god powers
	trPlayerTechTreeEnabledGodPowers(1, false);
	trPlayerTechTreeEnabledGodPowers(2, false);
	
	// omniscience for p0
	trTechSetStatus(0, 304, 4);
	
	trPlayerSetDiplomacy(0, 1, "Enemy");
	trPlayerSetDiplomacy(0, 2, "Enemy");
	trPlayerSetDiplomacy(1, 0, "Neutral");
	trPlayerSetDiplomacy(2, 0, "Neutral");
	trPlayerSetDiplomacy(2, 1, "Enemy");
	trPlayerSetDiplomacy(1, 2, "Enemy");
	
	xsDisableRule("initializeEverything");
}


rule PlsStopHardcodingCrapYouNoobs
highFrequency
active
{
	if ((trTime()-cActivationTime) >= 1){
		trModifyProtounit("Hero Greek Jason", 1, 27, 4.0);
		trModifyProtounit("Hero Greek Jason", 2, 27, 4.0);
		trModifyProtounit("Hero Greek Ajax", 1, 27, 3.0);
		trModifyProtounit("Hero Greek Ajax", 2, 27, 3.0);
		trModifyProtounit("Hero Greek Theseus", 1, 27, 4.0);
		trModifyProtounit("Hero Greek Theseus", 2, 27, 4.0);
		xsDisableRule("PlsStopHardcodingCrapYouNoobs");
	}
}
