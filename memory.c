/*
NOTE: In order for the database functionality to work, any database functions can only be called
while the context player is 0. If you need to switch context players (such as for getting a unit's current health or current attack target)
make sure to immediately switch back to context player 0 once you are done acquiring the information you need.
*/

rule context_change_always
active
highFrequency
{
	/*
	For whatever reason, the context player is set to -1 at the start of
	every trigger loop, but only in random map scripts. So here we are.
	*/
	xsSetContextPlayer(0);
}

const int mInt = 0;
const int mFloat = 1;
const int mString = 2;
const int mVector = 3;
const int mBool = 4;

const int xMetadata = 0; // contains current pointer and database size and numVariables. However, malloc doesn't have metadata so they have to shift down 1
const int xDirtyBit = 1;
const int xNextBlock = 2;
const int xPrevBlock = 3; // for databases, xData is unused and xPrevBlock takes its place
const int xData = 3;
const int xVarNames = 4; // list of variable names
const int xVariables = 5;

/*
Metadata information
*/
const int mPointer = 0;
const int mCount = 1;
const int mNextFree = 2;
const int mNewestBlock = 3;
const int mCacheHead = 4; // the cache stores items that you want to temporarily remove
const int mCacheCount = 5;
const int mVariableTypes = 5;
/*
subsequent items in the metadata will determine the datatypes of extra variables for the database
*/

const int NEXTFREE = 0; // the very first block contains the next free pointer and nothing else

int MALLOC = 0;
int ARRAYS = 0;
int mNumArrays = 0;

void debugLog(string msg = "") {
	if (trCurrentPlayer() == 1) {
		trChatSend(0, "<color=1,0,0>" + msg);
	}
}


string datatypeName(int data = 0) {
	string name = "void";
	if (data >= 0 && data <= 4) {
		name = aiPlanGetUserVariableString(MALLOC,15,data);
	}
	return(name);
}

int zNewArray(int type = 0, int size = 1, string name = "") {
	int index = mNumArrays;
	mNumArrays = mNumArrays + 1;
	switch(type)
	{
		case mInt:
		{
			aiPlanAddUserVariableInt(ARRAYS,index,name,size);
		}
		case mFloat:
		{
			aiPlanAddUserVariableFloat(ARRAYS,index,name,size);
		}
		case mString:
		{
			aiPlanAddUserVariableString(ARRAYS,index,name,size);
		}
		case mVector:
		{
			aiPlanAddUserVariableVector(ARRAYS,index,name,size);
		}
		case mBool:
		{
			aiPlanAddUserVariableBool(ARRAYS,index,name,size);
		}
	}
	return(index);
}

/*
*/
bool free(int type = -1, int index = -1) {
	bool success = false;
	if (aiPlanGetUserVariableBool(MALLOC, type * 3 + xDirtyBit - 1, index)) {
		aiPlanSetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, index,
			aiPlanGetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, NEXTFREE));
		aiPlanSetUserVariableBool(MALLOC, type * 3 + xDirtyBit - 1, index, false);
		aiPlanSetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, NEXTFREE, index); // set next free to be the newly added block
		success = true;
	}
	return(success);
}

/*
*/
int malloc(int type = -1) {
	/*
	get next free User variable
	*/
	int next = aiPlanGetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, NEXTFREE);
	if (next == 0) {
		/*
		if no free buffers, create a new one
		*/
		next = aiPlanGetNumberUserVariableValues(MALLOC,type * 3 + xNextBlock - 1);
		for(i=type * 3; < type * 3 + 3) {
			aiPlanSetNumberUserVariableValues(MALLOC,i,next + 1, false); // resizing seems to be a little expensive?
		}
		aiPlanSetUserVariableInt(MALLOC,type * 3 + xNextBlock - 1, next, 0); // next free block is 0 for a newly created block
	} else {
		/*
		if a free buffer exists, we set our nextFree pointer to the next free buffer
		*/
		aiPlanSetUserVariableInt(MALLOC,type * 3 + xNextBlock - 1,NEXTFREE,
			aiPlanGetUserVariableInt(MALLOC,type * 3 + xNextBlock - 1,next));
	}
	aiPlanSetUserVariableBool(MALLOC,type * 3 + xDirtyBit - 1, next, true); // set dirty bit
	
	return(next);
}

