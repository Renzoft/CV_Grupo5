#include <GL/glut.h>
#include <stdio.h>

float a, b, c;
// Rango para el eje x
float xmin, xmax;

// Funci�n que ajusta el �rea visible y las coordenadas del sistema gr�fico
void reshape(int width, int height) {
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);     
	glLoadIdentity();                
	glOrtho(xmin - 10, xmax + 10, -100, 100, -1, 1);
	glMatrixMode(GL_MODELVIEW);      
}

// Funci�n que dibuja un pixel en las coordenadas (x, y)
void write_pixel(int x, int y) {
	glBegin(GL_POINTS);  
	glVertex2i(x, y);    
	glEnd();             
}

// Funci�n que recorre el rango de x y calcula los puntos de la par�bola
void draw_parabola() {
	float x, y;
	for (x = xmin; x <= xmax; x += 0.1) {
		y = a * x * x + b * x + c;   // Ecuaci�n de la par�bola y = ax^2 + bx + c
		write_pixel((int)x, (int)y); 
	}
}

// Funci�n que limpia la pantalla y dibuja la par�bola
void display() {
	glClear(GL_COLOR_BUFFER_BIT);  
	glColor3f(0, 0, 1); // Par�bola azul      
	glLoadIdentity();              
	draw_parabola();                
	glFlush();                      
}

// Funci�n de inicializaci�n para configurar el color de fondo
void init() {
	glClearColor(1, 1, 1, 1); // Fondo blanco  
}

// Funci�n principal que gestiona la entrada del usuario y la inicializaci�n de OpenGL
int main(int argc, char **argv) {
	printf("Ingrese los coeficientes a, b, c de la par�bola (y = ax^2 + bx + c):\n");
	scanf("%f %f %f", &a, &b, &c);
	printf("Ingrese el rango m�nimo y m�ximo de x (xmin xmax):\n");
	scanf("%f %f", &xmin, &xmax);
	
	glutInit(&argc, argv);                      
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(500, 500);               
	glutInitWindowPosition(100, 100);           
	glutCreateWindow("Par�bola en OpenGL");     
	init();                                     
	glutDisplayFunc(display);                   
	glutReshapeFunc(reshape);                   
	glutMainLoop();                             
	return 0;
}
