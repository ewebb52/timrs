#ifndef TIME_H
#define TIME_H
#include <stdlib.h>

typedef void (*time_h)(size_t t_id, void* data);

int timer_init(int x);
void start_timer(int interval);
void stop_timer(size_t t_id);
void timer_destroy(int x);

#endif