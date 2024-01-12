// Berke Algül 040230762
// 19.12.2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*** MATRIX STRUCTURE ***/
/* A matrix structure that is suitable for dynamic matrix operations */
typedef struct{
    float **M;  // Pointer for a 2-dimensional (2D) float type array
    int n, m;   // Numbers of rows and columns for the 2D array
} Matrix;

/*** FUNCTION PROTOTYPES ***/
Matrix construct(Matrix x, int n, int m);   // Returns a Matrix variable by allocating memory for n-by-m sized 2D array
Matrix destruct(Matrix x);                  // Returns a Matrix variable by deallocating the memory allocated for the 2D array
Matrix configure(Matrix x);                 // Returns a Matrix variable by initializing its members with the user-specified parameters
void print(Matrix x);                       // Prints the 2D array elements held in a Matrix variable
float determinant(Matrix x);                // Returns the calculated determinant value for a Matrix variable
Matrix cofactor(Matrix x);                  // Returns a Matrix variable that holds the cofactors of the 2D array of a Matrix variable
Matrix transpose(Matrix x);                 // Returns a Matrix variable that holds the transpose of the 2D array of a Matrix variable
Matrix inverse(Matrix x);                   // Returns a Matrix variable that holds the inverse of the 2D array of a Matrix variable
Matrix multiply(Matrix x, Matrix y);        // Returns a Matrix variable that holds the multiplication of 2D array of 2 Matrix variables
Matrix solve(Matrix A, Matrix b);           // Returns the solution in Matrix type for a linear equations system specified by 2 Matrix variables



/*** MAIN FUNCTION ***/
// Define and solve a linear equations system (Ax=b)
int main(){
    Matrix A = configure(A);                                        // Define and configure the coefficient matrix (n-by-n)
    Matrix b = configure(b);                                        // Define and configure the constant (right-hand side) vector (n-by-1)
    Matrix x = solve(A, b);                                         // Solve the system and store the solution in the variable vector (n-by-1)
    getchar();                                                      // Press enter to see the solution
    for(int i=0; i<x.n; i++) printf("x%d = %g\t", i+1, x.M[i][0]);  // Print the solution
    putchar('\n');                                                  // Give a new line after printing the solution
    getchar();                                                      // Press enter to terminate the program
    return 0;
}



/*** FUNCTION IMPLEMENTATIONS ***/


/* Returns a Matrix variable by allocating memory for n-by-m sized 2D array */
Matrix construct(Matrix x, int n, int m){
    x.n = n;
    x.m = m;
    x.M = malloc(n*sizeof(float*)); // allocate row dimension
    for(int i = 0; i < n; i++){ // allocate column dimension for each row
        x.M[i] = malloc(m*sizeof(float*));
    }    
    return x;                                                   // Return the constructed Matrix argument
}


/* Returns a Matrix variable by deallocating the memory allocated for the 2D array */
Matrix destruct(Matrix x){
    for(int i = 0; i < x.n; i++) free(x.M[i]); // free each row
    free(x.M);
    return x;                               // Return the destructed Matrix argument
}


/* Returns a Matrix variable by initializing its members with the user-specified parameters */
Matrix configure(Matrix x){
    printf("Enter the matrix size as numbers of rows and columns (ex: 5 6): ");
    int n, m;
    scanf("%d %d", &n, &m);
    getchar(); // get rid of '\n' putted by scanf :(
    x = construct(x, n, m);

    printf("Enter the matrix elements row by row (ex: 3 4 5):\n");
    for(int i = 0; i < n; i++) {
        char row_str[1000];
        printf("Row %d/%d x %d | ", i+1, n, m);
        fgets(row_str, 1000, stdin); // get row from user
        char* token = strtok(row_str, " "); // tokenize row 
        for(int j = 0; j < m; j++){ // put elements to matrix
            x.M[i][j] = strtof(token, NULL);
            token = strtok(NULL, " ");
        }
    } 

    return x;                                                                   // Return the configured Matrix argument
}


/* Prints the 2D array elements held in a Matrix variable */
void print(Matrix x){
    printf("\n");
    for(int i = 0; i < x.n; i++) {
        for(int j = 0; j < x.m; j++) {
            printf("%f ", x.M[i][j]);
        }
        printf("\n");
    }
}


