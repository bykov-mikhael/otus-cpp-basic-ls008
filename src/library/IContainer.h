#pragma once

#include <string>

template<typename T>
class Container {
public:
  virtual void push_back(const T &value) = 0;
  virtual void insert(int pos, const T &value) = 0;
  virtual void erase(int pos) = 0;
  virtual size_t get_size() const = 0;
  virtual void print() const = 0;
  virtual T operator[](int index) = 0;
};
