#include "Game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TITLE "Ayy"

Game::Game(){
	
}

Game::~Game(){
	
}

void Game::init(){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	
	this->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_ACCELERATED);
	this->renderer = SDL_CreateRenderer(this->window,-1,0);
	this->screenClip = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	
	this->enemies.push_back(new Character(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,this->renderer,"../res/Untitled.png"));
	this->background = new MyTexture(renderer, "../res/yoot.png");
	this->mainCharacter = new Character(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,this->renderer,"../res/Untitled.png");
	this->mainCharacter->setXVelocity(0);
	this->mainCharacter->setYVelocity(0);
}


void Game::addEnemy(int x, int y, std::string filePath){
	
	Character* c = new Character(x, y, this->renderer, filePath);
	
	c->setXVelocity(0);
	c->setYVelocity(0);
	
	this->enemies.push_back(c);
	
}

void Game::addEnemy(Character* c){
	this->enemies.push_back(c);
}

void Game::render(){
	
	SDL_RenderClear(this->renderer);
	
	SDL_Rect clip = {enemies.at(0)->getX()-SCREEN_WIDTH/2,enemies.at(0)->getY()-SCREEN_HEIGHT/2,enemies.at(0)->getX()+SCREEN_WIDTH/2,enemies.at(0)->getY()+SCREEN_HEIGHT/2};
	background->render(renderer,0,0,&(this->screenClip));
	
	for(std::vector<Character*>::iterator i = this->enemies.begin(); i != this->enemies.end(); ++i){
		(*i)->render(this->renderer);
	}
	
	mainCharacter->render(this->renderer);
	SDL_RenderPresent(this->renderer);
}

void Game::update(){
	
	mainCharacter->setX(mainCharacter->getX() + mainCharacter->getXVelocity());
	mainCharacter->setY(mainCharacter->getY() + mainCharacter->getYVelocity());
	
}


void Game::t_setClip(int x, int y){
	this->mainCharacter->setX(this->mainCharacter->getX() + x);
	this->mainCharacter->setY(this->mainCharacter->getY() + y);

	this->screenClip = {this->screenClip.x + x, this->screenClip.y + y ,SCREEN_WIDTH, SCREEN_HEIGHT};
}