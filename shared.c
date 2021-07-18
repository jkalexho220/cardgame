bool Multiplayer = false;

bool playerIsPlaying(int p = 0) {
	return(kbIsPlayerHuman(p) == true && kbIsPlayerResigned(p) == false);
}

/* 
Given a quest var that stores a unit name, store
the unit's position in the vector.
*/
void trVectorSetUnitPos(string v = "", string db = "", bool reverse = true) {
	trVectorQuestVarSet(v, kbGetBlockPosition(""+1*trQuestVarGet(db), reverse));
}


void trUnitMoveToVector(string v = "", bool attack = false) {
	trUnitMoveToPoint(trVectorQuestVarGetX(v),0,trVectorQuestVarGetZ(v),-1,attack);
}

void trVectorScale(string db = "", float s = 1.0) {
	trQuestVarSet(db+"x", trQuestVarGet(db+"x") * s);
	trQuestVarSet(db+"z", trQuestVarGet(db+"z") * s);
}


void vectorSnapToGrid(string qv = "") {
	int x = trQuestVarGet(qv+"x") / 2;
	int z = trQuestVarGet(qv+"z") / 2;
	trQuestVarSet(qv+"x", x * 2 + 1);
	trQuestVarSet(qv+"z", z * 2 + 1);
}

int zModulo(int mod = 10, float val = 0) {
	int m = 0 + mod;
	int v = xsRound(val);
	return(v - xsFloor(val / m) * m);
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

void vectorToGrid(string from = "", string to = ""){
	int x = 0 + trQuestVarGet(from+"x") / 2;
	int z = 0 + trQuestVarGet(from+"z") / 2;
	trQuestVarSet(to+"x", x);
	trQuestVarSet(to+"z", z);
}

void gridToVector(string from = "", string to = "") {
	trQuestVarSet(to+"x", trQuestVarGet(from+"x") * 2 + 1);
	trQuestVarSet(to+"z", trQuestVarGet(from+"z") * 2 + 1);
}

float gridDistanceSquared(string from = "", string to = "") {
	float xdiff = trQuestVarGet(to+"x") - trQuestVarGet(from+"x");
	float zdiff = trQuestVarGet(to+"z") - trQuestVarGet(from+"z");
	return(xdiff * xdiff + zdiff * zdiff);
}

void zSquareVar(string qv = "") {
	trQuestVarSet(qv, xsPow(trQuestVarGet(qv), 2));
}

float zDistanceBetweenVectorsSquared(string start = "", string end = "") {
	float xdiff = trQuestVarGet(end + "X") - trQuestVarGet(start + "X");
	float zdiff = trQuestVarGet(end + "Z") - trQuestVarGet(start + "Z");
	float dist = xdiff * xdiff + zdiff * zdiff;
	return(dist);
}



float zDistanceBetweenVectors(string start = "", string end = "") {
	float xdiff = trQuestVarGet(end + "X") - trQuestVarGet(start + "X");
	float zdiff = trQuestVarGet(end + "Z") - trQuestVarGet(start + "Z");
	float dist = xsSqrt(xdiff * xdiff + zdiff * zdiff);
	return(dist);
}

float zDistanceBetweenVectors3d(string start = "", string end = "") {
	float xdiff = trQuestVarGet(end + "X") - trQuestVarGet(start + "X");
	float ydiff = trQuestVarGet(end + "Y") - trQuestVarGet(start + "Y");
	float zdiff = trQuestVarGet(end + "Z") - trQuestVarGet(start + "Z");
	float dist = xsSqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
	return(dist);
}

float zDistanceToVectorSquared(string qv = "", string v = "") {
	trVectorQuestVarSet("abcd", kbGetBlockPosition(""+1*trQuestVarGet(qv), true));
	return(zDistanceBetweenVectorsSquared("abcd", v));
}

/* For use in a ySearch */
float zDistanceToVector(string qv = "", string v = "") {
	trVectorQuestVarSet("abcd", kbGetBlockPosition(""+1*trQuestVarGet(qv), true));
	return(zDistanceBetweenVectors("abcd", v));
}

void trVectorSetFromAngle(string qv = "", float angle = 0) {
	trVectorQuestVarSet(qv,xsVectorSet(Math_sin(angle), 0, Math_cos(angle)));
}

float angleBetweenVectors(string from = "", string to = "") {
	float a = Math_atan((trQuestVarGet(to+"X")-trQuestVarGet(from+"X"))/(trQuestVarGet(to+"Z")-trQuestVarGet(from+"Z")));
	if (trVectorQuestVarGetZ(from) > trVectorQuestVarGetZ(to)) {
	    if (trVectorQuestVarGetX(from) > trVectorQuestVarGetX(to)) {
			a = a - PI;
	    } else {
			a = a + PI;
	    }
  	}
  	return(a);
}

vector zGetUnitVector(string start = "", string end = "", float mod = 1.0) {
	float xdiff = trQuestVarGet(end + "X") - trQuestVarGet(start + "X");
	float zdiff = trQuestVarGet(end + "Z") - trQuestVarGet(start + "Z");
	float dist = xsSqrt(xdiff * xdiff + zdiff * zdiff);
	vector ret = xsVectorSet(xdiff / dist * mod, 0, zdiff / dist * mod);
	return(ret);
}

vector zGetUnitVector3d(string start = "", string end = "", float mod = 1.0) {
	float xdiff = trQuestVarGet(end + "X") - trQuestVarGet(start + "X");
	float ydiff = trQuestVarGet(end + "Y") - trQuestVarGet(start + "Y");
	float zdiff = trQuestVarGet(end + "Z") - trQuestVarGet(start + "Z");
	float dist = xsSqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
	vector ret = xsVectorSet(xdiff / dist * mod, ydiff / dist * mod, zdiff / dist * mod);
	return(ret);
}

vector crossProduct(string a = "", string b = "") {
	float x = trQuestVarGet(a + "y") * trQuestVarGet(b + "z") - trQuestVarGet(a + "z") * trQuestVarGet(b + "y");
	float y = trQuestVarGet(a + "z") * trQuestVarGet(b + "x") - trQuestVarGet(a + "x") * trQuestVarGet(b + "z");
	float z = trQuestVarGet(a + "x") * trQuestVarGet(b + "y") - trQuestVarGet(a + "y") * trQuestVarGet(b + "x");
	vector ret = xsVectorSet(x, y, z);
	return(ret);
}

/* 
A shitty binary search algorithm to approximate the intersection of a line with 
the circle specified by the center vector and radius. Behavior is undefined if start
vector is outside the circle.  
Did this to avoid using trig as much as possible because trig is expensive.
*/
vector intersectionWithCircle(string start = "", string end = "", string center = "", float radius = 0) {
	trVectorQuestVarSet("iDir", zGetUnitVector(start, end));
	float x = 0;
	float z = 0;
	float dist = 0;
	float len = radius * 2;
	float lenmod = radius;
	for(i=8; >0) {
		x = trQuestVarGet(start+"x") + trQuestVarGet("iDirx") * len;
		z = trQuestVarGet(start+"z") + trQuestVarGet("iDirz") * len;
		dist = xsPow(x - trQuestVarGet(center+"x"), 2) + xsPow(z - trQuestVarGet(center+"z"), 2);
		if (dist > radius * radius) {
			len = len - lenmod;
		} else {
			len = len + lenmod;
		}
		lenmod = lenmod * 0.5;
	}
	return(xsVectorSet(x,0,z));
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
	trQuestVarCopy(name, "counter" + name + "pointer");
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
	return(trQuestVarGet("z"+name+"end") - trQuestVarGet("z"+name+"start"));
}

/* Adds a unit specified by the quest var 'from' to the database 'to' */
void yAddToDatabase(string to = "", string from = "") {
	int zdatacount = trQuestVarGet("zdatalite" + to + "count");
   	trQuestVarSet("zdatalite" + to + "index"+zdatacount, trQuestVarGet(from));
   	trQuestVarSet("zdatalite" + to + "count", zdatacount+1);
}

int yGetDatabaseCount(string db = "") {
	return(trQuestVarGet("zdatalite" + db + "count"));
}

/*
Gets the next unit in the database 'db'. Variables are associated with the
database index rather than the value.
*/
int yDatabaseNext(string db = "", bool select = false) {
	for(zdatapointer=0;>1){}
	trQuestVarSet("zdatalite" + db + "pointer", trQuestVarGet("zdatalite" + db + "pointer")-1);
	if (0 > trQuestVarGet("zdatalite" + db + "pointer")) {
		trQuestVarSet("zdatalite" + db + "pointer", trQuestVarGet("zdatalite" + db + "count")-1);
	}
	if (trQuestVarGet("zdatalite" + db + "pointer") >= trQuestVarGet("zdatalite" + db + "count")) {
		trQuestVarSet("zdatalite" + db + "pointer", trQuestVarGet("zdatalite" + db + "count")-1);
	}
	zdatapointer = trQuestVarGet("zdatalite" + db + "pointer");
	trQuestVarSet(db, trQuestVarGet("zdatalite" + db + "index"+zdatapointer));
	if (select) {
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet(db), true);
		return(kbGetBlockID(""+1*trQuestVarGet(db), true));
	}
	return(trQuestVarGet(db));
}

