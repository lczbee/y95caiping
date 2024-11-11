#ifndef __ALARM_API_H_
#define __ALARM_API_H_

#include "events_adapter.h"

typedef enum {
    ALARM_ON = 0,
    ALARM_RING,
    ALARM_OFF,
} ALARM_STATUS;

void alarm_start(int countdown_sec);
void alarm_cancel();
void alarm_ring_on();
void alarm_ring_off();
void alarm_refresh();
u8 alarm_status_get();

#endif/* __ALARM_API_H_ */