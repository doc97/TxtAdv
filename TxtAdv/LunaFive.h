/*
Source: http://lua-users.org/wiki/LunaFive 20.12.2018
Edited: Spacing, indentation, includes by Daniel Riissanen 20.12.2018
Edited: Combine with some of Lunar's code: http://lua-users.org/wiki/CppBindingWithLunar 21.12.2018
        Modify and customize functions
*/

#pragma once

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#include <cstring> // For strlen

template<class T>
class Luna
{
    // private by default
    typedef struct { T* pT; } userdataType;
public:
    struct PropertyType
    {
        const char*     name;
        int             (T::*getter) (lua_State *);
        int             (T::*setter) (lua_State *);
    };

    struct FunctionType
    {
        const char*     name;
        int             (T::*func) (lua_State *);
    };

    /*
      @ check
      Arguments:
        * L - Lua State
        * narg - Position to check

      Description:
        Retrieves a wrapped class from the arguments passed to the func, specified by narg (position).
        This func will raise an exception if the argument is not of the correct type.
    */
    static T* check(lua_State* L, int narg)
    {
        T** obj = static_cast<T**>(luaL_checkudata(L, narg, T::className));
        if (!obj)
            return nullptr; // lightcheck returns nullptr if not found.
        return *obj;        // pointer to T object
    }

    /*
      @ lightcheck
      Arguments:
        * L - Lua State
        * narg - Position to check

      Description:
        Retrieves a wrapped class from the arguments passed to the func, specified by narg (position).
        This func will return nullptr if the argument is not of the correct type.  Useful for supporting
        multiple types of arguments passed to the func
    */
    static T* lightcheck(lua_State* L, int narg) {
        T** obj = static_cast<T**>(luaL_testudata(L, narg, T::className));
        if (!obj)
            return nullptr; // lightcheck returns nullptr if not found.
        return *obj;        // pointer to T object
    }

    /*
      @ Register
      Arguments:
        * L - Lua State
        * namespac - Namespace to load into

      Description:
        Registers your class with Lua.  Leave namespac "" if you want to load it into the global space.
    */
    // REGISTER CLASS AS A GLOBAL TABLE
    static void Register(lua_State* L, const char *namespac = NULL ) {

        if (namespac && strlen(namespac))
        {
            lua_getglobal(L, namespac);

            // Create namespace if not present
            if(lua_isnil(L,-1))
            {
                lua_newtable(L);
                lua_pushvalue(L,-1); // Duplicate table pointer since setglobal pops the value
                lua_setglobal(L,namespac);
            }
            lua_pushcfunction(L, &Luna<T>::constructor);
            lua_setfield(L, -2, T::className);
            lua_pop(L, 1);
        }
        else
        {
            lua_pushcfunction(L, &Luna<T>::constructor);
            lua_setglobal(L, T::className);
        }

        luaL_newmetatable(L, T::className);
        int metatable = lua_gettop(L);

        lua_pushstring(L, "__gc");
        lua_pushcfunction(L, &Luna<T>::gc_obj);
        lua_settable(L, metatable);

        lua_pushstring(L, "__tostring");
        lua_pushcfunction(L, &Luna<T>::to_string);
        lua_settable(L, metatable);

        // To be able to compare two Luna objects (not natively possible with full userdata)
        lua_pushstring(L, "__eq");
        lua_pushcfunction(L, &Luna<T>::equals);
        lua_settable(L, metatable);

        lua_pushstring(L, "__index");
        lua_pushcfunction(L, &Luna<T>::property_getter);
        lua_settable(L, metatable);

        lua_pushstring(L, "__newindex");
        lua_pushcfunction(L, &Luna<T>::property_setter);
        lua_settable(L, metatable);

        // Register some properties in it
        for (size_t i = 0; T::properties[i].name; ++i)
        {
            lua_pushstring(L, T::properties[i].name);   // Having some string associated with them
            lua_pushnumber(L, i);                       // And a number indexing which property it is
            lua_settable(L, metatable);
        }

        for (size_t i = 0; T::methods[i].name; ++i)
        {
            lua_pushstring(L, T::methods[i].name);  // Register some functions in it
            lua_pushnumber(L, i | ( 1 << 8 ) );     // Add a number indexing which func it is
            lua_settable(L, metatable);
        }
    }

