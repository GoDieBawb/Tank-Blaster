/**
 * Name:        Obosa Osagie-Amayo
 * Description: Obosa Osagie-Amayo's code for Tank Blaster
 **/

// Sound =======================================================================
#ifdef noaudio

void doExplosion(){}
void doMusic(){}
void doShoot(){}
void initSound(){}
void cleanUpSound(){}

#else

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <AL/alut.h>
#include <pthread.h>

//Buffers hold the sound information.
ALuint alBuffer[2];
//Source refers to the sound.
ALuint alSource[2];

ALuint alBufferExplode, alBufferMusic, alBufferShoot;
ALuint alSourceExplode, alSourceMusic, alSourceShoot;

void initExplosion();
void initMusic();

void initSound() {

  alutInit(0, NULL);
  if (alGetError() != AL_NO_ERROR) {
    printf("ERROR: alutInit()\n");
    return;
  }
  //Clear error state.
  alGetError();

  //Setup the listener.
  //Forward and up vectors are used.
  float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
  alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
  alListenerfv(AL_ORIENTATION, vec);
  alListenerf(AL_GAIN, 1.0f);

  //Buffer holds the sound information.
  alBufferExplode = alutCreateBufferFromFile("./Explode.wav");

  //Source refers to the sound.
  //Generate a source, and store it in a buffer.
  alGenSources(1, &alSourceExplode);
  alSourcei(alSourceExplode, AL_BUFFER, alBufferExplode);
  alSourcef(alSourceExplode, AL_GAIN, .5f);
  alSourcef(alSourceExplode, AL_PITCH, 1.0f);
  alSourcei(alSourceExplode, AL_LOOPING, AL_FALSE);

  if (alGetError() != AL_NO_ERROR) {
    printf("ERROR: setting source\n");
    return;
  }

  alBufferMusic   = alutCreateBufferFromFile("./Home_Base_Groove.wav");
  //Generate a source, and store it in a buffer.
  alGenSources(1, &alSourceMusic);
  alSourcei(alSourceMusic, AL_BUFFER, alBufferMusic);
  alSourcef(alSourceMusic, AL_GAIN, 5.0f);
  alSourcef(alSourceMusic, AL_PITCH, 1.0f);
  alSourcei(alSourceMusic, AL_LOOPING, AL_TRUE);
  if (alGetError() != AL_NO_ERROR) {
  printf("ERROR: setting source\n");
    return;
  }

  alBufferShoot   = alutCreateBufferFromFile("./Shoot.wav");
  //Generate a source, and store it in a buffer.
  alGenSources(1, &alSourceShoot);
  alSourcei(alSourceShoot, AL_BUFFER, alBufferShoot);
  alSourcef(alSourceShoot, AL_GAIN, .1f);
  alSourcef(alSourceShoot, AL_PITCH, 1.0f);
  alSourcei(alSourceShoot, AL_LOOPING, AL_FALSE);
  if (alGetError() != AL_NO_ERROR) {
    printf("ERROR: setting source\n");
    return;
  }

}


void cleanUpSound() {

  //First delete the source.
  alDeleteSources(1, &alSourceExplode);
  alDeleteSources(1, &alSourceMusic);
  alDeleteSources(1, &alSourceShoot);
  //Delete the buffer.
  alDeleteBuffers(1, &alBufferExplode);
  alDeleteBuffers(1, &alBufferMusic);
  alDeleteBuffers(1, &alBufferShoot);
  //Close out OpenAL itself.
  //Get active context.
  ALCcontext *Context = alcGetCurrentContext();
  //Get device for active context.
  ALCdevice *Device = alcGetContextsDevice(Context);
  //Disable context.
  alcMakeContextCurrent(NULL);
  //Release context(s).
  alcDestroyContext(Context);
  //Close device.
  alcCloseDevice(Device);

}

void playSound(ALuint source){
	alSourcePlay(source);
}

pthread_t soundThread[2];

void doMusic() {
	alSourcePlay(alSourceMusic);
}

void doShoot() {
	playSound(alSourceShoot);
}

void doExplosion() {
	playSound(alSourceExplode);
}
#endif

// Player Manager ==============================================================

// Constructor initializes data members
PlayerManager::PlayerManager(InteractionManager &i) {

  // Name Player Node
  playerNode.name = "Player Node";
  // Attach player tank to player node
  playerNode.attachChild(player.tank);
  // Set interaction manager
  im = &i;
}

void PlayerManager::checkLoss() {

  if (player.health <= 0 || player.carsLeft <= 0) {
    player.isDead = true;

    if (player.health <= 0) {
      player.die();
      playerNode.detachChild(player.tank);
    }
  }
}

