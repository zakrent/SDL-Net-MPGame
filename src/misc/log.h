//
// Created by zakrent on 9/28/17.
//

#ifndef GAME_MP_SERVER_LOG_H
#define GAME_MP_SERVER_LOG_H

#include <string>
#include <iostream>
#include <ctime>
#include <cstring>

namespace consoleLog{

    enum logLevel{
        info,
        warning,
        error,
    };

    void logMessage(logLevel level, std::string message){
        time_t rawtime;
        struct tm * timeinfo;
        char charTime [80];
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (charTime,80,"] %T ",timeinfo);

        char logChar [80];

        switch(level){
            case info:
                strcpy(logChar, "Info");
                break;
            case warning:
                strcpy(logChar, "Warning!");
                break;
            case error:
                strcpy(logChar, "ERROR!");
                break;
        }

        std::cout<<"["<<logChar<<charTime<<": "<<message<<std::endl;
    }
}

#endif //GAME_MP_SERVER_LOG_H
