#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <cmath>

// Variables para controlar las transformaciones
float translateX = 0.0f, translateY = 0.0f;
float scaleFactor = 1.0f;
float angle = 0.0f;

void reshape_cb(int w, int h) {
    if (w == 0 || h == 0) return;
    glViewport(0, 0, w, h);

    // Configurando la proyecci�n ortogr�fica centrada
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);  // Sistema de coordenadas centrado en la ventana
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Funci�n para dibujar el tri�ngulo centrado en el origen
void drawTriangle() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);

    // V�rtices del tri�ngulo alrededor del origen (centrado)
    glVertex2f(-50, -50); glVertex2f(50, -50);
    glVertex2f(-50, -50); glVertex2f(0, 100);
    glVertex2f(0, 100); glVertex2f(50, -50);

    glEnd();
}

// Funci�n de visualizaci�n
void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Aplicar las transformaciones (traslaci�n, rotaci�n, escalado)
    glTranslatef(translateX, translateY, 0.0f);  // Desplazamiento
    glScalef(scaleFactor, scaleFactor, 1.0f);    // Escalado
    glRotatef(angle, 0.0f, 0.0f, 1.0f);          // Rotaci�n

    glColor3f(1, 1, 0);
    glLineWidth(3);
    drawTriangle();

    glutSwapBuffers();
}

// Funci�n para controlar el teclado
void keyboard_cb(unsigned char key, int x, int y) {
    switch (key) {
        case 'R':  // Rotaci�n positiva
            angle += 5.0f;
            break;
        case 'r':  // Rotaci�n negativa
            angle -= 5.0f;
            break;
        case 'S':  // Escalado hacia arriba
            scaleFactor += 0.1f;
            break;
        case 's':  // Escalado hacia abajo
            if (scaleFactor > 0.1f)  // Evitar escalado negativo
                scaleFactor -= 0.1f;
            break;
        case 27:  // Escape para salir
            exit(0);
            break;
    }
    glutPostRedisplay();  // Redibujar la escena
}

// Funci�n para manejar las teclas especiales (flechas de desplazamiento)
void specialKeys_cb(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            translateY += 10.0f;
            break;
        case GLUT_KEY_DOWN:
            translateY -= 10.0f;
            break;
        case GLUT_KEY_LEFT:
            translateX -= 10.0f;
            break;
        case GLUT_KEY_RIGHT:
            translateX += 10.0f;
            break;
    }
    glutPostRedisplay();  // Redibujar la escena
}

// Inicializaci�n
void initialize() {
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ventana OpenGL");

    // Registrando los callbacks
    glutDisplayFunc(display_cb);
    glutReshapeFunc(reshape_cb);
    glutKeyboardFunc(keyboard_cb);    // Teclas normales
    glutSpecialFunc(specialKeys_cb);  // Teclas especiales (flechas)

    glClearColor(1.f, 1.f, 1.f, 1.f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    initialize();
    glutMainLoop();
    return 0;
}

