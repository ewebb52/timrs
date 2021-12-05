#include <poll.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timerfd.h>
#include <unistd.h>

#ifndef TIME_H
#define TIME_H
typedef void (*time_h)(size_t t_id, void* data);

int timer_init();
void start_timer(int interval);
void stop_timer(size_t t_id);
void timer_destroy();

#endif

#define MAX_TIMERS 500

struct timer_node {
    int fd;
    struct timer_node* n;
    time_h callback;
    void* data;
    unsigned int interval;
};

static void* timer_thread();
static pthread_t thread_id;
static struct timer_node* head = NULL;

int timer_init(int x)
{
    if (pthread_create(&thread_id, NULL, timer_thread, NULL)) {
        return 0;
    }
    return 1;
}

void start_timer(int interval)
{
    struct timer_node* node = NULL;
    struct itimerspec value;
    uint64_t buf;
    node = (struct timer_node*)malloc(sizeof(struct timer_node));

    if (node == NULL) {
//         return 0;
    }
    // node->callback = handler;
    // node->data = data;
    node->interval = interval;

    node->fd = timerfd_create(CLOCK_REALTIME, 0);

    if (node->fd == -1) {
        free(node);
//         return 0;
    }

    value.it_value.tv_sec = interval / 1000;
    value.it_value.tv_nsec = (interval % 1000) * 1000000;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;
    timerfd_settime(node->fd, 0, &value, NULL);
    node->n = head;
    head = node;
    sleep((interval / 1000) + 1);
    // return (size_t)node;
}

void stop_timer(size_t timer_id)
{
    struct timer_node *t, *n;
    t = NULL;
    n = (struct timer_node*)timer_id;

    if (n != NULL) {
        close(n->fd);

        if (n == head) {
            head = head->n;
        } else {
            t = head;
            while (t && t->n != n) {
                t = t->n;
            }
            if (t) {
                t->n = t->n->n;
            }
        }
    }
    if (n) {
        free(n);
    }
}

void timer_destroy()
{
    while (head) {
        stop_timer((size_t)head);
    }
    pthread_cancel(thread_id);
    pthread_join(thread_id, NULL);
}

struct timer_node* get_timer(int fd)
{
    struct timer_node* t = head;

    while (t) {
        if (t->fd == fd) {
            return t;
        }
        t = t->n;
    }
    return NULL;
}

void* timer_thread()
{
    struct pollfd pfd[MAX_TIMERS] = { { 0 } };
    int count = 0;
    struct timer_node* t = NULL;
    int r_fds = 0;
    uint64_t e;

    while (1) {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

        count = 0;
        t = head;

        memset(pfd, 0, sizeof(struct pollfd) * MAX_TIMERS);
        while (t) {
            pfd[count].fd = t->fd;
            pfd[count].events = POLLIN;
            count++;
            t = t->n;
        }

        r_fds = poll(pfd, count, 100);
        if (r_fds <= 0) {
            continue;
        }

        for (int i = 0; i < count; i++) {
            if (pfd[i].revents & POLLIN) {
                int s = read(pfd[i].fd, &e, sizeof(uint64_t));
                if (s == sizeof(uint64_t)) {
                    t = get_timer(pfd[i].fd);
                    if (t && t->callback) {
                        t->callback((size_t)t, t->data);
                    }
                    printf("Timer ran for %d", t->interval);
                }
            }
        }
    }
    return NULL;
}

#ifdef BUILD_TEST

int main()
{

    timer_init(1);
    start_timer(200);
    timer_destroy(1);
    return 0;
}

#endif
