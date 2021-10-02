#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler(server.get_ap_drive()));
    server.get("/logout", new LogoutHandler());
    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler());
    server.get("/rand", new RandomNumberHandler());
    server.get("/Shuttle.jpg", new ShowImage("static/Shuttle.jpg"));
    server.get("/", new ShowPage("static/home.html"));
    server.get("/showlist", new ShowlistHandler(server.get_ap_drive()));
    server.get("/showfile", new ShowfileHandler(server.get_ap_drive()));
    server.get("/details", new ShowdetailHandler(server.get_ap_drive()));
    server.get("/management", new ManagementHandler());
    server.get("/userlist", new UserListHandler(server.get_ap_drive()));
    server.get("/adduser", new ShowPage("static/login.html"));
    server.post("/adduser", new AddUserHandler(server.get_ap_drive()));
    server.get("/makefolder", new ShowPage("static/makefolder.html"));
    server.post("/makefolder", new MakeFolder(server.get_ap_drive()));
    

    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
