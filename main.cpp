/*
 * Universidade Federal da Grande Dourados - UFGD.
 * Faculdade de Ci�ncias Exatas e Tecnologia - FACET.
 * Bacharelado em Engenharia de Computa��o.
 *
 * Disciplina: Laborat�rio de Computa��o Gr�fica - LCG.
 * Professor: Adailton Jos� Alves da Cruz.
 * Per�odo: semestre 2022.1 || ocorr�ncia no 2� semestre do ano de 2022.
 *
 * Programa: main.cpp
 * Desenvolvido por: Jo�o Vitor Nascimento De Souza.
 *
 * Objetivo: Desenhar um Bra�o Rob� 2D:
 * - Primitivas (quadrado e c�rculo).
 * - Transforma��es geom�tricas e de coordenadas.
 * Refer�ncia: Autoria pr�pria.
 */

// Bibliotecas utilizadas.
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include "cabecalho.h"

/*
 * Fun��o principal: respons�vel pela execu��o do programa do in�cio ao fim.
 * Entrada: argumentos passados pelos prompt de comando.
 * Sa�da:
 * - EXIT_SUCESS: finalizado corretamente.
 * - Outros valors: ocorr�ncia de erros na execu��o.
 */
int main(int argc, char *argv[])
{
    inicializa();                                // Inicializa vari�veis.
    glutInit(&argc, argv);                       // Inicicializa com os argumentos passados no prompt de comando.
    glutInitWindowSize(width, height);           // Define o tamanho da janela em pixels.
    glutInitWindowPosition(300, 200);            // Define a posi��o do canto superior esquerda da janela.
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Descreve as configura��es da janela (cores suportadas e suas caracter�sticas).
    glutCreateWindow("Braco Robo 2D");           // Cria a janela e inseri um t�tulo.

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Seleciona a cor de fundo para limpeza da tela (R, G, B, A).

    /*
     * Rotinas callback:
     *  Se ocorrer um evento de sistema devido a intera��o com a janela criada
     *  aciona uma dessas rotinas, executando suas fun��es internas.
     */
    glutReshapeFunc(resize);      // Executa o procedimento resize.
    glutDisplayFunc(display);     // Executa o procedimento display.
    glutKeyboardFunc(key);        // Executa o procedimento key.
    glutSpecialFunc(keyEspecial); // Executa o procedimento keyEspecial.

    glutMainLoop(); // Mant�m o programa executando em loop, aguardando a ocorr�ncia de novos eventos com a janela.

    return EXIT_SUCCESS;
}

/* Rotinas callback. */

/*
 * Fun��o respons�vel por adaptar a janela de visualiza��o (Viewport) e os elementos contidos na janela (Proje��o),
 * caso ocorra um evento de redimensionamento de janela.
 * Entrada:
 *  - w: nova largura.
 *  - h: nova altura.
 */
static void resize(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, width, height); // Porta de visualiza��o, onde ser� feitos os desenhos dos elementos.
    glMatrixMode(GL_PROJECTION);     // Inicializa os valores de visualiza��o.
    glLoadIdentity();                // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    // Se ocorrer de altura ser 0, altera � pelo menos 1.
    if (height == 0)
        height = 1;

    // Difine o limites para as coordenadas da janela (RANGE em 2D).
    if (width <= height)
        gluOrtho2D(-win, win, -win * height / width, win * height / width);
    else
        gluOrtho2D(-win * width / height, win * width / height, -win, win);
}

/*
 * Procedimento respons�vel por executar instru��es caso ocorra o pressionamento de teclas na janela exibida.
 * Entrada: uma tecla digitada.
 * - "ESC": fecha o programa.
 * - "q" e "e": rotaciona a Jun��o 1.
 * - "a" e "d": rotaciona a Jun��o 2.
 * - "y" e "i": rotaciona a Jun��o 3.
 * - "h" e "k": rotaciona a Jun��o 4.
 * - "o": volta o programa como original.
 * Sa�da: Executa uma instru��o.
 */
