#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h> // Para abs()

int x1, y1, x2, y2;

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

void pintar_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
}

void lineaPuntoMedio(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	
	while (x1 != x2 || y1 != y2)
	{
		pintar_pixel(x1, y1);
		
		int err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
	pintar_pixel(x2, y2);
}

void pintarEjes()
{
	glColor3f(1, 1, 1); // Color blanco para los ejes
	glBegin(GL_LINES);
	
	// Eje X
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	
	// Eje Y
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	pintarEjes(); // Dibuja los ejes
	
	glColor3f(1, 0, 0); // Color rojo para la línea
	lineaPuntoMedio(x1, y1, x2, y2);
	
	glFlush();
}

void init()
{
	glClearColor(0, 0, 0, 0); // Fondo negro
	glPointSize(5.0);         // Tamaño de los puntos (línea más gruesa)
}

int main(int argc, char **argv)
{
	// Solicita al usuario que ingrese las coordenadas
	printf("Ingresar x1, y1, x2, y2 \n");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	
	// Inicialización de GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(400, 400); // Ventana más grande para mejor visualización
	glutCreateWindow("Midpoint Line Algorithm - Any Octant");
	
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop(); // Inicia el loop de eventos
	return 0;
}

