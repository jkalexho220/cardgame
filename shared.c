bool amINoob(){
	return true;
}


bool playerIsPlaying(int p = 0) {
	return(kbIsPlayerHuman(p) == true && kbIsPlayerResigned(p) == false);
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

void modularCounterInit(string name = "", int size = 0) {
	trQuestVarSet("counter" + name + "size", size);
	trQuestVarSet("counter" + name + "pointer", 1);
	trQuestVarSet(name, 1);
}

int modularCounterNext(string name = "") {
	trQuestVarSet("counter" + name + "pointer", 1 + trQuestVarGet("counter" + name + "pointer"));
	if (trQuestVarGet("counter" + name + "pointer") > trQuestVarGet("counter" + name + "size")) {
		trQuestVarSet("counter" + name + "pointer", 1);
	}
	trQuestVarCopy(name, "counter" + name + "pointer");
	return(0 + trQuestVarGet("counter" + name + "pointer"));
}

int getModularCounterNext(string name = "") {
	trQuestVarSet("counter" + name + "fake", 1 + trQuestVarGet("counter" + name + "pointer"));
	if (trQuestVarGet("counter" + name + "fake") >= trQuestVarGet("counter" + name + "size")) {
		trQuestVarSet("counter" + name + "fake", 1);
	}
	return(0 + trQuestVarGet("counter" + name + "fake"));
}

void yAddToDatabase(string to = "", string from = "") {
	int zdatacount = trQuestVarGet("zdatalite" + to + "count");
   	trQuestVarSet("zdatalite" + to + "index"+zdatacount, trQuestVarGet(from));
   	trQuestVarSet("zdatalite" + to + "count", zdatacount+1);
}

int yGetDatabaseCount(string db = "") {
	return(trQuestVarGet("zdatalite" + db + "count"));
}

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

void yRemoveFromDatabase(string db = "") {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count") - 1;
	int zdataremove = trQuestVarGet("zdatalite" + db + "pointer");
	trQuestVarSet("zdatalite" + db + "index"+zdataremove, 
		trQuestVarGet("zdatalite" + db + "index"+zdatacount));
	trQuestVarSet("zdatalite" + db + "count", zdatacount);
}

void yRemoveUpdateVar(string db = "", string attr = "") {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count");
	int zdataremove = trQuestVarGet("zdatalite" + db + "pointer");
	trQuestVarSet("zdatalite" + db + "" + zdataremove + "" + attr, 
		trQuestVarGet("zdatalite" + db + "" + zdatacount + "" + attr));
	trQuestVarSet("zdatalite" + db + "" + zdatacount + "" + attr, 0);
}

void yTransferUpdateVar(string to = "", string from = "", string attr = "") {
	int zdatato = trQuestVarGet("zdatalite" + to + "count");
	int zdatafrom = trQuestVarGet("zdatalite" + from + "pointer");
	trQuestVarSet("zdatalite" + to + ""  + zdatato + "" + attr, 
		trQuestVarGet("zdatalite" + from + ""  + zdatafrom + "" + attr));
}

void yAddUpdateVar(string db = "", string attr = "", float value = 0.0) {
	int zdatacount = trQuestVarGet("zdatalite" + db + "count") - 1;
	trQuestVarSet("zdatalite" + db + "" + zdatacount + "" + attr, value);
}

float yGetVar(string db = "", string attr = "") {
	int zdatapointer = trQuestVarGet("zdatalite" + db + "pointer");
	return(trQuestVarGet("zdatalite" + db + "" + zdatapointer + "" + attr));
}

void ySetVar(string db = "", string attr = "", float value = 0.0) {
	int zdatapointer = trQuestVarGet("zdatalite" + db + "pointer");
	trQuestVarSet("zdatalite" + db + "" + zdatapointer + "" + attr, value);
}

void yClearDatabase(string db = "") {
	trQuestVarSet("zdatalite" + db + "count", 0);
	trQuestVarSet("zdatalite" + db + "pointer", 0);
	trQuestVarSet(db, 0);
}



int yFindLatest(string qv = "", string proto = "", int p = 0) {
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

int yFindLatestReverse(string qv = "", string proto = "", int p = 0) {
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


rule initializeEverything
highFrequency
active
runImmediately
{
	
	xsDisableRule("initializeEverything");
}
