#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>


#define KEY_UP 111
#define KEY_RIGHT 114
#define KEY_DOWN 116
#define KEY_LEFT 113
#define KEY_ESC 9

namespace mygame {

class GameDisplay {
public:
	GameDisplay();
	~GameDisplay();

	Display *getDisplay();
	
private:
	Display *display_;
	int screen_;
	Window window_;

};

GameDisplay::GameDisplay(){

	display_= XOpenDisplay(NULL);
	if (display_ == NULL)
	{
		throw std::runtime_error("Unable to open the display");
	}

	screen_ = DefaultScreen(display_);

	window_ = XCreateSimpleWindow(display_, RootWindow(display_, screen_), 0, 0, 100, 100, 1,
			BlackPixel(display_, screen_), WhitePixel(display_, screen_));

	XSelectInput(display_, window_, KeyPressMask);	
	XMapWindow(display_, window_);
}

GameDisplay::~GameDisplay(){
	XCloseDisplay(display_);
}

Display *GameDisplay::getDisplay(){
	return display_;
}

class Game{
public:
	Game();
	
	void run();

private:
	GameDisplay gamedisplay_;
	XEvent event_;
	bool is_running_ = true;


	bool getEvent();
	void handleEvent();
};

Game::Game()
{
}

void Game::run()
{
	while(is_running_)
	{
    if(getEvent())
    {
      handleEvent();
    }

	}

}

bool Game::getEvent()
{
    if (XPending(gamedisplay_.getDisplay()))
    {
      XNextEvent(gamedisplay_.getDisplay(), &event_);
      printf("EVENT: %d\n", event_.type);
      return true;
    }
    return false;
}

void Game::handleEvent()
{
	if (event_.type == KeyPress)
  {
		switch(event_.xkey.keycode)
		{
			case KEY_UP	: printf("KEY_UP\n"); break;
			case KEY_ESC	: printf("KEY_ESC\n"); is_running_ = false;
		}
	}

}


}

int main()
{
  mygame::Game game;

  game.run();

	return 0;
}

