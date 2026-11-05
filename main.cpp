#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// This class stores the matrix data and its size.
class Matrix {
private:
    int n;
    vector<int> data;

public:
    // Create a matrix and fill it with zeros.
    Matrix(int size) : n(size), data(size * size, 0) {}

    int getSize() const {
        return n;
    }

    // Get or change a value in the matrix.
    int get(int row, int col) const {
        return data[row * n + col];
    }

    void set(int row, int col, int value) {
        data[row * n + col] = value;
    }

    // Read all matrix values from the input file.
    bool readMatrix(istream& file) {
        for (int i = 0; i < n * n; i++) {
            if (!(file >> data[i])) {
                return false;
            }
        }
        return true;
    }

    // Print the matrix with aligned columns.
    void display() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(4) << get(i, j);
            }
            cout << endl;
        }
    }
// Add two matrices using the + operator.
	Matrix operator+(const Matrix& other) const {
		Matrix result(n);
	
		for(int i = 0; i<n; i++) {
			for(int j = 0; j < n; j++) {
				int sum = get(i, j) + other.get(i, j);
				result.set(i, j, sum);
			}

		}
		return result;

	}
    // Multiply two matrices using the * operator.
    Matrix operator*(const Matrix& other) const {
        Matrix result(n);

        // Multiply each row by each column.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int sum = 0;

                for (int k = 0; k < n; k++) {
                    sum += get(i, k) * other.get(k, j);
                }

                result.set(i, j, sum);
            }
        }

        return result;
    }
//calculate the sum of the main diagonal.
int mainDiagonalSum() const{
    int sum = 0;
	
	for(int i = 0; i<n;i++){
		sum+=get(i,i);
	}
	return sum;
}
//calculating the secondary diagonal
int secondaryDiagonalSum() const{
	int sum=0;
	
	for(int i =0; i<n; i++){
        sum += get(i, n - 1 - i);
	}
    return sum;
}
};
// Swap two rows without changing the original matrix.
Matrix swapRows(Matrix matrix, int row1 = 0, int row2 = 1) {

    // Make sure both row numbers are valid.
    if (row1 < 0 || row2 < 0 ||
        row1 >= matrix.getSize() || row2 >= matrix.getSize()) {
        return matrix;
    }

    // Exchange the values in the selected rows.
    for (int j = 0; j < matrix.getSize(); j++) {
        int temp = matrix.get(row1, j);
        matrix.set(row1, j, matrix.get(row2, j));
        matrix.set(row2, j, temp);
    }

    return matrix;
}

// Swap two columns without changing the original matrix.
Matrix swapColumns(Matrix matrix, int col1 = 0, int col2 = 1) {

    // Check that both column numbers are valid.
    if (col1 < 0 || col2 < 0 ||
        col1 >= matrix.getSize() || col2 >= matrix.getSize()) {
        return matrix;
    }

    // Exchange the values in the selected columns.
    for (int i = 0; i < matrix.getSize(); i++) {
        int temp = matrix.get(i, col1);
        matrix.set(i, col1, matrix.get(i, col2));
        matrix.set(i, col2, temp);
    }

    return matrix;
}

//update one matrix element without changing the original.
Matrix UpdateElement(Matrix matrix, int row = 0, int col = 0, int value = 100){
    // Check if that row and col are valid
    if (row<0 || col<0 ||
        row >= matrix.getSize() || col >= matrix.getSize()){
        return matrix;
    }

    // Change the value in the copied matrix.
    matrix.set(row, col, value);
    return matrix;
}

int main() {
    string filename;

    // Ask the user which input file to open.
    cout << "Enter input filename: ";
    cin >> filename;
    cout << endl;

    ifstream file(filename);

    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Read the size and create both matrices.
    int n;
    if (!(file >> n) || n <= 0) {
        cout << "Invalid matrix size." << endl;
        return 1;
    }

    Matrix A(n);
    Matrix B(n);

    if (!A.readMatrix(file) || !B.readMatrix(file)) {
        cout << "Error reading matrix values." << endl;
        return 1;
    }

    // Display both matrices.
    cout << "Matrix A:" << endl;
    A.display();

    cout << endl << "Matrix B:" << endl;
    B.display();
    //Add the two matrices and display the result.
    Matrix sum = A + B;
    cout << endl << "A + B:" << endl;
    sum.display();
    // Multiply the two matrices and display the result.
    Matrix product = A * B;

    cout << endl << "A * B:" << endl;
    product.display();
    // display the diagonal sum of matrix A.
    cout<<endl<<"Diagonal sums for Matrix A:"<< endl;
    cout<<"Main diagonal sum: "<<A.mainDiagonalSum()<<endl;
    cout << "Secondary diagonal sum: " << A.secondaryDiagonalSum() << endl;
        // Swap rows 0 and 2 and display the result.
    Matrix swappedRows = swapRows(A, 0, 2);

    cout << endl << "Problem 5 - Rows 0 and 2 swapped:" << endl;
    swappedRows.display();
    // Swap columns 0 and 2 and display the result.
    Matrix swappedColumns = swapColumns(A, 0, 2);

    cout << endl << "Problem 6 - Columns 0 and 2 swapped:" << endl;
    swappedColumns.display();
    //update row 1, col 2 to 99 and display the results
    Matrix updatedMatrix = UpdateElement(A, 1, 2, 99);
    
   cout << endl << "Problem 7 - Updated matrix:" << endl;
   updatedMatrix.display();
    return 0;
}