bool zGetBool(int index = 0) {
	bool val = false;
	if (aiPlanGetUserVariableBool(MALLOC, mBool * 3 + xDirtyBit - 1, index)) {
		val = aiPlanGetUserVariableBool(MALLOC, mBool * 3 + xData - 1, index);
	}
	return(val);
}

bool zSetBool(int index = 0, bool val = false) {
	bool success = false;
	if (aiPlanGetUserVariableBool(MALLOC, mBool * 3 + xDirtyBit - 1, index)) {
		success = aiPlanSetUserVariableBool(MALLOC, mBool * 3 + xData - 1, index, val);
	}
	return(success);
}

int zNewBool(bool val = false) {
	int index = malloc(mBool);
	zSetBool(index, val);
	return(index);
}

bool zFreeBool(int index = 0) {
	return(free(mBool, index));
}


string zGetString(int index = 0) {
	string val = "";
	if (aiPlanGetUserVariableBool(MALLOC, mString * 3 + xDirtyBit - 1, index)) {
		val = aiPlanGetUserVariableString(MALLOC, mString * 3 + xData - 1, index);
	}
	return(val);
}

bool zSetString(int index = 0, string val = "") {
	bool success = false;
	if (aiPlanGetUserVariableBool(MALLOC, mString * 3 + xDirtyBit - 1, index)) {
		success = aiPlanSetUserVariableString(MALLOC, mString * 3 + xData - 1, index, val);
	}
	return(success);
}

int zNewString(string val = "") {
	int index = malloc(mString);
	zSetString(index, val);
	return(index);
}

bool zFreeString(int index = 0) {
	return(free(mString, index));
}

int zGetInt(int index = 0) {
	int val = -1;
	if (aiPlanGetUserVariableBool(MALLOC, mInt * 3 + xDirtyBit - 1, index)) {
		val = aiPlanGetUserVariableInt(MALLOC, mInt * 3 + xData - 1, index);
	}
	return(val);
}

bool zSetInt(int index = 0, int val = 0) {
	bool success = false;
	if (aiPlanGetUserVariableBool(MALLOC, mInt * 3 + xDirtyBit - 1, index)) {
		success = aiPlanSetUserVariableInt(MALLOC, mInt * 3 + xData - 1, index, val);
	}
	return(success);
}

int zNewInt(int val = 0) {
	int index = malloc(mInt);
	zSetInt(index, val);
	return(index);
}

bool zFreeInt(int index = 0) {
	return(free(mInt, index));
}

float zGetFloat(int index = 0) {
	float val = -1;
	if (aiPlanGetUserVariableBool(MALLOC, mFloat * 3 + xDirtyBit - 1, index)) {
		val = aiPlanGetUserVariableFloat(MALLOC, mFloat * 3 + xData - 1, index);
	}
	return(val);
}

bool zSetFloat(int index = 0, float val = 0) {
	bool success = false;
	if (aiPlanGetUserVariableBool(MALLOC, mFloat * 3 + xDirtyBit - 1, index)) {
		success = aiPlanSetUserVariableFloat(MALLOC, mFloat * 3 + xData - 1, index, val);
	}
	return(success);
}

int zNewFloat(float val = 0) {
	int index = malloc(mFloat);
	zSetFloat(index, val);
	return(index);
}

bool zFreeFloat(int index = 0) {
	return(free(mFloat, index));
}

vector zGetVector(int index = 0) {
	vector val = vector(-1,-1,-1);
	if (aiPlanGetUserVariableBool(MALLOC, mVector * 3 + xDirtyBit - 1, index)) {
		val = aiPlanGetUserVariableVector(MALLOC, mVector * 3 + xData - 1, index);
	}
	return(val);
}

bool zSetVector(int index = 0, vector val = vector(0,0,0)) {
	bool success = false;
	if (aiPlanGetUserVariableBool(MALLOC, mVector * 3 + xDirtyBit - 1, index)) {
		success = aiPlanSetUserVariableVector(MALLOC, mVector * 3 + xData - 1, index, val);
	}
	return(success);
}

int zNewVector(vector val = vector(0,0,0)) {
	int index = malloc(mVector);
	zSetVector(index, val);
	return(index);
}

bool zFreeVector(int index = 0) {
	return(free(mVector, index));
}

