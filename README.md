## Find plane in points cloud

The autonomous vehicle stands on a flat asphalt surface, 
a LIDAR is installed on the roof of the car. The measurements obtained 
by the LIDAR for one scan period are given.
Measurements are a set of N points with x, y and z coordinates. 
More than 50% of the points belong to the road.
The model of the position of the points belonging to the road in space is
a plane with parameterization: 

`A*x + B*y + C*z + D = 0`

The points that belong to the road deviate from the model by no more 
than a specified value `p`.
It is necessary to find the parameters `A`, `B`, `C`, and D of the plane
 corresponding to the road. The number of points deviating 
from the model by no more than p must be at least 50% of the total 
number of points.
