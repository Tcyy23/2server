
#ifndef _AUTOVEHICLE_H_
#define _AUTOVEHICLE_H_

// AutoVehicle.h

#include "ecs36b_Common.h"

class Auto_V
{
 private:
 public:
  string type;
  string host_url;

  double longitude;
  double latitude;

  double speed;
  double acceleration;

  int passengers;

  bool is_selfish;
  bool is_avoid_way;

  Auto_V(int p = 0, string hu = "", string t = "V", 
         double lon = 0, double lat = 0, 
         double s = 0, double acc = 0, bool sel = true, bool iaw = false);

  virtual Json::Value dump2JSON();

  virtual Json::Value send_message(string, Json::Value);
  virtual Json::Value response_message(Json::Value);

  virtual double cal_collision_loss(Json::Value);
  virtual bool find_avoid_way(Json::Value);
  virtual void make_decision(double, double, double);
  
};

class Auto_C: public Auto_V
{
 private:
 public:
  string driver_direction;
  double protection;

  Auto_C(int p = 0, string hu = "", string t = "C", 
         double lon = 0, double lat = 0, 
         double s = 0, double acc = 0, bool sel = true, bool iaw = false, 
         string dd = "left", double prot = 0.5);

  virtual Json::Value dump2JSON();

  virtual double cal_collision_loss(Json::Value);
  virtual void make_decision(double, double, double);

};

class Auto_M: public Auto_V
{
 private:
 public:
  string emergency_direction;

  Auto_M(int p = 0, string hu = "", string t = "M", 
         double lon = 0, double lat = 0, 
         double s = 0, double acc = 0, bool sel = true, bool iaw = false, 
         string ed = "left");

  virtual Json::Value dump2JSON();

  virtual double cal_collision_loss(Json::Value);
  virtual void make_decision(double, double, double);
  
};

#endif  /* _AUTOVEHICLE_H_ */


