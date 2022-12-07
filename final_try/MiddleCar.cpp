
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
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>
#include "ecs36b_Exception.h"

using namespace jsonrpc;
using namespace std;

Auto_C car;


int
main()
{
  cout << "===== This is the program for middle car =====\n\n";

  int n = 2;
  string s = "left";

  bool sel = true;
  char c;


  cout << "Please enter the number of passengers(1~10): \n";
  cin >> n;

  cout << "Please enter whether the owner is selfish(y/n): \n";
  cin >> c;
  if (c == 'Y' || c == 'y')
    sel = true;
  else
    sel = false; 

  cout << "Please enter the driver's seat position(l/r): \n";
  cin >> c; 
  if (c == 'l' || c == 'L')
    s = "left";
  else
    s = "right";

  cout << "===== Simulated for decision making =====\n\n";

  car.passengers = n;
  car.is_selfish = sel;
  car.driver_direction = s;
  car.host_url = "http://127.0.0.1:8882";

  cout << car.dump2JSON().toStyledString() << endl;

  Json::Value mes;
  mes = car.send_message("emergency", car.dump2JSON());

  HttpClient httpclient_l("http://127.0.0.1:8881");
  hw5Client myClient_l(httpclient_l, JSONRPC_CLIENT_V2);

  HttpClient httpclient_r("http://127.0.0.1:8883");
  hw5Client myClient_r(httpclient_r, JSONRPC_CLIENT_V2);

  double loss_l, loss_r, loss_m;
  Json::Value myv;

  loss_m = car.passengers;

  try {
    myv = myClient_l.request(mes);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  cout << myv.toStyledString() << endl;

  loss_l = car.cal_collision_loss(myv);

  try {
    myv = myClient_r.request(mes);
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  cout << myv.toStyledString() << endl;

  loss_r = car.cal_collision_loss(myv);
  

  cout << "Left, Middle, Right loss: " << loss_l << ' ' << loss_m << ' ' << loss_r << endl;

  car.make_decision(loss_l, loss_m, loss_r);

  return 0;
}