// Uses InteractionManager to listen for key presses
void PlayerManager::actOnKeys() {

  Tank *tank = &player.tank;

  if (im->up && im->left) {
    tank->moveUpLeft();
  }

  else if (im->up && im->right) {
    tank->moveUpRight();
  }

  else if (im->up) {
    tank->moveUp();
  }

  else if (im->down && im->left) {
    tank->moveDownLeft();
  }

  else if (im->down && im->right) {
    tank->moveDownRight();
  }

  else if (im->down) {
    tank->moveDown();
  }

  else if (im->left) {
    tank->moveLeft();
  }

  else if (im->right) {
    tank->moveRight();
  }

  if (im->space) {
    if (!shootPressed) {
      bullets[bulletCount] = tank->shoot();
      doShoot();
      bulletCount++;
      shootPressed = true;
    }
  } else {
    if (shootPressed)
      shootPressed = false;
  }
}

// Called on Update Loop
void PlayerManager::update() {
  actOnKeys();
  checkLoss();
}

void Hud::checkDisplays() {
  int carsLeft = game.entm.pm.player.carsLeft;
  int health   = game.entm.pm.player.health;

  switch (carsLeft) {
  case 0:
    if (hudNode.hasChild(car3))
      hudNode.detachChild(car3);
    game.entm.pm.player.isDead = true;
    break;
  case 1:
    if (hudNode.hasChild(car2))
      hudNode.detachChild(car2);
    break;
  case 2:
    if (hudNode.hasChild(car1))
      hudNode.detachChild(car1);
    break;
  }

  switch (health) {
  case 0:
    if (hudNode.hasChild(lifeDisplay3))
      hudNode.detachChild(lifeDisplay3);
    game.entm.pm.player.isDead = true;
    break;
  case 1:
    if (hudNode.hasChild(lifeDisplay2))
      hudNode.detachChild(lifeDisplay2);
    break;
  case 2:
    if (hudNode.hasChild(lifeDisplay1))
      hudNode.detachChild(lifeDisplay1);
    break;
  }
}

void Hud::checkForRestart() {

  if (game.im.enter) {

    Player *player   = &game.entm.pm.player;
    player->score    = 0;
    player->health   = 3;
    player->carsLeft = 3;
    player->isDead   = false;
    bulletCount      = 0;
    game.entm.em.clearEnemies();
    hudNode.detachChild(promptShape);
    textShape.location.x = WINDOW_WIDTH / 3.5;
    textShape.location.y = WINDOW_HEIGHT - bar.height / 4;

    if (!game.entm.pm.playerNode.hasChild(player->tank)) {
      game.entm.pm.playerNode.attachChild(player->tank);
    }

    if (!hudNode.hasChild(car1)) {
      hudNode.attachChild(car1);
    }

    if (!hudNode.hasChild(car2)) {
      hudNode.attachChild(car2);
    }

    if (!hudNode.hasChild(car3)) {
      hudNode.attachChild(car3);
    }

    if (!hudNode.hasChild(lifeDisplay1)) {
      hudNode.attachChild(lifeDisplay1);
    }

    if (!hudNode.hasChild(lifeDisplay2)) {
      hudNode.attachChild(lifeDisplay2);
    }

    if (!hudNode.hasChild(lifeDisplay3)) {
      hudNode.attachChild(lifeDisplay3);
    }
  }
}

