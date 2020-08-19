#define __AVX__
#define __AVX2__
#include <immintrin.h>

int main(void) {
    __m256i a, b, result;
    result = _mm256_add_epi64(a, b);
    return 0;
}
