#pragma once

struct T {
    int hour;
    int minute;
    int second;
    int msecond;

    bool operator ==(const T& other) {
        if (hour == other.hour && minute == other.minute && second == other.second && msecond == other.msecond)
        { return 1; } else { return 0; }
    }

    bool operator !=(const T& other) {
        if (hour != other.hour || minute != other.minute || second != other.second || msecond != other.msecond)
        { return 1; } else { return 0; }
    }
} typedef T;