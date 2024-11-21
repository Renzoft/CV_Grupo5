#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.141516

float dameX(float R, int N, int n);
float dameZ(float R, int N, int n);
void anillo(float R, float y, int N);
float fCono(float y);
void conoAlambre(int N);
void formaAlambre(float H, int N, float(*f)(float y));
void Key(unsigned char tecla, int x, int y);
void specialKey(int key, int x, int y);
void display(void);
void inicializaVista(void);
void reshape(int width, int height);
void inicializaVentana(int argc, char **argv);
void iniciaOpenGL(int argc, char **argv);

float anguloRotacionX = 15.0f; // �ngulo de rotaci�n alrededor del eje X
float anguloRotacionY = 0.0f;  // �ngulo de rotaci�n alrededor del eje Y

/*-------------------------------------------------------------------------- 
Devuelve el valor de x del punto que gira.
R: el radio de giro.
N: el n�mero total de tramos en el anillo.
n: el tramo actual.
--------------------------------------------------------------------------*/
float dameX(float R, int N, int n) 
{
	float x = (float)R * cos(n * (2 * M_PI) / N);
	return x;
}

/*Devuelve el valor de z del punto que gira.*/
	float dameZ(float R, int N, int n) 
{
	float z = (float)R * sin(n * (2 * M_PI) / N);
	return z;
}

/*-------------------------------------------------------------------------- 
Dibuja un anillo.
R: el radio del anillo.
y: la altura a la que se dibuja el anillo.
N: el n�mero de tramos del anillo.
--------------------------------------------------------------------------*/
void anillo(float R, float y, int N) 
{
	int i;
	float x, z;
	
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < N; i++) 
	{
		x = dameX(R, N, i);
		z = dameZ(R, N, i);
		glVertex3f(x, y, z);
	}
	glEnd();
}

/*-------------------------------------------------------------------------- 
Devuelve el radio del cono en funci�n de la altura.
El radio disminuye linealmente desde un valor m�ximo en la base hasta cero en la punta.
y: el valor de la altura.
--------------------------------------------------------------------------*/
float fCono(float y) 
{
	float alturaMax = 100.0f; // Altura del cono
	float radioBase = 50.0f;  // Radio de la base del cono
	return radioBase * (1 - (y + alturaMax / 2) / alturaMax); // Radio disminuye linealmente
}

/*-------------------------------------------------------------------------- 
Dibuja un cono en forma de alambre.
N: el n�mero de anillos y tramos en cada anillo.
--------------------------------------------------------------------------*/
void conoAlambre(int N) 
{
	formaAlambre(100.0f, N, fCono); // La altura del cono es 100.0f
}

/*-------------------------------------------------------------------------- 
Algoritmo de dibujo para una figura de revoluci�n.
H: la altura de la figura.
N: el n�mero de anillos y divisiones en cada anillo.
f(float y): puntero a la funci�n que devuelve el valor de radio en funci�n de y.
--------------------------------------------------------------------------*/
void formaAlambre(float H, int N, float(*f)(float y)) 
{
	int i;
	float y, r;
	
	for (i = 0; i < N; i++) 
	{
		y = i * H / N - (H / 2);
		r = f(y);
		anillo(r, y, N);
	}
}

/*-------------------------------------------------------------------------- 
Borra la ventana y establece el color de dibujo y el ancho de las l�neas.
--------------------------------------------------------------------------*/
void display(void) 
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	glLoadIdentity();
	glPushMatrix();
	
	// Mueve la c�mara m�s lejos para ver el cono completo
	glTranslatef(0.0f, 0.0f, -200.0f);  // Aleja la c�mara a�n m�s
	
	// Aplica las rotaciones interactivas
	glRotatef(anguloRotacionX, 1.0f, 0.0f, 0.0f);  // Rotaci�n sobre el eje X
	glRotatef(anguloRotacionY, 0.0f, 1.0f, 0.0f);  // Rotaci�n sobre el eje Y
	
	conoAlambre(30);  // Dibuja el cono con m�s divisiones
	glPopMatrix();
	glFlush();
}

void inicializaVista(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 500.0f); // 45 grados de campo de visi�n, aspecto 1:1, rango de visi�n de 1.0 a 500 unidades
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*-------------------------------------------------------------------------- 
Esta funci�n se llama al cambiar el tama�o de la ventana.
width, height: ancho y alto de la zona de dibujo.
--------------------------------------------------------------------------*/
void reshape(int width, int height) 
{
	glViewport(0, 0, width, height);
	inicializaVista();
}

/* Maneja las teclas comunes */
void Key(unsigned char tecla, int x, int y) 
{
	if (tecla == 27) { // Tecla ESC para salir
		exit(0);
	}
}

/* Maneja las teclas especiales para la rotaci�n */
void specialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:   // Flecha arriba: rotar hacia arriba
		anguloRotacionX += 5.0f;
		break;
	case GLUT_KEY_DOWN: // Flecha abajo: rotar hacia abajo
		anguloRotacionX -= 5.0f;
		break;
	case GLUT_KEY_LEFT: // Flecha izquierda: rotar hacia la izquierda
		anguloRotacionY -= 5.0f;
		break;
	case GLUT_KEY_RIGHT: // Flecha derecha: rotar hacia la derecha
		anguloRotacionY += 5.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

/*Crea la ventana para dibujar con OpenGL.*/
	void inicializaVentana(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 30);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Key);
	glutSpecialFunc(specialKey);
}

void iniciaOpenGL(int argc, char **argv) 
{
	inicializaVentana(argc, argv);
	inicializaVista();
	glutMainLoop();
}

int main(int argc, char** argv) 
{
	iniciaOpenGL(argc, argv);
	return 1;
}