void yDatabaseSelectAll(string db = "") {
	trUnitSelectClear();
	for(zdatapointer=0; <yGetDatabaseCount(db)) {
		trUnitSelect(""+1*trQuestVarGet("zdatalite"+db+"index"+zdatapointer), true);
	}
}

bool yDatabaseContains(string db = "", int index = 0) {
	for (x=yGetDatabaseCount(db) - 1; >=0) {
		if (xsRound(trQuestVarGet("zdatalite" + db + "index" + x)) == index) {
			trQuestVarSet("zdatalite" + db + "pointer", x);
			trQuestVarSet(db, index);
			trUnitSelectClear();
			trUnitSelect(""+index, true);
			return(true);
		}
	}
	return(false);
}


void yDatabasePointerDefault(string db = "") {
	trQuestVarSet("zdatalite" + db + "pointer", 0);
}

/*
When something is removed from the database, we simply swap it with
the last item in the array and decrease count by 1. However, the variables
are associated by index, so we must call yRemoveUpdateVar afterwards for each
variable associated in this database.
*/
void yRemoveFromDatabase(string db = "") {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count") - 1;
	int zdataremove = trQuestVarGet("zdatalite" + db + "pointer");
	trQuestVarSet("zdatalite" + db + "index"+zdataremove, 
		trQuestVarGet("zdatalite" + db + "index"+zdatacount));
	trQuestVarSet("zdatalite" + db + "count", zdatacount);
}

