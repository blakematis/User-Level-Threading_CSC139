#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

bool gotit = false;	// Hints: 
			//  Note bool is not a standard in C
			//  You should use int instead. 
			//  Also take care to define true and false.


void timer_handler(int sig)
{
  int ret_val;
  gotit = true;
  printf("Timer expired\n");
}


int main()
{
   signal(SIGVTALRM, timer_handler);
   
   struct itimerval tv;
   tv.it_value.tv_sec = 2; //time of first timer
   tv.it_value.tv_usec = 0; //time of first timer
   tv.it_interval.tv_sec = 2; //time of all timers but the first one
   tv.it_interval.tv_usec = 0; //time of all timers but the first one

   setitimer(ITIMER_VIRTUAL, &tv, NULL);
   for(; ;) {
       if (gotit) {
           printf("Got it!\n");
           gotit = false;
       }
   }
   return 0;
}
