#include <string>
#include <cstdint>

class HashFuncGen {
public:
    uint32_t operator()(const std::string& s) const {
        uint32_t hash = FNV_OFFSET_BASIS;
        for (unsigned char c : s) {
            hash ^= c;
            hash *= FNV_PRIME;
        }
        return hash;
    }

private:
    static constexpr uint32_t FNV_OFFSET_BASIS = 2166136261u;
    static constexpr uint32_t FNV_PRIME = 16777619u;
};
