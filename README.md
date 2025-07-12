# timeutils.inc

[![sampctl](https://img.shields.io/badge/sampctl-timeutils-2f2f2f.svg?style=for-the-badge)](https://github.com/lantecds/timeutils)

An open.mp/SA-MP time utilities library for converting Unix timestamps to human-readable formats, relative time expressions, and various date/time formatting options.

This include was written by me a while ago for one of my servers! I'm currently working on my Roleplay server and needed something to show account last login times like "2 minutes ago". I remembered I had written something similar before, and after some digging I found this script. After cleaning it up, I decided to open source it.

![Example Output](image.webp)

## Installation

Simply install to your project:

```bash
sampctl package install lantecds/timeutils
```

Include in your code and begin using the library:

```pawn
#include <timeutils>
```

## Usage

### Example Usage

Here's how you can use timeutils to show a player's last login time:

```pawn
// Assume GetPVarInt(playerid, "PlayerLastLogin") stores the last login Unix time
SendClientMessage(playerid, 0xE0E0E0FF, "Welcome back, %s!", PlayerAccountData[playerid][E_PLAYER_ACCOUNT_NAME]);

SendClientMessage(playerid, 0xA0FFA0FF, "You have logged in as %s (%i).", PlayerCharacterData[playerid][E_CHARACTER_NAME], PlayerCharacterData[playerid][E_CHARACTER_SQL_ID]);

SendClientMessage(playerid, 0xC8E6C9FF, "Your previous visit was %s.", UnixToHumanReadable(gettime() - GetPVarInt(playerid, "PlayerLastLogin")));
```

### Constants

* `SERVER_TIME_ZONE`:
  * Defaults to 0, configurable timezone offset for the server.
* `SECONDS_PER_MINUTE`:
  * Constant for seconds in a minute (60).
* `SECONDS_PER_HOUR`:
  * Constant for seconds in an hour (3600).
* `SECONDS_PER_DAY`:
  * Constant for seconds in a day (86400).
* `SECONDS_PER_WEEK`:
  * Constant for seconds in a week (604800).
* `SECONDS_PER_MONTH`:
  * Constant for seconds in a month (2592000).
* `SECONDS_PER_YEAR`:
  * Constant for seconds in a year (31536000).
* `EPOCH_YEAR`:
  * Unix epoch start year (1970).
* `MAX_YEAR`:
  * Maximum supported year (2100).

### Functions

* `UnixToHumanReadable(unixdifference, bool:shortform = false, bool:biggestunitonly = false)`:
  * Converts a time difference into human-readable format.
  * Parameters:
    * `unixdifference`: Time difference in seconds (positive or negative)
    * `shortform`: Use abbreviated units (e.g., "h" instead of "hours")
    * `biggestunitonly`: Show only the largest significant unit
  * Returns: Formatted time string (e.g., "2 days 3 hours" or "5y 2m")
  * Examples:
    * `UnixToHumanReadable(93784)` → "1 day 2 hours 3 minutes"
    * `UnixToHumanReadable(93784, true)` → "1d 2h 3m"
    * `UnixToHumanReadable(93784, false, true)` → "1 day"

* `bool:IsLeapYear(year)`:
  * Determines if a year is a leap year.
  * Parameters:
    * `year`: 4-digit year
  * Returns: true if leap year, false otherwise
  * Example: `IsLeapYear(2024)` → true

* `UnixToDateTime(timestamp)`:
  * Converts Unix timestamp to formatted date/time string.
  * Parameters:
    * `timestamp`: Unix timestamp to convert
  * Returns: String in "HH:MM DD/MM/YYYY" format
  * Example: `UnixToDateTime(1752235200)` → "12:00 11/07/2025"

* `UnixToCustomDate(timestamp, bool:showtime = true, bool:shortform = false)`:
  * Converts a Unix timestamp to a customizable date format.
  * Parameters:
    * `timestamp`: The Unix timestamp to convert
    * `showtime`: Whether to include the time in the output
    * `shortform`: Whether to use short form for month names
  * Returns: A formatted date string based on the provided options
  * Examples:
    * `UnixToCustomDate(1752235200)` → "12:00 11 July 2025"
    * `UnixToCustomDate(1752235200, true, true)` → "12:00 11 Jul 2025"
    * `UnixToCustomDate(1752235200, false, true)` → "11 Jul 2025"

* `RelativeTime(unixdifference)`:
  * Generates relative time expression from time difference.
  * Parameters:
    * `unixdifference`: Time delta in seconds
  * Returns: Relative time string (future: "in X", past: "X ago")
  * Examples:
    * `RelativeTime(-3600)` → "in 1 hour"
    * `RelativeTime(3600)` → "1 hour ago"

* `UnixToISO8601(timestamp)`:
  * Formats timestamp according to ISO 8601 standard.
  * Parameters:
    * `timestamp`: Unix timestamp to format
  * Returns: ISO 8601 formatted string (YYYY-MM-DDTHH:MM:SSZ)
  * Example: `UnixToISO8601(1752235200)` → "2025-07-11T12:00:00Z"

* `bool:IsValidDate(year, month, day)`:
  * Validates Gregorian calendar date components.
  * Parameters:
    * `year`: Year
    * `month`: Month
    * `day`: Day of month
  * Returns: true if valid date, false otherwise
  * Examples:
    * `IsValidDate(2024, 2, 29)` → true
    * `IsValidDate(2023, 2, 29)` → false

* `GetWeekdayName(timestamp)`:
  * Gets weekday name from Unix timestamp.
  * Parameters:
    * `timestamp`: Unix timestamp
  * Returns: Full weekday name (e.g., "Wednesday")
  * Example: `GetWeekdayName(1752235200)` → "Friday"