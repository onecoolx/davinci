//
// Copyright for strftime() and its dependencies: 
//
// Date to string conversion
//
// Copyright (C) 2002 Michael Ringgaard. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the project nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

// Other functions in this file are taken from public domain without copyright
#include "config.h"

#if PLATFORM(WINCE)
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                             strftime() - taken from OpenBSD                             //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

#define IN_NONE	0
#define IN_SOME	1
#define IN_THIS	2
#define IN_ALL	3
#define CHAR_BIT      8

#define TYPE_BIT(type)	(sizeof (type) * CHAR_BIT)
#define TYPE_SIGNED(type) (((type) -1) < 0)

#define INT_STRLEN_MAXIMUM(type) \
    ((TYPE_BIT(type) - TYPE_SIGNED(type)) * 302 / 1000 + 1 + TYPE_SIGNED(type))

#define isleap(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

#define MONSPERYEAR	12
#define DAYSPERWEEK	7
#define TM_YEAR_BASE	1900
#define HOURSPERDAY	24
#define DAYSPERNYEAR	365
#define DAYSPERLYEAR	366

static char		wildabbr[] = "WILDABBR";

char *			tzname[2] = {
	wildabbr,
	wildabbr
};


#define Locale	(&C_time_locale)

struct lc_time_T {
	const char *	mon[MONSPERYEAR];
	const char *	month[MONSPERYEAR];
	const char *	wday[DAYSPERWEEK];
	const char *	weekday[DAYSPERWEEK];
	const char *	X_fmt;
	const char *	x_fmt;
	const char *	c_fmt;
	const char *	am;
	const char *	pm;
	const char *	date_fmt;
};

static const struct lc_time_T	C_time_locale = {
	{
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	}, {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	}, {
		"Sun", "Mon", "Tue", "Wed",
		"Thu", "Fri", "Sat"
	}, {
		"Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday"
	},

	/* X_fmt */
	"%H:%M:%S",

	/*
	** x_fmt
	** C99 requires this format.
	** Using just numbers (as here) makes Quakers happier;
	** it's also compatible with SVR4.
	*/
	"%m/%d/%y",

	/*
	** c_fmt
	** C99 requires this format.
	** Previously this code used "%D %X", but we now conform to C99.
	** Note that
	**      "%a %b %d %H:%M:%S %Y"
	** is used by Solaris 2.3.
	*/
	"%a %b %e %T %Y",

	/* am */
	"AM",

	/* pm */
	"PM",

	/* date_fmt */
	"%a %b %e %H:%M:%S %Z %Y"
};


static char *
_add(const char * str, char * pt, const char * const ptlim)
{
	while (pt < ptlim && (*pt = *str++) != '\0')
		++pt;
	return pt;
}


static char *
_conv(const int n, const char * const format, char * const pt, const char * const ptlim)
{
	char	buf[INT_STRLEN_MAXIMUM(int) + 1];

	(void) _snprintf(buf, sizeof buf, format, n);
	return _add(buf, pt, ptlim);
}


