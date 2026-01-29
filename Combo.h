/*#pragma once

#define INPUT_BUFFER 16

enum InputType {
    IN_NONE,
    IN_X,
    IN_Y,
    IN_LEFT,
    IN_RIGHT
};

struct ComboBuffer {
    InputType buffer[INPUT_BUFFER];
    float time[INPUT_BUFFER];
    int index;
};

void initCombo(ComboBuffer* cb);
void pushInput(ComboBuffer* cb, InputType in, float t);
int checkComboXXX(ComboBuffer* cb);
int checkComboXYX(ComboBuffer* cb); */

