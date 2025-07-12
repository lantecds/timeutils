#if defined _inc_lif_timeutils
    #endinput
#endif
#define _inc_lif_timeutils

#if !defined SERVER_TIME_ZONE
    #define SERVER_TIME_ZONE (0)
#endif

#define SECONDS_PER_MINUTE (60)
#define SECONDS_PER_HOUR (3600)
#define SECONDS_PER_DAY (86400)
#define SECONDS_PER_WEEK (604800)
#define SECONDS_PER_MONTH (2592000)
#define SECONDS_PER_YEAR (31536000)

#define EPOCH_YEAR (1970)
#define MAX_YEAR (2100)

/**
 * Converts a time difference into human-readable format.
 * 
 * @param unixdifference  Time difference in seconds (positive or negative)
 * @param shortform       Use abbreviated units (e.g., "h" instead of "hours")
 * @param biggestunitonly Show only the largest significant unit
 * 
 * @return Formatted time string (e.g., "2 days 3 hours" or "5y 2m")
 * 
 * Example:
 *   UnixToHumanReadable(93784)                 -> "1 day 2 hours 3 minutes"
 *   UnixToHumanReadable(93784, true)           -> "1d 2h 3m"
 *   UnixToHumanReadable(93784, false, true)    -> "1 day"
 */
stock UnixToHumanReadable(unixdifference, bool:shortform = false, bool:biggestunitonly = false)
{
    new years, months, weeks, days, hours, minutes, seconds;
    new result[128];
    new bool:hasContent = false;

    // Calculate time units.
    years = unixdifference / SECONDS_PER_YEAR;
    unixdifference %= SECONDS_PER_YEAR;

    months = unixdifference / SECONDS_PER_MONTH;
    unixdifference %= SECONDS_PER_MONTH;

    weeks = unixdifference / SECONDS_PER_WEEK;
    unixdifference %= SECONDS_PER_WEEK;

    days = unixdifference / SECONDS_PER_DAY;
    unixdifference %= SECONDS_PER_DAY;

    hours = unixdifference / SECONDS_PER_HOUR;
    unixdifference %= SECONDS_PER_HOUR;

    minutes = unixdifference / SECONDS_PER_MINUTE;
    unixdifference %= SECONDS_PER_MINUTE;

    seconds = unixdifference;

    new labelYear[] = " year", labelMonth[] = " month", labelWeek[] = " week";
    new labelDay[] = " day", labelHour[] = " hour", labelMinute[] = " minute", labelSecond[] = " second";

    if (shortform)
    {
        labelYear = "y"; labelMonth = "mo"; labelWeek = "w";
        labelDay = "d"; labelHour = "h"; labelMinute = "m"; labelSecond = "s";
    }
    
    if (years > 0)
    {
        format(result, sizeof(result), "%s%i%s%s", (hasContent ? " " : ""), years, labelYear, (years == 1 || shortform ? "" : "s"));
        hasContent = true;
        if (biggestunitonly) return result;
    }
    if (months > 0)
    {
        format(result, sizeof(result), "%s%s%i%s%s", result, (hasContent ? " " : ""), months, labelMonth, (months == 1 || shortform ? "" : "s"));
        hasContent = true;
        if (biggestunitonly) return result;
    }
    if (weeks > 0)
    {
        format(result, sizeof(result), "%s%s%i%s%s", result, (hasContent ? " " : ""), weeks, labelWeek, (weeks == 1 || shortform ? "" : "s"));
        hasContent = true;
        if (biggestunitonly) return result;
    }
    if (days > 0)
    {
        format(result, sizeof(result), "%s%s%i%s%s", result, (hasContent ? " " : ""), days, labelDay, (days == 1 || shortform ? "" : "s"));
        hasContent = true;
        if (biggestunitonly) return result;
    }
    if (hours > 0)
    {
        format(result, sizeof(result), "%s%s%i%s%s", result, (hasContent ? " " : ""), hours, labelHour, (hours == 1 || shortform ? "" : "s"));
        hasContent = true;
        if (biggestunitonly) return result;
    }
    if (minutes > 0)
    {
        format(result, sizeof(result), "%s%s%i%s%s", result, (hasContent ? " " : ""), minutes, labelMinute, (minutes == 1 || shortform ? "" : "s"));
        hasContent = true;
        if (biggestunitonly) return result;
    }
    if (seconds > 0)
    {
        format(result, sizeof(result), "%s%s%i%s%s", result, (hasContent ? " " : ""), seconds, labelSecond, (seconds == 1 || shortform ? "" : "s"));
        hasContent = true;
        if (biggestunitonly) return result;
    }

    if (!hasContent)
    {
        format(result, sizeof(result), "0%s", labelSecond);
    }
    return result;
}

/**
 * Determines if a year is a leap year.
 * 
 * @param year  4-digit year
 * 
 * @return true if leap year, false otherwise
 * 
 * Example:
 *   IsLeapYear(2024) // true
 */
stock bool:IsLeapYear(year)
{
    return (!(year % 4) && (year % 100 || !(year % 400)));
}

