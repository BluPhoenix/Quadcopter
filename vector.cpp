#include "vector.h"

Vector3D::Vector3D(double X, double Y, double Z)
{
	m_dCoords[0] = X;
	m_dCoords[1] = Y;
	m_dCoords[2] = Z;
}


Vector3D::Vector3D()
{
	m_dCoords[0] = 0;
	m_dCoords[1] = 0;
	m_dCoords[2] = 0;
}

void Vector3D::SetX(double X)
{
	m_dCoords[0] = X;
}

void Vector3D::SetY(double Y)
{
	m_dCoords[1] = Y;
}

void Vector3D::SetZ(double Z)
{
	m_dCoords[2] = Z;
}

double Vector3D::GetX() const
{
	return m_dCoords[0];
}

double Vector3D::GetY() const
{
	return m_dCoords[1];
}

double Vector3D::GetZ() const
{
	return m_dCoords[2];
}

double Vector3D::GetLength() const
{
	return sqrt(m_dCoords[0]*m_dCoords[0] + m_dCoords[1]*m_dCoords[1] + m_dCoords[2]*m_dCoords[2]);
}

void Vector3D::Normalize()
{
	double dScale = GetLength();
	m_dCoords[0] /= dScale;
	m_dCoords[1] /= dScale;
	m_dCoords[2] /= dScale;
}

Vector3D Vector3D::operator+(const Vector3D &right)
{
	return Vector3D(m_dCoords[0] + right.GetX(), m_dCoords[1] + right.GetY(), m_dCoords[2] + right.GetZ());
}

Vector3D Vector3D::operator-(const Vector3D &right)
{
	return Vector3D(m_dCoords[0] - right.GetX(), m_dCoords[1] - right.GetY(), m_dCoords[2] - right.GetZ());
}

Vector3D Vector3D::operator*(const Vector3D &right)
{
	Vector3D Value;
	Value.SetX(m_dCoords[1] * right.GetZ() - m_dCoords[2] * right.GetY());
	Value.SetY(m_dCoords[2] * right.GetX() - m_dCoords[0] * right.GetZ());
	Value.SetZ(m_dCoords[0] * right.GetY() - m_dCoords[1] * right.GetX());
	return Value;
}

Vector3D Vector3D::operator*(const double &right)
{
	return Vector3D(m_dCoords[0] * right, m_dCoords[1] * right, m_dCoords[2] * right);
}

Vector3D& Vector3D::operator+=(const Vector3D &right)
{
	m_dCoords[0] += right.GetX();
	m_dCoords[1] += right.GetY();
	m_dCoords[2] += right.GetZ();
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D &right)
{
	m_dCoords[0] -= right.GetX();
	m_dCoords[1] -= right.GetY();
	m_dCoords[2] -= right.GetZ();
	return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D &right)
{
	Vector3D Value;
	Value.SetX(m_dCoords[1] * right.GetZ() - m_dCoords[2] * right.GetY());
	Value.SetY(m_dCoords[2] * right.GetX() - m_dCoords[0] * right.GetZ());
	Value.SetZ(m_dCoords[0] * right.GetY() - m_dCoords[1] * right.GetX());
	*this = Value;
	return *this;
}

Vector3D& Vector3D::operator*=(const double &right)
{
	m_dCoords[0] *= right;
	m_dCoords[1] *= right;
	m_dCoords[2] *= right;
	return *this;
}



Matrix3x3::Matrix3x3(double A11, double A12, double A13, double A21, double A22, double A23, double A31, double A32, double A33)
{
	m_dValues[0][0] = A11;
	m_dValues[0][1] = A12;
	m_dValues[0][2] = A13;
	m_dValues[1][0] = A21;
	m_dValues[1][1] = A22;
	m_dValues[1][2] = A23;
	m_dValues[2][0] = A31;
	m_dValues[2][1] = A32;
	m_dValues[2][2] = A33;
}

Matrix3x3::Matrix3x3()
{
	m_dValues[0][0] = 0;
	m_dValues[0][1] = 0;
	m_dValues[0][2] = 0;
	m_dValues[1][0] = 0;
	m_dValues[1][1] = 0;
	m_dValues[1][2] = 0;
	m_dValues[2][0] = 0;
	m_dValues[2][1] = 0;
	m_dValues[2][2] = 0;
}

Matrix3x3::Matrix3x3(Vector3D Row1, Vector3D Row2, Vector3D Row3)
{
	m_dValues[0][0] = Row1.GetX();
	m_dValues[0][1] = Row1.GetY();
	m_dValues[0][2] = Row1.GetZ();
	m_dValues[1][0] = Row2.GetY();
	m_dValues[1][1] = Row2.GetY();
	m_dValues[1][2] = Row2.GetZ();
	m_dValues[2][0] = Row3.GetX();
	m_dValues[2][1] = Row3.GetY();
	m_dValues[2][2] = Row3.GetZ();
}

void Matrix3x3::SetCell(unsigned int uiRow, unsigned int uiColumn, double dValue)
{
	m_dValues[uiRow][uiColumn] = dValue;
}
