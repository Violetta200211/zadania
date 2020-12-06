#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include <random>
#include <vector>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>

using WinPtr = std::shared_ptr<SDL_Window>;
using RenPtr = std::shared_ptr<SDL_Renderer>;
using TexPtr = std::shared_ptr<SDL_Texture>;

constexpr int W=800,H=600;
// где изначально находятся клубы дыма и какого размера
constexpr int SMOKE_X = 325, SMOKE_Y = 150, SMOKE_W = 10, SMOKE_H = 10;
std::vector<SDL_Rect> smoke;


bool light = false;
bool dog_right = true;
bool bird_right = true;


WinPtr win;
RenPtr ren;
TexPtr bird, dog, smoketex, background, background_night;

std::minstd_rand rnd;
int bird_x = 150, bird_y = 20;
int dog_x = 150, dog_y = 500;

void SDL_DIE(const char* where) {
	throw std::runtime_error(
		std::string(where) + std::string(": ")
				+ std::string(SDL_GetError()));
}

//функция загрузки текстуры
TexPtr load_texture(const char* filename){
	SDL_Surface * s; //поверхность
	s = IMG_Load(filename);
	if (s== nullptr) SDL_DIE("IMG_Load()");
	TexPtr r = TexPtr(
			SDL_CreateTextureFromSurface(ren.get(),s),
			SDL_DestroyTexture);
	if (r == nullptr) SDL_DIE("SDL_CreateTextureFromSurface");
	SDL_FreeSurface (s);
	return r;
}

void render_background(){
	SDL_RenderClear(ren.get());
	//		нарисовали небо
	SDL_Rect r1{0,0,800,575};
	SDL_RenderCopy(ren.get(), light ? background_night.get() : background.get() , nullptr, &r1);

}

void render_scene(){
	SDL_Rect r1{0,0,800,575};

//		рисуем землю
	SDL_SetRenderDrawColor(ren.get(),0,150,54,255);
	r1 = {0,574,800,599};
	SDL_RenderFillRect(ren.get(),&r1);

//		тело дома рисуем
	SDL_SetRenderDrawColor(ren.get(),120,100,48,255);
	r1 = {50,269,400,305};
	SDL_RenderFillRect(ren.get(),&r1);

//		труба дома
	SDL_SetRenderDrawColor(ren.get(),120,48,48,255);
	r1 = {300,150,50,100};
	SDL_RenderFillRect(ren.get(),&r1);

	r1 = {0, 269, 0, 0};
	SDL_RenderFillRect(ren.get(),&r1);

//		окно (рама)
	SDL_SetRenderDrawColor(ren.get(),0,0,0,255);
	r1 = {70, 289, 200, 200};
	SDL_RenderFillRect(ren.get(), &r1);

//		Со светом куски
	if(light){
		SDL_SetRenderDrawColor(ren.get(),254,254,0,255);

	} else {
		SDL_SetRenderDrawColor(ren.get(), 1, 0, 100, 255);
	}
	for(int i = 80; i <= 200; i += 100){
		for(int j = 299; j <= 399; j += 100){
			SDL_Rect qw{i, j, 80, 80};
			SDL_RenderFillRect(ren.get(),&qw);
		}
	}

//		дверь
	SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 255);
	r1 = {300, 289, 130,285};
	SDL_RenderFillRect(ren.get(), &r1);
//		дверь в двери
	SDL_SetRenderDrawColor(ren.get(), 255, 150, 11, 255);
	r1 = {310, 309, 110,265};
	SDL_RenderFillRect(ren.get(), &r1);

//		это видимо нужно для того, чтобы рисовать крышу
	int x1=39;
	int x2=459;
	SDL_SetRenderDrawColor(ren.get(),237,186,0,255);
	for(int i=270;i>90;i--){

		SDL_RenderDrawLine(ren.get(),x1,i,x2,i);
		if(x1==x2){
			break;
		}
		x1+=1;
		x2-=2;
	}
//		трава
	std::minstd_rand gen(time(nullptr));
//		int valueStone = min + (gen() % (max - min + 1));
	for(int i = 10; i < 790; i += 15){
		SDL_SetRenderDrawColor(ren.get(),0,150,54,255);
		SDL_RenderDrawLine(ren.get(),i, 574, i, 544);
		SDL_RenderDrawLine(ren.get(),i+1, 574, i+1, 544);
		SDL_RenderDrawLine(ren.get(),i, 574, i-3, 560);
		SDL_RenderDrawLine(ren.get(),i, 570, i+5, 560);
		SDL_SetRenderDrawColor(ren.get(),(1 + (gen() % 5)) * 51, (1 + (gen() % 5)) * 51,(1 + (gen() % 5)) * 51, 255);
		for(int j = 0; j < 8; j++){
			SDL_RenderDrawLine(ren.get(), i-4, 544-j,i+4,544-j);
		}
	}
}

