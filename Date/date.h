#pragma once

//#ifndef DATE_H
//#define DATE_H
//...
//
//#endif
#include "status.h"

typedef void* DATE;
//init
DATE date_init_default(void);
//set date
//change date
Status date_set_month(DATE hDate, int month);
void out_date(DATE date);
void date_destroy(DATE* phDate);
