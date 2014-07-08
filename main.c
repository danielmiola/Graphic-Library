/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

#include "graphiclib.h"

int main(){
	
	printf("\e[H\e[2J"); //cleans the unix terminal
	printf("----------------------------------\n");
	printf("CG - Biblioteca Grafica de Funcoes\n");
	printf("----------------------------------\n\n");

	/*-----------------------------------------
	Variables declaration
	-----------------------------------------*/
	
	int i, j; //iterators
	point  minXY, maxXY, viewPortXY; //universe min and max and viewport dimensions
	point3D minXYZ, maxXYZ; //universe3D min and max
	int qPoint, qObject, qPointsFace, qFaces, qObject3D; //stores the quantity of points and objects selected by the user
	int option; //user decides if wants to work with 2D or 3D dimension
	int listNum; //user decides which object he/she wants to apply transformations
	int menu; //stores the menu input by the user

	/*-----------------------------------------
		Look-up table definition
		-----------------------------------------*/
		lookup lkt[6];
		lkt[0].colors.r = 1; lkt[0].colors.g = 1; lkt[0].colors.b = 1;
		lkt[1].colors.r = 0; lkt[2].colors.g = 0; lkt[2].colors.b = 0;
		lkt[2].colors.r = 1; lkt[3].colors.g = 1; lkt[3].colors.b = 0;
		lkt[3].colors.r = 1; lkt[4].colors.g = 0; lkt[4].colors.b = 0;
		lkt[4].colors.r = 0; lkt[5].colors.g = 1; lkt[5].colors.b = 0;
		lkt[5].colors.r = 0; lkt[6].colors.g = 0; lkt[6].colors.b = 1;

	printf("Deseja trabalhar em qual dimensao?\n\n- [0] para 2D;\n- [1] para 3D.\n\n-> ");
	scanf("%d", &option);
	
	/*=========================================
	2D
	=========================================*/

	if(option == 0){

		printf("\e[H\e[2J"); //cleans the unix terminal
		printf("-------------------------------------\n");
		printf("CG - Biblioteca Grafica de Funcoes 2D\n");
		printf("-------------------------------------\n\n");

		/*-----------------------------------------
		Universe and viewport setting
		-----------------------------------------*/

		setUniverse(&minXY, &maxXY); //setting universe values
		//getUniverse(&minXY, &maxXY); //getting universe values

		setViewPort(&viewPortXY); //setting the view port size according to user input
		//getViewPort(&viewPortXY); //getting the view port dimensions

		/*-----------------------------------------
		Matrix declaration and inicialization
		-----------------------------------------*/

		int image[(int)viewPortXY.x * (int)viewPortXY.y]; //creating the matrix
		initMatrix(image, &viewPortXY); //initializes the matrix

		/*-----------------------------------------
		Objects declaration
		-----------------------------------------*/	
		printf("\nQuantos objetos a imagem ira possuir: ");
		scanf("%d", &qObject);

		list l[qObject]; //list that will contain the array of objects with its points
		int objColor[qObject]; //array that contains the color of each object
		point pt; //point entered by the user that is added to the list

		for(j = 0; j < qObject; j++){
			printf("\nQual a cor do objeto %d: ", j+1);
			scanf("%d", &objColor[j]);

			printf("\nQuantos pontos o objeto %d ira possuir: ", j+1);
			scanf("%d", &qPoint);
			printf("\n");

			startList(&l[j]); //starting the list

			//fullfils the list with the points provided by the user
			for(i = 0; i < qPoint; i++){
				
				printf("-> Ponto %d do objeto %d\n\nCoordenada X: ", i+1, j+1);
				scanf("%f", &pt.x);
				printf("Coordenada Y: ");
				scanf("%f", &pt.y);
				printf("\n");

				//adds this point to the list
				addEndList(&l[j], &pt, &maxXY, &minXY, &viewPortXY);
			}
		}

		/*-----------------------------------------
		Menu
		-----------------------------------------*/	
		printf("\e[H\e[2J"); //cleans the unix terminal
		printf("--------------------------\n");
		printf("2D - Menu de operacoes\n");
		printf("--------------------------\n\n");

		printf("- [0] Deslocamento;\n");
		printf("- [1] Rotacao;\n");
		printf("- [2] Escalonamento;\n");
		printf("- [3] Cisalhamento;\n");
		printf("- [4] Espelhamento;\n");
		printf("- [5] Exibir a imagem;\n");
		printf("- [6] Sair;\n");

		printf("\n-> ");
		scanf("%d", &menu);

		while(menu != 6){
			//translation option

			switch (menu) {
				case 0: // translate
					printf("\nQual objeto deseja deslocar: ");
					scanf("%d", &listNum);
					translate(&l[listNum-1], &minXY, &maxXY, &viewPortXY);
					break;

				case 1: // rotate
					printf("\nQual objeto deseja rotacionar: ");
					scanf("%d", &listNum);
					rotate(&l[listNum-1], &minXY, &maxXY, &viewPortXY);
					break;

				case 2: // scaling
					printf("\nQual objeto deseja escalonar: ");
					scanf("%d", &listNum);
					scale(&l[listNum-1], &minXY, &maxXY, &viewPortXY);
					break;

				case 3: // shearing
					printf("\nQual objeto deseja cisalhar: ");
					scanf("%d", &listNum);
					shearing(&l[listNum-1], &minXY, &maxXY, &viewPortXY);
					break;

				case 4: // mirror
					printf("\nQual objeto deseja espelhar: ");
					scanf("%d", &listNum);
					mirror(&l[listNum-1], &minXY, &maxXY, &viewPortXY);
					break;

				case 5: // exibir a imagem
					for(j = 0; j < qObject; j++){
						//calls the function of the list responsible for printing the lines using Bresenham's algorithm
						printListBresenham(&l[j], image, &viewPortXY, objColor[j]);
					}
					//prints the objects with the defined colors
					drawWindowLine(&viewPortXY, image, lkt);
					break;

				case 6:
					exit(0);
			}

			printf("\e[H\e[2J"); //cleans the unix terminal
			printf("--------------------------\n");
			printf("2D - Menu de operacoes\n");
			printf("--------------------------\n\n");

			printf("- [0] Deslocamento;\n");
			printf("- [1] Rotacao;\n");
			printf("- [2] Escalonamento;\n");
			printf("- [3] Cisalhamento;\n");
			printf("- [4] Espelhamento;\n");
			printf("- [5] Exibir a imagem;\n");
			printf("- [6] Sair;\n");

			printf("\n-> ");
			scanf("%d", &menu);
		}

	}

	/*=========================================
	3D
	=========================================*/

	if(option == 1){
		
		printf("\e[H\e[2J"); //cleans the unix terminal
		printf("-------------------------------------\n");
		printf("CG - Biblioteca Grafica de Funcoes 3D\n");
		printf("-------------------------------------\n\n");

		/*-----------------------------------------
		Universe and viewport setting
		-----------------------------------------*/

		setUniverse3D(&minXYZ, &maxXYZ); //setting universe values
		//getUniverse3D(&minXYZ, &maxXYZ); //getting universe values

		setViewPort(&viewPortXY); //setting the view port size according to user input
		//getViewPort(&viewPortXY); //getting the view port dimensions

		/*-----------------------------------------
		Matrix declaration and inicialization
		-----------------------------------------*/

		int image[(int)viewPortXY.x * (int)viewPortXY.y]; //creating the matrix
		initMatrix(image, &viewPortXY); //initializes the matrix

		/*-----------------------------------------
		Objects declaration
		-----------------------------------------*/	
		printf("\nQuantos objetos a imagem ira possuir: ");
		scanf("%d", &qObject3D);

		object3D objects[qObject3D]; //list that will contain the array of objects with its points
		int objColor3D[qObject3D]; //array that contains the color of each object
		point3D pt3D; //point entered by the user that is added to the list
		list *l = NULL;
		point pt;

		for(j = 0; j < qObject3D; j++){
			printf("\nQual a cor do objeto %d: ", j+1);
			scanf("%d", &objColor3D[j]);

			printf("\nQuantas faces o objeto 3D %d ira possuir: ", j+1);
			scanf("%d", &qFaces);
			printf("\n");

			printf("\nQuantos pontos a face 3D %d ira possuir: ", j+1);
			scanf("%d", &qPointsFace);
			printf("\n");

			startList(&l[j]); //starting the list

			//fullfils the list with the points provided by the user
			for(i = 0; i < qPoint; i++){
				
				printf("-> Ponto %d do objeto %d\n\nCoordenada X: ", i+1, j+1);
				scanf("%f", &pt.x);
				printf("Coordenada Y: ");
				scanf("%f", &pt.y);
				printf("\n");

				//adds this point to the list
				addEndList(&l[j], &pt, &maxXY, &minXY, &viewPortXY);
			}
		}
	}

	return 0;
}
