// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <assert.h>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should be less or equal MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& other)
  {
      sz = other.sz;
      pMem = new T [sz];
      for (size_t i = 0; i < sz; i++)
          pMem[i] = other.pMem[i];
  }
  TDynamicVector(TDynamicVector&& other) noexcept
  {
      pMem = other.pMem;
      other.pMem = nullptr;
      sz = other.sz;
  }

  ~TDynamicVector()
  {
      delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& other)
  {
      sz = other.sz;
      pMem = new T[sz];
      for (size_t i = 0; i < sz; i++)
          pMem[i] = other.pMem[i];
      return *this;

  }
  TDynamicVector& operator=(TDynamicVector&& other) noexcept
  {
      swap(pMem, other.pMem);
      sz = other.sz;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t i)
  {
      return pMem[i];
  }
  const T& operator[](size_t i) const
  {
      return pMem[i];

  }
  // индексация с контролем
  T& at(size_t i)
  {
      if (i >= sz)
          throw(out_of_range("Index out of range"));
      return pMem[i];
  }
  const T& at(size_t ind) const
  {
      if (i >= sz)
          throw(out_of_range("Index out of range"));
      return pMem[i];
  }

  // сравнение
  bool operator==(const TDynamicVector& other) const noexcept
  {
      if (this == &other)
          return true;
      if (sz == other.sz)
      {
          bool flag = true;
          for (size_t i = 0; i < sz; i++)
          {
              flag = pMem[i] == other.pMem[i];
              if (flag == false)
                  break;
          }
          return flag;
      }
      else 
      {
          return false;
      }
  }
  bool operator!=(const TDynamicVector& other) const noexcept
  {
      return !(*this == other);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + val;
      return res;

  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - val;
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& other)
  {
      if (sz != other.sz)
          throw logic_error("sum error");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + other.pMem[i];
      return res;

  }
  TDynamicVector operator-(const TDynamicVector& other)
  {
      if (sz != other.sz)
          throw logic_error("sum error");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - other.pMem[i];
      return res;
  }
  T operator*(const TDynamicVector& other) noexcept(noexcept(T()))
  {
      if (sz != other.sz)
          throw logic_error("multiply error");
      T res = T();
      for (size_t i = 0; i < sz; i++)
          res += pMem[i] * other.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s >= MAX_MATRIX_SIZE)
          throw out_of_range(" ");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  using TDynamicVector<TDynamicVector<T>>::at;

  // индексация с контролем
  T& at(size_t row, size_t col)
  {
      return (*this).at(row).at(col);
  }

  size_t size() const noexcept
  {
      return sz;
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      for (int i = 0; i < sz; i++)
          if ((*this)[i] != m[i])
              return false;
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] * val;
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz)
          throw logic_error("Matrix size doesn't match vector size");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] * v;
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] + m[i];
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] - m[i];
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = (*this)[i] * m[i];
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
          for (size_t j = 0; j < m.sz; j++)
              in >> m[i][j];
      return in;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (int i = 0; i < m.sz ; i++)
      {
          for (int j = 0; j < m.sz; j++)
              ostr << m[i][j] << " ";
          cout << '\n';
      }
      return ostr;
  }
};

#endif
