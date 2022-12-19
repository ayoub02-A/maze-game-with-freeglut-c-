#include <iostream>		//Pour lire ou écrire dans des entrée/sortie, vous devez l'inclure
#include"Joueur.h"		//pour inclure la classe Joueur
#include"Cible.h"		//pour inclure la classe Cible
#include<GL/freeglut.h>  // inclure les librairies du openGL (inclure GLUT, glu.h et gl.h)
using namespace std;


Joueur *joueur;		//objet de type Joueur
Cible *cible;		//objet de type Cible	
//int refreshMillis = 30;		//pour rafraichir l'affichage graphiques dans l'ecran.
GLfloat dx=0;		//	(les abscisses)	nous permette de savoir la position du joueur ou du Cible aussi pour dessiner les mures.
GLfloat dy=0;		//	(les ordonnées) nous permette de savoir la position du joueur ou du Cible aussi pour dessiner les mures
GLfloat step=0.0f;		//	variable de type GLfloat nous permette de generer notre labyrinthe
int posx=0;		//	(les abscisses) pour passer a la case suivant du labyrinthe et controler la distance.
int posy=0;		//	(les ordonnées)	pour passer a la case suivant du labyrinthe et controler la distance.
int l=0;		// pour savoir le nombre des lignes.
int c=0;		//  pour savoir le nopmbre des colonnes.
int n=15;		//   la nombre des lignes et des cases (la taille de la matrice 15*15) 
int posGanX=n-1;		// les abscisses de la sortie de le labyrinthe
int posGanY=n-1; 		// les ordonnées de la sortie de le labyrinthe
int menu=3; // la variable de type int qui nous permette de contrôler l'affichage des interfaces.
	   
