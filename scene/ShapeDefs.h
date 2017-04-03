//Basic 3f Vector
struct Vec {
	float x, y, z;
	Vec() {x=0;y=0;z=0;}
	Vec(float x, float y, float z) {this->x = x; this->y = y; this->z=z;};
};

//Abstract Spatial can be either Node or Spatial
class Node;
class Spatial {

	public:
		Spatial();
		Vec location;
		float angle;
		std::string name;
		Node *parent;
		Node getParent();

};

Spatial::Spatial() {
	angle = 0;
}

//Shape is a type of spatial that has an actual Geometry being drawn
class Shape: public Spatial {

	public:
		float width, height;
		float radius;
		Vec color;
		Shape();

};


//A Node is a Spatial that holds other Spatials
class Node: public Spatial {

	public:
		Node();
		Node  *nodeArr[15];
		Shape *shapeArr[15];
		int  shapeCount;
		int  nodeCount;
		void attachChild(Shape &s);
		void attachChild(Node  &n);
		void detachChild(Node &n);
		void detachChild(Shape &s);  
		void printTree();

};

Shape::Shape() {
	name = "Shape";
}

//Construct Node
Node::Node() {
	name 	   = "Node";
	shapeCount = 0;
	nodeCount  = 0;
}

//Attach Shape to Node
void Node::attachChild(Shape &s) {
	shapeArr[shapeCount] = &s;
	shapeCount++;
	s.parent = this;
}

//Attach Node to Node
void Node::attachChild(Node &n) {
	nodeArr[nodeCount] = &n;
	nodeCount++;
	n.parent = this;
}

//Remove Shape Child from Node
void Node::detachChild(Shape &s) {

	for (int i =0; i < shapeCount; i++) {

		if (shapeArr[i] == &s) {
			shapeArr[i] = shapeArr[shapeCount];
			shapeCount--;
			return;
		}

	}

	std::cout << "CHILD NOT FOUND!\n";

}
 
//Remove Node Child From Node
void Node::detachChild(Node &n) {

	for (int i =0; i < nodeCount; i++) {

		if (nodeArr[i] == &n) {
			nodeArr[i] = nodeArr[nodeCount-1];
			nodeCount--;	
			return;
		}

	}

	std::cout << "CHILD NOT FOUND!\n";

}

//Recusrive Function to Print Nodes Children
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

//Particle
struct Particle {
	Shape s;
	Vec velocity;
};