    /*
      @ constructor (internal)
      Arguments:
        * L - Lua State
    */
    static int constructor(lua_State* L)
    {
        T*  ap = new T(L);
        T** a = static_cast<T**>(lua_newuserdata(L, sizeof(T*))); // Push value = userdata
        *a = ap;

        // Fetch global metatable T::classname
        luaL_getmetatable(L, T::className);
        lua_setmetatable(L, -2);
        return 1;
    }

    /*
      @ createNew
      Arguments:
        * L - Lua State
        T*	- Instance to push

      Description:
        Loads an instance of the class into the Lua stack, and provides you a pointer so you can modify it.
    */
    static void push(lua_State* L, T* instance)
    {
        T** a = (T**) lua_newuserdata(L, sizeof(T*)); // Create userdata
        *a = instance;

        luaL_getmetatable(L, T::className);
        lua_setmetatable(L, -2);
    }

    /*
      @ new_global
      Arguments:
        * L - Lua State
        * obj - Pointer to object
        * name - The name of the variable that will hold the pointer in the global namespace
        bool - Whether or not to delete the object when the userdata gc event occurs
    */
    static int new_global(lua_State* L, T* obj, const char* name, bool gc = false)
    {
        if (!obj)
        {
            lua_pushnil(L);
            return 0;
        }

        luaL_getmetatable(L, T::className);
        if (lua_isnil(L, -1))
            luaL_error(L, "%s missing metatable", T::className);

        int mt = lua_gettop(L);
        subtable(L, mt, "userdata", "v");
        userdataType* data = static_cast<userdataType*>(pushuserdata(L, obj, sizeof(userdataType)));
        if (data)
        {
            data->pT = obj;  // store pointer to object in userdata
            lua_pushvalue(L, mt);
            lua_setmetatable(L, -2);
            if (!gc)
            {
                lua_checkstack(L, 3);
                subtable(L, mt, "do not trash", "k");
                lua_pushvalue(L, -2);
                lua_pushboolean(L, 1);
                lua_settable(L, -3);
                lua_pop(L, 1);
            }
        }
        lua_replace(L, mt);
        lua_settop(L, mt);

        // Add global variable
        lua_pushvalue(L, mt);
        lua_setglobal(L, name);

        return mt;
    }