/*
Size is the starting size of the database, but databases can grow indefinitely
returns the identifier of the database. Use this identifier in other xDatabase triggers
*/
int xInitDatabase(string name = "", int size = 0) {
	int id = aiPlanCreate(name, 8);
	aiPlanAddUserVariableBool(id,xDirtyBit,"DirtyBit",size+1);
	aiPlanAddUserVariableInt(id,xNextBlock,"NextBlock",size+1);
	aiPlanAddUserVariableInt(id,xPrevBlock,"PrevBlock",size+1);
	aiPlanAddUserVariableInt(id,xMetadata,"Metadata",6);
	aiPlanSetUserVariableInt(id,xMetadata,mPointer,0);
	aiPlanSetUserVariableInt(id,xMetadata,mCount,0);
	aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,0);
	aiPlanSetUserVariableInt(id,xMetadata,mCacheCount,0);
	
	aiPlanSetUserVariableInt(id,xMetadata,mNextFree,size);
	aiPlanSetUserVariableInt(id,xNextBlock,0,0);
	for(i=1; <= size) { // connect all the free buffers together
		aiPlanSetUserVariableBool(id,xDirtyBit,i,false);
		aiPlanSetUserVariableInt(id,xNextBlock,i,i-1);
	}
	aiPlanAddUserVariableString(id,xVarNames,"VarNames",1);
	aiPlanSetUserVariableString(id,xVarNames,0,"none");
	return(id);
}

/*
returns the index of the newly added variable
*/
int xInitAddVar(int id = 0, string name = "", int type = 0) {
	int count = aiPlanGetNumberUserVariableValues(id,xDirtyBit);
	/*
	first, add the type to our list of types in this struct
	*/
	int index = aiPlanGetNumberUserVariableValues(id,xMetadata);
	aiPlanSetNumberUserVariableValues(id,xMetadata,index + 1,false);
	aiPlanSetUserVariableInt(id,xMetadata,index,type);
	
	index = aiPlanGetNumberUserVariableValues(id,xVarNames);
	aiPlanSetNumberUserVariableValues(id,xVarNames,index+1,false);
	aiPlanSetUserVariableString(id,xVarNames,index,name);
	/*
	next, add a new array of the specified datatype to hold values
	*/
	index = xVarNames + index;
	switch(type)
	{
		case mInt:
		{
			aiPlanAddUserVariableInt(id,index,name,count);
		}
		case mFloat:
		{
			aiPlanAddUserVariableFloat(id,index,name,count);
		}
		case mString:
		{
			aiPlanAddUserVariableString(id,index,name,count);
		}
		case mVector:
		{
			aiPlanAddUserVariableVector(id,index,name,count);
		}
		case mBool:
		{
			aiPlanAddUserVariableBool(id,index,name,count);
		}
	}
	return(index);
}

/*
id is the integer name of the database
name is unused but required
defVal = default value for newly created database entries
*/
int xInitAddInt(int id = 0, string name = "", int defVal = 0) {
	int index = xInitAddVar(id,name,mInt);
	aiPlanSetUserVariableInt(id, index, 0, defVal);
	return(index);
}

int xInitAddFloat(int id = 0, string name = "", float defVal = 0) {
	int index = xInitAddVar(id, name, mFloat);
	aiPlanSetUserVariableFloat(id, index, 0, defVal);
	return(index);
}

int xInitAddString(int id = 0, string name = "", string defVal = "") {
	int index = xInitAddVar(id, name, mString);
	aiPlanSetUserVariableString(id, index, 0, defVal);
	return(index);
}

int xInitAddVector(int id = 0, string name = "", vector defVal = vector(0,0,0)) {
	int index = xInitAddVar(id, name, mVector);
	aiPlanSetUserVariableVector(id, index, 0, defVal);
	return(index);
}

int xInitAddBool(int id = 0, string name = "", bool defVal = false) {
	int index = xInitAddVar(id,name,mBool);
	aiPlanSetUserVariableBool(id, index, 0, defVal);
	return(index);
}

