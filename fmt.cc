#define FMT_HEADER_ONLY

#include <fmt/color.h>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <string>


  std::string getTimeStamp()
    {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(localtime(&now_c), "%H:%M:%S");
        return ss.str();
    }




auto Print_Time_Stamp(std::string str1){
  fmt::print(fg(fmt::color::floral_white) | fmt::emphasis::italic,getTimeStamp());
  fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
             "  [{}]        ", str1);


}


/* fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
             "Hello, {}!\n", "world");
  fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
             fmt::emphasis::underline, "Hello, {}!\n", "мир");
  fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
             "Hello, {}!\n", "世界");

  fmt::print(fg(fmt::color::crimson) | fmt::emphasis::italic,getTimeStamp());
  fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.",
  fmt::arg("name", "World"), fmt::arg("number", 42));*/







int main() {

    Print_Time_Stamp("Test");
    fmt::print(fg(fmt::color::green) | fmt::emphasis::bold,
             "Every Thing All fine.\n");
    
        fmt::print(fg(fmt::color::magenta) | fmt::emphasis::bold,
             "Every Thing All fine.\n");

 
 

 
}
