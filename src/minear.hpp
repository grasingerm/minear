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
        Matrix<T>() : n_rows(10), n_cols(10), data(new T[100]), 
            insertion_index(0) {}
        
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
        T& operator()(const unsigned int i, const unsigned int j)
            { return data[i*n_rows + j]; }
        const T& operator() (const unsigned int i, 
            const unsigned int j) const
            { return data[i*n_rows + j]; }
        
        /* printing */
        friend std::ostream& operator<< (std::ostream& stream, const Matrix& a)
        {
            for (unsigned int i = 0; i < a.n_rows; i++)
            {
                for (unsigned int j = 0; j < a.n_cols; j++)
                    stream << " " << a(i,j);
                stream << std::endl;
            }
            
            return stream;
        }
        
        /* memory management */
        void resize(const unsigned int, const unsigned int);
            
    private:
        T* data;
        unsigned int insertion_index;
    };
    
    template <class T> Matrix<T>::Matrix(const unsigned int n, 
        const unsigned int m, const T value) : Matrix<T>(n,m)
    { 
        for (unsigned int i = 0; i < n*m; i++) data[i] = value;
    }
    
    template <class T> Matrix<T>::Matrix(const Matrix<T>& a) : 
        n_rows(a.n_rows), n_cols(a.n_cols)
    {
        data = new T[n_rows*n_cols];
        for (unsigned int i = 0; i < n_rows; i++)
            for (unsigned int j = 0; j < n_cols; j++)
                data[i*n_rows + j] = a(i,j);
    }
    
    template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& a)
    {
        insertion_index = 0;
        T* p = new T[a.n_rows*a.n_cols];
        
        for (unsigned int i = 0; i < n_rows; i++)
            for (unsigned int j = 0; j < n_cols; j++)
                p[i*n_rows + j] = a(i,j);
        
        delete[] data;
        data = p;
        n_rows = a.n_rows;
        n_cols = a.n_cols;
        return *this;
    }
    
    template <class T> Matrix<T>::Matrix(Matrix<T>&& a) :
        n_rows(a.n_rows), n_cols(a.n_cols), data(a.data), insertion_index(0)
    {
        a.data = nullptr;
        a.n_rows = 0;
        a.n_cols = 0;
        a.insertion_index = 0;
    }
    
    template <class T> Matrix<T>& Matrix<T>::operator=(Matrix<T>&& a)
    {
        insertion_index = 0;
        data = a.data;
        n_rows = a.n_rows;
        n_cols = a.n_cols;
        
        a.data = nullptr;
        a.n_rows = 0;
        a.n_cols = 0;
        a.insertion_index = 0;
        
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
        for (unsigned int i = 0; i < a.n_rows; i++)
            for (unsigned int j = 0; j < a.n_cols; j++)
                result(i,j) = a(i,j) + b(i,j);
                
        return result;
    }
    
    template <class T> Matrix<T> operator-(const Matrix<T>& a, 
        const Matrix<T>& b)
    {
        /* TODO: make sure matrices are the same size */
        Matrix<T> result(a.n_rows,a.n_cols);
        for (unsigned int i = 0; i < a.n_rows; i++)
            for (unsigned int j = 0; j < a.n_cols; j++)
                result(i,j) = a(i,j) - b(i,j);
                
        return result;
    }
    
    template <class T> Matrix<T> operator-(const Matrix<T>& a)
    {
        /* TODO: make sure matrices are the same size */
        Matrix<T> result(a.n_rows,a.n_cols);
        for (unsigned int i = 0; i < a.n_rows; i++)
            for (unsigned int j = 0; j < a.n_cols; j++)
                result(i,j) = -a(i,j);
                
        return result;
    }
    
    template <class T> Matrix<T> operator*(const Matrix<T>& a,
        const Matrix<T>& b)
    {
        Matrix<T> result(a.n_rows,b.n_cols,0);
        for (unsigned int i = 0; i < a.n_rows; i++)
        {
            for (unsigned int j = 0; j < b.n_cols; j++)
                for (unsigned int k = 0; k < b.n_rows; k++)
                    result(i,j) += a(i,k)*b(k,j);
        }
        
        return result;
    }
    
    template <class T> void Matrix<T>::resize(const unsigned int n,
        const unsigned int m)
    {
        if (sizeof(data)/sizeof(T) < n*m)
        {
            double* p = data;
            data = new double[n*m];
            delete[] p;
            insertion_index = 0;
        }
        
        n_rows = n;
        n_cols = m;
    }
}

#endif /* __MINEAR_HPP__ */
