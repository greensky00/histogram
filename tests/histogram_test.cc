#include "histogram.h"
#include "test_common.h"

#include <thread>
#include <vector>

#include <stdio.h>


int basic_test() {
    uint64_t n = 10000;
    Histogram h;

    for (uint64_t i=0; i<n; ++i) {
        h.add(i);
    }
    CHK_EQ(n, h.getTotal());

    uint64_t sum=0;
    for (auto& itr: h) {
        sum += itr.getCount();
    }
    CHK_EQ(n, sum);
    return 0;
}

void print_hist(Histogram::iterator& itr) {
    std::cout << itr.getLowerBound() << " - ";
    std::cout << itr.getUpperBound() << ": ";
    std::cout << itr.getCount() << std::endl;
}

int random_gap_test() {
    Histogram h;
    uint64_t n = 100000;
    uint64_t i, r1, r2;
    for (i=0; i<n; ++i) {
        r1 = std::rand() % 200;
        r2 = std::rand() % 100;
        if (!r2) r1 *= r1;
        h.add(r1);
    }

    for (auto& itr: h) {
        if (itr.getCount()) {
            print_hist(itr);
        }
    }

    printf("num: %d, avg: %d, max: %d\n",
           (int)h.getTotal(),
           (int)h.getAverage(),
           (int)h.getMax());
    printf("p50: %d, p95: %d, p99: %d, p99.9: %d\n",
           (int)h.estimate(50),
           (int)h.estimate(95),
           (int)h.estimate(99),
           (int)h.estimate(99.9));

    return 0;
}

int copy_test() {
    uint64_t n = 10000;
    Histogram h;

    for (uint64_t i=0; i<n; ++i) {
        h.add(i);
    }
    CHK_EQ(n, h.getTotal());

    Histogram h_copy = h;
    CHK_EQ(h.getTotal(), h_copy.getTotal());

    std::vector<uint64_t> counts;
    for (auto& itr: h) {
        counts.push_back(itr.getCount());
    }

    size_t idx = 0;
    for (auto& itr: h_copy) {
        CHK_EQ(counts[idx++], itr.getCount());
    }

    Histogram h_copy2;
    h_copy2 = h_copy;
    idx = 0;
    for (auto& itr: h_copy) {
        CHK_EQ(counts[idx++], itr.getCount());
    }

    return 0;
}

int main()
{
    TestSuite test;

    test.doTest("basic test", basic_test);

    test.options.printTestMessage = true;
    test.doTest("random gap test", random_gap_test);

    test.options.printTestMessage = false;
    test.doTest("copy test", copy_test);

    return 0;
}
