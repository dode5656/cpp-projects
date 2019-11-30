#include <iostream>

using namespace std;

class Cube {
    private:
        double x, y, z, w, h, d;
    public:
        Cube(double ax, double ay, double az, double aw, double ah, double ad) {
            x = ax;
            y = ay;
            z = az;
            w = aw;
            h = ah;
            d = ad;
        }
        bool checkCollision(Cube& cube) {
            if ((x+(w/2) >= cube.get('x')-(cube.get('w')/2)) && 
            (y+(h/2) >= cube.get('y')-(cube.get('h')/2)) &&
            (z+(d/2) >= cube.get('z')-(cube.get('d')/2)) && 
            (x-(w/2) >= cube.get('x')+(cube.get('w')/2)) && 
            (y-(h/2) >= cube.get('y')+(cube.get('h')/2)) && 
            (z-(d/2) >= cube.get('z')+(cube.get('d')/2))) {
                return true;
            } else {
                return false;
            }
        }
        int move(double ax, double ay, double az) {
            x += ax;
            y += ay;
            z += az;
            return 0;
        }
        int growShrink(bool grow, double proportion) {
            if (grow) {
                w *= proportion;
                h *= proportion;
                d *= proportion;
            } else {
                w *= 1/proportion;
                h *= 1/proportion;
                d *= 1/proportion;
            }
            return 0;
        }
        double get(char var) {
            switch (var) {
                case 'x':
                    return x;
                    break;
                case 'y':
                    return y;
                    break;
                case 'z':
                    return z;
                    break;
                case 'w':
                    return w;
                    break;
                case 'h':
                    return h;
                    break;
                case 'd':
                    return d;
                    break;
                default:
                    throw "ArgumentError: Argument is not a variable of Cube class";
                    break;                

            }
        }
};
