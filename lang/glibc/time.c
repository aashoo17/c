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

CPU has two clocks
1. for measuring calendar time (date, time, year calculation etc)
2. clock for synchronizing cpu execution - at each clock tick cpu is able to complete 1 cycle i.e. any 1 instruction
TODO: give the link from the book why do I know it for 2nd type of clocks

how the time measuring clock works:
[Real-time clock](https://en.wikipedia.org/wiki/Real-time_clock)  
[How the modern world keeps track of time - An introduction to crystal oscillators](https://www.youtube.com/watch?v=fPKdDCiJDok)
[How a quartz watch works - its heart beats 32,768 times a second](https://www.youtube.com/watch?v=_2By2ane2I4)

piezoelectric effect:
some crystals when deformed by applying mechanical force produce voltage - called piezoelectric effect
and reverse is also true when voltage is given crystal deforms and when voltage is removed cyystal come back to
original state this makes a vibration at crysatl natural frequency - this property is used for making a clock

quartz oscillator:
quartz crystal when electromagnetic field is applied will vibrate on it natural frequency 
frequency can be controlled by changing mass using some other material like gold coating to make it vibrate at some fixed 
frequency which we want
we need the frequency to be atleast above 20 kHz frequency so that it can not be heard by humans
we select first power of 2 which goes above 20k which is 2^15 = 32768
TODO: why we select frequency which is in power of 2

flip flops:
TODO: give better definition
15 step flip flops - 15 flip flops are connected together
1st flip flop will change its state - every 1 vibration of crystal
2nd one - every 2 vibration
3rd one - every 2^3 vibration
4th one - every 2^4 vibration
...
15th one - every 2^15 = 32768 vibration 
so 15th flip flop changes state (from 0 to 1) every 32768 vibration i.e. every 1 second, so it is counting 1 second

Calendar time:
conversion of these seconds in wall clock time - hrs:min:sec + day, month, year
then we have programs to convert these seconds into GMT or your local time zone

[timezones explained](https://www.youtube.com/watch?v=viyERCiHgj0)
so earth rotates 360 degree in 24 hours - every hour 15 degree
earth can be divided by vertical circular lines in many parts - can be selected random nos of lines
if at one location time is made fixed (which was done at GMT) other lines will have increased or decreased 
time based on direction of earth rotation so we can add or remove time since we know how much time earth rotation 
takes around sun
if earth rotates east to west - west will have time in +ve from GMT and east will have in -ve 
how much we can know by how many degree that location id from GMT - we know that 15 degree is 1 hour difference

usually this computer clock is very precise but it is possible it will not match with others for some reason
or you want another clock as source of truth say another computer on internet to be used for 
getting the current time and date
so OS provides flexibility to do so as per convenience and can modify calendar time as per requirement

elapsed time:
another use of these seconds is to calculate time elapsed between two times
so at some time say clock gives 100 second then later it is 120 seconds = time used is 20 seconds
usually we keep track of time since epoch (from 1970) which is a big no usually in seconds 
and we take another time and get the difference we get elapsed time
but we can make it simple for elapsed time by taking epoch any time after computer boot
which once taken as smaller epoch will keep on increasing only
get the current time from this epoch substract it we will get the same result
I think this is called monotonic clock - so physical clock does not do it so it must be software 
implemented
TODO: why will go monotonic elapsed time - to reduce the substraction overflow from big nos maybe

CPU time:
time cpu has taken to execute some program or procedure or code
waiting on external events is not counted in cpu tike waiting for IO etc..
calendar time or elapsed time will be useless as cpu might have been waiting for IO etc...
in GNU systems we track no of clock ticks since the start of any process - this means for this 2nd clock is used
which synchronizes the cpu execution cycles

so clock() call gives clock ticks (cpu cycles) at that time from when cpu started this current process
call clock() again to get the total ticks till now and substract from previous one to get the ticks 
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

    //takes any time in past as starting point (eooch for the clock) but will be same during same session without boot
    //so this can be used to get difference between two times but not absolute time as starting point is unknown
    clock_gettime(CLOCK_MONOTONIC,&ts);     
    printf("%ld, %ld\n",ts.tv_sec,ts.tv_nsec);

}

//broken down time
void broken_down_time(){
    //convert to broken down time
    time_t t = time(NULL);
    //TODO: are tm1 and tm2 static allocations
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
    new.it_interval.tv_sec = 0;     //send alarm only once
    new.it_interval.tv_usec = 0; 
    new.it_value.tv_sec = 3;        //send alarm after  seconds
    new.it_value.tv_usec = 0;       //microsecond value

    //this is more powerful and alarm() call is a special case of it
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