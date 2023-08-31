#include<iostream>

#include<cmath>

// 24.36473,88.62763;24.3649,88.62769;24.36489,88.62793;24.3647,88.62788;4#
// 24.36737,88.62567;24.36738,88.62582;24.36715,88.62583;24.36715,88.62567;4#
// 24.3666, 88.62717; 24.36763, 88.62679; 24.36832, 88.62903; 24.36723, 88.62941
// 31,32,33,34,36,37
using namespace std;

const int no_points=4;
double points_lat[no_points*2];
double points_lon[no_points*2];
double dist = 0, brng=0;
double toRadian = 0.01745329251;
double toDegree = 57.2957795131;


double point1_lat = 24.3666; 
double point1_lon = 88.62717;
double point2_lat = 24.36763;
double point2_lon = 88.62679;
double point3_lat = 24.36832; 
double point3_lon = 88.62903;
double point4_lat = 24.36723; 
double point4_lon = 88.62941;

void intermediate_point(double lat1, double lon1, double lat2, double lon2, double angular_dist, double frac, int index){
  double a = sin((1-frac)*angular_dist) / sin(angular_dist);
  double b = sin(frac*angular_dist) / sin(angular_dist);
  double x = a*cos(lat1)*cos(lon1) + b*cos(lat2)*cos(lon2);
  double y = a*cos(lat1)*sin(lon1) + b*cos(lat2)*sin(lon2);
  double z = a * sin(lat1) + b*sin(lat2);
  points_lat[index] = atan2(z,sqrt((x*x)+(y*y)))*toDegree;
  points_lon[index] = atan2(y,x)*toDegree;

  // points_lat[index] = index;
  // points_lon[index] = index;
  // cout.precision(10);
  // cout << lon_i*toDegree <<"," <<  lat_i*toDegree << endl;
}

void dist_brng(double lat1, double lon1, double lat2, double lon2, double lat3, double lon3, double lat4, double lon4){
  //Theta
	lat1 *= toRadian;
  lat2 *= toRadian;
  lat3 *= toRadian;
  lat4 *= toRadian;

  // labmda
  lon1 *= toRadian;
  lon2 *= toRadian;
  lon3 *= toRadian;
  lon4 *= toRadian;

  // Delta coordinates
  double deltaLat= (lat4 - lat1);
  double deltaLon = (lon4 - lon1);

  // Distance
  double a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos(lat1) * cos(lat4) * sin(deltaLon / 2) * sin(deltaLon / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  int i =0,f=0;
  // if(isSecond){

  // }
  // else{
  intermediate_point(lat1,lon1,lat4,lon4,c,(double)0,0);
  i+=3;
  // isSecond = true;
  for(f=1 ;i<no_points*2;i+=3,f++){
    intermediate_point(lat1,lon1,lat4,lon4,c,(double)f/no_points,i);
    f++,i++;
    if(i>=no_points*2)break;
    intermediate_point(lat1,lon1,lat4,lon4,c,(double)f/no_points,i);
  }

  deltaLat = (lat3 - lat2);
  deltaLon = (lon3 - lon2);

  // Distance
  a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos(lat2) * cos(lat3) * sin(deltaLon / 2) * sin(deltaLon / 2);
  c = 2 * atan2(sqrt(a), sqrt(1 - a));
  i =0,f=0;
  i++;
  // isSecond = false;
  for( ;i<no_points*2-2;i+=3,f++){
    intermediate_point(lat2,lon2,lat3,lon3,c,(double)f/no_points,i);
    f++,i++;
    intermediate_point(lat2,lon2,lat3,lon3,c,(double)f/no_points,i);
  }
  // }


  // dist = 6371 * c * 1000;

  // // cout << "dist: " << dist << endl;

  // double y = sin(lon2_r - lon1_r) * cos(lat2_r);
  // double x = cos(lat1_r) * sin(lat2_r) - sin(lat1_r) * cos(lat2_r) * cos(lon2_r - lon1_r);
  // brng = atan2(y, x) * 57.3; // *******  +/-
}

int main(){
  dist_brng(point1_lat, point1_lon,point2_lat, point2_lon, point3_lat, point3_lon,point4_lat, point4_lon);
  // dist_brng(point3_lat, point3_lon,point4_lat, point4_lon);
  for (int i=0;i<no_points*2; i++){
    cout.precision(8);
    cout << points_lat[i] << ',' << points_lon[i] <<",red,circle" <<endl;
  }
}