void yRemoveUpdateString(string db = "", string attr = "") {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count");
	int zdataremove = trQuestVarGet("zdatalite" + db + "pointer");
	trStringQuestVarSet("zdatalite" + db + "" + zdataremove + "" + attr, 
		trStringQuestVarGet("zdatalite" + db + "" + zdatacount + "" + attr));
	trStringQuestVarSet("zdatalite" + db + "" + zdatacount + "" + attr, " ");
}

void yRemoveUpdateVar(string db = "", string attr = "") {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count");
	int zdataremove = trQuestVarGet("zdatalite" + db + "pointer");
	trQuestVarSet("zdatalite" + db + "" + zdataremove + "" + attr, 
		trQuestVarGet("zdatalite" + db + "" + zdatacount + "" + attr));
	trQuestVarSet("zdatalite" + db + "" + zdatacount + "" + attr, 0);
}

void yTransferUpdateVar(string to = "", string from = "", string attr = "") {
	int zdatato = trQuestVarGet("zdatalite" + to + "count") - 1;
	int zdatafrom = trQuestVarGet("zdatalite" + from + "pointer");
	trQuestVarSet("zdatalite" + to + ""  + zdatato + "" + attr, 
		trQuestVarGet("zdatalite" + from + ""  + zdatafrom + "" + attr));
}

void yTransferUpdateString(string to = "", string from = "", string attr = "") {
	int zdatato = trQuestVarGet("zdatalite" + to + "count") - 1;
	int zdatafrom = trQuestVarGet("zdatalite" + from + "pointer");
	trStringQuestVarSet("zdatalite" + to + ""  + zdatato + "" + attr, 
		trStringQuestVarGet("zdatalite" + from + ""  + zdatafrom + "" + attr));
}

void yAddUpdateString(string db = "", string attr = "", string value = "") {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count") - 1;
	trStringQuestVarSet("zdatalite" + db + "" + zdatacount + "" + attr, value);
}

void yAddUpdateVar(string db = "", string attr = "", float value = 0.0) {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count") - 1;
	trQuestVarSet("zdatalite" + db + "" + zdatacount + "" + attr, value);
}

string yGetString(string db = "", string attr = "") {
	int zdatapointer = trQuestVarGet("zdatalite" + db + "pointer");
	return(trStringQuestVarGet("zdatalite" + db + "" + zdatapointer + "" + attr));
}

float yGetVar(string db = "", string attr = "") {
	int zdatapointer = trQuestVarGet("zdatalite" + db + "pointer");
	return(trQuestVarGet("zdatalite" + db + "" + zdatapointer + "" + attr));
}

