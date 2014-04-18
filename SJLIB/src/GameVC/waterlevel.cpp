#include "SJLIB/stdinc.h"

int& nNoOfWaterLevels = *(int*)0x9B6CE8;
/*
void WaterLevelInitialize()
{
	nNoOfWaterLevels = 0;
	FILE* fp = fopen("DATA\\waterpro.dat", "rb");

	fseek(fp, 0, SEEK_END);
	int fpsize = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	
	// they loaded default format file
	if (fpsize == 21444)
	//*/