// HUD =========================================================================
Hud::Hud() : lifeDisplay1(Vec(0, 0, 0)), lifeDisplay2(Vec(30, 0, 0)),
  lifeDisplay3(Vec(60, 0, 0)), car1(Vec(0, 0, 0)), car2(Vec(0, 0, 0)),
  car3(Vec(0, 0, 0)) {

  lifeDisplay1.location.x = -WINDOW_WIDTH / 2 + lifeDisplay1.body.width;
  lifeDisplay2.location.x = -WINDOW_WIDTH / 2 + (lifeDisplay2.body.width * 2);
  lifeDisplay3.location.x = -WINDOW_WIDTH / 2 + (lifeDisplay3.body.width * 3);

  car1.angle = 90;
  car2.angle = 90;
  car3.angle = 90;

  car1.body.color  = blue;
  car1.front.color = blue;
  car1.back.color  = blue;

  car2.body.color  = green;
  car2.front.color = green;
  car2.back.color  = green;

  car3.body.color  = red;
  car3.front.color = red;
  car3.back.color  = red;

  car1.location.x = WINDOW_WIDTH / 2 - car1.body.width * 2;
  car2.location.x = WINDOW_WIDTH / 2 - car2.body.width * 3;
  car3.location.x = WINDOW_WIDTH / 2 - car3.body.width;

  bar.width  = WINDOW_WIDTH;
  bar.height = WINDOW_HEIGHT / 10;
  bar.color  = Vec(201, 208, 201);
  bar.angle  = 0;

  hudNode.location.y = WINDOW_HEIGHT - WINDOW_HEIGHT / 20;
  hudNode.location.x = WINDOW_WIDTH / 2;
  hudNode.attachChild(bar);
  hudNode.attachChild(lifeDisplay1);
  hudNode.attachChild(lifeDisplay2);
  hudNode.attachChild(lifeDisplay3);
  hudNode.attachChild(car1);
  hudNode.attachChild(car2);
  hudNode.attachChild(car3);

  textShape.width      = WINDOW_WIDTH / 5;
  textShape.height     = WINDOW_HEIGHT / 10;
  textShape.location.x = WINDOW_WIDTH / 3.5;
  textShape.location.y = WINDOW_HEIGHT - bar.height / 4;

  promptShape.width    = WINDOW_WIDTH / 3;
  promptShape.height   = WINDOW_HEIGHT / 5;
  promptShape.color    = Vec(201, 208, 201);
  promptShape.location = Vec(0, -WINDOW_HEIGHT / 2, 0);
  promptShape.angle    = 0;

  promptText.width      = WINDOW_WIDTH / 3;
  promptText.height     = WINDOW_HEIGHT / 5;
  promptText.location.x = WINDOW_WIDTH / 2 + promptShape.width / 2;
  promptText.location.y = WINDOW_HEIGHT / 2;

  hudNode.attachChild(promptShape);
}

void Hud::checkGameState() {

  bool isDead = game.entm.pm.player.isDead;

  if (isDead) {
    prompt();
    checkForRestart();
  }
}

void Hud::prompt() {

  writePromptText();
  if (!hudNode.hasChild(promptShape)) {
    hudNode.attachChild(promptShape);
    textShape.location.x = WINDOW_WIDTH / 2 + promptShape.width / 4;
    textShape.location.y = WINDOW_HEIGHT / 2;
  }
}

void Hud::writePromptText() {
  char buf[20];
  sprintf(buf, "Press Enter to Start");
  Rect r = boxToRect(promptText);
  ggprint16(&r, 32, 0x000000, buf);
}

void Hud::writeScoreText() {
  char buf[20];
  sprintf(buf, "Score: %d", game.entm.pm.player.score);
  Rect r = boxToRect(textShape);
  ggprint16(&r, 32, 0x000000, buf);
}

void Hud::update() {
  writeScoreText();
  checkDisplays();
  checkGameState();
}

Rect boxToRect(Shape &s) {

  Rect rect;
  rect.centerx = s.location.x;
  rect.centery = s.location.y;
  rect.width   = s.width;
  rect.height  = s.height;
  rect.bot     = s.location.y - s.height / 2;
  rect.top     = s.location.y + s.height / 2;
  rect.left    = s.location.x - s.width / 2;
  rect.right   = s.location.x + s.width / 2;

  return rect;
}

// Tank Behaviors ==============================================================

// Box Behavior
struct BoxBehavior : public Behavior {
  void behave(Node &model);
  BoxBehavior();
};

void BoxBehavior::behave(Node &model) {
  Tank &tank = (Tank &)model;
  int box    = rand() % 2;

  while (1) {
    if (box == 0) {
      tank.moveUp();
      box = 2;
    } else if (box == 1) {
      tank.moveUpRight();
      box = 2;
    }

    if (tank.location.x <= WINDOWS_WIDTH) {
      tank.moveUpRight();
    } else if (tank.location.x < (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) &&
               tank.location.y > (WINDOWS_HEIGHT / 2)) {
      tank.moveLeft();
    }

    if (tank.location.x <= (WINDOWS_WIDTH - 20) &&
        tank.location.y <= (WINDOWS_HEIGHT / 2)) {
      tank.moveUp();
    } else if (tank.location.x < (WINDOWS_WIDTH - 20) &&
               tank.location.y > (WINDOWS_HEIGHT / 2)) {
      tank.moveDown();
    }
  }
}

// Left, Right Behavior
struct LeftRightBehavior : public Behavior {
  void behave(Node &model);
  // BoxBehavior();
};

void LeftRightBehavior::behave(Node &model) {
  Tank &tank = (Tank &)model;
  int box = rand() % 2;

  while (1) {
    if (box == 0) {
      tank.moveLeft();
      box = 2;
    } else if (box == 1) {
      tank.moveRight();
      box = 2;
    }

    if (tank.location.x == WINDOWS_WIDTH - 20) {
      tank.moveLeft();
    } else if (tank.location.x == (WINDOWS_WIDTH - WINDOWS_WIDTH) + 20) {
      tank.moveRight();
    }
  }
}