static void key(unsigned char letra, int x, int y)
{
    switch (letra)
    {
    case 27: // Fecha a janela.
        exit(0);
        break;
    /* Rotacionar a junta 1. */
    case 'q':
    case 'Q':
        rotaciona[0] += 6;
        break;
    case 'e':
    case 'E':
        rotaciona[0] -= 6;
        break;
    /* Rotacionar a junta 2. */
    case 'a':
    case 'A':
        rotaciona[1] += 6;
        break;
    case 'd':
    case 'D':
        rotaciona[1] -= 6;
        break;
    /* Rotacionar a junta 3. */
    case 'y':
    case 'Y':
        rotaciona[2] += 6;
        break;
    case 'i':
    case 'I':
        rotaciona[2] -= 6;
        break;
    /* Rotacionar a junta 4. */
    case 'h':
    case 'H':
        rotaciona[3] += 6;
        break;
    case 'k':
    case 'K':
        rotaciona[3] -= 6;
        break;
    case 'o':
    case 'O':
        rotaciona[0] = 90;
        rotaciona[1] = -90;
        rotaciona[2] = 45;
        rotaciona[3] = 0;
        translada[0] = -70;
        translada[1] = -50;
        break;
    default:
        break;
    }

    glutPostRedisplay(); // Atualiza o display a cada evento do teclado.
}

/*
 * Procedimento respons�vel por executar instru��es caso ocorra o pressionamento de teclas ESPECIAIS na janela exibida.
 * Entrada: uma tecla digitada especial do teclado.
 * - Seta LEFT: translada para esquerda.
 * - Seta RIGHT: translada para direita.
 * - Seta UP: transalada para cima.
 * - Seta Down: translada para baixo.
 * Sa�da: Executa uma instru��o.
 */
static void keyEspecial(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
    { // Translada para esquerda.
        translada[0] -= 5;
    }
    if (key == GLUT_KEY_RIGHT)
    { // Translada para direita.
        translada[0] += 5;
    }
    if (key == GLUT_KEY_UP)
    { // Translada para cima.
        translada[1] += 5;
    }
    if (key == GLUT_KEY_DOWN)
    { // Translada para baixo.
        translada[1] -= 5;
    }

    glutPostRedisplay();
}

/*
 * Procedimento respons�vel por atualizar o display da janela.
 *  -> Mostra todos os desenhos.
 */
static void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cores atual da janela.

    glMatrixMode(GL_MODELVIEW); // Matriz corrente, contendo todas as transforma��es geom�tricas em um determinado momento.
    glLoadIdentity();           // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    /* Utiliza transforma��es de COORDENADAS. */

    /* draw Base. */
    glTranslatef(translada[0], translada[1], 0); // Permite transaladar todos os objetos do desenho.
    glScalef(3, 1, 1);                           // Escala para desenhar os membros.
    Quadrado();

    /* draw Membro 1. */
    glTranslatef(10, 7, 0);           // 10 - 3 = 7
    glScalef(0.33, 1, 1);             // Escala volta ao valor padr�o.
    glRotatef(rotaciona[0], 0, 0, 1); // Rotaciona o Membro 1 e a Junta 1.
    glScalef(3, 1, 1);
    Quadrado();

    /* draw Junta 1. */
    glScalef(0.33, 1, 1); // Escala volta ao valor padr�o.
    Circulo(11);          // Desenha um c�culo de raio 11.

    /* draw Membro 2. */
    glTranslatef(57, 0, 0);           // 60 - 3 = 57.
    glRotatef(rotaciona[1], 0, 0, 1); // Rotaciona o Membro 2 e a junta 2.
    glScalef(3, 1, 1);                // Escala para desenhar os membros.
    Quadrado();

    /* draw Junta 2. */
    glScalef(0.33, 1, 1); // Escala volta a ser o valor padr�o.
    Circulo(11);          // Desenha um c�culo de raio 11.

    /* draw Membro 3. */
    glTranslatef(57, 0, 0);           // 60 - 3 igual os outros.
    glRotatef(rotaciona[2], 0, 0, 1); // Rotaciona a o Membro 3 e a junta 3.
    glScalef(3, 1, 1);                // Escala para desenhar os membros.
    Quadrado();

    /* draw Junta 3. */
    glScalef(0.33, 1, 1); // Escala volta a ser o valor padr�o.
    Circulo(10);          // Desenha um c�culo de raio 10.

    /* draw palma. */
    glTranslatef(57, 0, 0);           // 60 - 3 igual os outros.
    glRotatef(rotaciona[3], 0, 0, 1); // Rotaciona a Palma e os dedos.
    glScalef(0.75, 2, 1);             // Escala para criar a palma.
    Quadrado();

    /* draw Junta 4. */
    glScalef(1.33, 0.5, 1); // Escala volta a ser o valor padr�o.
    Circulo(10);            // Desenha um c�culo de raio 10.

    // Salva a posi��o atual dos eixos, para voltar a essa configura��o posteriormente.
    glPushMatrix();

    // A palma foi reduzida em x de 1 para 0.75, logo seu tamanho em x foi para 20*0.75 = 15
    // A palma foi aumentada em y de 1 para 2, logo seu tamanho em y foi para 20*2 = 40

    /* draw dedo esquerdo. */
    glTranslatef(15, 15, 0);
    glScalef(1, 0.5, 1);
    Quadrado();

    // Carrega a matriz armazenada na mem�ria na matriz corrente.
    glPopMatrix();

    /* draw dedo direito. */
    glTranslatef(15, -15, 0);
    glScalef(1, 0.5, 1);
    Quadrado();

    // PontosExtremos();
    // Eixos();

    glFlush(); // Faz os comandos n�o executados serem executados.
}

