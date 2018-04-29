#include <iostream>

#include "creature.h"

namespace j5E {
	std::vector<Creature*> Creature::cList;

	Creature::Creature(circle c) {
		_pos=c;
		cList.push_back(this);
	}
	std::vector<Creature*>* Creature::getCreatures() {
		return &cList;
	}

	
	bool Creature::tryMove(double x, double y, std::vector<point*> *collisions) {
		line move( {_pos.p.x, _pos.p.y}, { x, y});

		int i=0;
		int n=0;

		point col[2];
		
		for(auto cr : cList) {
			if(cr->id != id) {
				circle tmp=cr->_pos;
				tmp.r+=_pos.r;
				n=intersectLineCircle(move, tmp, col);
				if(n>=1) collisions->push_back(new point(col[0]));
				if(n==2) collisions->push_back(new point(col[1]));
#ifdef DEBUG
				//std::cout << col[0].x << ", " << col[0].y << "; " << col[1].x << ", " << col[1].y << std::endl;
#endif
			}
		}
		return true;
	}  //
	circle Creature::getCircle() {
		return _pos;
	}

#ifdef DEBUG
	void Creature::listCreatures() {
		int size=cList.size();
		for(int i=0;i<size;++i) {
			std::cout << "entity " << cList.at(i)->id << ", alive: " << cList.at(i)->alive << std::endl;
		}
	}
#endif
}