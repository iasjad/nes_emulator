#include "Mapper066.h"

Mapper066::Mapper066(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{
}


Mapper066::~Mapper066()
{
}

bool Mapper066::cpuMapRead(uint16_t addr, uint32_t& mapped_addr, uint8_t& data)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		mapped_addr = nPRGBankSelect * 0x8000 + (addr & 0x7FFF);
		return true;
	}
	else
		return false;
}

bool Mapper066::cpuMapWrite(uint16_t addr, uint32_t& mapped_addr, uint8_t data)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		nCHRBankSelect = data & 0x03;
		nPRGBankSelect = (data & 0x30) >> 4;
	}

	return false;
}

bool Mapper066::ppuMapRead(uint16_t addr, uint32_t& mapped_addr)
{
	if (addr < 0x2000)
	{
		mapped_addr = nCHRBankSelect * 0x2000 + addr;
		return true;
	}
	else
		return false;
}

bool Mapper066::ppuMapWrite(uint16_t addr, uint32_t& mapped_addr)
{
	return false;
}

void Mapper066::reset()
{
	nCHRBankSelect = 0;
	nPRGBankSelect = 0;
}