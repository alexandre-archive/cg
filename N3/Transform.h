#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif
#include <math.h>

/**
    Representa a classe de transformação de objetos.
**/
class Transform
{
private:
    double matriz[16];
public:
    Transform();
    ~Transform();
    void MakeIdentity();
    double* getDate();
    void dumpMatriz();
    void MakeTranslation(Point point);
    void MakeScale(double sX, double sY, double sZ);
    void MakeZRotation(double radians);
    Transform transformMatrix(Transform t);
    Point GetPoint();
} Transf;

Transform::Transform()
{
    MakeIdentity();
}

Transform::~Transform()
{

}

void Transform::MakeIdentity()
{
    for (int i=0; i<16; ++i)
    {
        matriz[i] = 0.0;
    }

    matriz[0] = matriz[5] = matriz[10] = matriz[15] = 1.0;
}

double* Transform::getDate()
{
    return matriz;
}

//Listar a matriz de transformação
void Transform::dumpMatriz()
{
    cout << "__________________MATRIZ______________________\n";
    cout << "|" <<  matriz[0] << " | " << matriz[1] << " | " << matriz[2] << " | " << matriz[3] << "\n";
    cout << "|"  << matriz[4] << " | " << matriz[5] << " | " << matriz[6] << " | " << matriz[7] << "\n";
    cout << "|"  << matriz[8] << " | " << matriz[9] << " | " << matriz[10] << " | " << matriz[11] << "\n";
    cout << "|" <<  matriz[12] << " | " << matriz[13] << " | " << matriz[14] << " | " << matriz[15] << "\n";
    cout << "_____________________________________________________\n";
    cout << "\n";
}

void Transform::MakeTranslation(Point translationVector)
{
    MakeIdentity();
    matriz[12] = translationVector.x;
    matriz[13] = translationVector.y;
    //verificar, tinha no exemplo em JAVA o eixo Z
    //matriz[14] = translationVector.z;
}

Point Transform::GetPoint()
{
    Point p;
    p.x = matriz[12];
    p.y = matriz[13];
    return p;
}

Transform Transform::transformMatrix(Transform t)
{
    Transform result;

    for (int i=0; i < 16; ++i)
    {
        result.matriz[i] = matriz[i%4] * t.matriz[i/4*4] + matriz[(i%4)+4] * t.matriz[i/4*4+1] + matriz[(i%4)+8] * t.matriz[i/4*4+2] + matriz[(i%4)+12] * t.matriz[i/4*4+3];
    }

    return result;
}

void Transform::MakeScale(double sX, double sY, double sZ)
{
    MakeIdentity();
    matriz[0] = sX;
    matriz[5] = sY;
    matriz[10] = sZ;
}

void Transform::MakeZRotation(double radians)
{
    MakeIdentity();
    matriz[0] =  cos(radians);
    matriz[4] = -sin(radians);
    matriz[1] =  sin(radians);
    matriz[5] =  cos(radians);
}