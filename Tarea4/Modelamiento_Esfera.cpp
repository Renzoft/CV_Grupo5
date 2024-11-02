#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.141516

void esferaAlambre(int slices, int stacks);
void Key(unsigned char tecla, int x, int y);
void display(void);
void inicializaVista(void);
void reshape(int width, int height);
void inicializaVentana(int argc, char **argv);
void iniciaOpenGL(int argc, char **argv);

/*-------------------------------------------------------------------------- 
Dibuja una esfera usando líneas de alambre.
slices: el número de divisiones a lo largo de la longitud (meridianos).
stacks: el número de divisiones a lo largo de la latitud (paralelos).
--------------------------------------------------------------------------*/
void esferaAlambre(int slices, int stacks)
{
	float phi, theta;
	float dPhi = M_PI / stacks;
	float dTheta = 2.0f * M_PI / slices;
	
	float x, y, z;
	
	glColor3f(0.0f, 0.0f, 1.0f);  // Esfera azul
	glBegin(GL_LINE_LOOP);        // Dibujar usando líneas de alambre
	
	for (int i = 0; i < stacks; i++)
	{
		phi = i * dPhi - M_PI / 2;            // Ángulo de la latitud actual
		float phi_next = (i + 1) * dPhi - M_PI / 2; // Ángulo de la siguiente latitud
		
		for (int j = 0; j < slices; j++)
		{
			theta = j * dTheta;              // Ángulo del meridiano actual
			
			// Primer vértice del segmento
			x = cos(phi) * cos(theta);
			y = sin(phi);
			z = cos(phi) * sin(theta);
			glVertex3f(x, y, z);
			
			// Segundo vértice del segmento
			x = cos(phi_next) * cos(theta);
			y = sin(phi_next);
			z = cos(phi_next) * sin(theta);
			glVertex3f(x, y, z);
		}
	}
	
	glEnd(); // Termina el dibujado de las líneas
}

/*-------------------------------------------------------------------------- 
Borra la ventana y establece el color de dibujo y el ancho de las líneas.
--------------------------------------------------------------------------*/
void display(void) 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia el buffer de color y profundidad
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f); // Alejar la cámara más (antes era -2.0f)
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f); // Rotar la esfera para mejor visualización
	esferaAlambre(30, 30); // Esfera en alambre con 30 divisiones en latitud y longitud
	glFlush();
	glutSwapBuffers(); // Usar doble buffer para evitar parpadeos
}

/*-------------------------------------------------------------------------- 
Especifica las características de la vista (perspectiva).
--------------------------------------------------------------------------*/
void inicializaVista(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 10.0f); // Proyección en perspectiva con campo de visión de 45 grados
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height) 
{
	glViewport(0, 0, width, height);
	inicializaVista();
}

void inicializaVentana(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Activar doble buffer y profundidad
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 30);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST); // Habilitar el test de profundidad para representar correctamente la esfera
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
