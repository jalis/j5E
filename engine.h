#pragma once

#include <string>
#include <vector>
#include <memory>

namespace j5E {
	struct point {
		double x=0.0;
		double y=0.0;
		point operator +(point a) {
			return point(x+a.x, y+a.y);
		}
		point operator -(point a) {
			return point(x-a.x, y-a.y);
		}
		double dot(point a) {
			return (a.x*x + a.y*y);
		}
		point operator=(point a) {
			x=a.x;
			y=a.y;
			return *this;
		} 
		point operator=(double a[2]) {
			x=a[0];
			y=a[1];
			return *this;
		}
		point() {}; 
		point(double _x, double _y) {
			x=_x;
			y=_y;
		}
	};

	struct circle {
		point p;
		double r=1.0;
		circle() {};
		circle(double _x, double _y, double _r) {
			p=point(_x, _y);
			r=_r;
		}
	};

	struct line {
		public:
			point p[2];
			point operator [](int i) const {
				return p[i];
			}
			point &operator [](int i) {
				return p[i];
			}
			line() {};
			line(double a[2], double b[2]) {
				p[0]=a;
				p[1]=b;
			}
			line(point a, point b) {
				p[0]=a;
				p[1]=b;
			}
	};

	class Entity { //entity container
		private:
			static std::vector<std::unique_ptr<Entity>> eList;
			static int nextID;

		protected:
			bool alive;
			int id;
			std::string type;

		public:
			Entity();
#ifdef DEBUG
			static void listEntities();
			static std::vector<std::unique_ptr<Entity>> *getEntities();
#endif
	};

	//Returns intersection type, '1' means 1 intersection stored in point[0], '2' means 2 intersections std in point[0..1], '3' means 1 intersection stored in point[1]
	int intersectLineCircle(line, circle, point[2]);

	//Checks for collision between line and a clockwise arc defined by circle and the arc beginning point and end point
	bool collisionLineArc(line, circle, point, point); //First argument is the line, second is the arc's center, last two are start and end points of the arc

/*	//Possible overloads with circles as the second arguments instead of points.
	bool collisionLineArc(line, circle, point, point); 
	bool collisionLineArc(line, circle, line); 
	bool collisionLineArc(line, circle, point[2]); 
	bool collisionLineArc(line, circle, double, double); 
	bool collisionLineArc(line, point[3]); //Same as above but two args
	bool collisionLineArc(line, point, line); //3rd argument is instead a line containing the start and end of the arc.
	bool collisionLineArc(line, point, double, double); //First two args are the same, last two are start and end angles of the arc.*/
}