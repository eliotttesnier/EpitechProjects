#include <criterion/criterion.h>
#include <strings.h>

Test(ffs, zero_input)
{
    cr_assert_eq(ffs(0), 0);
}

Test(ffs, power_of_two)
{
    cr_assert_eq(ffs(1), 1);
    cr_assert_eq(ffs(2), 2);
    cr_assert_eq(ffs(4), 3);
    cr_assert_eq(ffs(8), 4);
    cr_assert_eq(ffs(16), 5);
    cr_assert_eq(ffs(32), 6);
    cr_assert_eq(ffs(64), 7);
    cr_assert_eq(ffs(128), 8);
}

Test(ffs, random_numbers)
{
    cr_assert_eq(ffs(123), 1);
    cr_assert_eq(ffs(456), 4);
    cr_assert_eq(ffs(789), 1);
}

Test(ffs, negative_numbers)
{
    cr_assert_eq(ffs(-8), 4);
    cr_assert_eq(ffs(-123), 1);
}

Test(ffs, all_bits_set)
{
    cr_assert_eq(ffs(-1), 1);
}

Test(ffs, alternating_bits)
{
    cr_assert_eq(ffs(0x55555555), 1);  // 0101 0101...
    cr_assert_eq(ffs(0xAAAAAAAA), 2);  // 1010 1010...
}

Test(ffs, sparse_bits)
{
    cr_assert_eq(ffs(1UL << 31), 32);
    cr_assert_eq(ffs(1UL << 15), 16);
    cr_assert_eq(ffs(1UL << 23), 24);
}

Test(ffs, consecutive_ones)
{
    cr_assert_eq(ffs(0x3), 1);    // 11
    cr_assert_eq(ffs(0x7), 1);    // 111
    cr_assert_eq(ffs(0xF), 1);    // 1111
    cr_assert_eq(ffs(0xFF), 1);   // 11111111
}

Test(ffs, boundary_values)
{
    cr_assert_eq(ffs(0x80000000), 32);  // Highest bit set
    cr_assert_eq(ffs(0x7FFFFFFF), 1);   // All bits except highest
    cr_assert_eq(ffs(0xFFFFFFFF), 1);   // All bits set
}

Test(ffs, complex_patterns)
{
    cr_assert_eq(ffs(0x1010), 5);       // Sparse pattern
    cr_assert_eq(ffs(0x8040), 7);       // Two bits set
    cr_assert_eq(ffs(0xF0F0F0F0), 5);   // Alternating nibbles
}

Test(ffs, more_negative_numbers)
{
    cr_assert_eq(ffs(-2), 2);
    cr_assert_eq(ffs(-4), 3);
    cr_assert_eq(ffs(-32768), 16);
    cr_assert_eq(ffs(-2147483648), 32);
}

Test(ffs, more_edge_cases)
{
    cr_assert_eq(ffs(0x80000001), 1);    // Highest and lowest bits set
    cr_assert_eq(ffs(0xFFFFFFFE), 2);    // All bits except lowest
    cr_assert_eq(ffs(-0x80000000), 32);  // Minimum negative number
    cr_assert_eq(ffs(0x00000002), 2);    // Single bit in second position
}

Test(ffs, specific_patterns)
{
    cr_assert_eq(ffs(0x0F0F0F0F), 1);    // Checkerboard pattern
    cr_assert_eq(ffs(0xF0F0F0F0), 5);    // Inverse checkerboard
    cr_assert_eq(ffs(0x00FFFFFF), 1);    // 24-bit mask
    cr_assert_eq(ffs(0xFFFF0000), 17);   // Upper 16 bits set
}
