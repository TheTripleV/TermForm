#include <iostream>
#ifndef TermFormH
#define TermFormH

namespace termform{
    
    //consts for Ansi Escape
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

    const int kAnsiCustomColorBegin = 38;
    const std::string kAnsiCustomColorMiddle = ";5;";

    //Ansi codes for 8 bit color and special modifiers
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

        kBright = kBold,

        kReset = 0
    };

    //Foreground/Background modifiers
    enum ForegroundBackground{
        kForeground = 0,
        kBackground = 10,

        kFG = kForeground,
        kBG = kBackground
    };

    //Methods to use a custom ansi color code for 256 color support
    std::string customColor(ForegroundBackground F, int code){
        return std::to_string(F + kAnsiCustomColorBegin) 
        + kAnsiCustomColorMiddle 
        + std::to_string(code);
    }

    std::string customColor(int code){
        return customColor(kForeground, code);
    }

    //Template methods to print formatted text to user provided output
    template<typename OutputStream, typename T>
    void out(OutputStream &out_stream, T arg){
        out_stream << arg;
        out_stream << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;
        out_stream << std::endl;
    }

    template<typename OutputStream, typename T, typename ... Args>
    void out(OutputStream &out_stream, T arg, bool endline){
        out_stream << arg;
        out_stream << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;
        if(endline){
            out_stream << std::endl;
        }
    }

    template<typename OutputStream, typename T, typename ... Args>
    void out(OutputStream &out_stream, T style, const Args&... rest) {
        out_stream << kAnsiEscapeBegin << style << kAnsiEscapeEndColor;
        out(out_stream, rest...);
    }


    //Template methods to print formatted text to cout
    template<typename T>
    void cout(T arg){
        out(std::cout, arg);
    }

    template<typename T, typename ... Args>
    void cout(T arg, bool endline){
        out(std::cout, arg, endline);
    }

    template<typename T, typename ... Args>
    void cout(T style, const Args&... rest) {
        out(std::cout, style, rest...);
    }
    
    
    //Ansi Codes to clear line/screen
    enum ClearAmount{
        kAll = 2,
        kCursorToStart = 1,
        kCursorToEnd = 0
    };

    //Methods to clear line
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

    //Methods to clear screen
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

    //Direction to move cursor
    enum Direction{
        kUp,
        kDown,
        kLeft,
        kRight
    };

    //Method to move cursor
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

    //Cursor memory functions
    void saveCursorPosition(){
        std::cout << kAnsiEscapeBegin << kAnsiEscapeEndSaveCursorPosition;
    }

    void restoreCursorPosition(){
        std::cout << kAnsiEscapeBegin << kAnsiEscapeEndRestoreCursorPosition;
    }

}


#endif // end of TermFormH