#include <iostream> 
#include<GL/freeglut.h> 
using namespace std;   


class Cible {       
public:                 
    GLfloat x;       // la position du Cible
    GLfloat y ;  	// la position du Cible
    int posx;
    int posy;
    GLfloat step; 
    
	Cible(){ // constructeur par défaut
		this->x=1.0f;
		this->y=1.0f;		
	}
	
	Cible(GLfloat x,GLfloat y,GLfloat step){ 
		this->x=x;
		this->y=y;	
		this->posx=0;
		this->posy=0;
		this->step=step;
	}
	/* une fonction qui nous permette d'afficher la cible dans le labyrinthe*/
	void afficherCible(GLfloat dx1,GLfloat dy1){
    	glBegin(GL_QUADS);  //
      	glColor3f(2.0f, 0.5f, 1.0f);		// La coleur du carre
      	glVertex2f(x,  y-step);    // Sommet 1
      	glVertex2f( x+step, y-step); // Sommet 2
      	glVertex2f( x+step,  y); //  Sommet 3
      	glVertex2f(x,  y); // Sommet 4
      	glEnd();
	}
	
};
