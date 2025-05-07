#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>

#include "Mapper000.h"
#include "Mapper001.h"
#include "Mapper002.h"
#include "Mapper003.h"
#include "Mapper004.h"
#include "Mapper066.h"

class Cartridge
{
public:
	Cartridge(const std::string& sFileName);
	~Cartridge();


public:
	bool ImageValid();

	

private:
	bool bImageValid = false;

	uint8_t nMapperID = 0;
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;

	std::vector<uint8_t> vPRGMemory;
	std::vector<uint8_t> vCHRMemory;

	std::shared_ptr<Mapper> pMapper;

	MIRROR hw_mirror = HORIZONTAL;


public:
	bool cpuRead(uint16_t addr, uint8_t& data);
	bool cpuWrite(uint16_t addr, uint8_t data);

	bool ppuRead(uint16_t addr, uint8_t& data);
	bool ppuWrite(uint16_t addr, uint8_t data);

	void reset();
	MIRROR Mirror();

	std::shared_ptr<Mapper> GetMapper();


};