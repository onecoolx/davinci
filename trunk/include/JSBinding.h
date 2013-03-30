
#ifndef _JSBinging_H_
#define _JSBinging_H_

#ifdef __cplusplus
extern "C"{
#endif

/**
 * The JSConstructor defines the type of the native implementation of
 * the JS object constructor.
 */
typedef JSObjectCallAsConstructorCallback JSConstructor;

/**
 * The JSDestructor defines the type of the native implementation of
 * the JS object destructor.
 */
typedef JSObjectFinalizeCallback JSDestructor;

/**
 * The JSMethod describes the type of the native implementation of
 * the JS object methods.
 */
typedef JSStaticFunction JSMethod;

/**
 * The JSNativeFunction defines the type of the native implementation of
 * the JS function.
 */
typedef JSStaticFunction JSNativeFunction;

/**
 * The JSMethod describes the type of the native implementation of
 * the JS object properties.
 */
typedef JSStaticValue JSProperty;

/**
 * A JSNativeClass describes a class of the Javascript native binding objects.
 * A C/C++ programe can use JSNativeClass with macross_js_define_class
 * API to create objects that have custom methods and properties implemented
 * in C/C++.
 */
typedef struct _JSNativeClass JSNativeClass;

struct _JSNativeClass {
    /** Class name */
    const char    *name;
    /** JavaScript native binding version: default 0 */
    int           version;
    /** Pointer to the constructor for the object that represents this class */
    JSConstructor ctor;
    /** Pointer to the destructor for the object that represents this class */
    JSDestructor  dtor;
    /** Pointer to the methods for the object that represents this class */
    JSMethod      *method;
    /** Pointer to the properties for the object that represents this class */
    JSProperty    *property; 
};

#ifdef __cplusplus
}
#endif

#endif /*_JSBinging_H_*/
