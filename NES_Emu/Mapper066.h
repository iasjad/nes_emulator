#pragma once
#include "Mapper.h"
class Mapper066 : public Mapper
{
public:
	Mapper066(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper066();

	bool cpuMapRead(uint16_t addr, uint32_t& mapped_addr, uint8_t& data) override;
	bool cpuMapWrite(uint16_t addr, uint32_t& mapped_addr, uint8_t data = 0) override;
	bool ppuMapRead(uint16_t addr, uint32_t& mapped_addr) override;
	bool ppuMapWrite(uint16_t addr, uint32_t& mapped_addr) override;
	void reset() override;

private:
	uint8_t nCHRBankSelect = 0x00;
	uint8_t nPRGBankSelect = 0x00;
};