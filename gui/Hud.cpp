Rect boxToRect(Shape &s);

class Hud {

	private:
		Shape bar;
		Shape textShape;
		Node  hudNode;
		Tank  lifeDisplay;
	public:
		Hud(Node &rootNode);
		void writeTestText();
		void update();

};

Hud::Hud(Node &rootNode) : lifeDisplay(Vec(0,0,0)) {

	lifeDisplay.location.x = -WINDOW_WIDTH/2 + lifeDisplay.body.width;

	bar.width  = WINDOW_WIDTH;
	bar.height = WINDOW_HEIGHT/10;
	bar.color  = red;
	bar.angle  = 0;

	hudNode.location.y  = WINDOW_HEIGHT - WINDOW_HEIGHT/20;
	hudNode.location.x  = WINDOW_WIDTH/2;
	hudNode.attachChild(bar);
	hudNode.attachChild(lifeDisplay);

	textShape.width        = WINDOW_WIDTH/5;
	textShape.height       = WINDOW_HEIGHT/10; 
	textShape.location.x   = WINDOW_WIDTH/5;
	textShape.location.y   = WINDOW_HEIGHT;

	rootNode.attachChild(hudNode);

}

void Hud::writeTestText() {
	Rect r = boxToRect(textShape);
	ggprint8b(&r, 32, 0x00dddd00, "Test Text Here");
}

void Hud::update() {
	writeTestText();
}

Rect boxToRect(Shape &s) {

	Rect rect;
	rect.centerx = s.location.x;
	rect.centery = s.location.y;
	rect.width	 = s.width;
	rect.height  = s.height;
	rect.bot	 = s.location.y - s.height/2;
	rect.top 	 = s.location.y + s.height/2;
	rect.left    = s.location.x - s.width/2;
	rect.right   = s.location.x + s.width/2;
	return rect;

}
