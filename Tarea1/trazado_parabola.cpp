#include <GL/glut.h>
#include <stdio.h>

float a, b, c;      // Coeficientes de la parábola
float xmin, xmax;   // Rango para el eje x
float ymin, ymax;   // Rango dinámico para el eje y

// Ajusta el área visible y las coordenadas del sistema gráfico
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xmin - 10, xmax + 10, ymin - 10, ymax + 10, -1, 1); // Rango ajustado
	glMatrixMode(GL_MODELVIEW);
}

// Dibuja los ejes X y Y
void draw_axes() {
	glColor3f(0, 0, 0); // Color negro para los ejes
	glBegin(GL_LINES);
	// Eje X
	glVertex2f(xmin - 10, 0);
	glVertex2f(xmax + 10, 0);
	// Eje Y
	glVertex2f(0, ymin - 10);
	glVertex2f(0, ymax + 10);
	glEnd();
}

// Dibuja la parábola conectando los puntos con líneas
void draw_parabola() {
	glColor3f(0, 0, 1); // Color azul para la parábola
	glBegin(GL_LINE_STRIP); // Dibujar líneas continuas
	for (float x = xmin; x <= xmax; x += 0.01) {
		float y = a * x * x + b * x + c; // Ecuación de la parábola
		glVertex2f(x, y);               // Agregar el punto al trazado
	}
	glEnd();
}

// Limpia la pantalla y dibuja la escena completa
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	draw_axes();     // Dibujar los ejes
	draw_parabola(); // Dibujar la parábola
	glFlush();
}

// Configura el color de fondo
void init() {
	glClearColor(1, 1, 1, 1); // Fondo blanco
}

// Calcula el rango dinámico para el eje y según la parábola
void calculate_y_range() {
	ymin = ymax = a * xmin * xmin + b * xmin + c; // Inicializar con un valor
	for (float x = xmin; x <= xmax; x += 0.1) {
		float y = a * x * x + b * x + c;
		if (y < ymin) ymin = y;
		if (y > ymax) ymax = y;
	}
}

int main(int argc, char **argv) {
	printf("Ingrese los coeficientes a, b, c de la parábola (y = ax^2 + bx + c):\n");
	scanf("%f %f %f", &a, &b, &c);
	printf("Ingrese el rango mínimo y máximo de x (xmin xmax):\n");
	scanf("%f %f", &xmin, &xmax);
	
	calculate_y_range(); // Calcular el rango para y
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Parábola en OpenGL");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
