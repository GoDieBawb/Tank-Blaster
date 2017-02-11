struct Vec {
	float x, y, z;
	Vec() {x=0;y=0;z=0;}
	Vec(float x, float y, float z) {this->x = x; this->y = y; this->z=z;};
};

class Spatial {

	public:
		Vec location;
		float angle;
		std::string name;

};

class Shape: public Spatial {

	public:
		float width, height;
		float radius;
		Vec color;
		Shape();

};

Shape::Shape() {
	name = "Shape";
}

class Node: public Spatial {

	public:
		Node();
		Node  *nodeArr[10];
		Shape *shapeArr[10];
		int  shapeCount;
		int  nodeCount;
		void attachChild(Shape &s);
		void attachChild(Node  &n);
		void printTree();
		//Node(const Node &src) = delete;
		//Node &operator =(const Node &src) = delete;

};

Node::Node() {
	name 	   = "Node";
	shapeCount = 0;
	nodeCount  = 0;
}

void Node::attachChild(Shape &s) {
	shapeArr[shapeCount] = &s;
	shapeCount++;
}
 
void Node::attachChild(Node &n) {
	nodeArr[nodeCount] = &n;
	nodeCount++;
}

void Node::printTree() {

	std::cout << name << "\n";

	for (int i = 0; i < shapeCount; i++) {
		std::cout << shapeArr[i]->name << " ";
	}

	for (int i = 0; i < nodeCount; i++) {
		nodeArr[i]->printTree();
	}

	std::cout << "\n";

}

struct Particle {
	Shape s;
	Vec velocity;
};
