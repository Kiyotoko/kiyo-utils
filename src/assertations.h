#ifndef ASSERTATIONS_H
#define ASSERTATIONS_H

#include <stdbool.h>
#include <stdlib.h>

#define fail exit(1)

void fail_with(const char* str);
void succeed_with(const char* str);

void assert_equalsi_with(int a, int b, const char* str);
void assert_equalsl_with(long a, long b, const char* str);
void assert_equalsf_with(float a, float b, const char* str);
void assert_equalsb_with(bool a, bool b, const char* str);
void assert_equalsp_with(void* a, void* b, const char* str);

#define assert_equals_with(X, Y, Z) _Generic((X), \
    int: assert_equalsi_with, \
    long: assert_equalsl_with, \
    float: assert_equalsf_with, \
    bool: assert_equalsb_with, \
    default: assert_equalsp_with \
)(X, Y, Z)

void assert_equalsi(int a, int b);
void assert_equalsl(long a, long b);
void assert_equalsf(float a, float b);
void assert_equalsb(bool a, bool b);
void assert_equalsp(void* a, void* b);

#define assert_equals(X, Y) _Generic((X), \
    int: assert_equalsi, \
    long: assert_equalsl, \
    float: assert_equalsf, \
    bool: assert_equalsb, \
    default: assert_equalsp \
)(X, Y)

void assert_true_with(bool v, const char* str);
void assert_false_with(bool v, const char* str);

void assert_true(bool v);
void assert_false(bool v);

void assert_success_with(int v, const char* str);
void assert_failure_with(int v, const char* str);

void assert_success(int v);
void assert_failure(int v);

#endif
