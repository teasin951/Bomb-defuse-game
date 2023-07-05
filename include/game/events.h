#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

/**
 * @file Declare all events
 * 
 * Events shall be granual to avoid switch statements for button presses in every state
*/

/**
 * @brief Event where displayed stuff shall be made up to date
 * 
 * This event should be called periodically from the main()
*/
struct Update : tinyfsm::Event {};

// ------------------------------------------------------------------- //

/**
 * @brief Event for a keypad press
*/
struct KeypadPressed : public tinyfsm::Event {};

/**
 * @brief Event for a specific key
*/
struct KeypadOnePressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadTwoPressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadThreePressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadFourPressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadFivePressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadSixPressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadSevenPressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadEightPressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadNinePressed : KeypadPressed {};

/**
 * @brief Event for a specific key
*/
struct KeypadZeroPressed : KeypadPressed {};

// ------------------------ //

/**
 * @brief Set sequence matched
*/
struct KeypadMatched : tinyfsm::Event {};

/**
 * @brief Set sequence did not matched
*/
struct KeypadNotMatched : tinyfsm::Event {};

/**
 * @brief Keypad sequence has been cleared
*/
struct KeypadCleared : tinyfsm::Event {};

/**
 * @brief Keypad sequence has overflowed
*/
struct KeypadOverflowed : tinyfsm::Event {};

// ------------------------------------------------------------------- //

/**
 * @brief Emergency button has just been pressed 
*/
struct EmergencyPressed : tinyfsm::Event {};

/**
 * @brief Emergency button has just been released
*/
struct EmergencyReleased : tinyfsm::Event {};

// ------------------------------------------------------------------- //

/**
 * @brief Potenciometer1 has been moved
*/
struct Potenciometer1Moved : tinyfsm::Event {
    /**
     * @brief Construct event with the new value;
    */
    Potenciometer1Moved( int new_amount ) : current_amount(new_amount) {}
    int current_amount;
};

/**
 * @brief Potenciometer2 has been moved
*/
struct Potenciometer2Moved : tinyfsm::Event {
    /**
     * @brief Construct event with the new value;
    */
    Potenciometer2Moved( int new_amount ) : current_amount(new_amount) {}
    int current_amount;
};

/**
 * @brief Potenciometer3 has been moved
*/
struct Potenciometer3Moved : tinyfsm::Event {
    /**
     * @brief Construct event with the new value
    */
    Potenciometer3Moved( int new_amount ) : current_amount(new_amount) {}
    int current_amount;
};

// ------------------------------------------------------------------- //

/**
 * @brief Joystick has been moved event
*/
struct JoystickMoved : tinyfsm::Event {
    /**
     * @brief Construct joystick move event with the new values
    */
    JoystickMoved( uint16_t x, uint16_t y ) : x(x), y(y) {}

    uint16_t x;
    uint16_t y;
};

/**
 * @brief Joystick has been pressed
*/
struct JoystickPressed : tinyfsm::Event {};

// ------------------------------------------------------------------- //

/**
 * @brief ADKeyboard has been tempered with
*/
struct ADKeyboardPressed : tinyfsm::Event {};

/**
 * @brief Left key on the ADKeyboard has been pressed
*/
struct ADKeyboardLeftPressed : ADKeyboardPressed {};

/**
 * @brief Right key on the ADKeyboard has been pressed
*/
struct ADKeyboardRightPressed : ADKeyboardPressed {};

/**
 * @brief Up key on the ADKeyboard has been pressed
*/
struct ADKeyboardUpPressed : ADKeyboardPressed {};

/**
 * @brief Down key on the ADKeyboard has been pressed
*/
struct ADKeyboardDownPressed : ADKeyboardPressed {};

/**
 * @brief Enter key on the ADKeyboard has been pressed
*/
struct ADKeyboardEnterPressed : ADKeyboardPressed {};

// ------------------------ //

/**
 * @brief Left key on the ADKeyboard has been held
*/
struct ADKeyboardLeftHeld : tinyfsm::Event {};

/**
 * @brief Right key on the ADKeyboard has been held
*/
struct ADKeyboardRightHeld : tinyfsm::Event {};

/**
 * @brief Up key on the ADKeyboard has been held
*/
struct ADKeyboardUpHeld : tinyfsm::Event {};

/**
 * @brief Down key on the ADKeyboard has been held
*/
struct ADKeyboardDownHeld : tinyfsm::Event {};

/**
 * @brief Enter key on the ADKeyboard has been held
*/
struct ADKeyboardEnterHeld : tinyfsm::Event {};

// ------------------------------------------------------------------- //