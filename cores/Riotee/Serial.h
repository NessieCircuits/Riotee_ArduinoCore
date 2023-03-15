#ifndef __SERIAL_H_
#define __SERIAL_H_

#include "Stream.h"

class SerialClass : public Stream {
public:
  void begin(unsigned long);
  virtual int peek();
  virtual int available();
  virtual int read();
  virtual void flush();
  size_t write(const uint8_t *, size_t);
  size_t write(uint8_t);
};

extern SerialClass Serial;

#endif /* __SERIAL_H_ */