#pragma once
//--------------------------------------------------------------
// cpp standard library
//--------------------------------------------------------------
#include <iostream>
#include <chrono>
#include <functional>
#include <tuple>
//--------------------------------------------------------------
namespace TimeIt {
    //--------------------------------------------------------------
    class TimeIt {
        //--------------------------------------------------------------
        public:
            //--------------------------
            // Constructor 
            //--------------------------
            TimeIt(void);
            //--------------------------
            // Constructor 
            //--------------------------
            // std::string function_name: a string to pass the function name 
            //--------------------------
            // Examples of ways to pass the function name
            //------------
            // MSVC: __FUNCTION__, __FUNCDNAME__, __FUNCSIG__
            // GCC: __func__, __FUNCTION__, __PRETTY_FUNCTION__
            //--------------------------
            TimeIt(const std::string& function_name);
            //--------------------------
            // Destructor
            //--------------------------
            ~TimeIt(void);
            //--------------------------
            double get_time(void);
            //--------------------------
            std::tuple<double, std::string> get_time_unit(void);
            //--------------------------------------------------------------
        protected:
            //--------------------------
            std::tuple<double, std::string> determine_time_unit(const std::chrono::high_resolution_clock::duration& elapsed);
            //--------------------------------------------------------------
        private:
            //--------------------------
            const std::string m_function_name;
            //--------------------------
            bool m_get_time;
            //--------------------------
            const std::chrono::time_point<std::chrono::high_resolution_clock> m_start;    
        //--------------------------------------------------------------
    };// end class TimeIt
    //--------------------------------------------------------------
} // end namespace TimeIt
//--------------------------------------------------------------