/* Primitiva. */

/*
 * Procedimento para desenhar um quadrado no centro dos eixos de coordendas com lado = 20.
 */
void Quadrado()
{
    glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex2f(0, -10);
    glColor3f(1, 1, 0);
    glVertex2f(0, 10);
    glColor3f(0, 1, 1);
    glVertex2f(20, 10);
    glColor3f(0, 0, 1);
    glVertex2f(20, -10);
    glEnd();
}

/*
 * Desenha um c�rculo cinza com borda na cor vermelho.
 * - Desenha o c�rculo externo primeiro com valor de raio = raio.
 * - Desenha o c�rculo interno por �ltimo com valor de radio reduzido.
 */
void Circulo(float raio)
{
    int i, pts = 60;
    float radianos, angulo = 0, aumento = 360 / pts;

    // C�rculo externo.
    glColor3f(1, 0, 0); // Cor Vermelho.
    glBegin(GL_POLYGON);
    for (i = 0; i < pts; i++)
    {
        radianos = angulo * (PI / 180);
        glVertex2f(raio * sin(radianos), raio * cos(radianos));
        angulo -= aumento;
    }
    glEnd();

    // C�rculo interno.
    angulo = 0;
    raio = raio * 0.85;       // Reduz o tamanho do raio em 15%.
    glColor3f(0.3, 0.3, 0.3); // Cor Cinza escuro.
    glBegin(GL_POLYGON);
    for (i = 0; i < pts; i++)
    {
        radianos = angulo * (PI / 180);
        glVertex2f(raio * sin(radianos), raio * cos(radianos));
        angulo -= aumento;
    }
    glEnd();
}

/* Outras rotinas. */

/*
 * Inicializa��o das vari�veis globais.
 */
void inicializa()
{
    width = 800;
    height = 500;
    rotaciona[0] = 90;
    rotaciona[1] = -90;
    rotaciona[2] = 45;
    rotaciona[3] = 0;
    translada[0] = -70;
    translada[1] = -50;
}

/*
 * Desenha o eixo de coordenadas (x, y).
 */
void Eixos()
{
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1); // Cor Branco.
    // eixo x.
    glVertex2f(-win, 0);
    glVertex2f(win, 0);

    glColor3f(1, 1, 0); // Cor Amarelo.
    // eixo y.
    glVertex2f(0, -win);
    glVertex2f(0, win);
    glEnd();
}

/*
 * Mostra a posi��o dos extremos para o eixo x e para o eixo y.
 */
void PontosExtremos()
{
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 1); // Cor Azul escuro.
    glVertex2f(-win, 0);
    glColor3f(0, 1, 1); // Cor Azul claro.
    glVertex2f(win, 0);
    glColor3f(1, 0, 0); // Cor Vermelho.
    glVertex2f(0, -win);
    glColor3f(1, 0.5, 0); // Cor laranja.
    glVertex2f(0, win);
    glEnd();
}
