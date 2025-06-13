#include <stdio.h>
#include <string.h>
#include <math.h>

// Column major mat4
typedef struct mat4{
    float elements[4*4];
}mat4;

// Column major mat4 indexing
int mat4Index(int row, int col){
    return row + 4 * col;
}

// Creates identity matrix
mat4 mat4Identity(){
    mat4 mat;
    // zero out
    memset(mat.elements, 0, 16 * sizeof(float));
    mat.elements[mat4Index(0,0)] = 1;
    mat.elements[mat4Index(1,1)] = 1;
    mat.elements[mat4Index(2,2)] = 1;
    mat.elements[mat4Index(3,3)] = 1;

    return mat;
}

// Creates a scaling matrix
mat4 mat4Scale(float w, float h){
    mat4 mat;
    // zero out
    memset(mat.elements, 0, 16 * sizeof(float));
    mat.elements[mat4Index(0,0)] = w;
    mat.elements[mat4Index(1,1)] = h;
    mat.elements[mat4Index(2,2)] = 1; // Who needs 3 dimensions
    mat.elements[mat4Index(3,3)] = 1;

    return mat;
}

// Creates a translation matrix
mat4 mat4Translation(float x, float y){
    // Start with identity
    mat4 mat = mat4Identity();
    mat.elements[mat4Index(0,3)] = x;
    mat.elements[mat4Index(1,3)] = y;

    return mat;
}

// Z axis rotation
mat4 mat4Rotation(float theta){
    // Start with identity
    mat4 mat = mat4Identity();

    mat.elements[mat4Index(0,0)] = (float) cos(theta);
    mat.elements[mat4Index(0,1)] = (float) -sin(theta);
    mat.elements[mat4Index(1,0)] = (float) sin(theta);
    mat.elements[mat4Index(1,1)] = (float) cos(theta);

    return mat;
}

// Applies a matrix multiplication to mat4 this, multiplying it with mat4 other
// If written down, other would be on the left and this on the right (matmul is right to left)
void mat4Multiply(mat4* this, mat4 other){
    // Stores result
    float product[16];

    for(int col =0; col<4; col++){ // loop through col on right side
        for(int row=0; row<4; row++){ // loop through rows on left side
            float sum = 0.0f;
            for(int e =0; e<4; e++){ // loop through elements of left row / right col
                sum += this->elements[mat4Index(e, col)] * other.elements[mat4Index(row, e)]; // sum element-wise products
            }

            product[mat4Index(row, col)] = sum;
        }
    }

    memcpy(this->elements, product, 16 * sizeof(float));

}

mat4 mat4Ortho(float left, float right, float bottom, float top, float near, float far){

    mat4 mat;
    memset(mat.elements, 0, 16 * sizeof(float));

    // Diagonal
    mat.elements[mat4Index(0,0)] = 2.0f / (right - left);
    mat.elements[mat4Index(1,1)] = 2.0f / (top - bottom);
    mat.elements[mat4Index(2,2)] = -2.0f / (far - near);
    mat.elements[mat4Index(3,3)] = 1;
    
    // Last col
    mat.elements[mat4Index(0,3)] = (right + left) / (left - right); // This is flipped from a lot of diagrams for some reason...
    mat.elements[mat4Index(1,3)] = (top + bottom) / (bottom - top);
    mat.elements[mat4Index(2,3)] = (far + near) / (far - near);

    return mat;
}

void mat4Print(mat4* mat){
    for(int row = 0; row<4; row++){
        for(int col=0; col<4; col++){
            printf("%f ",mat->elements[mat4Index(row, col)]);
        }
        printf("\n");
    }
}

