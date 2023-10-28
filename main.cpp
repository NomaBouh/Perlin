#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

class PerlinNoise {
private:
    std::vector<int> p;

    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double grad(int hash, double x) {
        int h = hash & 15;
        double grad = 1.0 + (h & 7);  // Gradient value is one of 1, 2, ..., 8
        return (h & 8) ? -grad : grad;  // and a random an orientation
    }

    double lerp(double a, double b, double x) {
        return a + x * (b - a);
    }

public:
    PerlinNoise() {
        p.resize(512);
        std::iota(p.begin(), p.end(), 0);
        std::random_shuffle(p.begin(), p.end());
        for (unsigned i = 0; i < 256; ++i) {
            p[256 + i] = p[i];
        }
    }

    double noise(double x) {
        int X = (int)floor(x) & 255;
        x -= floor(x);
        double u = fade(x);
        return lerp(grad(p[X], x), grad(p[X + 1], x - 1), u);
    }
};

int main() {
    PerlinNoise pn;
    for (double x = 0; x < 10; x += 0.1) {
        double value = pn.noise(x);
        // Do something with value, for instance:
        std::cout << value << std::endl;
    }

    return 0;
}
