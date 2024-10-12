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

void write_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
}

void midPointLine(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1); // Valor absoluto de la diferencia en x
	int dy = abs(y2 - y1); // Valor absoluto de la diferencia en y
	int sx = (x1 < x2) ? 1 : -1; // Dirección en x (1 si va a la derecha, -1 si va a la izquierda)
	int sy = (y1 < y2) ? 1 : -1; // Dirección en y (1 si sube, -1 si baja)
	
	int err = dx - dy;  // Error inicial
	
	while (x1 != x2 || y1 != y2)
	{
		write_pixel(x1, y1); // Dibuja el pixel en la nueva coordenada
		
		int err2 = 2 * err;
		
		// Ajusta el error y mueve los puntos según la dirección
		if (err2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (err2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
	write_pixel(x2, y2);  // Dibuja el último pixel
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0); // Color rojo para la línea
	glLoadIdentity();
	midPointLine(x1, y1, x2, y2);  // Dibuja la línea con el algoritmo de punto medio
	glFlush();
}

void init()
{
	glClearColor(0, 0, 0, 0); // Fondo negro
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
	glutInitWindowSize(200, 200);
	glutCreateWindow("Midpoint Line Algorithm - Any Octant");
	
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop(); // Inicia el loop de eventos
	return 0;
}
