#include "Mapper002.h"


Mapper002::Mapper002(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{
}


Mapper002::~Mapper002()
{
}

bool Mapper002::cpuMapRead(uint16_t addr, uint32_t& mapped_addr, uint8_t& data)
{
	if (addr >= 0x8000 && addr <= 0xBFFF)
	{
		mapped_addr = nPRGBankSelectLo * 0x4000 + (addr & 0x3FFF);
		return true;
	}

	if (addr >= 0xC000 && addr <= 0xFFFF)
	{
		mapped_addr = nPRGBankSelectHi * 0x4000 + (addr & 0x3FFF);
		return true;
	}

	return false;
}

bool Mapper002::cpuMapWrite(uint16_t addr, uint32_t& mapped_addr, uint8_t data)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		nPRGBankSelectLo = data & 0x0F;
	}

	return false;
}

bool Mapper002::ppuMapRead(uint16_t addr, uint32_t& mapped_addr)
{
	if (addr < 0x2000)
	{
		mapped_addr = addr;
		return true;
	}
	else
		return false;
}

bool Mapper002::ppuMapWrite(uint16_t addr, uint32_t& mapped_addr)
{
	if (addr < 0x2000)
	{
		if (nCHRBanks == 0) 
		{
			mapped_addr = addr;
			return true;
		}
	}
	return false;
}

void Mapper002::reset()
{
	nPRGBankSelectLo = 0;
	nPRGBankSelectHi = nPRGBanks - 1;
}