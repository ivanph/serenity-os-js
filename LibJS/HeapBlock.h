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

#pragma once

#include <AK/Types.h>
#include <LibJS/Cell.h>
#include <LibJS/Forward.h>

namespace JS {

class HeapBlock {
public:
    static constexpr size_t block_size = 16 * KB;
    static NonnullOwnPtr<HeapBlock> create_with_cell_size(Heap&, size_t);

    void operator delete(void*);

    size_t cell_size() const { return m_cell_size; }
    size_t cell_count() const { return (block_size - sizeof(HeapBlock)) / m_cell_size; }

    Cell* cell(size_t index) { return reinterpret_cast<Cell*>(&m_storage[index * cell_size()]); }

    Cell* allocate();
    void deallocate(Cell*);

    template<typename Callback>
    void for_each_cell(Callback callback)
    {
        for (size_t i = 0; i < cell_count(); ++i)
            callback(cell(i));
    }

    Heap& heap() {
        dbg() << "HEAP!!!";
        return m_heap; 
    }

    static HeapBlock* from_cell(Cell* cell)
    {
        return reinterpret_cast<HeapBlock*>((FlatPtr)cell & ~(block_size - 1));
    }

private:
    HeapBlock(Heap&, size_t cell_size);

    struct FreelistEntry : public Cell {
        FreelistEntry* next;
    };

    Heap& m_heap;
    size_t m_cell_size { 0 };
    FreelistEntry* m_freelist { nullptr };
    u8 m_storage[];
};

}
