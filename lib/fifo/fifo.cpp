#include <stdint.h>

#include "fifo.h"
 
template <class T>
FIFO<T>::FIFO(uint32_t bufsize){
    buffer = new T[bufsize];
    size = bufsize;
    getindex = 0;
    putindex = 0;
    count = 0;
    return;
}
 
template <class T>
FIFO<T>::~FIFO(void){
    delete[] buffer;
    return;
}
 
template <class T>
void FIFO<T>::clear(void){
    irs_disable();
  
  count = 0;
  getindex = 0;
  putindex = 0;
 
  irs_enable();
 
    return;
}
 
template <class T>
size_t FIFO<T>::getsize(void){
  return size;
}
 
template <class T>
T FIFO<T>::get(void){
  T getdata;
 
    irs_disable();
 
  if ( count <= 0 ){
    irs_enable();
    return 0;
  }
  
  getdata = buffer[getindex];
  getindex++;
  if ( getindex >= size ){
    getindex = 0;
  }
  count--;
 
    irs_enable();
 
  return getdata;
}
 
template <class T>
T FIFO<T>::peek(void){
  T getdata;
  
  irs_disable();
 
  if ( count == 0 ){
        irs_enable();
    return 0;
  }
  getdata = buffer[getindex];
 
    irs_enable();
  return getdata;
}
 
template <class T>
void FIFO<T>::put(const T putdata){
  irs_disable();
  
  buffer[putindex] = putdata;
  putindex++;
  if ( putindex >= size ){
    putindex = 0;
  }
  count++;
 
  irs_enable();
}
 
template <class T>
uint32_t FIFO<T>::available(void){
  uint32_t c = 0;
  
  irs_disable();
 
  c = count;
 
  irs_enable();
  
  return c;
}
 
template class FIFO<uint8_t>;
template class FIFO<int8_t>;
template class FIFO<uint16_t>;
template class FIFO<int16_t>;
template class FIFO<uint32_t>;
template class FIFO<int32_t>;
template class FIFO<uint64_t>;
template class FIFO<int64_t>;
template class FIFO<char>;
template class FIFO<wchar_t>;
