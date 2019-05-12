#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Point3D {
public:
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;
};

void fit_plane(vector<Point3D>& point_cloud, int n, float p) {
    for (int i = 0; i < n; i++) {
        cout << point_cloud[i].x << " " << point_cloud[i].y << " " << point_cloud[i].z << endl;
    }
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
        fit_plane(point_cloud, n, p);
        input.close();
    } else {
        cout << "unable to open file" << endl;
    }
    return 0;
}