void render_bird(){
	SDL_Rect r_bird{bird_x,bird_y,94, 64};
	auto flip = bird_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(ren.get(), bird.get(), nullptr, &r_bird, 0., nullptr, flip);
}
void render_dog(){
	SDL_Rect r_dog{dog_x,dog_y,144, 104};
	auto flip = dog_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(ren.get(), dog.get(), nullptr, &r_dog, 0., nullptr, flip);
//	SDL_RenderCopy(ren.get(), dog.get(), nullptr, &r_dog);
}

void render_smoke(){
//Случайное распределение по направлениям по осям x и y
	std::uniform_int_distribution<> xd(-2,4), yd(-5, 1);
	for(auto&& r: smoke){
		SDL_RenderCopy(ren.get(), smoketex.get(), nullptr, &r);
		r.x += xd(rnd);
		r.y += yd(rnd);
		r.w += 2;
		r.h += 2;
		if (r.x >= W || r.y >= H || r.x < -r.w || r.y < -r.h){
			r.x = SMOKE_X;
			r.y = SMOKE_Y;
			r.w = SMOKE_W;
			r.h = SMOKE_H;
		}
	}

}
void render(){
	render_background();
	render_smoke();
	render_scene();
	render_bird();
	render_dog();
	SDL_RenderPresent(ren.get());
}

void main_loop(){
	SDL_Event e;
	auto keys = SDL_GetKeyboardState(nullptr);
	for(;;){
		while(SDL_PollEvent(&e)){
			if(e.type==SDL_QUIT){exit(0);}
			else if (e.type == SDL_KEYDOWN){
				if(e.key.keysym.scancode == SDL_SCANCODE_L) light = ! light;
			}
		}
//		птица
		bird_x += bird_right? -4: 4;
		if(keys[SDL_SCANCODE_RIGHT]) {
			bird_right = false;
		}
		if(keys[SDL_SCANCODE_LEFT]) {
			bird_right = true;
		}
		if(keys[SDL_SCANCODE_UP]) bird_y-=2;
		if(keys[SDL_SCANCODE_DOWN]) bird_y+=2;
		if(bird_y < 0) bird_y = 0;
		if(bird_y >= 150 - 64) bird_y = 150 - 64;
		if(bird_x > W) bird_x = -64;
		if(bird_x < -64) bird_x = W;
//		пес
		if(keys[SDL_SCANCODE_D]) {
			dog_x+=5;
			dog_right = true;
		}
		if(keys[SDL_SCANCODE_A]){
			dog_x-=5;
			dog_right = false;
		}
		if(dog_x < 0) dog_x = 0;
		if (dog_x >= W -144) dog_x = W-144-1;
		render();

	}
}
int main(int, char**) {
	using std::cerr;
	using std::endl;
	//обработк ошибок
	try {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			SDL_DIE("SDL_Init");
		//cerr << "SDL_Init: " << SDL_GetError() << endl;
		//exit(1);
		//создание самого окна
		win = WinPtr(SDL_CreateWindow("SDL Test", //заголовок
				SDL_WINDOWPOS_CENTERED, //положение
				SDL_WINDOWPOS_CENTERED, W, H, //размеры
				SDL_WINDOW_SHOWN), SDL_DestroyWindow); //видимость окна после создания
		if (win == nullptr)
			SDL_DIE("SDL_CreateWindow");
//			cerr << "SDL_CreateWindow: " << SDL_GetError() << endl;
//			exit(1);
		ren = RenPtr(SDL_CreateRenderer(win.get(), -1, //порядковый номер видюхи - в данном случае - первая попавшаяся вид
				SDL_RENDERER_ACCELERATED | //с поддержкой аппаратного ускорения
						SDL_RENDERER_PRESENTVSYNC), //заблокирует частоту кадров на той, которую поддерживает монитор
		SDL_DestroyRenderer);

		if (ren == nullptr)
			SDL_DIE("SDL_CreateRenderer");
//			cerr << "SDL_CreateRenderer: " << SDL_GetError() << endl;
//			exit(1);

		//под текстуры
		bird = load_texture("bird.png");
		dog = load_texture("11.png");
		smoketex = load_texture("smoke.png");
		background = load_texture("background.png");
		background_night = load_texture("background_night.png");
		smoke.resize(50);
//		запихиываем все клубы дыма внутрь трубы
		for(auto&& r: smoke){
			r.x = SMOKE_X;
			r.y = SMOKE_Y;
			r.w = SMOKE_W;
			r.h = SMOKE_H;
		}
		main_loop();
	} catch (const std::exception& e) {
		std::cerr << "Произошла ошибка:\n" << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "Произошла неизвестная ошибка:\n" << std::endl;
		return 1;
	}
	//	SDL_Delay(3000);
	return 0;
}

