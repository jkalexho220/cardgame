
int chooseRandomPlayer() {
	for(p=trQuestVarGet("numHumans"); >0) {
		trQuestVarSetFromRand("rand", 1, p, true);
		int temp = trQuestVarGet("playerTarget"+1*trQuestVarGet("rand"));
		trQuestVarSet("playerTarget"+1*trQuestVarGet("rand"), trQuestVarGet("playerTarget"+p));
		trQuestVarSet("playerTarget"+p, temp);
	}
	int x = 0;
	for(p=trQuestVarGet("numHumans"); >0) {
		x = trQuestVarGet("playerTarget"+p);
		if (trQuestVarGet("p"+x+"dead") == 0) {
			return(x);
		}
	}
	return(0);
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

float zGetTime() {
	return(trQuestVarGet("timeLordWatch"));
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

float zDistanceBetweenVectorsRootless(string start = "", string end = "") {
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

float zDistanceToVectorRootless(string qv = "", string v = "") {
	trVectorQuestVarSet("abcd", kbGetBlockPosition(""+1*trQuestVarGet(qv), true));
	return(zDistanceBetweenVectorsRootless("abcd", v));
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

int yDatabaseNext(string db = "", bool reverse = true) {
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
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet(db), reverse);
	return(kbGetBlockID(""+1*trQuestVarGet(db), reverse));
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

void yDatabasePointerBacktrack(string db = "") {
	trQuestVarSet("zdatalite" + db + "pointer", 1 + trQuestVarGet("zdatalite" + db + "pointer"));
	if (trQuestVarGet("zdatalite" + db + "pointer") >= trQuestVarGet("zdatalite" + db + "count")) {
		trQuestVarSet("zdatalite" + db + "pointer", 0);
	}
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


void updateAttack(int p = 0) {
	zSetProtoUnitStat("Valkyrie", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Anubite", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Royal Guard", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Royal Guard Hero", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Bolt Strike", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Archer Atlantean", p, 31, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Fire Lance", p, 32, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Throwing Axeman", p, 30, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Swordsman", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Peltast", p, 31, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Lampades", p, 31, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Frost Giant", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Myrmidon", p, 29, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Einheriar", p, 27, trQuestVarGet("p"+p+"baseAttack"));
	zSetProtoUnitStat("Nereid", p, 27, trQuestVarGet("p"+p+"Attack"));
}

// SETS //



int yAddToSet(string to = "", string from = "") {
	int set = zModulo(16, trQuestVarGet(from));
	yAddToDatabase(to + set, from);
	return(set);
}

bool ySetContains(string db = "", int index = 0) {
	int set = zModulo(16, index);
	return(yDatabaseContains(db + set, index));
}

int ySetRemove(string db = "", int index = 0) {
	int set = zModulo(16, index);
	for(x=yGetDatabaseCount(db + set) - 1; >=0) {
		if (trQuestVarGet("zdatalite"+db+set+"index"+x) == index) {
			trQuestVarSet("zdatalite"+db+set+"pointer", x);
			yRemoveFromDatabase(db+set);
			return(set);
		}
	}
	return(-1);
}

int yGetSetCount(string db = "") {
	int count = 0;
	for(x = 15; >=0) {
		count = count + yGetDatabaseCount(db + x);
	}
	return(count);
}

int trUnitOwner() {
	for(x=0;<=12) {
		if (trUnitIsOwnedBy(x)) {
			return(x);
		}
	}
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


void spyFind() {
	while(trQuestVarGet("spySearch") < trGetNextUnitScenarioNameNumber()) {
		if (kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet("spySearch"), true)) == kbGetProtoUnitID("Spy Eye")){
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("spySearch"), true);
			trMutateSelected(kbGetProtoUnitID("Rocket"));
			int spy = modularCounterNext("spyFound");
			trQuestVarSet("spyEye" + spy, trQuestVarGet("spySearch"));
		}
		trQuestVarSet("spySearch", 1 + trQuestVarGet("spySearch"));
	}
	if (trQuestVarGet("spyFind") != trQuestVarGet("spyFound")) {
		trQuestVarSet("spyDieTimer", 1 + trQuestVarGet("spyDieTimer"));
	} else {
		trQuestVarSet("spyDieTimer", 0);
	}
	if (trQuestVarGet("spyDieTimer") >= 3) {
		while(trQuestVarGet("spyFound") != trQuestVarGet("spyFind")) {
			modularCounterNext("spyFound");
			trQuestVarSet("spyEye" + 1*trQuestVarGet("spyFound"), -1);
		}
		trQuestVarSet("spyDieTimer", 0);
	}
}

void ySilenceUnit(string db = "", float duration = 0.0) {
	if (yGetVar("playerCharacters", "silenceDuration") > 0) {
		ySetVar("playerCharacters", "silenceDuration", xsMax(duration, yGetVar("playerCharacters", "silenceDuration")));
	} else if ((kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet(db),true)) == kbGetProtoUnitID("Royal Guard Hero")) == false){
		ySetVar("playerCharacters", "silenceDuration", duration);
		int p = yGetVar("playerCharacters", "player");
		trQuestVarSet("p"+p+"silenced", 1 + trQuestVarGet("p"+p+"silenced"));
		ySetVar("playerCharacters", "silenceTime", trTime());
		if (yGetVar("playerCharacters", "silenceSFXIndex") == -1) {
			trTechInvokeGodPower(0, "spy", vector(0,0,0), vector(0,0,0));
			ySetVar("playerCharacters", "silenceSFXIndex", modularCounterNext("spyFind"));
		} else {
			trUnitSelectClear();
			trUnitSelect(""+1*yGetVar("playerCharacters", "silenceSFX"), true);
			trMutateSelected(kbGetProtoUnitID("UI Range Indicator Egypt SFX"));
		}
	}
}

void yStunUnit(string db = "", float duration = 0.0, bool spy = true) {
	if (trUnitPercentDamaged() < 100) {
		if (ySetContains("stunned", trQuestVarGet(db))) {
			int set = zModulo(16, trQuestVarGet(db));
			if (yGetVar("stunned" + set, "stunTime") < duration) {
				ySetVar("stunned" + set, "stunTime", duration);
			}
		} else if ((kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet(db),true)) == kbGetProtoUnitID("Royal Guard Hero")) == false){
			
			int type = kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet(db), true));
			int setNum = yAddToSet("stunned", db);
			
			yAddUpdateVar("stunned" + setNum, "stunTime", duration);
			yAddUpdateVar("stunned" + setNum, "stunSFX", -1);
			yAddUpdateVar("stunned" + setNum, "type", type);
			if (spy) {
				yAddUpdateVar("stunned" + setNum, "spy", 1);
				trTechGodPower(0, "spy", 1);
				trTechInvokeGodPower(0, "spy", vector(0,0,0), vector(0,0,0));
				yAddUpdateVar("stunned" + setNum, "stunSFXIndex", modularCounterNext("spyFind"));
			} else {
				yAddUpdateVar("stunned" + setNum, "spy", 0);
			}
			trMutateSelected(type);
			if (trUnitIsOwnedBy(5)) {
				trUnitSetStance("Passive");
			}
		}
	}
}

void yPoisonUnit(string db = "", int duration = 0, float damage = 3) {
	if (trUnitPercentDamaged() < 100) {
		if (ySetContains("poisoned", trQuestVarGet(db))) {
			int set = zModulo(16, trQuestVarGet(db));
			if (yGetVar("poisoned" + set, "poisonTime") < duration) {
				ySetVar("poisoned" + set, "poisonTime", duration);
				if (trCurrentPlayer() == trQuestVarGet("shadowstealerplayer") ||
					trCurrentPlayer() == trQuestVarGet("venomancerplayer")) {
					trUnitHighlight(duration, true);
				}
			}
			if (yGetVar("poisoned" + set, "poisonDamage") < damage) {
				ySetVar("poisoned" + set, "poisonDamage", duration);
			}
		} else if ((kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet(db),true)) == kbGetProtoUnitID("Royal Guard Hero")) == false){
			trTechGodPower(0, "spy", 1);
			trTechInvokeGodPower(0, "spy", vector(0,0,0), vector(0,0,0));
			int setNum = yAddToSet("poisoned", db);
			yAddUpdateVar("poisoned" + setNum, "poisonSFXIndex", modularCounterNext("spyFind"));
			yAddUpdateVar("poisoned" + setNum, "poisonTime", duration);
			yAddUpdateVar("poisoned" + setNum, "poisonSFX", -1);
			yAddUpdateVar("poisoned" + setNum, "poisonDamage", damage);
			if (trUnitIsOwnedBy(5)) {
				if (trCurrentPlayer() == trQuestVarGet("shadowstealerplayer")) {
					trUnitHighlight(duration, true);
				} else if (trCurrentPlayer() == trQuestVarGet("venomancerplayer")) {
					trUnitHighlight(duration, true);
					trUnitChangeName("Poison: " + 1*damage+":"+1*duration);
				}
			}
		}
	}
}

