
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PASSO    5

struct tipo_camera {
    GLint   posx;               // posição x da camera
    GLint   posy;               // posição y da camera
    GLint   posz;               // posição z da camera
    GLint   alvox;              // alvo x da visualização
    GLint   alvoy;              // alvo y da visualização
    GLint   alvoz;              // alvo z da visualização
    GLfloat inicio;             // início da área de visualização em profundidade
    GLfloat fim;                // fim da área de visualização em profundidade
    GLfloat ang;                // efeito de zoom
    GLfloat aspecto;
};

struct tipo_luz {
   GLfloat posicao[ 4 ];
   GLfloat ambiente[ 4 ];
   GLfloat difusa[ 4  ];
   GLfloat especular[ 4 ];
   GLfloat especularidade[ 4 ];
};

// camera vai conter as definições da camera
struct tipo_camera camera;

// luz vai conter as informações da iluminação
struct tipo_luz luz;

GLint rotacao_y = 0 , rotacao_x = 0, liga = 1 , shade = 0;

void Define_Iluminacao( void )
{
    glShadeModel( GL_SMOOTH );

    glEnable( GL_LIGHTING );

	glLightModelfv( GL_LIGHT_MODEL_AMBIENT , luz.ambiente );

    glLightfv( GL_LIGHT0 , GL_POSITION , luz.posicao );

    glLightfv( GL_LIGHT0 , GL_AMBIENT  , luz.ambiente  );
    
    glLightfv( GL_LIGHT0 , GL_DIFFUSE  , luz.difusa );
    
    glLightfv( GL_LIGHT0 , GL_SPECULAR , luz.especular );

    glEnable ( GL_LIGHT0 );

    glEnable( GL_COLOR_MATERIAL );

    glMaterialfv( GL_FRONT , GL_SPECULAR  , luz.especularidade );

    glMateriali ( GL_FRONT , GL_SHININESS , 24);
}