void xResetValues(int id = 0, int index = -1, int stopAt = -1) {
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	if (stopAt == -1) {
		stopAt = aiPlanGetNumberUserVariableValues(id, xVarNames);
	} else {
		stopAt = stopAt - mVariableTypes;
	}
	for(i = 1; < stopAt) {
		switch(aiPlanGetUserVariableInt(id,xMetadata,mVariableTypes + i))
		{
			case mInt:
			{
				aiPlanSetUserVariableInt(id,xVarNames + i,index,aiPlanGetUserVariableInt(id,xVarNames + i,0));
			}
			case mFloat:
			{
				aiPlanSetUserVariableFloat(id,xVarNames + i,index,aiPlanGetUserVariableFloat(id,xVarNames + i,0));
			}
			case mString:
			{
				aiPlanSetUserVariableString(id,xVarNames + i,index,aiPlanGetUserVariableString(id,xVarNames + i,0));
			}
			case mVector:
			{
				aiPlanSetUserVariableVector(id,xVarNames + i,index,aiPlanGetUserVariableVector(id,xVarNames + i,0));
			}
			case mBool:
			{
				aiPlanSetUserVariableBool(id,xVarNames + i,index,aiPlanGetUserVariableBool(id,xVarNames + i,0));
			}
		}
	}
}

bool xSetPointer(int id = 0, int index = 0) {
	bool success = false;
	if (aiPlanGetUserVariableBool(id,xDirtyBit,index)) {
		aiPlanSetUserVariableInt(id,xMetadata,mPointer,index);
		success = true;
	}
	return(success);
}

int xAddDatabaseBlock(int id = 0, bool setPointer = false) {
	int next = aiPlanGetUserVariableInt(id,xMetadata,mNextFree);
	if (next == 0) {
		/*
		if no available buffers, we extend the total sizes of the arrays
		*/
		next = aiPlanGetNumberUserVariableValues(id,xDirtyBit);
		/* increase lengths of variable arrays */
		for(i=aiPlanGetNumberUserVariableValues(id,xVarNames) - 1; > 0) {
			aiPlanSetNumberUserVariableValues(id,i + xVarNames,next+1,false);
		}
		/* increase lengths of metadata arrays */
		for(i=xPrevBlock; > xMetadata) {
			aiPlanSetNumberUserVariableValues(id,i,next+1,false);
		}
	} else {
		/*
		if a free buffer is available, we grab it and set next free to be the next of the buffer we grabbed
		*/
		aiPlanSetUserVariableInt(id,xMetadata,mNextFree,aiPlanGetUserVariableInt(id,xNextBlock,next));
	}
	aiPlanSetUserVariableBool(id,xDirtyBit,next,true);
	
	if (aiPlanGetUserVariableInt(id,xMetadata,mCount) == 0) {
		/*
		If it's the only thing in the db, point it to itself and also set the database pointer to the new thing
		*/
		aiPlanSetUserVariableInt(id,xNextBlock,next,next);
		aiPlanSetUserVariableInt(id,xPrevBlock,next,next);
		aiPlanSetUserVariableInt(id,xMetadata,mPointer,next);
	} else {
		/*
		otherwise, slide in between two links in the list at mPointer
		*/
		int before = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
		int after = aiPlanGetUserVariableInt(id,xNextBlock,before);
		
		aiPlanSetUserVariableInt(id,xNextBlock,next,after); // next of me is after
		aiPlanSetUserVariableInt(id,xPrevBlock,next,before); // prev of me is before
		aiPlanSetUserVariableInt(id,xNextBlock,before,next); // next of before is me
		aiPlanSetUserVariableInt(id,xPrevBlock,after,next); // prev of after is me
	}
	aiPlanSetUserVariableInt(id,xMetadata,mNewestBlock,next);
	aiPlanSetUserVariableInt(id,xMetadata,mCount, 1 + aiPlanGetUserVariableInt(id,xMetadata,mCount));
	/*
	finally, initialize all the variables of the struct to their default values (whatever's in index 0 of the array)
	*/
	xResetValues(id,next);
	if (setPointer) {
		xSetPointer(id, next);
	}
	return(next);
}


