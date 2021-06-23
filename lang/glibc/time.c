#include <stdio.h>
#include <time.h>
#include <unistd.h>     //sleep()
#include <sys/time.h>   //setitimer()
#include <signal.h>     //signal()

/*
clock_t => used for cpu/processor time - some integer/float value typedef
time_t => used for calendar time - some integer/float value typedef
calendar time is measured as time elapsed from epoch which is 00:00:00 on January 1,1970 Coordinated Universal Time (UTC)

struct timespec = represents simple calendar time with nano second resolution

getting current calendar time
time() call gets time elapsed from epoch returns time_t
clock_gettime() gives the time from epoch in struct timespec with nano second precision  

Broken down time: it is human representable time in day, month, year etc
struct tm = used for broken down time
localtime() - used to get time in local timezone
gmtime() - used to get time w.r.t. GMT

getting cpu execution time
clock() gives the calling process' current cpu time (i.e. cpu cycles made from start of this process)

if we put some code between two clock() calls like this

clock_t a = clock()
my c code goes here
clock_t b = clock()

a - b = difference gives total cpu cycle run in my code execution
if we divide a - b with no of cycles made by cpu in 1 second (represented using macro CLOCKS_PER_SEC )
we will get actual time to run our code in seconds 

cpu time does not calculate waiting for IO etc.. use processor time if required
*/

//getting absolute time and conversion to calendar time (time date month year etc..)
void calendar_time(){
    //gives no of seconds from epoch
    time_t t = time(NULL); //instead of NULL pointer to time_t can be used which also gets the time value
    printf("%ld\n",t);
    //this gives more control over time
    struct timespec ts;
    //CLOCK_REALTIME - just like time() call it gives time from epoch
    //CLOCK_MONOTONIC - gives time from any random time in past (not epoch) - so this should be used for
    //elapsed time and not absolute time
    clock_gettime(CLOCK_REALTIME, &ts);     //this is better version of time() gives nano second precision
    //printf the seconds since epoch
    printf("%ld\n",ts.tv_sec);  //tv_sec gives seconds from epoch
    printf("%ld\n",ts.tv_nsec); //tv_nsec gives nano second elapsed after tv_sec seconds 

    //takes any time in past as starting point (epoch for the clock) but will be same during same session without boot
    //so this can be used to get difference between two times but not absolute time as starting point is unknown
    clock_gettime(CLOCK_MONOTONIC,&ts);     
    printf("%ld, %ld\n",ts.tv_sec,ts.tv_nsec);

}

//broken down time
void broken_down_time(){
    //convert to broken down time
    time_t t = time(NULL);
    //TODO: tm1 and tm2 static allocations - do they point to same memory
    //fields of struct tm - tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year .. etc
    //broken down time against local time zone
    struct tm* tm1 = localtime(&t);
    //broken down time against greenwich mean time
    struct tm* tm2 = gmtime(&t);

    //FIXME: it is not coming same as native time. why ??
    printf("%d:%d:%d\n",tm1->tm_hour,tm1->tm_min,tm1->tm_sec);
}

//formatting time 
void format_time(){
    time_t t = time(NULL);
    struct tm* tm1 = localtime(&t);
    struct tm* tm2 = gmtime(&t);
    //convert broken down time back to time_t (epoch based time)
    time_t t1 = mktime(tm1);

    //Formatting Calendar Time
    printf("%s%s%s\n",asctime(tm1),asctime(tm2),ctime(&t));
    //TODO: see all the other available formatting options for time
}

//getting cpu time
//TODO: this must be accessing the 2nd clock inside cpu - for execution synchronisation
void cpu_time(){
    //get cpu time used for printf() call here
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    printf("%s\n","Hello World");   //my code for which cpu time is being evaluated
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%.10f\n",cpu_time_used);
}

/*
alarm:
types of alarm
1. SIGALRM - real timer counts elapsed time
2. SIGVTALRM - virtual timer counts processor time
3. SIGPROF - profiling timer counts processor time and processor time spent in system calls

setitimer() - all 3 types of alarm can be generated for same process
alarm() - special case of setitimer which implicitly generates SIGALRM
*/

static void create_alarm(){
    //struct used to set the alarm
    struct itimerval old,new;
    new.it_interval.tv_sec = 0;     //0 means send alarm only once other no will give no of time alarm to be sent
    new.it_interval.tv_usec = 0; 
    new.it_value.tv_sec = 3;        //send alarm after seconds
    new.it_value.tv_usec = 0;       //microsecond precision value

    //this is more powerful and alarm() call is a special case of it
    //old will give any previous alarm created
    setitimer(ITIMER_REAL, &new, &old);
}

static void create_alarm2(){
    //special case of setitimer()
    alarm(3);
}

//handle alarm receipt
static void alarm_handler(int signum){
    puts("got an alarm wow");
}

//creating alarm and handling it
void create_and_respond_to_alarm(){
    //listen for SIGALRM signal
    signal(SIGALRM, alarm_handler);
    //raise alarm signal to itself
    create_alarm();
    //pause the process to it does not exit and receives SIGALRM after 3 seconds
    pause();
}

//sleep
void sleep_process_for_some_time(){
    //sleep for 3 seconds
    sleep(3);
}

int main(){
    create_and_respond_to_alarm();
}