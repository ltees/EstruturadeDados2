#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct
{
    float X;
    float Y;
} Ponto;


float CalculoDeterminante(Ponto A, Ponto B);
float AreaTriangulo(Ponto A, Ponto B, Ponto C);
float AreaPoligono(int n, Ponto *vertices);

int main()
{

    FILE *arquivo;
    int quantidadeVertices;

    arquivo = fopen("poligono.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    fscanf(arquivo, "%d", &quantidadeVertices);

    if (quantidadeVertices == 0)
    {
        printf("Area do Poligono: %f", 0.0f);
        fclose(arquivo);
        return 0;
    }

    Ponto *vertices = malloc(sizeof(Ponto) * quantidadeVertices);

    Ponto *iterador = vertices;

    while (!feof(arquivo) && &vertices[quantidadeVertices - 1] >= iterador)
    {
        
        fscanf(arquivo, "%f", &iterador->X);
        fscanf(arquivo, "%f", &iterador->Y);
        iterador++;
    }

    fclose(arquivo);

    printf("Area do Poligono: %f\n", AreaPoligono(quantidadeVertices, vertices));

    free(vertices);

    return 0;
}

float CalculoDeterminante(Ponto A, Ponto B)
{
    return (A.X * B.Y) - (A.Y * B.X);
}


float AreaPoligono(int n, Ponto *vertices)
{
    float area = 0;

    for (int i = 0; i < n - 1; i++)
    {
        area += CalculoDeterminante(vertices[i], vertices[i + 1]);
    }

    area += CalculoDeterminante(vertices[n - 1], vertices[0]);
    
    return fabs(0.5 * area);
}

float AreaTriangulo(Ponto A, Ponto B, Ponto C)
{
    return fabs(0.5 * ((A.X * B.Y) - (A.Y * B.X) + (B.X * C.Y) - (C.X * B.Y) + (C.X * A.Y) - (C.Y * A.X)));
}