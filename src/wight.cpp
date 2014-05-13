#include "game\game.h"
#include <list>
#include "game\map_generation\Leaf.hpp"

int main(int argc, char** argv)
{
	LeafPtr<int> a = std::make_shared<Leaf<int>>(0, 0, 0, 0);


//	Game game;
//	game.Run();
	return 0;
}

