#include <iostream> 
#include<GL/freeglut.h>
using namespace std; 



class Joueur {       

public:             
    GLfloat x;       // la position du joueur
    GLfloat y ;  	// la position du joueur
    int posx;
    int posy;
    GLfloat step;
    
    Joueur(){  // constructeur par défaut
    	this->x=0.0f;
		this->y=0.0f;
	}
	Joueur(GLfloat x,GLfloat y,GLfloat step){  
		this->x=x;
		this->y=y;
		this->posx=0;
		this->posy=0;
		this->step=step;
	}
	/* une fonction qui nous permette d'afficher le joueur dans le labyrinthe*/
	void afficherJouer(GLfloat dx1,GLfloat dy1){
    	glTranslatef(dx1, dy1, 0.0f);  // Pour faire la traslation avec dx1,dy1      
      	glBegin(GL_QUADS);        // La fonction pour tracer un carre
      	glColor3f(0.0f, 0.5f, 0.0f); // La coleur du carre      
      	glVertex2f(x,  y-step);    // Sommet 1
      	glVertex2f( x+step, y-step); // Sommet 2
      	glVertex2f( x+step,  y); // Sommet 3
      	glVertex2f(x,  y);  // Sommet 4
      	glFlush(); 
      	glEnd();
	}
	
};
