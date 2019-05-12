#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

class Point3D {
public:
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;
};

class Vector3D {
public:
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3D(const Point3D& first_point, const Point3D& second_point) {
        x = second_point.x - first_point.x;
        y = second_point.y - first_point.y;
        z = second_point.z - first_point.z;
    }

    float x;
    float y;
    float z;

    Vector3D cross_product(const Vector3D& other) {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    float length() {
        return sqrt(x * x + y * y + z * z);
    }
};

class Plane3D {
public:
    Plane3D(const Point3D& first_point, const Point3D& second_point, const Point3D& third_point) {
        Vector3D first_vector(first_point, second_point);
        Vector3D second_vector(second_point, third_point);
        Vector3D normal_vector = first_vector.cross_product(second_vector);
        a = normal_vector.x;
        b = normal_vector.y;
        c = normal_vector.z;
        d = -(a * first_point.x + b * first_point.y + c * first_point.z);
    }

    float a;
    float b;
    float c;
    float d;

    void print() {
        cout << a << " " << b << " " << c << " " << d << endl;
    }
};

Plane3D fit_plane(const vector<Point3D>& point_cloud, int n, float p) {
    return {
        point_cloud[0], point_cloud[1], point_cloud[2]
    };
}

int main() {
    string line;
    ifstream input("input.txt");
    vector<Point3D> point_cloud;
    if (input.is_open()) {
        getline(input, line);
        float p = stof(line);
        getline(input, line);
        int n = stoi(line);
        while (getline(input, line)) {
            istringstream points(line);
            float x, y, z;
            points >> x; points >> y; points >> z;
            point_cloud.emplace_back(x, y, z);
        }
        Plane3D plane = fit_plane(point_cloud, n, p);
        plane.print();
        input.close();
    } else {
        cout << "unable to open file" << endl;
    }
    return 0;
}