bool xFreeDatabaseBlock(int id = 0, int index = -1) {
	bool success = false;
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	if (aiPlanGetUserVariableBool(id,xDirtyBit,index)) {
		/* connect next with prev */
		int after = aiPlanGetUserVariableInt(id,xNextBlock,index);
		int before = aiPlanGetUserVariableInt(id,xPrevBlock,index);
		aiPlanSetUserVariableInt(id,xNextBlock,before,after); // next block of before is after
		aiPlanSetUserVariableInt(id,xPrevBlock,after,before); // prev block of after is before
		
		/* add myself to the top of the free stack */
		aiPlanSetUserVariableInt(id,xNextBlock,index,aiPlanGetUserVariableInt(id,xMetadata,mNextFree));
		aiPlanSetUserVariableInt(id,xMetadata,mNextFree,index);
		aiPlanSetUserVariableBool(id,xDirtyBit,index,false);
		
		/* set mPointer to my previous block and decrement count */
		if (index == aiPlanGetUserVariableInt(id,xMetadata,mPointer)) {
			aiPlanSetUserVariableInt(id,xMetadata,mPointer,aiPlanGetUserVariableInt(id,xPrevBlock,index));
		}
		aiPlanSetUserVariableInt(id,xMetadata,mCount, aiPlanGetUserVariableInt(id,xMetadata,mCount) - 1);
		success = true;
	}
	return(success);
}

// Detaches the block and saves it in the cache.
bool xDetachDatabaseBlock(int id = 0, int index = -1) {
	bool success = false;
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	if (aiPlanGetUserVariableBool(id,xDirtyBit,index)) {
		/* connect next with prev */
		int after = aiPlanGetUserVariableInt(id,xNextBlock,index);
		int before = aiPlanGetUserVariableInt(id,xPrevBlock,index);
		aiPlanSetUserVariableInt(id,xNextBlock,before,after); // next block of before is after
		aiPlanSetUserVariableInt(id,xPrevBlock,after,before); // prev block of after is before
		
		aiPlanSetUserVariableBool(id,xDirtyBit,index,false);
		
		/* set mPointer to my previous block and decrement count */
		if (index == aiPlanGetUserVariableInt(id,xMetadata,mPointer)) {
			aiPlanSetUserVariableInt(id,xMetadata,mPointer,before);
		}
		
		/* insert myself into the detach cache */
		if (aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) == 0) {
			/*
			If it's the only thing in the db, point it to itself and also set the database pointer to the new thing
			*/
			aiPlanSetUserVariableInt(id,xNextBlock,index,index);
			aiPlanSetUserVariableInt(id,xPrevBlock,index,index);
			aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,index);
		} else {
			/*
			otherwise, slide in between two links in the list at mCacheHead
			*/
			before = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
			after = aiPlanGetUserVariableInt(id,xNextBlock,before);
			
			aiPlanSetUserVariableInt(id,xNextBlock,index,after); // next of me is after
			aiPlanSetUserVariableInt(id,xPrevBlock,index,before); // prev of me is before
			aiPlanSetUserVariableInt(id,xNextBlock,before,index); // next of before is me
			aiPlanSetUserVariableInt(id,xPrevBlock,after,index); // prev of after is me
		}
		
		aiPlanSetUserVariableInt(id,xMetadata,mCount, aiPlanGetUserVariableInt(id,xMetadata,mCount) - 1);
		aiPlanSetUserVariableInt(id,xMetadata,mCacheCount, aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) + 1);
		success = true;
	}
	return(success);
}

