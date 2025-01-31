#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Matrix
{
public:
	Matrix(int rows, int columns);
	Matrix(const Matrix& other);
	~Matrix();
	
	Matrix& operator=(const Matrix& other);
	bool operator==(const Matrix& other);
	//bool operator!=(const Matrix& other);
	Matrix& operator+(const Matrix& other);
	double& operator()(int row, int column);
	
	bool compatible(const Matrix& other);

	void print();

	int get_rows()const { return rows; }
	int get_columns()const { return columns; }
private:
	double* container = nullptr; //ARRAY
	int rows=0;
	int columns=0;
};

Matrix::Matrix(int r, int c):rows{r},columns{c}
{
	if (r*c<=0)
	{
		cout << "\nerror: weird number of rows or columns. number of rows set to 1. number of columns set to 1.\n";
		rows = 1, columns = 1;
	}
	container = new double[rows * columns];
	for (int i = 0; i < rows*columns; i++)
	{
		container[i] = 0;
	}
}
Matrix::Matrix(const Matrix& other)
{
	if (other == *this)
	{
		return;
	}
	delete[] container;
	rows = other.rows;
	columns = other.columns;
	container = new double[rows * columns];
	for (int i = 0; i < rows*columns; i++)
	{
		container[i] = other.container[i];
	}
}

Matrix::~Matrix()
{
	delete[] container;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (other==*this)
	{
		return *this;
	}
	delete[] container;
	rows = other.rows;
	columns = other.columns;
	container = new double[rows * columns];
	for (int i = 0; i < rows * columns; i++)
	{
		container[i] = other.container[i];
	}
	return *this;
}

bool Matrix::operator==(const Matrix& other)
{
	if ((rows!=other.rows)||(columns!=other.columns))
	{
		return false;
	}
	for (int i = 0; i < rows*columns; i++)
	{
		if (container[i]!=other.container[i])
		{
			return false;
		}
	}
	return true;
}
/*
bool Matrix::operator!=(const Matrix& other)
{
	return !(*this == other);
}
*/
Matrix& Matrix::operator+(const Matrix& other)
{
	if (!compatible(other))
	{
		cout << "\nerror:can't add incompatible matrices, returned self with no change\n";
		return *this;
	}
	for (int i = 0; i < rows*columns; i++)
	{
		container[i] += other.container[i];
	}
	return *this;
}

double& Matrix::operator()(int row, int column)
{
	int r = row - 1;
	int c = column - 1;
		
	if ((r>rows)||(c>columns)||(r<0)||(c<0))
	{
		std::cout << "\nerror: row or column out of range, change applied to first row first column\n";
		return container[0];
	}
	//cout << (r * columns) + c<<endl;
	return container[(r)*columns+c];
}


bool Matrix::compatible(const Matrix& other)
{
	if ((rows!=other.rows)||(columns!=other.columns))
	{
		
		return false;
	}
	return true;
}

void Matrix::print()
{
	for (int i = 0; i < rows; i++)
	{
		cout << '\n' << '{';
		for (int ii = 0; ii < columns; ii++)
		{
			
			cout << container[(i)*columns + ii]<<';';
			//cout<<'(' << (i)*columns+ii << ')'<<' ';
		}
		cout << '}';
	}
}

int main()
{
	Matrix a(2, 3);
	int b = 0;
	for (int i = 0; i < a.get_rows(); i++)
	{
		for (int ii = 0; ii < a.get_columns(); ii++)
		{
			b++;
			a(i + 1, ii + 1) = b;
		}
	}
	a(2, 3) = 18;
	
	a.print();
}