void timediff() {
	if (kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet("timelord"))) == -1){
		trQuestVarSet("timelord", trGetNextUnitScenarioNameNumber());
		trArmyDispatch("1, 10", "Pegasus", 1, trQuestVarGet("timeoldX"), 0, trQuestVarGet("timeoldZ"), 0, true);
		trUnitSelectClear();
		trUnitSelect("" + 1*trQuestVarGet("timelord"), true);
		trUnitConvert(0);
		trMutateSelected(kbGetProtoUnitID("Rocket"));
		trUnitMoveToPoint(50, 0, trQuestVarGet("timeoldZ"), -1, false);
		trQuestVarSet("timelordDirection", 1);
	} else {
		trVectorQuestVarSet("timenew", kbGetBlockPosition(""+1*trQuestVarGet("timelord")));
		float diff = xsAbs(trQuestVarGet("timenewX") - trQuestVarGet("timeoldX"));
		trUnitSelectClear();
		trUnitSelect("" + 1*trQuestVarGet("timelord"), true);
		if (diff > 0) {
			trQuestVarSet("timediff", diff);
			trQuestVarCopy("timeoldX", "timenewX");
			trQuestVarSet("timeLordWatch", trQuestVarGet("timeLordWatch") + trQuestVarGet("timediff"));
		} else {
			if (trQuestVarGet("timelordDirection") == 1) {
				trUnitMoveToPoint(50, 0, trQuestVarGet("timeoldZ"), -1, false);
			} else {
				trUnitMoveToPoint(0, 0, trQuestVarGet("timeoldZ"), -1, false);
			}
		}
		if (trQuestVarGet("timenewX") > 40 && trQuestVarGet("timelordDirection") == 1) {
			trQuestVarSet("timelordDirection", 0);
			trUnitMoveToPoint(0, 0, trQuestVarGet("timeoldZ"), -1, false);
		} else if (trQuestVarGet("timenewX") < 10 && trQuestVarGet("timelordDirection") == 0) {
			trQuestVarSet("timelordDirection", 1);
			trUnitMoveToPoint(50, 0, trQuestVarGet("timeoldZ"), -1, false);
		}
	}
}


void maintainStun() {
	trQuestVarSet("bossStunned", 0);
	for (y=15; >= 0) {
		yDatabasePointerDefault("stunned" + y);
		for(x=yGetDatabaseCount("stunned" + y); >0) {
			int name = yDatabaseNext("stunned" + y);
			if (trUnitAlive()==false) {
				yRemoveFromDatabase("stunned" + y);
				yRemoveUpdateVar("stunned" + y, "stunTime");
				yRemoveUpdateVar("stunned" + y, "stunSFX");
				yRemoveUpdateVar("stunned" + y, "stunSFXIndex");
				yRemoveUpdateVar("stunned" + y, "type");
				yRemoveUpdateVar("stunned" + y, "spy");
			} else {
				ySetVar("stunned" + y, "stunTime", yGetVar("stunned" + y, "stunTime") - trQuestVarGet("timediff"));
				if (trQuestVarGet("boss") > 0 && trUnitIsOwnedBy(5)) {
					trQuestVarSet("bossStunned", 1);
					trQuestVarSet("bossRecovery", trQuestVarGet("timediff") * (1.0 + trQuestVarGet("progression")));
					ySetVar("stunned" + y, "stunTime", yGetVar("stunned" + y, "stunTime") - trQuestVarGet("bossRecovery"));
				}
				if (yGetVar("stunned" + y, "stunTime") > 0) {
					trMutateSelected(1*yGetVar("stunned" + y, "type"));
					trUnitOverrideAnimation(2, 0, false, true, -1, 0);
					if (yGetVar("stunned" + y, "stunSFX") == -1 && 
						trQuestVarGet("spyFound") == trQuestVarGet("spyFind") &&
						yGetVar("stunned"+y, "spy") == 1) {
						ySetVar("stunned"+y, "stunSFX", trQuestVarGet("spyEye" + 1*yGetVar("stunned"+y, "stunSFXIndex")));
						trUnitSelectClear();
						trUnitSelect(""+1*yGetVar("stunned"+y, "stunSFX"), true);
						trMutateSelected(kbGetProtoUnitID("Shockwave stun effect"));
					}
				} else {
					if (trUnitIsOwnedBy(5)) {
						trUnitSetStance("Aggressive");
					}
					if (1*yGetVar("stunned"+y, "type") == kbGetProtoUnitID("Einheriar")) {
						trUnitChangeProtoUnit("Einheriar");
						trUnitSelectClear();
						trUnitSelect(""+1*trQuestVarGet("stunned"+y), true);
						trMutateSelected(kbGetProtoUnitID("Einheriar"));
					}
					if (yGetVar("stunned"+y, "spy") == 1) {
						trUnitSelectClear();
						trUnitSelect(""+1*yGetVar("stunned" + y, "stunSFX"), true);
						trUnitDestroy();
					}
					
					yRemoveFromDatabase("stunned" + y);
					yRemoveUpdateVar("stunned" + y, "stunTime");
					yRemoveUpdateVar("stunned" + y, "stunSFX");
					yRemoveUpdateVar("stunned" + y, "stunSFXIndex");
					yRemoveUpdateVar("stunned" + y, "type");
					yRemoveUpdateVar("stunned" + y, "spy");
				}
			}
		}
	}
}

void clearStun() {
	for (y=15; >= 0) {
		yDatabasePointerDefault("stunned" + y);
		for(x=yGetDatabaseCount("stunned" + y); >0) {
			yDatabaseNext("stunned" + y);
			
			if (yGetVar("stunned"+y, "spy") == 1) {
				trUnitSelectClear();
				trUnitSelect(""+1*yGetVar("stunned" + y, "stunSFX"), true);
				trUnitDestroy();
			}
		}
		yClearDatabase("stunned" + y);
	}
}

void yCleanseUnit(string db = "") {
	int y = 0;
	if (ySetContains("stunned", 1*trQuestVarGet(db))) {
		y = ySetRemove("stunned", 1*trQuestVarGet(db));
		
		if (yGetVar("stunned" + y, "spy") == 1) {
			trUnitSelectClear();
			trUnitSelect(""+1*yGetVar("stunned" + y, "stunSFX"), true);
			trUnitDestroy();
		}
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet(db), true);
		if (trUnitIsOwnedBy(5)) {
			trUnitSetStance("Aggressive");
		}
		yRemoveUpdateVar("stunned"+y, "stunTime");
		yRemoveUpdateVar("stunned"+y, "stunSFX");
		yRemoveUpdateVar("stunned"+y, "stunSFXIndex");
		yRemoveUpdateVar("stunned" + y, "type");
		yRemoveUpdateVar("stunned" + y, "spy");
	}
	if (ySetContains("poisoned", 1*trQuestVarGet(db))) {
		y = ySetRemove("poisoned", 1*trQuestVarGet(db));
		trUnitSelectClear();
		trUnitSelect(""+1*yGetVar("poisoned" + y, "poisonSFX"), true);
		trUnitDestroy();
		yRemoveUpdateVar("poisoned" + y, "poisonTime");
		yRemoveUpdateVar("poisoned" + y, "poisonSFX");
		yRemoveUpdateVar("poisoned" + y, "poisonSFXIndex");
		yRemoveUpdateVar("poisoned" + y, "poisonDamage");
	}
	if (yDatabaseContains("playerCharacters", 1*trQuestVarGet(db))) {
		if (yGetVar("playerCharacters", "silenceDuration") >0) {
			ySetVar("playerCharacters", "silenceDuration", 0);
			int p = trUnitOwner();
			trQuestVarSet("p"+p+"silenced", trQuestVarGet("p"+p+"silenced") - 1);
			trUnitSelectClear();
			trUnitSelect(""+1*yGetVar("playerCharacters", "silenceSFX"), true);
			trMutateSelected(kbGetProtoUnitID("Rocket"));
		}
	}
}


void poisonDamage() {
	for (y=15; >= 0) {
		yDatabasePointerDefault("poisoned" + y);
		for(x=yGetDatabaseCount("poisoned" + y); >0) {
			int name = yDatabaseNext("poisoned" + y);
			if (trUnitAlive()==false) {
				yRemoveFromDatabase("poisoned" + y);
				yRemoveUpdateVar("poisoned" + y, "poisonTime");
				yRemoveUpdateVar("poisoned" + y, "poisonSFX");
				yRemoveUpdateVar("poisoned" + y, "poisonFXIndex");
				yRemoveUpdateVar("poisoned" + y, "poisonDamage");
			} else {
				ySetVar("poisoned" + y, "poisonTime", yGetVar("poisoned" + y, "poisonTime") - 1);
				if (yGetVar("poisoned" + y, "poisonTime") > 0) {
					if (trCurrentPlayer() == trQuestVarGet("venomancerplayer") && trUnitIsOwnedBy(5)) {
						trUnitChangeName("Poison: " +1*yGetVar("poisoned"+y,"poisonDamage")+":"+1*yGetVar("poisoned"+y,"poisonTime"));
					}
					trDamageUnit(yGetVar("poisoned"+y, "poisonDamage"));
					if (yGetVar("poisoned" + y, "poisonSFX") == -1 && trQuestVarGet("spyFound") == trQuestVarGet("spyFind")) {
						ySetVar("poisoned"+y, "poisonSFX", trQuestVarGet("spyEye" + 1*yGetVar("poisoned"+y, "poisonSFXIndex")));
						trUnitSelectClear();
						trUnitSelect(""+1*yGetVar("poisoned"+y, "poisonSFX"), true);
						trMutateSelected(kbGetProtoUnitID("Poison SFX"));
					}
				} else {
					if (trCurrentPlayer() == trQuestVarGet("venomancerplayer") && trUnitIsOwnedBy(5)) {
						trUnitChangeName("Poison: --:--");
					}
					trUnitSelectClear();
					trUnitSelect(""+1*yGetVar("poisoned" + y, "poisonSFX"), true);
					trUnitDestroy();
					yRemoveFromDatabase("poisoned" + y);
					yRemoveUpdateVar("poisoned" + y, "poisonTime");
					yRemoveUpdateVar("poisoned" + y, "poisonSFX");
					yRemoveUpdateVar("poisoned" + y, "poisonSFXIndex");
					yRemoveUpdateVar("poisoned" + y, "poisonDamage");
				}
			}
		}
	}
}

