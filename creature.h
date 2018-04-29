#pragma once

#include <vector>

#include "engine.h"

namespace j5E {

	class Creature : private Entity {
		private:
			static std::vector<Creature*> cList;
			
			circle _pos;

		public:
			static std::vector<Creature*>* getCreatures();
			Creature(circle);

			bool tryMove(double, double, std::vector<point*> *collisions);
			circle getCircle();

#ifdef DEBUG
			static void listCreatures();
#endif
	};
}