#pragma once
#include <Windows.h>
#include <vector>

namespace Utils
{
    inline static std::vector<int> PatternToIntVector(const char* Pattern)
    {
        std::vector<int> PatternVector = std::vector<int>{};

        char* Start = const_cast<char*>(Pattern);

        char* End = const_cast<char*>(Pattern) + strlen(Pattern);

        for (char* Current = Start; Current < End; ++Current)
        {
            if (*Current == '?')
            {
                ++Current;

                PatternVector.push_back(-69);
            }
            else {
                PatternVector.push_back(strtoul(Current, &Current, 16));
            }
        }

        return PatternVector;
    };

    template<typename T>
    inline static T PatternScan(const char* Pattern, uint64_t Start)
    {
        const HMODULE GameModule = (HMODULE)Start;

        const IMAGE_DOS_HEADER* DOSHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(GameModule);
        const IMAGE_NT_HEADERS* NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<long long>(GameModule) + DOSHeader->e_lfanew);
        const size_t Size = NtHeaders->OptionalHeader.SizeOfImage;

        std::vector<int> PatternVector = PatternToIntVector(Pattern);

        uint8_t* Search = reinterpret_cast<uint8_t*>(Start);

        const size_t SizeOfPattern = PatternVector.size();
        const int* PatternData = PatternVector.data();

        for (int i = 0; i < Size - SizeOfPattern; ++i)
        {
            bool FoundSignature = true;

            for (int j = 0; j < SizeOfPattern; ++j)
            {
                if (Search[i + j] != PatternData[j] && PatternData[j] != -69)
                {
                    FoundSignature = false;
                    break;
                }
            }

            if (FoundSignature) {

                return reinterpret_cast<T>(&Search[i]);
            }
        }

        return reinterpret_cast<T>(nullptr);
    }

    inline uint64_t NtCurrentPeb() {
        return __readgsqword(0x60);
    }


    inline bool IsValidPointer(uintptr_t ptr) {
        return ptr != 0 && ptr >= 0x10000 && ptr <= 0x7FFFFFFFFFFF;
    }

}