void desenhaBotao(GLint y)
{
    glColor3f(0.890, 0.862, 0.431);

    glBegin(GL_QUADS);
        glVertex3f(60.0, 0.0, 0.0);
        glVertex3f(60.0, 0.0, 0.0);
        glVertex3f(60.0, 0.0, 0.0);
        glVertex3f(60.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(   0.0 ,   1.0 ,  0.0 );

        glVertex3f(60.0, y, 35.0);
        glVertex3f(60.0, y, 0.0);
        glVertex3f(45.0, y, 20.0);
        glVertex3f(60.0, y, 0.0);
        glVertex3f(30.0, y, 10.0);
        glVertex3f(60.0, y, 0.0);
        glVertex3f(15.0, y, 5.0);
        glVertex3f(0.0,  y, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        glNormal3f(   0.0 ,   1.0 ,  0.0 );
        glVertex3f(0.0,  y-30.0,  0.0);
        glVertex3f(60.0, y-30.0,  0.0);
        glVertex3f(15.0, y-30.0,  5.0);
        glVertex3f(60.0, y-30.0,  0.0);
        glVertex3f(30.0, y-30.0, 10.0);
        glVertex3f(60.0, y-30.0,  0.0);
        glVertex3f(45.0, y-30.0, 20.0);
        glVertex3f(60.0, y-30.0, 35.0);
    glEnd();

    glNormal3f(   1.0 ,   0 ,  0 );
    glBegin(GL_QUADS);
        glVertex3f(60, y-30,  0);
        glVertex3f(60, y,  0);
        glVertex3f(60, y, 35);
        glVertex3f(60, y-30, 35);

        glNormal3f(0.0 , 0.0 ,  -1.0 );
        glVertex3f(0.0,  y-30.0, 0.0);
        glVertex3f(0.0,  y,  0.0);
        glVertex3f(60.0, y,  0.0);
        glVertex3f(60.0, y-30.0, 0.0);

        glNormal3f(   0.7 ,   0.0 ,  0.7 );
        glVertex3f(15.0, y-30.0, 5.0);
        glVertex3f(15.0, y, 5.0);
        glVertex3f(0.0, y,  0.0);
        glVertex3f(0.0, y-30.0,  0.0);

        glVertex3f(30.0,  y-30.0, 10.0);
        glVertex3f(30.0,  y,  10.0);
        glVertex3f(15.0, y, 5.0);
        glVertex3f(15.0, y-30.0, 5.0);

        glVertex3f(45.0, y-30.0,  20.0);
        glVertex3f(45.0, y, 20.0);
        glVertex3f(30.0,  y, 10.0);
        glVertex3f(30.0,  y-30.0,  10.0);

        glVertex3f(60.0, y-30.0, 35.0);
        glVertex3f(60.0, y, 35.0);
        glVertex3f(45.0, y, 20.0);
        glVertex3f(45.0, y-30.0, 20.0);
    glEnd();
}

void DesenhaBotoes(void)
{
    glBegin(GL_QUADS);

        glColor3f(0, 0, 0);

        glNormal3f(0.0, 0.0, 0.0);
        glVertex3f(-5, -35, 0);
        glVertex3f(65, -35, 0);
        glVertex3f(65, 75,  0);
        glVertex3f(-5, 75,  0);

        desenhaBotao(0);
        desenhaBotao(35);
        desenhaBotao(70);
    glEnd();
}

void desenharLadoCubo(int x, int y)
{
    GLUquadricObj *quadObj  = gluNewQuadric();
    GLUquadricObj *quadObj2 = gluNewQuadric();
    GLUquadricObj *quadObj3 = gluNewQuadric();

    gluQuadricDrawStyle(quadObj,  GLU_FILL);
    gluQuadricDrawStyle(quadObj2, GLU_FILL);
    gluQuadricDrawStyle(quadObj3, GLU_FILL);

    glPushMatrix();
        glTranslatef(x, y, -68);
        gluCylinder(quadObj, 20, 20 , 58, 40, 40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, y, -10);
        gluDisk(quadObj2, 0, 20 , 40, 40);
    glPopMatrix();

    glPushMatrix();
        glDisable(GL_CULL_FACE);
        glTranslatef(x, y, -68);
        gluDisk(quadObj3, 0, 20 , 40, 40);
    glPopMatrix();
}

void desenhaBaseParafuso(float x, float y, float z)
{
    GLUquadricObj *quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);

    glPushMatrix();
        glTranslatef(x, y, (z - 5));
        gluCylinder(quadObj, 8, 8, 5, 40, 40);
    glPopMatrix();
}

void desenhaMeioCilindro(float radius, float loops, float height)
{
    int   STEPS       = loops;
    float DELTA       = 3.1415 / STEPS;
    float half_height = height;
    int   step        = 10;

    glCullFace(GL_FRONT_AND_BACK);
    glNormal3f(0, 0.3, 0.7);

    glBegin(GL_POLYGON);
        for (step = 0; step <= STEPS; ++step)
        {
            float angle = step * DELTA;
            glVertex3f(half_height, radius * cos(angle), radius * sin(angle));
        }
    glEnd();

    glBegin(GL_POLYGON);
        for (step = 0; step <= STEPS; ++step)
        {
            float angle = step * DELTA;
            glVertex3f(-half_height, radius * cos(angle), radius * sin(angle));
        }
    glEnd();

    glBegin(GL_QUADS);
        for (step = 0; step < STEPS; ++step)
        {
            float angle1   = step*DELTA;
            float angle2   = (step + 1)*DELTA;
            float rsine1   = radius*sin(angle1);
            float rcosine1 = radius*cos(angle1);
            float rsine2   = radius*sin(angle2);
            float rcosine2 = radius*cos(angle2);

            glVertex3f(half_height, rcosine1,rsine1);
            glVertex3f(half_height, rcosine2,rsine2);
            glVertex3f(-half_height,rcosine2,rsine2);
            glVertex3f(-half_height,rcosine1,rsine1);
        }
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(half_height,   radius, 0);
        glVertex3f(half_height,  -radius, 0);
        glVertex3f(-half_height, -radius, 0);
        glVertex3f(-half_height,  radius, 0);
    glEnd();
}

void desenhaParafuso(float x, float y, float z)
{
    GLUquadricObj *quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);

    glColor3f(0.3, 0.3, 0.3);

    desenhaBaseParafuso(x, y, z);

    glPushMatrix();
        glTranslatef(x, y, z);
        gluDisk(quadObj, 0, 8, 40, 40);
    glPopMatrix();

    glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();
        glTranslatef(x + 1, y, z);
        glRotatef(90, 0, 1, 0);
        desenhaMeioCilindro(8, 40, 3);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x - 1, y, z);
        glRotatef(-90, 0, 1, 0);
        desenhaMeioCilindro(8, 40, 3);
    glPopMatrix();

    corPadrao();
}