    /*
      @ pushuserdata
      Arguments:
        * L - Lua State
        * key - Light userdata
        size_t - The size of new full userdata if lookup[key] = nil
    */
    static void* pushuserdata(lua_State* L, void* key, size_t size)
    {
        void* data = NULL;
        lua_pushlightuserdata(L, key);
        lua_gettable(L, -2);  // lookup[key]
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);  // drop nil
            lua_checkstack(L, 3);
            data = lua_newuserdata(L, size);  // create new userdata
            lua_pushlightuserdata(L, key);
            lua_pushvalue(L, -2); // duplicate userdata
            lua_settable(L, -4);  // lookup[key] = userdata
        }
        return data;
    }

    /*
      @ weaktable
      Arguments:
        * L - Lua State
        *mode - Metatable __mode field
    */
    static void weaktable(lua_State* L, const char* mode)
    {
        lua_newtable(L);
        lua_pushvalue(L, -1); // table as its own metatable
        lua_setmetatable(L, -2);
        lua_pushliteral(L, "__mode");
        lua_pushstring(L, mode);
        lua_settable(L, -3);  // metatable.__mode = mode
    }

    /*
      @ subtable
      Arguments:
        * L - Lua State
        tindex - Table index
        *name - Name of the subtable
        *mode - Metatable __mode field
    */
    static void subtable(lua_State* L, int tindex, const char* name, const char* mode)
    {
        lua_pushstring(L, name);
        lua_gettable(L, tindex);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            lua_checkstack(L, 3);
            weaktable(L, mode);
            lua_pushstring(L, name);
            lua_pushvalue(L, -2);
            lua_settable(L, tindex);
        }
    }

    /*
      @ property_getter (internal)
      Arguments:
        * L - Lua State
    */
    static int property_getter(lua_State* L)
    {
        lua_getmetatable(L, 1); // Look up the index of a name
        lua_pushvalue(L, 2);    // Push the name
        lua_rawget(L, -2);      // Get the index

        if (lua_isnumber(L, -1)) { // Check if we got a valid index
            int _index = static_cast<int>(lua_tonumber(L, -1));
            T** obj = static_cast<T**>(lua_touserdata(L, 1));

            lua_pushvalue(L, 3);

            if(_index & ( 1 << 8 )) // A func
            {
                // Push the right func index
                lua_pushnumber(L, _index ^ ( 1 << 8 ));
                lua_pushlightuserdata(L, obj);
                lua_pushcclosure(L, &Luna<T>::function_dispatch, 2);
                return 1; // Return a func
            }

            lua_pop(L,2);    // Pop metatable and _index
            lua_remove(L,1); // Remove userdata
            lua_remove(L,1); // Remove [key]

            return ((*obj)->*(T::properties[_index].getter)) (L);
        }
        return 1;
    }

    /*
      @ property_setter (internal)
      Arguments:
        * L - Lua State
    */
    static int property_setter(lua_State* L)
    {
        lua_getmetatable(L, 1); // Look up the index from name
        lua_pushvalue(L, 2);
        lua_rawget(L, -2);

        if (lua_isnumber(L, -1)) // Check if we got a valid index
        {
            int _index = static_cast<int>(lua_tonumber(L, -1));
            T** obj = static_cast<T**>(lua_touserdata(L, 1));

            if(!obj || !(*obj))
            {
                luaL_error( L , "Internal error, no object given!" );
                return 0;
            }

            if(_index >> 8) // Try to set a func
            {
                char c[128];
                sprintf_s(c, "Trying to set the method [%s] of class [%s]" ,
                    (*obj)->T::methods[_index ^ ( 1 << 8 )].name , T::className);
                luaL_error(L, c);
                return 0;
            }

            lua_pop(L,2);    // Pop metatable and _index
            lua_remove(L,1); // Remove userdata
            lua_remove(L,1); // Remove [key]

            return ((*obj)->*(T::properties[_index].setter)) (L);
        }
        return 0;
    }

    /*
      @ function_dispatch (internal)
      Arguments:
        * L - Lua State
    */
    static int function_dispatch(lua_State* L)
    {
        int i = static_cast<int>(lua_tonumber(L, lua_upvalueindex(1)));
        T** obj = static_cast<T**>(lua_touserdata(L, lua_upvalueindex(2)));
        return ((*obj)->*(T::methods[i].func)) (L);
    }

    /*
      @ gc_obj (internal)
      Arguments:
        * L - Lua State
    */
    static int gc_obj(lua_State* L)
    {
        if (luaL_getmetafield(L, 1, "do not trash"))
        {
            lua_pushvalue(L, 1); // duplicate userdata
            lua_gettable(L, -2);
            if (!lua_isnil(L, -1))
                return 0;
        }
        T** obj = static_cast<T**>(lua_touserdata(L, -1));
        if (obj && *obj)
            delete(*obj);
        return 0;
    }

    static int to_string(lua_State* L)
    {
        T** obj = static_cast<T**>(lua_touserdata(L, -1));
        if (obj)
            lua_pushfstring(L, "%s (%p)", T::className, (void*)*obj);
        else
            lua_pushstring(L,"Empty object");

        return 1;
    }

    /*
     * Method which compares two Luna objects.
     * The full userdatas (as opposed to light userdata) can't be natively compared one to other, we have to had this to do it.
     */
    static int equals(lua_State* L)
    {
        T** obj1 = static_cast<T**>(lua_touserdata(L, -1));
        T** obj2 = static_cast<T**>(lua_touserdata(L, 1));
        lua_pushboolean(L, *obj1 == *obj2);
        return 1;
    }
};
