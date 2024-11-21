#include <GL/glut.h>
#include <stdio.h>

// Coordenadas de los puntos en el espacio 3D
int x1, y1, z1, x2, y2, z2;

// Función que ajusta el área visible en 3D
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);  // Configura una vista ortogonal 3D
	glMatrixMode(GL_MODELVIEW);
}

// Función que dibuja un punto en 3D
void write_pixel(int x, int y, int z) {
	glBegin(GL_POINTS);
	glVertex3i(x, y, z);  // Dibuja un punto en las coordenadas (x, y, z)
	glEnd();
}

// Función que implementa el trazado de una línea en 3D
void line3D(int x1, int y1, int z1, int x2, int y2, int z2) {
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dz = abs(z2 - z1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int sz = (z1 < z2) ? 1 : -1;
	int err1 = dx - dy;
	int err2 = dz - dy;
	
	while (x1 != x2 || y1 != y2 || z1 != z2) {
		write_pixel(x1, y1, z1);  // Dibuja el punto en 3D
		int e2 = err1 * 2;
		int e3 = err2 * 2;
		if (e2 > -dy) {
			err1 -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err1 += dx;
			y1 += sy;
		}
		if (e3 > -dz) {
			err2 -= dz;
			z1 += sz;
		}
		if (e3 < dz) {
			err2 += dz;
		}
	}
}

// Función para limpiar la pantalla y dibujar la línea en 3D
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);  // Línea azul
	glLoadIdentity();
	line3D(x1, y1, z1, x2, y2, z2);  // Llama a la función que dibuja la línea en 3D
	glFlush();
}

// Función de inicialización para configurar el color de fondo
void init() {
	glClearColor(1, 1, 1, 1);  // Fondo blanco
}

// Función principal que solicita los puntos 3D y gestiona OpenGL
int main(int argc, char **argv) {
	// Solicita al usuario las coordenadas de los dos puntos en el espacio 3D
	printf("Ingrese las coordenadas de los dos puntos en 3D (x1, y1, z1, x2, y2, z2):\n");
	scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Linea en el Espacio 3D");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
