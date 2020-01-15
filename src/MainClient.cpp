#include <iostream>
#include <string>
#include <include/User.h>
#include <boost/lexical_cast.hpp>
#include <include/connectionHandler.h>
#include <thread>
#include <include/FromServerReader.h>
#include <include/KeyboardReader.h>
#include <vector>
#include <boost/algorithm/string.hpp>

//vector<string> split(string str, string seperator);

vector<string> split(string s, string delimiter);
vector<string> split(string s, string delimiter)
{
    vector<string> wordsVector;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
        wordsVector.push_back(token);
    }
    wordsVector.push_back(s);

    return wordsVector;
}
using namespace std;



int main() {

    bool terminate = false;
    while (!(terminate)) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        vector<string> commands;
        //commands = split(line, " ");
        boost::split(commands, line, boost::is_any_of(" "));
        if (commands[0] == "login") {
            string host = commands[1].substr(0, commands[1].find(':'));
            string portS = commands[1].substr(commands[1].find(':') + 1);
            short port = boost::lexical_cast<short>(portS);
            User *user = new User(commands[2], commands[3]);
            Inventory * inventory = new Inventory();
            ConnectionHandler *connectionHandler = new ConnectionHandler(host, port);
            connectionHandler->connect();
            string frame =
                    "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + commands[2] + "\npasscode:" +
                    commands[3] + "\n\n" + '\0';
            vector<string> output;
            boost::split(output, frame, boost::is_any_of("\n"));
            connectionHandler->sendLine(frame);

            KeyboardReader keyBoardThread(connectionHandler, user, inventory);
            FromServerReader serverSocketThread(connectionHandler, user, inventory);

            //bool *t = new bool;
            //bool *r = new bool;
//            KeyboardReader keyBoardThread(&connectionHandler, r, t);
//            FromServerReader serverSocketThread(&connectionHandler, r, t);
//            thread serverInput(&FromServerReader::run, &serverSocketThread);
//            thread keyBoardInput(&KeyboardReader::run, &keyBoardThread);
//            serverInput.join();
//            keyBoardInput.join();

            std::thread t1(std::ref(keyBoardThread));
            std::thread t2(std::ref(serverSocketThread));
            t2.join();
            t1.join();
            return 0;
        }
    }

}







