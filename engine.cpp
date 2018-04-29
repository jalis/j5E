#include <cmath>
#include <iostream>

#include "engine.h"

namespace j5E {
	std::vector<std::unique_ptr<Entity>> Entity::eList;
	int Entity::nextID=0;

	int intersectLineCircle(line l, circle ci, point intersections[2]) {
		point d = l[0] - l[1]; // Direction vector of line, calculated using vector substraction
		point f = l[1] - ci.p; // vector from circle's center to start of line, also vector substraction
		// dividing equation into multiple variables for reuse and readability
		double a = d.dot(d); // dot product of 'd' with itself
		double b = 2*f.dot(d); // dot product of 'f' and 'd', multiplied by two(2)
		double c = f.dot(f) - ci.r*ci.r; //dot product of 'f' with itself, minus the square of the circle's radius ('ci.r')

		double discriminant = b*b-4*a*c;

		std::cout << "\rd:(" << d.x << "," << d.y << "), f:(" << f.x << "," << f.y << "), a:"<< a << ", b:" << b << ", c:" << c << ", discriminant:" << discriminant;
		if (discriminant < 0)
			return 0;
		
		discriminant=std::sqrt(discriminant);
		
		double t1 = (-b - discriminant)/(2*a);
		double t2 = (-b + discriminant)/(2*a);

		intersections[0]={l[1].x + t2 * d.x, l[1].y + t2 * d.y};
		intersections[1]={l[1].x + t1 * d.x, l[1].y + t1 * d.y};

		if(t1 >= 0 && t1 <= 1) 
			return 2;
		if(t2 >= 0 && t2 <= 1)
			return 1;
		return 0;

/*		double dx, dy, A, B, C, det, t;

		dx = l[1].x - l[0].x;
		dy = l[1].y - l[0].y;

		A = dx*dx + dy*dy;
		B = 2 * (dx * (l[0].x - ci.p.x) + dy * (l[0].y - ci.p.y));
		C = (l[1].x - ci.p.x) * (l[0].x - ci.p.x) + (l[0].y - ci.p.y) * (l[0].y - ci.p.y) - ci.r*ci.r;

		det = B * B - 4 * A * C;
		if ((A <= 0.0000001) || (det < 0)) {
			return 0;
		}
		else if(det ==0) {
			t = -B / (2 * A);
			intersections[0] = {l[0].x + t * dx, l[0].y + t * dy};
			return 1;
		}
		else {
			t = (double)((-B + std::sqrt(det)) / (2 * A));
			intersections[0] = {l[0].x + t * dx, l[0].y + t * dy};
			t = (double)((-B - std::sqrt(det)) / (2 * A));
			intersections[1] = {l[0].x + t * dx, l[0].y + t * dy};
			return 2;
		} */

/*		double m = (l[1].y - l[0].y) / (l[1].x - l[0].x);
		double b = l[0].y - (m * l[0].x);

		double A = 1+m*m;
		double B = -2*ci.p.x + 2*m*b - 2*ci.p.y*m;
		double C = ci.p.x*ci.p.x + b*b + ci.p.y*ci.p.y - 2*ci.p.y*b - ci.r*ci.r;

		double delta = B*B - 4*A*C;

		if(delta<0){
			return false;
		}

		double x1=(-B+std::sqrt(delta))/(2*A);
		double x2=(-B-std::sqrt(delta))/(2*A);

		double y1=m*x1+b;
		double y2=m*x2+b;

		point int1;
		point int2;

		int1.x=x1;
		int1.y=y1;
		int2.x=x2;
		int2.y=y2;

		intersections[0]=int1;
		intersections[1]=int2;
		return true;*/
	}

	Entity::Entity() {
		id=nextID;
		eList.push_back(std::unique_ptr<Entity>(this));
		++nextID;
		alive=true;
		std::cout << "new entity " << id << std::endl;
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