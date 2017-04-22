/**
 * Name:        Obosa Osagie-Amayo
 * Description: Obosa Osagie-Amayo's code for Tank Blaster
 **/

#include <stdlib.h>

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 600

// Player Manager ==============================================================

// Constructor initializes data members
PlayerManager::PlayerManager(InteractionManager &i)
{

	// Name Player Node
	playerNode.name = "Player Node";
	// Attach player tank to player node
	playerNode.attachChild(player.tank);
	// Set interaction manager
	im = &i;

}

// Uses InteractionManager to listen for key presses
void PlayerManager::actOnKeys()
{

	Tank* tank = &player.tank;

	if (im->up && im->left)
  {
		tank->moveUpLeft();
	}

	else if (im->up && im->right)
  {
		tank->moveUpRight();
	}

	else if (im->up)
  {
		tank->moveUp();
	}

	else if (im->down && im->left)
  {
		tank->moveDownLeft();
	}

	else if (im->down && im->right)
  {
		tank->moveDownRight();
	}

	else if (im->down)
  {
		tank->moveDown();
	}

	else if (im->left)
  {
		tank->moveLeft();
	}

	else if (im->right)
  {
		tank->moveRight();
	}

	if (im->space)
  {
		bullets[bulletCount] = tank->shoot();
		bulletCount++;
		im->space = false;
	}

}

// Called on Update Loop
void PlayerManager::update()
{
	actOnKeys();
}

// HUD =========================================================================
Hud::Hud(Node &rootNode) : lifeDisplay(Vec(0,0,0))
{

	lifeDisplay.location.x = -WINDOW_WIDTH/2 + lifeDisplay.body.width;

	bar.width  = WINDOW_WIDTH;
	bar.height = WINDOW_HEIGHT/10;
	bar.color  = red;
	bar.angle  = 0;

	hudNode.location.y  = WINDOW_HEIGHT - WINDOW_HEIGHT/20;
	hudnode.location.x  = window_width/2;
	hudNode.attachChild(bar);
	hudNode.attachChild(lifeDisplay);

	textShape.width      = WINDOW_WIDTH/5;
	textShape.height     = WINDOW_HEIGHT/10;
	textShape.location.x = WINDOW_WIDTH/5;
	textShape.location.y = WINDOW_HEIGHT;

	rootNode.attachChild(hudNode);

}

void Hud::writeTestText()
{
	Rect r = boxToRect(textShape);
	ggprint8b(&r, 32, 0x00dddd00, "Tank Blaster");
}

void Hud::update()
{
	writeTestText();
}

Rect boxToRect(Shape &s)
{

	Rect rect;
	rect.centerx = s.location.x;
	rect.centery = s.location.y;
	rect.width	 = s.width;
	rect.height  = s.height;
	rect.bot	   = s.location.y - s.height/2;
	rect.top 	   = s.location.y + s.height/2;
	rect.left    = s.location.x - s.width/2;
	rect.right   = s.location.x + s.width/2;

	return rect;
}


// Tank Behaviors ==============================================================

// Box Behavior
struct BoxBehavior : public Behavior
{
  void behave (Node &model);
  BoxBehavior();
};

void BoxBehavior::behave (Node &model)
{
  Tank &tank = (Tank&) model;
  int box = rand() % 2;

  while(1)
  {
	  if (box == 0)
    {
      tank.moveUp();
      box = 2;
    }
    else if (box == 1)
    {
      tank.moveUpRight();
      box = 2;
    }

    if (tank.location.x <= WINDOWS_WIDTH)
    {
      tank.moveUpRight();
    }
    else if (tank.location.x < (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) &&
      tank.location.y > (WINDOWS_HEIGHT/2))
    {
      tank.moveLeft();
    }

    if (tank.location.x <= (WINDOWS_WIDTH - 20) &&
      tank.location.y <= (WINDOWS_HEIGHT/2))
    {
      tank.moveUp();
    }
    else if (tank.location.x < (WINDOWS_WIDTH - 20) &&
      tank.location.y > (WINDOWS_HEIGHT/2))
    {
      tank.moveDown();
    }
  }
}


// Left, Right Behavior
struct LeftRightBehavior: public Behavior
{
  void behave (Node &model);
  BoxBehavior();
};

void LeftRightBehavior::behave (Node &model)
{
  Tank &tank = (Tank&) model;
  int box    = rand() % 2;

  while(1)
  {
	  if (box == 0)
    {
      tank.moveLeft();
      box = 2;
    }
    else if (box == 1)
    {
      tank.moveRight();
      box = 2;
    }

    if (tank.location.x == windows_width - 20)
    {
      tank.moveLeft();
    }
    else if (tank.location.x == (WINDOWS_WIDTH-WINDOWS_WIDTH) + 20)
    {
      tank.moveRight();
    }
  }
}
