#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

// Constantes.
#define win 100    // Constante que armazena o valor de coordenadas para orientação x e y.
#define PI 3.14159 // Constante PI.

// Variáveis globais.
GLfloat width, height;              // Armazena o tamanho da janela, para eventos de redimensionar a janela.
GLfloat rotaciona[4], translada[2]; // Variáveis para animar o objeto. (Rotacionar e transaladar)

/* Protótipos de Funções/Procedimentos. */
// Rotinas callbacks.
static void resize(int, int);
static void display();
static void key(unsigned char, int, int);
static void keyEspecial(int, int, int);

// Rotinas diversos.
void inicializa();
void Eixos();
void PontosExtremos();

// Primitivas.
void Quadrado();
void Circulo(float);

#endif // CABECALHO_H_INCLUDED
