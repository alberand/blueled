#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdlib.h>
#include <stdint.h>

#ifdef Arduino_h
#   define irs_disable() do{ noInterrupts();}while(0)
#   define irs_enable() do{ interrupts();}while(0)
#else
#   define irs_disable() do{ ;}while(0)
#   define irs_enable() do{ ;}while(0)
#endif

// based on work of T. Kawamura

template <typename T>
class FIFO {
private:
    T *buffer;
    size_t size;
    volatile uint32_t getindex;
    volatile uint32_t putindex;
    volatile uint32_t count;

public:
    FIFO(uint32_t bufsize);

    virtual ~FIFO(void);
    virtual void clear(void);
    virtual size_t getsize(void);
    virtual T get(void);
    virtual T peek(void);
    virtual void put(const T putdata);
    virtual uint32_t available(void);

    FIFO &operator= (T data) {
        put(data);
        return *this;
    }

    operator int(void) {
        return get();
    }

};

#endif // __FIFO_H__
