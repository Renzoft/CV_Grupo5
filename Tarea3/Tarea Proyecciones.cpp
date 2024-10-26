#include <GL/glut.h> 
GLfloat anguloCuboX = 0.0f;  
GLfloat anguloCuboY = 0.0f; 
GLfloat anguloEsfera = 0.0f; 
GLint ancho, alto; 
int hazPerspectiva = 1; 
GLfloat planoCerca = 2.0f;
GLfloat planoLejos = 5.0f;

void reshape(int width, int height) 
{ 
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	if(hazPerspectiva) 
		gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, planoCerca, planoLejos); 
	else 
		glOrtho(-4, 4, -4, 4, planoCerca, planoLejos); 
	
	glMatrixMode(GL_MODELVIEW); 
	
	ancho = width; 
	alto = height; 
} 

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glLoadIdentity(); 
	
	glTranslatef(0.0f, 0.0f, -5.0f); 
	
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f); 
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f);
	glutWireTeapot(1.5f);
	
	glFlush(); 
	glutSwapBuffers(); 
} 

void init() 
{ 
	glClearColor(0,0,0,0); 
	glEnable(GL_DEPTH_TEST); 
	ancho = 400; 
	alto = 400; 
} 

void idle() 
{ 
	display(); 
} 

void keyboard(unsigned char key, int x, int y) 
{ 
	switch(key) 
	{
	case 'p': 
	case 'P': 
		hazPerspectiva=1; 
		reshape(ancho,alto); 
		break; 
		
	case 'o': 
	case 'O': 
		hazPerspectiva=0; 
		reshape(ancho,alto); 
		break; 
		
	case 'A':
		planoCerca += 0.1f;  // Incrementa el plano de corte anterior
		if (planoCerca >= planoLejos) 
			planoCerca = planoLejos - 0.1f;
		reshape(ancho, alto);
		break;
	case 'a':
		planoLejos += 0.3f;  // Incrementa el plano de corte posterior
		reshape(ancho, alto);
		break;
		
	case 'b': //Adicional retroceso
		planoLejos -= 0.3f;  // Disminuye el plano de corte posterior
		if (planoLejos <= planoCerca + 0.1f)
			planoLejos = planoCerca + 0.1f;
		reshape(ancho, alto);
		break;
	case 'B': //Adicional retroceso
		planoCerca -= 0.1f;  // Disminuye el plano de corte anterior
		if (planoCerca < 0.1f) 
			planoCerca = 0.1f;
		reshape(ancho, alto);
		break;
	case 27:   // escape 
		exit(0); 
		break; 
	} 
} 

int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(ancho, alto); 
	glutCreateWindow("Cubo 1"); 
	init(); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutIdleFunc(idle); 
	glutKeyboardFunc(keyboard); 
	glutMainLoop(); 
	return 0; 
}
