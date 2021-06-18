#include <stdio.h>
#include <time.h>
#include <unistd.h>     //sleep()
#include <sys/time.h>   //setitimer()
#include <signal.h>     //signal()

/*
How time works in computer:
all computers has an in-built clock which is set to give value in seconds (even with nanosecond precision) from 
epoch (1st Jan 1970 at 00:00:00 hrs)
this clock will keep on increasing over the time

TODO: do the cpu has two clocks
1. for measuring time
2. clock for synchronizing cpu execution

TODO: how the time measuring clock works
[Real-time clock](https://en.wikipedia.org/wiki/Real-time_clock)  
[How the modern world keeps track of time - An introduction to crystal oscillators](https://www.youtube.com/watch?v=fPKdDCiJDok)
[How a quartz watch works - its heart beats 32,768 times a second](https://www.youtube.com/watch?v=_2By2ane2I4)
quartz oscillator:
piezoelectric effect:
flip flops:

Calendar time:
conversion of these seconds in wall clock time - hrs:min:sec + day, month, year
then we have programs to convert these seconds into GMT or your local time zone
[timezones explained](https://www.youtube.com/watch?v=viyERCiHgj0)

usually this computer clock is very precise but it is possible it will not match with others for some reason
or you want another clock as source of truth say another computer on internet to be used for 
getting the current time and date
so OS provides flexibility to do so as per convenience and can modify calendar time as per requirement

CPU time:
another use of these seconds is to calculate time elapsed between two times usually to determine how much 
time cpu has taken to execute some program or procedure or code
waiting on external events is not counted in cpu tike waiting for IO etc..
so at some time say clock gives 100 second then later it is 120 seconds = time used is 20 seconds
so clocks ticks faster than a second may be 10^9 times in a second 
so clock() call gives clock ticks (cpu cycles) at that time from when cpu started this current process
call clock() again to get the total ticks till now and substract from previos one to get the ticks 
made in part of code execution 
if we know clock ticks per second divide the result by it to get the actual time in seconds

processor time:
it calculates all times even waiting for IO etc for some code execution

*/

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
if we divide a - b with no of cycles made by cpu in 1 second (represenetd using macro CLOCKS_PER_SEC )
we will get actual time to run our code in seconds 

cpu time does not calculate waiting for IO etc.. use processor time if required
*/

//getting absolute time and conversion to calendar time (time date month year etc..)
void calendar_time(){
    //gives no od seconds from epoch
    time_t t = time(NULL); //instead of NULL pointer to time_t can be used which also gets the time value
    printf("%ld",t);
    //this gives more control over time
    struct timespec ts;
    //CLOCK_REALTIME - just like time() call it gives time from epoch
    //CLOCK_MONOTONIC - gives time from any random time in past (not epoch) - so this should be used for
    //elapsed time and not absolute time
    clock_gettime(CLOCK_REALTIME, &ts);     //this is better version of time() gives nano second precision
    //printf the seconds since epoch
    printf("%ld\n",ts.tv_sec);  //tv_sec gives seconds from epoch
    printf("%ld\n",ts.tv_nsec); //tv_nsec gives nano second elapsed after tv_sec seconds 
}

//broken down time
void broken_down_time(){
    //convert to broken down time
    time_t t = time(NULL);
    //TODO: are tm1 and tm2 static allocations
    //TODO: get to know about fields of struct tm
    //broken down time against local time zone
    struct tm* tm1 = localtime(&t);
    //broken down time against greenwich mean time
    struct tm* tm2 = gmtime(&t);
}

//formatting time 
void format_time(){
    time_t t = time(NULL);
    struct tm* tm1 = localtime(&t);
    struct tm* tm2 = gmtime(&t);
    //convert broken down time back to time_t (epoch based time)
    time_t t1 = mktime(tm1);

    //Formatting Calendar Time
    printf("%s%s%s",asctime(tm1),asctime(tm2),ctime(&t));
}

//getting cpu time
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

//alarm
static void create_alarm(){
    //struct used to set the alarm
    struct itimerval new;
    new.it_interval.tv_sec = 0;     //send alarm only once
    new.it_value.tv_sec = 3;        //send alarm after  seconds

    //this is more powerful and alarm() call is a special case of it
    setitimer(ITIMER_REAL, &new, NULL);
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
//FIXME: this is not working try to resolve
void create_and_respond_to_alarm(){
    //listen for SIGALRM
    signal(SIGALRM, alarm_handler);
    //raise alarm to itself
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