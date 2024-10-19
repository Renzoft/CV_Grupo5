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

    // Configurando la proyección ortográfica centrada
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);  // Sistema de coordenadas centrado en la ventana
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Función para dibujar el triángulo centrado en el origen
void drawTriangle() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);

    // Vértices del triángulo alrededor del origen (centrado)
    glVertex2f(-50, -50); glVertex2f(50, -50);
    glVertex2f(-50, -50); glVertex2f(0, 100);
    glVertex2f(0, 100); glVertex2f(50, -50);

    glEnd();
}

// Función de visualización
void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Aplicar las transformaciones (traslación, rotación, escalado)
    glTranslatef(translateX, translateY, 0.0f);  // Desplazamiento
    glScalef(scaleFactor, scaleFactor, 1.0f);    // Escalado
    glRotatef(angle, 0.0f, 0.0f, 1.0f);          // Rotación

    glColor3f(1, 1, 0);
    glLineWidth(3);
    drawTriangle();

    glutSwapBuffers();
}

// Función para controlar el teclado
void keyboard_cb(unsigned char key, int x, int y) {
    switch (key) {
        case 'R':  // Rotación positiva
            angle += 5.0f;
            break;
        case 'r':  // Rotación negativa
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

// Función para manejar las teclas especiales (flechas de desplazamiento)
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

// Inicialización
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

