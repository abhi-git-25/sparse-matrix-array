#include <iostream>
using namespace std;

struct Element {
    int row;
    int col;
    int value;
};

class SparseMatrix {
private:
    int rows, cols, numNonZero;
    Element* elements;

public:
    SparseMatrix(int r, int c, int n) : rows(r), cols(c), numNonZero(n) {
        elements = new Element[numNonZero];
    }

    ~SparseMatrix() {
        delete[] elements;
    }

    void read() {
        cout << "Enter non-zero elements (row col value):\n";
        for (int i = 0; i < numNonZero; ++i) {
            cin >> elements[i].row >> elements[i].col >> elements[i].value;
        }
    }

    void display() {
        int k = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (k < numNonZero && elements[k].row == i && elements[k].col == j) {
                    cout << elements[k].value << " ";
                    ++k;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    SparseMatrix add(SparseMatrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for addition.");
        }

        SparseMatrix result(rows, cols, numNonZero + other.numNonZero);
        int i = 0, j = 0, k = 0;

        while (i < numNonZero && j < other.numNonZero) {
            if (elements[i].row < other.elements[j].row ||
               (elements[i].row == other.elements[j].row && elements[i].col < other.elements[j].col)) {
                result.elements[k++] = elements[i++];
            } else if (elements[i].row > other.elements[j].row ||
                      (elements[i].row == other.elements[j].row && elements[i].col > other.elements[j].col)) {
                result.elements[k++] = other.elements[j++];
            } else {
                Element e;
                e.row = elements[i].row;
                e.col = elements[i].col;
                e.value = elements[i].value + other.elements[j].value;
                if (e.value != 0) {
                    result.elements[k++] = e;
                }
                ++i;
                ++j;
            }
        }

        while (i < numNonZero) result.elements[k++] = elements[i++];
        while (j < other.numNonZero) result.elements[k++] = other.elements[j++];

        result.numNonZero = k;
        return result;
    }
};

int main() {
    int rows = 4, cols = 5, numNonZero1 = 4, numNonZero2 = 3;

    SparseMatrix mat1(rows, cols, numNonZero1);
    SparseMatrix mat2(rows, cols, numNonZero2);

    cout << "Matrix 1:\n";
    mat1.read();
    cout << "Matrix 2:\n";
    mat2.read();

    cout << "Matrix 1:\n";
    mat1.display();

    cout << "Matrix 2:\n";
    mat2.display();

    SparseMatrix sum = mat1.add(mat2);
    cout << "Sum Matrix:\n";
    sum.display();

    return 0;
}
