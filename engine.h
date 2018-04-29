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
			point operator [](int i) {
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

	//Returns number of intersections. Sets 'position[0]' to the intersection point closest to 'line.a', and 'position[1]' to the intersection point closest to 'line.b'
	int intersectLineCircle(line, circle, point[2]);
}