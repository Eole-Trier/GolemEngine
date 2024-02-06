#include <iomanip>


Matrix2::Matrix2()
{
}

Matrix2::~Matrix2() 
{
}

Matrix2::Matrix2(
	float _a, float _b, 
	float _c, float _d
)
{
	data[0][0] = _a;
	data[0][1] = _b;
	data[1][0] = _c;
	data[1][1] = _d;
}

Matrix2::Matrix2(float _number)
{
	data[0][0] = data[0][1] = data[1][0] = data[1][1] = _number;
}


Matrix2 Matrix2::Identity()
{
	Matrix2 identity(
		1, 0,
		0, 1
	);
	return identity;
}

Matrix2 Matrix2::Transpose()
{
	Matrix2 Transpose;

	for (int i = 0; i < 2; i++) {
		// assign Vector2 as new column of matrix
		float temp[2];
		for (int j = 0; j < 2; j++) {
			temp[j] = data[i][j];
		}
		// set the temp Vector2 to the correct lign of the tranposed matrix
		for (int k = 0; k < 2; k++) {
			Transpose.data[k][i] = temp[k];
		}
	}
	return Transpose;
}

Vector2 Matrix2::Diagonal()
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
	Vector2 diagonal(temp[0], temp[1]);
	return diagonal;
}

float Matrix2::Trace()
{
	Vector2 temp = this->Diagonal();
	float trace = temp.x + temp.y;
	return trace;
}

float Matrix2::Determinant()
{
	float result =
		data[0][0] * data[1][1] -
		data[1][0] * data[0][1];
	return result;
}

Matrix2 Matrix2::Rotate(float _angleRad)
{
	Matrix2 temp(
		cos(_angleRad), sin(_angleRad),
		-sin(_angleRad), cos(_angleRad)
	);
	return temp;
}

// TODO : GaussJordan


#pragma region Operators

Matrix2 operator+(Matrix2 _A, float _n)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			_A.data[i][j] += _n;
	return _A;
}

Matrix2 operator-(Matrix2 _A, float _n)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			_A.data[i][j] -= _n;
	return _A;
}

Matrix2 operator*(Matrix2 _A, float _n)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			_A.data[i][j] *= _n;
	return _A;
}

Matrix2 operator/(Matrix2 _A, float _s)
{
	return _A * (1.0f / _s);
}

Matrix2 operator+(Matrix2 _A, Matrix2 _B)
{
	Matrix2 temp;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			temp.data[i][j] = _A.data[i][j] + _B.data[i][j];
	return temp;
}

Matrix2 operator-(Matrix2 _A, Matrix2 _B)
{
	Matrix2 temp;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			temp.data[i][j] = _A.data[i][j] - _B.data[i][j];
	return temp;
}

Matrix2 operator*(Matrix2 _A, Matrix2 _B)
{
	Matrix2 temp;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				temp.data[i][j] += _A.data[i][k] * _B.data[k][j];
	return temp;
}


std::ostream& operator<<(std::ostream& _os, const Matrix2& _matrix2)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			_os << _matrix2.data[i][j] << " ";
		_os << "\n";
	}
	return _os;
}

#pragma endregion Operators