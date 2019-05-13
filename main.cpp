#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

class Point3D {
public:
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;

    void print() {
        cout << "(" << x << ", " << y << ", " << x << ")" << endl;
    }
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
    Plane3D() {}

    Plane3D(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) {}

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


float point_to_plane_distance(const Point3D& point, const Plane3D& plane) {
    return fabs(plane.a * point.x + plane.b * point.y + plane.c * point.z + plane.d) /
           (sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c));
}


// Random sample consensus (RANSAC) algorithm
Plane3D fit_plane(const vector<Point3D>& point_cloud, float p) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, point_cloud.size() - 1);
    // todo: pointers?
    vector<Point3D> consensus_set;
    vector<Point3D> best_consensus_set;
    int k = 100;
    int number_of_possible_planes = 0;
    Plane3D result_plane;
    for (int i = 0; i < k; i++) {
        Plane3D sample_plane = Plane3D(point_cloud[dist(mt)], point_cloud[dist(mt)], point_cloud[dist(mt)]);
        for (auto j : point_cloud) {
            if (point_to_plane_distance(j, sample_plane) < p) {
                consensus_set.push_back(j);
            }
        }
        if (consensus_set.size() > best_consensus_set.size()) {
            best_consensus_set = consensus_set;
            result_plane = sample_plane;
        }
        if (consensus_set.size() > point_cloud.size() / 2) {
            number_of_possible_planes++;
        }
        consensus_set.clear();
    }
    // todo: need to average best fitting plane
    cout << "number of possible planes = " << number_of_possible_planes << endl;
    cout << "max consensus set size = " << best_consensus_set.size() << endl;
    return result_plane;
}

int main() {
    string line;
    ifstream input("input.txt");
    if (input.is_open()) {
        getline(input, line);
        float p = stof(line);
        getline(input, line);
        int n = stoi(line);
        vector<Point3D> point_cloud;
        point_cloud.reserve(n);
        while (getline(input, line)) {
            istringstream points(line);
            float x, y, z;
            points >> x; points >> y; points >> z;
            point_cloud.emplace_back(x, y, z);
        }
        Plane3D plane = fit_plane(point_cloud, p);
        plane.print();
        input.close();
    } else {
        cout << "unable to open file" << endl;
    }
    return 0;
}