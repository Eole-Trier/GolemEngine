#include <iomanip>


Matrix3::Matrix3()
{
}

Matrix3::~Matrix3() 
{ 
}

Matrix3::Matrix3(
	float a, float b, float c,
	float d, float e, float f,
	float g, float h, float i
)
{
	data[0][0] = a;
	data[0][1] = b;
	data[0][2] = c;
	data[1][0] = d;
	data[1][1] = e;
	data[1][2] = f;
	data[2][0] = g;
	data[2][1] = h;
	data[2][2] = i;
}

Matrix3::Matrix3(float _number)
{
	data[0][0] = data[0][1] = data[0][2] = data[1][0] = data[1][1] = data[1][2] = data[2][0] = data[2][1] = data[2][2] = _number;
}


Matrix3 Matrix3::Transpose()
{
	Matrix3 Transpose;

	for (int i = 0; i < 3; i++) {
		// assign Vector3 as new column of matrix
		float temp[3];
		for (int j = 0; j < 3; j++) {
			temp[j] = data[i][j];
		}
		// set the temp Vector3 to the correct lign of the tranposed matrix
		for (int k = 0; k < 3; k++) {
			Transpose.data[k][i] = temp[k];
		}
	}
	return Transpose;
}

Vector3 Matrix3::Diagonal()
{
	float temp[3];
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				temp[k] = data[i][j];
				k++;
			}
		}
	}
	Vector3 diagonal(temp[0], temp[1], temp[2]);
	return diagonal;
}

float Matrix3::Trace()
{
	Vector3 temp = this->Diagonal();
	float trace = temp.x + temp.y + temp.z;
	return trace;
}

float Matrix3::Determinant()
{
	float result =
		data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
		data[0][1] * (data[1][0] * data[2][2] - data[2][0] * data[1][2]) +
		data[0][2] * (data[1][0] * data[2][1] - data[2][0] * data[1][1]);
	return result;
}

Matrix3 Matrix3::RotateX(float _angleRad)
{
	Matrix3 temp(
		1, 0, 0,
		0, cos(_angleRad), -sin(_angleRad),
		0, sin(_angleRad), cos(_angleRad)
	);
	return temp;
}

Matrix3 Matrix3::RotateY(float _angleRad)
{
	Matrix3 temp(
		cos(_angleRad), 0, sin(_angleRad),
		0, 1, 0,
		-sin(_angleRad), 0, cos(_angleRad)
	);
	return temp;
}

Matrix3 Matrix3::RotateZ(float _angleRad)
{
	Matrix3 temp(
		cos(_angleRad), -sin(_angleRad), 0,
		-sin(_angleRad), cos(_angleRad), 0,
		0, 0, 1
	);
	return temp;
}



#pragma region Operators

Matrix3 operator+(Matrix3 _A, float _n)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_A.data[i][j] += _n;
	return _A;
}

Matrix3 operator-(Matrix3 _A, float _n)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_A.data[i][j] -= _n;
	return _A;
}

Matrix3 operator*(Matrix3 _A, float _n)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_A.data[i][j] *= _n;
	return _A;
}

Matrix3 operator/(Matrix3 _A, float _s)
{
	return _A * (1.0f / _s);
}

Matrix3 operator+(Matrix3 _A, Matrix3 _B)
{
	Matrix3 temp;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			temp.data[i][j] = _A.data[i][j] + _B.data[i][j];
	return temp;
}

Matrix3 operator-(Matrix3 _A, Matrix3 _B)
{
	Matrix3 temp;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			temp.data[i][j] = _A.data[i][j] - _B.data[i][j];
	return temp;
}

Matrix3 operator*(Matrix3 _A, Matrix3 _B)
{
	Matrix3 temp;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				temp.data[i][j] += _A.data[i][k] * _B.data[k][j];
	return temp;
}


std::ostream& operator<<(std::ostream& _os, const Matrix3& _matrix3)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			_os << _matrix3.data[i][j] << " ";
		_os << "\n";
	}
	return _os;
}

#pragma endregion Operators