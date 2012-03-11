# include "main.h"
# include "RenderingCore.h"
# include "Exception.h"
# include <iostream>
# include <GLUT/glut.h>

using namespace std;

// A few basic colors.
CColor g_objRed		(1.0f, 0.0f, 0.0f);
CColor g_objGreen	(0.0f, 1.0f, 0.0f);
CColor g_objBlue	(0.0f, 0.0f, 1.0f);
CColor g_objYellow	(0.0f, 1.0f, 1.0f);
CScene g_objScene = CScene();

CRenderingCore	g_Core;

void display(void)
{
	
	static int firstTime;
	
	if (!firstTime) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		g_Core.Render();
		
		glFlush();
	}
	
	firstTime = 1;	
}

void reshape(int width, int height)
{
	/*****************************************************************
	STRATEGY:
	1. ReDefine the viewport
	*****************************************************************/
	
	// 1.
	glViewport(0, 0, width, height);
	
}

void idle(void)
{
    glutPostRedisplay();
}

void init () {
	
	/*************************************************************
	STRATEGY:
	1. Define the clear color
	2. Define the projecction volume.
	3. Define the modelview projections.
	
	NOTE:
	The reason why this code si not inside the reshape function is
	that the projection we have is fixed and does not depend upon
	the size of the window.
	*************************************************************/
	
	// 1.
	glClearColor (0, 0, 0, 1);
	
	// 2.
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, 640, -480, 0, -10, 10);
	
	// 3.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();	
}
	
int main(int argc, char** argv)
{
	/*************************************************************
	Configuration and Initialization
	*************************************************************/
	g_Log.SetLogFileName ("Log.txt");
	g_Log.Write ("\n\n\n **** The log file is operational ****\n");
	
	/************************************************************/    glutInit(&argc, argv);
	
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
	
    glutCreateWindow("GLUT Program");
    
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	
	init();
	
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
