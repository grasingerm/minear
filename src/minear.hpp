#ifndef __MINEAR_HPP__
#define __MINEAR_HPP__

#include <memory>
#include <iostream>

namespace minear
{
    template <class T> class Matrix
    {
    public:
        unsigned int n_rows;
        unsigned int n_cols;
        
        /* constructors and destructors */
        Matrix<T>() : n_rows(0), n_cols(0), data(nullptr), insertion_index(0) {}
        
        Matrix<T>(const unsigned int n, const unsigned int m) :
            n_rows(n), n_cols(m), data(new T[n*m]), insertion_index(0) {};
        Matrix<T>(const unsigned int n, const unsigned int m, const T value);
        
        Matrix<T>(const Matrix<T>&);
        Matrix<T>& operator=(const Matrix<T>&);
        
        Matrix<T>(Matrix<T>&&);
        Matrix<T>& operator=(Matrix<T>&&);
        
        ~Matrix<T>() { delete[] data; }
        
        /* data insertion */
        Matrix<T>& operator<<(const T value);
        void reset_index() { insertion_index = 0; }
             
        /* data accessors */
        inline T& operator()(const unsigned int i, const unsigned int j)
        { 
            if (i >= n_rows || j >= n_cols) 
                throw std::out_of_range ("Trying to access Matrix out of range."); 
            
            return data[i*n_cols + j];
        }

        inline const T& operator() (const unsigned int i, const unsigned int j) 
            const
        { 
            if (i >= n_rows || j >= n_cols) 
                throw std::out_of_range ("Trying to access Matrix out of range."); 
            
            return data[i*n_cols + j];
        }
        
        /* printing */
        friend std::ostream& operator<< (std::ostream& stream, const Matrix& a)
        {
            for (unsigned int i = 0; i < a.n_rows; ++i)
            {
                for (unsigned int j = 0; j < a.n_cols; ++j)
                    stream << " " << a(i,j);
                stream << std::endl;
            }
            
            return stream;
        }
        
        /* memory management */
        void resize(const unsigned int, const unsigned int);

        /* iterator */
        typedef T* iterator;
        typedef const T* const_iterator;
        iterator begin() { return data; }
        iterator end() { return (data + n_rows * n_cols); }
        const_iterator begin() const { return data; }
        const_iterator end() const { return (data + n_rows * n_cols); }
        const_iterator cbegin() const { return data; }
        const_iterator cend() const { return (data + n_rows * n_cols); }
            
    private:
        T* data;
        unsigned int insertion_index;
    };
    
    template <class T> Matrix<T>::Matrix(const unsigned int n, 
        const unsigned int m, const T value) : Matrix<T>(n,m)
    { 
        for (auto& elem : *this) elem = value;
    }
    
    template <class T> Matrix<T>::Matrix(const Matrix<T>& a) : 
        n_rows(a.n_rows), n_cols(a.n_cols)
    {
        data = new T[n_rows*n_cols];
        for (unsigned int i = 0; i < n_rows; ++i)
            for (unsigned int j = 0; j < n_cols; ++j)
                (*this)(i,j) = a(i,j);
    }
    
    template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& a)
    {
        resize(a.n_rows, a.n_cols);
        insertion_index = 0;
        
        for (unsigned int i = 0; i < n_rows; ++i)
            for (unsigned int j = 0; j < n_cols; ++j)
                (*this)(i,j) = a(i,j);
        
        return *this;
    }
    
    template <class T> Matrix<T>::Matrix(Matrix<T>&& a) :
        n_rows(a.n_rows), n_cols(a.n_cols), data(a.data), insertion_index(0)
    {
        a.data = nullptr; /* ensure nothing funny happens when a is deleted */
    }
    
    template <class T> Matrix<T>& Matrix<T>::operator=(Matrix<T>&& a)
    {
        insertion_index = 0;
        
        /* delete old memory, move rvalue memory in */
        T* p = data;
        data = a.data;
        delete[] p;
        
        n_rows = a.n_rows;
        n_cols = a.n_cols;
        
        a.data = nullptr;
        
        return *this;
    }
    
    template <class T> Matrix<T>& Matrix<T>::operator<<(const T value)
    {
        data[insertion_index] = value;
        insertion_index++;
        if (insertion_index == n_rows*n_cols) insertion_index = 0;
        return *this;
    }
    
    template <class T> Matrix<T> operator+(const Matrix<T>& a, 
        const Matrix<T>& b)
    {
        /* TODO: make sure matrices are the same size */
        Matrix<T> result(a.n_rows,a.n_cols);
        for (unsigned int i = 0; i < a.n_rows; ++i)
            for (unsigned int j = 0; j < a.n_cols; ++j)
                result(i,j) = a(i,j) + b(i,j);
                
        return result;
    }
    
    template <class T> Matrix<T> operator-(const Matrix<T>& a, 
        const Matrix<T>& b)
    {
        /* TODO: make sure matrices are the same size */
        Matrix<T> result(a.n_rows,a.n_cols);
        for (unsigned int i = 0; i < a.n_rows; ++i)
            for (unsigned int j = 0; j < a.n_cols; ++j)
                result(i,j) = a(i,j) - b(i,j);
                
        return result;
    }
    
    template <class T> Matrix<T> operator-(const Matrix<T>& a)
    {
        /* TODO: make sure matrices are the same size */
        Matrix<T> result(a.n_rows,a.n_cols);
        for (unsigned int i = 0; i < a.n_rows; ++i)
            for (unsigned int j = 0; j < a.n_cols; ++j)
                result(i,j) = -a(i,j);
                
        return result;
    }
    
    template <class T> Matrix<T> operator*(const Matrix<T>& a,
        const Matrix<T>& b)
    {
        Matrix<T> result(a.n_rows,b.n_cols,0);
        for (unsigned int i = 0; i < a.n_rows; ++i)
        {
            for (unsigned int j = 0; j < b.n_cols; ++j)
                for (unsigned int k = 0; k < b.n_rows; ++k)
                    result(i,j) += a(i,k)*b(k,j);
        }
        
        return result;
    }

    template <class T> Matrix<T> operator*(const Matrix<T>& a, const T& s)
    {
        Matrix<T> result(a);
        for (auto& elem : result) elem *= s;

        return result;
    }

    template <class T> Matrix<T> operator*(const T& s, const Matrix<T>& a)
    {
        Matrix<T> result(a);
        for (auto& elem : result) elem *= s;

        return result;
    }
    
    template <class T> void Matrix<T>::resize(const unsigned int n,
        const unsigned int m)
    {
        if (sizeof(data)/sizeof(T) < n*m)
        {
            T* p = data;
            data = new T[n*m];
            delete[] p;
            insertion_index = 0;
        }
        
        n_rows = n;
        n_cols = m;
    }
}

#endif /* __MINEAR_HPP__ */
