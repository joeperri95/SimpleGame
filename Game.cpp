#include "Game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BOUNDARY 50
#define SPEED 2.0
#define TITLE "Ayy"

Game::Game(){
	
}

Game::~Game(){
	
}

void Game::init(){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	this->state = Running;
	this->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_ACCELERATED);
	this->renderer = SDL_CreateRenderer(this->window,-1,0);
	this->screenClip = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	
	this->fpsTimer = new Timer();
	this->immuneTimer = new Timer();
	this->fpsTimer->start();
	this->countedFrames = 0;
	this->hearts = new MyTexture(renderer, "../res/heart.png");
	this->background = new MyTexture(renderer, "../res/yoot.png");
	this->mainCharacter = new Character(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,this->renderer,"../res/char.png");
	this->gameOverFont = new MyTexture();
	this->pauseFont = new MyTexture();
	
	this->gameOverFont->loadFont(this->renderer, "../res/lazy.ttf", 72);
	this->pauseFont->loadFont(this->renderer, "../res/lazy.ttf", 72);
	
	GameObject* g = new GameObject(300, 200, "../res/rock.png", this->renderer);
	Character* e = new Character(300, 400, this->renderer, "../res/Untitled.png");
	
	this->addScenery(g);
	this->addEnemy(e);
	
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

void Game::addScenery(GameObject* g){
	this->scenery.push_back(g);
}

void Game::render(){
	
	SDL_RenderClear(this->renderer);
	
	this->countedFrames++;
	float avgFPS = this->countedFrames / (fpsTimer->getTicks() / 1000.f);
	if(avgFPS > 2000000){
		avgFPS = 0;
	}
	
	std::stringstream msg;
	
	switch(this->state){
		case Pause:
			{
			SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderFillRect(this->renderer, NULL);
			
			SDL_Color msgColor = {0x00, 0x00, 0x00, 0xFF};
			
			pauseFont->loadMessage(this->renderer, msgColor, "Game Paused");
			pauseFont->render(this->renderer, 100, 100);
			
			msg << avgFPS;
			pauseFont->loadMessage(this->renderer,msgColor, msg.str().c_str());
			pauseFont->render(this->renderer, 500,300);
			
			}
			
		break;
		
		case Running:
			{
				
			background->render(renderer,0,0);
			
			if(mainCharacter->b != NULL){
				mainCharacter->b->render(renderer);
			}
			
			for(std::vector<Character*>::iterator i = this->enemies.begin(); i != this->enemies.end(); ++i){
				(*i)->render(this->renderer);
			}
			
			for(std::vector<GameObject*>::iterator i = this->scenery.begin(); i != this->scenery.end(); ++i){
				(*i)->render(this->renderer);
			}
			
			mainCharacter->render(this->renderer);
			
			for(int i = 0; i < mainCharacter->getHealth(); i++){
				SDL_Rect heartDest = {25 * i,0,25,25};
				this->hearts->render(this->renderer, &heartDest);
			}
			
			}
		break;
		
		case GameOver:
		{
			SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(this->renderer, NULL);
			
			SDL_Color msgColor = {0xFF, 0x00, 0x00, 0xFF};
			
			gameOverFont->loadMessage(this->renderer, msgColor, "YOU DIED");
			gameOverFont->render(this->renderer, 100, 100);
			
			msg << avgFPS;
			gameOverFont->loadMessage(this->renderer,msgColor, msg.str().c_str());
			gameOverFont->render(this->renderer, 500,300);
			
		}
	}
	
	SDL_RenderPresent(this->renderer);
}

