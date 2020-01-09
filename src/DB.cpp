//#include "DB.h"
//#include <vector>
//
//
//DB* DB::instance = 0;
//DB* DB::getInstance(){
//    if(DB::instance == 0){
//        instance = new DB;
//    }
//    return instance;
//};
//
//void DB::addUser(User *user) {
//    userList.push_back(user);
//}
//
//void DB::deleteUser(User * user) {
//    vector<User*>::iterator it;
////    userList.erase(it);
//    for(it = userList.begin(); it!=userList.end(); ++it)
//    {
//        if((*it) == user)
//        {
//            userList.erase(it);
//        }
//    }
//}
//
//User *DB::getCurrentUser() {
//    return currentActiveUser;
//}
//
//void DB::setCurrentUser(User *user) {
//    currentActiveUser = user;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
