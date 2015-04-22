#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>

class Vector3D
{
	private:
		double m_dCoords[3];
	public:
		Vector3D(double X, double Y, double Z);
		Vector3D();

		void SetX(double X);
		void SetY(double Y);
		void SetZ(double Z);
		double GetX() const;
		double GetY() const;
		double GetZ() const;

		double GetLength() const;

		void Normalize();

		Vector3D operator+(const Vector3D &right);
		Vector3D operator-(const Vector3D &right);
		Vector3D operator*(const Vector3D &right);
		Vector3D operator*(const double &right);

		Vector3D& operator+=(const Vector3D &right);
		Vector3D& operator-=(const Vector3D &right);
		Vector3D& operator*=(const Vector3D &right);
		Vector3D& operator*=(const double &right);
};


class Matrix3x3
{
	private:
		double m_dValues[3][3];
	public:
		Matrix3x3(double A11, double A12, double A13, double A21, double A22, double A23, double A31, double A32, double A33);
		Matrix3x3();
		Matrix3x3(Vector3D Row1, Vector3D Row2, Vector3D Row3);
		
		void SetCell(unsigned int uiRow, unsigned int uiColumn, double dValue);
		double GetCell(unsigned int uiRow, unsigned int uiColumn);
		void SetRow(unsigned int uiRow, Vector3D Value);
		Vector3D GetRow(unsigned int uiRow);
		void SetColumn(unsigned int uiColumn, Vector3D Value);
		Vector3D GetColumn(unsigned int uiColumn);
		
		void Normalize();

		Matrix3x3 operator*(const Matrix3x3 &right);
		Matrix3x3 operator*(const double &right);
		Vector3D operator*(const Vector3D &right);

		Matrix3x3& operator*(const Matrix3x3 &right);
		Matrix3x3& operator*(const double &right);
};

#endif