void clearPoison() {
	for (y=15; >= 0) {
		yDatabasePointerDefault("poisoned" + y);
		for(x=yGetDatabaseCount("poisoned" + y); >0) {
			yDatabaseNext("poisoned" + y);
			if (trCurrentPlayer() == trQuestVarGet("venomancerplayer") && trUnitIsOwnedBy(5)) {
				trUnitChangeName("Poison: --:--");
			}
			trUnitSelectClear();
			trUnitSelect(""+1*yGetVar("poisoned" + y, "poisonSFX"), true);
			trUnitDestroy();
		}
		yClearDatabase("poisoned" + y);
	}
}

bool removeThunderblade() {
	if (kbGetBlockID(""+1*trQuestVarGet("thunderblade"), true) == -1 || trUnitAlive() == false) {
		ySetVar("thunderblade", "electrofieldSFX", 0);
		ySetVar("thunderblade", "superchargeSFX", 0);
		yRemoveFromDatabase("thunderblade");
		yRemoveUpdateVar("thunderblade", "electrofieldSFX");
		yRemoveUpdateVar("thunderblade", "electrofieldIndex");
		yRemoveUpdateVar("thunderblade", "superchargeSFX");
		yRemoveUpdateVar("thunderblade", "superchargeIndex");
		yRemoveUpdateVar("thunderblade", "attacking");
		return(true);
	}
	return(false);
}

bool removeFirewalker() {
	if (kbGetBlockID(""+1*trQuestVarGet("firewalker"), true) == -1 || trUnitAlive() == false) {
		ySetVar("firewalker", "rekindleSFX", 0);
		ySetVar("firewalker", "phoenixDiveSFX", 0);
		yRemoveFromDatabase("firewalker");
		yRemoveUpdateVar("firewalker", "xPos");
		yRemoveUpdateVar("firewalker", "zPos");
		yRemoveUpdateVar("firewalker", "rekindleSFX");
		yRemoveUpdateVar("firewalker", "rekindleIndex");
		yRemoveUpdateVar("firewalker", "xPosH");
		yRemoveUpdateVar("firewalker", "zPosH");
		yRemoveUpdateVar("firewalker", "phoenixDiveSFX");
		yRemoveUpdateVar("firewalker", "phoenixDiveIndex");
		yRemoveUpdateVar("firewalker", "jumping");
		return(true);
	}
	return(false);
}

