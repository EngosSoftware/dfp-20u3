#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../library/src/bid_conf.h"
#include "../library/src/bid_functions.h"

void display(char* f_name, const BID_UINT128 x)
{
    char buffer[500];
    printf("\n%s\n", f_name);
    printf("=====================================================================\n");
    printf("[%016llx,%016llx] ", x.w[1], x.w[0]);
    printf("%02x ", *pfpsf);
    bid128_to_string(buffer, x);
    printf("%s\n", buffer);
}

void display_from_string_rnd(char* input, const unsigned int rnd)
{
    char buffer[500];
    printf("%d \"%s\" ", rnd, input);
    *pfpsf = 0;
    const clock_t start = clock();
    const BID_UINT128 x = bid128_from_string(input, rnd);
    const clock_t end = clock();
    printf("[0x%016llx,0x%016llx] ", x.w[1], x.w[0]);
    printf("%02x ", *pfpsf);
    bid128_to_string(buffer, x);
    printf("%s ", buffer);
    const double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f[s]\n", time_spent);
}

void display_from_string(char* input, const unsigned int rnd)
{
    display_from_string_rnd(input, rnd);
}

void display_from_words(const BID_UINT64 hi, const BID_UINT64 lo)
{
    BID_UINT128 bid128;
    bid128.w[1] = hi;
    bid128.w[0] = lo;
    display("value", bid128);
}

void test_bid128_scalbn()
{
    BID_UINT128 bid128;
    bid128.w[1] = 0x000000028a080400;
    bid128.w[0] = 0x8002020024000000;
    const BID_UINT128 res = bid128_scalbn(bid128, -9, BID_ROUNDING_TO_NEAREST);
    display("bid128_scalbn", res);
}

void test_bid128_zeros()
{
    display_from_string("0e-6211",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e-6210",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e-6209",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e-6177",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e-6176",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e-6175",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e-6174",BID_ROUNDING_TO_NEAREST);
    printf("\n");
    display_from_string("0e+6110",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6111",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6112",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6209",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6210",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6211",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6212",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6212",BID_ROUNDING_TO_NEAREST);
    display_from_string("0e+6500",BID_ROUNDING_TO_NEAREST);
}

void test_bid128_ones()
{
    display_from_string("1e-6211",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e-6210",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e-6209",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e-6177",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e-6176",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e-6175",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e-6174",BID_ROUNDING_TO_NEAREST);
    printf("\n");
    display_from_string("1e+6110",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6112",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6113",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6143",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6144",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6145",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6210",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6211",BID_ROUNDING_TO_NEAREST);
    display_from_string("1e+6500",BID_ROUNDING_TO_NEAREST);
}

void bench_from_string()
{
    display_from_string_rnd("12", BID_ROUNDING_TO_NEAREST);
    display_from_string_rnd("938475E-03", BID_ROUNDING_TO_NEAREST);
    display_from_string_rnd("0.00003E-02", BID_ROUNDING_TO_NEAREST);
    display_from_string_rnd("9999999999999999999999999999999999", BID_ROUNDING_TO_NEAREST);
    display_from_string_rnd("+9999999999999999999999999999999999e+6111", BID_ROUNDING_TO_NEAREST);
    display_from_string_rnd("+1000000000000000000000000000000000e-6176", BID_ROUNDING_TO_NEAREST);
}

void test()
{
    BID_UINT64 x = 0x8000000000000000ull;
    BID_UINT128 v = bid128_from_uint64(x);
    display("a", v);
}

void nans()
{
    display_from_string("NaN",BID_ROUNDING_TO_NEAREST);
    display_from_string("QNaN",BID_ROUNDING_TO_NEAREST);
    display_from_string("-NaN",BID_ROUNDING_TO_NEAREST);
    display_from_string("-QNaN",BID_ROUNDING_TO_NEAREST);
    display_from_string("SNaN",BID_ROUNDING_TO_NEAREST);
    display_from_string("-SNaN",BID_ROUNDING_TO_NEAREST);
    display_from_string("Inf",BID_ROUNDING_TO_NEAREST);
    display_from_string("-Inf",BID_ROUNDING_TO_NEAREST);
}

void test_bid128_add(const BID_UINT64 xh, const BID_UINT64 xl, const BID_UINT64 yh, const BID_UINT64 yl)
{
    BID_UINT128 x, y;
    x.w[1] = xh;
    x.w[0] = xl;
    y.w[1] = yh;
    y.w[0] = yl;
    const BID_UINT128 res = bid128_add(x, y, 0);
    display("bid128_add", res);
}


void mul_128x64_to_128(BID_UINT128 Q128, BID_UINT64 A64, BID_UINT128 B128)
{
    BID_UINT64 ALBH_L = (A64) * (B128).w[1];

    BID_UINT64 CX64 = A64;
    BID_UINT64 CY64 = (B128).w[0];
    BID_UINT128 P128;

    BID_UINT64 CXH = (CX64) >> 32;
    BID_UINT64 CXL = (BID_UINT32)(CX64);
    BID_UINT64 CYH = (CY64) >> 32;
    BID_UINT64 CYL = (BID_UINT32)(CY64);
    BID_UINT64 PM = CXH * CYL;
    BID_UINT64 PH = CXH * CYH;
    BID_UINT64 PL = CXL * CYL;
    BID_UINT64 PM2 = CXL * CYH;
    PH += (PM >> 32);
    PM = (BID_UINT64)((BID_UINT32)PM) + PM2 + (PL >> 32);
    (P128).w[1] = PH + (PM >> 32);
    (P128).w[0] = (PM << 32) + (BID_UINT32)PL;

    Q128 = P128;

    (Q128).w[1] += ALBH_L;
}

int main()
{
    // bench_from_string();

    // test();

    // nans();

    // test_bid128_scalbn();

    // test_bid128_zeros();

    // test_bid128_ones();

    // display_from_words(0x378D8E63FFFFFFFF, 0x5FFFED09BEAD87C0);

    // test_bid128_add(0x0009000002080300, 0x415686c8259c1f86, 0x8008081481000000, 0x9642b65b40a018ca);

    // BID_UINT128 x;
    // x.w[1] = 17005591913777583919;
    // x.w[0] = 109951162781692;
    //
    // mul_128x64_to_128(x, 100, x);

    // display_from_string("12345678901234567890123456789012345",0);
    // display_from_string("12345678901234567890123456789012345",1);
    // display_from_string("12345678901234567890123456789012345",2);
    // display_from_string("12345678901234567890123456789012345",3);
    // display_from_string("12345678901234567890123456789012345",4);
    // display_from_string("0.0000000000000000000000000000000000001001",0);

    display_from_string("-9.9999999999999999999999999999999995",2);

    return EXIT_SUCCESS;
}