bool xRestoreDatabaseBlock(int id = 0, int index = -1) {
	bool success = false;
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
	}
	if (aiPlanGetUserVariableBool(id,xDirtyBit,index) == false) {
		/* connect next with prev */
		int after = aiPlanGetUserVariableInt(id,xNextBlock,index);
		int before = aiPlanGetUserVariableInt(id,xPrevBlock,index);
		aiPlanSetUserVariableInt(id,xNextBlock,before,after); // next block of before is after
		aiPlanSetUserVariableInt(id,xPrevBlock,after,before); // prev block of after is before
		
		aiPlanSetUserVariableBool(id,xDirtyBit,index,true);
		
		/* set mCacheHead to my previous block and decrement count */
		if (index == aiPlanGetUserVariableInt(id,xMetadata,mCacheHead)) {
			aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,aiPlanGetUserVariableInt(id,xPrevBlock,index));
		}
		
		/* insert myself into the database */
		if (aiPlanGetUserVariableInt(id,xMetadata,mCount) == 0) {
			/*
			If it's the only thing in the db, point it to itself and also set the database pointer to the new thing
			*/
			aiPlanSetUserVariableInt(id,xNextBlock,index,index);
			aiPlanSetUserVariableInt(id,xPrevBlock,index,index);
			aiPlanSetUserVariableInt(id,xMetadata,mPointer,index);
		} else {
			/*
			otherwise, slide in between two links in the list at mPointer
			*/
			before = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
			after = aiPlanGetUserVariableInt(id,xNextBlock,before);
			
			aiPlanSetUserVariableInt(id,xNextBlock,index,after); // next of me is after
			aiPlanSetUserVariableInt(id,xPrevBlock,index,before); // prev of me is before
			aiPlanSetUserVariableInt(id,xNextBlock,before,index); // next of before is me
			aiPlanSetUserVariableInt(id,xPrevBlock,after,index); // prev of after is me
		}
		
		aiPlanSetUserVariableInt(id,xMetadata,mCount, aiPlanGetUserVariableInt(id,xMetadata,mCount) + 1);
		aiPlanSetUserVariableInt(id,xMetadata,mCacheCount, aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) - 1);
		success = true;
	}
	
	return(success);
}

bool xRestoreCache(int id = 0) {
	bool success = false;
	if (aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) > 0) {
		int pointer = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
		for(i=aiPlanGetUserVariableInt(id,xMetadata,mCacheCount); >0) {
			aiPlanSetUserVariableBool(id,xDirtyBit,pointer,true);
			pointer = aiPlanGetUserVariableInt(id,xNextBlock,pointer);
		}
		/* insert the ends of the chain into the database */
		if (aiPlanGetUserVariableInt(id,xMetadata,mCount) == 0) {
			/*
			If it's the only thing in the db, pointer now points to the cacheHead
			*/
			aiPlanSetUserVariableInt(id,xMetadata,mPointer,aiPlanGetUserVariableInt(id,xMetadata,mCacheHead));
		} else {
			/*
			otherwise, slide in between two links in the list at mPointer
			*/
			int before = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
			int after = aiPlanGetUserVariableInt(id,xNextBlock,before);
			int index = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
			int next = aiPlanGetUserVariableInt(id,xPrevBlock,index); // the next of this block will be the after block
			
			aiPlanSetUserVariableInt(id,xNextBlock,next,after); // next of next is after
			aiPlanSetUserVariableInt(id,xPrevBlock,after,next); // prev of after is next
			
			aiPlanSetUserVariableInt(id,xNextBlock,before,index); // next of before is me
			aiPlanSetUserVariableInt(id,xPrevBlock,index,before); // prev of me is before
		}
		aiPlanSetUserVariableInt(id,xMetadata,mCount,
			aiPlanGetUserVariableInt(id,xMetadata,mCount) + aiPlanGetUserVariableInt(id,xMetadata,mCacheCount));
		aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,0);
		aiPlanSetUserVariableInt(id,xMetadata,mCacheCount,0);
		success = true;
	}
	return(success);
}

int xGetNewestPointer(int id = 0) {
	return(aiPlanGetUserVariableInt(id,xMetadata,mNewestBlock));
}

int xDatabaseNext(int id = 0, bool reverse = false) {
	int pointer = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	if (reverse) {
		pointer = aiPlanGetUserVariableInt(id,xPrevBlock,pointer);
	} else {
		pointer = aiPlanGetUserVariableInt(id,xNextBlock,pointer);
	}
	if (aiPlanGetUserVariableBool(id,xDirtyBit,pointer) && (aiPlanGetUserVariableInt(id,xMetadata,mCount) > 0)) {
		aiPlanSetUserVariableInt(id,xMetadata,mPointer,pointer);
	} else {
		pointer = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
		debugLog("xDatabaseNext: " + aiPlanGetName(id) + " pointer is incorrect!");
		debugLog("xNextBlock: " + aiPlanGetUserVariableInt(id,xNextBlock,pointer));
		debugLog("Me: " + pointer);
		debugLog("xPrevblock: " + aiPlanGetUserVariableInt(id,xPrevBlock,pointer));
	}
	return(pointer);
}

