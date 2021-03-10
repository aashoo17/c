#include <stdio.h>
#include <time.h>

/*
clock_t => used for cpu/processor time
time_t => used for calendar time
calendar time is measured from epoch which is 00:00:00 on January 1, 1970, Coordinated Universal Time.

struct timespec = represents simple calendar time with nano second resolution
struct timeval = older struct from timespec which same thing as timespec but with microsecond resolution
DO: how to get current calendar time
time()
clock_gettime
DO: difference between two calendar times using difftime()
Broken down time: it is human representable time in day, month, year etc
struct tm = used for broken down time
localtime()

TODO: get cpu time
*/

int main(){
    //DO: how to get current calendar time
    time_t t1 = time(NULL);
    printf("%ld\n",t1);

    //this gives more control over time
    struct timespec tp;
    //TODO: CLOCK_REALTIME vs CLOCK_MONOTONIC in clock_gettime()
    clock_gettime(CLOCK_REALTIME, &tp);
    //printf the seconds since epoch
    printf("%ld\n",tp.tv_sec);
    printf("%ld\n",tp.tv_nsec);

    //convert to broken down time
    time_t t2 = time(NULL);
    //broken down time against local time zone
    struct tm* tm1 = localtime(&t2);
    //broken down time against greenwich mean time
    struct tm* tm2 = gmtime(&t2);

    //convert broken down time back to time_t (epoch based stime)
    time_t t3 = mktime(tm1);

    //Formatting Calendar Time
    printf("%s%s%s",asctime(tm1),asctime(tm2),ctime(&t2));

    //get cpu time
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /* Do the work. */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
}