#ifndef MEW_STACK_LIB_SO2U
#define MEW_STACK_LIB_SO2U
#include "mewlib.h"

namespace mew {
  
int mod(int a, int b) {
  if(b < 0) 
    return -mod(-a, -b);
  int ret = a % b;
  if(ret < 0)
    ret+=b;
  return ret;
}


template<typename T>
class stack {
private:
  size_t _M_size, _M_capacity;
  T* data = nullptr;
public:
  ////////////////////////////////////////////////////////////
  stack(): _M_capacity(sizeof(T)), _M_size(0) {
    data = realloc(nullptr, _M_capacity);
  }

  ////////////////////////////////////////////////////////////
  ~stack() {
    delete[] data;
  }

  ////////////////////////////////////////////////////////////
  void resize(size_t new_size) {
    data = (T*)realloc(data, new_size);
    if (_M_size > new_size) {
      _M_size = new_size;
    } 
    _M_capacity = new_size;
  }

  ////////////////////////////////////////////////////////////
  void upsize_if_needs() {
    if (_M_size*sizeof(T) > _M_capacity) {
      resize(_M_size*sizeof(T));
    }
  }

  ////////////////////////////////////////////////////////////
  bool has(int idx) const noexcept {
    size_t real_idx = get_real_idx(idx);
    return real_idx < _M_size;
  }

  ////////////////////////////////////////////////////////////
  T& at(size_t idx) {
    MewAssert(has(idx));
    return data[idx];
  }

  ////////////////////////////////////////////////////////////
  size_t get_real_idx(int idx) const {
    size_t real_idx;
    real_idx = mod(idx, _M_size);
    real_idx = (_M_size + real_idx) % _M_size;
    return real_idx;
  }

  ////////////////////////////////////////////////////////////
  T& at(int idx) {
    return at(get_real_idx(idx));
  }

  ////////////////////////////////////////////////////////////
  T& operator[](int idx) {
    return at(idx);
  }

  ////////////////////////////////////////////////////////////
  size_t data_size() const noexcept{
    return (sizeof(T)*_M_size);
  }

  ////////////////////////////////////////////////////////////
  size_t size() const noexcept{
    return _M_size;
  }

  ////////////////////////////////////////////////////////////
  void push(T&& value) {
    upsize_if_needs();
    T* pointer = data+_M_size;
    memcpy(pointer, &value, sizeof(value));
    _M_size++;
  }

  ////////////////////////////////////////////////////////////
  void push(const T& value) {
    upsize_if_needs();
    memcpy(data+_M_size, &value, sizeof(value));
    _M_size++;
  }

  ////////////////////////////////////////////////////////////
  T top() {
    return at(-1);
  }

  ////////////////////////////////////////////////////////////
  T pop() {
    T t = top();
    _M_size -= 1;
    return t;
  }

  ////////////////////////////////////////////////////////////
  void erase(size_t start, size_t size = 1) {
    MewAssert(size <= _M_size);
    T* begin = (T*)(data+start);
    T* end = (T*)(data+start+size);
    memmove(begin, end, size*sizeof(T));
    _M_size -= size;
    ____MEWMEW____
  }
  
  ////////////////////////////////////////////////////////////
  void erase(int idx) {
    erase(get_real_idx(idx));
  }

  ////////////////////////////////////////////////////////////
  bool empty() const noexcept {
    return _M_size == 0;
  }

  ////////////////////////////////////////////////////////////
  void clear() {
    _M_size = 0;
    memset(data, 0, _M_capacity);
  }
};

}

#endif