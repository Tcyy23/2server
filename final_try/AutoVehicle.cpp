#include "AutoVehicle.h"


// Auto_V
Auto_V::Auto_V
(int p, string hu, string t,
 double lon, double lat,
 double s, double acc, bool sel, bool iaw)
{
  passengers = p;
  host_url = hu;
  type = t;
  longitude = lon;
  latitude = lat;
  speed = s;
  acceleration = acc;
  passengers = p;
  is_selfish = sel;  
  is_avoid_way = iaw;
}

Json::Value
Auto_V::dump2JSON
()
{
  Json::Value result;

  result["type"] = type;
  result["host_url"] = host_url;
  result["longitude"] = longitude;
  result["latitude"] = latitude;
  result["speed"] = speed;
  result["acceleration"] = acceleration;
  result["passengers"] = passengers;
  result["selfish"] = is_selfish;

  return result;
}

Json::Value 
Auto_V::send_message
(string operation, Json::Value obj)
{
  Json::Value result;

  result["operation"] = operation;
  result["information"] = obj;

  return result;
}

Json::Value 
Auto_V::response_message
(Json::Value obj)
{
  Json::Value result;
  if (obj["operation"] == "emergency")
  {
    result = dump2JSON();
    if (find_avoid_way(obj["information"]))
      result["avoid way"] = true;
    return result;
  }
    
  else if (obj["operation"] == "move")
    return dump2JSON();
  else 
    return result;
}

double 
Auto_V::cal_collision_loss
(Json::Value obj)
{
  double my_loss, obj_loss;
  my_loss = passengers;
  obj_loss = stoi(obj["passengers"].asString());

  if (!obj["avoid way"].isNull())
    return 0;

  if (!obj["protection"].isNull())
    obj_loss *= stod(obj["protection"].asString());
  return my_loss + obj_loss; 
}

bool 
Auto_V::find_avoid_way
(Json::Value obj)
{
  return is_avoid_way;
}

void 
Auto_V::make_decision
(double l, double s, double r)
{
  cout << "\nFinal decision is: ";
  if (is_selfish)
  {
     if (r <= l)
       cout << "Turn to the right" << endl;
     else 
       cout << "Turn to the left" << endl;
  }
  else
  {
     if (r <= l && r <= s)
       cout << "Turn to the right" << endl;
     else if (l <= r && l <= s)
       cout << "Turn to the left" << endl;
     else 
       cout << "Stay in lane" << endl;     
  }
}


// Auto_C
Auto_C::Auto_C
(int p, string hu, string t,
 double lon, double lat,
 double s, double acc, bool sel, bool iaw,
 string dd, double prot)
{
  passengers = p;
  host_url = hu;
  type = t;
  longitude = lon;
  latitude = lat;
  speed = s;
  acceleration = acc;
  passengers = p;
  is_selfish = sel;
  driver_direction = dd;
  protection = prot;
  is_avoid_way = iaw;
}

Json::Value 
Auto_C::dump2JSON()
{
  Json::Value result;
  result = Auto_V::dump2JSON();
  result["protection"] = protection;
  result["driver seat"] = driver_direction;
  return result;
}

double 
Auto_C::cal_collision_loss
(Json::Value obj)
{
  double my_loss, obj_loss;
  my_loss = passengers * protection;
  obj_loss = stoi(obj["passengers"].asString());

  if (!obj["avoid way"].isNull())
    return 0;

  if (!obj["protection"].isNull())
    obj_loss *= stod(obj["protection"].asString());
  return my_loss + obj_loss; 
}

void 
Auto_C::make_decision
(double l, double s, double r)
{
  cout << "\nFinal decision is: ";
  if (is_selfish)
  {
     if (r < l)
       cout << "Turn to the right" << endl;
     else if (l > r)
       cout << "Turn to the left" << endl;
     else if (driver_direction == "right")
       cout << "Turn to the right" << endl;
     else
       cout << "Turn to the left" << endl;
  }
  else if (driver_direction == "right")
  {
     if (r <= l && r <= s)
       cout << "Turn to the right" << endl;
     else if (l <= r && l <= s)
       cout << "Turn to the left" << endl;
     else 
       cout << "Stay in lane" << endl;     
  }
  else
  {
     if (l <= r && l <= s)
       cout << "Turn to the left" << endl;
     else if (r <= l && r <= s)
       cout << "Turn to the right" << endl;
     else 
       cout << "Stay in lane" << endl;       
  }
}


// Auto_M
Auto_M::Auto_M
(int p, string hu, string t,
 double lon, double lat,
 double s, double acc, bool sel, bool iaw,
 string ed)
{
  passengers = p;
  host_url = hu;
  type = t;
  longitude = lon;
  latitude = lat;
  speed = s;
  acceleration = acc;
  passengers = p;
  is_selfish = sel;
  emergency_direction = ed;
  is_avoid_way = iaw;
}

Json::Value 
Auto_M::dump2JSON()
{
  Json::Value result;
  result = Auto_V::dump2JSON();
  result["emergency direction"] = emergency_direction;
  return result;
}

double 
Auto_M::cal_collision_loss
(Json::Value obj)
{
  double my_loss, obj_loss;
  my_loss = passengers * 0.9;
  obj_loss = stoi(obj["passengers"].asString());

  if (!obj["avoid way"].isNull())
    return 0;

  if (!obj["protection"].isNull())
    obj_loss *= stod(obj["protection"].asString());
  return my_loss + obj_loss; 
}

void 
Auto_M::make_decision
(double l, double s, double r)
{
  cout << "\nFinal decision is: ";
  if (is_selfish)
  {
     if (r < l)
       cout << "Turn to the right" << endl;
     else if (l > r)
       cout << "Turn to the left" << endl;
     else if (emergency_direction == "right")
       cout << "Turn to the right" << endl;
     else
       cout << "Turn to the left" << endl;
  }
  else if (emergency_direction == "right")
  {
     if (r <= l && r <= s)
       cout << "Turn to the right" << endl;
     else if (l <= r && l <= s)
       cout << "Turn to the left" << endl;
     else 
       cout << "Stay in lane" << endl;     
  }
  else
  {
     if (l <= r && l <= s)
       cout << "Turn to the left" << endl;
     else if (r <= l && r <= s)
       cout << "Turn to the right" << endl;
     else 
       cout << "Stay in lane" << endl;       
  }
}



