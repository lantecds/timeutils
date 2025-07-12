#include <a_samp>
#include <timeutils>

// Test data - various Unix timestamps
#define TEST_TIMESTAMP_1 (1752235200)  // July 11, 2025 12:00:00 UTC
#define TEST_TIMESTAMP_2 (1640995200)  // January 1, 2022 00:00:00 UTC
#define TEST_TIMESTAMP_3 (1704067200)  // January 1, 2024 00:00:00 UTC
#define TEST_TIMESTAMP_4 (gettime())   // Current time

// Test time differences
#define TEST_DIFF_1 (93784)           // 1 day 2 hours 3 minutes
#define TEST_DIFF_2 (3600)            // 1 hour
#define TEST_DIFF_3 (86400)           // 1 day
#define TEST_DIFF_4 (31536000)        // 1 year
#define TEST_DIFF_5 (-3600)           // -1 hour (future)

public OnGameModeInit()
{
    print("=== timeutils.inc Test Suite ===");
    print("Starting the tests...");
    
    // Run all tests
    TestUnixToHumanReadable();
    TestIsLeapYear();
    TestUnixToDateTime();
    TestUnixToCustomDate();
    TestRelativeTime();
    TestUnixToISO8601();
    TestIsValidDate();
    TestGetWeekdayName();
    
    print("=== All Tests Complete ===");
    print("Check the console output above for results.");
    return 1;
}

TestUnixToHumanReadable()
{
    print("--- Testing UnixToHumanReadable() ---");
    
    // Test 1: Basic functionality
    new result[128];
    result = UnixToHumanReadable(TEST_DIFF_1);
    printf("Test 1: %d seconds = %s", TEST_DIFF_1, result);
    
    // Test 2: Short form
    result = UnixToHumanReadable(TEST_DIFF_1, true);
    printf("Test 2: %d seconds (short) = %s", TEST_DIFF_1, result);
    
    // Test 3: Biggest unit only
    result = UnixToHumanReadable(TEST_DIFF_1, false, true);
    printf("Test 3: %d seconds (biggest only) = %s", TEST_DIFF_1, result);
    
    // Test 4: One hour
    result = UnixToHumanReadable(TEST_DIFF_2);
    printf("Test 4: %d seconds = %s", TEST_DIFF_2, result);
    
    // Test 5: One day
    result = UnixToHumanReadable(TEST_DIFF_3);
    printf("Test 5: %d seconds = %s", TEST_DIFF_3, result);
    
    // Test 6: One year
    result = UnixToHumanReadable(TEST_DIFF_4);
    printf("Test 6: %d seconds = %s", TEST_DIFF_4, result);
    
    // Test 7: Zero seconds
    result = UnixToHumanReadable(0);
    printf("Test 7: 0 seconds = %s", result);
    
    print("");
}

TestIsLeapYear()
{
    print("--- Testing IsLeapYear() ---");
    
    printf("Test 1: 2024 is leap year = %s", IsLeapYear(2024) ? "true" : "false");
    printf("Test 2: 2000 is leap year = %s", IsLeapYear(2000) ? "true" : "false");
    printf("Test 3: 2020 is leap year = %s", IsLeapYear(2020) ? "true" : "false");
    
    printf("Test 4: 2023 is leap year = %s", IsLeapYear(2023) ? "true" : "false");
    printf("Test 5: 2100 is leap year = %s", IsLeapYear(2100) ? "true" : "false");
    printf("Test 6: 1900 is leap year = %s", IsLeapYear(1900) ? "true" : "false");
    
    print("");
}

TestUnixToDateTime()
{
    print("--- Testing UnixToDateTime() ---");
    
    printf("Test 1: %d = %s", TEST_TIMESTAMP_1, UnixToDateTime(TEST_TIMESTAMP_1));
    printf("Test 2: %d = %s", TEST_TIMESTAMP_2, UnixToDateTime(TEST_TIMESTAMP_2));
    printf("Test 3: %d = %s", TEST_TIMESTAMP_3, UnixToDateTime(TEST_TIMESTAMP_3));
    printf("Test 4: Current time = %s", UnixToDateTime(TEST_TIMESTAMP_4));
    
    print("");
}

TestUnixToCustomDate()
{
    print("--- Testing UnixToCustomDate() ---");
    
    printf("Test 1: Full format = %s", UnixToCustomDate(TEST_TIMESTAMP_1));
    printf("Test 2: Short month names = %s", UnixToCustomDate(TEST_TIMESTAMP_1, true, true));
    printf("Test 3: Date only = %s", UnixToCustomDate(TEST_TIMESTAMP_1, false, false));
    printf("Test 4: Date only (short) = %s", UnixToCustomDate(TEST_TIMESTAMP_1, false, true));
    
    print("");
}

TestRelativeTime()
{
    print("--- Testing RelativeTime() ---");
    
    printf("Test 1: Past time = %s", RelativeTime(TEST_DIFF_2));
    printf("Test 2: Future time = %s", RelativeTime(TEST_DIFF_5));
    printf("Test 3: Past day = %s", RelativeTime(TEST_DIFF_3));
    printf("Test 4: Past year = %s", RelativeTime(TEST_DIFF_4));
    
    print("");
}

TestUnixToISO8601()
{
    print("--- Testing UnixToISO8601() ---");
    
    printf("Test 1: %d = %s", TEST_TIMESTAMP_1, UnixToISO8601(TEST_TIMESTAMP_1));
    printf("Test 2: %d = %s", TEST_TIMESTAMP_2, UnixToISO8601(TEST_TIMESTAMP_2));
    printf("Test 3: %d = %s", TEST_TIMESTAMP_3, UnixToISO8601(TEST_TIMESTAMP_3));
    printf("Test 4: Current time = %s", UnixToISO8601(TEST_TIMESTAMP_4));
    
    print("");
}

TestIsValidDate()
{
    print("--- Testing IsValidDate() ---");
    
    printf("Test 1: 2024-02-29 (leap year) = %s", IsValidDate(2024, 2, 29) ? "valid" : "invalid");
    printf("Test 2: 2024-12-31 = %s", IsValidDate(2024, 12, 31) ? "valid" : "invalid");
    printf("Test 3: 2024-01-01 = %s", IsValidDate(2024, 1, 1) ? "valid" : "invalid");
    
    printf("Test 4: 2023-02-29 (non-leap) = %s", IsValidDate(2023, 2, 29) ? "valid" : "invalid");
    printf("Test 5: 2024-02-30 = %s", IsValidDate(2024, 2, 30) ? "valid" : "invalid");
    printf("Test 6: 2024-13-01 = %s", IsValidDate(2024, 13, 1) ? "valid" : "invalid");
    printf("Test 7: 2024-00-01 = %s", IsValidDate(2024, 0, 1) ? "valid" : "invalid");
    
    print("");
}

TestGetWeekdayName()
{
    print("--- Testing GetWeekdayName() ---");
    
    printf("Test 1: %d = %s", TEST_TIMESTAMP_1, GetWeekdayName(TEST_TIMESTAMP_1));
    printf("Test 2: %d = %s", TEST_TIMESTAMP_2, GetWeekdayName(TEST_TIMESTAMP_2));
    printf("Test 3: %d = %s", TEST_TIMESTAMP_3, GetWeekdayName(TEST_TIMESTAMP_3));
    printf("Test 4: Current time = %s", GetWeekdayName(TEST_TIMESTAMP_4));

    print("");
}