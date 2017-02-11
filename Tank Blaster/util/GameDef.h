#include "../entity/EntityManager.cpp"

struct Game {

	Node			   rootNode;
	InteractionManager im;
	EntityManager	   em;
	Game();
	void printDataTree();

};

Game::Game() : em(im) {
	rootNode.name = "Root Node";
	rootNode.attachChild(em.pm.playerNode);
}

void Game::printDataTree() {

	std::cout << "\nGame Data:\n";

	std::cout << rootNode.name 	  << std::endl;
	std::cout << em.pm.playerNode.name  << std::endl;
	std::cout << em.pm.player.tank.name << std::endl;
	std::cout << em.pm.player.tank.body.name << std::endl;
	std::cout << em.pm.player.tank.gun.name << std::endl;
	std::cout << em.pm.player.tank.hatch.name << std::endl;

	std::cout << "\n";

}
