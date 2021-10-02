#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
public:
  LoginHandler(Ap_Drive* _ap_drive) {ap_drive=_ap_drive;}
  Response *callback(Request *);
  private:
  	Ap_Drive* ap_drive;
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);

};

class ShowlistHandler : public RequestHandler {
 public:
 	ShowlistHandler(Ap_Drive* _ap_drive) {ap_drive=_ap_drive;}
 	Response *callback(Request *);
 private:
 Ap_Drive* ap_drive;
};

class ShowfileHandler : public RequestHandler {
 public:
 	ShowfileHandler(Ap_Drive* _ap_drive) {ap_drive=_ap_drive;}
 	Response *callback(Request *);
 private:
 Ap_Drive* ap_drive;
};
class LogoutHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ShowdetailHandler : public RequestHandler {
 public:
 	ShowdetailHandler(Ap_Drive* _ap_drive) {ap_drive=_ap_drive;}
 	Response *callback(Request *);
 private:
 Ap_Drive* ap_drive;
};
class ManagementHandler : public RequestHandler {
 public:
 	Response *callback(Request *);
 private:
};
class UserListHandler : public RequestHandler {
 public:
 	UserListHandler(Ap_Drive* _ap_drive) {ap_drive=_ap_drive;}
 	Response *callback(Request *);
 private:
 Ap_Drive* ap_drive;
};
class AddUserHandler : public RequestHandler {
 public:
 	AddUserHandler(Ap_Drive* _ap_drive) {ap_drive=_ap_drive;}
 	Response *callback(Request *);
 private:
 Ap_Drive* ap_drive;
};
class MakeFolder : public RequestHandler {
 public:
 	MakeFolder(Ap_Drive* _ap_drive) {ap_drive=_ap_drive;}
 	Response *callback(Request *);
 private:
 Ap_Drive* ap_drive;
};







