#include <iostream>

void library() {
    long k, m, d;
    std::cin >> k >> m >> d;
    long count = 1;
    bool first_week_pass = true;
    while (d != 1) {
        if (d < 6) m += k;
        if (m < count) {
            first_week_pass = false;
            break;
        }
        m -= count++;
        d = d % 7 + 1;
    }
    if (first_week_pass) {
        while (m + 5 * k >= 7 * count + 21) {
            m = m + 5 * k - (7 * count + 21);
            count += 7;
        }
        while (true) {
            if (d < 6) m += k;
            if (m < count) {
                break;
            }
            m -= count++;
            d = d % 7 + 1;
        }
    }
    std::cout << count - 1;
}

int main() {
    library();
    return 0;
}
