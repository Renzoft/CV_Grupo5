#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.141516

float anguloRotacion = 0.0f; 

void esferaAlambre(int rebanadas, int pilas);
void teclaPresionada(unsigned char tecla, int x, int y);
void mostrar(void);
void inicializaVista(void);
void redimensionar(int ancho, int alto);
void inicializaVentana(int argc, char **argv);
void iniciaOpenGL(int argc, char **argv);
void actualizarRotacion(int valor);

void esferaAlambre(int rebanadas, int pilas)
{
	float phi, theta;
	float dPhi = M_PI / pilas;
	float dTheta = 2.0f * M_PI / rebanadas;
	
	float x, y, z;
	
	glColor3f(0.0f, 0.0f, 1.0f);  
	glBegin(GL_LINE_LOOP);       
	
	for (int i = 0; i < pilas; i++)
	{
		phi = i * dPhi - M_PI / 2;            
		float phiSiguiente = (i + 1) * dPhi - M_PI / 2; 
		
		for (int j = 0; j < rebanadas; j++)
		{
			theta = j * dTheta;              
			
			x = cos(phi) * cos(theta);
			y = sin(phi);
			z = cos(phi) * sin(theta);
			glVertex3f(x, y, z);
			
			x = cos(phiSiguiente) * cos(theta);
			y = sin(phiSiguiente);
			z = cos(phiSiguiente) * sin(theta);
			glVertex3f(x, y, z);
		}
	}
	
	glEnd(); 
}

void mostrar(void) 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f); 
	glRotatef(anguloRotacion, 1.0f, 1.0f, 0.0f); 
	esferaAlambre(30, 30); 
	glFlush();
	glutSwapBuffers(); 
}

void inicializaVista(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 10.0f); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void redimensionar(int ancho, int alto) 
{
	glViewport(0, 0, ancho, alto);
	inicializaVista();
}

void inicializaVentana(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 30);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(mostrar);
	glutReshapeFunc(redimensionar);
	glEnable(GL_DEPTH_TEST); 
}

void actualizarRotacion(int valor)
{
	anguloRotacion += 1.0f; 
	if (anguloRotacion > 360.0f)
	{
		anguloRotacion -= 360.0f; 
	}
	glutPostRedisplay(); 
	glutTimerFunc(16, actualizarRotacion, 0); 
}

void iniciaOpenGL(int argc, char **argv) 
{
	inicializaVentana(argc, argv);
	inicializaVista();
	glutTimerFunc(16, actualizarRotacion, 0); 
	glutMainLoop();
}

int main(int argc, char** argv) 
{
	iniciaOpenGL(argc, argv);
	return 1;
}

