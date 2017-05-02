////////////////////////////////////////////////////////////////////////

void f( void ) {
    printf("My ID is: %d\n", GetMyID()); 
    int i=0;

    while(1) {
        ++i;
        if (i % 99999555 == 0) {
	  printf("f: switching\n");
        }
	int j;
	while(j<99995555) j++;
    }
}

void g( void )
{
    printf("My ID is: %d\n", GetMyID()); 
    int i=0;

    CleanUp(); //for test
    while(1){
        ++i;
        if (i % 99999555 == 0) {
	   printf("g: switching\n");
        }
	int j;
        while(j<99995555) j++;
    }
}

void h( void )
{
    printf("My ID is: %d\n", GetMyID()); 
    int i=0;

    while(1){
        ++i;
        if (i % 99999555 == 0) {
           printf("h: switching\n");
        }
	int j;
        while(j<99995555) j++;
    }
}

void* t(void* arg) {
  int i = 0;
  printf("In the thread with arguments and will return!\n");
  fflush(stdout); 

  while(1){ 
        ++i;
	if (i % 99999555 == 0) {
	  printf("in t()\n");
        }
	int j;
        while(j<99995555) j++;
    }
} 

int main()
{
  InitiateThreads();

  // for test
  int i = 0;
  for(i=0;i<20;i++) {
    CreateThread(f);
    CreateThread(h);
    CreateThreadWithArgs(t, (void *)ready_qhead);
  }
  CreateThread(g);

  CreateStatistics();

  signal(SIGVTALRM, Dispatch);

  // Time to the next timer expiration.
  tv.it_value.tv_sec = TIME_QUANTUM/SECOND; //time of first timer
  tv.it_value.tv_usec = 0; //time of first timer

  // Value to put into "it_value" when the timer expires.
  tv.it_interval.tv_sec = TIME_QUANTUM/SECOND; //time of all timers but the first one
  tv.it_interval.tv_usec = 0; //time of all timers but the first one
  
  setitimer(ITIMER_VIRTUAL, &tv, NULL);	
	
  Go();
  
  return 0;
}