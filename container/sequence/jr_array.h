#ifndef JR_ARRAY_H
#define JR_ARRAY_H

#include <cstddef>

/* array为聚合类类型（C++ Prime 7.5.5）;
 * 没有显式的构造/复制/销毁;
 * 也没有非public的成员。
 */

namespace jr_std {
  template<class T, size_t N>
  struct array {
    // 类型
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T* iterator;
    typedef const T* const_iterator;
    value_type _base_array[N];
    // 聚合类型无显式的构造/复制/销毁
    void fill(const T& u) {
        for(int i = 0; i < N; i++)
            _base_array[i] = u;
    }

    void swap(array& x) noexcept {
        if(this == &x)    return;
        for(size_type i = 0; i < N; i++) {
            value_type tmp = (*this)[i];
            (*this)[i] = x[i];
            x[i] = tmp;
        }
    }

    // 迭代器
    iterator begin() noexcept { return _base_array; }
    const_iterator begin() const noexcept { return _base_array; }
    iterator end() noexcept { return _base_array+N; }
    const_iterator end() const noexcept { return _base_array+N; }
    const_iterator cbegin() const noexcept { return _base_array; }
    const_iterator cend() const noexcept { return _base_array+N; }

    // 容量
    bool empty() const noexcept { return N==0; }
    size_type size() const noexcept { return N; }
    size_type max_size() const noexcept { return N; }

    // 元素访问
    reference operator[](size_type n) { return _base_array[n]; }
    const_reference operator[](size_type n) const { return _base_array[n]; }
    reference at(size_type n) { return _base_array[n]; }
    const_reference at(size_type n) const { return _base_array[n]; }
    reference front() { return _base_array[0]; }
    const_reference front() const { return _base_array[0]; }
    reference back() { return _base_array[N-1]; }
    const_reference back() const { return _base_array[N-1]; }

    T *data() noexcept { return _base_array; }
    const T *data() const noexcept { return _base_array; }
  };

  // 同大小的两array才可交换
  template< class T, std::size_t N >
  void swap( jr_std::array<T,N>& lhs,
             jr_std::array<T,N>& rhs )
  { lhs.swap(rhs); }

  template< class T, std::size_t N >
  bool operator==( const jr_std::array<T,N>& lhs,
                   const jr_std::array<T,N>& rhs ) {
      for(int i = 0; i < N; i++) {
          if(lhs[i] != rhs[i])
              return false;
      }
      return true;
  }

  template< class T, std::size_t N >
  bool operator!=( const jr_std::array<T,N>& lhs,
                   const jr_std::array<T,N>& rhs ) {
      return !(lhs == rhs);
  }

  template< class T, std::size_t N >
  bool operator<( const jr_std::array<T,N>& lhs,
                  const jr_std::array<T,N>& rhs ) {
      for(int i = 0; i < N; i++) {
          if(lhs[i] >= rhs[i])
              return false;
      }
      return true;
  }

  template< class T, std::size_t N >
  bool operator>( const jr_std::array<T,N>& lhs,
                  const jr_std::array<T,N>& rhs ) {
      for(int i = 0; i < N; i++) {
          if(lhs[i] <= rhs[i])
              return false;
      }
      return true;
  }

  template< class T, std::size_t N >
  bool operator<=( const jr_std::array<T,N>& lhs,
                   const jr_std::array<T,N>& rhs ) {
      return !(lhs > rhs);
  }

  template< class T, std::size_t N >
  bool operator>=( const jr_std::array<T,N>& lhs,
                   const jr_std::array<T,N>& rhs ) {
      return !(lhs < rhs);
  }

  template< size_t I, class T, size_t N >
  T& get( jr_std::array<T,N>& a ) noexcept {
      return a[I];
  }

  template< size_t I, class T, size_t N >
  const T& get( const jr_std::array<T,N>& a ) noexcept {
      return a[I];
  }

  template< std::size_t I, class T, std::size_t N >
  T&& get( jr_std::array<T,N>&& a ) noexcept {
      return a[I];
  }

  template< std::size_t I, class T, std::size_t N >
  const T&& get( const jr_std::array<T,N>&& a ) noexcept {
      return a[I];
  }

//  template<class T, class... U>
//    array(T, U...) -> array<T, 1 + sizeof...(U)>;
}

#endif // JR_ARRAY_H
