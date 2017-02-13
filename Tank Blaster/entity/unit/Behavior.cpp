//Abstract Structure with a single function
struct Behavior {
	virtual void behave(Node &model) = 0;
	virtual ~Behavior(){};
};