/* Returns the calculated determinant value for a Matrix variable */
float determinant(Matrix x){
    if(x.n != x.m || x.n <= 0 || x.m <= 0) {
        printf("The matrix is non-square and has no determinant!\n");
        return 0;
    }

    float det = 0;
    int n = x.n;

    // cover edge cases
    if(n == 1) return x.M[0][0];  // |1x1| is the element itself                                                  
    else if(n == 2) return x.M[0][0]*x.M[1][1]-x.M[0][1]*x.M[1][0]; // 2x2 determinant is easy

    for(int i = 0; i < n; i++) {
        // create sub matrix
        Matrix sub = construct(sub, n-1, n-1);
        int sj = 0; // sub matrix col idx
        for(int j = 0; j < n; j++) { 
            if(j == i) continue;
            for(int k = 1; k < n; k++) { // sub matrix column
                sub.M[k-1][sj] = x.M[k][j];
            }  
            sj++;
        }
        det += pow(-1, i) * x.M[0][i] * determinant(sub);
        destruct(sub); // free sub matrix after usage
    }

    return det;                                                             // Return the calculated determinant value
}


/* Returns a Matrix variable that holds the cofactors of the 2D array of a Matrix variable*/
Matrix cofactor(Matrix x){
    int n = x.n;                                                        // Define the matrix size with a single variable by assuming a square matrix
    Matrix cfc = construct(cfc, n, n);                                  // Define and construct a square Matrix variable for the cofactor matrix

    if(x.n != x.m || x.n <= 0 || x.m <= 0) {
        printf("The matrix is non-square and has no cofactor!\n");
        return cfc;
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            Matrix sub = construct(sub, n-1, n-1);
            int si = 0;
            for(int z = 0; z < n; z++) {
                int sj = 0;
                if(z == i) continue;
                for(int w = 0; w < n; w++) {
                    if(w == j) continue;
                    sub.M[si][sj] = x.M[z][w];
                    sj++;
                }
                si++;
            }
            cfc.M[i][j] = pow(-1, i+j) * determinant(sub);
            destruct(sub);
        }

    return cfc;                                                         // Return the Matrix variable that holds the cofactors
}


 /* Returns a Matrix variable that holds the transpose of the 2D array of a Matrix variable */
Matrix transpose(Matrix x){
    Matrix tr = construct(tr, x.m, x.n);
    for(int i = 0; i < tr.n; i++)
        for(int j = 0; j < tr.m; j++)
            tr.M[i][j] = x.M[j][i];
    return tr;                                                                  // Return the transposed Matrix variable
}


/* Returns a Matrix variable that holds the inverse of the 2D array of a Matrix variable */
Matrix inverse(Matrix x){
    int n = x.n;                                                                     // Define the matrix size with a single variable by assuming a square matrix
    float det = determinant(x); 
    Matrix inv = construct(inv, n, n);

    if(det == 0) {
        printf("The matrix is non-square or singular and has no inverse!\n");
        return inv;
    }

    Matrix adjoint = transpose(cofactor(x));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            inv.M[i][j] = adjoint.M[i][j] / det;

    return inv;                                                                         // Return the inverted Matrix variable
}


/* Returns a Matrix variable that holds the multiplication of 2D arrays of 2 Matrix variables */
Matrix multiply(Matrix x, Matrix y){
    Matrix mlt = construct(mlt, x.n, y.m);
    if(x.m != y.n) {
        printf("Sizes of matrices do not match for the matrix multiplication!\n");
        return mlt;
    }

    int vector_size = x.m; // y.n is also fine
    for(int i = 0; i < mlt.n; i++)
        for(int j = 0; j < mlt.m; j++)  
        {
            float dot = 0;
            // calculate dot product of vectors from both matrix
            for(int k = 0; k < vector_size; k++) {
                dot += x.M[i][k] * y.M[k][j];
            }
            mlt.M[i][j] = dot;
        }

    return mlt;                                                                         // Return the Matrix variable that holds the multiplication of matrices
}


/* Returns the solution in Matrix type for a linear equations system specified by 2 Matrix variables */
Matrix solve(Matrix A, Matrix b){
    return multiply(inverse(A), b);
}
