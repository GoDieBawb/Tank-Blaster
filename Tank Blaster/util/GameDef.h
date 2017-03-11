#include "../entity/EntityManager.cpp"

struct Game {

	Node			   rootNode;
	InteractionManager im;
	EntityManager	   entm;
	Game();
	void printDataTree();

};

//Game Constructor passes interactionmanager to entity manager
Game::Game() : entm(im) {
	//Name Root Node
	rootNode.name = "Root Node";
	//Attach Player and Enemy Nodes to Root Node
	rootNode.attachChild(entm.fm.streetNode);	
	rootNode.attachChild(entm.pm.playerNode);
	rootNode.attachChild(entm.em.enemyNode);
	rootNode.attachChild(entm.fm.carNode);
}

//Used to Print Games Data 
void Game::printDataTree() {

	std::cout << "\nGame Data:\n";

	std::cout << rootNode.name 	  << std::endl;
	std::cout << entm.pm.playerNode.name  << std::endl;
	std::cout << entm.pm.player.tank.name << std::endl;
	std::cout << entm.pm.player.tank.body.name << std::endl;
	std::cout << entm.pm.player.tank.gun.name << std::endl;
	std::cout << entm.pm.player.tank.hatch.name << std::endl;

	std::cout << "\n";

}