string yGetStringByIndex(string db = "", string attr = "", int index = 0) {
	return(trStringQuestVarGet("zdatalite" + db + "" + index + "" + attr));
}

float yGetVarByIndex(string db = "", string attr = "", int index = 0) {
	return(trQuestVarGet("zdatalite" + db + "" + index + "" + attr));
}

void ySetString(string db = "", string attr = "", string value = "") {
	int zdatapointer = trQuestVarGet("zdatalite" + db + "pointer");
	trStringQuestVarSet("zdatalite" + db + "" + zdatapointer + "" + attr, value);
}

void ySetVar(string db = "", string attr = "", float value = 0.0) {
	int zdatapointer = trQuestVarGet("zdatalite" + db + "pointer");
	trQuestVarSet("zdatalite" + db + "" + zdatapointer + "" + attr, value);
}

void ySetStringByIndex(string db = "", string attr = "", int index = 0, string value = "") {
	trStringQuestVarSet("zdatalite" + db + "" + index + "" + attr, value);
}

void ySetVarByIndex(string db = "", string attr = "", int index = 0, float value = 0.0) {
	trQuestVarSet("zdatalite" + db + "" + index + "" + attr, value);
}

int yGetUnitAtIndex(string db = "", int index = 0) {
	return(trQuestVarGet("zdatalite"+db+"index"+index));
}

int ySetUnitAtIndex(string db = "", int index = 0, int value = 0) {
	trQuestVarSet("zdatalite"+db+"index"+index, value);
}

int yGetPointer(string db = "") {
	return(trQuestVarGet("zdatalite"+db+"pointer"));
}

void ySetPointer(string db = "", int val = 0) {
	trQuestVarSet("zdatalite"+db+"pointer", val);
	trQuestVarSet(db, trQuestVarGet("zdatalite" + db + "index"+val));
}

void yClearDatabase(string db = "") {
	trQuestVarSet("zdatalite" + db + "count", 0);
	trQuestVarSet("zdatalite" + db + "pointer", 0);
	trQuestVarSet(db, 0);
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
	trQuestVarSet("next",trGetNextUnitScenarioNameNumber() - 1);
	while(trQuestVarGet("next") > trQuestVarGet(qv)) {
		trQuestVarSet(qv, 1 + trQuestVarGet(qv));
		int i = kbGetBlockID(""+1*trQuestVarGet(qv), true);
		if (kbGetUnitBaseTypeID(i) == id) {
			trUnitSelectClear();
			trUnitSelectByID(i);
			if (trUnitIsOwnedBy(p)) {
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
			return (zModulo(2,n)==1);
		}
		n=n/2;
	}
	return (false);
}

int SetBit(int n=0, int p=0){
	int r = 0;
	for(i=0;<30){
		if(zModulo(2,n)==1||i==p){
			r=r+xsPow(2,i);
		}
		n=n/2;
	}
	return (r);
}
		
int ClearBit(int n=0, int p=0){
	int r = 0;
	for(i=0;<30){
		if(zModulo(2,n)==1&&i!=p){
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
    trSetObscuredUnits(false);
	trSetCivAndCulture(1, 9, 3); // Set P1 to Kronos
	trSetCivAndCulture(2, 9, 3); // Set P2 to Kronos
	Multiplayer = aiIsMultiplayer(); 	// nottud is smart
	if(Multiplayer && kbIsPlayerHuman(2) == false){
		Multiplayer = false; // or kick?
	}
	if(Multiplayer){
		trChatSend(0, "Mode:Multiplayer");
	} else {
		trChatSend(0, "Mode:Singleplayer");
		// Cards will probably be unlocked in order, so I'm assuming the player has not played before if the first value is zero
		bool virgin = trGetScenarioUserData(0); 
		virgin = false; // testing
		trChatSend(0, "Checking if played before...");
		if(virgin && trQuestVarGet("chad") == 0){
			xsEnableRule("CinPrologue00");
		}
	}

	modularCounterInit("lightningPop", 40);
	modularCounterInit("lightningPush", 40);
	modularCounterInit("lightningActivate", 40);

	modularCounterInit("spyFind", 40);
	modularCounterInit("spyFound", 40);


	trModifyProtounit("Gold Mine Dwarven", 1, 55, 4);
	trModifyProtounit("Gold Mine Dwarven", 2, 55, 4);
	// Modify animal attractor flying
	trModifyProtounit("Animal Attractor", 1, 55, 4);
	trModifyProtounit("Animal Attractor", 2, 55, 4);


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