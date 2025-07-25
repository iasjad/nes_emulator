#include "Cartridge.h"



Cartridge::Cartridge(const std::string& sFileName)
{
	struct sHeader
	{
		char name[4];
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		char unused[5];
	} header;

	bImageValid = false;

	std::ifstream ifs;
	ifs.open(sFileName, std::ifstream::binary);
	if (ifs.is_open())
	{
		ifs.read((char*)&header, sizeof(sHeader));

		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		hw_mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

		uint8_t nFileType = 1;

		if ((header.mapper2 & 0x0C) == 0x08) nFileType = 2;

		if (nFileType == 0)
		{

		}

		if (nFileType == 1)
		{
			nPRGBanks = header.prg_rom_chunks;
			vPRGMemory.resize(nPRGBanks * 16384);
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

			nCHRBanks = header.chr_rom_chunks;
			if (nCHRBanks == 0)
			{
				vCHRMemory.resize(8192);
			}
			else
			{
				vCHRMemory.resize(nCHRBanks * 8192);
			}
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}

		if (nFileType == 2)
		{
			nPRGBanks = ((header.prg_ram_size & 0x07) << 8) | header.prg_rom_chunks;
			vPRGMemory.resize(nPRGBanks * 16384);
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());


			nCHRBanks = ((header.prg_ram_size & 0x38) << 8) | header.chr_rom_chunks;
			vCHRMemory.resize(nCHRBanks * 8192);
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}

		switch (nMapperID)
		{
		case   0: pMapper = std::make_shared<Mapper000>(nPRGBanks, nCHRBanks); break;
		case   1: pMapper = std::make_shared<Mapper001>(nPRGBanks, nCHRBanks); break;
		case   2: pMapper = std::make_shared<Mapper002>(nPRGBanks, nCHRBanks); break;
		case   3: pMapper = std::make_shared<Mapper003>(nPRGBanks, nCHRBanks); break;
		case   4: pMapper = std::make_shared<Mapper004>(nPRGBanks, nCHRBanks); break;
		case  66: pMapper = std::make_shared<Mapper066>(nPRGBanks, nCHRBanks); break;

		}

		bImageValid = true;
		std::cout << "[DEBUG] Mapper ID: " << (int)nMapperID << std::endl;
		std::cout << "[DEBUG] PRG ROM Chunks: " << (int)header.prg_rom_chunks << std::endl;
		std::cout << "[DEBUG] CHR ROM Chunks: " << (int)header.chr_rom_chunks << std::endl;
		std::cout << "[DEBUG] PRG ROM Size: " << vPRGMemory.size() << " bytes" << std::endl;
		std::cout << "[DEBUG] CHR ROM Size: " << vCHRMemory.size() << " bytes" << std::endl;
		std::cout << "[DEBUG] Mapper pointer valid: " << (pMapper != nullptr ? "YES" : "NO") << std::endl;
		ifs.close();
	}

}


Cartridge::~Cartridge()
{
}

bool Cartridge::ImageValid()
{
	return bImageValid;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t& data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapRead(addr, mapped_addr, data)) 
	{
		if (mapped_addr == 0xFFFFFFFF)
		{
			return true;
		}
		else
		{
			data = vPRGMemory[mapped_addr];
		}
		return true;
	}
	else
		return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapWrite(addr, mapped_addr, data))
	{
		if (mapped_addr == 0xFFFFFFFF)
		{
			return true;
		}
		else
		{
			vPRGMemory[mapped_addr] = data;
		}
		return true;
	}
	else
		return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t& data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapRead(addr, mapped_addr))
	{
		data = vCHRMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapWrite(addr, mapped_addr))
	{
		vCHRMemory[mapped_addr] = data;
		return true;
	}
	else
		return false;
}


void Cartridge::reset()
{

	if (pMapper != nullptr)
		pMapper->reset();
}


MIRROR Cartridge::Mirror()
{
	MIRROR m = pMapper->mirror();
	if (m == MIRROR::HARDWARE)
	{
		
		return hw_mirror;
	}
	else
	{
		
		return m;
	}
}

std::shared_ptr<Mapper> Cartridge::GetMapper()
{
	return pMapper;
}