static char *
_fmt(const char * format, const struct tm * const t, char * pt, const char * const ptlim, int * warnp)
{
	for ( ; *format; ++format) {
		if (*format == '%') {
label:
			switch (*++format) {
			case '\0':
				--format;
				break;
			case 'A':
				pt = _add((t->tm_wday < 0 ||
					t->tm_wday >= DAYSPERWEEK) ?
					"?" : Locale->weekday[t->tm_wday],
					pt, ptlim);
				continue;
			case 'a':
				pt = _add((t->tm_wday < 0 ||
					t->tm_wday >= DAYSPERWEEK) ?
					"?" : Locale->wday[t->tm_wday],
					pt, ptlim);
				continue;
			case 'B':
				pt = _add((t->tm_mon < 0 ||
					t->tm_mon >= MONSPERYEAR) ?
					"?" : Locale->month[t->tm_mon],
					pt, ptlim);
				continue;
			case 'b':
			case 'h':
				pt = _add((t->tm_mon < 0 ||
					t->tm_mon >= MONSPERYEAR) ?
					"?" : Locale->mon[t->tm_mon],
					pt, ptlim);
				continue;
			case 'C':
				/*
				** %C used to do a...
				**	_fmt("%a %b %e %X %Y", t);
				** ...whereas now POSIX 1003.2 calls for
				** something completely different.
				** (ado, 1993-05-24)
				*/
				pt = _conv((t->tm_year + TM_YEAR_BASE) / 100,
					"%02d", pt, ptlim);
				continue;
			case 'c':
				{
				int warn2 = IN_SOME;

				pt = _fmt(Locale->c_fmt, t, pt, ptlim, warnp);
				if (warn2 == IN_ALL)
					warn2 = IN_THIS;
				if (warn2 > *warnp)
					*warnp = warn2;
				}
				continue;
			case 'D':
				pt = _fmt("%m/%d/%y", t, pt, ptlim, warnp);
				continue;
			case 'd':
				pt = _conv(t->tm_mday, "%02d", pt, ptlim);
				continue;
			case 'E':
			case 'O':
				/*
				** C99 locale modifiers.
				** The sequences
				**	%Ec %EC %Ex %EX %Ey %EY
				**	%Od %oe %OH %OI %Om %OM
				**	%OS %Ou %OU %OV %Ow %OW %Oy
				** are supposed to provide alternate
				** representations.
				*/
				goto label;
			case 'e':
				pt = _conv(t->tm_mday, "%2d", pt, ptlim);
				continue;
			case 'F':
				pt = _fmt("%Y-%m-%d", t, pt, ptlim, warnp);
				continue;
			case 'H':
				pt = _conv(t->tm_hour, "%02d", pt, ptlim);
				continue;
			case 'I':
				pt = _conv((t->tm_hour % 12) ?
					(t->tm_hour % 12) : 12,
					"%02d", pt, ptlim);
				continue;
			case 'j':
				pt = _conv(t->tm_yday + 1, "%03d", pt, ptlim);
				continue;
			case 'k':
				/*
				** This used to be...
				**	_conv(t->tm_hour % 12 ?
				**		t->tm_hour % 12 : 12, 2, ' ');
				** ...and has been changed to the below to
				** match SunOS 4.1.1 and Arnold Robbins'
				** strftime version 3.0.  That is, "%k" and
				** "%l" have been swapped.
				** (ado, 1993-05-24)
				*/
				pt = _conv(t->tm_hour, "%2d", pt, ptlim);
				continue;
#ifdef KITCHEN_SINK
			case 'K':
				/*
				** After all this time, still unclaimed!
				*/
				pt = _add("kitchen sink", pt, ptlim);
				continue;
#endif /* defined KITCHEN_SINK */
			case 'l':
				/*
				** This used to be...
				**	_conv(t->tm_hour, 2, ' ');
				** ...and has been changed to the below to
				** match SunOS 4.1.1 and Arnold Robbin's
				** strftime version 3.0.  That is, "%k" and
				** "%l" have been swapped.
				** (ado, 1993-05-24)
				*/
				pt = _conv((t->tm_hour % 12) ?
					(t->tm_hour % 12) : 12,
					"%2d", pt, ptlim);
				continue;
			case 'M':
				pt = _conv(t->tm_min, "%02d", pt, ptlim);
				continue;
			case 'm':
				pt = _conv(t->tm_mon + 1, "%02d", pt, ptlim);
				continue;
			case 'n':
				pt = _add("\n", pt, ptlim);
				continue;
			case 'p':
				pt = _add((t->tm_hour >= (HOURSPERDAY / 2)) ?
					Locale->pm :
					Locale->am,
					pt, ptlim);
				continue;
			case 'R':
				pt = _fmt("%H:%M", t, pt, ptlim, warnp);
				continue;
			case 'r':
				pt = _fmt("%I:%M:%S %p", t, pt, ptlim, warnp);
				continue;
			case 'S':
				pt = _conv(t->tm_sec, "%02d", pt, ptlim);
				continue;
			case 's':
				{
					struct tm	tm;
					char		buf[INT_STRLEN_MAXIMUM(
								time_t) + 1];
					time_t		mkt;

					tm = *t;
					mkt = mktime(&tm);
					if (TYPE_SIGNED(time_t))
						(void) _snprintf(buf, sizeof buf,
						    "%ld", (long) mkt);
					else	(void) _snprintf(buf, sizeof buf,
						    "%lu", (unsigned long) mkt);
					pt = _add(buf, pt, ptlim);
				}
				continue;
			case 'T':
				pt = _fmt("%H:%M:%S", t, pt, ptlim, warnp);
				continue;
			case 't':
				pt = _add("\t", pt, ptlim);
				continue;
			case 'U':
				pt = _conv((t->tm_yday + DAYSPERWEEK -
					t->tm_wday) / DAYSPERWEEK,
					"%02d", pt, ptlim);
				continue;
			case 'u':
				/*
				** From Arnold Robbins' strftime version 3.0:
				** "ISO 8601: Weekday as a decimal number
				** [1 (Monday) - 7]"
				** (ado, 1993-05-24)
				*/
				pt = _conv((t->tm_wday == 0) ?
					DAYSPERWEEK : t->tm_wday,
					"%d", pt, ptlim);
				continue;
			case 'V':	/* ISO 8601 week number */
			case 'G':	/* ISO 8601 year (four digits) */
			case 'g':	/* ISO 8601 year (two digits) */
				{
					int	year;
					int	yday;
					int	wday;
					int	w;

					year = t->tm_year + TM_YEAR_BASE;
					yday = t->tm_yday;
					wday = t->tm_wday;
					for ( ; ; ) {
						int	len;
						int	bot;
						int	top;

						len = isleap(year) ?
							DAYSPERLYEAR :
							DAYSPERNYEAR;
						/*
						** What yday (-3 ... 3) does
						** the ISO year begin on?
						*/
						bot = ((yday + 11 - wday) %
							DAYSPERWEEK) - 3;
						/*
						** What yday does the NEXT
						** ISO year begin on?
						*/
						top = bot -
							(len % DAYSPERWEEK);
						if (top < -3)
							top += DAYSPERWEEK;
						top += len;
						if (yday >= top) {
							++year;
							w = 1;
							break;
						}
						if (yday >= bot) {
							w = 1 + ((yday - bot) /
								DAYSPERWEEK);
							break;
						}
						--year;
						yday += isleap(year) ?
							DAYSPERLYEAR :
							DAYSPERNYEAR;
					}
					if (*format == 'V')
						pt = _conv(w, "%02d",
							pt, ptlim);
					else if (*format == 'g') {
						*warnp = IN_ALL;
						pt = _conv(year % 100, "%02d",
							pt, ptlim);
					} else	pt = _conv(year, "%04d",
							pt, ptlim);
				}
				continue;
			case 'v':
				pt = _fmt("%e-%b-%Y", t, pt, ptlim, warnp);
				continue;
			case 'W':
				pt = _conv((t->tm_yday + DAYSPERWEEK -
					(t->tm_wday ?
					(t->tm_wday - 1) :
					(DAYSPERWEEK - 1))) / DAYSPERWEEK,
					"%02d", pt, ptlim);
				continue;
			case 'w':
				pt = _conv(t->tm_wday, "%d", pt, ptlim);
				continue;
			case 'X':
				pt = _fmt(Locale->X_fmt, t, pt, ptlim, warnp);
				continue;
			case 'x':
				{
				int	warn2 = IN_SOME;

				pt = _fmt(Locale->x_fmt, t, pt, ptlim, &warn2);
				if (warn2 == IN_ALL)
					warn2 = IN_THIS;
				if (warn2 > *warnp)
					*warnp = warn2;
				}
				continue;
			case 'y':
				*warnp = IN_ALL;
				pt = _conv((t->tm_year + TM_YEAR_BASE) % 100,
					"%02d", pt, ptlim);
				continue;
			case 'Y':
				pt = _conv(t->tm_year + TM_YEAR_BASE, "%04d",
					pt, ptlim);
				continue;
			case 'Z':
				if (t->tm_isdst >= 0)
					pt = _add(tzname[t->tm_isdst != 0],
						pt, ptlim);
				/*
				** C99 says that %Z must be replaced by the
				** empty string if the time zone is not
				** determinable.
				*/
				continue;
			case 'z':
				{
				int		diff;
				char const *	sign;

				if (t->tm_isdst < 0)
					continue;
				continue;
				if (diff < 0) {
					sign = "-";
					diff = -diff;
				} else	sign = "+";
				pt = _add(sign, pt, ptlim);
				diff /= 60;
				pt = _conv((diff/60)*100 + diff%60,
					"%04d", pt, ptlim);
				}
				continue;
			case '+':
				pt = _fmt(Locale->date_fmt, t, pt, ptlim,
					warnp);
				continue;
			case '%':
			default:
				break;
			}
		}
		if (pt == ptlim)
			break;
		*pt++ = *format;
	}
	return pt;
}


