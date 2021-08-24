#include <iostream>
#include <math.h>
#include <random>
#include <unistd.h>

#include "GameWindow.hpp"

using namespace std;

bool drawFirstRun = true;
SDL_Renderer *renderer;

const int point_ammount = 500;
SDL_Point* points = new SDL_Point[point_ammount];
int pixelsValues[point_ammount][point_ammount];

float lerp(float s, float e, float t){return s+(e-s)*t;}
float ilerp(float s, float e, float t){return (t-s)/(e-s);}

int Remap(int x, int a, int b, int c, int d){
	return lerp(c, d, ilerp(a, b, x));
}

//calculate saturation based on distance
int CalculateValue(SDL_Point _point, int _x, int _y){
	int _dist = sqrt(pow((_point.x - _x),2)+pow((_point.y - _y), 2));
	if(_dist > 50){ return 255; }
	int r = Remap(_dist, 0, 50, 0, 255);
	return r;
}


bool event(GameWindow* GW){
	SDL_Event e = GW->getEvent();
	return 0;
}

bool draw(GameWindow* GW){
	if(drawFirstRun){
		drawFirstRun = false;
		renderer = GW->getRenderer();
		srandom(time(NULL));

		// 1) generating random points
		for(int i = 0; i < 500; i++){
			points[i].x = random()%500;
			points[i].y = random()%500;
		}

		// 2) set value for each pixels of the screen
		for(int x = 0; x < 500; x++){
			for(int y = 0; y < 500; y++){
				pixelsValues[x][y] = 255;
				// 2.1) calculate distance to points
				for(int i = 0; i < 500; i++){
					int _value = CalculateValue(points[i], x, y);
					if(pixelsValues[x][y] > _value){
						pixelsValues[x][y] = _value; 
					}
				}
			}
		}

	}
		for(int x = 0; x < 500; x++){
			for(int y = 0; y < 500; y++){
				SDL_SetRenderDrawColor(renderer, pixelsValues[x][y], pixelsValues[x][y], pixelsValues[x][y], 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		/* SDL_SetRenderDrawColor(renderer, 255,0,0, 255); */
		/* SDL_RenderDrawPoints(renderer, points, 500); */
	return 0;
}

int main(void){
	GameWindow Gwin;
	if(Gwin.InitWindow("test", 500, 500)){
		return 1;
	}
	Gwin.setBackgroundColor(0xFF,0xFF,0xFF,0xFF);
	Gwin.runWindow(draw, event);
	return 0;
}

