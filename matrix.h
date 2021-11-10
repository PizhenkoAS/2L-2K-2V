#pragma once
#include <utility>
#include <iostream>
#include <complex>

template <class T>
class matrix {
private:
	T** _data;
	int _columns, _rows;

public:
	matrix();
	matrix(const int columns, const int rows);
	matrix(const matrix& rhs);

	void swap(matrix& rhs);

	~matrix();

	int get_columns() const;
	int get_rows() const;

	void set_columns(const int columns);
	void set_rows(const int rows);

	T& operator()(const int columns, const int rows);
	T operator()(const int columns, const int rows) const;

	void operator=(const matrix& rhs);
	matrix operator+(const matrix& rhs);
	matrix operator-(const matrix& rhs);
	matrix operator*(const matrix& rhs);
	matrix operator*(const T rhs);
	matrix operator/(const T rhs);

	bool operator==(const matrix& rhs);
	bool operator!=(const matrix& rhs);
	bool operator>=(const matrix& rhs);
	bool operator<=(const matrix& rhs);
	bool operator>(const matrix& rhs);
	bool operator<(const matrix& rhs);

	double matrix_trace() const;

	template <class T>
	friend std::ostream& operator<< (std::ostream& out, const matrix<T>& lhs);
	template <class T>
	friend std::istream& operator>> (std::istream& in, matrix<T>& lhs);
};


template<class T>
inline matrix<T>::matrix()
{
	_columns = 0;
	_rows = 0;
	_data = NULL;
}
template<class T>
inline matrix<T>::matrix(const int colums, const int rows)
{
	_columns = colums;
	_rows = rows;
	_data = new T * [_columns];
	for (int i = 0; i < _columns; i++) {
		_data[i] = new T[_rows]();
	}
}
template<class T>
inline matrix<T>::matrix(const matrix& rhs) : _columns(rhs._columns), _rows(rhs._rows)
{
	_data = new T * [_columns];
	for (int i = 0; i < _columns; i++) {
		_data[i] = new T[_rows]();
		for (int j = 0; j < _rows; j++) {
			_data[i][j] = rhs._data[i][j];
		}
	}
}

template<class T>
inline void matrix<T>::swap(matrix& rhs)
{
	std::swap(_columns, rhs._columns);
	std::swap(_rows, rhs._rows);
	std::swap(_data, rhs._data);
}

template<class T>
inline matrix<T>::~matrix()
{
	for (int i = 0; i < _columns; i++) {
		delete[] _data[i];
	}
	delete[] _data;
}

template<class T>
inline int matrix<T>::get_columns() const
{
	return _columns;
}
template<class T>
inline int matrix<T>::get_rows() const
{
	return _rows;
}

template<class T>
inline void matrix<T>::set_columns(const int columns)
{
	_columns = columns;
	_data = new T * [_columns];
}

template<class T>
inline void matrix<T>::set_rows(const int rows)
{
	_rows = rows;
	for (int i = 0; i < _columns; i++) {
		_data[i] = new T[_rows]();
	}
}

template<class T>
inline T& matrix<T>::operator()(const int columns, const int rows)
{
	if (_columns <= columns || _rows <= rows)
		throw std::out_of_range("error");
	return _data[columns][rows];
}
template<class T>
inline T matrix<T>::operator()(const int columns, const int rows) const
{
	if (_columns <= columns || _rows <= rows)
		throw std::out_of_range("error");
	return _data[columns][rows];
}