void desenharEncaixeParafuso(float y)
{
    desenhaParafuso(30, (y > 0 ? y - 2 : y + 2), 0);

    glPushMatrix();
        glTranslatef(30, y, -6.5);
        glRotatef(90, 1, 0, 0);
        glScalef( 3 , 1 , 2);
        glutSolidCube( 10 );
    glPopMatrix();
}

void desenhaCano(float y)
{
    GLUquadricObj *quadObj  = gluNewQuadric();
    GLUquadricObj *quadObj2 = gluNewQuadric();
    GLUquadricObj *quadObj3 = gluNewQuadric();

    gluQuadricDrawStyle(quadObj,  GLU_FILL);
    gluQuadricDrawStyle(quadObj2, GLU_FILL);
    gluQuadricDrawStyle(quadObj3, GLU_FILL);

    glColor3f(0.3, 0.3, 0.3);

    glPushMatrix();
        glTranslatef(30, y, -40);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadObj, 25, 25 , 45, 40, 40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, y, -40);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadObj2, 20, 20 , 45, 40, 40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, (y > 0 ? y : y - 45), -40);
        glRotatef((y > 0 ? -90 : 90), 1, 0, 0);
        gluDisk(quadObj2, 20, 25, 40, 40);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, y, -40);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadObj, 25, 25 , 45, 40, 40);
    glPopMatrix();

    GLUquadricObj *quadObj4 = gluNewQuadric();
    gluQuadricDrawStyle(quadObj4, GLU_FILL);

    glPushMatrix();
        glTranslatef(30, y -20, -20);
        gluCylinder(quadObj, 8, 8, 8, 40, 40);
    glPopMatrix();

    desenhaParafuso(30, y - 20, -10);
}

void desenhaCanoLateral()
{
    glPushMatrix();
        glTranslatef(-30, 45, 0);
        glRotatef(-90, 0, 0, 1);
        desenhaCano(160);
    glPopMatrix();
}

void desenhaQuadrado(float size)
{
    GLUquadricObj *quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);

    glPushMatrix();
        glRotatef(45, 0, 0, 1);
        gluDisk(quadObj, 0, size, 4, 4);
    glPopMatrix();
}

void desenhaCanto()
{
    glPushMatrix();
        glTranslatef(-15, 101, -2);
        desenhaQuadrado(7);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10, 106, -2);
        desenhaQuadrado(7);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-15, 106, -2);
        glRotatef(45, 0, 0, 1);
        desenhaQuadrado(5);
    glPopMatrix();

    glBegin(GL_POLYGON);
        glCullFace(GL_FRONT_AND_BACK);

        glNormal3f(1.0, 1.0, 1.0);
        glVertex3f(-15, 118, -9);
        glVertex3f(-15, 111, -2);
        glVertex3f(-20, 106, -2);
        glVertex3f(-27, 106, -9);
    glEnd();
}

void desenhaCantoGenerico()
{
    float x = 0;
    float y = 0;

    glPushMatrix();
        glTranslatef(x, y - 5, -2);
        desenhaQuadrado(7);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x + 5, y, -2);
        desenhaQuadrado(7);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, y, -2);
        glRotatef(45, 0, 0, 1);
        desenhaQuadrado(5);
    glPopMatrix();

    glBegin(GL_POLYGON);
        glCullFace(GL_FRONT_AND_BACK);

        glNormal3f(0.0, 0.3, 0.7);
        glVertex3f(x,      y + 12, -9);
        glVertex3f(x,      y + 5,  -2);
        glVertex3f(x - 5,  y,      -2);
        glVertex3f(x - 12, y,      -9);
    glEnd();
}

void corPadrao()
{
    glColor3f(0.4, 0.4, 0.4);
}