int matrice [15][15] ={ 		//	 la matrice qui nous permette de dessiner le labyrinthe.
       {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	   {1,1,1,0,1,1,1,1,1,0,1,1,1,0,0},
	   {0,0,1,0,0,0,0,0,0,0,0,1,1,1,0},
	   {1,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
	   {1,0,0,1,1,0,0,0,1,1,0,0,0,1,0},
	   {1,1,1,1,0,0,1,0,1,0,0,1,1,1,0},
	   {1,0,0,0,0,0,1,0,0,0,0,1,0,0,1},
	   {0,0,1,1,1,0,1,0,0,0,1,1,0,1,1},
	   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
	   {1,1,0,0,1,1,0,0,1,0,1,1,1,0,1},
	   {1,0,0,1,1,0,0,0,1,0,0,0,1,0,1},
	   {1,0,0,1,1,0,1,0,1,0,1,0,1,0,1},
	   {1,1,0,0,1,0,1,0,1,0,1,0,1,0,1},
	   {0,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
	   {0,1,1,1,1,1,1,1,1,0,0,0,1,0,0},
	   };

/* une fonction qui nous permette de dessiner les caractères  */
void output(GLfloat x, GLfloat y, char *string){
    int len, i; //
    glRasterPos2f(x,y); // pour donner les coordonnées du caractères.
    len=(int) strlen(string); //exprimée en nombre de caractères, de la chaîne de caractères.
    for (i = 0; i < len; i++){
		glFlush(); //pour forcer la carte graphiques à faire tracer les caractères.
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);	/*glutBitmapCharacter rend un caractère bitmap en utilisant OpenGL  
		
		(bitmap=il s'agit d'images pixellisées, 
		c'est-à-dire un ensemble de points (pixels) contenus dans un tableau,
		chacun de ces points possédant une ou plusieurs valeurs décrivant sa couleur) */
		
	}	
}

/* une fonction qui nous permette de régler la taille la fenetres */
void myreshape(int w, int h){ 
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // Réglez notre fenêtre à la taille de notre choix w= width  et h= height  (largeur et langueur) 
}


/* une fonction qui nous permette de construire l'interface de début */
void Homescreen(){
	glClear(GL_COLOR_BUFFER_BIT);	// pour rendre l'arrière-plans de l'interface noire
	/*effacer les couleurs et de les profondeur des tampons pour etre de bonne pratique pour le départ. c'est comme une ardoise propre.*/
	glColor3f(0.0,1.0,0.0);		// la couleur des caractères
	output(-0.5f,0.6f,"PROJET DE LABYRINTH (C++) : S4 2020/2021");
	output(-0.3f,0.4f,"Ayoub Ouhdidou & Hakim Ossor");
	output(-0.4f,0.0f,"1.COMMENCER LE JEU");
	output(-0.4f,-0.1f,"2.INSTRUCTIONS");
	output(-0.4f,-0.2f,"3.MENU");
	output(-0.4f,-0.3f,"0.QUITTER");
	//glFlush();  //pour forcer la carte graphiques à faire tracer les caractères.
}

/* une fonction qui nous permette de construire l'interface d'instruction*/
void instructions(){
  	glClear(GL_COLOR_BUFFER_BIT);	// pour rendre l'arrière-plans de l'interface noire
	/*effacer les couleurs et de les profondeur des tampons pour etre de bonne pratique pour le départ. c'est comme une ardoise propre.*/
	glColor3f(1.0,0.0,1.0);		//la couleur des caractères
    output(-0.15f,0.6f,"INSTRUCTIONS:");
    glColor3f(1.0,1.0,0.0);
  	output(-0.7f,0.1f,"* POUR DEPLACER LE POINT, UTILISER LES TOUCHES FLECHEES");
  	output(-0.7f,0.0f,"* TROUVEZ LE CHEMIN DE SORTIE DANS LE LABYRINTHE");
  	output(-0.7f,-0.1f,"* LE POINT DE COULEUR VERT INDIQUE LE POINT QUI A LA POSSIBILITE DE DEPLACER");
  	output(-0.7f,-0.2f,"* LE POINT DE COULEUR ROSE INDIQUE LA SORTIE DE LABYRINTH");
  	glColor3f(0.0,0.0,1.0);
  	output(-0.7f,-0.4f,"* TAPEZ 0 POUR QUITTER LE JEU");
  	//glFlush();  //pour forcer la carte graphiques à faire tracer les caractères.
}
/* une fonction qui nous permette de construire l'interface de la victoire*/
void WinScreen(){
  	glClear(GL_COLOR_BUFFER_BIT);		// pour rendre l'arrière-plans de l'interface noire
	/*effacer les couleurs et de les profondeur des tampons pour etre de bonne pratique pour le départ. c'est comme une ardoise propre.*/
	glColor3f(0.0,1.0,0.0);		//la couleur des caractères
 	output(-0.9f,0.6f,"*******************************************************************************************************");
 	glColor3f(1.0,1.0,0.0);	
 	output(-0.9f,0.5f,"*******************************************************************************************************");
 	glColor3f(0.0,1.0,0.0);
 	output(-0.9f,0.4f,"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\");
 	glColor3f(1.0,1.0,0.0);	
 	output(-0.9f,0.3f,"<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>");
 	glColor3f(0.0,1.0,0.0);	
 	output(-0.9f,0.2f,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
 	glColor3f(1.0,1.0,1.0);	
 	output(-0.9f,0.1f,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Vous avez Gagne~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
 	glColor3f(0.0,1.0,0.0);
 	output(-0.9f,0.0f,"*******************************************************************************************************");
 	glColor3f(1.0,1.0,0.0);	
 	output(-0.9f,-0.1f,"*******************************************************************************************************");
 	glColor3f(0.0,1.0,0.0);
 	output(-0.9f,-0.2f,"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\");
 	glColor3f(1.0,1.0,0.0);	
 	output(-0.9f,-0.3f,"<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>");
 	glColor3f(0.0,1.0,0.0);	
 	output(-0.9f,-0.4f,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	glColor3f(0.5,0.5,0.5);
 	output(-0.9f,-0.6f,"*tapez 0 pour quitter");
   	//glFlush();  //pour forcer la carte graphiques à faire tracer les caractères.
}

/* une fonction qui nous permette de tracer des carre pour construire le labyrinthe*/
void tracerCarre(float x,float y,float step){
	glBegin(GL_QUADS);  /*glBegin() et glEnd() délimitent les sommets qui définissent une primitive ou un groupe de primitives similaires.
	glBegin() accepte un seul argument qui spécifie de quelles dix manières les sommets sont interprétés. 4 Sommets*/
	//GL_QUADS : Traite chaque groupe de quatre sommets comme un quadrilatère indépendant.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// pour rendre l'arrière-plans de l''interface noire
    glClear(GL_COLOR_BUFFER_BIT);  // pour rendre l'arrière-plans de l'interface noire
	/*effacer les couleurs et de les profondeur des tampons pour etre de bonne pratique pour le départ. c'est comme une ardoise propre.*/
    glColor3f(1.0f, 0.5f, 0.0f); // rendre la couleur orange.
    float n=0.05f;
    n=step;  
    glVertex2f(x,  y-n);    //  Sommet 1
    glVertex2f( x+n, y-n); 	//  Sommet 2
    glVertex2f( x+n,  y);	//	Sommet 3
	glVertex2f(x,  y);		//  Sommet 4
	//pour tracer le carre 
	glFlush();  //pour forcer la carte graphiques à faire tracer les carres.
    glEnd(); 
}

/* une fonction qui nous permette de generer le labyrinthe*/
void genererLabyrinthe(GLfloat step,int n){
	float step1=0.0f;   
	float step2=0.0f;  
	for(int i=0;i<n;i++){   // Un boucle sur les lignes
		step1=0.0f;
		for(int j=0;j<n;j++){   // Une boucle sur les colonnes
			if(matrice[i][j]==1){    // Si une case contient 1 tracer un carre
				tracerCarre(-1.0f+step1,1.0f-step2,step);
				}
			step1=step1+step; // augmenter les x dans tracerCarre
		}
	step2=step2+step; //  augmenter les y dans tracerCarre
	}
}

/* une fonction qui nous permette de generer le labyrinthe avec le joueur et la cible*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT);  // pour rendre l'arrière-plans de l'interface noire (clear the color buffer)
	/*effacer les couleurs et de les profondeur des tampons pour etre de bonne pratique pour le départ. c'est comme une ardoise propre.*/
    //glMatrixMode(GL_MODELVIEW); // pour spécifier la matrice de loadUdentity 
    step=(2.0f/n);  // Pour determiner la taille de chaque caree 
	glLoadIdentity();  // Pour separer les objects dans la matrice
   	joueur=new Joueur(-1.0f,1.0f,step);// instanciation du pointeur Joueur
  	joueur->afficherJouer(dx,dy); // l'appel de la methode afficherJoueur
  	glLoadIdentity(); //  Pour separer les objects dans la matrice
   	cible=new Cible(0.87f,-0.8699f,step);// instanciation du pointeur Cible
  	cible->afficherCible(dx,dy); // l'appel de la methode afficherCible
  	glLoadIdentity();//	Pour separer les objects dans la matrice
	genererLabyrinthe(step,n);   // Pour generer le labyrinthe
	glutSwapBuffers();//	échange les tampons de la fenêtre actuelle si double tampon (pour facilite l'affichage des fenetres.
	glutPostRedisplay(); // pour rafraîchir l'affichage pendant le mouvement du joueur
}


/* une fonction qui nous permette de generer le jeu*/
void dispalyAll(){	
	glClear(GL_COLOR_BUFFER_BIT);   // pour rendre l'arrière-plans de l'interface noire (clear the color buffer)
	/*effacer les couleurs et de les profondeur des tampons pour etre de bonne pratique pour le départ. c'est comme une ardoise propre.*/
	if(menu==1){
		display();	
	}
	if(menu==2){
		instructions();  
	}
	if(menu==3){
		Homescreen(); 	
	}
	if(l==posGanX && c==posGanY){	// la sortie de labyrinthe
		menu=4;
		WinScreen();
	}
}

/* une fonction qui nous permette de generer le mouvement dans le jeu*/
void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_RIGHT: // la touche droite
        	if(posx+1<n & matrice[l][c+1]==0){  // si la route est ouver et la position du joueur et inferireur 
          		dx+=step; 
            	posx++; 
            	c++; 
			}
          	break;
			         
        case GLUT_KEY_LEFT:    // la touche gauche
			if(posx-1>=0 & matrice[l][c-1]==0){ 
        		dx-=step;
         		posx--;
         		c--;
     		}	
		 	break;
		 	
		case GLUT_KEY_UP:  // la touche haut
			if( posy-1>=0 & matrice[l-1][c]==0){     
         	dy+=step;
         	posy--;
         	l--;
     		}
		  	break;
		  	
       	case GLUT_KEY_DOWN:    // la touche bas
	    	if(posy+1<n & matrice[l+1][c]==0) {		
          		dy-=step; 
          		posy++;
          		l++;
		  	}
			break;     
	}
  	cout<<"Ligne="<<l;
	cout<<" Coulmn="<<c<<endl;
}

/* une fonction qui nous permette de generer le clavier*/
void vClavier(unsigned char key, int x, int y){ 
// unsigned char :pour lire les nombres dans le clavier (ASCII caractères)
	switch (key){
		case '1' :
			display(); 
			menu=1;
			glutPostRedisplay();	// pour rafraîchir l'affichage pendant le mouvement du joueur	
			break;
		
	    case '2' :
	    	instructions();
			menu=2;
			glutPostRedisplay(); // pour rafraîchir l'affichage pendant le mouvement du joueur
			break;

		case '3' :
			Homescreen();
			menu=3;
			glutPostRedisplay(); // pour rafraîchir l'affichage pendant le mouvement du joueur
			break;
		case '0':
 			exit(1);	// pour quitter le jeu.
	}
}


int main(int argc, char** argv) {
	
   glutInit(&argc, argv);  // pour initialiser la librairie du GLUT 
   glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE); 	// pour initialiser l'affichage du couleur et du fenetres
   glutInitWindowSize(1200, 600);  // pour initialiser la taille du fenetre
   glutInitWindowPosition(40, 40); // pour denfinir la position du fentre 
   glutCreateWindow("JEU DE LABYRINTH");   // pour denfinir le nom du fentre 
   glutDisplayFunc(dispalyAll);  // pour appeler la fonction principale du jeu.
   glutSpecialFunc(specialKeys); // pour lancer l'utilisation des touches (UP,DOWN,LEFT,RIGHT)
   glutKeyboardFunc(vClavier);    // pour lancer l'utilisation de clavier
   glutMainLoop();           // pour répéter les fonctions glut dans le main.  
   return 0;
}