size_t
strftime(char * const s, const size_t maxsize, const char * const format, const struct tm * const t)
{
	char *	p;
	int	warn;

	warn = IN_NONE;
	p = _fmt(((format == NULL) ? "%c" : format), t, s, s + maxsize, &warn);

	if (p == s + maxsize) {
		if (maxsize > 0)
			s[maxsize - 1] = '\0';
		return 0;
	}
	*p = '\0';
	return p - s;
}

// Code below is from public domain without copyright

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                                         time()                                          //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

#define SECS_BETWEEN_EPOCHS     11644473600L  // seconds between Jan 1, 1601 and Jan 1, 1970
#define MSEC_TO_HUNDRED_NSEC    10000000

time_t
fileTimeToUnixTime(const FILETIME* ft)
{
    ULARGE_INTEGER i;
    double converted;

    // copy to a ULARGE_INTEGER so that it can be manipulated as a single 64-bit number
    i.LowPart = ft->dwLowDateTime;
    i.HighPart = ft->dwHighDateTime;

    // convert from hundreds of nanoseconds to milliseconds
    converted = i.QuadPart / MSEC_TO_HUNDRED_NSEC;

    // convert from Windows epoch to Unix epoch
    converted -= SECS_BETWEEN_EPOCHS;
    return converted;
}

