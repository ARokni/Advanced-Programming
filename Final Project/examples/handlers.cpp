#include "handlers.hpp"
#include <unistd.h>


using namespace std;

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);

  return res;
}

Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
 // if (username == "root")
 //   throw Server::Exception("Remote root access has been disabled.");
  cout << "username: " << username << ",\tpassword: " << password << endl;
  Response *res;
  if(ap_drive->get_current_user()->get_position()=="Normaluser")
     res = Response::redirect("/showlist");
  else
    res = Response::redirect("/management");
  res->setSessionId("SID");
  return res;
}

Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  cout << name << " (" << file.size() << "B):\n" << file << endl;
  Response *res = Response::redirect("/");
  return res;
}


//******************* PHASE II **********************
Response *ShowlistHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<h2>";
  body +=ap_drive->get_current_folder()->get_folder_name();
  body +="</h2>";
  body += "<p>";
  body += "List : ";
  body += to_string(50);
  body += "</p>";
  body +="<p>";
  body +="<a href=/showlist?name=back>back</a>";
  body +="</p>";
  body +="<a href=/logout>logout</a>";

  for(int i=0; i<ap_drive->get_current_folder()->get_folder().size(); i++)
  {
    body +="<p>";
    body +="<a href=/showlist?name=";
    body +=ap_drive->get_current_folder()->get_folder()[i]->get_folder_name();
    body +=">";
    body +=ap_drive->get_current_folder()->get_folder()[i]->get_folder_name();
    body +="</a>";
    body +=" ";
    body +="<a href=/showlist?name=remove&name2=";
    body +=ap_drive->get_current_folder()->get_folder()[i]->get_folder_name();
    body +=">";
    body +="remove";
    body +="</a>";
    body +=" ";
    body +="<a href=/details?name=details&name2=";
    body +=ap_drive->get_current_folder()->get_folder()[i]->get_folder_name();
    body +=">";
    body +="details";
    body +="</a>";
    
    body +="</p>";
  }

  for(int i=0; i<ap_drive->get_current_folder()->get_file().size(); i++)
  {
    body +="<p>";
    body +="<a href=/showfile?name=";
    body +=ap_drive->get_current_folder()->get_file()[i]->get_file_name();
    body +=">";
    body +=ap_drive->get_current_folder()->get_file()[i]->get_file_name();
    body +="</a>";
     body +=" ";
    body +="<a href=/showlist?name=remove&name2=";
    body +=ap_drive->get_current_folder()->get_file()[i]->get_file_name();
    body +=">";
    body +="remove";
    body +="</a>";
    body +=" ";
    body +="<a href=/showlist?name=copy&name2=";
    body +=ap_drive->get_current_folder()->get_file()[i]->get_file_name();
    body +=">";
    body +="copy";
    body +="</a>";
    body +=" ";
    body +="<a href=/showlist?name=move&name2=";
    body +=ap_drive->get_current_folder()->get_file()[i]->get_file_name();
    body +=">";
    body +="move";
    body +="</a>";
    body +=" ";
    body +="<a href=/details?name=details&name2=";
    body +=ap_drive->get_current_folder()->get_file()[i]->get_file_name();
    body +=">";
    body +="details";
    body +="</a>";
    body +="</p>";
  }
  body +="<p>";
  body +="<a href=/showlist?name=paste>paste</a>";
  body +=" ";
  body +="<a href=/makefolder>MakeFolder</a>";
  body +="</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}


Response *ShowfileHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body +="<p>";
  body +="<a href=/showlist>back</a>";
  body +="</p>";
  body +="<p>";
  body +=ap_drive->show_file();
  body +="</p>";
  body += "</body>";
  body += "</html>";
  body +="<a href=/logout>logout</a>";
  res->setBody(body);

  return res;
}

Response *LogoutHandler::callback(Request *req) {
  Response *res = Response::redirect("/login");
  return res;
}

Response *ShowdetailHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body +="<p>";
  body +="<a href=/showlist>back</a>";
  body +="</p>";
  for(int i=0; i<ap_drive->get_details().size();i++)
  {
    body +="<p>";
    body +=ap_drive->get_details()[i];
    body +="</p>";
  }
  body += "</body>";
  body += "</html>";
  body +="<a href=/logout>logout</a>";
  res->setBody(body);

  return res;
}

Response *ManagementHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body +="<p>";
  body +="<a href=/showlist>elements_list</a>";
  body +="</p>";
  body +="<p>";
  body +="<a href=/userlist>user_list</a>";
  body +="</p>";
  body +="<p>";
  body +="<a href=/adduser>adduser</a>";
  body +="</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  

  return res;
}

Response *UserListHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  for(int i=0 ; i<ap_drive->get_users().size() ; i++)
  {
    body +="<p>";
    body +=ap_drive->get_users()[i]->get_username();
    body +=" ";

    body +="<a href=/userlist?name=promote&name2=";
    body +=ap_drive->get_users()[i]->get_username();
    body += ">promote</a>";
    body +="</p>";
    body +=" ";
    body +="<p>";
    body +="<a href=/userlist?name=demote&name2=";
    body +=ap_drive->get_users()[i]->get_username();
    body += ">demote</a>";
    body +="</p>";
  }
  body +="<p>";
  body +="<a href=/management>back</a>";
  body +="</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  


  return res;
}
Response *AddUserHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  Response *res;


  ap_drive->add_user(username , password);

  res = Response::redirect("/management");
  return res;
}

Response *MakeFolder::callback(Request *req) {
  string directory_name = req->getBodyParam("foldername");
  Response *res;
  res = Response::redirect("/showlist");
  ap_drive->make_directory(directory_name);
  return res;
}