void Desenha(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLineWidth( 2 );

    Define_Iluminacao();

    glPushMatrix();
        glColor4f( 1.0 , 1.0 , 1.0 , 1.0 );
        glTranslatef( luz.posicao[ 0 ] , luz.posicao[ 1 ] , luz.posicao[ 2 ]  );
        glutSolidSphere( 5 , 10 , 10 );
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0, 0, 0);
    glRotatef(rotacao_y, 0, 1, 0);
    glRotatef(rotacao_x, 1, 0, 0);
    glScalef(1, 1, 1);

    corPadrao();

    glPushMatrix();
        glTranslatef(30, 21, -7);
        glScalef( 8 , 18 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, 21, -7);
        glScalef( 10, 16, 1);
        glutSolidCube( 10 );
    glPopMatrix();

    desenharEncaixeParafuso(108);
    desenharEncaixeParafuso(-66);

    glPushMatrix();
        glTranslatef(-15, 106, 0);
        desenhaCantoGenerico();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(75, 106, 0);
        glRotatef(-90, 0, 0, 1);
        desenhaCantoGenerico();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-15, -64, 0);
        glRotatef(90, 0, 0, 1);
        desenhaCantoGenerico();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(75, -64, 0);
        glRotatef(180, 0, 0, 1);
        desenhaCantoGenerico();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-11.5, 102.5, -7);
        glRotatef(45, 0, 0, 1);
        glScalef( 1.4 , 1 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(71.5, 102.5, -7);
        glRotatef(-45, 0, 0, 1);
        glScalef( 1.4 , 1 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-11.5, -60.5, -7);
        glRotatef(135, 0, 0, 1);
        glScalef( 1.4 , 1 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(71.5, -60.5, -7);
        glRotatef(-135, 0, 0, 1);
        glScalef( 1.4 , 1 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20, 21, -9);
        glRotatef(45, 0, 1, 0);
        glScalef( 1 , 17 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(80, 21, -9);
        glRotatef(45, 0, 1, 0);
        glScalef( 1 , 17 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, 111, -9);
        glRotatef(45, 1, 0, 0);
        glScalef( 9 , 1 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, -69, -9);
        glRotatef(45, 1, 0, 0);
        glScalef( 9 , 1 , 1 );
        glutSolidCube( 10 );
    glPopMatrix();

    glColor3f(0.2, 0.2, 0.2);

    desenharLadoCubo(-7, 98);
    desenharLadoCubo(67, 98);
    desenharLadoCubo(-7, -56);
    desenharLadoCubo(67, -56);

    glPushMatrix();
        glTranslatef(30, 21, -39);
        glScalef(8, 18.4, 6);
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, 113, -39);
        glScalef(8, 1, 6);
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, -71, -39);
        glScalef(8, 1, 6);
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, 21, -39);
        glScalef(10.4, 16, 6);
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-22, 21, -39);
        glScalef(1, 16, 6);
        glutSolidCube( 10 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(82, 21, -39);
        glScalef(1, 16, 6);
        glutSolidCube( 10 );
    glPopMatrix();

    desenhaCano(160);
    desenhaCano(-70);
    desenhaCanoLateral();

    DesenhaBotoes();

    glPopMatrix();

    glutSwapBuffers();
 }

void Inicializa (void)
{
    glClearColor( 0.0 , 0.0 , 0.0 , 1.0 );

    camera.posx   = 0;
    camera.posy   = 0;
    camera.posz   = 1000;
    camera.alvox  = 0;
    camera.alvoy  = 0;
    camera.alvoz  = 0;
    camera.inicio = 0.1;
    camera.fim    = 5000.0;
    camera.ang    = 25;

    luz.posicao[ 0 ] = 100.0;
    luz.posicao[ 1 ] = 100.0;
    luz.posicao[ 2 ] = 300.0;
    luz.posicao[ 3 ] = 1.0;

    luz.ambiente[ 0 ] = 0.3;
    luz.ambiente[ 1 ] = 0.3;
    luz.ambiente[ 2 ] = 0.3;
    luz.ambiente[ 3 ] = 1.0;

    luz.difusa[ 0 ] = 1.0;
    luz.difusa[ 1 ] = 1.0;
    luz.difusa[ 2 ] = 1.0;
    luz.difusa[ 3 ] = 1.0;

    luz.especular[ 0 ] = 1.0;
    luz.especular[ 1 ] = 1.0;
    luz.especular[ 2 ] = 1.0;
    luz.especular[ 3 ] = 1.0;

    luz.especularidade[ 0 ] = 0.8;
    luz.especularidade[ 1 ] = 0.8;
    luz.especularidade[ 2 ] = 0.8;
    luz.especularidade[ 3 ] = 1.0;

    rotacao_y = rotacao_x = 0;

    glEnable( GL_BLEND );

    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

    glEnable( GL_DEPTH_TEST );

    glEnable( GL_CULL_FACE );
}

