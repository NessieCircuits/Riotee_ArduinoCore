#ifndef __SHTC3_H_
#define __SHTC3_H_

#include <cstddef>

typedef enum { ERR_OK = 0, ERR_I2C = 1, ERR_CRC = 2, ERR_ID = 3 } shtc3_error_t;

typedef struct {
  float temp;
  float humidity;
} shtc3_res_t;

class SHTC3Class {
public:
  int begin();
  int read(shtc3_res_t *res);
};

extern SHTC3Class SHTC3;

#endif /* __SHTC3_H_ */