template<class T>
inline void matrix<T>::operator=(const matrix& rhs)
{
	matrix tmp(rhs);
	swap(tmp);
}
template<class T>
inline matrix<T> matrix<T>::operator+(const matrix& rhs)
{
	if (_rows != rhs._rows || _columns != rhs._columns)
		throw std::logic_error("Matrices with different sizes cannot be added!");
	matrix c(_columns, _rows);
	for (int i = 0; i < c._columns; i++) {
		c._data[i] = new T[c._rows];
		for (int j = 0; j < c._rows; j++) {
			c._data[i][j] = _data[i][j] + rhs._data[i][j];
		}
	}
	return c;
}
template<class T>
inline matrix<T> matrix<T>::operator-(const matrix& rhs)
{
	if (_rows != rhs._rows || _columns != rhs._columns)
		throw std::logic_error("Matrices with different sizes cannot be added!");
	matrix c(_columns, _rows);
	for (int i = 0; i < c._columns; i++) {
		c._data[i] = new T[c._rows];
		for (int j = 0; j < c._rows; j++) {
			c._data[i][j] = _data[i][j] - rhs._data[i][j];
		}
	}
	return c;
}
template<class T>
inline matrix<T> matrix<T>::operator*(const matrix& rhs)
{
	if (_rows != rhs._columns)
		throw std::logic_error("Matrices of different sizes!");
	matrix c(_columns, rhs._rows);

	for (int i = 0; i < _columns; i++) {
		c._data[i] = new T[c._rows];
		for (int j = 0; j < rhs._rows; j++) {
			c._data[i][j] = 0;
			for (int k = 0; k < _rows; k++) {
				c._data[i][j] += _data[i][k] * rhs._data[k][j];
			}
		}
	}
	return c;
}
template<class T>
inline matrix<T> matrix<T>::operator*(const T rhs)
{
	matrix<T> c(_columns, _rows);
	for (int i = 0; i < _columns; i++) {
		c._data[i] = new T[c._rows];
		for (int j = 0; j < _rows; j++) {
			c._data[i][j] = _data[i][j] * rhs;
		}
	}
	return c;
}
template<class T>
inline matrix<T> matrix<T>::operator/(const T rhs)
{
	matrix<T> c(_columns, _rows);
	for (int i = 0; i < _columns; i++) {
		c._data[i] = new T[c._rows];
		for (int j = 0; j < _rows; j++) {
			c._data[i][j] = _data[i][j] / rhs;
		}
	}
	return c;
}

template<class T>
inline bool matrix<T>::operator==(const matrix& rhs)
{
	if (_columns != rhs._columns || _rows != rhs._rows)
		throw std::logic_error("Matrices of different sizes!");
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			if (_data[i][j] != rhs._data[i][j])
				return false;
		}
	}
	return true;
}
template<class T>
inline bool matrix<T>::operator!=(const matrix& rhs)
{
	return !this->operator==(rhs);
}
template<class T>
inline bool matrix<T>::operator>=(const matrix& rhs)
{
	if (_columns != rhs._columns || _rows != rhs._rows)
		throw std::logic_error("Matrices of different sizes!");
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			if (_data[i][j] < rhs._data[i][j])
				return false;
		}
	}
	return true;
}
inline bool matrix<std::complex<double>>::operator>=(const matrix& rhs)
{
	if (_columns != rhs._columns || _rows != rhs._rows)
		throw std::logic_error("Matrices of different sizes!");
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			if (sqrt(pow(_data[i][j].imag(), 2) + pow(_data[i][j].real(), 2)) < sqrt(pow(rhs._data[i][j].imag(), 2) + pow(rhs._data[i][j].real(), 2)))
				return false;
		}
	}
	return true;
}
inline bool matrix<std::complex<float>>::operator>=(const matrix& rhs)
{
	if (_columns != rhs._columns || _rows != rhs._rows)
		throw std::logic_error("Matrices of different sizes!");
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			if (sqrt(pow(_data[i][j].imag(), 2) + pow(_data[i][j].real(), 2)) < sqrt(pow(rhs._data[i][j].imag(), 2) + pow(rhs._data[i][j].real(), 2)))
				return false;
		}
	}
	return true;
}
template<class T>
inline bool matrix<T>::operator<=(const matrix& rhs)
{
	return !this->operator>=(rhs);
}

