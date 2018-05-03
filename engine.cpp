#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

#include "engine.h"

namespace j5E {
	std::vector<std::unique_ptr<Entity>> Entity::eList;
	int Entity::nextID=0;

	int intersectLineCircle(line l, circle ci, point intersections[2]) {
		point d = l[1] - l[0]; // Direction vector of line, calculated using vector substraction
		point f = l[0] - ci.p; // vector from circle's center to start of line, also vector substraction
		// dividing equation into multiple variables for reuse and readability
		double a = d.dot(d); // dot product of 'd' with itself
		double b = 2*f.dot(d); // dot product of 'f' and 'd', multiplied by two(2)
		double c = f.dot(f) - ci.r*ci.r; //dot product of 'f' with itself, minus the square of the circle's radius ('ci.r')

		double discriminant = b*b-4*a*c;

#ifdef DEBUG
//		std::cout << "d:(" << d.x << "," << d.y << "), f:(" << f.x << "," << f.y << "), a:"<< a << ", b:" << b << ", c:" << c << ", discriminant:" << discriminant << "       ";
#endif
		if (discriminant < 0)
			return 0;
		
		discriminant=std::sqrt(discriminant);
		
		double t1 = (-b - discriminant)/(2*a);
		double t2 = (-b + discriminant)/(2*a);

		intersections[0]={l[0].x + t1 * d.x, l[0].y + t1 * d.y};
		intersections[1]={l[0].x + t2 * d.x, l[0].y + t2 * d.y};

#ifdef DEBUG
//		std::cout << "t1:" << t1 << " t2:" << t2;
#endif
		
		if(t1<=1 && t1>=0) {
			if(t2<=1)
				return 2; //2 intersections, stored in intersections[0..1]
			return 1; //1 intersection, stored in intersections[0]
		}
		if(t2>=0 && t2<=1)
			return 3; //1 intersection, stored in intersections[1]
		return 0;
	}

	Entity::Entity() {
		id=nextID;
		eList.push_back(std::unique_ptr<Entity>(this));
		++nextID;
		alive=true;
		
#ifdef DEBUG		
		std::cout << "new entity " << id << std::endl;
#endif
	}


	bool collisionLineArc(line l, circle c, point a, point b) {
		double A=std::atan2(a.y-c.p.y, a.x-c.p.x); //Angle of a on circle
		double B=std::atan2(b.y-c.p.y, b.x-c.p.x); //Angle of b on circle

		point cols[2];
		int n=intersectLineCircle(l, c, cols);

		if(n==1) {
			double D1=std::atan2(cols[0].y-c.p.y, cols[0].x-c.p.x);
			return (D1 < B && (D1 > A || B < A)) || (D1 > A && B < A);
		}
		if(n==2) {
			double D1=std::atan2(cols[0].y-c.p.y, cols[0].x-c.p.x);
			double D2=std::atan2(cols[1].y-c.p.y, cols[1].x-c.p.x);
			return ((D1 < B && (D1 > A || B < A)) || (D1 > A && B < A)) || (D2 < B && (D2 > A || B < A)) || (D2 > A && B < A);
		}
		if(n==3) {
			double D1=std::atan2(cols[1].y-c.p.y, cols[1].x-c.p.x);
			return (D1 < B && (D1 > A || B < A)) || (D1 > A && B < A);
		}
		return false;
	}

#ifdef DEBUG
	void Entity::listEntities() {
		int size=eList.size();
		for(int i=0;i<size;++i) {
			std::cout << "entity " << eList.at(i).get()->id << ", alive: " << eList.at(i).get()->alive << std::endl;
		}
	}
	std::vector<std::unique_ptr<Entity>> *Entity::getEntities() {
		return &eList;
	}
#endif
}