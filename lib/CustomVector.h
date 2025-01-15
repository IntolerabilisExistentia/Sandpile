#pragma once
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class vector {
public:
  vector() {
    array_ = new T[100];
    capacity_ = 100;
    sizet_ = 0;
  }

  vector(uint64_t length) {
    array_ = new T[length];
    capacity_ = length;
    sizet_ = length;
    for (uint64_t i = 0; i < length; ++i) {
      array_[i] = 0;
    }
  }

  vector(const vector<T>& other) {
    array_ = new T[other.capacity_];
    sizet_ = other.sizet_;
    capacity_ = other.capacity_;
    for (uint64_t i = 0; i < other.sizet_; ++i) {
      array_[i] = other.array_[i];
    }
  }

  void pushback(T element) {
    if (capacity_ == sizet_) {
      T* tmp = new T[capacity_ + 100];
      for (uint64_t i = 0; i < capacity_; ++i) {
        tmp[i] = array_[i];
      }
      capacity_ += 100;
      delete [] array_;
      array_ = tmp;
    } 
    array_[sizet_] = element;
    ++sizet_;
  }

  void insert(T element) {
    T* tmp = new T[capacity_ + 1];
    for (uint64_t i = 1; i < capacity_ + 1; ++i) {
      tmp[i] = array_[i - 1];
    }
    ++capacity_;
    delete [] array_;
    array_ = tmp;
    array_[0] = element;
    ++sizet_;
  }

  void clear() {
    sizet_ = 0;
  }

  void print() {
    for (int i = 0; i < sizet_; ++i) {
      std::cout << array_[i] << ' ';
    }
    std::cout << '\n';
  }

  T pop() {
    if (sizet_ == 0) {
      throw std::invalid_argument("Trying to pop from an empty vector.");
    }
    T element = array_[sizet_ - 1];
    --sizet_;
    return element;
  }

  uint32_t size() const {
    return sizet_;
  }

  const T& operator[](uint64_t index) const {
    if (index < sizet_) {
      return array_[index];
    }
    throw std::invalid_argument("Vector index out of range.");
  }

  T& operator[](uint64_t index) {
    if (index < sizet_) {
      return array_[index];
    }
    throw std::invalid_argument("Vector index out of range.");
  }

  vector<T>& operator=(const vector<T>& other) {
    if (this != &other) {
      delete [] array_;
      array_ = new T[other.capacity_];
      sizet_ = other.sizet_;
      capacity_ = other.capacity_;
      for (uint64_t i = 0; i < sizet_; ++i) {
        array_[i] = other.array_[i];
      }
    }
    return *this;
  }

  ~vector() {
    delete [] array_;
  }

private:
  T* array_;
  uint64_t capacity_;
  uint64_t sizet_;
};