template<class T>
inline bool matrix<T>::operator>(const matrix& rhs)
{
	if (_rows != rhs._rows || _columns != rhs._columns)
		throw std::logic_error("Matrices of different sizes!");
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			if (_data[i][j] <= rhs._data[i][j])
				return false;
		}
	}
	return true;
}
inline bool matrix<std::complex<double>>::operator>(const matrix& rhs)
{
	if (_columns != rhs._columns || _rows != rhs._rows)
		throw std::logic_error("Matrices of different sizes!");
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			if (sqrt(pow(_data[i][j].imag(), 2) + pow(_data[i][j].real(), 2)) <= sqrt(pow(rhs._data[i][j].imag(), 2) + pow(rhs._data[i][j].real(), 2)))
				return false;
		}
	}
	return true;
}
inline bool matrix<std::complex<float>>::operator>(const matrix& rhs)
{
	if (_columns != rhs._columns || _rows != rhs._rows)
		throw std::logic_error("Matrices of different sizes!");
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			if (sqrt(pow(_data[i][j].imag(), 2) + pow(_data[i][j].real(), 2)) <= sqrt(pow(rhs._data[i][j].imag(), 2) + pow(rhs._data[i][j].real(), 2)))
				return false;
		}
	}
	return true;
}
template<class T>
inline bool matrix<T>::operator<(const matrix& rhs)
{
	return !this->operator>(rhs);
}

template<class T>
inline double matrix<T>::matrix_trace() const
{
	if (_columns != _rows)
		throw std::logic_error("The matrix is not square!");
	double res = 0;
	for (int i = 0; i < _columns; i++) {
		res += _data[i][i];
	}
	return res;
}

inline double matrix<std::complex<double>>::matrix_trace() const {
	double res = 0;
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			res += sqrt(pow(_data[i][j].imag(), 2) + pow(_data[i][j].real(), 2));
		}
	}
	return res;
}
inline double matrix<std::complex<float>>::matrix_trace() const {
	double res = 0;
	for (int i = 0; i < _columns; i++) {
		for (int j = 0; j < _rows; j++) {
			res += sqrt(pow(_data[i][j].imag(), 2) + pow(_data[i][j].real(), 2));
		}
	}
	return res;
}

template<class T>
inline std::ostream& operator<<(std::ostream& out, const matrix<T>& lhs)
{
	for (int i = 0; i < lhs._columns; i++) {
		for (int j = 0; j < lhs._rows; j++) {
			out << lhs._data[i][j] << " ";
		}
		out << "\n";
	}
	return out;
}

template<class T>
inline std::istream& operator>>(std::istream& in, matrix<T>& lhs)
{
	for (int i = 0; i < lhs._columns; i++) {
		for (int j = 0; j < lhs._rows; j++) {
			std::cout << "input data[" << i << "][" << j << "] - ";
			in >> lhs._data[i][j];
		}
	}
	return in;
}
inline std::istream& operator>>(std::istream& in, matrix<std::complex <float>>& lhs) {
	for (int i = 0; i < lhs.get_columns(); i++) {
		for (int j = 0; j < lhs.get_rows(); j++) {
			float real = 0, imagine = 0;
			std::cout << "\nData [" << i << ", " << j << "]\nInput real part: ";
			std::cin >> real;
			std::cout << "Input imagine part: ";
			std::cin >> imagine;
			lhs(i, j) = { real, imagine };
		}
	}
	return in;
}
inline std::istream& operator>>(std::istream& in, matrix<std::complex <double>>& lhs) {
	for (int i = 0; i < lhs.get_columns(); i++) {
		for (int j = 0; j < lhs.get_rows(); j++) {
			double real = 0, imagine = 0;
			std::cout << "\nData [" << i << ", " << j << "]\nInput real part: ";
			std::cin >> real;
			std::cout << "Input imagine part: ";
			std::cin >> imagine;
			lhs(i, j) = { real, imagine };
		}
	}
	return in;
}
