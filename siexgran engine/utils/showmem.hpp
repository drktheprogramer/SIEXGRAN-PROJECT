#pragma once 
#include <cstdint>
#include <cstdio>


struct memVisor {
	
	//static void show(T const* mem) {std::printf("%p\n",(void*)reinterpret_cast<std::uint8_t const*>(&mem));}
	template<typename T>
	void print(T& mem) {
		auto* aux = reinterpret_cast<std::uint8_t const*>(&mem);
		std::printf("#### SHOWING AN OBJECT ####\n");
		show(aux,sizeof(mem));
	}
	
	void show(auto const* mem, std::size_t size, std::size_t const width = defaultWidth) {
		auto* aux = reinterpret_cast<std::uint8_t const*>(mem);
		std::printf("#### SHOWING A POINTER(CONTENT) ####\n");
		show(aux,size,width);
	}
	
	void show(std::uint8_t const* mem, std::size_t size, std::size_t const width = defaultWidth) {
		std::printf("\e[0;30m");
		std::printf("\e[43m");
		
		std::printf("         ADDRESS           ||  00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\n");
		std::printf("\033[0m");
		std::printf("\e[1;33m");
		std::printf("---------------------------||----------------------------------------------------------------\n");
		
		for(std::size_t i{}; i<calculateLines(size, width); ++i) {
			showMemoryLine(mem, width);
			mem += width;
	 	}
	 	std::printf("\e[1;33m");
		std::printf("---------------------------||----------------------------------------------------------------\n");
		std::printf("\033[0m");
	}
	
	
private:
	static constexpr std::size_t defaultWidth { 16 };	
	std::size_t calculateLines(std::size_t const size, std::size_t const width = defaultWidth) {
		auto const lines { size / width };
		if((size & 0xF) != 0)
			return lines +1;
		return lines;
	}
	void showMemoryLine(std::uint8_t const* mem, std::size_t const width = defaultWidth) {
		std::printf("\e[1;33m");
		std::printf("%16p           ||",(void*)mem);
		for(std::size_t i{}; i< width; ++i) {
			std::printf("\033[0m");
			std::printf("  %02X", mem[i]);	
		}
		
		
	
		std::printf("\e[1;33m");
		std::printf(" || ");
		for(std::size_t i{};i<width;++i) {
			auto c = (mem[i] > 31 && mem[i] < 128) ? mem[i] : 46;
			std::printf("\033[0m");
			//auto c = mem[i];
			std::printf("%c", c);
		}
		
		std::printf("\e[1;33m");
		std::printf(" ||\n");
		std::printf("\033[0m");
	}
};