static stock UnixToComponents(timestamp, &year, &month, &day, &hour, &minute, &second)
{
    new days, seconds;
    new monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (year = EPOCH_YEAR; year <= MAX_YEAR; year++)
    {
        days = 365 + (IsLeapYear(year) ? 1 : 0);
        seconds = days * SECONDS_PER_DAY;

        if (seconds > timestamp)
		{
			break;
		}

        timestamp -= seconds;
    }

    if (IsLeapYear(year))
    {
        monthDays[1] = 29;
    }
    
    for (month = 1; month <= 12; month++)
    {
        seconds = monthDays[month - 1] * SECONDS_PER_DAY;

        if (seconds > timestamp)
		{
			break;
		}
            

        timestamp -= seconds;
    }

    day = timestamp / SECONDS_PER_DAY + 1;
    timestamp %= SECONDS_PER_DAY;

    hour = timestamp / SECONDS_PER_HOUR + SERVER_TIME_ZONE;
    timestamp %= SECONDS_PER_HOUR;

    minute = timestamp / SECONDS_PER_MINUTE;
    second = timestamp % SECONDS_PER_MINUTE;
}

/**
 * Converts Unix timestamp to formatted date/time string.
 * 
 * @param timestamp  Unix timestamp to convert
 * 
 * @return String in "HH:MM DD/MM/YYYY" format
 * 
 * Example:
 *   UnixToDateTime(1752235200)  -> "12:00 11/07/2025"
 */
stock UnixToDateTime(timestamp)
{
    new year, month, day, hour, minute, second;
    new result[32];

    UnixToComponents(timestamp, year, month, day, hour, minute, second);

    format(result, sizeof(result), "%02i:%02i %02i/%02i/%04i", hour, minute, day, month, year);
    return result;
}

/**
 * Converts a Unix timestamp to a customizable date format.
 *
 * Parameters:
 *   timestamp  - The Unix timestamp to convert.
 *   showtime   - Whether to include the time in the output.
 *   shortform  - Whether to use short form for month names (e.g., "Jul" instead of "July").
 *
 * Returns:
 *   A formatted date string based on the provided options.
 *
 * Examples:
 *   UnixToCustomDate(1752235200)               -> "12:00 11 July 2025"
 *   UnixToCustomDate(1752235200, true, true)   -> "12:00 11 Jul 2025"
 *   UnixToCustomDate(1752235200, false, true)  -> "11 Jul 2025"
 *   UnixToCustomDate(1752235200, false, false) -> "11 July 2025"
 */
stock UnixToCustomDate(timestamp, bool:showtime = true, bool:shortform = false)
{
    new year, month, day, hour, minute, second;
    new result[64];

    new const months[][] = { "January", "February", "March", "April", "May", "June", 
                             "July", "August", "September", "October", "November", "December" };
    new const shortMonths[][] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    UnixToComponents(timestamp, year, month, day, hour, minute, second);

    if (showtime)
    {
        format(result, sizeof(result), "%02i:%02i ", hour, minute);
    }

    format(result, sizeof(result), "%s%02i %s", result, day, shortform ? shortMonths[month - 1] : months[month - 1]);

    format(result, sizeof(result), "%s %04i", result, year);

    return result;
}


/**
 * Generates relative time expression from time difference.
 * 
 * @param unixdifference  Time delta in seconds
 * 
 * @return Relative time string (future: "in X", past: "X ago")
 * 
 * Example:
 *   RelativeTime(-3600)      -> "in 1 hour"
 *   RelativeTime(3600)       -> "1 hour ago"
 */
stock RelativeTime(unixdifference)
{
    new result[64];
    if (unixdifference < 0)
    {
        unixdifference = -unixdifference;
        format(result, sizeof(result), "in %s", UnixToHumanReadable(unixdifference, false, true));
        return result;
    }
    format(result, sizeof(result), "%s ago", UnixToHumanReadable(unixdifference, false, true));
    return result;
}



/**
 * Formats timestamp according to ISO 8601 standard.
 * 
 * @param timestamp  Unix timestamp to format
 * 
 * @return ISO 8601 formatted string (YYYY-MM-DDTHH:MM:SSZ)
 * 
 * Example:
 *   UnixToISO8601(1752235200)  -> "2025-07-11T12:00:00Z"
 */
stock UnixToISO8601(timestamp)
{
    new year, month, day, hour, minute, second;
    UnixToComponents(timestamp, year, month, day, hour, minute, second);
    new result[32];
    format(result, sizeof(result), "%04i-%02i-%02iT%02i:%02i:%02iZ", year, month, day, hour, minute, second);
    return result;
}

/**
 * Validates Gregorian calendar date.
 * 
 * @param year   Year
 * @param month  Month (1-12)
 * @param day    Day of month
 * 
 * @return true if valid date, false otherwise
 * 
 * Example:
 *   IsValidDate(2024, 2, 29)   ->  true
     IsValidDate(2025, 2, 29)   ->  false
 */
stock bool:IsValidDate(year, month, day)

{
    new monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (IsLeapYear(year))
    {
        monthDays[1] = 29; // Adjust February for leap year
    }
    return month >= 1 && month <= 12 && day >= 1 && day <= monthDays[month - 1];
}

/**
 * Gets weekday name from Unix timestamp.
 * 
 * @param timestamp  Unix timestamp
 * 
 * @return Full weekday name (e.g., "Wednesday")
 * 
 * Example:
 *   GetWeekdayName(1752235200) -> "Friday"
 */
stock GetWeekdayName(timestamp)
{
    new weekdayName[16];
    new const weekdayNames[][] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    new dayOfWeek = (timestamp / SECONDS_PER_DAY + 4) % 7;
    format(weekdayName, sizeof(weekdayName), "%s", weekdayNames[dayOfWeek]);
    return weekdayName;
}