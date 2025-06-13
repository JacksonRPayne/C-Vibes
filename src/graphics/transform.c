typedef struct Transform{
    float x; // fuck vectors
    float y;
    float w;
    float h;
    float r;
}Transform;

// Creates a matrix to be passed to shader
mat4 transformToMat4(Transform transform){
    mat4 mat = mat4Identity();
    mat4Multiply(&mat, mat4Scale(transform.w, transform.h));
    mat4Multiply(&mat, mat4Translation(transform.x, transform.y));
    mat4Multiply(&mat, mat4Rotation(transform.r));

    return mat;
}