#include "Combo.h"

void initCombo(ComboBuffer* cb) {
    cb->index = 0;
    for (int i = 0; i < INPUT_BUFFER; i++) cb->buffer[i] = IN_NONE;
}

void pushInput(ComboBuffer* cb, InputType in, int) {
    cb->buffer[cb->index] = in;
    cb->index = (cb->index + 1) % INPUT_BUFFER;
}