bool removeIronbender() {
	if (kbGetBlockID(""+1*trQuestVarGet("ironbender"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("ironbender");
		yRemoveUpdateVar("ironbender", "shootWatch");
		yRemoveUpdateVar("ironbender", "shooting");
		return(true);
	}
	return(false);
}

bool removeLightrider() {
	if (kbGetBlockID(""+1*trQuestVarGet("lightrider"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("lightrider");
		yRemoveUpdateVar("lightrider", "AttackWatch");
		yRemoveUpdateVar("lightrider", "attacking");
		yRemoveUpdateVar("lightrider", "victorySFX");
		yRemoveUpdateVar("lightrider", "victoryIndex");
		yRemoveUpdateVar("lightrider", "searingSFX");
		yRemoveUpdateVar("lightrider", "searingIndex");
		yRemoveUpdateVar("lightrider", "posx");
		yRemoveUpdateVar("lightrider", "posz");
		return(true);
	}
	return(false);
}

bool removePotioneer() {
	if (kbGetBlockID(""+1*trQuestVarGet("potioneer"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("potioneer");
		yRemoveUpdateVar("potioneer", "potionCount");
		return(true);
	}
	return(false);
}

bool removeWindcutter() {
	if (kbGetBlockID(""+1*trQuestVarGet("windcutter"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("windcutter");
		yRemoveUpdateVar("windcutter", "firing");
		yRemoveUpdateVar("windcutter", "shootWatch");
		return(true);
	}
	return(false);
}

bool removeTimejumper() {
	if (kbGetBlockID(""+1*trQuestVarGet("timejumper"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("timejumper");
		yRemoveUpdateVar("timejumper", "ranged");
		yRemoveUpdateVar("timejumper", "attacking");
		yRemoveUpdateVar("timejumper", "attackNext");
		yRemoveUpdateVar("timejumper", "qBonus");
		yRemoveUpdateVar("timejumper", "wBonus");
		yRemoveUpdateVar("timejumper", "target");
		yRemoveUpdateVar("timejumper", "targetx");
		yRemoveUpdateVar("timejumper", "targetz");
		for(x=10; >0) {
			trUnitSelectClear();
			trUnitSelect(""+1*yGetVar("timejumper", "unit"+x), true);
			trUnitDestroy();
			yRemoveUpdateVar("timejumper", "pos"+x+"x");
			yRemoveUpdateVar("timejumper", "pos"+x+"z");
			yRemoveUpdateVar("timejumper", "health"+x);
			yRemoveUpdateVar("timejumper", "unit"+x);
		}
		return(true);
	}
	return(false);
}

bool removeShadowstealer() {
	if (kbGetBlockID(""+1*trQuestVarGet("shadowstealer"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("shadowstealer");
		return(true);
	}
	return(false);
}

bool removeVenomancer() {
	if (kbGetBlockID(""+1*trQuestVarGet("venomancer"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("venomancer");
		yRemoveUpdateVar("venomancer", "spearProgress");
		return(true);
	}
	return(false);
}

bool removeTidechaser() {
	if (kbGetBlockID(""+1*trQuestVarGet("tidechaser"), true) == -1 || trUnitAlive() == false) {
		if (yGetVar("tidechaser", "tail") == 2) {
			trQuestVarSet("tailwhipping", trQuestVarGet("tailwhipping") - 1);
		}
		yRemoveFromDatabase("tidechaser");
		yRemoveUpdateVar("tidechaser", "attackWatch");
		yRemoveUpdateVar("tidechaser", "tail");
		yRemoveUpdateVar("tidechaser", "huntSFX");
		yRemoveUpdateVar("tidechaser", "huntIndex");
		yRemoveUpdateVar("tidechaser", "target");
		yRemoveUpdateVar("tidechaser", "destx");
		yRemoveUpdateVar("tidechaser", "destz");
		yRemoveUpdateVar("tidechaser", "posx");
		yRemoveUpdateVar("tidechaser", "posz");
		yRemoveUpdateVar("tidechaser", "prevx");
		yRemoveUpdateVar("tidechaser", "prevz");
		yRemoveUpdateVar("tidechaser", "dirx");
		yRemoveUpdateVar("tidechaser", "dirz");
		yRemoveUpdateVar("tidechaser", "torrentActive");
		return(true);
	}
	return(false);
}

bool removeDeathbringer() {
	if (kbGetBlockID(""+1*trQuestVarGet("deathbringer"), true) == -1 || trUnitAlive() == false) {
		yRemoveFromDatabase("deathbringer");

		yRemoveUpdateVar("deathbringer", "dominationSFX");
		yRemoveUpdateVar("deathbringer", "dominationIndex");
		return(true);
	}
	return(false);
}


 bool removeEnemies() {
	if (kbGetBlockID(""+1*trQuestVarGet("enemies"), true) == -1 || trUnitAlive() == false) {
		int p = trQuestVarGet("deathbringerplayer");
		trQuestVarSet("posx", yGetVar("enemies", "posx"));
		trQuestVarSet("posz", yGetVar("enemies", "posz"));
		for(x=yGetDatabaseCount("deathbringer"); >0) {
			yDatabaseNext("deathbringer");
			if (removeDeathbringer()) {
				continue;
			} else if (zDistanceToVectorRootless("deathbringer", "pos") < 36) {
				trPlayerGrantResources(p, "favor", trQuestVarGet("deathbringerPassiveFavor") * trQuestVarGet("p"+p+"abilityDamage"));
				trDamageUnitPercent(0 - trQuestVarGet("deathbringerPassiveHeal") * trQuestVarGet("p"+p+"abilityDamage"));
			}
		}
		trQuestVarSet("kills", 1 + trQuestVarGet("kills"));
		for(p=4; >0) {
			if (trQuestVarGet("p"+p+"unique14") > 0) {
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("p"+p+"unit"), true);
				trDamageUnitPercent(0.0 - trQuestVarGet("p"+p+"unique14"));
			}
		}
		if (trQuestVarGet("harvestActive") == 1) {
			p = trQuestVarGet("shadowstealerplayer");
			trQuestVarSet("p"+p+"baseAttack", 1 + trQuestVarGet("p"+p+"baseAttack"));
			updateAttack(p);
		}
		if (trQuestVarGet("kills") >= trQuestVarGet("numHumans")) {
			trQuestVarSet("kills", 0);
			for(p=4;>0) {
				trPlayerGrantResources(p, "favor", 1);
			}
		}
		yRemoveFromDatabase("enemies");
		yRemoveUpdateVar("enemies", "electrofieldCount");
		yRemoveUpdateVar("enemies", "hero");
		yRemoveUpdateVar("enemies", "garrisoned");
		yRemoveUpdateVar("enemies", "posx");
		yRemoveUpdateVar("enemies", "posz");
		return(true);
	}
	return(false);
}


bool removePlayerCharacters() {
	if (kbGetBlockID(""+1*trQuestVarGet("playerCharacters"), true) == -1 || trUnitAlive() == false) {
		if (yGetVar("playerCharacters", "silenceDuration") > 0) {
			int p = yGetVar("playerCharacters", "player");
			trQuestVarSet("p"+p+"silenced", trQuestVarGet("p"+p+"silenced") - 1);
		}
		yRemoveFromDatabase("playerCharacters");
		yRemoveUpdateVar("playerCharacters", "accelerationSFX");
		yRemoveUpdateVar("playerCharacters", "accelerationSFXIndex");
		yRemoveUpdateVar("playerCharacters", "harvestSFX");
		yRemoveUpdateVar("playerCharacters", "harvestSFXIndex");
		yRemoveUpdateVar("playerCharacters", "silenceSFXIndex");
		yRemoveUpdateVar("playerCharacters", "silenceSFX");
		yRemoveUpdateVar("playerCharacters", "silenceDuration");
		yRemoveUpdateVar("playerCharacters", "silenceTime");
		yRemoveUpdateVar("playerCharacters", "player");
		return(true);
	}
	return(false);
}

void addPlayerCharacter(string db = "", int p = 0) {
	yAddToDatabase("playerCharacters", db);
	yAddUpdateVar("playerCharacters", "silenceSFXIndex", -1);
	yAddUpdateVar("playerCharacters", "silenceSFX", -1);
	yAddUpdateVar("playerCharacters", "harvestSFX", 0);
	yAddUpdateVar("playerCharacters", "harvestSFXIndex", -1);
	yAddUpdateVar("playerCharacters", "silenceDuration", 0);
	yAddUpdateVar("playerCharacters", "player", p);
}

void addPlayerUnit(string db = "", int p = 0) {
	yAddToDatabase("playerUnits", db);
	yAddUpdateVar("playerUnits", "player", p);
}

bool removePlayerUnits() {
	if (kbGetBlockID(""+1*trQuestVarGet("playerUnits"), true) == -1 || trUnitAlive() == false) {
		int p = trQuestVarGet("deathbringerplayer");
		trQuestVarSet("posx", yGetVar("playerUnits", "posx"));
		trQuestVarSet("posz", yGetVar("playerUnits", "posz"));
		for(x=yGetDatabaseCount("deathbringer"); >0) {
			yDatabaseNext("deathbringer");
			if (removeDeathbringer()) {
				continue;
			} else if (zDistanceToVectorRootless("deathbringer", "pos") < 36) {
				trPlayerGrantResources(p, "favor", trQuestVarGet("deathbringerPassiveFavor") * trQuestVarGet("p"+p+"abilityDamage"));
				trDamageUnitPercent(0 - trQuestVarGet("deathbringerPassiveHeal") * trQuestVarGet("p"+p+"abilityDamage"));
			}
		}
		yRemoveFromDatabase("playerUnits");
		yRemoveUpdateVar("playerUnits", "garrisoned");
		yRemoveUpdateVar("playerUnits", "player");
		yRemoveUpdateVar("playerUnits", "posx");
		yRemoveUpdateVar("playerUnits", "posz");
		
		return(true);
	}
	return(false);
}

bool removePlayerDuplicates() {
	if (kbGetBlockID(""+1*trQuestVarGet("playerDuplicates"), true) == -1) {
		yRemoveFromDatabase("playerDuplicates");
		yRemoveUpdateVar("playerDuplicates", "decay");
		return(true);
	}
	return(false);
}

void displaySpellStats(int p = 0) {
	for(norm=0;>1){}
	for(dec=0;>1){}
	string pr = "";
	norm = trQuestVarGet("p"+p+"abilityDamage");
	dec = zModulo(100, 100.0 * trQuestVarGet("p"+p+"abilityDamage"));
	pr = "Spell Power " + norm + ".";
	if (dec < 10) {
		pr = pr + "0" + dec;
	} else {
		pr = pr + dec;
	}
	norm = trQuestVarGet("p"+p+"abilityRange");
	dec = zModulo(100, 100.0 * trQuestVarGet("p"+p+"abilityRange"));
	pr = pr + " | Range " + norm + ".";
	if (dec < 10) {
		pr = pr + "0" + dec;
	} else {
		pr = pr + dec;
	}
	norm = trQuestVarGet("p"+p+"abilityDuration");
	dec = zModulo(100, 100.0 * trQuestVarGet("p"+p+"abilityDuration"));
	pr = pr + ": Duration " + norm + ".";
	if (dec < 10) {
		pr = pr + "0" + dec;
	} else {
		pr = pr + dec;
	}
	norm = trQuestVarGet("p"+p+"cooldownReduction");
	dec = zModulo(100, 100.0 * trQuestVarGet("p"+p+"cooldownReduction"));
	pr = pr + " | Cooldown " + norm + ".";
	if (dec < 10) {
		pr = pr + "0" + dec;
	} else {
		pr = pr + dec;
	}
	if (trCurrentPlayer() == p) {
		trSoundPlayFN("default","1",-1,pr,"");
	}
}

void refreshPlayerList() {
	trQuestVarSet("numHumans", 4);
	for(x=4; >0) {
		trQuestVarSet("playerTarget"+x, x);
	}
	for(p=4; >0) {
		if (kbIsPlayerHuman(p) == false || kbIsPlayerResigned(p) == true) {
			trQuestVarSet("temp", trQuestVarGet("playerTarget"+p));
			trQuestVarSet("playerTarget"+p, trQuestVarGet("playerTarget"+1*trQuestVarGet("numHumans")));
			trQuestVarSet("playerTarget"+1*trQuestVarGet("numHumans"), trQuestVarGet("temp"));
			trQuestVarSet("numHumans", trQuestVarGet("numHumans") - 1);
			for(x=yGetDatabaseCount("playerUnits"); >0) {
				yDatabaseNext("playerUnits");
				if (removePlayerUnits()) {
					continue;
				} else if (trUnitIsOwnedBy(p)) {
					trUnitDestroy();
				}
			}
		}
	}
	modularCounterInit("modularPlayersPointer", trQuestVarGet("numHumans"));
}

void cleanDatabase() {


	if (yGetDatabaseCount("playerCharacters") > 0) {
		yDatabaseNext("playerCharacters");
		if (removePlayerCharacters() == false) {
			if (yGetVar("playerCharacters", "silenceDuration") > 0) {
				int p = yGetVar("playerCharacters", "player");
				if (trTime() > yGetVar("playerCharacters", "silenceTime")) {
					ySetVar("playerCharacters", "silenceDuration", yGetVar("playerCharacters", "silenceDuration") - 1);
					ySetVar("playerCharacters", "silenceTime", trTime());
					if (yGetVar("playerCharacters", "silenceDuration") <= 0) {
						trQuestVarSet("p"+p+"silenced", trQuestVarGet("p"+p+"silenced") - 1);
						trUnitSelectClear();
						trUnitSelect(""+1*yGetVar("playerCharacters", "silenceSFX"), true);
						trMutateSelected(kbGetProtoUnitID("Rocket"));
					}
				}
				if (yGetVar("playerCharacters", "silenceSFX") == -1) {
					if (trQuestVarGet("spyFind") == trQuestVarGet("spyFound")) {
						ySetVar("playerCharacters", "silenceSFX", trQuestVarGet("spyEye"+1*yGetVar("playerCharacters", "silenceSFXIndex")));
						trUnitSelectClear();
						trUnitSelect(""+1*yGetVar("playerCharacters", "silenceSFX"), true);
						trMutateSelected(kbGetProtoUnitID("UI Range Indicator Egypt SFX"));
					}
				}
			}
		}
	}
}


void zArmyDeploy(string db = "", int p = 0, string r = "", string v = "") {
	trUnitSelectClear();
	trQuestVarSet("newUnit", trGetNextUnitScenarioNameNumber());
	yAddToDatabase(db, "newUnit");
	trArmyDispatch("1,10", r, 1,trVectorQuestVarGetX(v),trVectorQuestVarGetY(v),trVectorQuestVarGetZ(v), 180, true);
	trUnitSelect(""+1*trQuestVarGet("newUnit"), true);
	trUnitConvert(p);
}

void setupStadiumAttach() {
	unitTransform("Bridge", "Relic");
	unitTransform("UI Range Indicator Greek SFX", "Hero Greek Achilles");
	int relic = kbGetProtoUnitID("Relic");
	for(x=128; >48) {
		trUnitSelectClear();
		trUnitSelectByID(x+80);
		trImmediateUnitGarrison(""+x);
		trUnitSelectClear();
		trUnitSelectByID(x);
		trUnitSetStance("Passive");
	}
	unitTransform("Relic", "Bridge");
	unitTransform("UI Range Indicator Egypt SFX", "Hero Greek Achilles");
	for(x=496; >256) {
		trUnitSelectClear();
		trUnitSelectByID(x+240);
		trMutateSelected(relic);
		trImmediateUnitGarrison(""+x);
		trDamageUnitPercent(100);
		trUnitSelectClear();
		trUnitSelectByID(x);
		trUnitSetStance("Passive");
	}
	unitTransform("Relic", "Villager Egyptian");
	for(x=765; >759) {
		trUnitSelectClear();
		trUnitSelectByID(x+6);
		trMutateSelected(relic);
		trImmediateUnitGarrison(""+x);
		trUnitSelectClear();
		trUnitSelectByID(x);
		trUnitSetStance("Passive");
	}
	unitTransform("Relic", "Rocket");
	unitTransform("Hero Greek Achilles", "Wadjet Spit");
}


void evilCopyStats() {
	int c = 0;
	for(p=4; >0) {
		if (trQuestVarGet("p"+p+"character") > 0) {
			c = trQuestVarGet("p"+p+"character");
			zSetProtoUnitStat(trStringQuestVarGet("proto"+c), 5, 0, trQuestVarGet("p"+p+"health"));
			zSetProtoUnitStat(trStringQuestVarGet("proto"+c), 5, 1, trQuestVarGet("p"+p+"speed"));
			zSetProtoUnitStat(trStringQuestVarGet("proto"+c), 5, 13, trQuestVarGet("p"+p+"numProjectiles"));
			zSetProtoUnitStat(trStringQuestVarGet("proto"+c), 5, 29, trQuestVarGet("p"+p+"baseAttack"));
			zSetProtoUnitStat(trStringQuestVarGet("proto"+c), 5, 31, trQuestVarGet("p"+p+"baseAttack"));
		}
		if (trQuestVarGet("p"+p+"character") == 12) {
			zSetProtoUnitStat("Minion", 5, 0, trQuestVarGet("p"+p+"health")*0.2);
		}
	}
}


void checkForFreeze() {
	int UnitID = 0;
	int old = xsGetContextPlayer();
	xsSetContextPlayer(5);
	for(x=xsMin(3, yGetDatabaseCount("enemies")); >0) {
		UnitID = yDatabaseNext("enemies");
		if (removeEnemies()) {
			continue;
		}
		trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet("enemies"), true));
		ySetVar("enemies", "posx", trQuestVarGet("posx"));
		ySetVar("enemies", "posz", trQuestVarGet("posz"));
		if (kbUnitGetActionType(UnitID) == 25) {
			trUnitConvert(0);
			trUnitConvert(5);
			yStunUnit("enemies", 3);
			trSoundPlayFN("woodcrush3.wav", "1", -1, "","");
		}
	}
	int p = 0;
	for (x=xsMin(3,yGetDatabaseCount("playerUnits")); >0) {
		UnitID = yDatabaseNext("playerUnits");
		if (removePlayerUnits()) {
			continue;
		}
		trVectorQuestVarSet("pos", kbGetBlockPosition(""+1*trQuestVarGet("playerUnits"), true));
		ySetVar("playerUnits", "posx", trQuestVarGet("posx"));
		ySetVar("playerUnits", "posz", trQuestVarGet("posz"));
		p = yGetVar("playerUnits", "player");
		xsSetContextPlayer(p);
		if (kbUnitGetActionType(UnitID) == 25) {
			trUnitConvert(0);
			trUnitConvert(p);
			yStunUnit("playerUnits", 3);
			trSoundPlayFN("woodcrush3.wav", "1", -1, "","");
			if (trCurrentPlayer() == p) {
				trCameraShake(1.0, 0.25);
			}
		}
	}
	xsSetContextPlayer(old);
}

void silence() {
	for(p=4; >0) {
		if (trQuestVarGet("p"+p+"silenced") > 0 && trQuestVarGet("p"+p+"silenceStatus") == 0) {
			if (trQuestVarGet("play") == 1) {
				trSoundPlayFN("frostgiantmove1.wav", "1", -1, "", "");
				trChatSend(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has been silenced!");
			}
			trPlayerKillAllGodPowers(p);
		} else if (trQuestVarGet("p"+p+"silenced") == 0 && trQuestVarGet("p"+p+"silenceStatus") > 0) {
			if (trQuestVarGet("p"+p+"q") == 0) {
				trTechGodPower(p, trStringQuestVarGet("p"+p+"q"), 1);
			}
			if (trQuestVarGet("p"+p+"w") == 0) {
				trTechGodPower(p, trStringQuestVarGet("p"+p+"w"), 1);
			}
			if (trQuestVarGet("p"+p+"e") == 0) {
				trTechGodPower(p, trStringQuestVarGet("p"+p+"e"), 1);
			}
		}
		trQuestVarCopy("p"+p+"silenceStatus", "p"+p+"silenced");
	}
}

rule no_specials
highFrequency
active
{
	if (trTime() >= 1 + trQuestVarGet("no_specials_timer")) {
		trQuestVarSet("no_specials_timer", trTime());
		for(p=5; >0) {
			trModifyProtounit("Mummy", p, 9, -99990);
			trModifyProtounit("Mummy", p, 9, 99999);
			trModifyProtounit("Lampades", p, 9, -99990);
			trModifyProtounit("Lampades", p, 9, 99999);
			trModifyProtounit("Cyclops", p, 9, -99990);
			trModifyProtounit("Cyclops", p, 9, 99999);
			trModifyProtounit("Heka Gigantes", p, 9, -99990);
			trModifyProtounit("Heka Gigantes", p, 9, 99999);
			trModifyProtounit("Nereid", p, 9, -99990);
			trModifyProtounit("Nereid", p, 9, 99999);
			trModifyProtounit("Einheriar", p, 9, -99990);
			trModifyProtounit("Einheriar", p, 9, 99999);
			if (trPlayerResourceCount(p, "favor") > trQuestVarGet("p"+p+"ultCost")) {
				trPlayerGrantResources(p, "favor", trQuestVarGet("p"+p+"ultCost") - trPlayerResourceCount(p, "favor"));
			}
		}
		
	}
}

void playerDie(int p = 0) {
	if (trQuestVarGet("p"+p+"revive") <= 0 && trQuestVarGet("play") == 1) {
		trQuestVarSet("deathCount", 1 + trQuestVarGet("deathCount"));
		trQuestVarSet("p"+p+"dead", 1);
		trSoundPlayFN("lightningstrike"+p+".wav", "1", -1, "","");
		trChatSend(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has died!");
		trChatSend(0, "They will revive after the round ends.");
		trQuestVarSet("p"+p+"silenced", 1 + trQuestVarGet("p"+p+"silenced"));
		if (trCurrentPlayer() == p) {
			trMessageSetText("You have died! You will revive when the round ends.");
		}
	} else {
		if (trQuestVarGet("play") == 1) {
			trQuestVarSet("p"+p+"revive", 0 + trQuestVarGet("p"+p+"revive") - 1);
			trChatSend(0, "<color={Playercolor("+p+")}>{Playername("+p+")}</color> has used a revive!");
			trChatSend(0, "("+1*trQuestVarGet("p"+p+"revive")+" left this round)");
			trSoundPlayFN("herorevived.wav", "1", -1, "", "");
			trSetCivilizationNameOverride(p, "Revives: " +1*trQuestVarGet("p"+p+"revive"));
		}
		trQuestVarSet("next", trGetNextUnitScenarioNameNumber());
		trArmyDispatch("1,10", "Dwarf", 1, 55,0,55,0,true);
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("next"), true);
		yAddToDatabase(trStringQuestVarGet("character"+1*trQuestVarGet("p"+p+"character")), "next");
		addPlayerUnit("next", p);
		addPlayerCharacter("next", p);
		trQuestVarSet("p"+p+"unit", trQuestVarGet("next"));
		trUnitChangeName("{Playername("+p+")}");
		trUnitConvert(p);
		trUnitChangeProtoUnit(trStringQuestVarGet("proto"+1*trQuestVarGet("p"+p+"character")));
	}
}


rule death
highFrequency
inactive
{
	int x = modularCounterNext("modularPlayersPointer");
	int p = trQuestVarGet("playerTarget"+x);
	if (playerIsPlaying(p) && trQuestVarGet("p"+p+"dead") == 0) {
		if (kbGetUnitBaseTypeID(kbGetBlockID(""+1*trQuestVarGet("p"+p+"unit"))) == -1) {
			playerDie(p);
		} else {
			trUnitSelectClear();
			trUnitSelect(""+1*trQuestVarGet("p"+p+"unit"), true);
			if (trUnitDead()) {
				playerDie(p);
			}
		}
	}
	if (trQuestVarGet("deathCount") == trQuestVarGet("numHumans")) {
		map("q", "game", "");
		map("w", "game", "");
		map("e", "game", "");
		for(p=4; >0) {
			trSetPlayerDefeated(p);
		}
		trSetPlayerWon(5);
		trEndGame();
	}
}

rule initializeEverything
highFrequency
active
runImmediately
{
	trQuestVarSet("lighting0", 1);
	trStringQuestVarSet("lighting0", "default");

	trQuestVarSet("arenaCenterX", 55);
	trQuestVarSet("arenaCenterZ", 55);

	trStringQuestVarSet("character1", "Thunderblade");
	trStringQuestVarSet("character2", "Firewalker");
	trStringQuestVarSet("character3", "Lightrider");
	trStringQuestVarSet("character4", "Ironbender");
	trStringQuestVarSet("character5", "Windcutter");
	trStringQuestVarSet("character6", "Potioneer");
	trStringQuestVarSet("character7", "Shadowstealer");
	trStringQuestVarSet("character8", "Venomancer");
	trStringQuestVarSet("character9", "Snowshaper");
	trStringQuestVarSet("character10", "Tidechaser");
	trStringQuestVarSet("character11", "Timejumper");
	trStringQuestVarSet("character12", "Deathbringer");

	trStringQuestVarSet("description1", "A close-ranged fighter with lots of area damage and stuns.");
	trStringQuestVarSet("description2", "A fast fighter that leaves behind trails of fire.");
	trStringQuestVarSet("description3", "A healer that can tank and stun enemies.");
	trStringQuestVarSet("description4", "A slow, mid-ranged fighter with an arsenal of weapons.");
	trStringQuestVarSet("description5", "A long-ranged archer that can teleport himself and enemies.");
	trStringQuestVarSet("description6", "A versatile support with a variety of utility abilities.");
	trStringQuestVarSet("description7", "A rogue that gains permanent stats from kills.");
	trStringQuestVarSet("description8", "A spellcaster with high damage over time.");
	trStringQuestVarSet("description9", "A spellcaster that has large freezing abilities.");
	trStringQuestVarSet("description10", "A hit-and-run fighter with powerful disruption tools.");
	trStringQuestVarSet("description11", "An assassin who bends space and time.");
	trStringQuestVarSet("description12", "A tanky fighter that gains strength from the souls of the dead.");

	trStringQuestVarSet("proto1", "Royal Guard");
	trStringQuestVarSet("proto2", "Anubite");
	trStringQuestVarSet("proto3", "Valkyrie");
	trStringQuestVarSet("proto4", "Fire Lance");
	trStringQuestVarSet("proto5", "Archer Atlantean");
	trStringQuestVarSet("proto6", "Throwing Axeman");
	trStringQuestVarSet("proto7", "Swordsman");
	trStringQuestVarSet("proto8", "Peltast");
	trStringQuestVarSet("proto9", "Lampades");
	trStringQuestVarSet("proto10", "Nereid");
	trStringQuestVarSet("proto11", "Myrmidon");
	trStringQuestVarSet("proto12", "Einheriar");

	trQuestVarSet("character1ranged", 0);
	trQuestVarSet("character2ranged", 0);
	trQuestVarSet("character3ranged", 0);
	trQuestVarSet("character4ranged", 1);
	trQuestVarSet("character5ranged", 1);
	trQuestVarSet("character6ranged", 1);
	trQuestVarSet("character7ranged", 0);
	trQuestVarSet("character8ranged", 1);
	trQuestVarSet("character9ranged", 1);
	trQuestVarSet("character10ranged", 0);
	trQuestVarSet("character11ranged", 0);
	trQuestVarSet("character12ranged", 0);

	trQuestVarSet("numHumans", 0);

	trRevealEntireMap();
	trSetFogAndBlackmap(false, false);
	trSetObscuredUnits(false);

	modularCounterInit("spyFind", 256);
	modularCounterInit("spyFound", 256);
	trVectorQuestVarSet("timeOld", xsVectorSet(9, 10, 5));
	trVectorQuestVarSet("gate1", xsVectorSet(79, 0, 79));
	trVectorQuestVarSet("gate2", xsVectorSet(79, 0, 31));
	trVectorQuestVarSet("gate3", xsVectorSet(31, 0, 31));
	trVectorQuestVarSet("gate4", xsVectorSet(31, 0, 79));
	trQuestVarSet("timelord", -1);
	trPlayerSetDiplomacy(0, 5, "Enemy");
	trTechSetStatus(0, 304, 4);
	trModifyProtounit("Curse SFX", 1, 8, 7);

	trModifyProtounit("Wall Long", 0, 0, 999999);
	trModifyProtounit("Gate", 5, 0, 999999);
	trModifyProtounit("Phoenix", 5, 0, 999999);
	trModifyProtounit("Gate", 5, 24, 1);
	trModifyProtounit("Gate", 5, 25, 1);
	trModifyProtounit("Gate", 5, 26, 1);
	trModifyProtounit("Helepolis", 0, 55, 2);

	trModifyProtounit("Ball of Fire", 0, 8, -99);

	trUnitSelectClear();
	trQuestVarSet("wallPointer", 1);
	trQuestVarSet("gatePointer", 1);
	for(x=16; >0) {
		if (kbGetUnitBaseTypeID(x) == kbGetProtoUnitID("Wall Long")) {
			trQuestVarSet("arenawall"+1*trQuestVarGet("wallPointer"), x);
			trQuestVarSet("wallpointer", 1 + trQuestVarGet("wallpointer"));
			trQuestVarSet("arenaBorder"+x, 0);
		} else {
			trQuestVarSet("arenagate"+1*trQuestVarGet("gatePointer"), x);
			trQuestVarSet("gatepointer", 1 + trQuestVarGet("gatepointer"));
			trQuestVarSet("arenaBorder"+x, 1);
		}
	}

	for(p=5; >=0) {
		zInitProtoUnitStat("Ball of Fire Impact", p, 8, 5);

		trModifyProtounit("Wadjet Spit", p, 0, 999999);
		trModifyProtounit("Relic", p, 0, 999999);

		trModifyProtounit("Hero Greek Achilles", p, 5, 10);
		zInitProtoUnitStat("Ball of Fire", p, 1, 30);
		zInitProtoUnitStat("Ballista Shot", p, 1, 30);
		zInitProtoUnitStat("Stymph Bird Feather", p, 1, 30);
		zInitProtoUnitStat("Petosuchus Projectile", p, 1, 30);
		zInitProtoUnitStat("Priest Projectile", p, 1, 30);
		zInitProtoUnitStat("Sling Stone", p, 1, 30);
		zInitProtoUnitStat("Wadjet Spit", p, 1, 30);
		zInitProtoUnitStat("Lampades Bolt", p, 1, 30);
		trModifyProtounit("Stymph Bird Feather", p, 8, 10);
		trModifyProtounit("Nereid", p, 55, 1.0);

		trModifyProtounit("Transport Ship Greek", p, 55, 4.0);
		trModifyProtounit("Royal Guard", p, 24, -1);
		trModifyProtounit("Royal Guard Hero", p, 24, -1);
		trModifyProtounit("Anubite", p, 24, -1);
		trModifyProtounit("Valkyrie", p, 24, -1);
		trModifyProtounit("Fire Lance", p, 24, -1);
		trModifyProtounit("Archer Atlantean", p, 24, -1);
		trModifyProtounit("Throwing Axeman", p, 24, -1);
		trModifyProtounit("Swordsman", p, 24, -1);
		trModifyProtounit("Peltast", p, 24, -1);
		trModifyProtounit("Lampades", p, 24, -1);
		trModifyProtounit("Nereid", p, 24, -1);
		trModifyProtounit("Frost Giant", p, 24, -1);
		trModifyProtounit("Myrmidon", p, 24, -1);
		trModifyProtounit("Einheriar", p, 24, -1);

		trModifyProtounit("Royal Guard", p, 25, -1);
		trModifyProtounit("Royal Guard Hero", p, 25, -1);
		trModifyProtounit("Anubite", p, 25, -1);
		trModifyProtounit("Valkyrie", p, 25, -1);
		trModifyProtounit("Fire Lance", p, 25, -1);
		trModifyProtounit("Archer Atlantean", p, 25, -1);
		trModifyProtounit("Throwing Axeman", p, 25, -1);
		trModifyProtounit("Swordsman", p, 25, -1);
		trModifyProtounit("Peltast", p, 25, -1);
		trModifyProtounit("Lampades", p, 25, -1);
		trModifyProtounit("Nereid", p, 25, -1);
		trModifyProtounit("Frost Giant", p, 25, -1);
		trModifyProtounit("Myrmidon", p, 25, -1);
		trModifyProtounit("Einheriar", p, 25, -1);

		trModifyProtounit("Royal Guard", p, 26, -1);
		trModifyProtounit("Royal Guard Hero", p, 26, -1);
		trModifyProtounit("Anubite", p, 26, -1);
		trModifyProtounit("Valkyrie", p, 26, -1);
		trModifyProtounit("Fire Lance", p, 26, -1);
		trModifyProtounit("Archer Atlantean", p, 26, -1);
		trModifyProtounit("Throwing Axeman", p, 26, -1);
		trModifyProtounit("Swordsman", p, 26, -1);
		trModifyProtounit("Peltast", p, 26, -1);
		trModifyProtounit("Lampades", p, 26, -1);
		trModifyProtounit("Nereid", p, 26, -1);
		trModifyProtounit("Frost Giant", p, 24, -1);
		trModifyProtounit("Myrmidon", p, 26, -1);
		trModifyProtounit("Einheriar", p, 26, -1);

		trModifyProtounit("Royal Guard", p, 0, 880);
		trModifyProtounit("Royal Guard", p, 27, 30);
		trModifyProtounit("Royal Guard", p, 35, -1);
		trModifyProtounit("Royal Guard", p, 36, -1);
		zInitProtoUnitStat("Royal Guard", p, 0, 1000);
		zInitProtoUnitStat("Royal Guard", p, 27, 40);
		zInitProtoUnitStat("Royal Guard", p, 1, 4.6);

		trModifyProtounit("Royal Guard Hero", p, 0, 1865);
		trModifyProtounit("Royal Guard Hero", p, 27, 30);
		trModifyProtounit("Royal Guard Hero", p, 35, -1);
		trModifyProtounit("Royal Guard Hero", p, 36, -1);
		zInitProtoUnitStat("Royal Guard Hero", p, 0, 2000);
		zInitProtoUnitStat("Royal Guard Hero", p, 27, 40);
		zInitProtoUnitStat("Royal Guard Hero", p, 1, 4.6);

		trModifyProtounit("Anubite", p, 0, 725);
		trModifyProtounit("Anubite", p, 27, 34.4);
		trModifyProtounit("Anubite", p, 33, -2);
		trModifyProtounit("Anubite", p, 34, 0.5);
		zInitProtoUnitStat("Anubite", p, 0, 1000);
		zInitProtoUnitStat("Anubite", p, 27, 50);
		zInitProtoUnitStat("Anubite", p, 1, 5.3);

		trModifyProtounit("Valkyrie", p, 14, -1.0);
		trModifyProtounit("Valkyrie", p, 15, -21);
		trModifyProtounit("Valkyrie", p, 0, 825);
		trModifyProtounit("Valkyrie", p, 27, 22);
		trModifyProtounit("Valkyrie", p, 33, -2);
		trModifyProtounit("Valkyrie", p, 34, 0.5);
		zInitProtoUnitStat("Valkyrie", p, 0, 1200);
		zInitProtoUnitStat("Valkyrie", p, 27, 40);
		zInitProtoUnitStat("Valkyrie", p, 1, 5.5);

		trModifyProtounit("Fire Lance", p, 0, 835);
		trModifyProtounit("Fire Lance", p, 31, -5);
		trModifyProtounit("Fire Lance", p, 32, 38);
		trModifyProtounit("Fire Lance", p, 11, -8);
		trModifyProtounit("Fire Lance", p, 12, -3);
		zInitProtoUnitStat("Fire Lance", p, 0, 900);
		zInitProtoUnitStat("Fire Lance", p, 32, 50);
		zInitProtoUnitStat("Fire Lance", p, 11, 12);
		zInitProtoUnitStat("Fire Lance", p, 1, 3.6);
		zInitProtoUnitStat("Fire Lance", p, 13, 1);

		trModifyProtounit("Archer Atlantean", p, 0, 840);
		trModifyProtounit("Archer Atlantean", p, 31, 24);
		trModifyProtounit("Archer Atlantean", p, 11, -4);
		zInitProtoUnitStat("Archer Atlantean", p, 0, 900);
		zInitProtoUnitStat("Archer Atlantean", p, 31, 30);
		zInitProtoUnitStat("Archer Atlantean", p, 11, 16);
		zInitProtoUnitStat("Archer Atlantean", p, 1, 3.75);
		zInitProtoUnitStat("Archer Atlantean", p, 13, 1);

		trModifyProtounit("Throwing Axeman", p, 0, 935);
		trModifyProtounit("Throwing Axeman", p, 30, 25.5);
		trModifyProtounit("Throwing Axeman", p, 11, 7);
		trModifyProtounit("Throwing Axeman", p, 47, -0.5);
		zInitProtoUnitStat("Throwing Axeman", p, 0, 1000);
		zInitProtoUnitStat("Throwing Axeman", p, 30, 30);
		zInitProtoUnitStat("Throwing Axeman", p, 11, 16);
		zInitProtoUnitStat("Throwing Axeman", p, 1, 4.0);
		zInitProtoUnitStat("Throwing Axeman", p, 13, 1);

		trModifyProtounit("Swordsman", p, 0, 690);
		trModifyProtounit("Swordsman", p, 27, 22);
		trModifyProtounit("Swordsman", p, 1, 0.5);
		zInitProtoUnitStat("Swordsman", p, 0, 800);
		zInitProtoUnitStat("Swordsman", p, 27, 30);
		zInitProtoUnitStat("Swordsman", p, 1, 5.0);

		trModifyProtounit("Peltast", p, 0, 930);
		trModifyProtounit("Peltast", p, 31, 17);
		trModifyProtounit("Peltast", p, 11, 0);
		trModifyProtounit("Peltast", p, 48, -3);
		zInitProtoUnitStat("Peltast", p, 0, 900);
		zInitProtoUnitStat("Peltast", p, 31, 20);
		zInitProtoUnitStat("Peltast", p, 11, 16);
		zInitProtoUnitStat("Peltast", p, 1, 4.0);
		zInitProtoUnitStat("Peltast", p, 13, 1);

		trModifyProtounit("Lampades", p, 0, 650);
		trModifyProtounit("Lampades", p, 31, 18);
		trModifyProtounit("Lampades", p, 32, -10);
		trModifyProtounit("Lampades", p, 44, -1);
		trModifyProtounit("Lampades", p, 45, 0.75);
		trModifyProtounit("Lampades", p, 11, 6);
		zInitProtoUnitStat("Lampades", p, 0, 1000);
		zInitProtoUnitStat("Lampades", p, 31, 30);
		zInitProtoUnitStat("Lampades", p, 11, 16);
		zInitProtoUnitStat("Lampades", p, 1, 4.3);
		zInitProtoUnitStat("Lampades", p, 13, 1);

		trModifyProtounit("Nereid", p, 0, 600);
		trModifyProtounit("Nereid", p, 27, 25);
		trModifyProtounit("Nereid", p, 33, -6);
		trModifyProtounit("Nereid", p, 34, 0.5);
		zInitProtoUnitStat("Nereid", p, 0, 1000);
		zInitProtoUnitStat("Nereid", p, 27, 50);
		zInitProtoUnitStat("Nereid", p, 1, 5.0);

		trModifyProtounit("Myrmidon", p, 0, 880);
		trModifyProtounit("Myrmidon", p, 27, -10);
		trModifyProtounit("Myrmidon", p, 29, 50);
		zInitProtoUnitStat("Myrmidon", p, 0, 1000);
		zInitProtoUnitStat("Myrmidon", p, 29, 50);
		zInitProtoUnitStat("Myrmidon", p, 1, 4.3);

		trModifyProtounit("Einheriar", p, 0, 1225);
		trModifyProtounit("Einheriar", p, 27, 35);
		trModifyProtounit("Einheriar", p, 33, -1);
		trModifyProtounit("Einheriar", p, 34, 0.5);
		zInitProtoUnitStat("Einheriar", p, 0, 1500);
		zInitProtoUnitStat("Einheriar", p, 27, 50);
		zInitProtoUnitStat("Einheriar", p, 1, 3.5);


		trModifyProtounit("Minion", p, 0, 160);
		trModifyProtounit("Minion", p, 8, -99);
		zInitProtoUnitStat("Minion", p, 0, 300);

		zSetProtoUnitStat("Petosuchus Projectile", p, 1, 15);
		trModifyProtounit("Petosuchus Projectile", p, 8, 2);
		
		trQuestVarSet("p"+p+"maxChoices", 1);
	}

	trModifyProtounit("Hero Birth", 0, 0, 999999);

	trQuestVarSet("numHumans", 4);

	trModifyProtounit("Animal Attractor", 0, 55, 4.0);

	for(p=4; >0) {
		trQuestVarSet("p"+p+"unique24", 0);
		trQuestVarSet("p"+p+"q", 0);
		trQuestVarSet("p"+p+"w", 0);
		trQuestVarSet("p"+p+"e", 0);
		trQuestVarSet("p"+p+"cooldownReduction", 1.0);
		trQuestVarSet("playerTarget"+p, p);
		trSetCivAndCulture(p, 1, 0);
		trTechSetStatus(p, 115, 4);
		trTechSetStatus(p, 91, 4);
		trPlayerTechTreeEnabledGodPowers(p, false);

		trForbidProtounit(p, "Swordsman Hero");
		trForbidProtounit(p, "Trident Soldier Hero");
		trForbidProtounit(p, "Archer Atlantean Hero");
		trForbidProtounit(p, "Royal Guard Hero");
		trForbidProtounit(p, "Wall Connector");
		trForbidProtounit(p, "Dock");
		trForbidProtounit(p, "Settlement Level 1");
		trForbidProtounit(p, "House");
		trForbidProtounit(p, "Granary");
		trForbidProtounit(p, "Mining Camp");
		trForbidProtounit(p, "Lumber Camp");
		trForbidProtounit(p, "Monument");
		trForbidProtounit(p, "Temple");
		trForbidProtounit(p, "Wonder");
		trForbidProtounit(p, "Market");
		trForbidProtounit(p, "Dwarf Foundry");
		trForbidProtounit(p, "Armory");
		trForbidProtounit(p, "Hill Fort");
		trForbidProtounit(p, "Tower");
		trForbidProtounit(p, "Longhouse");


		trQuestVarSet("p"+p+"abilityDuration", 1);
		trQuestVarSet("p"+p+"abilityDamage", 1);
		trQuestVarSet("p"+p+"abilityRange", 1);
		trQuestVarSet("p"+p+"numProjectiles", 1);

		trPlayerSetDiplomacy(0, p, "Enemy");
		trPlayerSetDiplomacy(p, 0, "Neutral");
		trPlayerSetDiplomacy(p, 5, "Enemy");
		trPlayerSetDiplomacy(5, p, "Enemy");

		for(z=4;>0) {
			if ((z == p) == false) {
				trPlayerSetDiplomacy(z, p, "Ally");
			}
		}

		trModifyProtounit("Villager Egyptian", p, 6, -1);

		trModifyProtounit("Folstag Flag Bearer", p, 55,4.0);

		trModifyProtounit("Vision SFX", p, 0, -9999);
		trModifyProtounit("Vision Revealer", p, 6, 1000);
		trModifyProtounit("Fire Lance Projectile", p, 6, 99);
		
		trModifyProtounit("Animal Attractor", p, 55, 4.0);


		trModifyProtounit("Frost Giant", p, 0, 400);
		trModifyProtounit("Frost Giant", p, 1, 0.5);
		trModifyProtounit("Frost Giant", p, 27, 12);
		trModifyProtounit("Frost Giant", p, 33, -2);
		trModifyProtounit("Frost Giant", p, 34, 0.5);
		zInitProtoUnitStat("Frost Giant", p, 0, 1000);
		zInitProtoUnitStat("Frost Giant", p, 27, 30);
		zInitProtoUnitStat("Frost Giant", p, 1, 4.3);
		zInitProtoUnitStat("Frost Giant", p, 9, 15);

		trModifyProtounit("Hero Birth", p, 0, 999999);

		trTechSetStatus(p, 297, 4);

		trModifyProtounit("Frost Drift", p, 8, -99);

				
		zSetProtoUnitStat("Stymph Bird Feather", p, 1, 15);
		zSetProtoUnitStat("Ballista Shot", p, 1, 15);
		zSetProtoUnitStat("Ball of Fire", p, 1, 15);

		trModifyProtounit("Ballista Shot", p, 8, 2);
		trModifyProtounit("Ball of Fire", p, 8, 2);
		
	
		if (kbIsPlayerHuman(p) == false || kbIsPlayerResigned(p) == true) {
			trQuestVarSet("temp", trQuestVarGet("playerTarget"+p));
			trQuestVarSet("playerTarget"+p, trQuestVarGet("playerTarget"+1*trQuestVarGet("numHumans")));
			trQuestVarSet("playerTarget"+1*trQuestVarGet("numHumans"), trQuestVarGet("temp"));
			trQuestVarSet("numHumans", trQuestVarGet("numHumans") - 1);
			aiSet("NoAI", p);
		} else {
			trTechSetStatus(5, 78, 4);
			trQuestVarSet("p"+p+"dead", 0);
			trModifyProtounit("Avenger", 5, 0, 5000);
			trModifyProtounit("Troll", 5, 0, 5000);
			trModifyProtounit("Hero Greek Bellerophon", 5, 0, 15000);
			trModifyProtounit("Heka Gigantes", 5, 0, 15000);
			trModifyProtounit("Hero Greek Odysseus", 5, 0, 10000);
			trModifyProtounit("Hoplite", 5, 0, 50000);
		}
	}

	modularCounterInit("modularPlayersPointer", trQuestVarGet("numHumans"));

	trQuestVarCopy("numChoices", "numHumans");
	trModifyProtounit("Avenger", 5, 0, 5000);
	trModifyProtounit("Troll", 5, 0, 5000);
	trModifyProtounit("Hero Greek Bellerophon", 5, 0, 15000);
	trModifyProtounit("Heka Gigantes", 5, 0, 15000);
	trModifyProtounit("Hero Greek Odysseus", 5, 0, 10000);
	trModifyProtounit("Hoplite", 5, 0, 50000);

	

	trModifyProtounit("Migdol Stronghold", 0, 11, -9999);
	trModifyProtounit("Helepolis", 0, 11, -9999);
	trModifyProtounit("Helepolis", 1, 2, -99999);
	trModifyProtounit("Helepolis", 0, 2, -99999);
	trModifyProtounit("Argus", 5, 1, -2);
	trModifyProtounit("Carcinos", 5, 1, -2);
	trModifyProtounit("Revealer", 0, 11, 50);
	trSetCivAndCulture(5, 4, 1);

	trTechSetStatus(5, 127, 4);
	trTechSetStatus(0, 127, 4);
	trTechSetStatus(0, 67, 4);

	trModifyProtounit("UI Range Indicator Atlantean SFX",1,8,2);

	for(x=30; >0) {
		trTechSetStatus(5, 297, 4);
		trTechSetStatus(1, 297, 4);
	}

	
	zSetProtoUnitStat("Stymph Bird Feather", 5, 1, 6);

	for(x=931; >=0) {
		trModifyProtounit(kbGetProtoUnitName(x), 5, 24, -0.2);
		trModifyProtounit(kbGetProtoUnitName(x), 5, 24, 0.01);
		trModifyProtounit(kbGetProtoUnitName(x), 5, 25, -0.3);
		trModifyProtounit(kbGetProtoUnitName(x), 5, 25, 0.01);
		trModifyProtounit(kbGetProtoUnitName(x), 5, 26, -1);
		trModifyProtounit(kbGetProtoUnitName(x), 5, 26, 0.01);
	}
	trModifyProtounit("Wadjet Spit", 0, 0, 999999);
	trModifyProtounit("Wadjet Spit", 5, 0, 999999);
	trModifyProtounit("Rocket", 0, 1, -30.0);
	trModifyProtounit("Arkantos God", 0, 2, -99);
	trModifyProtounit("Phoenix", 0, 2, -99);
	trModifyProtounit("Arkantos God", 0, 55, 4.0);
	trModifyProtounit("Dwarf", 1, 55, 4.0);
	trModifyProtounit("Hero Greek Achilles", 1, 55, 4.0);

	trModifyProtounit("Servant", 1, 55, 3.0);
	trModifyProtounit("Carcinos", 1, 55, 3.0);
	

	trModifyProtounit("Servant", 5, 55, 3.0);
	trModifyProtounit("Carcinos", 5, 55, 3.0);
	

	trModifyProtounit("Dryad", 5, 6, 1.0);
	trModifyProtounit("Pharaoh", 5, 6, 1.0);
	trModifyProtounit("Mercenary", 5, 6, 1.0);
	trModifyProtounit("Walking Woods Pine", 5, 6, 1.0);
	trModifyProtounit("Mercenary Cavalry", 5, 6, 1.0);
	trModifyProtounit("Tartarian Gate spawn", 5, 6, 1.0);
	trModifyProtounit("Shade XP", 5, 6, 1.0);

	trModifyProtounit("Shade XP", 5, 1, -2.0);
	trModifyProtounit("Shade XP", 5, 29, 9899);

	trModifyProtounit("Ballista", 5, 13, -3);
	trModifyProtounit("Ballista", 5, 11, -10);
	trModifyProtounit("Fire Siphon", 5, 11, 0);
	trModifyProtounit("Ballista Shot", 5, 8, 10);

	trModifyProtounit("Lampades Bolt", 5, 8, 5);

	zSetProtoUnitStat("Petosuchus Projectile", 5, 1, 10);
	zSetProtoUnitStat("Priest Projectile", 5, 1, 6);

	trModifyProtounit("Bolt Strike", 0, 27, -10000);
	trModifyProtounit("Bolt Strike", 0, 28, -10000);
	trModifyProtounit("Bolt Strike", 0, 29, -10000);
	zInitProtoUnitStat("Bolt Strike", 0, 27, 0);

	trModifyProtounit("Pharaoh", 5, 11, 12);

	trModifyProtounit("Helepolis", 0, 55, 4.0);
	trModifyProtounit("Avenger", 5, 55, 4.0);
	trModifyProtounit("Hoplite", 5, 55, 4.0);
	trModifyProtounit("Heka Gigantes", 5, 55, 4.0);

	zSetProtoUnitStat("Rocket", 0, 1, 1.0);
	trQuestVarSet("timelordSpeed", 1);

	if (trQuestVarGet("numHumans") == 1) {
		trSoundPlayFN("default","1",-1,
			"WARNING: You are playing in singleplayer! (Sometimes AoM bugs and sends everyone into singleplayer)","");
	}

	trSetDisableGPBlocking(true);
	aiSet("NoAI", 0);
	aiSet("NoAI", 5);
	xsDisableRule("initializeEverything");
}

rule timeMod_00
highFrequency
active
{
	if (trQuestVarGet("timeNewX") > 20 && trQuestVarGet("timeNewX") < 30) {
		trQuestVarSet("timeModStep", 0);
		trDelayedRuleActivation("timeMod_01");
		xsDisableRule("timeMod_00");
	}
}

rule timeMod_01
highFrequency
inactive
{
	if (trQuestVarGet("timeModStep") == 0 && (trTime()-cActivationTime) >= 1) {
		trQuestVarCopy("timeModScaleStart", "timeOldX");
		trQuestVarSet("timeModStep", 1);
	} else
	if (trQuestVarGet("timeModStep") == 1 && (trTime()-cActivationTime) >= 2) {
		trQuestVarCopy("timeModScaleEnd", "timeOldX");
		float diff = xsAbs(trQuestVarGet("timeModScaleStart") - trQuestVarGet("timeModScaleEnd"));
		trQuestVarSet("timeLordSpeed", trQuestVarGet("timeLordSpeed") / xsMax(xsMin(diff, 2.0), 0.5));
		zSetProtoUnitStat("Rocket", 0, 1, trQuestVarGet("timeLordSpeed"));
		trQuestVarSet("timeModStep", 2);
	} else
	if (trQuestVarGet("timeModStep") == 2 && (trQuestVarGet("timeNewX") < 20 || trQuestVarGet("timeNewX") > 30)) {
		trQuestVarSet("timeModStep", 0);
		xsEnableRule("timeMod_00");
		xsDisableRule("timeMod_01");
	}
}

rule iSpyWithMyLittleEye
highFrequency
active
{
	timediff();
	spyFind();
	checkForFreeze();
	maintainStun();
	if (zGetTime() > trQuestVarGet("poisonWatch")) {
		trQuestVarSet("poisonWatch", trQuestVarGet("poisonWatch") + 1);
		poisonDamage();
		if (trQuestVarGet("play") == 1) {
			for(p=4;>0) {
				trPlayerGrantResources(p, "favor", 1*trQuestVarGet("p"+p+"unique34"));
			}
		}
	}
	cleanDatabase();
	silence();

}