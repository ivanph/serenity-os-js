/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <AK/ByteBuffer.h>
#include <AK/NonnullOwnPtr.h>
#include <LibJS/AST.h>
#include <LibJS/Interpreter.h>
#include <LibJS/Object.h>
#include <LibJS/Parser.h>
#include <LibJS/PrimitiveString.h>
#include <LibJS/Value.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#define PROGRAM 6

int main(int argc, char** argv)
{
    JS::Interpreter interpreter;
    dbg() << "Start...";
    dbg() << "Created interpreter";
    ifstream file("./test.js");
    if (!file) {
       cout << "Unable to open file\n";
       exit(1);
    }
    stringstream strStream;
    strStream << file.rdbuf();
    dbg() << "Read file";
    auto file_contents = strStream.str();
    auto program = JS::Parser(JS::Lexer(file_contents.c_str())).parse_program();
    program->dump(0);
    auto result = interpreter.run(*program);
    dbg() << "Interpreter returned " << result;
    printf("%s\n", result.to_string().characters());
    dbg() << "Collecting garbage on exit...";
    interpreter.heap().collect_garbage();
    return 0;
}
