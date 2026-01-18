// combo.cpp
#include "Combo.h"

void initCombo(ComboBuffer* cb) {
    cb->index = 0;
    for (int i = 0; i < INPUT_BUFFER; i++) {
        cb->buffer[i] = IN_NONE;
        cb->time[i] = 0.0f;
    }
}

void pushInput(ComboBuffer* cb, InputType in, float t) {
    cb->buffer[cb->index] = in;
    cb->time[cb->index] = t;
    cb->index = (cb->index + 1) % INPUT_BUFFER;
}
