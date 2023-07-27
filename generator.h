#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>
#include <vector>

class Generator {
public:
    Generator() = default;
    std::vector<bool> generateBlocks(const int xNum, const int yNum) {

        const size_t size{static_cast<size_t>(xNum) * static_cast<size_t>(yNum)};
        std::vector<bool> result(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::bernoulli_distribution d(0.25);
        for (size_t n{}; n < size; ++n)
            result[n] = d(gen);

        return result;
    }
};

#endif // GENERATOR_H