void EspecificaParametrosVisualizacao( void )
{
	glMatrixMode( GL_PROJECTION );

	glLoadIdentity();

	gluPerspective( camera.ang , camera.aspecto , camera.inicio , camera.fim );

	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();

    gluLookAt( camera.posx , camera.posy , camera.posz , camera.alvox , camera.alvoy , camera.alvoz , 0 , 1 , 0 );
}

void AlteraTamanhoJanela( GLsizei largura , GLsizei altura )
{
	if ( altura == 0 )
        altura = 1;

	glViewport( 0 , 0 , largura , altura );

	camera.aspecto = ( GLfloat )largura / ( GLfloat )altura;

    EspecificaParametrosVisualizacao();
}

void GerenciaMouse( GLint button , GLint state , GLint x , GLint y )
{
	if ( button == GLUT_LEFT_BUTTON )
		if ( state == GLUT_DOWN )
			if ( camera.ang >= 6 ) camera.ang -= 5;

	if ( button == GLUT_RIGHT_BUTTON )
		if ( state == GLUT_DOWN )
			if ( camera.ang <= 174 ) camera.ang += 5;

	EspecificaParametrosVisualizacao();

	glutPostRedisplay();
}

void GerenciaTeclado( GLubyte key , GLint x , GLint y )
{
   // ESC
   if ( key == 27 )
      exit( 0 );

   if( key == 'r' )
      rotacao_y -= PASSO;

   if( key == 'R' )
      rotacao_y += PASSO;

   if ( key == 'G' )
       rotacao_x += PASSO;

   if ( key == 'g' )
       rotacao_x -= PASSO;

   if ( key == 'X' ){
       camera.posx += PASSO;
   }

   if ( key == 'x' ){
       camera.posx -= PASSO;
   }

   if ( key == 'Y' ){
       camera.posy += PASSO;
   }

   if ( key == 'y' ){
       camera.posy -= PASSO;
   }

   if ( key == 'Z' ){
       camera.posz += PASSO;
   }

   if ( key == 'z' ){
       camera.posz -= PASSO;
   }

   if ( key == 'Q' )
       camera.alvox += PASSO;

   if ( key == 'q' )
       camera.alvox -= PASSO;

   if ( key == 'W' )
       camera.alvoy += PASSO;

   if ( key == 'w' )
       camera.alvoy -= PASSO;

   if ( key == 'E' )
       camera.alvoz += PASSO;

   if ( key == 'e' )
       camera.alvoz -= PASSO;

   if ( key == 'A' && camera.ang + PASSO < 180 )
       camera.ang += PASSO;

   if ( key == 'a' && camera.ang - PASSO > 0 )
       camera.ang -= PASSO;

   if ( key == 'I'  || key == 'i' ){
      Inicializa();
   }

   EspecificaParametrosVisualizacao();

   glutPostRedisplay();

}

void TeclasEspeciais( GLint key , GLint x , GLint y )
{
   if ( key == GLUT_KEY_LEFT )
      luz.posicao[ 0 ] -= PASSO;

   if ( key == GLUT_KEY_RIGHT )
      luz.posicao[ 0 ] += PASSO;

   if ( key == GLUT_KEY_UP )
      luz.posicao[ 1 ] += PASSO;

   if ( key == GLUT_KEY_DOWN )
      luz.posicao[ 1 ] -= PASSO;

   if ( key == GLUT_KEY_PAGE_UP )
      luz.posicao[ 2 ] += PASSO;

   if ( key == GLUT_KEY_PAGE_DOWN )
      luz.posicao[ 2 ] -= PASSO;

   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   
   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  );

   glutInitWindowSize( 600 , 600 );

   glutInitWindowPosition( 0 , 0 );

   glutCreateWindow( "3D Object" );

   glutDisplayFunc( Desenha );

   glutReshapeFunc( AlteraTamanhoJanela );

   glutMouseFunc( GerenciaMouse );

   glutKeyboardFunc( GerenciaTeclado );

   glutSpecialFunc( TeclasEspeciais );

   printf("\nI   => Starging Position");
   printf("\nX x => Change camera's X position");
   printf("\nY y => Change camera's y position");
   printf("\nZ z => Change camera's z position");
   printf("\nQ q => Change target's X");
   printf("\nW w => Change target's Y");
   printf("\nE e => Change target's Z");
   printf("\nR r => Rotate the object");
   printf("\nG G => Rotate the camera");
   printf("\nA a => Zoom");
   printf("\n\nGood Luck!!!\n\n");

   Inicializa();

   glutMainLoop();
}