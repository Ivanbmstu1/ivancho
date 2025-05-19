#ifndef TEST_H
#define TEST_H

typedef void (*TestFunction)();

struct TestCase {
    const char* name;
    TestFunction function;
};

void addTest(const char* name, TestFunction function);
void runAllTests();

#endif // TEST_H
