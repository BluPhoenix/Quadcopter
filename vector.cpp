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

Vector3D Vector3D::operator+(const Vector3D &right) const
{
	return Vector3D(m_dCoords[0] + right.GetX(), m_dCoords[1] + right.GetY(), m_dCoords[2] + right.GetZ());
}

Vector3D Vector3D::operator-(const Vector3D &right) const
{
	return Vector3D(m_dCoords[0] - right.GetX(), m_dCoords[1] - right.GetY(), m_dCoords[2] - right.GetZ());
}

Vector3D Vector3D::Cross(const Vector3D left, const Vector3D right)
{
	Vector3D Value;
	Value.SetX(left.GetY() * right.GetZ() - left.GetZ() * right.GetY());
	Value.SetY(left.GetZ() * right.GetX() - left.GetX() * right.GetZ());
	Value.SetZ(left.GetX() * right.GetY() - left.GetY() * right.GetX());
	return Value;
}

double Vector3D::operator*(const Vector3D &right) const
{
	return m_dCoords[0] * right.GetX() + m_dCoords[1] * right.GetY() + m_dCoords[2] * right.GetZ();
}

Vector3D Vector3D::operator*(const double &right) const
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

double Matrix3x3::GetCell(unsigned int uiRow, unsigned int uiColumn) const
{
	return m_dValues[uiRow][uiColumn];
}

void Matrix3x3::SetRow(unsigned int uiRow, Vector3D Value)
{
	m_dValues[uiRow][0] = Value.GetX();
	m_dValues[uiRow][1] = Value.GetY();
	m_dValues[uiRow][2] = Value.GetZ();
}

Vector3D Matrix3x3::GetRow(unsigned int uiRow) const
{
	return Vector3D(m_dValues[uiRow][0], m_dValues[uiRow][1], m_dValues[uiRow][2]); 
}


void Matrix3x3::SetColumn(unsigned int uiColumn, Vector3D Value)
{
	m_dValues[0][uiColumn] = Value.GetX();
	m_dValues[1][uiColumn] = Value.GetY();
	m_dValues[2][uiColumn] = Value.GetZ();
}

Vector3D Matrix3x3::GetColumn(unsigned int uiColumn) const
{
	return Vector3D(m_dValues[0][uiColumn], m_dValues[1][uiColumn], m_dValues[2][uiColumn]); 
}

Matrix3x3 Matrix3x3::GetTranspose() const
{
	return Matrix3x3(m_dValues[0][0], m_dValues[1][0], m_dValues[2][0],
		   			 m_dValues[0][1], m_dValues[1][1], m_dValues[2][1],
					 m_dValues[0][2], m_dValues[1][2], m_dValues[2][2]);
}

void Matrix3x3::Renormalization()
{
	Vector3D Xorth, Yorth, Zorth, X = GetRow(0), Y = GetRow(1);
	double Error = X * Y;
	Xorth = X - Y * Error;
	Yorth = Y - X * Error;
	Zorth = Vector3D::Cross(Xorth, Yorth);
	// Normalize via Taylor expansion
	Xorth = Xorth * 0.5d * (3.0d - Xorth * Xorth);
	Yorth = Yorth * 0.5d * (3.0d - Yorth * Yorth);
	Zorth = Zorth * 0.5d * (3.0d - Zorth * Zorth);
	SetRow(0, Xorth);
	SetRow(1, Yorth);
	SetRow(2, Zorth);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &right) const
{
	Matrix3x3 ret;
	for (unsigned int iRow = 0; iRow < 3; iRow++)
	{
		for (unsigned int iCol = 0; iCol < 3; iCol++)
		{
			ret.SetCell(iRow, iCol, this->GetRow(iRow) * right.GetColumn(iCol));
		}
	}
	return ret;
}

Matrix3x3 Matrix3x3::operator*(const double &right) const
{
	Matrix3x3 ret = *this;
	for (unsigned int iRow = 0; iRow < 3; iRow++)
	{
		for (unsigned int iCol = 0; iCol < 3; iCol++)
		{
			ret.SetCell(iRow,iCol, right * m_dValues[iRow][iCol]);
		}
	}
	return ret;
}

Vector3D Matrix3x3::operator*(const Vector3D &right) const
{
	return Vector3D(GetRow(0) * right, GetRow(1) * right, GetRow(2) * right);
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3 &right)
{
	Matrix3x3 temp;
	for (unsigned int iRow = 0; iRow < 3; iRow++)
	{
		for (unsigned int iCol = 0; iCol < 3; iCol++)
		{
			temp.SetCell(iRow, iCol, this->GetRow(iRow) * right.GetColumn(iCol));
		}
	}
	*this = temp;
	return *this;
}

Matrix3x3& Matrix3x3::operator*=(const double &right)
{
	for (unsigned int iRow = 0; iRow < 3; iRow++)
	{
		for (unsigned int iCol = 0; iCol < 3; iCol++)
		{
			m_dValues[iRow][iCol] *= right;
		}
	}
	return *this;
}