void xClearDatabase(int id = 0) {
	int next = aiPlanGetUserVariableInt(id,xMetadata,mNextFree);
	int pointer = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	aiPlanSetUserVariableInt(id,xMetadata,mNextFree,aiPlanGetUserVariableInt(id,xNextBlock,pointer));
	aiPlanSetUserVariableInt(id,xNextBlock,pointer,next);

	for(i=0; < aiPlanGetNumberUserVariableValues(id,xDirtyBit)) {
		aiPlanSetUserVariableBool(id,xDirtyBit,i,false);
	}
	
	aiPlanSetUserVariableInt(id,xMetadata,mCount,0);
	aiPlanSetUserVariableInt(id,xMetadata,mPointer,0);
}

void xResetDatabase(int id = 0) {
	int size = aiPlanGetNumberUserVariableValues(id,xDirtyBit);
	aiPlanSetUserVariableInt(id,xMetadata,mPointer,0);
	aiPlanSetUserVariableInt(id,xMetadata,mCount,0);
	aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,0);
	aiPlanSetUserVariableInt(id,xMetadata,mCacheCount,0);
	
	aiPlanSetUserVariableInt(id,xMetadata,mNextFree,size - 1);
	aiPlanSetUserVariableInt(id,xNextBlock,0,0);
	for(i=1; < size) { // connect all the free buffers together
		aiPlanSetUserVariableBool(id,xDirtyBit,i,false);
		aiPlanSetUserVariableInt(id,xNextBlock,i,i-1);
	}
}

int xGetInt(int id = 0, int data = 0, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mInt) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xGetInt: " + aiPlanGetName(id) + " variable " + name + " is not an int! Type: " + type);
		return(-1); // if we are trying to get an int from the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanGetUserVariableInt(id,data,index));
}

bool xSetInt(int id = 0, int data = 0, int val = 0, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mInt) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xSetInt: " + aiPlanGetName(id) + " variable " + name + " is not an int! Type: " + type);
		return(false); // if we are trying to set the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	bool success = aiPlanSetUserVariableInt(id,data,index,val);
	if (success == false) {
		string err = ": Could not assign value: " + val;
		debugLog("xSetInt: " + aiPlanGetName(id) + aiPlanGetUserVariableString(id,xVarNames,data - xVarNames) + err);
	}
	return(success);
}


float xGetFloat(int id = 0, int data = 0, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mFloat) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xGetFloat: " + aiPlanGetName(id) + " variable " + name + " is not a float! Type: " + type);
		return(-1.0); // if we are trying to get an int from the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanGetUserVariableFloat(id,data,index));
}

bool xSetFloat(int id = 0, int data = 0, float val = 0, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mFloat) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xSetFloat: " + aiPlanGetName(id) + " variable " + name + " is not a float! Type: " + type);
		return(false); // if we are trying to set the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	bool success = aiPlanSetUserVariableFloat(id,data,index,val);
	if (success == false) {
		string err = ": Could not assign value: " + val;
		debugLog("xSetFloat: " + aiPlanGetName(id) + aiPlanGetUserVariableString(id,xVarNames,data - xVarNames) + err);
	}
	return(success);
}


string xGetString(int id = 0, int data = 0, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mString) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xGetString: " + aiPlanGetName(id) + " variable " + name + " is not a string! Type: " + type);
		return(""); // if we are trying to get an int from the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanGetUserVariableString(id,data,index));
}

bool xSetString(int id = 0, int data = 0, string val = "", int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mString) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xSetString: " + aiPlanGetName(id) + " variable " + name + " is not a string! Type: " + type);
		return(false); // if we are trying to set the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanSetUserVariableString(id,data,index,val));
}


vector xGetVector(int id = 0, int data = 0, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mVector) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xGetVector: " + aiPlanGetName(id) + " variable " + name + " is not a vector! Type: " + type);
		return(vector(0,0,0)); // if we are trying to get an int from the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanGetUserVariableVector(id,data,index));
}

bool xSetVector(int id = 0, int data = 0, vector val = vector(0,0,0), int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mVector) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xSetVector: " + aiPlanGetName(id) + " variable " + name + " is not a vector! Type: " + type);
		return(false); // if we are trying to set the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanSetUserVariableVector(id,data,index,val));
}


bool xGetBool(int id = 0, int data = 0, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mBool) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xGetBool: " + aiPlanGetName(id) + " variable " + name + " is not a bool! Type: " + type);
		return(false); // if we are trying to get an int from the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanGetUserVariableBool(id,data,index));
}

