#include <AK/LogStream.h>
#include <AK/String.h>
#include <LibJS/GlobalObject.h>
#include <LibJS/Heap.h>
#include <LibJS/Interpreter.h>
#include <LibJS/NativeFunction.h>
#include <LibJS/Value.h>
#include <stdio.h>

namespace JS {

GlobalObject::GlobalObject()
{
    put_native_function("print", [](Interpreter&, Vector<Value> arguments) -> Value {
        for (auto& argument : arguments)
            printf("%s ", argument.to_string().characters());
        return js_undefined();
    });
    // put_native_function("gc", [](Interpreter& interpreter, Vector<Value>) -> Value {
    //     dbg() << "Forced garbage collection requested!";
    //     interpreter.heap().collect_garbage();
    //     return js_undefined();
    // });
}

GlobalObject::~GlobalObject()
{
}

}
