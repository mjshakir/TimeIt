//--------------------------------------------------------------
// Main Header 
//--------------------------------------------------------------
#include "TimeIt.hpp"
//--------------------------------------------------------------
// Definitions
//--------------------------------------------------------------
// ANSI colors
//--------------------------
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//--------------------------------------------------------------
TimeIt::TimeIt::TimeIt(void) : m_function_name("Unknown"), m_get_time(false), m_start(std::chrono::high_resolution_clock::now()) {
    //--------------------------
}// end TimeIt::TimeIt::TimeIt()
//--------------------------------------------------------------
TimeIt::TimeIt::TimeIt(const std::string& function_name) : m_function_name(function_name), m_get_time(false), m_start(std::chrono::high_resolution_clock::now()) {
    //--------------------------
}// end TimeIt::TimeIt::TimeIt(const std::string& function_name)
//--------------------------------------------------------------
TimeIt::TimeIt::~TimeIt(void){
    //--------------------------
    if(!m_get_time){ 
        //--------------------------
        auto [time, unit] = determine_time_unit(std::chrono::high_resolution_clock::now() - m_start);
        //--------------------------
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET " Execution time: [" ANSI_COLOR_RED "%f " ANSI_COLOR_RESET "%s]\n", 
                m_function_name.c_str(), time, unit.c_str());
        //--------------------------
    }// end if(!m_get_time)
    //--------------------------
}// end TimeIt::TimeIt::~TimeIt()
//--------------------------------------------------------------
double TimeIt::TimeIt::get_time(void){
    //--------------------------
    m_get_time = true;
    //--------------------------
    return std::chrono::duration<double, std::chrono::nanoseconds::period>(std::chrono::high_resolution_clock::now() - m_start).count();
    //--------------------------
}// end double TimeIt::TimeIt::get_time(void)
//--------------------------------------------------------------
std::tuple<double, std::string> TimeIt::TimeIt::get_time_unit(void){
    //--------------------------
    m_get_time = true;
    //--------------------------
    return determine_time_unit(std::chrono::high_resolution_clock::now() - m_start);
    //--------------------------
}// end std::tuple<double, std::string> TimeIt::TimeIt::get_time_unit(void)
//--------------------------------------------------------------
std::tuple<double, std::string> TimeIt::TimeIt::determine_time_unit(const std::chrono::high_resolution_clock::duration& elapsed){
    //--------------------------
    if (std::chrono::duration_cast<std::chrono::days>(elapsed).count() >= 1) {
        return {std::chrono::duration<double, std::chrono::days::period>(elapsed).count(), "days"};
    }// end if (std::chrono::duration_cast<std::chrono::days>(elapsed).count() >= 1)
    if (std::chrono::duration_cast<std::chrono::hours>(elapsed).count() >= 1) {
        return {std::chrono::duration<double, std::chrono::hours::period>(elapsed).count(), "hours"};
    }// end if (std::chrono::duration_cast<std::chrono::hours>(elapsed).count() >= 1)
    if (std::chrono::duration_cast<std::chrono::minutes>(elapsed).count() >= 1) {
        return {std::chrono::duration<double, std::chrono::minutes::period>(elapsed).count(), "minutes"};
    }// end if (std::chrono::duration_cast<std::chrono::minutes>(elapsed).count() >= 1)
    if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 1) {
        return {std::chrono::duration<double, std::chrono::seconds::period>(elapsed).count(), "seconds"};
    }// end if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 1)
    if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() >= 1) {
        return {std::chrono::duration<double, std::chrono::milliseconds::period>(elapsed).count(), "milliseconds"};
    }// end if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() >= 1)
    if (std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() >= 1) {
        return {std::chrono::duration<double, std::chrono::microseconds::period>(elapsed).count(), "microseconds"};
    }// end if (std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() >= 1)
    //--------------------------
    return {std::chrono::duration<double, std::chrono::nanoseconds::period>(elapsed).count(), "nanoseconds"};
    //--------------------------
}// end std::tuple<double, std::string> TimeIt::TimeIt::determine_time_unit(const std::chrono::high_resolution_clock::duration& elapsed)
//--------------------------------------------------------------