bool xSetBool(int id = 0, int data = 0, bool val = false, int index = -1) {
	if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mBool) {
		string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
		string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
		debugLog("xGetBool: " + aiPlanGetName(id) + " variable " + name + " is not a bool! Type: " + type);
		return(false); // if we are trying to set the wrong datatype, stop
	}
	if (index == -1) {
		index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
	}
	return(aiPlanSetUserVariableBool(id,data,index,val));
}

int xGetDatabaseCount(int id = 0) {
	return(aiPlanGetUserVariableInt(id,xMetadata,mCount));
}

int xGetPointer(int id = 0) {
	return(aiPlanGetUserVariableInt(id,xMetadata,mPointer));
}

void xPrintAll(int id = 0, int index = 0) {
	trChatSend(0, "<u>" + aiPlanGetName(id) + "</u>");
	trChatSend(0, "size: " + xGetDatabaseCount(id));
	trChatSend(0, "pointer: " + index);
	for(i=1; < aiPlanGetNumberUserVariableValues(id,xVarNames)) {
		string name = aiPlanGetUserVariableString(id,xVarNames,i);
		int type = aiPlanGetUserVariableInt(id,xMetadata,mVariableTypes + i);
		switch(type)
		{
			case mInt:
			{
				trChatSend(0, name + ": " + aiPlanGetUserVariableInt(id,xVarNames + i,index));
			}
			case mFloat:
			{
				trChatSend(0, name + ": " + aiPlanGetUserVariableFloat(id,xVarNames + i,index));
			}
			case mString:
			{
				trChatSend(0, name + ": " + aiPlanGetUserVariableString(id,xVarNames + i,index));
			}
			case mVector:
			{
				trChatSend(0, name + ": " + aiPlanGetUserVariableVector(id,xVarNames + i,index));
			}
			case mBool:
			{
				if (aiPlanGetUserVariableBool(id,xVarNames + i,index)) {
					trChatSend(0, name + ": true");
				} else {
					trChatSend(0, name + ": false");
				}
			}
		}
	}
}

void xUnitSelect(int id = 0, int varn = 0, bool reverse = true) {
	trUnitSelectClear();
	trUnitSelect(""+xGetInt(id,varn), reverse);
}

void xUnitSelectByID(int db = 0, int varn = 0) {
	trUnitSelectClear();
	trUnitSelectByID(xGetInt(db,varn));
}

rule mInitializeMemory
active
highFrequency
{
	xsDisableSelf();
	aiSet("NoAI", 0);
	MALLOC = aiPlanCreate("memory",8);
	ARRAYS = aiPlanCreate("arrays",8);
	for(i=0; < 5) {
		aiPlanAddUserVariableBool(MALLOC,i * 3 + xDirtyBit - 1,"DirtyBit"+i,1);
		aiPlanAddUserVariableInt(MALLOC,i * 3 + xNextBlock - 1,"NextBlock"+i,1);
		aiPlanSetUserVariableBool(MALLOC,i * 3 + xDirtyBit - 1, NEXTFREE, true);
		aiPlanSetUserVariableInt(MALLOC,i * 3 + xNextBlock - 1, NEXTFREE, 0);
	}
	aiPlanAddUserVariableInt(MALLOC,mInt * 3 + xData - 1, "intData",1);
	aiPlanAddUserVariableFloat(MALLOC,mFloat * 3 + xData - 1, "floatData",1);
	aiPlanAddUserVariableString(MALLOC,mString * 3 + xData - 1, "stringData",1);
	aiPlanAddUserVariableVector(MALLOC,mVector * 3 + xData - 1, "vectorData",1);
	aiPlanAddUserVariableBool(MALLOC,mBool * 3 + xData - 1, "boolData",1);
	
	aiPlanAddUserVariableString(MALLOC,15,"datatypes",5);
	aiPlanSetUserVariableString(MALLOC,15,mInt,"Integer");
	aiPlanSetUserVariableString(MALLOC,15,mFloat,"Float");
	aiPlanSetUserVariableString(MALLOC,15,mString,"String");
	aiPlanSetUserVariableString(MALLOC,15,mVector,"Vector");
	aiPlanSetUserVariableString(MALLOC,15,mBool,"Bool");
}