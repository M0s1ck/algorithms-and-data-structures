#include <string>
#include <vector>
#include <random>
#include <cstdint>
#include <limits>

class RandomStreamGen {
public:
    explicit RandomStreamGen(uint32_t seed = std::random_device{}())
        : rng(seed),
          lenDist(1, 30),
          charDist(0, static_cast<int>(alphabet.size() - 1)) {}

    std::string next() {
        size_t len = lenDist(rng);
        std::string s;
        s.reserve(len);
        for (size_t i = 0; i < len; ++i) {
            s.push_back(alphabet[charDist(rng)]);
        }
        return s;
    }

    std::vector<std::string> generateChunk(size_t chunkSize) {
        std::vector<std::string> chunk;
        chunk.reserve(chunkSize);
        for (size_t i = 0; i < chunkSize; ++i) {
            chunk.push_back(next());
        }
        return chunk;
    }

private:
    std::mt19937 rng;
    std::uniform_int_distribution<size_t> lenDist;
    std::uniform_int_distribution<int> charDist;

    static inline const std::string alphabet =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789-";
};
