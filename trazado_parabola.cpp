#include <GL/glut.h>
#include <stdio.h>

float a, b, c;
// Rango para el eje x
float xmin, xmax;

// Función que ajusta el área visible y las coordenadas del sistema gráfico
void reshape(int width, int height) {
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);     
	glLoadIdentity();                
	glOrtho(xmin - 10, xmax + 10, -100, 100, -1, 1);
	glMatrixMode(GL_MODELVIEW);      
}

// Función que dibuja un pixel en las coordenadas (x, y)
void write_pixel(int x, int y) {
	glBegin(GL_POINTS);  
	glVertex2i(x, y);    
	glEnd();             
}

// Función que recorre el rango de x y calcula los puntos de la parábola
void draw_parabola() {
	float x, y;
	for (x = xmin; x <= xmax; x += 0.1) {
		y = a * x * x + b * x + c;   // Ecuación de la parábola y = ax^2 + bx + c
		write_pixel((int)x, (int)y); 
	}
}

// Función que limpia la pantalla y dibuja la parábola
void display() {
	glClear(GL_COLOR_BUFFER_BIT);  
	glColor3f(0, 0, 1); // Parábola azul      
	glLoadIdentity();              
	draw_parabola();                
	glFlush();                      
}

// Función de inicialización para configurar el color de fondo
void init() {
	glClearColor(1, 1, 1, 1); // Fondo blanco  
}

// Función principal que gestiona la entrada del usuario y la inicialización de OpenGL
int main(int argc, char **argv) {
	printf("Ingrese los coeficientes a, b, c de la parábola (y = ax^2 + bx + c):\n");
	scanf("%f %f %f", &a, &b, &c);
	printf("Ingrese el rango mínimo y máximo de x (xmin xmax):\n");
	scanf("%f %f", &xmin, &xmax);
	
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
