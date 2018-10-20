#include <iostream>
#ifndef TermFormH
#define TermFormH

namespace termform{
    
    const std::string kAnsiEscapeBegin = "\u001b[";
    const char kAnsiEscapeEndColor = 'm';
    const char kAnsiEscapeEndClearLine = 'K';
    const char kAnsiEscapeEndClearScreen = 'J';
    const char kAnsiEscapeEndSetColumn = 'G';
    const char kAnsiEscapeEndSetPosition = 'H';
    const char kAnsiEscapeEndCursorPreviousLine = 'F';
    const char kAnsiEscapeEndCursorNextLine = 'E';
    const char kAnsiEscapeEndCursorUp = 'A';
    const char kAnsiEscapeEndCursorDown = 'B';
    const char kAnsiEscapeEndCursorLeft = 'D';
    const char kAnsiEscapeEndCursorRight = 'C';
    const char kAnsiEscapeEndSaveCursorPosition = 's';
    const char kAnsiEscapeEndRestoreCursorPosition = 'u';


    enum Style{
        kBlack = 30,
        kRed = 31,
        kGreen = 32,
        kYellow = 33,
        kBlue = 34,
        kMagenta = 35,
        kCyan = 36,
        kWhite = 37,

        kBold = 1,
        
        kUnderline = 4,
        kInvert = 7,
        kBlink = 5,
        kConceal = 8,

        kForeground = 0,
        kBackground = 10,

        kFG = kForeground,
        kBG = kBackground,
        kBright = kBold,

        kReset = 0
    };

    template<typename T>
    void cout(T arg){
        std::cout << arg;
        std::cout << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;
    }

    template<typename T, typename ... Args>
    void cout(T arg, bool endline){
        cout(arg);
        if(endline){
            std::cout << std::endl;
        }
    }

    template<typename T, typename ... Args>
    void cout(T style, const Args&... rest) {
        std::cout << kAnsiEscapeBegin << style << kAnsiEscapeEndColor;
        cout(rest...);
    }
    

    
    enum ClearAmount{
        kAll = 2,
        kCursorToStart = 1,
        kCursorToEnd = 0
    };

    void clearLine(int amount){
        std::cout << kAnsiEscapeBegin << amount << kAnsiEscapeEndClearLine;
    }

    void clearLine(ClearAmount amount){
        int temp = amount;
        clearLine(temp);
    }

    void clearLine(){
        clearLine(kAll);
    }

    void clearScreen(int amount){
        std::cout << kAnsiEscapeBegin << amount << kAnsiEscapeEndClearScreen;
    }

    void clearScreen(ClearAmount amount){
        int temp = amount;
        clearScreen(temp);
    }

    void clearScreen(){
        clearScreen(kAll);
    }


    enum Direction{
        kUp,
        kDown,
        kLeft,
        kRight
    };

    void moveCursor(Direction d, int spaces){
        switch(d){
            case kUp:
                std::cout << kAnsiEscapeBegin << spaces << kAnsiEscapeEndCursorUp;
                break;
            case kDown:
                std::cout << kAnsiEscapeBegin << spaces << kAnsiEscapeEndCursorDown;
                break;
            case kLeft:
                std::cout << kAnsiEscapeBegin << spaces << kAnsiEscapeEndCursorLeft;
                break;
            case kRight:
                std::cout << kAnsiEscapeBegin << spaces << kAnsiEscapeEndCursorRight;
                break;
        }
    }

    void saveCursorPosition(){
        std::cout << kAnsiEscapeBegin << kAnsiEscapeEndSaveCursorPosition;
    }

    void restoreCursorPosition(){
        std::cout << kAnsiEscapeBegin << kAnsiEscapeEndRestoreCursorPosition;
    }

}


#endif // end of TermFormH