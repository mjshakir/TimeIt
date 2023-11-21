#pragma once
//--------------------------------------------------------------
// User Defined library
//--------------------------------------------------------------
#include "TimeIt.hpp"
//--------------------------------------------------------------
// cpp standard library
//--------------------------------------------------------------
#include <type_traits>
//--------------------------------------------------------------
namespace TimeIt {
    //--------------------------------------------------------------
    class TimeFunction {
        //--------------------------------------------------------------
        public:
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<!std::is_void_v<ReturnType>>>
            static ReturnType timed_Function(const std::function<ReturnType(Args...)>& function, const Args&... args){
                //--------------------------
                return time_function(function, args...);
                //--------------------------
            }// end ReturnType timed_Function(const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<std::is_void_v<ReturnType>>>
            static void timed_Function(const std::function<ReturnType(Args...)>& function, const Args&... args){
                //--------------------------
                time_function(function, args...);
                //--------------------------
            }// end ReturnType timed_Function(const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<!std::is_void_v<ReturnType>>>
            static std::tuple<ReturnType, double, std::string> timed_unit_Function(const std::function<ReturnType(Args...)>& function, const Args&... args){
                //--------------------------
                return time_unit_function(function, args...);
                //--------------------------
            }// end std::tuple<ReturnType, double, std::string> timed_unit_Function(const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<std::is_void_v<ReturnType>>>
            static std::tuple<double, std::string> timed_unit_Function(const std::function<ReturnType(Args...)>& function, const Args&... args){
                //--------------------------
                return time_unit_function(function, args...);
                //--------------------------
            }// end std::tuple<ReturnType, double, std::string> timed_unit_Function(const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<!std::is_void_v<ReturnType>>>
            static ReturnType timed_Function(const std::string& function_name, const std::function<ReturnType(Args...)>& function, const Args&... args){
                //--------------------------
                return time_function(function_name, function, args...);
                //--------------------------
            }// end ReturnType timed_Function(const std::string& function_name, const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<std::is_void_v<ReturnType>>>
            static void timed_Function(const std::string& function_name, const std::function<ReturnType(Args...)>& function, const Args&... args){
                //--------------------------
                time_function(function_name, function, args...);
                //--------------------------
            }// end ReturnType timed_Function(const std::string& function_name, const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------------------------------------------
        protected:
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<!std::is_void_v<ReturnType>>>
            static ReturnType time_function(const std::function<ReturnType(Args...)>& function, const Args&... args) {
                //--------------------------
                TimeIt timer;
                //--------------------------
                return function(args...);
                //--------------------------
            }// end ReturnType time_function(const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<std::is_void_v<ReturnType>>>
            static void time_function(const std::function<ReturnType(Args...)>& function, const Args&... args) {
                //--------------------------
                TimeIt timer;
                //--------------------------
                function(args...);
                //--------------------------
            }// end ReturnType time_function(const std::function<ReturnType(Args...)>& function, const Args&... args)
            //--------------------------
            // For non-void return types
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<!std::is_void_v<ReturnType>>>
            static std::tuple<ReturnType, double, std::string> time_unit_function(const std::function<ReturnType(Args...)>& function, Args... args) {
                //--------------------------
                TimeIt timer;
                //--------------------------
                ReturnType result = function(args...);
                //--------------------------
                auto [time, unit] = timer.get_time_unit();
                //--------------------------
                return {result, time, unit};
                //--------------------------
            }// end std::tuple<ReturnType, double, std::string> time_unit_function(const std::function<ReturnType(Args...)>& function, Args... args)
            //--------------------------
            // Specialization for void return type
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<std::is_void_v<ReturnType>>>
            static std::tuple<double, std::string> time_unit_function(const std::function<ReturnType(Args...)>& function, Args... args) {
                //--------------------------
                TimeIt timer;
                //--------------------------
                function(args...);
                //--------------------------
                auto [time, unit] = timer.get_time_unit();
                //--------------------------
                return {time, unit};
                //--------------------------
            }// end std::tuple<double, std::string> time_unit_function(const std::function<void(Args...)>& function, Args... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<!std::is_void_v<ReturnType>>>
            static ReturnType time_function(const std::string& function_name, const std::function<ReturnType(Args...)>& function, const Args&... args) {
                //--------------------------
                TimeIt timer(function_name);
                //--------------------------
                return function(args...);
                //--------------------------
            }// end ReturnType time_function(const std::string& function_name, const std::function<ReturnType(const Args&...)>& function, const Args&... args)
            //--------------------------
            template <typename ReturnType, typename... Args,
                    typename = std::enable_if_t<std::is_void_v<ReturnType>>>
            static void time_function(const std::string& function_name, const std::function<ReturnType(Args...)>& function, const Args&... args) {
                //--------------------------
                TimeIt timer(function_name);
                //--------------------------
                function(args...);
                //--------------------------
            }// end ReturnType time_function(const std::string& function_name, const std::function<ReturnType(const Args&...)>& function, const Args&... args)
        //--------------------------------------------------------------
    };// end class TimeFunction
    //--------------------------------------------------------------
} // end namespace TimeFunction
//--------------------------------------------------------------