void Game::update(){
	
	switch(this->state){
		case Pause:
			
		break;
		
		case Running:
			
			if(!mainCharacter->isAlive()){
				this->state = GameOver;
			}
			
			else{
				
				if(mainCharacter->b != NULL){
					mainCharacter->b->move();
				
				}
				
				int newX = mainCharacter->getX() + mainCharacter->getXVelocity();
				int newY = mainCharacter->getY() + mainCharacter->getYVelocity();
				
				//collision detection with scenery 
				
				for(std::vector<GameObject*>::iterator i = this->scenery.begin(); i != this->scenery.end(); ++i){
					
					if(((newX + mainCharacter->getWidth()) > (*i)->getX() && newX < ((*i)->getWidth() + (*i)->getX()))  &&  (newY + mainCharacter->getHeight() > (*i)->getY() && newY < ((*i)->getHeight() + (*i)->getY()))){
						newX = mainCharacter->getX();
						newY = mainCharacter->getY();
					}
					
				}
				
				//check if damage is taken
				
				for(std::vector<Character*>::iterator i = this->enemies.begin(); i != this->enemies.end(); ++i){
					
					if(((newX + mainCharacter->getWidth()) > (*i)->getX() && newX < ((*i)->getWidth() + (*i)->getX()))  &&  (newY + mainCharacter->getHeight() > (*i)->getY() && newY < ((*i)->getHeight() + (*i)->getY()))){
						
						if(mainCharacter->isImmune()){
							
							std::cout << "immune" << std::endl;
							
							if(this->immuneTimer->isRunning() && !this->immuneTimer->isPaused()){
								if(this->immuneTimer->getTicks() > 500){
									mainCharacter->setImmune(false);
									immuneTimer->stop();
								}
							}
							else{
								immuneTimer->start();
							}
							
							newX = mainCharacter->getX();
							newY = mainCharacter->getY();
						}
						
						else{								
							newX = mainCharacter->getX();
							newY = mainCharacter->getY();
							mainCharacter->takeDamage(1);
						}
						
					}
					
				}
				
				
				
				mainCharacter->setX(newX % SCREEN_WIDTH);
				mainCharacter->setY(newY % SCREEN_HEIGHT);
				
				//scroll right
				if(newX > (SCREEN_WIDTH - SCREEN_BOUNDARY)){
					if((this->screenClip.x + this->screenClip.w) >= this->background->getTotalWidth()){
						
						//stop scrolling if at maximum
						if(newX >= (SCREEN_WIDTH - mainCharacter->getWidth())){
							mainCharacter->setX(SCREEN_WIDTH - mainCharacter->getWidth());
							mainCharacter->setXVelocity(0);
						}
						
					}
					else{
						mainCharacter->setX(SCREEN_WIDTH - SCREEN_BOUNDARY);
						mainCharacter->setXVelocity(0);
						this->t_setClip(SPEED,0);
					}
				}
				
				//scroll left
				else if(newX < SCREEN_BOUNDARY){
					if(this->screenClip.x == 0){
						
						//stop scrolling if at minimum X
						if(newX < 0){
							mainCharacter->setXVelocity(0);
							mainCharacter->setX(0);
						}
					}
					else{
						this->t_setClip(-SPEED,0);
						mainCharacter->setX(SCREEN_BOUNDARY);
					}
				}
				
				//scroll down
				if(newY > (SCREEN_HEIGHT - SCREEN_BOUNDARY)){
					if(this->screenClip.h + this->screenClip.y >= this->background->getTotalHeight()){
						if(newY > SCREEN_HEIGHT - mainCharacter->getHeight()){
							mainCharacter->setY(SCREEN_HEIGHT - mainCharacter->getHeight());
							mainCharacter->setYVelocity(0);
						}
						
					}
					else{
						mainCharacter->setY(SCREEN_HEIGHT - SCREEN_BOUNDARY);
						mainCharacter->setYVelocity(0);
						this->t_setClip(0,SPEED);
						
					}
				}
				
				//scroll up
				else if(newY < SCREEN_BOUNDARY - mainCharacter->getHeight()){
					if(this->screenClip.y == 0){
						if(newY <= 0){
							mainCharacter->setY(0);
							mainCharacter->setYVelocity(0);
						}
					}
					else{
						mainCharacter->setY(SCREEN_BOUNDARY - mainCharacter->getHeight());
						this->t_setClip(0,-SPEED);
					}
				}		
			}
		break;
		
		case GameOver:
		
		
		break;
	}
	
		
}


void Game::t_setClip(int x, int y){
	this->screenClip = {this->screenClip.x + x, this->screenClip.y + y ,SCREEN_WIDTH, SCREEN_HEIGHT};
	this->background->setClip(&(this->screenClip));
	
	for(std::vector<Character*>::iterator i = this->enemies.begin(); i != this->enemies.end(); ++i){
		(*i)->setX((*i)->getX() - x);
		(*i)->setY((*i)->getY() - y);
	}
			
	for(std::vector<GameObject*>::iterator i = this->scenery.begin(); i != this->scenery.end(); ++i){
		(*i)->setX((*i)->getX() - x);
		(*i)->setY((*i)->getY() - y);
	}
	
	
	
}

void Game::loop(){
	
	bool quit = false;
	SDL_Event e;
	
	//corresponds to W      A      S     D  
	bool keys[5] = {false,false,false,false};
	
	while(!quit){
		
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			
			else if(e.type == SDL_KEYDOWN){
				switch(e.key.keysym.sym){
					case SDLK_w:
						keys[0] = true;
						break;
					case SDLK_a:
						keys[1] = true;
						break;
					case SDLK_s:
						keys[2] = true;
						break;
					case SDLK_d:
						keys[3] = true;
						break;
					case SDLK_q:
						SDL_Quit();
						quit = true;
						break;
					case SDLK_SPACE:
						
						if(state == Pause){
							state = Running;
						}
						else if(state == Running){
							state = Pause;
						}
						else if(state == GameOver){
							mainCharacter->setHealth(3);
							state = Running;
						}
						break;
					case SDLK_e:
						mainCharacter->shoot(this->renderer);
					break;
				}
			}
			
			else if(e.type == SDL_KEYUP){
				switch(e.key.keysym.sym){
					case SDLK_w:
						keys[0] = false;
						break;
					case SDLK_a:
						keys[1] = false;
						break;
					case SDLK_s:
						keys[2] = false;
						break;
					case SDLK_d:
						keys[3] = false;
						break;
				}
			}
		}
		
		if(keys[0] && keys[2]){
			mainCharacter->setYVelocity(0);
		}
		else if(keys[0] && !keys[2]){
			mainCharacter->setYVelocity(-SPEED);
		}
		else if(!keys[0] && keys[2]){
			mainCharacter->setYVelocity(SPEED);
		}
		else{
			mainCharacter->setYVelocity(0);
		}
		
		if(keys[1] && keys[3]){
			mainCharacter->setXVelocity(0);
		}
		else if(keys[1] && !keys[3]){
			mainCharacter->setXVelocity(-SPEED);
		}
		else if(!keys[1] && keys[3]){
			mainCharacter->setXVelocity(SPEED);
		}
		else{
			mainCharacter->setXVelocity(0);
		}
		
		this->update();
		this->render();
		SDL_Delay(5);
	}
}