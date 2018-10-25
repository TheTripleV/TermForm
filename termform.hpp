#ifndef TermFormH
#define TermFormH
#include <iostream>
#include <string>
#include <sstream>

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

    //Code to Beep
    const char kBeepCode = '\a';

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
    std::string CustomColor(ForegroundBackground F, int code){
        return std::to_string(F + kAnsiCustomColorBegin) 
        + kAnsiCustomColorMiddle 
        + std::to_string(code);
    }

    std::string CustomColor(int code){
        return CustomColor(kForeground, code);
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
    void out(OutputStream &out_stream, T arg, bool endline, bool reset){
        out_stream << arg;
        if(reset){
            out_stream << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;
        }
        if(endline){
            out_stream << std::endl;
        }
    }

    template<typename OutputStream, typename Y, typename T, typename ... Args>
    void out(OutputStream &out_stream, Y arg, T style, const Args&... rest) {
        out_stream << kAnsiEscapeBegin << style << kAnsiEscapeEndColor;
        out(out_stream, arg, rest...);
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

    template<typename ... Args>
    void cout(const Args&... rest) {
        out(std::cout, rest...);
    }
    
    void cout(){
        out(std::cout, "");
    }
    
    //Ansi Codes to clear line/screen
    enum ClearAmount{
        kAll = 2,
        kCursorToStart = 1,
        kCursorToEnd = 0
    };

    //Methods to clear line
    void ClearLine(int amount){
        std::cout << kAnsiEscapeBegin << amount << kAnsiEscapeEndClearLine;
    }

    void ClearLine(ClearAmount amount){
        int temp = amount;
        ClearLine(temp);
    }

    void ClearLine(){
        ClearLine(kAll);
    }

    //Methods to clear screen
    void ClearScreen(int amount){
        std::cout << kAnsiEscapeBegin << amount << kAnsiEscapeEndClearScreen;
    }

    void ClearScreen(ClearAmount amount){
        int temp = amount;
        ClearScreen(temp);
    }

    void ClearScreen(){
        ClearScreen(kAll);
    }

    //Direction to move cursor
    enum Direction{
        kUp,
        kDown,
        kLeft,
        kRight
    };

    //Method to move cursor
    void MoveCursor(Direction d, int spaces){
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
    void SaveCursorPosition(){
        std::cout << kAnsiEscapeBegin << kAnsiEscapeEndSaveCursorPosition;
    }

    void RestoreCursorPosition(){
        std::cout << kAnsiEscapeBegin << kAnsiEscapeEndRestoreCursorPosition;
    }

    //Beep methods
    void Beep(){
        std::cout << kBeepCode;
    }
    void BeepBeep(){
        Beep();
    }
    void Honk(){
        Beep();
    }
    void HonkHonk(){
        Beep();
    }
    void Toot(){
        Beep();
    }
    void TootToot(){
        Beep();
    }


    //Progress Bar
    template <typename Filled = char, typename Unfilled = char, typename BookendBegin = char, typename BookendEnd = char>
    class ProgressBar{
        private:
            BookendBegin bookend_begin_;
            BookendEnd bookend_end_;
            Filled filled_;
            Unfilled unfilled_;
            int length_;
            int num_filled_;

            std::ostringstream filled_style_;
            std::ostringstream unfilled_style_;
            std::ostringstream bookend_begin_style_;
            std::ostringstream bookend_end_style_;

            bool bookend_begin_set_ = false;
            bool bookedn_end_set_ = false;
            bool filled_set_ = false;
            bool unfilled_set_ = false;
            bool length_set_ = false;

            bool something_changed_ = false;

        public:
            ProgressBar(){}


            ProgressBar(Filled filled){
                SetFilled(filled);
            }            

            ProgressBar(int length){
                SetLength(length);
            }

            ProgressBar(Filled filled, int length){
                SetFilled(filled);
                SetLength(length);
            }

            ProgressBar(Filled filled, Unfilled unfilled){
                SetFilled(filled);
                SetUnfilled(unfilled);
            }

            ProgressBar(Filled filled, Unfilled unfilled, int length){
                SetFilled(filled);
                SetUnfilled(unfilled);
                SetLength(length);
            }

            ProgressBar(Filled filled, Unfilled unfilled, int length, BookendBegin bookend_begin, BookendEnd bookend_end){
                SetFilled(filled);
                SetUnfilled(unfilled);
                SetLength(length);
                SetBookendBegin(bookend_begin);
                SetBookendEnd(bookend_end);
            }

            void SetFilled(Filled filled){
                filled_ = filled;
                filled_set_ = true;
                something_changed_ = true;
            }

            void SetUnfilled(Unfilled unfilled){
                unfilled_ = unfilled;
                unfilled_set_ = true;
                something_changed_ = true;
            }

            void SetLength(int length){
                length_ = length;
                length_set_ = true;
                something_changed_ = true;
            }

            void SetBookendBegin(BookendBegin bookend){
                bookend_begin_ = bookend;
                bookend_begin_set_ = true;
                something_changed_ = true;
            }

            void SetBookendEnd(BookendEnd bookend){
                bookend_end_ = bookend;
                bookedn_end_set_ = true;
                something_changed_ = true;
            }

            template<typename ... Args>
            void SetBookendBeginStyle(const Args&... rest) {
                bookend_begin_style_.clear();
                out(bookend_begin_style_, rest..., "", false, false);
                something_changed_ = true;
            }

            template<typename ... Args>
            void SetBookendEndStyle(const Args&... rest) {
                bookend_end_style_.clear();
                out(bookend_end_style_, rest..., "", false, false);
                something_changed_ = true;
            }

            template<typename ... Args>
            void SetBookendsStyle(const Args&... rest) {
                bookend_begin_style_.clear();
                bookend_end_style_.clear();
                out(bookend_begin_style_, rest..., "", false, false);
                out(bookend_end_style_, rest..., "", false, false);
                something_changed_ = true;
            }

            template<typename ... Args>
            void SetFilledStyle(const Args&... rest) {
                filled_style_.clear();
                out(filled_style_, rest..., "", false, false);
                something_changed_ = true;
            }

            template<typename ... Args>
            void SetUnfilledStyle(const Args&... rest) {
                unfilled_style_.clear();
                out(unfilled_style_, rest..., "", false, false);
                something_changed_ = true;
            }

            template<typename Numerator, typename Denominator>
            void update(Numerator numerator, Denominator denominator){
                SetDefaults();

                int new_num_filled = length_ * (double)(numerator / (double)denominator);
                if(num_filled_ != new_num_filled || HasSomethingChanged()){

                    ClearLine();
                    MoveCursor(kLeft, 50);

                    num_filled_ = new_num_filled;

                    std::cout << bookend_begin_style_.str() << bookend_begin_;

                    std::cout << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;

                    std::cout << filled_style_.str();
                    for(int i = 0; i < num_filled_; i++){
                        std::cout << filled_;
                    }

                    std::cout << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;

                    std::cout << unfilled_style_.str();
                    for(int i = 0; i < length_ - num_filled_; i++){
                        std::cout << unfilled_;
                    }

                    std::cout << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;

                    std::cout << bookend_end_style_.str() << bookend_end_;

                    std::cout << kAnsiEscapeBegin << kReset << kAnsiEscapeEndColor;

                    //MoveCursor(kRight, 20);

                    std::cout.flush();
                }
            }


            bool HasSomethingChanged(){
                if(something_changed_){
                    something_changed_ = false;
                    return true;
                }
                return false;
            }

            void SetDefaults(){
                if(!bookend_begin_set_) bookend_begin_ = '[';
                if(!bookedn_end_set_) bookend_end_ = ']';
                if(!filled_set_) filled_ = '#';
                if(!unfilled_set_) unfilled_ = ' ';
            }

    };


}


#endif // end of TermFormH