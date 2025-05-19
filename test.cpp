#include "test.h"
#include <cstdio>
#include <vector>

static std::vector<TestCase>& getTests() {
    static std::vector<TestCase> tests;
    return tests;
}

void addTest(const char* name, TestFunction function) {
    getTests().push_back({name, function});
}

void runAllTests() {
    printf("Running %zu tests...\n\n", getTests().size());
    
    int passed = 0;
    for (const auto& test : getTests()) {
        printf("TEST %s... ", test.name);
        try {
            test.function();
            printf("PASSED\n");
            passed++;
        } catch (const char* msg) {
            printf("FAILED: %s\n", msg);
        } catch (...) {
            printf("FAILED with unknown error\n");
        }
    }
    
    printf("\nTest results: %d/%zu passed\n", passed, getTests().size());
}
