#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "timer.h"

void callback(size_t timer_id, void* data)
{
    printf("Single shot timer expired\n");
    printf("%s\n", data);
}


void main() 
{
    size_t t1;
    timer_init(1);
    start_timer(2000);
    timer_destroy(1);
}
