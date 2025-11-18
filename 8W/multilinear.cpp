#include <iostream>
#include <vector>
#include <numeric>   // std::iota
#include <stdexcept> // std::runtime_error
#include <cmath>     // pow
#include <cstdint>   // std::int64_t

/**
 * @brief 모듈러 연산을 위한 간단한 정수 클래스.
 * 암호학적 연산에서는 유한체(Finite Field) 연산이 필수적입니다.
 * (실제 프로덕션에서는 BigInt 라이브러리를 사용해야 합니다.)
 */
class ModInt {
public:
    // 실제 암호학에서는 256비트 이상의 매우 큰 소수를 사용합니다.
    // 여기서는 ProofsArgsAndZK.pdf의 Figure 3.2 예시를 위해 5를 사용합니다.
    static constexpr std::int64_t MODULUS = 5;

    std::int64_t value;

    ModInt(std::int64_t v = 0) {
        value = v % MODULUS;
        if (value < 0) {
            value += MODULUS;
        }
    }

    ModInt operator+(const ModInt& other) const {
        return ModInt(value + other.value);
    }

    ModInt operator-(const ModInt& other) const {
        return ModInt(value - other.value);
    }

    ModInt operator*(const ModInt& other) const {
        return ModInt(value * other.value);
    }

    friend std::ostream& operator<<(std::ostream& os, const ModInt& m) {
        os << m.value;
        return os;
    }
};

/**
 * @brief 모든 n = 2^v 개의 라그랑주 기저 다항식 chi_w(r) 값을 O(n)에 계산합니다.
 * Lemma 3.8 및 Figure 3.3의 동적 프로그래밍(메모이제이션) 방식입니다.
 * @param r 평가 지점 (r_1, ..., r_v)
 * @return 모든 w에 대한 chi_w(r) 값의 벡터 (크기 n=2^v)
 */
std::vector<ModInt> compute_all_chi_values(const std::vector<ModInt>& r) {
    const std::size_t v = r.size();
    const std::size_t n = 1ULL << v; // 2^v
    std::vector<ModInt> chi_values(n);

    // 기저 케이스: 0-변수 다항식은 1입니다.
    chi_values[0] = 1;
    std::size_t current_size = 1;

    // v 단계를 반복합니다 (Figure 3.3의 각 레이어에 해당)
    for (std::size_t j = 0; j < v; ++j) {
        const ModInt r_j = r[j];
        const ModInt one_minus_r_j = ModInt(1) - r_j;

        // 배열을 뒤에서부터 순회하여 덮어쓰기 문제를 피합니다.
        for (std::size_t k_int = 0; k_int < current_size; ++k_int) {
            std::size_t k = current_size - 1 - k_int;
            
            ModInt old_val = chi_values[k];
            
            // w_j = 1 (상위 절반)에 해당하는 값을 계산합니다.
            chi_values[k + current_size] = old_val * r_j;
            
            // w_j = 0 (하위 절반)에 해당하는 값을 계산합니다.
            chi_values[k] = old_val * one_minus_r_j;
        }
        current_size *= 2;
    }

    return chi_values;
}

/**
 * @brief 두 벡터의 내적(inner product)을 계산합니다.
 * sum(a[i] * b[i])
 */
ModInt inner_product(const std::vector<ModInt>& a, const std::vector<ModInt>& b) {
    ModInt result = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        result = result + (a[i] * b[i]);
    }
    return result;
}

/**
 * @brief O(n) 시간에 다중 선형 확장(MLE) f_tilde(r)을 평가합니다. (Lemma 3.8)
 *
 * @param evaluations f(w) 값의 목록 (크기 n = 2^v).
 * 인덱스는 w의 이진 표현에 해당합니다 (e.g., w=(w1, w2) -> index = w1 + 2*w2)
 * @param r           평가할 무작위 점 (r_1, ..., r_v)
 * @return f_tilde(r)의 평가 값
 */
ModInt evaluate_mle(const std::vector<ModInt>& evaluations, const std::vector<ModInt>& r) {
    const std::size_t n = evaluations.size();
    const std::size_t v = r.size();

    // 입력 유효성 검사
    if (n == 0 || (n & (n - 1)) != 0) {
        throw std::runtime_error("Evaluations 벡토 크기는 2의 거듭제곱이어야 합니다.");
    }
    if (n != (1ULL << v)) {
        throw std::runtime_error("evaluations.size() != 2^r.size()");
    }

    // 1. 모든 chi_w(r) 값을 O(n)에 계산합니다. 
    std::vector<ModInt> chi_values = compute_all_chi_values(r);

    // 2. f(w) 값들과 chi_w(r) 값들의 내적을 O(n)에 계산합니다. 
    return inner_product(evaluations, chi_values);
}

// --- 예제 실행 (Figure 3.1 & 3.2 기반) ---
int main() {
    // 1. 입력 설정 (ProofsArgsAndZK.pdf, Figure 3.1 )
    // f: {0, 1}^2 -> F_5
    // f(0,0) = 1
    // f(0,1) = 2
    // f(1,0) = 1
    // f(1,1) = 4
    
    // 우리 구현의 인덱싱: w=(w1, w2) -> index = w1 + 2*w2
    // f(0,0) -> index 0
    // f(1,0) -> index 1
    // f(0,1) -> index 2
    // f(1,1) -> index 3
    std::vector<ModInt> f_evaluations = {1, 1, 2, 4};
    const std::size_t v = 2; // 변수 개수

    // 2. 평가할 지점 'r' 설정 (Figure 3.2 에서 (2, 3)을 선택)
    std::vector<ModInt> r = {2, 3};

    // 3. MLE 평가 실행
    try {
        ModInt result = evaluate_mle(f_evaluations, r);

        std::cout << "f_tilde(r) 평가 (Lemma 3.8 구현)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "필드(Field): F_" << ModInt::MODULUS << std::endl;
        std::cout << "입력 함수 f(w) (인덱스 순): {";
        for(std::size_t i = 0; i < f_evaluations.size(); ++i) {
            std::cout << f_evaluations[i] << (i == f_evaluations.size() - 1 ? "" : ", ");
        }
        std::cout << "}" << std::endl;
        std::cout << "평가 지점 r: (" << r[0] << ", " << r[1] << ")" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "계산 결과: f_tilde(" << r[0] << ", " << r[1] << ") = " << result << std::endl;
        std::cout << "기대 값 (Figure 3.2): 1" << std::endl;

        // 다른 지점 테스트: r = (4, 1) -> f_tilde(4, 1) = 0 (Figure 3.2)
        r = {4, 1};
        result = evaluate_mle(f_evaluations, r);
        std::cout << "\n테스트 2: f_tilde(" << r[0] << ", " << r[1] << ") = " << result << std::endl;
        std::cout << "기대 값 (Figure 3.2): 0" << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "오류 발생: " << e.what() << std::endl;
    }

    return 0;
}