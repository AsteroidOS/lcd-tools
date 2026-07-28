# Adding a new feature
To add a new feature first add it to the `featurelist.h` file.  Note that this only provides a consistent place to name features.  Implementation is done for each watch.

# Adding a new watch
Adding a new watch, assuming you already know how to activate and deactivate the features it has requires a few simple steps.  Many places use the code name for the watch, so in the instructions below, we use `<codename>` as a placeholder for the actual name.

 1. create `<codename>-tools.h`
 2. create `<codename>-tools.cpp`
 3. add `<codename>-tools.cpp` to the `src/CMakeLists.txt` file
 4. add the watch to `lcd-tools.cpp`

Each step is described in more detail below.

## create `<codename>-tools.h`
The header file is usually very simple.  For example, a simplified version of `catfish-tools.h` is shown here:

```c++
#ifndef CATFISH_TOOLS_H
#define CATFISH_TOOLS_H
#include "featurelist.h"

class Catfish : public IWatch {
public:
    Catfish();
    ~Catfish() final;
    SyncTime st;
    PrepareTimepiece pt;
    SessionRestart sr;
private:
    void sync_time();
    void prepare_timepiece();
    void session_restart();
};
#endif /* CATFISH_TOOLS_H */
```

The key points here are that it must derive from `IWatch`, and that each named feature must be listed.  Any required member functions can be listed here.  An alternative is to use free-standing `static` functions within the implementation file, as described in the next section.

## create `<codename>-tools.cpp`
This is where most of the new code lives for a watch.  In some cases, it may be convenient to have an object in which the initialization is handled as part of the constructor.  For example, the `catfish.cpp` implementation uses this to open a shared library.  In such cases, it's also often important to have the destructor clean up any resources explicitly if they're not automatically handled.

For each named feature, initialize it in the constructor of your class in the same order that they are listed in the declaration (the `.h` file).  The rules of C++ dictate that they will be initialied in declaration order anyway, so it's useful to list them in the same order in both places.

The style of implementation of each feature depends on whether you use static functions or class member functions.  For our simplified example `catfish.cpp` file, for example, it might look like this:

```c++
#include "catfish-tools.h"
#include <iostream>

Catfish::Catfish() 
    : st([this]{ sync_time(); }) 
    , pt([this]{ prepare_timepiece(); })
    , sr([this]{ session_restart(); })
{}

void Catfish::sync_time() {
    std::cout << "Invoking sync_time\n";
}
// other functions
```

Any invocable function that has a signature like `void function(void);` may be used.  In this case, we use a lambda to capture the `this` variable to make use of member functions and data.  For other implementation which don't need or use member functions or data, the lambda can be slightly simpler:

```c++
    st([]{ std::cout << "Invoking sync_time\n";})
```

Or if there is a static function which implements it, it might look like this:

```c++
static void sync_time() {
    // do some time syncing
}

    st(sync_time)
```

It's often the case that the only difference between and enable and a disable call is some data in a function call.  In this case we can have a single function and use a lambda to call it:

```c++
static void heartate(bool enable)
{
    // enable or disable depending on the value of the "enable" parameter
}

// use this in our fictional Fishy watch constructor and features
Fishy::Fishy()
    : eh([]{ heartrate(true); }
    , dh([]{ heartrate(false); }
    // etc.
```

## add `<codename>-tools.cpp` to the `src/CMakeLists.txt` file

This should be as simple as adding the file name to the `add_executable()` line in the `src/CMakeLists.txt` file.  If other helper files are used, add those.  If addtional libraries are employed, you may have to add them to the `target_link_libraries` line.

## add the watch to `lcd-tools.cpp`

Finally, add the watch to the main file.  This is usually as simple as adding the appropriate `#include` line and adding to the `watches` list.