void
unixTimeToFileTime(time_t t, FILETIME* ft)
{
    ULARGE_INTEGER i;

    // convert from Unix epoch to Windows epoch
    i.QuadPart = t + SECS_BETWEEN_EPOCHS;

    // convert from milliseconds to hundreds of nanoseconds
    i.QuadPart *= MSEC_TO_HUNDRED_NSEC;

    ft->dwLowDateTime = i.LowPart;
    ft->dwHighDateTime = i.HighPart;
}

time_t
time(time_t* timer)
{
    time_t result;
	FILETIME ft;
    GetCurrentFT(&ft);
    result = fileTimeToUnixTime(&ft);
    if (timer)
        *timer = result;
    return result;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                                        mktime()                                         //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

int month_to_day[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

BOOL fillInDate(const SYSTEMTIME *in, SYSTEMTIME *out)
{
    FILETIME ft;
    int diff;

    memcpy(out, in, sizeof(SYSTEMTIME));

    // find first day of target month
    out->wDayOfWeek = 0;
    out->wDay = 1;

    // find what day of the week that is by converting to FILETIME and back
    if (!SystemTimeToFileTime(out, &ft))
        return FALSE;
    if (!FileTimeToSystemTime(&ft, out))
        return FALSE;

    // advance day until we get the correct day of the week
    diff = in->wDayOfWeek - out->wDayOfWeek;
    if (diff < 0) diff += 7;

    out->wDayOfWeek = in->wDayOfWeek;
    out->wDay += diff;

    // wDay in input struct is actually the week-in-month value.  Advance by this many weeks.
    out->wDay += 7 * (in->wDay - 1);

    return TRUE;
}

BOOL findDSTCutoverTime(time_t *result, SYSTEMTIME *st, WORD year)
{
    FILETIME ft;
    if (st->wYear == 0) {
        // day-of-month format
        SYSTEMTIME fullDate;
        st->wYear = year;
        if (!fillInDate(st, &fullDate))
            return FALSE;
        SystemTimeToFileTime(&fullDate, &ft);
    } else {
        SystemTimeToFileTime(st, &ft);
    }
    *result = fileTimeToUnixTime(&ft);
    return TRUE;
}

time_t convertToOrFromUTC(time_t timestamp, BOOL toUTC, BOOL* isDST)
{
    time_t result = timestamp;
    TIME_ZONE_INFORMATION tzone;
    DWORD err;

    if (isDST)
        *isDST = FALSE;

    err = GetTimeZoneInformation(&tzone);
    if (err == TIME_ZONE_ID_INVALID)
        return result;

    if (toUTC)
        result += tzone.Bias * 60;
    else
        result -= tzone.Bias * 60;

    if (tzone.StandardDate.wMonth != 0 && tzone.DaylightDate.wMonth != 0)
    {
        time_t standardStartTime, daylightStartTime;
        FILETIME ft;
        SYSTEMTIME st;
        BOOL targetDateInDST;

        // may need to know the year
        unixTimeToFileTime(timestamp, &ft);
        FileTimeToSystemTime(&ft, &st);

        if (!findDSTCutoverTime(&standardStartTime, &tzone.StandardDate, st.wYear))
            return result;
        if (!findDSTCutoverTime(&daylightStartTime, &tzone.DaylightDate, st.wYear))
            return result;

        if (standardStartTime > daylightStartTime)
            targetDateInDST = (daylightStartTime <= result && result < standardStartTime);
        else
            targetDateInDST = !(standardStartTime <= result && result < daylightStartTime);

        if (targetDateInDST) {
            if (toUTC)
                result += tzone.DaylightBias * 60;
            else
                result -= tzone.DaylightBias * 60;
        } else {
            if (toUTC)
                result += tzone.StandardBias * 60;
            else
                result -= tzone.StandardBias * 60;
        }

        if (isDST)
            *isDST = targetDateInDST;
    }

    return result;
}

time_t mktime(struct tm *t)
{
        short  month, year;
        time_t result;

        month = t->tm_mon;
        year = t->tm_year + month / 12 + 1900;
        month %= 12;
        if (month < 0)
        {
                year -= 1;
                month += 12;
        }
        result = (year - 1970) * 365 + month_to_day[month];
        if (month <= 1)
                year -= 1;
        result += (year - 1968) / 4;
        result -= (year - 1900) / 100;
        result += (year - 1600) / 400;
        result += t->tm_mday;
        result -= 1;
        result *= 24;
        result += t->tm_hour;
        result *= 60;
        result += t->tm_min;
        result *= 60;
        result += t->tm_sec;

        result = convertToOrFromUTC(result, TRUE, NULL);

        return(result);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                                      gmtime()                                           //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////



static struct tm mytm;

int DMonth[13] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
int monthCodes[12] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };


int
calcDayOfWeek(const struct tm* nTM)
{
	int day;
	
	day = (nTM->tm_year%100);
	day += day/4;
	day += monthCodes[nTM->tm_mon];
	day += nTM->tm_mday;
	while(day>=7)
		day -= 7;

	return day;
}


struct tm *
gmtime(const time_t *timer)
{
	unsigned long x = (unsigned long) *timer;
	int imin, ihrs, iday, iyrs;
	int sec, min, hrs, day, mon, yrs;
	int lday, qday, jday, mday;


	imin = x / 60;							// whole minutes since 1/1/70
	sec = x - (60 * imin);					// leftover seconds
	ihrs = imin / 60;						// whole hours since 1/1/70
	min = imin - 60 * ihrs;					// leftover minutes
	iday = ihrs / 24;						// whole days since 1/1/70
	hrs = ihrs - 24 * iday;					// leftover hours
	iday = iday + 365 + 366; 				// whole days since 1/1/68
	lday = iday / (( 4* 365) + 1);			// quadyr = 4 yr period = 1461 days
	qday = iday % (( 4 * 365) + 1);			// days since current quadyr began
	if(qday >= (31 + 29))					// if past feb 29 then
		lday = lday + 1;					// add this quadyr’s leap day to the
											// # of quadyrs (leap days) since 68
	iyrs = (iday - lday) / 365;				// whole years since 1968
	jday = iday - (iyrs * 365) - lday;		// days since 1 /1 of current year.
	if(qday <= 365 && qday >= 60)			// if past 2/29 and a leap year then
		jday = jday + 1;					// add a leap day to the # of whole
											// days since 1/1 of current year
	yrs = iyrs + 1968;						// compute year
	mon = 13;								// estimate month ( +1)
	mday = 366;								// max days since 1/1 is 365
	while(jday < mday)						// mday = # of days passed from 1/1
	{										// until first day of current month
		mon = mon - 1;						// mon = month (estimated)
		mday = DMonth[mon];					// # elapsed days at first of ”mon?		if((mon > 2) && (yrs % 4) == 0)		// if past 2/29 and leap year then
			mday = mday + 1;				// add leap day
											// compute month by decrementing
	}										// month until found
		
	day = jday - mday + 1;					// compute day of month

	mytm.tm_sec = sec;
	mytm.tm_min = min;
	mytm.tm_hour = hrs;
	mytm.tm_mday = day;
	mytm.tm_mon = mon;
	mytm.tm_year = yrs - 1900;

	mytm.tm_wday = calcDayOfWeek(&mytm);
	mytm.tm_yday = jday;
	mytm.tm_isdst = 0;

	return &mytm;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//                            localtime()                                                  //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////


struct tm *
localtime(const time_t *timer)
{
    time_t local;
    struct tm * result;
    BOOL isDST;

    local = convertToOrFromUTC(*timer, FALSE, &isDST);
    result = gmtime(&local);
    result->tm_isdst = isDST;
    return result;
}
#endif