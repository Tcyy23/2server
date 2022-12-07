
// hw3_miou_2022.cpp

#include "ecs36b_Common.h"
#include "AutoVehicle.h"

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>
#include "ecs36b_Exception.h"

using namespace jsonrpc;
using namespace std;

Auto_M r_moto;


class Myhw5Server : public hw5Server
{
public:
  Myhw5Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value request(const Json::Value& json_object);
};

Myhw5Server::Myhw5Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Server(connector, type)
{
  std::cout << "Myhw5Server Object created" << std::endl;
}

// member functions

Json::Value
Myhw5Server::request
(const Json::Value& json_object)
{
  Json::Value result;
  result = r_moto.response_message(json_object);

  cout << result.toStyledString() << endl;

  return result;
}


int
main()
{
  cout << "===== This is the program for right motorcycle =====\n\n";

  int n = 1;
  string s = "left";

  bool sel = true;
  bool way = false;
  char c;


  cout << "Please enter the number of passengers(1~10): \n";
  cin >> n;

  cout << "Please enter whether the owner is selfish(y/n): \n";
  cin >> c;
  if (c == 'Y' || c == 'y')
    sel = true;
  else
    sel = false; 

  cout << "Please enter whether existing the way to avoid conflict(y/n): \n";
  cin >> c;
  if (c == 'Y' || c == 'y')
    way = true;
  else
    way = false; 

  cout << "Please enter the motorcycle's emergency_direction(l/r): \n";
  cin >> c; 
  if (c == 'l' || c == 'L')
    s = "left";
  else
    s = "right";
  
  r_moto.passengers = n;
  r_moto.is_selfish = sel;
  r_moto.emergency_direction = s;
  r_moto.is_avoid_way = way;
  r_moto.host_url = "http://127.0.0.1:8883";


  HttpServer httpserver(8883);
  Myhw5Server srv(httpserver,
                  JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  srv.StartListening();
  
  std::cout << "Hit enter to stop the RightMotorcycle server" << endl;
  // avoid line break character
  getchar();
  getchar();
  srv.StopListening();

  return 0;
}


