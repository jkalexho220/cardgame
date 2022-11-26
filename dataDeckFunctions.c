vector readDeckCommanderAndClass(int slot = 0) {
	string fn = slotFilename(slot);
	int bit = 0;
	int data = trGetScenarioUserData(10, fn);
	int commander = 0;
	int first = 0;
	int second = 0;
	vector result = vector(0,0,0);
	/*
	for(x=0; < 6) {
		data = trGetScenarioUserData(x, fn);
		bit = iModulo(2, data);
		// Check if class is in deck
		if (bit == 1) {
			data = data / 2;
			bit = iModulo(2, data);
			// Check if class is first or second
			if (bit == 1) {
				second = x;
			} else {
				first = x;
				data = data / 2;
				bit = iModulo(2, data);
				// Calculate commander
				commander = 2 * first + bit;
			}
		}
	}
	*/
	commander = iModulo(12, data);
	data = data / 12;
	first = iModulo(6, data);
	data = data / 6;
	second = iModulo(6, data);
	data = data / 6;
	result = xsVectorSet(commander, first, second);
	return(result);
}

vector readDeckCardCount(int slot = 0) {
	string fn = slotFilename(slot);
	int data = 0;
	int card = 0;
	vector classes = readDeckCommanderAndClass(slot);
	int first = xsVectorGetY(classes);
	int second = xsVectorGetZ(classes);
	int firstCount = 0;
	int secondCount = 0;
	vector result = vector(0,0,0);
	int c = 0;
	c = 30 * first;
	data = trGetScenarioUserData(6, fn);
	for(x=0;<15) {
		card = c + x;
		firstCount = firstCount + iModulo(4, data);
		data = data / 4;
		if (data == 0) {
			break;
		}
	}
	data = trGetScenarioUserData(7, fn);
	for(x=15;<30) {
		card = c + x;
		firstCount = firstCount + iModulo(4, data);
		data = data / 4;
		if (data == 0) {
			break;
		}
	}
	if (first != second) {
		c = 30 * second;
		data = trGetScenarioUserData(8, fn);
		for(x=0;<15) {
			card = c + x;
			secondCount = secondCount + iModulo(4, data);
			data = data / 4;
			if (data == 0) {
				break;
			}
		}
		data = trGetScenarioUserData(9, fn);
		for(x=15;<30) {
			card = c + x;
			secondCount = secondCount + iModulo(4, data);
			data = data / 4;
			if (data == 0) {
				break;
			}
		}
	}
	result = xsVectorSet(firstCount, secondCount, 0);
	return(result);
}